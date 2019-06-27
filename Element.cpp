/*
 * Element.cpp
 *
 * 1 fork.. join is not supported
 * 2 local variable is not supported
 * 3 disable internal block is supported, disable external block should be top block, disable external block inside block is not supported
 * 4 for forever is not supported
 * 5 One always block has one clock domain, It means @(posedge clk1); @(posedge clk2); can't exist in same always block
 * 6 @(var); var can only be event
 * 7 synable block is like this
 *   always
 *   begin : name
 *   @(posedge clk);
 *   end
 *   name can be SYNC_RESET or ASYNC_RESET
 *   other block won't be synthesized
 * 8 Only one module can exist in one file.
 * 9 "wait" is not supported
 * 10 "@(event)" = "while(!event) @posedge(clk)"
 * 11 function call in expression is supported
 *  Created on: Sep 22, 2012
 *      Author: yuchen
 */


#include "FileParse.h"
#include <map>

extern FileParse * my_parse;

string Element::get_text()
{
	return my_parse->get_text(begin_pos, end_pos);
}

//append element exist in same level as this element
void Element::append(Element *e)
{
	if (e==NULL)
		return;
	Element * tail = prev_emt;
	Element * etail = e->prev_emt;

	etail->next_emt = this;
	this->prev_emt = etail;
	tail->next_emt = e;
	e->prev_emt = tail;
}

//link child in down level as this element
void Element::link_child(Element *e)
{
	ASSERT((unsigned) child_num< sizeof(child_emt)/sizeof(child_emt[0]));
	child_emt[child_num++] = e;
	if (e!=NULL) {
		e->father_emt = this;
		e->prop |= ELEMENT_FIRST_CHILD;
	}
}

/*
 * out: can be cout, or sstreamout,
 * layer: is 0, 1, 2, 3; layer 0 is original one
 * space: how many space is in the prefill
 */
void Element::display(ostream& out, int layer, int space)
{
	string prespace(space, ' ');

	if (get_emt_type()==ELEMENT_MODULE) {
		out<<prespace<<"module ";
		if (get_child(0)!=NULL)
			out<<get_child(0)->get_text(); //display module name
		out<<" ";
		if (get_child(1)!=NULL)
			out<<get_child(1)->get_text(); //display module parameter
		out<<";\n";
		if (get_child(2)!=NULL)
			get_child(2)->display(out, layer, space+TAB_SPACE); //display module body
		if (layer==3 || layer==2) {
			unsigned i, j;
			vector<AlwaysBlock *> all_block;
			vector<State *> block_state;
			all_block = my_parse->get_all_block();
			for (i=0; i<all_block.size(); i++) {
				if (all_block[i]->get_always_type()!=AlwaysBlock::NORMAL)
					continue;
				block_state =all_block[i]->get_all_state();
				ASSERT(block_state.size()>0);
				if (block_state.size()==1)
					continue;
				out<<"//state transition for block "<<all_block[i]->get_name()<<"\n";
				for (j=0; j<block_state.size(); j++)
					block_state[j]->display(out, layer, space); //display syn state transition
			}
			vector<Variable *> all_var;
			all_var = my_parse->get_all_variable();
			for (i=0; i<all_var.size(); i++)
				all_var[i]->display(out, layer, space); //display syn variable assign
		}
		out<<prespace<<"\nendmodule\n";
	} else {
		out<<prespace<<get_text()<<"\n";
	}
	if (get_prop() & ELEMENT_FIRST_CHILD) {
		Element *emt;
		LOOP_LEVEL(this, emt)
			if (emt!=this)
				emt->display(out, layer, space);
	}
}

void Variable::create_event_condition()
{
	event_cond =my_parse->condition_new(NULL);
	event_cond->make_zero();
}

bool Variable::check_assign()
{
	unsigned i, j;
	int ret;
	set <unsigned> intersect;

	for (i=0; i<assign_out.size(); i++) {
		AlwaysBlock * blk;
		Condition * c;
		blk = assign_out[i]->get_block();
		if (blk->get_always_type()==AlwaysBlock::ASYNC_RST)
			continue;
		c = assign_out[i]->get_precond();
		for (j=i+1; j<assign_out.size(); j++) {
			ret = assign_out[j]->get_precond()->cmp(c);
			if (abs(ret)<2) {
				printf("Error %d: %s has 2 contradict assign in one cycle, \nline%d %s:", ret, get_text().c_str(),
						assign_out[i]->get_line(), assign_out[i]->get_text().c_str());
				assign_out[i]->get_precond()->print(cout);
				printf("\nline%d %s:", assign_out[j]->get_line(), assign_out[j]->get_text().c_str());
				assign_out[j]->get_precond()->print(cout);
				printf("\n");
				exit(1);
			}
			if (ret==-2) {
				intersect.insert(i);
				intersect.insert(j);
			}
		}
	}

	if (!intersect.empty()) {
		set <unsigned>::iterator iter;
		printf("Warning: %s may have contradict assigns in one cycle, check following\n", get_text().c_str());
		for (iter=intersect.begin(); iter!=intersect.end(); iter++) {
			printf("line%d %s:", assign_out[*iter]->get_line(), assign_out[*iter]->get_text().c_str());
			assign_out[*iter]->get_precond()->print(cout);
			printf("\n");
		}
		return false;
	}

	return true;
}

