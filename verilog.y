%{
    #include <stdio.h>
    #include "parse_misc.h"
    #include "FileParse.h"
    #define YYDEBUG 1
    void yyerror(char *);
    int yylex(void); 
    extern FileParse * my_parse;
    AlwaysBlock *current_block =NULL;
    Statement * current_top_name_block =NULL;
    
    #define YYRHSLOC(Rhs, K) ((Rhs)[K])
    #define YYLLOC_DEFAULT(Current, Rhs, N)                             \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
          (Current).begin_pos    = YYRHSLOC (Rhs, 1).begin_pos;         \
          (Current).end_pos      = YYRHSLOC (Rhs, N).end_pos;           \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
          (Current).begin_pos    = (Current).end_pos     =              \
            YYRHSLOC (Rhs, 0).end_pos;                                  \
        }                                                               \
    while (0)
%}

%union {
    Element * emt;
    Expression *exp;
    Statement *smt;
    State *state;
    Assign * assign;
    Variable * var;
    int value;
};	
	
%token <emt> IDENTIFIER STATENAME K_ASYNC_RESET
%token SYSTEM_IDENTIFIER DEFINE_IDENTIFIER STRING BASED_NUMBER DEC_NUMBER
%token K_LE K_GE K_EG K_EQ K_NE K_CEQ K_CNE K_LS K_RS K_RSS
%token K_LOR K_LAND K_NAND K_NOR K_NXOR K_TRIGGER

%token K_always K_assign K_automatic K_begin K_case K_casex K_casez
%token K_deassign K_default K_define K_defparam K_disable K_dowhile
%token K_else K_end K_endcase K_enddefine K_endfunction K_endgenerate K_endmodule
%token K_endspecify K_endtask K_event K_for
%token K_force K_forever K_fork K_function K_generate K_genvar K_if
%token K_include K_initial K_inout K_input K_integer K_join
%token K_localparam K_macromodule K_module K_negedge
%token K_or K_output K_parameter K_posedge
%token K_reg K_release K_repeat
%token K_signed K_specify K_task K_undef K_unsigned
%token K_wait K_while K_wire

%type <emt> source_file define_item include_item statename_or_null 
%type <emt> module module_port_list_opt module_item_list module_item_list_opt module_item
%type <emt> block_item_decls block_item_decl block_item_decls_opt
%type <emt> net_variable_list net_variable list_of_identifiers register_variable_list register_variable
%type <smt> statement_syn statement_syn_or_null statement_syn_list
%type <exp> expr_primary expression expression_list_proper expression_list_with_nuls
%type <emt> hierarchy_identifier
%type <value> dimensions_opt signed_opt range_opt port_type reg_opt pos_or_neg_edge
%type <state> wait_cycle

%nonassoc less_than_K_else
%nonassoc K_else

%right '?' ':'
%left K_LOR
%left K_LAND
%left '|'
%left '^' K_NXOR K_NOR
%left '&' K_NAND
%left K_EQ K_NE K_CEQ K_CNE
%left K_GE K_LE '<' '>'
%left K_LS K_RS K_RSS
%left '+' '-'
%left '*' '/' '%'
%left UNARY_PREC

%%
main	:
		source_file {
				int prop =$1->get_prop();
				prop |=ELEMENT_FIRST_CHILD;
				$1->set_prop(prop);
				my_parse->output($1);
			}
		;
source_file
        : module {$$ = $1;}
        | define_item {$$ = $1;}
        | include_item {$$ = $1;}
        | source_file module { 
        		my_parse->append($1, $2);
        		$$ = $1;
        	}
        | source_file define_item {
        		my_parse->append($1, $2);
        		$$ = $1;
        	}
        | source_file include_item {
        		my_parse->append($1, $2);
        		$$ = $1;
        	}
        ;

include_item
		: K_include {
				$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);
			}
define_item
        : K_define error K_enddefine {
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);
        	}       
        | K_define IDENTIFIER expression K_enddefine { 
        		my_parse->add_define($2->get_text().c_str()); 
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);
            }         
        | K_define IDENTIFIER K_enddefine { 
        		my_parse->add_define($2->get_text().c_str());
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);
        	}
        | K_undef IDENTIFIER K_enddefine { 
        		my_parse->del_define($2->get_text().c_str()); 
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);
        	}
        ;
        
