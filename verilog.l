%{
#include <stdio.h>
#include <errno.h>
#include <string>
#include <vector>
#include "public.h"
#include "parse_misc.h"
#include "FileParse.h"
#include "verilog.tab.hpp"
using namespace std;

int file_num;
int file_num_max;
static int line_num=1;
static int column=1;
static int pos=0;
char **files;
FileParse * my_parse=NULL;
static int state_stack[20];
static int state_sp=0;
static int ifdel_deep=0;
extern int errno;
static int lookup_key_word(char * yytext, int begin_pos, int yyleng);
#define RECORD_YYLLOC  do { 			\
        yylloc.first_line = line_num;   \
        yylloc.first_column = column;   \
        yylloc.begin_pos = pos;         \
        column+=yyleng;                 \
        pos+=yyleng;                    \
        yylloc.last_line = line_num;    \
        yylloc.last_column = column;    \
        yylloc.end_pos = pos;           \
        ASSERT(my_parse->get_text(yylloc.begin_pos, yylloc.end_pos)==yytext); \
    } while(0)

#define PUSH_STATE state_stack[state_sp++] = YY_START
#define POP_STATE BEGIN(state_stack[--state_sp])
%}
%x CCOMMENT
%x LCOMMENT
%x CSTRING
%x PPTIMESCALE
%x IFDEF_DEL
%x IFDEF_JUDGE
%x IFNDEF_JUDGE
%x ELSE_DEL
%s IFDEF_ACCEPT
%s ELSE_ACCEPT
%s DEFINE
%x STATE_NAME
W [ \t\b\f\r]+
%%
"//sname="				{ column+=yyleng; pos+=yyleng; PUSH_STATE; BEGIN(STATE_NAME); }
<STATE_NAME>[a-zA-Z_][a-zA-Z0-9$_]* {
							RECORD_YYLLOC; 
							BEGIN(LCOMMENT); 
							yylval.emt = my_parse->element_new(pos-yyleng, pos, line_num,  Element::ELEMENT_NORMAL, 0);
							return STATENAME; 
						}
"//dowhile"				{RECORD_YYLLOC; PUSH_STATE; BEGIN(LCOMMENT); return K_dowhile; }						
"//"                    { column+=yyleng; pos+=yyleng; PUSH_STATE; BEGIN(LCOMMENT); }
<LCOMMENT>.             { column+=yyleng; pos+=yyleng;}
<LCOMMENT>\n            { column=1; line_num++; pos+=1; POP_STATE; }
"/*"                    { column+=yyleng; pos+=yyleng; PUSH_STATE; BEGIN(CCOMMENT); }
<CCOMMENT>.             { column+=yyleng; pos+=yyleng;}
<CCOMMENT>\n            { column=1; line_num++; pos+=1;}
<CCOMMENT>"*/"          { column+=yyleng; pos+=yyleng; POP_STATE;}
\"                      { column+=yyleng; pos+=yyleng; PUSH_STATE; BEGIN(CSTRING); }
<CSTRING>\\\\           { column+=yyleng; pos+=yyleng; yymore(); /* Catch \\, which is a \ escaping itself */ }
<CSTRING>\\\"           { column+=yyleng; pos+=yyleng; yymore(); /* Catch \", which is an escaped quote */ }
<CSTRING>\n             { column=1; line_num++; pos+=1; POP_STATE; printf("Missing close quote of string at line %d", line_num); }
<CSTRING>\"             { RECORD_YYLLOC;  POP_STATE;  return STRING;}
<CSTRING>.              { column+=yyleng; pos+=yyleng; yymore(); }
^{W}?"`define"          { RECORD_YYLLOC;  PUSH_STATE; BEGIN(DEFINE); return K_define; }
^{W}?`undef             { RECORD_YYLLOC;  PUSH_STATE; BEGIN(DEFINE); return K_undef; }       
<DEFINE>\n              { yylloc.first_line = line_num;
                          yylloc.first_column = column;
                          yylloc.last_line = line_num;
                          yylloc.last_column = column+1;
                          yylloc.begin_pos = pos;
                          yylloc.end_pos = pos;
                          column=1; 
                          line_num++; 
                          pos+=1;
                          POP_STATE;                       
                          return K_enddefine; }                          
^{W}?`ifdef{W}?         { column+=yyleng; pos+=yyleng; PUSH_STATE; BEGIN(IFDEF_JUDGE); }
^{W}?`ifndef{W}?        { column+=yyleng; pos+=yyleng; PUSH_STATE; BEGIN(IFNDEF_JUDGE); }
<IFDEF_JUDGE>[a-zA-Z_][a-zA-Z0-9$_]*    { column+=yyleng; pos+=yyleng;
                                          if (my_parse->lookup_define(yytext))
                                              BEGIN(IFDEF_ACCEPT);
                                          else
                                              BEGIN(IFDEF_DEL);
                                        }
<IFDEF_JUDGE>\n         { printf("ifdef empty followed at line %d", line_num); exit(1); }
<IFNDEF_JUDGE>[a-zA-Z_][a-zA-Z0-9$_]*   { column+=yyleng; pos+=yyleng;
                                          if (!my_parse->lookup_define(yytext))
                                              BEGIN(IFDEF_ACCEPT);
                                          else
                                              BEGIN(IFDEF_DEL);
                                        }
<IFNDEF_JUDGE>.*        { printf("ifndef no valid identifier followed at line %d", line_num); exit(1); }                                        
<IFNDEF_JUDGE>\n        { printf("ifndef empty followed at line %d", line_num); exit(1); }                              
<IFDEF_DEL,ELSE_DEL>\n  { column=1; line_num++; pos+=1; }
<IFDEF_DEL,ELSE_DEL>.   { column+=yyleng; pos+=yyleng; }
<IFDEF_DEL,ELSE_DEL>^{W}?`ifdef  { column+=yyleng; pos+=yyleng; ifdel_deep++; }
<IFDEF_DEL,ELSE_DEL>^{W}?`ifndef { column+=yyleng; pos+=yyleng; ifdel_deep++; }
<IFDEF_DEL>^{W}?`else   { column+=yyleng; pos+=yyleng; 
                          if (ifdel_deep==0)
                              BEGIN(ELSE_ACCEPT);
                        }