void Variable::display(ostream& out, int layer, int space)
{
	string tab(TAB_SPACE, ' ');
	string prefill;
	Variable * clk=NULL, * async=NULL;
	Assign * arst=NULL;

	unsigned i;

	if ((layer!=2 && layer!=3) || (var_prop & VAR_REG)==0 || assign_out.empty())
		return;


	for (i=0; i<assign_out.size(); i++) {
		AlwaysBlock * blk;
		blk = assign_out[i]->get_block();
		ASSERT(blk->get_clk()!=NULL);
		if (blk->get_always_type()==AlwaysBlock::ASYNC_RST) {
			if (async!=NULL || arst!=NULL) {
				printf("reg %s have at least two async reset, this is not supported!\n", get_text().c_str());
				exit(1);
			}
			async = blk->get_clk();
			arst = assign_out[i];
		}
		else {
			if (clk!=NULL && clk!=blk->get_clk()) {
				printf("reg %s have at least two clock domain, this is not supported!\n", get_text().c_str());
				exit(1);
			}
			clk = blk->get_clk();
		}
	}

	ASSERT(clk!=NULL || async!=NULL);
	//following output "always @(posedge clk or negedge rst)
	out<<'\n'<<tab<<"always @(";
	if (clk!=NULL) { //output clock
		out<<"posedge "<<clk->get_text();
		if (async!=NULL)
			out<<" or ";
	}
	if (async!=NULL) { //output async signal
		if (arst->get_block()->get_edge())
			out<<"negedge ";
		else
			out<<"posedge ";
		out<<async->get_text();
	}
	out<<")\n";
	//following output 	"if (rst)"
	//                 	"    var <= #1 asyn"
	//					"else"
	int left= assign_out.size();
	if (async!=NULL) { //out async reset
		out<<tab<<"if (";
		if (arst->get_block()->get_edge())
			out<<'!';
		out<<async->get_text();
		out<<")\n";
		out<<tab<<tab<<arst->get_text()<<'\n';
		if (--left>0)
			out<<tab<<"else\n";
	}

	//following output 	"if (syn_rst)"
	//					"    var <= #1 syn"
	//					"else"
	for (i=0; i<assign_out.size(); i++) { //output sync reset
		AlwaysBlock * blk;
		blk = assign_out[i]->get_block();
		if (blk->get_always_type()==AlwaysBlock::SYNC_RST) {
			--left;
			if (assign_out[i]->get_precond()->isone()) {
				printf("no condition for sync reset assign: %s, line:%d\n", assign_out[i]->get_text().c_str(), assign_out[i]->get_line());
				exit(1);
			}
			if (!assign_out[i]->get_precond()->iszero()) {
				prefill = prefill +tab;
				out<<prefill<<tab<<"if (";
				assign_out[i]->get_precond()->print(out, (layer==2));
				out<<")\n";
				out<<prefill<<tab<<tab<<assign_out[i]->get_text()<<'\n';
				if (left>0)
					out<<prefill<<tab<<"else\n";
			}
		}
	}
	//following output  "begin"
	//					"if (cond1)
	//					"	var <= #1 expr1;"
	//					"if (cond2)
	//					"	var <= #1 expr2;"
	//					"end"
	if (left>0){ //output normal assign
		out<<prefill<<tab<<"begin\n";
		prefill = prefill +tab;
		for (i=0; i<assign_out.size(); i++) {
			AlwaysBlock * blk;
			blk = assign_out[i]->get_block();
			if (blk->get_always_type()==AlwaysBlock::NORMAL) {
				--left;
				if (assign_out[i]->get_precond()->iszero()) {
					printf("warning, assign: %s can't be reached, line:%d\n", assign_out[i]->get_text().c_str(), assign_out[i]->get_line());
					continue;
				} else {
					out<<prefill<<tab<<"if (";
					assign_out[i]->get_precond()->print(out, (layer==2));
					out<<")\n";
					out<<prefill<<tab<<tab<<assign_out[i]->get_text()<<'\n';
				}
			}
		}
		out<<prefill<<"end";
	}
	ASSERT(left==0);
	out<<'\n';
}

Statement::Statement(int b, int e, int l, StatementType st): Element(b, e, l, STATEMENT)
{
	smt_type = st;
	pre_cond = my_parse->condition_new(this);
	switch (smt_type) {
	case STATE:
		post_cond = my_parse->condition_new(this);
		post_cond->make_state((State*)this);
		break;
	case BEGINEND:
	case IF:
	case IFELSE:
	case WHILE:
	case DOWHILE:
	case WAIT_EVENT:
	case DISABLE:
		post_cond = my_parse->condition_new(this);
		break;
	case BEGINEND_NAME:
		post_cond = my_parse->condition_new(this);
		post_cond->make_zero();
		break;
	case ASSIGN:
		post_cond = pre_cond; //post_cond$ = pre_cond$;
		break;
	case TRIGGURE_EVENT:
		post_cond = pre_cond;
		break;
	}
}
/*
 * if (exp) 0; else 1; pre_cond0=pre_cond$ & exp; pre_cond1=pre_cond$ & !exp; post_cond$=post_cond0 | post_cond1;
 * if (exp) 0; pre_cond0 =pre_cond$ & exp; post_cond$=precond$ & !exp |post_cond0;
 * begin 0; 1; 2; end  pre_cond0=pre_cond$; pre_cond[i]=post_cond[i-1]; post_cond$=post_cond[n];
 * while(exp) 0;  pre_cond0=(pre_cond$ | post_cond0) & exp; post_cond$ = (pre_cond$ | post_cond0) & !exp;
 * do 0; while(exp);  pre_cond0=pre_cond$ | post_cond0&exp; post_cond$=post_cond0&!exp;
 * @(postedge clk); post_cond$=state0;
 * A<=B; post_cond$=pre_cond$;
 * ->event post_cond$=pre_cond$; save event condition
 * @event == while(!event) @(post_edge clk) state_name; pre_cond(state_name)=pre_cond$ & !event; post_cond$=pre_cond$&event |state_name&event;
 * disable A;
 *  0) A is external top block and this block is ASYNC_BLOCK
 *  1) A is external top block. reset |= pre_cond$;
 *  2) A is local block. post_cond$=0; post_cond[block] |= pre_cond$;
 */
