/*
 * FileParse.h
 *
 *  Created on: Sep 15, 2012
 *      Author: yuchen
 */

#ifndef FILEPARSE_H_
#define FILEPARSE_H_

#include <set>
#include <map>
#include <string>
#include "Element.h"
#include "Robdd.h"
using namespace std;

class FileParse {
private:
	vector <Element*> emt_container; //contain all element
	map <string, AlwaysBlock *> ablock_table; //contain all always block, map name to block
	map <string, Condition *> unresolved_ablock_syn;  //contain all unresolved syn reset's condition
	map <string, AlwaysBlock *> unresolved_ablock_asyn; //contain all unresolved asyn reset's block
	vector<char> text;  //contain file's raw text
	vector<string> define_items;
	map<string, Variable*> var_table; //contain all variable, map name to var
	AlwaysBlock * cur_always_block;
	vector<pair<string, Statement *> > nameblock_stack;
	string source_filename;
	int module_num;
public:
	FileParse();
	virtual ~FileParse();
	void load_file(const char * name);
	void add_define(const char * name);
	void del_define(const char * name);
	int lookup_define(const char * name);
	string get_text(int begin_pos, int end_pos);
	AlwaysBlock * get_current_block();
	vector<AlwaysBlock *> get_all_block();
	vector<Variable *> get_all_variable();
	Element * element_new(int begin_pos, int end_pos, int line, Element::ElementType t, int prop=0);
	void append(Element *e1, Element *e2);
	void born(Element *fa, Element *c);
	Variable * variable_new(Element *e, int var_prop);
	Variable * variable_lookup(string s);
	Expression * expression_new(int begin_pos, int end_pos, int line, Expression::ExpressionType et=Expression::NA);
	Statement * statement_new(int begin_pos, int end_pos, int line, Statement::StatementType st);
	void nameblock_begin(string name, Statement * s);
	void nameblock_end();
	Statement * nameblock_lookup(string name);
	Condition * condition_new(Statement * smt);
	Assign * assign_new(int begin_pos, int end_pos, int line);
	AlwaysBlock * ablock_new(int begin_pos, int end_pos, int line, string name, int edge);
	AlwaysBlock * ablock_lookup(string name);
	Condition * unresolved_ablock_synrst_new(string name);
	void unresolved_ablock_del(string name);
	Condition * unresolved_ablock_synrst(string name);
	void unresolved_ablock_asynrst_new(string name, AlwaysBlock *a);
	AlwaysBlock * unresolved_ablock_asynrst(string name);
	State * state_new(int begin_pos, int end_pos, int line, string state_name);
	void output(Element *top);

};

#endif /* FILEPARSE_H_ */
