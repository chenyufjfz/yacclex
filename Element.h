/*
 * Element.h
 *
 *  Created on: Sep 22, 2012
 *      Author: yuchen
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_
#include "public.h"
#include <vector>
#include <set>
#include <string>
#include "Robdd.h"
using namespace std;
class AlwaysBlock;
class Variable;
class Statement;
class Assign;
class State;
class Expression;
class Condition;

#define TAB_SPACE			4

#define ELEMENT_FIRST_CHILD 0x00000010

class Element {
public:
	enum ElementType{
		STATEMENT,
		EXPRESSION,
		VARIABLE,
		ALWAYSBLOCK,
		ELEMENT_MODULE,
		ELEMENT_NORMAL
	};
protected:
	int begin_pos, end_pos, line; //begin_pos to end_pos can be used to fetch whole text, line is the begining line
	ElementType element_type;
	int prop;
	int child_num; //maxium child num is 3
	Element * prev_emt; //prev link point to same level, bidirection pointers forms a link loop
	Element * next_emt; //if only one element exist in the level, then pointers point to itself
	Element* child_emt[3];
	Element* father_emt;
public:
	Element(int b, int e, int l, ElementType t, int p=0) {
		begin_pos = b;
		end_pos = e;
		line = l;
		element_type = t;
		prop =p;
		child_num =0;
		prev_emt = this;
		next_emt = this;
		for (unsigned i=0; i<sizeof(child_emt)/sizeof(child_emt[0]); i++)
			child_emt[i] = NULL;
		father_emt = NULL;
	}
	Element(Element *e, ElementType t, int p=0) {
		ASSERT(e!=NULL);
		begin_pos = e->begin_pos;
		end_pos = e->end_pos;
		line = e->line;
		element_type = t;
		prop =p;
		child_num =0;
		prev_emt = this;
		next_emt = this;
		for (unsigned i=0; i<sizeof(child_emt)/sizeof(child_emt[0]); i++)
			child_emt[i] = NULL;
		father_emt = NULL;
	}
	virtual ~Element() {}
	string get_text();
	virtual void append(Element *e);
	virtual void link_child(Element *e);
	virtual void display(ostream& out, int layer, int space);
	Element * get_child(int c) {
		ASSERT((unsigned) c<sizeof(child_emt)/sizeof(child_emt[0]) && c>=0);
		return child_emt[c];
	}
	Element * get_father() {
		return father_emt;
	}
	Element * get_next() {
		return next_emt;
	}
	int get_child_num() {
		return child_num;
	}
	int get_prop() {
		return prop;
	}
	void set_prop(int p) {
		prop = p;
	}
	ElementType get_emt_type() {
		return this->element_type;
	}
	int get_line() {
		return line;
	}
	void set_pos(int b, int e, int l) {
		begin_pos = b;
		end_pos = e;
		line = l;
	}
};
#define LOOP_LEVEL(b, v) 			\
	v=b;							\
	for (int loop_num=0; v!=b || loop_num==0; v=v->get_next(), loop_num++)
#define LOOP_CHILD(b, v)			\
	if (b->get_child_num()>0)		\
		for (int loop_num=0, v=b->get_child(loop_num); loop_num<b->get_child_num(); loop_num++)


#define VAR_SIGNED		0x1
#define VAR_REG			0x2
#define VAR_INPUT		0x4
#define VAR_OUTPUT		0x8
#define VAR_RANGE		0x10
#define VAR_EVENT		0x40
#define BLOCK_NAME		0x80

class Variable : public Element {
protected:
	int var_prop;
	vector<Assign *> assign_out;
	Condition * event_cond;  //used only for event variable
	void create_event_condition();
public:
	Variable(Element *e, int p=0) : Element(e, VARIABLE) {
		var_prop =p;
		if (p & VAR_EVENT)
			create_event_condition();
	}
	virtual ~Variable() {}
	int get_var_prop() {
		return var_prop;
	}
	void add_var_prop(int p) {
		if ((p & VAR_EVENT) && !(var_prop & VAR_EVENT))
			create_event_condition();
		var_prop |=p;
	}
	Condition * get_evt_cond() {
		return event_cond;
	}
	void link_assign(Assign * as) {
		assign_out.push_back(as);
	}
	bool check_assign();
	virtual void display(ostream& out, int layer, int space);
	//Variable::get_text return variable's name
};

class Expression : public Element {
public:
	enum ExpressionType {
		EQU=0,
		NEQ,
		BIG,
		LESS,
		BIGEQU,
		LESSEQU,
		NOT,
		NUMBER,
		VAR,
		NA
	};
protected:
	set<Variable *> vars;
	ExpressionType exp_type;
	Expression *child[2];
public:
	friend class Condition;
	Expression(int b, int e, int l, ExpressionType t) : Element(b, e, l, EXPRESSION) {
		exp_type = t;
		child[0]=NULL;
		child[1]=NULL;
	}
	virtual ~Expression() {}
	ExpressionType get_exp_type() {
		return exp_type;
	}
	void merge_expression(Expression * exp) {
		if (exp==NULL)
			return;
		if (child[0]==NULL)
			child[0] = exp;
		else
			child[1] = exp;
		vars.insert(exp->vars.begin(), exp->vars.end());
		exp->vars.clear();
	}
	void insert_var(Variable * v) {
		if (v==NULL)
			return;
		vars.insert(v);
	}
};


class Statement : public Element {
public:
	enum StatementType {
		ASSIGN,
		STATE,
		BEGINEND,
		IF,
		IFELSE,
		WHILE,
		DOWHILE,
		DISABLE,
		WAIT_EVENT,
		BEGINEND_NAME,
		TRIGGURE_EVENT,
	};
protected:
	StatementType smt_type;
	Condition * pre_cond;  //pre_condtion to execute this statement
	Condition * post_cond; //post_condtion when finish executing this statement
public:
	friend class AlwaysBlock;
	Statement(int b, int e, int l, StatementType st);
	StatementType get_smt_type() {return smt_type;}
	Condition * get_precond() {
		return pre_cond;
	}
	virtual ~Statement() {}
	virtual void link_child(Element *e);
	virtual void display(ostream& out, int layer, int space);
};

class Assign : public Statement {
protected:
	AlwaysBlock *block;
	Variable * left_var;
	Expression * right_exp;

public:
	Assign(int b, int e, int l, AlwaysBlock *ab) : Statement(b, e, l, ASSIGN) {
		block = ab;
	}
	void put_left_var(Variable * l) {
		left_var = l;
	}
	void put_right_exp(Expression * r) {
		right_exp = r;
	}
	AlwaysBlock * get_block() {
		return block;
	}
};

class State : public Statement {
protected:
	AlwaysBlock *block;
	string name;
	bool def_name;
public:
	State(int b, int e, int l, string n, bool defined, AlwaysBlock *ab) : Statement(b, e, l, STATE) {
		block = ab;
		name = n;
		def_name = defined;
	}

	AlwaysBlock * get_block() {
		return block;
	}
	string get_name() {
		return name;
	}
	bool is_define() {
		return def_name;
	}
	virtual void display(ostream& out, int layer, int space);
};


class AlwaysBlock : public Element {
public:
	enum AlwaysBlockType {
		ASYNC_RST,
		SYNC_RST,
		NORMAL
	};
protected:
	string name;
	vector<Assign *> block_as;
	vector<State *> block_st;
	Variable * clk;
	Condition * syn_reset;
	AlwaysBlock * asyn_reset;
	AlwaysBlockType always_type;
	int edge; //only used in ASYNC_RESET block, posedge is 0, negedge is 1
public:
	AlwaysBlock(int b, int e, int l, string n, int edge);
	void set_pos(int b, int e, int l) {
		begin_pos = b;
		end_pos = e;
		line = l;
	}
	void add_state(State * st) {
		ASSERT(st!=NULL);
		block_st.push_back(st);
	}
	void add_assign(Assign * as) {
		ASSERT(as!=NULL);
		block_as.push_back(as);
	}
	int get_state_num() {
		return block_st.size();
	}
	Variable * get_clk() {
		return clk;
	}
	void put_clk(string vclk);
	string get_name() {
		return name;
	}
	int get_edge() {
		return edge;
	}
	AlwaysBlockType get_always_type() {
		return always_type;
	}
	Condition * get_syn_reset() {return syn_reset;}
	AlwaysBlock * get_asyn_block() {
		return asyn_reset;
	}
	void set_asyn_block(AlwaysBlock *a) {
		asyn_reset = a;
	}
	State * get_first_state() {
		ASSERT(!block_st.empty());
		return block_st[0];
	}
	vector<State *> get_all_state() {
		return block_st;
	}
	virtual void link_child(Element *e);
	virtual void display(ostream& out, int layer, int space);
};

class Condition {
public:
	typedef enum {
		INVALID,
		RAW_STATE,
		RAW_EXPRESSION,
		EQUAL_TO,
		AND,
		AND_NOT,
		OR,
		ZERO,
		ONE
	} ConditionType;
protected:
	ConditionType cond_type;
	Condition * left_cond;
	Condition * right_cond;
	Statement * smt;
	union {
		State * state;
		Expression *exp;
	} raw;
	Robdd * bdd_node;
	static vector<Condition *> cond_sets;
public:
	Condition (Statement *s) {
		smt =s;
		cond_type = INVALID;
		left_cond = NULL;
		right_cond = NULL;
		raw.state = NULL;
		raw.exp = NULL;
		bdd_node = NULL;
	}
	void make_equal_to(Condition *c) {
		cond_type = EQUAL_TO;
		left_cond = c;
	}
	void make_expression(Expression *e) {
		cond_type = RAW_EXPRESSION;
		raw.exp =e;
	}
	void make_state(State *s) {
		cond_type = RAW_STATE;
		raw.state = s;
	}
	void make_and(Condition *c1, Condition *c2) {
		cond_type = AND;
		left_cond = c1;
		right_cond = c2;
	}
	void make_and_not(Condition *c1, Condition *c2) {
		cond_type = AND_NOT;
		left_cond = c1;
		right_cond = c2;
	}
	void make_or(Condition *c1, Condition *c2) {
		cond_type = OR;
		left_cond = c1;
		right_cond = c2;
	}
	void make_zero() {
		cond_type = ZERO;
	}
	void make_one() {
		cond_type = ONE;
	}
	void add_to_cond_set() {
		cond_sets.push_back(this);
	}
	void print(ostream& out, bool raw=true);
	bool iszero() {
		return (bdd_node==Robdd::zero || cond_type==ZERO);
	}
	bool isone() {
		return (bdd_node==Robdd::one || cond_type==ONE);
	}
	int cmp(Condition *c);
	vector<VUI> get_logic() {
		return bdd_node->get_logic();
	}
	static void assign_bdd_all();
};
#endif /* ELEMENT_H_ */