void Statement::link_child(Element *emt)
{
	Element::link_child(emt);
	Element *first;
	Statement *s, *s1, *s2;
	Expression * exp;
	Condition *c, *c1, *c2;
	State *st;
	Assign *as;
	string vname;
	Variable *v;
	AlwaysBlock * ab;
	switch (smt_type) {
	case STATE:
		ASSERT(emt!=NULL && get_child_num()==1);
		ASSERT(emt->get_emt_type()==Element::ELEMENT_NORMAL);
		vname = emt->get_text();
		st = (State *) this;
		st->get_block()->put_clk(vname);
		break;
	case BEGINEND:
		ASSERT(emt!=NULL && get_child_num()==1);
		first = emt;

		LOOP_LEVEL(first, emt) {
			ASSERT(emt->get_emt_type()==Element::STATEMENT);
			s = (Statement *) emt;
			if (emt==first)
				s->pre_cond->make_equal_to(pre_cond);  //pre_cond0 = pre_cond$
			else
				s->pre_cond->make_equal_to(s1->post_cond); //pre_cond1 = post_cond0
			s1 =s;
		}
		post_cond->make_equal_to(s1->post_cond); //post_cond$ = post_condn;
		break;
	case BEGINEND_NAME:
		if (get_child_num()==1) {
			ASSERT(emt!=NULL);
			ASSERT(emt->get_emt_type()==Element::ELEMENT_NORMAL);
			my_parse->nameblock_begin(emt->get_text(), this);
			return;
		}
		ASSERT(emt!=NULL && get_child_num()==2);
		first =emt;
		LOOP_LEVEL(first, emt) {
			ASSERT(emt->get_emt_type()==Element::STATEMENT);
			s = (Statement *) emt;
			if (emt==first)
				s->pre_cond->make_equal_to(pre_cond);  //pre_cond0 = pre_cond$
			else
				s->pre_cond->make_equal_to(s1->post_cond); //pre_cond1 = post_cond0
			s1 =s;
		}
		c = my_parse->condition_new(NULL);
		*c = *post_cond;
		post_cond->make_or(c, s1->post_cond); //post_cond$= post_condn | disable
		my_parse->nameblock_end();
		break;
	case IF:
		if (get_child_num()==1) {
			ASSERT(emt!=NULL);
			ASSERT(emt->get_emt_type()==Element::EXPRESSION);
			return;
		}
		//e is statement or NULL now
		if (emt==NULL) {
			post_cond->make_equal_to(pre_cond);
			return;
		}
		//e is statement now
		ASSERT(emt->get_emt_type()==Element::STATEMENT && get_child_num()==2);
		exp = (Expression *) this->get_child(0);
		s= (Statement *) emt;
		c = my_parse->condition_new(NULL);
		c->make_expression(exp);
		s->pre_cond->make_and(this->pre_cond, c);  //pre_cond0 = pre_cond$ & exp
		c1 = my_parse->condition_new(NULL);
		c1->make_and_not(this->pre_cond, c); //c1 =pre_cond$ & !c
		post_cond->make_or(c1, s->post_cond);  //post_cond$ = c1 || post_cond0
		break;
	case IFELSE:
		if (get_child_num()==1) {
			ASSERT(emt!=NULL);
			ASSERT(emt->get_emt_type()==Element::EXPRESSION);
			return;
		}
		if (get_child_num()==2) {
			ASSERT(emt==NULL || emt->get_emt_type()==Element::STATEMENT);
			return;
		}
		ASSERT(emt->get_emt_type()==Element::STATEMENT && get_child_num()==3);
		exp = (Expression *) this->get_child(0);
		s1= (Statement *) this->get_child(1);
		s2= (Statement *) emt;
		if (s1==NULL && s2==NULL) {
			post_cond->make_equal_to(pre_cond);
			return;
		}
		c = my_parse->condition_new(NULL);
		Condition *post_c1, *post_c2;
		c->make_expression(exp);
		if (s1!=NULL) {
			s1->pre_cond->make_and(this->pre_cond, c);  //pre_cond0 = pre_cond$ & exp
			post_c1 = s1->post_cond;
		} else {
			c1 = my_parse->condition_new(NULL);
			c1->make_and(this->pre_cond, c);
			post_c1 = c1;
		}
		if (s2!=NULL) {
			s2->pre_cond->make_and_not(this->pre_cond, c); //pre_cond1 = pre_cond$ & !exp
			post_c2 = s2->post_cond;
		} else {
			c2 = my_parse->condition_new(NULL);
			c2->make_and_not(this->pre_cond, c);
			post_c2 = c2;
		}
		post_cond->make_or(post_c1, post_c2);  //post_cond$ = post_cond0 | post_cond1
		break;
	case WHILE:
		if (get_child_num()==1) {
			ASSERT(emt!=NULL);
			ASSERT(emt->get_emt_type()==Element::EXPRESSION);
			return;
		}
		//e is statement or NULL now
		if (emt==NULL) {
			printf("inside while without @postedge at line %d", line);
			return;
		}
		ASSERT(emt->get_emt_type()==Element::STATEMENT && get_child_num()==2);
		exp = (Expression *) this->get_child(0);
		s= (Statement *) emt;
		c = my_parse->condition_new(NULL);
		c1 = my_parse->condition_new(NULL);
		c->make_expression(exp);
		c1->make_or(pre_cond, s->post_cond); // c1= pre_cond$ || post_cond0
		s->pre_cond->make_and(c1, c); //pre_cond0 = c1 & exp;
		post_cond->make_and_not(c1, c); //post_cond$ = c1 & !exp;
		break;
	case DOWHILE:
		if (get_child_num()==1) {
			ASSERT(emt!=NULL);
			ASSERT(emt->get_emt_type()==Element::EXPRESSION);
			return;
		}

		//e is statement or NULL now
		if (emt==NULL) {
			printf("inside while without @postedge at line %d", line);
			return;
		}
		ASSERT(emt->get_emt_type()==Element::STATEMENT && get_child_num()==2);
		exp = (Expression *) this->get_child(0);
		s= (Statement *) emt;
		c = my_parse->condition_new(NULL);
		c1 = my_parse->condition_new(NULL);
		c->make_expression(exp);
		c1->make_and(s->post_cond, c);  //c1=post_cond0 & exp;
		s->pre_cond->make_or(pre_cond, c1); //pre_cond0 = c1 | pre_cond$;
		post_cond->make_and_not(s->post_cond, c); //post_cond$=post_cond0 & !exp;
		break;
	case WAIT_EVENT:
		if (get_child_num()==1) {
			ASSERT(emt!=NULL);
			ASSERT(emt->get_emt_type()==ELEMENT_NORMAL);
			return;
		}
		ASSERT(emt!=NULL);
		ASSERT(emt->get_emt_type()==Element::STATEMENT && get_child_num()==2);
		s = (Statement *) emt;
		ASSERT(s->smt_type==Statement::STATE);
		vname = this->get_child(0)->get_text();
		v =my_parse->variable_lookup(vname);
		if (v==NULL || (v->get_var_prop() & VAR_EVENT)==0) {
			printf("only support wait for event, at line %d", line);
			exit(1);
		}
		c = my_parse->condition_new(NULL);
		c->make_or(pre_cond, s->post_cond); //c=pre_cond$ || state
		s->pre_cond->make_and_not(c, v->get_evt_cond()); //state.pre_cond0 = c &!event
		post_cond->make_and(c, v->get_evt_cond()); //post_cond$ = c & event
		break;
	case ASSIGN:
		if (get_child_num()==1) {
			ASSERT(emt!=NULL);
			ASSERT(emt->get_emt_type()==ELEMENT_NORMAL);
			return;
		}
		vname = this->get_child(0)->get_text();
		v =my_parse->variable_lookup(vname);
		if (v==NULL) {
			printf("variable %s not found at line %d", vname.c_str(), line);
			exit(1);
		}
		if (!(v->get_var_prop() & VAR_REG)) {
			printf("variable %s is not reg at line %d", vname.c_str(), line);
			exit(1);
		}
		ASSERT(emt!=NULL);
		ASSERT(emt->get_emt_type()==Element::EXPRESSION && get_child_num()==2);
		as = (Assign *) this;
		as->put_left_var(v);
		as->put_right_exp((Expression *)emt);
		v->link_assign(as);
		break;
	case TRIGGURE_EVENT:
		ASSERT(emt!=NULL && get_child_num()==1);
		ASSERT(emt->get_emt_type()==ELEMENT_NORMAL);
		vname = emt->get_text();
		v =my_parse->variable_lookup(vname);
		if (v==NULL) {
			printf("variable not found %s at line %d", vname.c_str(), line);
			exit(1);
		}
		c = my_parse->condition_new(NULL);
		c1 = v->get_evt_cond();
		*c = *c1;
		c1->make_or(c, pre_cond);	//save event condition: event |= pre_cond
		break;
	case DISABLE:
		ASSERT(emt!=NULL && get_child_num()==1);
		ASSERT(emt->get_emt_type()==ELEMENT_NORMAL);
		if (emt->get_text()=="ASYNC_RESET" || emt->get_text()=="SYNC_RESET") {
			printf("can't disable reset at line %d", line);
			exit(1);
		}

		if (my_parse->get_current_block()->get_always_type()==AlwaysBlock::ASYNC_RST) {
			ab =my_parse->ablock_lookup(emt->get_text());
			if (ab==NULL) { //not exist in always_block
				ab =my_parse->unresolved_ablock_asynrst(emt->get_text());
				if (ab!=NULL) {
					printf("two async rst, line:%d %s and line:%d %s both disable %s", ab->get_line(), ab->get_name().c_str(),
							my_parse->get_current_block()->get_line(), my_parse->get_current_block()->get_name().c_str(), emt->get_text().c_str());
					exit(1);
				}
				my_parse->unresolved_ablock_asynrst_new(emt->get_text(), my_parse->get_current_block());
			} else {
				if (ab->get_asyn_block()!=NULL) {
					printf("two async rst, line:%d %s and lind:%d %s both disable %s", ab->get_asyn_block()->get_line(), ab->get_asyn_block()->get_name().c_str(),
							my_parse->get_current_block()->get_line(), my_parse->get_current_block()->get_name().c_str(), emt->get_text().c_str());
					exit(1);
				}
				ab->set_asyn_block(my_parse->get_current_block());
			}
		} else { //it is normal or syn always block
			s =my_parse->nameblock_lookup(emt->get_text());
			if (s==NULL) { 				//not exist in local always_block
				ab =my_parse->ablock_lookup(emt->get_text());
				if (ab==NULL) { 		//not exist in always_block
					c1 =my_parse->unresolved_ablock_synrst(emt->get_text());
					if (c1==NULL) {		//not exist in unresolved always block
						c1 = my_parse->unresolved_ablock_synrst_new(emt->get_text());
						c1->make_equal_to(pre_cond);
					} else {			//exist in unresolved always block
						c = my_parse->condition_new(NULL);
						*c = *c1;
						c1->make_or(c, pre_cond); //set syn reset condition: syn_reset |= pre_cond$
					}
				} else { 				//exist in always_block
					c = my_parse->condition_new(NULL);
					*c = *(ab->get_syn_reset());
					ab->get_syn_reset()->make_or(c, pre_cond); //set syn reset condition: syn_reset |= pre_cond$
				}
				post_cond->make_equal_to(pre_cond); //post_cond$ = pre_condn;
			} else { 					//exist in local always_block
				c = my_parse->condition_new(NULL);
				*c = *(s->post_cond);
				s->post_cond->make_or(c, pre_cond); //set disable condition: disable |= pre_cond$
				post_cond->make_zero();  //disable following statements,
			}
		}
		break;
	default:
		ASSERT(0);
		break;
	}
}