module  : module_start IDENTIFIER module_port_list_opt ';' module_item_list_opt K_endmodule {
				$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_MODULE, 0);				
				my_parse->born($$, $2);
				my_parse->born($$, $3);
				my_parse->born($$, $5);
			}
        ;
        
module_start 
		: K_module 
		| K_macromodule {printf("don't support macromodule at line %d", @$.first_line); exit(1);}

module_port_list_opt
        : '(' list_of_ports ')' {
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);
        	}       
        | '(' ')'{
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);
        	}  
        | {$$ = NULL;}
        ;

list_of_ports
        : IDENTIFIER
        | list_of_ports ',' IDENTIFIER
        ;
        
module_item_list_opt
        : module_item_list {$$ = $1;}        
        | {$$ = NULL;}
        ;
        
module_item_list
        : module_item_list module_item {
        		my_parse->append($1, $2);
        		$$ = $1;
        	}
        | module_item {$$ = $1;}
        ;       
                
module_item
        : K_wire signed_opt range_opt net_variable_list ';' {
        		int prop;
        		Element * b, *e;
        		
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);
        		prop = $2 | $3;        		
        		b = $4;
        		LOOP_LEVEL(b, e) {
        			Variable * v;
        			v = (Variable *) e->get_child(0);
        			ASSERT(v->get_emt_type() == Element::VARIABLE);
        			v->add_var_prop(prop);
        		}
        		my_parse->born($$, b);
        	}
        | port_type net_type_opt signed_opt range_opt list_of_identifiers ';' {
        		Element * b, *e;
        		Variable * vb, *v;
        		int prop;
        		
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);
        		prop = $1 | $3 | $4;        		
        		b = $5;        		
        		LOOP_LEVEL(b, e) {
        			v = my_parse->variable_new(e, prop);
        			if (b==e)
        				vb = v;
        			else
        				my_parse->append(vb, v);
        		}
        		my_parse->born($$, vb);
        	}
        | K_output K_reg signed_opt range_opt IDENTIFIER ';' {
        		int prop;
        		Variable * v;
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);
        		prop = VAR_REG | VAR_OUTPUT | $3 | $4;
        		v = my_parse->variable_new($5, prop);
        		my_parse->born($$, v);
        	}
        | block_item_decl {$$=$1;}
        | define_item {$$=$1;}
        | K_always statement_wo_name_block {
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);        		
        	}
        | K_always K_begin ':' IDENTIFIER error K_end {
        		printf("translate block must start with @");
        		exit(1);
        	}
        | K_always K_begin ':' IDENTIFIER {        		
        		current_block = my_parse->ablock_new(0, 0, 0, $4->get_text(), 0); 
        		current_top_name_block = my_parse->statement_new(0, 0, 0, Statement::BEGINEND_NAME);
        		my_parse->born(current_top_name_block, $4);
          	}
          wait_cycle statement_syn_list K_end {
        		current_block->set_pos(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$ =current_block;
        		current_top_name_block->set_pos(@2.begin_pos, @$.end_pos, @2.first_line);        		
        		my_parse->append($6, $7);
        		my_parse->born(current_top_name_block, $6);
        		my_parse->born($$, current_top_name_block);        		
        	}
        | K_always K_begin ':' K_ASYNC_RESET '@' '(' pos_or_neg_edge IDENTIFIER ')' ';' {        		
        		current_block = my_parse->ablock_new(0, 0, 0, $4->get_text(), $7);
        		current_block->put_clk($8->get_text());
        		current_top_name_block = my_parse->statement_new(0, 0, 0, Statement::BEGINEND_NAME);
        		my_parse->born(current_top_name_block, $4);
        	}
          statement_syn_list K_end {
          		current_block->set_pos(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$ =current_block;
        		current_top_name_block->set_pos(@2.begin_pos, @$.end_pos, @2.first_line);
        		my_parse->born(current_top_name_block, $12);
        		my_parse->born($$, current_top_name_block);        		
        	}
        | K_assign cont_assign_list ';' {
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);        		
        	}
        | K_initial statement {
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);        		
        	}
        | K_task automatic_opt IDENTIFIER ';' task_item_list_opt statement_or_null K_endtask {
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);        		
        	}
        | K_function automatic_opt function_range_or_type_opt IDENTIFIER ';' function_item_list statement K_endfunction {
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);        		
        	}
        | K_generate module_item_list_opt K_endgenerate {
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);        		
        	}
        | K_genvar list_of_identifiers ';' {
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);        		
        	}
        | K_for '(' IDENTIFIER '=' expression ';' expression ';' IDENTIFIER '=' expression ')' generate_block {
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);        		
        	}
        | K_if '(' expression ')' generate_block_opt K_else generate_block {
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);        		
        	}
        /*module instance*/
        | IDENTIFIER '#' '(' expression_list_with_nuls ')' gate_instance ';' {
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);        		
        	}
        | IDENTIFIER gate_instance ';' {
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);        		
        	}
        ;
        