<IFDEF_DEL,ELSE_DEL>^{W}?`endif { 
                          column+=yyleng; pos+=yyleng;
                          if (ifdel_deep==0)
                              POP_STATE;
                          else
                              ifdel_deep--;
                        }               
<IFDEF_ACCEPT>^{W}?`else        { column+=yyleng; pos+=yyleng; BEGIN(ELSE_DEL); } 
<ELSE_ACCEPT>^{W}?`else         { printf("`else is more than twice at line %d", line_num); exit(1); }
<IFDEF_ACCEPT,IFDEF_DEL,ELSE_ACCEPT,ELSE_DEL>^{W}?`elsif.*      { printf("not support elsif at line %d", line_num); exit(1); }       
<IFDEF_ACCEPT,ELSE_ACCEPT>^{W}?`endif   { column+=yyleng; pos+=yyleng; POP_STATE; }     
^`timescale.*           { RECORD_YYLLOC; return K_include;}
^`include{W}?.*         { RECORD_YYLLOC; return K_include; }
[a-zA-Z_][a-zA-Z0-9$_]* { RECORD_YYLLOC; return lookup_key_word(yytext, pos-yyleng, yyleng); }
\$([a-zA-Z0-9$_]+)      { RECORD_YYLLOC; return SYSTEM_IDENTIFIER; }
`[a-zA-Z_][a-zA-Z0-9$_]*        { RECORD_YYLLOC; return DEFINE_IDENTIFIER; }                       
\n                      { column =1; line_num++; pos+=1; }
"<<"                    { RECORD_YYLLOC; return K_LS; }
"<<<"                   { RECORD_YYLLOC; return K_LS; }
">>"                    { RECORD_YYLLOC; return K_RS; }
">>>"                   { RECORD_YYLLOC; return K_RSS; }
"<="                    { RECORD_YYLLOC; return K_LE; }
">="                    { RECORD_YYLLOC; return K_GE; }
"=>"                    { RECORD_YYLLOC; return K_EG; }
"=="                    { RECORD_YYLLOC; return K_EQ; }
"!="                    { RECORD_YYLLOC; return K_NE; }
"==="                   { RECORD_YYLLOC; return K_CEQ; }
"!=="                   { RECORD_YYLLOC; return K_CNE; }
"||"                    { RECORD_YYLLOC; return K_LOR; }
"&&"                    { RECORD_YYLLOC; return K_LAND; }
"~|"                    { RECORD_YYLLOC; return K_NOR; }
"~^"                    { RECORD_YYLLOC; return K_NXOR; }
"^~"                    { RECORD_YYLLOC; return K_NXOR; }
"~&"                    { RECORD_YYLLOC; return K_NAND; }
"->"                    { RECORD_YYLLOC; return K_TRIGGER; }
[}{;:\[\],()#=.@&!?<>%|^~+*/-]  { RECORD_YYLLOC; return *yytext; }
\'[sS]?[dD][ \t]*[0-9][0-9_]*   { RECORD_YYLLOC; return BASED_NUMBER; }
\'[sS]?[dD][ \t]*[xzXZ?]_*      { RECORD_YYLLOC; return BASED_NUMBER; }
\'[sS]?[bB][ \t]*[0-1xzXZ_\?]+  { RECORD_YYLLOC; return BASED_NUMBER; }
\'[sS]?[oO][ \t]*[0-7xzXZ_\?]+  { RECORD_YYLLOC; return BASED_NUMBER; }
\'[sS]?[hH][ \t]*[0-9a-fA-FxzXZ_\?]+    { RECORD_YYLLOC; return BASED_NUMBER; }
[0-9][0-9_]*            { RECORD_YYLLOC;  return DEC_NUMBER; }
.                       { column+=yyleng; pos+=yyleng; }
%%
static int lookup_key_word(char * yytext, int begin_pos, int yyleng)
{       
        if (strcmp(yytext, "always")==0)
                return K_always;
        if (strcmp(yytext, "assign")==0)
                return K_assign;
        if (strcmp(yytext, "automatic")==0)
                return K_automatic;
        if (strcmp(yytext, "begin")==0)
                return K_begin;
        if (strcmp(yytext, "case")==0)
                return K_case;
        if (strcmp(yytext, "casex")==0)
                return K_casex;
        if (strcmp(yytext, "casez")==0)
                return K_casez;
        if (strcmp(yytext, "deassign")==0)
                return K_deassign;
        if (strcmp(yytext, "default")==0)
                return K_default;
        if (strcmp(yytext, "defparam")==0)
                return K_defparam;
        if (strcmp(yytext, "disable")==0)
                return K_disable;
        if (strcmp(yytext, "else")==0)
                return K_else;
        if (strcmp(yytext, "end")==0)
                return K_end;
        if (strcmp(yytext, "endcase")==0)
                return K_endcase;
        if (strcmp(yytext, "endfunction")==0)
                return K_endfunction;
        if (strcmp(yytext, "endgenerate")==0)
                return K_endgenerate;   
        if (strcmp(yytext, "endmodule")==0)
                return K_endmodule;
        if (strcmp(yytext, "endspecify")==0)
                return K_endspecify;    
        if (strcmp(yytext, "endtask")==0)
                return K_endtask;
        if (strcmp(yytext, "event")==0)
                return K_event;
        if (strcmp(yytext, "for")==0)
                return K_for;
        if (strcmp(yytext, "force")==0)
                return K_force;
        if (strcmp(yytext, "forever")==0)
                return K_forever;
        if (strcmp(yytext, "fork")==0)
                return K_fork;
        if (strcmp(yytext, "function")==0)
                return K_function;
        if (strcmp(yytext, "generate")==0)
                return K_generate;
        if (strcmp(yytext, "genvar")==0)
                return K_genvar;
        if (strcmp(yytext, "if")==0)
                return K_if;
        if (strcmp(yytext, "initial")==0)
                return K_initial;
        if (strcmp(yytext, "inout")==0)
                return K_inout;
        if (strcmp(yytext, "input")==0)
                return K_input;
        if (strcmp(yytext, "integer")==0)
                return K_integer;       
        if (strcmp(yytext, "join")==0)
                return K_join;
        if (strcmp(yytext, "localparam")==0)
                return K_localparam;    
        if (strcmp(yytext, "macromodule")==0)
                return K_macromodule;
        if (strcmp(yytext, "module")==0)
                return K_module;
        if (strcmp(yytext, "negedge")==0)
                return K_negedge;
        if (strcmp(yytext, "or")==0)
                return K_or;
        if (strcmp(yytext, "output")==0)
                return K_output;
        if (strcmp(yytext, "parameter")==0)
                return K_parameter;
        if (strcmp(yytext, "posedge")==0)
                return K_posedge;
        if (strcmp(yytext, "reg")==0)
                return K_reg;
        if (strcmp(yytext, "release")==0)
                return K_release;
        if (strcmp(yytext, "repeat")==0)
                return K_repeat;
        if (strcmp(yytext, "signed")==0)
                return K_signed;
        if (strcmp(yytext, "specify")==0)
                return K_specify;               
        if (strcmp(yytext, "task")==0)
                return K_task;
        if (strcmp(yytext, "unsigned")==0)
                return K_unsigned;      
        if (strcmp(yytext, "wait")==0)
                return K_wait;
        if (strcmp(yytext, "while")==0)
                return K_while; 
        if (strcmp(yytext, "wire")==0)
                return K_wire;        
        yylval.emt = my_parse->element_new(begin_pos, begin_pos+yyleng, line_num, Element::ELEMENT_NORMAL, 0);
        if (strcmp(yytext, "ASYNC_RESET")==0)
        		return K_ASYNC_RESET;
        return IDENTIFIER;
}
int prepare(int argc, char *argv[]) {
        file_num=1;
        file_num_max = argc;
        files = argv;
        my_parse = new FileParse;           
        if ( argc > 1 ) {                
                my_parse->load_file(argv[file_num]);
                if ( (yyin = fopen(argv[file_num],"r")) == 0 ) {
                        perror(argv[file_num]);
                        exit(1);
                }
        } else {
                my_parse->load_file(".\\test\\t0.v");
                if ( (yyin = fopen(".\\test\\t0.v","r")) == 0 ) {
                        perror(argv[file_num]);
                        exit(1);
                }
        }    
        return 0;
}

int yywrap() {
        fclose(yyin);
        if (ifdel_deep>0) {
            printf("if endif mismatch");
            exit(1);
        }
        if ( ++file_num < file_num_max ) {
                delete my_parse;
                my_parse = new FileParse;
                my_parse->load_file(files[file_num]);
                if ( (yyin = fopen(files[file_num],"r")) == 0 ) {
                        perror(files[file_num]);
                        exit(1);
                }
                return 0;
        } else {
                return 1;
        }
}