void Statement::display(ostream& out, int layer, int space)
{
	Statement *st;
	string prespace(space, ' ');
	string tab(TAB_SPACE, ' ');

	switch (smt_type) {
	case STATE:
		State *s;
		s = (State *)this;
		if (s->is_define())
			out<<prespace<<"begin trig_"<<s->get_name()<<"<= #1 1;\n";
		out<<prespace<<get_text();
		if (layer==1) {
			out<<"/*";
			pre_cond->print(out);
			out<<"*/";
		}
		if (s->is_define())
			out<<"\n"<<prespace<<"end";
		out<<"\n";
		break;
	case BEGINEND:
		out<<prespace<<"begin\n";
		get_child(0)->display(out, layer, space+TAB_SPACE);
		out<<prespace<<"end\n";
		break;
	case BEGINEND_NAME:
		out<<prespace<<"begin : ";
		out<<get_child(0)->get_text()<<"\n";
		get_child(1)->display(out, layer, space+TAB_SPACE);
		out<<prespace<<"end\n";
		break;
	case IF:
		out<<prespace<<"if ("<<get_child(0)->get_text()<<")\n";
		st = (Statement *) get_child(1);
		if (st==NULL)
			out<<prespace<<tab<<";\n";
		else
			if (st->get_smt_type()==BEGINEND || st->get_smt_type()==BEGINEND_NAME)
				st->display(out, layer, space);
			else
				st->display(out, layer, space+TAB_SPACE);
		break;
	case IFELSE:
		out<<prespace<<"if ("<<get_child(0)->get_text()<<")\n";
		st = (Statement *) get_child(1);
		if (st==NULL)
			out<<prespace<<tab<<";\n";
		else
			if (st->get_smt_type()==BEGINEND || st->get_smt_type()==BEGINEND_NAME)
				st->display(out, layer, space);
			else
				st->display(out, layer, space+TAB_SPACE);
		out<<prespace<<"else\n";
		st = (Statement *) get_child(2);
		if (st==NULL)
			out<<prespace<<tab<<";\n";
		else
			if (st->get_smt_type()==BEGINEND || st->get_smt_type()==BEGINEND_NAME)
				st->display(out, layer, space);
			else
				st->display(out, layer, space+TAB_SPACE);
		break;
	case WHILE:
		out<<prespace<<"while ("<<get_child(0)->get_text()<<")\n";
		st = (Statement *) get_child(1);
		if (st->get_smt_type()==BEGINEND || st->get_smt_type()==BEGINEND_NAME)
			st->display(out, layer, space);
		else
			st->display(out, layer, space+TAB_SPACE);
		break;
	case DOWHILE:
		out<<prespace<<"while ("<<get_child(0)->get_text()<<") //dowhile\n";
		st = (Statement *) get_child(1);
		if (st->get_smt_type()==BEGINEND || st->get_smt_type()==BEGINEND_NAME)
			st->display(out, layer, space);
		else
			st->display(out, layer, space+TAB_SPACE);
		break;
	case WAIT_EVENT:
		out<<prespace<<get_text();
		if (layer==1) {
			out<<"/*";
			pre_cond->print(out);
			out<<"*/";
		}
		out<<"\n";
		break;
	case ASSIGN:
		out<<prespace<<get_text();
		if (layer==1) {
			out<<"/*";
			pre_cond->print(out);
			out<<"*/";
		}
		out<<"\n";
		break;
	case TRIGGURE_EVENT:
		out<<prespace<<get_text();
		if (layer==1) {
			out<<"/*";
			pre_cond->print(out);
			out<<"*/";
		}
		out<<"\n";
		break;
	case DISABLE:
		out<<prespace<<get_text();
		if (layer==1) {
			out<<"/*";
			pre_cond->print(out);
			out<<"*/";
		}
		out<<"\n";
		break;
	default:
		ASSERT(0);
		break;
	}
	if (get_prop() & ELEMENT_FIRST_CHILD) {
		Element *emt;
		LOOP_LEVEL(this, emt)
			if (emt!=this)
				emt->display(out, layer, space);
	}
}