block_item_decl
        : K_reg signed_opt range_opt register_variable_list ';' {
        		int prop;
        		Element * b, *e;
        		
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);
        		prop = VAR_REG | $2 | $3;        		
        		b = $4;
        		LOOP_LEVEL(b, e) {
        			Variable * v;
        			v = (Variable *) e->get_child(0);
        			ASSERT(v->get_emt_type() == Element::VARIABLE);
        			v->add_var_prop(prop);
        		}
        		my_parse->born($$, b);
        	}
        | K_integer register_variable_list ';' {
        		int prop;
        		Element * b, *e;
        		
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);
        		prop = VAR_REG | VAR_RANGE | VAR_SIGNED;        		
        		b = e = $2;
        		LOOP_LEVEL(b, e) {
        			Variable * v;
        			v = (Variable *) e->get_child(0);
        			ASSERT(v->get_emt_type() == Element::VARIABLE);
        			v->add_var_prop(prop);
        		}
        		my_parse->born($$, b);
        	}       
        | K_parameter parameter_assign_decl ';' {
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);
        	}
        | K_localparam parameter_assign_decl ';' {
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);
            }
        | K_event list_of_identifiers ';' {
        		Element * b, *e;
        		Variable * vb, *v;
        		int prop;
        		
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);
        		prop = VAR_EVENT;        		
        		b = $2;        		
        		LOOP_LEVEL(b, e) {
        			v = my_parse->variable_new(e, prop);
        			if (b==e)
        				vb = v;
        			else
        				my_parse->append(vb, v);
        		}
        		my_parse->born($$, vb);
        	}
            
        ;

signed_opt 
        : K_signed {$$ =VAR_SIGNED;}
        | {$$ =0;}
        ;

range_opt
        : range {$$ =VAR_RANGE;}
        | {$$ =0;}
        ;

reg_opt
        : K_reg {$$ =VAR_REG;}
        | {$$ =0;}
        ;
                
range
        : '[' expression ':' expression ']'
        ;       

expression
        : expr_primary {$$ =$1};
        | '-' expr_primary %prec UNARY_PREC {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($2);
        	}
        | '~' expr_primary %prec UNARY_PREC {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($2);
        	}
        | '&' expr_primary %prec UNARY_PREC {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($2);
        	}
        | '!' expr_primary %prec UNARY_PREC {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line, Expression::NOT);
        		$$->merge_expression($2);
        	}
        | '|' expr_primary %prec UNARY_PREC {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($2);
        	}
        | '^' expr_primary %prec UNARY_PREC {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($2);
        	}
        | '~' '&' expr_primary %prec UNARY_PREC {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($3);
        	}
        | '~' '|' expr_primary %prec UNARY_PREC {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($3);
        	}
        | '~' '^' expr_primary %prec UNARY_PREC {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($3);
        	}
        | expression '^' expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression '*' expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression '/' expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression '%' expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression '+' expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression '-' expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression '&' expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression '|' expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression '<' expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line, Expression::LESS);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression '>' expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line, Expression::BIG);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression K_LS expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression K_RS expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression K_RSS expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression K_EQ expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line, Expression::EQU);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression K_CEQ expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression K_LE expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line, Expression::LESSEQU);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression K_GE expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line, Expression::BIGEQU);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression K_NE expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line, Expression::NEQ);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression K_CNE expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression K_LOR expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression K_LAND expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression '?' expression ':' expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        		$$->merge_expression($5);
        	}
        ;
        
