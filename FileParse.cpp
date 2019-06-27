/*
 * FileParse.cpp
 *
 *  Created on: Sep 15, 2012
 *      Author: yuchen
 */
#include "public.h"
#include "FileParse.h"
#include <fstream>
#include <string.h>

extern int yyparse();
int prepare(int argc, char *argv[]);
FileParse::FileParse() {
	text.reserve(4096);
	module_num =0;
}

FileParse::~FileParse() {

}

void FileParse::load_file(const char *name)
{
	FILE * fp;
	char line[1000];

	fp = fopen(name,"rt");
	if (fp==NULL)
		throw MyException("input file open failed");
	source_filename = name;
	line[sizeof(line)-1] =10;
	while (fgets(line, sizeof(line), fp)!=NULL) {
		if (line[sizeof(line)-1]==0) //if it is 0, it is overwrite by fgets
			throw MyException("input file line too long");
		text.insert(text.end(), line, line+ strlen(line));
	}
	fclose(fp);
}

void FileParse::add_define(const char * name)
{
	for (unsigned i=0; i<define_items.size(); i++)
		if (define_items[i]==name)
			return;
	define_items.push_back(string(name));
}

void FileParse::del_define(const char * name)
{
    for (unsigned i=0; i<define_items.size(); i++)
    	if (define_items[i]==name)
    		define_items.erase(define_items.begin()+i);
}

int FileParse::lookup_define(const char * name)
{
    for (unsigned i=0; i<define_items.size(); i++)
    	if (define_items[i]==name)
    		return 1;
    return 0;
}

string FileParse::get_text(int begin_pos, int end_pos)
{
	ASSERT(begin_pos>=0 && begin_pos<(int) text.size());
	ASSERT(end_pos>0 && end_pos<=(int) text.size());

	string s;

	s.append(&text[begin_pos], end_pos-begin_pos);
	return s;
}

AlwaysBlock * FileParse::get_current_block()
{
	return cur_always_block;
}

vector<AlwaysBlock *> FileParse::get_all_block()
{
	map <string, AlwaysBlock *>::iterator ai;
	vector<AlwaysBlock *> ret;

	for (ai=ablock_table.begin(); ai!=ablock_table.end(); ai++)
		ret.push_back(ai->second);

	return ret;
}

vector<Variable *> FileParse::get_all_variable()
{
	map<string, Variable*>::iterator vi;
	vector<Variable *> ret;

	for (vi=var_table.begin(); vi!=var_table.end(); vi++)
		ret.push_back(vi->second);

	return ret;
}

Element * FileParse::element_new(int begin_pos, int end_pos, int line, Element::ElementType t, int prop)
{
	if (t==Element::ELEMENT_MODULE) {
		module_num++;
		if (module_num>1) {
			printf("Two module exist in file, it is not supported.\n");
			exit(1);
		}
	}
	Element * e =new Element(begin_pos, end_pos, line, t, prop);
	emt_container.push_back(e);
	return e;
}

void FileParse::append(Element * e1, Element *e2)
{
	ASSERT(e1!=NULL);
	e1->append(e2);
}

void FileParse::born(Element *fa, Element *c)
{
	ASSERT(fa!=NULL);
	fa->link_child(c);
}

Variable * FileParse::variable_new(Element *e, int var_prop)
{
	Variable * v = new Variable(e, var_prop);
	emt_container.push_back(v);
	var_table.insert(make_pair(v->get_text(), v));
	return v;
}

Variable * FileParse::variable_lookup(string s)
{
	map<string,Variable *>::iterator pos;
	pos =var_table.find(s);
	if (pos==var_table.end())
		return NULL;
	else
		return pos->second;
}

Expression * FileParse::expression_new(int begin_pos, int end_pos, int line, Expression::ExpressionType et)
{
	Expression * exp = new Expression(begin_pos, end_pos, line, et);
	emt_container.push_back(exp);
	return exp;
}

Statement * FileParse::statement_new(int begin_pos, int end_pos, int line, Statement::StatementType st)
{
	Statement * smt = new Statement(begin_pos, end_pos, line, st);
	emt_container.push_back(smt);
	return smt;
}

void FileParse::nameblock_begin(string name, Statement *s)
{
	nameblock_stack.push_back(make_pair(name, s));
}

void FileParse::nameblock_end()
{
	nameblock_stack.pop_back();
}

Statement * FileParse::nameblock_lookup(string name)
{
	for (int i=nameblock_stack.size()-1; i>=0; i--) {
		if (nameblock_stack[i].first==name)
			return nameblock_stack[i].second;
	}
	return NULL;
}