void State::display(ostream& out, int layer, int space)
{
	string tab(TAB_SPACE, ' ');
	string prefill;
	bool first_state;
	Variable * clk=NULL, * async=NULL;

	if (layer<2) {
		Statement::display(out, layer, space);
		return;
	}
	if (this==block->get_first_state())
		first_state=true;
	else
		first_state=false;

	clk = block->get_clk();
	ASSERT(clk!=NULL);
	//following output "always @(posedge clk or negedge rst)"
	out<<tab<<"always @(posedge "<<clk->get_text();
	if (block->get_asyn_block()!=NULL) {
		async = block->get_asyn_block()->get_clk();
		if (block->get_asyn_block()->get_edge())
			out<<" or negedge ";
		else
			out<<" or posedge ";
		out<<async->get_text();
	} else
		if (first_state)
			printf("Warning!!! No async reset for block %s\n", block->get_name().c_str());
	out<<")\n";
	//following output  "if (rst)
	//                  "	state <= #1 1;
	//					"else
	if (async!=NULL) {
		out<<tab<<"if (";
		if (block->get_asyn_block()->get_edge())
			out<<'!';
		out<<async->get_text();
		out<<")\n";
		out<<tab<<tab<<name<<" <= #1 ";
		if (first_state)
			out<<"1;\n";
		else
			out<<"0;\n";
		out<<tab<<"else\n";
		prefill=tab;
	}
	//following output	"if (syn_rst)
	//					"	state<= #1 1;
	//					"else"
	if (!block->get_syn_reset()->iszero()) {
		out<<prefill<<tab<<"if (";
		block->get_syn_reset()->print(out, (layer==2));
		out<<")\n";
		out<<prefill<<tab<<tab<<name<<" <= #1 ";
		if (first_state)
			out<<"1;\n";
		else
			out<<"0;\n";
		out<<prefill<<tab<<"else\n";
		prefill+=tab;
	}
	//following output  "	state <= #1 cond;
	out<<prefill<<tab<<name<<" <= #1 ";
	pre_cond->print(out, (layer==2));
	out<<";\n\n";
}