expr_primary
        : number {
        		$$=my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line, Expression::NUMBER);
        	}
        | DEFINE_IDENTIFIER {
        		$$=my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line, Expression::NUMBER);
        	}
        | STRING {$$=NULL;}
        | hierarchy_identifier {
        		string vname =my_parse->get_text(@$.begin_pos, @$.end_pos);
        		Variable *v =my_parse->variable_lookup(vname);
        		if (vname.find('.', 0) == string::npos && v!=NULL) { //not found '.'
        			$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line, Expression::VAR);
        			$$->insert_var(v);
        		} else { //found '.'
        			$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line, Expression::VAR); //not support hierarchy variable
        		}
        	}
        /* concatenation expressions. */
        | '{' expression_list_proper '}' {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($2);
        	}
        | '{' expression '{' expression_list_proper '}' '}' {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);        		
        		$$->merge_expression($4);
        	}
        | '(' expression ')' {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($2);
        	}
        /*function call*/
        | hierarchy_identifier '(' expression_list_proper ')' {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($3);
        	}
        | SYSTEM_IDENTIFIER '(' expression_list_proper ')' {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($3);
        	}
        ;

number  : BASED_NUMBER
        | DEC_NUMBER
        | DEC_NUMBER BASED_NUMBER
        ;
        
expression_list_proper
        : expression_list_proper ',' expression {
        		$$ = my_parse->expression_new(@$.begin_pos, @$.end_pos, @$.first_line);
        		$$->merge_expression($1);
        		$$->merge_expression($3);
        	}
        | expression {$$=$1;}
        ;
        
expression_list_with_nuls
        : expression_list_proper {$$=$1;}
        | {$$=NULL;}
        ;               
  /* The hierarchy_identifier rule matches simple identifiers as well as
     indexed arrays and part selects */
     
hierarchy_identifier
        : IDENTIFIER
        | hierarchy_identifier '.' IDENTIFIER
        | hierarchy_identifier '[' expression ']'
        | hierarchy_identifier '[' expression ':' expression ']'
        ;
             
net_variable_list
        : net_variable {$$=$1;}
        | net_variable_list ',' net_variable {
        		$$ =$1;
        		my_parse->append($$, $3);
        	}
        ;

net_variable
        : IDENTIFIER dimensions_opt {
        		Variable *v;
        		int range;
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);
        		range = $2;
        		v  = my_parse->variable_new($1, range);
				my_parse->born($$, v);
			}
        ;

dimensions_opt
        : {$$=0;}
        | dimensions {$$=VAR_RANGE;}
        ;
        
dimensions
        : '[' expression ':' expression ']'
        | dimensions '[' expression ':' expression ']'
        ;
        
port_type
        : K_input  {$$=VAR_INPUT;}              
        | K_output {$$=VAR_OUTPUT;}       
        | K_inout  {$$=VAR_INPUT | VAR_OUTPUT;}      
        ;       

net_type_opt
        : K_wire
        |
        ;       
        
list_of_identifiers
        : IDENTIFIER {$$=$1;} 
        | list_of_identifiers ',' IDENTIFIER {
        		$$ = $1;
        		my_parse->append($$, $3);
        	}
        ;
                
register_variable_list
        : register_variable {$$=$1;}
        | register_variable_list ',' register_variable {
        		$$ = $1;
        		my_parse->append($$, $3);
        	}
        ;
        
register_variable
        : IDENTIFIER dimensions_opt {
        		Variable *v;
        		int range;
        		$$ = my_parse->element_new(@$.begin_pos, @$.end_pos, @$.first_line, Element::ELEMENT_NORMAL, 0);
        		range = $2;
        		v  = my_parse->variable_new($1, range | VAR_REG);
				my_parse->born($$, v);
			}
        ;

parameter_assign_decl   
        : signed_opt range_opt parameter_assign_list
        | K_integer parameter_assign_list
        ;
        
parameter_assign_list
        : parameter_assign
        | parameter_assign_list ',' parameter_assign
        ;
        
parameter_assign
        : IDENTIFIER '=' expression
        ; 

statement_or_null
        : statement
        | ';'
        ;

statement
		: statement_wo_name_block
		| K_begin ':' IDENTIFIER block_item_decls_opt statement_list K_end
		| K_begin ':' IDENTIFIER K_end
		;
		