Condition * FileParse::condition_new(Statement * smt)
{
	Condition * cond = new Condition(smt);
	cond->add_to_cond_set();
	return cond;
}

Assign * FileParse::assign_new(int begin_pos, int end_pos, int line)
{
	ASSERT(cur_always_block!=NULL);
	Assign * a = new Assign(begin_pos, end_pos, line, cur_always_block);
	emt_container.push_back(a);
	cur_always_block->add_assign(a);
	return a;
}

AlwaysBlock * FileParse::ablock_new(int begin_pos, int end_pos, int line, string name, int edge)
{
	if (ablock_lookup(name)!=NULL) {
		printf("always block name %s already exist at line %d", name.c_str(), line);
		exit(1);
	}
	cur_always_block= new AlwaysBlock(begin_pos, end_pos, line, name, edge);
	if (cur_always_block->get_always_type()==AlwaysBlock::NORMAL)
		ablock_table[name] = cur_always_block;
	emt_container.push_back(cur_always_block);
	return cur_always_block;
}

AlwaysBlock * FileParse::ablock_lookup(string name)
{
	if (ablock_table.find(name)!=ablock_table.end())
		return ablock_table[name];
	else
		return NULL;
}

Condition * FileParse::unresolved_ablock_synrst_new(string name)
{
	ASSERT(unresolved_ablock_synrst(name)==NULL);
	Condition * c;
	c = condition_new(NULL);
	unresolved_ablock_syn[name] = c;
	return c;
}

void FileParse::unresolved_ablock_del(string name)
{
	if (unresolved_ablock_synrst(name)!=NULL)
		unresolved_ablock_syn.erase(name);
	if (unresolved_ablock_asynrst(name)!=NULL)
		unresolved_ablock_asyn.erase(name);
}

Condition * FileParse::unresolved_ablock_synrst(string name)
{
	if (unresolved_ablock_syn.find(name)!=unresolved_ablock_syn.end())
		return unresolved_ablock_syn[name];
	else
		return NULL;
}

void FileParse::unresolved_ablock_asynrst_new(string name, AlwaysBlock *a)
{
	ASSERT(unresolved_ablock_asynrst(name)==NULL);
	unresolved_ablock_asyn[name] = a;
}

AlwaysBlock * FileParse::unresolved_ablock_asynrst(string name)
{
	if (unresolved_ablock_asyn.find(name)!=unresolved_ablock_asyn.end())
		return unresolved_ablock_asyn[name];
	else
		return NULL;
}

State * FileParse::state_new(int begin_pos, int end_pos, int line, string state_name)
{
	char num_st[6];
	bool def_name = true;

	ASSERT(cur_always_block!=NULL);
	if (state_name.empty()) {
		state_name = cur_always_block->get_name();
		sprintf(num_st, "_%02d", cur_always_block->get_state_num());
		state_name.append(num_st);
		def_name = false;
	}
	State * st = new State(begin_pos, end_pos, line, state_name, def_name, cur_always_block);
	emt_container.push_back(st);
	cur_always_block->add_state(st);
	return st;
}

void FileParse::output(Element *top)
{
	filebuf fb;
	ostream out(&fb);
	string file_rawname, file_l0, file_l1, file_l2, file_l3;
	int index;

	if (!unresolved_ablock_asyn.empty()) {
		map <string, AlwaysBlock *>::iterator a;
		a = unresolved_ablock_asyn.begin();
		printf("can't find disable block %s in async reset %s\n", (a->first).c_str(), a->second->get_name().c_str());
		exit(1);
	}
	if (!unresolved_ablock_syn.empty()) {
		map <string, Condition *>::iterator c;
		c = unresolved_ablock_syn.begin();
		printf("can't find disable block %s for sync reset\n", (c->first).c_str());
		exit(1);
	}
	Condition::assign_bdd_all();
	index =source_filename.find_last_of('.');
	file_rawname = source_filename.substr(0, index);
	file_l0 = file_rawname +"_0.v";
	file_l1 = file_rawname +"_1.v";
	file_l2 = file_rawname +"_2.v";
	file_l3 = file_rawname +"_3.v";

	fb.open(file_l0.c_str(),ios::out);
	top->display(out, 0, 0);
	fb.close();
	fb.open(file_l1.c_str(),ios::out);
	top->display(out, 1, 0);
	fb.close();
	fb.open(file_l2.c_str(),ios::out);
	top->display(out, 2, 0);
	fb.close();
	fb.open(file_l3.c_str(),ios::out);
	top->display(out, 3, 0);
	fb.close();
}

int main(int argc, char *argv[]) {
	Robdd::init();
    prepare(argc, argv);
    yyparse();
    cout<<"finish successfully\n";
}