AlwaysBlock::AlwaysBlock(int b, int e, int l, string n, int edge) :
	Element(b, e, l, ALWAYSBLOCK)
{
	name =n;
	clk = NULL;
	this->edge =edge;
	if (n=="ASYNC_RESET")
		always_type = ASYNC_RST;
	else
		if (n=="SYNC_RESET")
			always_type = SYNC_RST;
		else {
			always_type = NORMAL;
			syn_reset = my_parse->unresolved_ablock_synrst(n);
			if (syn_reset==NULL) {
				syn_reset = my_parse->condition_new(NULL);
				syn_reset->make_zero();
			}
			asyn_reset = my_parse->unresolved_ablock_asynrst(n);
			my_parse->unresolved_ablock_del(n);
		}
}

void AlwaysBlock::put_clk(string vclk)
{
	Variable *c;
	c =my_parse->variable_lookup(vclk);
	if (c==NULL) {
		printf("clock not found %s at line %d", vclk.c_str(), line);
		exit(1);
	}
	if (clk==NULL)
		clk =c;
	else
		if (clk!=c) {
			printf("two clock domain in always block %s, at line %d", name.c_str(), line);
			exit(1);
		}
}
void AlwaysBlock::link_child(Element *emt)
{
	Element *first;
	Element::link_child(emt);
	ASSERT(emt!=NULL && get_child_num()==1 && emt->get_emt_type()==STATEMENT);
	Statement * st = (Statement *) emt;
	Statement * child;
	ASSERT(st->get_smt_type()==Statement::BEGINEND_NAME);
	if (always_type ==ASYNC_RST) {
		st->pre_cond->make_one();
		st->post_cond->make_one();
		first = st->get_child(1);
		LOOP_LEVEL(first, emt) {
			ASSERT(emt->get_emt_type() ==STATEMENT);
			child = (Statement *) emt;
			child->pre_cond->make_one();
			child->post_cond->make_one();
			if (child->get_smt_type()!=Statement::ASSIGN && child->get_smt_type()!=Statement::DISABLE)
				printf("wrong at line %d, only assign and disable are allowed in reset block", line);
		}
		return;
	}
	if (always_type ==SYNC_RST) {
		ASSERT(block_st.size()==1);
		first = st->get_child(1);
		LOOP_LEVEL(first, emt) {
			ASSERT(emt->get_emt_type() ==STATEMENT);
			child = (Statement *) emt;
			if (child->get_smt_type()==Statement::WHILE || child->get_smt_type()==Statement::DOWHILE) {
				printf("wrong at line %d, WHILE is not allowed in reset block", line);
				exit(1);
			}
			if (child->get_smt_type()==Statement::TRIGGURE_EVENT){
				printf("wrong at line %d, TRIGGURE is not allowed in reset block", line);
				exit(1);
			}
		}
	}
	if (block_st.size()==1) {	//only one posedge(clk)
		st->pre_cond->make_one();
		st->post_cond->make_one();
		ASSERT(st->get_child(1)->get_emt_type() == STATEMENT);
		child = (Statement *) st->get_child(1);
		ASSERT(child->get_smt_type() == Statement::STATE);
		child->pre_cond->make_one();
		child->post_cond->make_one();
	} else //normal condition, which has several states
		st->pre_cond->make_equal_to(st->post_cond);
}