statement_wo_name_block
        : K_begin statement_list K_end         
        | K_begin K_end        
          /* fork-join blocks are very similar to begin-end blocks. In fact,
          from the parser's perspective there is no real difference. All we
          need to do is remember that this is a parallel block so that the
          code generator can do the right thing. */
        | K_fork statement_list K_join 
        | K_fork ':' IDENTIFIER block_item_decls_opt statement_list K_join 
        | K_fork K_join
        | K_fork ':' IDENTIFIER K_join 
        | K_disable hierarchy_identifier ';'
        | K_TRIGGER hierarchy_identifier ';'
        | K_forever statement
        | K_repeat '(' expression ')' statement
        | K_case '(' expression ')' case_items K_endcase
        | K_casex '(' expression ')' case_items K_endcase
        | K_casez '(' expression ')' case_items K_endcase
        | K_if '(' expression ')' statement_or_null %prec less_than_K_else 
        | K_if '(' expression ')' statement_or_null K_else statement_or_null 
        | K_for '(' lpvalue '=' expression ';' expression ';' lpvalue '=' expression ')' statement
        | K_while '(' expression ')' statement
        | delay1 statement_or_null
        | event_control statement_or_null
        | '@' '(' '*' ')' statement_or_null     
        | lpvalue K_LE expression ';' 
        | lpvalue K_LE delay1 expression ';'           
        | lpvalue K_LE event_control expression ';'
        | lpvalue '=' expression ';'            
        | lpvalue '=' delay1 expression ';'            
        | lpvalue '=' event_control expression ';'
        | K_wait '(' expression ')' statement_or_null
        | SYSTEM_IDENTIFIER '(' expression_list_with_nuls ')' ';'
        | SYSTEM_IDENTIFIER ';'
        | hierarchy_identifier '(' expression_list_proper ')' ';'
        | hierarchy_identifier '(' ')' ';'
        | error ';'
        ;

statement_list
        : statement_list statement 
        | statement 
        ;

statement_syn_list
		: statement_syn_list statement_syn { my_parse->append($1,$2); $$=$1;}
		| statement_syn {$$=$1; }
		;
		
statement_syn
		: K_begin statement_syn_list K_end	{
        		$$ = my_parse->statement_new(@$.begin_pos, @$.end_pos, @$.first_line, Statement::BEGINEND);
        		my_parse->born($$, $2);        		
        	}
        | K_begin ':' IDENTIFIER {
        		$<smt>$ = my_parse->statement_new(0, 0, 0, Statement::BEGINEND_NAME);
        		my_parse->born($<smt>$, $3);
        	} statement_syn_list K_end {
        		$$ = $<smt>4;
        		$$->set_pos(@$.begin_pos, @$.end_pos, @$.first_line);
        		my_parse->born($$, $5);
        	}	
        | K_begin K_end { $$ = NULL; }	
        | K_begin ':' IDENTIFIER K_end { $$ = NULL; }     
        | K_disable IDENTIFIER ';' {
        		$$ = my_parse->statement_new(@$.begin_pos, @$.end_pos, @$.first_line, Statement::DISABLE);
        		my_parse->born($$, $2);
        	}
        | K_TRIGGER IDENTIFIER ';' {
        		$$ = my_parse->statement_new(@$.begin_pos, @$.end_pos, @$.first_line, Statement::TRIGGURE_EVENT);
        		my_parse->born($$, $2);
        	}
        | K_if '(' expression ')' statement_syn_or_null %prec less_than_K_else {
        		$$ = my_parse->statement_new(@$.begin_pos, @$.end_pos, @$.first_line, Statement::IF);
        		my_parse->born($$, $3);
        		my_parse->born($$, $5);        		
        	}
        | K_if '(' expression ')' statement_syn_or_null K_else statement_syn_or_null {
    			$$ = my_parse->statement_new(@$.begin_pos, @$.end_pos, @$.first_line, Statement::IFELSE);
    			my_parse->born($$, $3);
    			my_parse->born($$, $5);
    			my_parse->born($$, $7);
        	}  
        | K_while '(' expression ')' statement_syn_or_null {        		
        		$$ = my_parse->statement_new(@$.begin_pos, @$.end_pos, @$.first_line, Statement::WHILE);
        		my_parse->born($$, $3);
        		my_parse->born($$, $5);
        	} 
        | K_while '(' expression ')' K_dowhile statement_syn_or_null {        		
        		$$ = my_parse->statement_new(@$.begin_pos, @$.end_pos, @$.first_line, Statement::DOWHILE);
        		my_parse->born($$, $3);
        		my_parse->born($$, $6);
        	} 
        | IDENTIFIER K_LE expression ';' {
        		$$ = my_parse->assign_new(@$.begin_pos, @$.end_pos, @$.first_line);
	        	my_parse->born($$, $1);
	        	my_parse->born($$, $3);	        	
        	}
        | IDENTIFIER K_LE delay1 expression ';' {
        		$$ = my_parse->assign_new(@$.begin_pos, @$.end_pos, @$.first_line);
	        	my_parse->born($$, $1);
	        	my_parse->born($$, $4);	        	
        	}	
        | '@' '(' IDENTIFIER ')' ';' statename_or_null {
				$$ =my_parse->statement_new(@$.begin_pos, @$.end_pos, @$.first_line, Statement::WAIT_EVENT);	        		
				State * st;
				if ($6==NULL)
					st = my_parse->state_new(0, 0, 0, "");
				else
					st = my_parse->state_new(0, 0, 0, $6->get_text());
									
				my_parse->born($$, $3);
				my_parse->born($$, st);				
			}
		| wait_cycle {$$ =$1;}        
        ;
        