void AlwaysBlock::display(ostream& out, int layer, int space)
{
	string prespace(space, ' ');
	string tab(TAB_SPACE, ' ');

	if (layer==1 || layer==0) {
		if (always_type ==ASYNC_RST) {
			out<<"\n";
			out<<prespace<<"always\n";
			out<<prespace<<"begin : ASYNC_RESET\n";
			out<<prespace<<tab<<"@(";
			if (edge==0)
				out<<"posedge ";
			else
				out<<"negedge ";
			out<<clk->get_text()<<");\n";
			this->get_child(0)->get_child(1)->display(out, layer, space+TAB_SPACE);
			out<<prespace<<"end\n";
		} else {
			for (unsigned i=0; i<block_st.size(); i++)
				if (block_st[i]->is_define()) {
					out<<prespace<<"reg\t\t"<<block_st[i]->get_name()<<",";
					out<<"trig_"<<block_st[i]->get_name()<<";\n";  //display reg state, trig_state;
					out<<prespace<<"initial begin\n";
					out<<prespace<<tab<<"trig_"<<block_st[i]->get_name()<<"=0;\n";
					out<<prespace<<tab<<block_st[i]->get_name()<<"=0;\n";
					out<<prespace<<"end\n";
					out<<prespace<<"always @(posedge "<<"trig_"<<block_st[i]->get_name()<<") begin\n"; //display @(posedge trig_state)
					out<<prespace<<tab<<block_st[i]->get_name()<<"<= #1 1;\n";                         //begin state <= #1 1;
					out<<prespace<<tab<<"trig_"<<block_st[i]->get_name()<<"<= #1 0;\n";                //trig_state <= #1 0; end
					out<<prespace<<"end\n";
					out<<prespace<<"always @(posedge "<<clk->get_text()<<") "; //display  @(posedge clk)
					out<<prespace<<tab<<block_st[i]->get_name()<<"<= #1 0;\n"; // state<= #1 0;
				}

			out<<prespace<<"always\n";
			this->get_child(0)->display(out, layer, space);
		}
	}
	if (layer==3 || layer==2) {
		if (block_st.size()>1) {
			out<<prespace<<"//states for block "<<name<<"\n";
			for (unsigned i=0; i<block_st.size(); i++)
				out<<prespace<<"reg\t\t"<<block_st[i]->get_name()<<";\n"; //display reg state1; reg state2;
		}
		out<<"\n";
	}
	if (get_prop() & ELEMENT_FIRST_CHILD) {
		Element *emt;
		LOOP_LEVEL(this, emt)
			if (emt!=this)
				emt->display(out, layer, space);
	}
}

vector<Condition *> Condition::cond_sets;

static string invert_op[] = {
		"!=",
		"==",
		"<=",
		">=",
		"<",
		">"
};
void Condition::print(ostream& out, bool raw)
{
	vector<VUI> r;
	Element *e;
	State *state;
	State * b;
	string sh;
	if (bdd_node==Robdd::zero) {
		out<<'0';
		return;
	}
	if (bdd_node==Robdd::one) {
		out<<'1';
		return;
	}
	r = bdd_node->get_logic();
	for (unsigned i=0; i<r.size(); i++) {
		sh.clear();

		b = NULL;
		for (unsigned j=0; j<r[i].size(); j+=2) {
			e = (Element *)r[i][j+1];
			if (e->get_emt_type()==Element::STATEMENT && r[i][j]==1) {
				b = (State *) e; //records first reachable state's block
				break;
			}
		}

		for (unsigned j=0; j<r[i].size(); j+=2) {
			e = (Element *)r[i][j+1];
			if (e->get_emt_type()==Element::EXPRESSION) {
				if (raw) {
					if (r[i][j]==0)
						sh+="!";
					sh+='('+e->get_text()+')';
				} else {
					Expression *exp = (Expression*) e;
					if (exp->get_exp_type()!=Expression::NA && exp->get_exp_type()!=Expression::NUMBER && exp->get_exp_type()!=Expression::VAR) {
						if (r[i][j]==0) {
							if (exp->get_exp_type()==Expression::NOT)
								sh+=exp->child[0]->get_text();
							else {
								sh+='(';
								sh+=exp->child[0]->get_text();
								sh+= invert_op[(int)exp->get_exp_type()];
								sh+=exp->child[1]->get_text();
								sh+=')';
							}
						} else
							if (exp->get_exp_type()==Expression::NOT)
								sh+=e->get_text();
							else
								sh+='('+e->get_text()+')';
					} else{
						if (r[i][j]==0)
							sh+="!";
						if (exp->get_exp_type()==Expression::NUMBER || exp->get_exp_type()==Expression::VAR)
							sh+=e->get_text();
						else
							sh+='('+e->get_text()+')';
					}
				}
			} else { //now do optimize check for state
				state = (State *) e;
				if (r[i][j]==0 && state->get_block()!=b->get_block()) {
					sh+="!";			//print non-reachable state which is in different block, generated by ->
					sh+=state->get_name();
				}
				if (r[i][j]==1 && state->get_block()==b->get_block()) {
					if (state==b)
						sh+=state->get_name(); //print first reachable state's block
					else {
						printf("Optimize not good, same block's two reachable state exist together (%s, %s)\n", state->get_name().c_str(), b->get_name().c_str());
						sh.clear();			//two reachable state which are in same block, is false, it should be optimized
						break;
					}
				}
				if (r[i][j]==1 && state->get_block()!=b->get_block())
					sh+=state->get_name(); //print other block's reachable state, generated by disable and ->
				if (r[i][j]==0 && state->get_block()==b->get_block()) {
					printf("Optimize not good, same block's reachable and non-reachable state exist together (%s,%s)\n",
							state->get_name().c_str(), b->get_name().c_str());
					continue;				//non-reachable state is covered by same block's reachable state condition, it should be optimized, so delete non-reachable state
				}
			}
			if (j+2==r[i].size()) {
				if (i+1!=r.size())
					sh+=" || ";
			} else
				sh+="&&";
		}

		out<<sh;
	}
}

/*
 * return
 * 0 : v1=v2
 * 1 : v1->v2, all v2's literals belong to v1
 * -1: v2->v1, all v1's literals belong to v2
 * 2 : v1 ^ v2=0, if v1==1, then v2=0. Or if v2==1, then v1=0
 * -2: v1 ^ v2!=0, There is a minterm which let v1=1 and v2=1
 */
static int cmp_product(VUI & v1, VUI & v2)
{
	unsigned i, j;
	bool v1_v2=true, v2_v1=true; //v1_v2 means v1->v2
	bool intersect_state=false;
	Element *e;
	vector<bool> found_v2j(v2.size()/2, false);

	for (i=0; i<v1.size(); i+=2) {
		bool found_v1i;
		found_v1i=false;
		for (j=0; j<v2.size(); j+=2) {
			if (v1[i+1]==v2[j+1]) {
				if (v1[i]!=v2[j])
					return 2;
				else {
					e = (Element *)v2[j+1];
					if (e->get_emt_type()==Element::STATEMENT)
						intersect_state =true;
				}
				found_v1i=true;
				found_v2j[j/2]=true;
			}
		}
		if (!found_v1i)
			v2_v1=false;
	}
	for (j=0; j<found_v2j.size(); j++)
		if (!found_v2j[j])
			v1_v2=false;

	if (v1_v2 && v2_v1)
		return 0;
	if (!v1_v2 && v2_v1)
		return -1;
	if (v1_v2 && !v2_v1)
		return 1;
	if (intersect_state)
		return -2;
	else
		return 2;
}

/*
 * return
 * 0 : v1=v2
 * 1 : v1->v2
 * -1: v2->v1
 * 2 : v1 ^ v2=0
 * -2: v1 ^ v2!=0
 */
int Condition::cmp(Condition *c)
{
	vector<VUI> r1, r2;
	int ret;
	bool intersect=false;
	if (bdd_node==Robdd::zero || bdd_node==Robdd::one || c->bdd_node==Robdd::zero || c->bdd_node==Robdd::one)
		return 2;

	r1 = bdd_node->get_logic();
	r2 = c->bdd_node->get_logic();
	for (unsigned i=0; i<r1.size(); i++)
		for (unsigned j=0; j<r2.size(); j++) {
			ret = cmp_product(r1[i], r2[j]);
			if (abs(ret)<2) {
				printf("leadto %d,%d\n", i, j);
				return ret;
			}
			if (ret==-2) {
				printf("intersect %d,%d\n", i, j);
				intersect=true;
			}
		}
	if (intersect)
		return -2;
	else
		return 2;
}

void Condition::assign_bdd_all()
{
	unsigned i;
	bool finish=false;
	for (i=0; i<cond_sets.size(); i++) { //first assign all raw_state and raw_expression
		switch (cond_sets[i]->cond_type) {
		case RAW_STATE:
			cond_sets[i]->bdd_node = Robdd::leaf_var((unsigned long long)cond_sets[i]->raw.state);
			break;
		case RAW_EXPRESSION:
			cond_sets[i]->bdd_node = Robdd::leaf_var((unsigned long long)cond_sets[i]->raw.exp);
			break;
		case ZERO:
			cond_sets[i]->bdd_node = Robdd::zero;
			break;
		case ONE:
			cond_sets[i]->bdd_node = Robdd::one;
			break;
		default:
			continue;
		}
	}

	while(!finish) {  //continue kuopo assign until no conditions can be assigned bdd_node
		finish=true;
		for (i=0; i<cond_sets.size(); i++) {
			if (cond_sets[i]->bdd_node!=NULL)
				continue;
			switch (cond_sets[i]->cond_type) {
			case EQUAL_TO:
				if (cond_sets[i]->left_cond->bdd_node !=NULL) {
					cond_sets[i]->bdd_node = cond_sets[i]->left_cond->bdd_node;
					finish =false;
				}
				break;
			case AND:
				if (cond_sets[i]->left_cond->bdd_node !=NULL && cond_sets[i]->right_cond->bdd_node !=NULL) {
					cond_sets[i]->bdd_node = Robdd::tree_and(cond_sets[i]->left_cond->bdd_node, cond_sets[i]->right_cond->bdd_node);
					finish =false;
				}
				break;
			case OR:
				if (cond_sets[i]->left_cond->bdd_node !=NULL && cond_sets[i]->right_cond->bdd_node !=NULL) {
					cond_sets[i]->bdd_node = Robdd::tree_or(cond_sets[i]->left_cond->bdd_node, cond_sets[i]->right_cond->bdd_node);
					finish =false;
				}
				break;
			case AND_NOT:
				if (cond_sets[i]->left_cond->bdd_node !=NULL && cond_sets[i]->right_cond->bdd_node !=NULL) {
					cond_sets[i]->bdd_node = Robdd::tree_and_not(cond_sets[i]->left_cond->bdd_node, cond_sets[i]->right_cond->bdd_node);
					finish =false;
				}
				break;
			default:
				continue;
			}
		}
	}

	//if there is an unassigned condition, report error
	finish =true;
	for (i=0; i<cond_sets.size(); i++)
		if (cond_sets[i]->bdd_node==NULL) {
			printf("Check loop without @(posedge), there is unassigned condition");
			if (cond_sets[i]->smt!=NULL)
				printf(" at line %d\n", cond_sets[i]->smt->get_line());
			else
				printf(" at unknown line\n");
			finish =false;
		}
	if (!finish)
		exit(1)	;
	//compute sop
	vector<Robdd*> ve;
	for (i=0; i<cond_sets.size(); i++)
		ve.push_back(cond_sets[i]->bdd_node);
	Robdd::simplify(ve);
	//check if sop equal to Robdd
	for (i=0; i<cond_sets.size(); i++)
		cond_sets[i]->bdd_node->check();

	vector<Variable *> all_var;
	all_var = my_parse->get_all_variable();
	for (i=0; i<all_var.size(); i++)
		all_var[i]->check_assign();

}