statement_syn_or_null
        : statement_syn {$$=$1;}
        | ';' {$$=NULL;}
        ;      
               
block_item_decls_opt
        : block_item_decls {$$=$1;}
        | {$$=NULL;}
        ;

block_item_decls
        : block_item_decl
        | block_item_decls block_item_decl
        ;
        
case_items
        : case_items case_item
        | case_item
        ;

case_item
        : expression_list_proper ':' statement_or_null
        | K_default ':' statement_or_null
        ;

delay1
        : '#' delay_value_simple
        | '#' '(' expression ')'
        ;

delay_value_simple
        : DEC_NUMBER
        | IDENTIFIER
        ;       

wait_cycle
		: '@' '(' K_posedge IDENTIFIER ')' ';' statename_or_null {									
        		if ($7==NULL)
        			$$ = my_parse->state_new(@$.begin_pos, @$.end_pos, @$.first_line, "");
        		else
        			$$ = my_parse->state_new(@$.begin_pos, @$.end_pos, @$.first_line, $7->get_text());	
        		my_parse->born($$, $4);	        		
			}		
		;

pos_or_neg_edge
		: K_posedge { $$ =0; }
		| K_negedge { $$ =1; }
		;	
statename_or_null
		: STATENAME { $$ =$1;}
		| {$$ =NULL; }
		;

event_control
        : '@' hierarchy_identifier
        | '@' '(' event_expression_list ')'
        ;

event_expression_list
        : event_expression
        | event_expression_list K_or event_expression
        ;

event_expression
        : K_posedge expression
        | K_negedge expression
        | expression
        ;
                        
lpvalue
        : hierarchy_identifier          
        | '{' expression_list_proper '}'
        ;

cont_assign_list
        : cont_assign_list ',' cont_assign
        | cont_assign
        ;
        
cont_assign
        : lpvalue '=' expression
        ;
                
automatic_opt
        : K_automatic
        |
        ;

task_item_list_opt
        : task_item_list
        |
        ;
        
task_item_list
        : task_item_list task_item
        | task_item
        ;

task_item
        : block_item_decl
        | task_port_item
        ;
        
task_port_item
        : K_input reg_opt signed_opt range_opt list_of_identifiers ';'
        | K_output reg_opt signed_opt range_opt list_of_identifiers ';'
        | K_inout reg_opt signed_opt range_opt list_of_identifiers ';'
        | K_input K_integer list_of_identifiers ';'
        | K_output K_integer list_of_identifiers ';'
        | K_inout K_integer list_of_identifiers ';'
        ;
        
function_range_or_type_opt
        : range
        | K_signed range
        | K_integer
        |
        ;       
        
function_item_list
        : function_item
        | function_item_list function_item
        ;
        
function_item
        : task_port_item
        | block_item_decl
        ;
        
generate_block
        : module_item
        | K_begin module_item_list_opt K_end
        | K_begin ':' IDENTIFIER module_item_list_opt K_end
        ;

generate_block_opt 
        : generate_block 
        | ';'
        ;
        
gate_instance
        : IDENTIFIER '(' expression_list_with_nuls ')'
        | IDENTIFIER '(' port_name_list ')'     
        ;
        
port_name_list
        : port_name_list ',' port_name
        | port_name
        ;
        
port_name
        : '.' IDENTIFIER '(' expression ')'
        | '.' IDENTIFIER '(' ')'
        ;
%%

void yyerror(char *s) {
    fprintf(stderr, "%d.%d-%d.%d %s\n", yylloc.first_line, yylloc.first_column, yylloc.last_line, yylloc.last_column, s);
}


