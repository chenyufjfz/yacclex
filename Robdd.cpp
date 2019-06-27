/*
 * Robdd.cpp
 *
 *  Created on: Oct 16, 2012
 *      Author: yuchen
 */

#include "Robdd.h"
#include "SimplifyTool.h"
#include <algorithm>

Sop::Sop() {
	state = NOT_ASSIGN;
}

Sop::~Sop() {

}

void Sop::print(ostream& out)
{
	for (unsigned i=0; i<sum.size(); i++) {
		for (unsigned j=0; j<sum[i].size(); j++) {
			out<<sum[i][j];
			if (j+1==sum[i].size()) {
				if (i+1!=sum.size())
					out<<'+';
			}
			else
				out<<'*';
		}
	}
	out<<'\n';
	for (unsigned i=0; i<vars.size(); i++)
		out<<vars[i]<<' ';
	out<<'\n';
}

void Sop::check(bool sign)
{
	unsigned i;
	for (i=0; i<sum.size(); i++)
		for (unsigned j=1; j<sum[i].size(); j++)
			if (sign)
				ASSERT(abs(sum[i][j])>abs(sum[i][j-1]));
			else
				ASSERT(abs(sum[i][j])<abs(sum[i][j-1]));
	for (i=1; i<vars.size(); i++)
		if (sign)
			ASSERT(vars[i]>vars[i-1]);
		else
			ASSERT(vars[i]<vars[i-1]);
}

Robdd * Robdd::zero;
Robdd * Robdd::one;
set <Robdd> Robdd::node_set;
vector<unsigned> Robdd::tags;
bool Robdd::sign;
#define SIMPLE_WIDE_IN  50
#define SIMPLE_WIDE_OUT 35
#define SIMPLE_ROW_MAX  1000

Robdd::Robdd() {
	left = NULL;
	right = NULL;
	var =0;
}

Robdd::Robdd(int v, Robdd* l, Robdd *r) {
	left = l;
	right = r;
	var =v;
}

Robdd::~Robdd() {

}

Robdd * Robdd::find_or_add(const Robdd & tn)
{
	pair<set <Robdd>::iterator, bool> pos;
	pos=node_set.insert(tn);		//insert return new position or exist position
	ASSERT((pos.first)->var==tn.var);
	return (Robdd *) &(*(pos.first));
}

void Robdd::init()
{
	zero =find_or_add(Robdd(0x73336025, NULL, NULL));  //zero and one is only pointer, their var have no meaning
	one =find_or_add(Robdd(0x73378615, NULL, NULL));
	sign = true;
	zero->s.state=Sop::ZERO;
	one->s.state=Sop::ONE;
}

Robdd * Robdd::leaf_var(unsigned long long _tag)
{
	int v;
	vector<unsigned>::iterator pos;
	unsigned tag = (_tag & 0xffffffff) ^ (_tag >> 32 & 0xffffffff);
	pos = find(tags.begin(), tags.end(), tag);
	if (pos==tags.end()) {
		tags.push_back(tag);
		v = tags.size();
	} else {
		v = pos - tags.begin();
		v++;
	}

	return find_or_add(Robdd(v, zero, one));
}

Robdd * Robdd::leaf_var_not(unsigned long long _tag)
{
	int v;
	vector<unsigned>::iterator pos;
	unsigned tag = (_tag & 0xffffffff) ^ (_tag >> 32 & 0xffffffff);
	pos = find(tags.begin(), tags.end(), tag);
	if (pos==tags.end()) {
		tags.push_back(tag);
		v = tags.size();
	} else {
		v = pos - tags.begin();
		v++;
	}

	return find_or_add(Robdd(v, one, zero));
}

// f = vf1 + !vf0
// !f = (!v+!f1) (v + !f0) =v!f1 + !v!f0 + !f0!f1 = v!f1 + !v!f0
Robdd * Robdd::tree_not(Robdd *tn)
{
	Robdd * nl, *nr;
	int nv;

	if (tn==zero)
		return one;
	if (tn==one)
		return zero;
	ASSERT(tn->var>0);
	nv = tn->var;
	nl = tree_not(tn->left);			//nl = !f0
	nr = tree_not(tn->right);			//nr = !f1
	return find_or_add(Robdd(nv, nl, nr));
}

/*
 * f =ite(v, f0, f1) = vf1 + !vf0
 * g =ite(v, g0, g1) = vg1 + !vg0
 * f & g = (vf1 + !vf0) (vg1 + !vg0) =vf1g1 +!vf0g0 = ite(v, f0g0, f1g1)
 */
Robdd * Robdd::tree_and(Robdd * tn1, Robdd * tn2)
{
	Robdd * nl, *nr;
	int nv;

	ASSERT(tn1->var>0 && tn2->var>0);
	if (tn1==zero || tn2==zero)  // 0&g=0,
		return zero;
	if (tn1==one)				//1&g=g
		return tn2;
	if (tn2==one)
		return tn1;

	if (tn1==tn2)			//vf+!vf=f
		return tn1;
	if (tn1->var==tn2->var) {
		nv = tn1->var;
		nl = tree_and(tn1->left, tn2->left);	//nl=f0g0
		nr = tree_and(tn1->right, tn2->right);	//nr=f1g1
	} else {
		if (tn1->var>tn2->var ^ sign) {
			nv = tn1->var;							//g=vg+!vg
			nl = tree_and(tn1->left, tn2);			//nl=f0g
			nr = tree_and(tn1->right, tn2);			//nr=f1g
		}
		if (tn1->var<tn2->var ^ sign) {
			nv = tn2->var;							//f=vf+!vf
			nl = tree_and(tn1, tn2->left);			//nl=fg0
			nr = tree_and(tn1, tn2->right);			//nr=fg1
		}
	}
	ASSERT(nl!=NULL && nr!=NULL);
	if (nl==nr)									//vf+!vf=f
		return nl;
	return find_or_add(Robdd(nv, nl, nr));
}
/*
 * f =ite(v, f0, f1) = vf1 + !vf0
 * g =ite(v, g0, g1) = vg1 + !vg0
 * !g = !(vg1 + !vg0) = !(vg1)!(!vg0) =(!v+!g1) (v+!g0) =v!g1+!v!g0
 * f & !g = (vf1 + !vf0) (v!g1+!v!g0) =vf1!g1 +!vf0!g0= ite(v, f0!g0, f1!g1)
 */
Robdd * Robdd::tree_and_not(Robdd * tn1, Robdd * tn2)
{
	Robdd * nl, *nr;
	int nv;

	ASSERT(tn1->var>0 && tn2->var>0);
	if (tn1==zero || tn2==one)	//0&!g=0, f & !1=0
		return zero;
	if (tn1==one)				//1&!g=!g
		return tree_not(tn2);
	if (tn2==zero)
		return tn1;

	if (tn1==tn2)				//vf+!vf=f
		return tn1;
	if (tn1->var==tn2->var) {
		nv = tn1->var;
		nl = tree_and_not(tn1->left, tn2->left);	//nl=f0!g0
		nr = tree_and_not(tn1->right, tn2->right);	//nr=f1!g1
	} else {
		if (tn1->var>tn2->var ^ sign) {
			nv = tn1->var;							//g=vg+!vg
			nl = tree_and_not(tn1->left, tn2);		//nl=f0!g
			nr = tree_and_not(tn1->right, tn2);		//nr=f1!g
		}
		if (tn1->var<tn2->var ^ sign) {
			nv = tn2->var;							//f=vf+!vf
			nl = tree_and_not(tn1, tn2->left);		//nl=f!g0
			nr = tree_and_not(tn1, tn2->right);		//nr=f!g1
		}
	}
	ASSERT(nl!=NULL && nr!=NULL);
	if (nl==nr)									//vf+!vf=f
		return nl;
	return find_or_add(Robdd(nv, nl, nr));
}
/*
 * f =ite(v, f0, f1) = vf1 + !vf0
 * g =ite(v, g0, g1) = vg1 + !vg0
 * f | g = vf1 + !vf0 + vg1+!vg0 = ite(v, f0+g0, f1+g1)
 */
Robdd * Robdd::tree_or(Robdd * tn1, Robdd * tn2)
{
	Robdd * nl, *nr;
	int nv;

	ASSERT(tn1->var>0 && tn2->var>0);
	if (tn1==one || tn2==one)	//1+f=1
		return one;
	if (tn1==zero)				//0+g=g
		return tn2;
	if (tn2==zero)
		return tn1;

	if (tn1==tn2)				//vf+!vf=f
		return tn1;
	if (tn1->var==tn2->var) {
		nv = tn1->var;
		nl = tree_or(tn1->left, tn2->left);		//nl=f0+g0
		nr = tree_or(tn1->right, tn2->right);	//nr=f1+g1
	} else {
		if (tn1->var>tn2->var ^ sign) {
			nv = tn1->var;							//g=vg+!vg
			nl = tree_or(tn1->left, tn2);			//nl=f0+g
			nr = tree_or(tn1->right, tn2);			//nr=f1+g
		}
		if (tn1->var<tn2->var ^ sign) {
			nv = tn2->var;							//f=vf+!vf
			nl = tree_or(tn1, tn2->left);			//nl=f+g0
			nr = tree_or(tn1, tn2->right);			//nr=f+g1
		}
	}
	ASSERT(nl!=NULL && nr!=NULL);
	if (nl==nr)									//vf+!vf=f
		return nl;
	return find_or_add(Robdd(nv, nl, nr));
}

void Robdd::print(ostream& out)
{
	vector<VUI> r;

	r = get_logic();
	for (unsigned i=0; i<r.size(); i++) {
		for (unsigned j=0; j<r[i].size(); j+=2) {
			if (r[i][j]==1)
				cout<<r[i][j+1];
			else
				cout<<'-'<<r[i][j+1];
			if (j+2==r[i].size()) {
				if (i+1!=r.size())
					cout<<'+';
			} else
				cout<<'*';
		}
	}
	cout<<'\n';
}

void Robdd::compute_sop()
{
	unsigned i;

	if (s.state!=Sop::NOT_ASSIGN)
		return;

	left->compute_sop();
	right->compute_sop();

	ASSERT(var!=left->var);
	ASSERT(var!=right->var);

	s.state = Sop::ASSIGN;
	if (left!=one) {
		if (left!=zero)
			ASSERT(left->s.sum.size()>=1);
		for (i=0; i<left->s.sum.size(); i++) {
			VI product;
			product.clear();
			product.push_back(-var);
			product.insert(product.end(), left->s.sum[i].begin(), left->s.sum[i].end());
			s.sum.push_back(product);
		}
	} else {
		VI product;
		product.clear();
		product.push_back(-var);
		s.sum.push_back(product);
	}

	if (right!=one) {
		if (right!=zero)
			ASSERT(right->s.sum.size()>=1);
		for (i=0; i<right->s.sum.size(); i++) {
			VI product;
			product.clear();
			product.push_back(var);
			product.insert(product.end(), right->s.sum[i].begin(), right->s.sum[i].end());
			s.sum.push_back(product);
		}
	} else {
		VI product;
		product.clear();
		product.push_back(var);
		s.sum.push_back(product);
	}

	s.vars.push_back(var);
	if (sign)
		set_union(left->s.vars.begin(), left->s.vars.end(), right->s.vars.begin(), right->s.vars.end(), back_inserter(s.vars));
	else
		set_union(left->s.vars.begin(), left->s.vars.end(), right->s.vars.begin(), right->s.vars.end(), back_inserter(s.vars), greater<int>());
	s.check(sign);
}

bool Robdd::operator < (const Robdd & tn) const
{
	if (var!=tn.var)
		return (var<tn.var);
	if (left!=tn.left)
		return (left<tn.left);
	if (right!=tn.right)
		return (right<tn.right);
	return false;
}

/*
 * s.sum, s.vars, s.state are used as input
 */
Robdd * Robdd::sop_to_bdd(Sop & s)
{
	Sop ls, rs;
	bool finish;
	Robdd *lt, *rt;
	VI product;

	ASSERT(s.state!=Sop::NOT_ASSIGN);
	if (s.state==Sop::ZERO)
		return zero;
	if (s.state==Sop::ONE)
		return one;
	for (unsigned i=0; i<s.vars.size(); i++) {
		finish =false;
		ls.state = Sop::ZERO;
		rs.state = Sop::ZERO;
		ls.sum.clear();
		rs.sum.clear();
		for (unsigned j=0; j<s.sum.size(); j++)
			if (s.sum[j][0]== -s.vars[i]) {
				finish =true;
				if (ls.state ==Sop::ZERO)
					ls.state =Sop::ASSIGN;
				if (s.sum[j].size()==1) {
					ls.state =Sop::ONE;
					ls.sum.clear();
				}
				if (ls.state !=Sop::ONE) {
					product.clear();
					product.insert(product.end(), s.sum[j].begin()+1, s.sum[j].end());
					ls.sum.push_back(product);
				}
			} else
				if (s.sum[j][0]== s.vars[i]) {
					finish =true;
					if (rs.state ==Sop::ZERO)
						rs.state =Sop::ASSIGN;
					if (s.sum[j].size()==1) {
						rs.state =Sop::ONE;
						rs.sum.clear();
					}
					if (rs.state !=Sop::ONE) {
						product.clear();
						product.insert(product.end(), s.sum[j].begin()+1, s.sum[j].end());
						rs.sum.push_back(product);
					}
				} else {
					if (ls.state ==Sop::ZERO)
						ls.state =Sop::ASSIGN;
					if (ls.state !=Sop::ONE)
						ls.sum.push_back(s.sum[j]);
					if (rs.state ==Sop::ZERO)
						rs.state = Sop::ASSIGN;
					if (rs.state !=Sop::ONE)
						rs.sum.push_back(s.sum[j]);
				}
		if (!finish)
			continue;
		ls.vars.insert(ls.vars.end(), s.vars.begin()+i+1, s.vars.end());
		rs.vars =ls.vars;
		lt = sop_to_bdd(ls);
		rt = sop_to_bdd(rs);
		ASSERT(lt!=NULL && rt!=NULL);
		if (lt==rt)
			return lt;
		return find_or_add(Robdd(s.vars[i], lt, rt));
	}
	return NULL;
}

void Robdd::simplify(vector<Robdd *> bdd_node)
{
	unsigned i, j, k, l;
	bool finish=false;
	set <int, Runtime_less> var_in_set;
	vector <int> var_in_inc;
	vector <int> var_out;
	SimplifyTool tool;
	int row;

	for (i=0; i<bdd_node.size(); i++)
		bdd_node[i]->compute_sop();

	while (!finish) {
		finish = true;

		var_in_set.clear();
		var_out.clear();
		row =0;
		//Step 1: begin to select which logic add to this round's simply
		for (i=0; i<bdd_node.size(); i++) {
			if (bdd_node[i]->s.state==Sop::SIMPLIFIED || bdd_node[i]->s.state==Sop::ZERO || bdd_node[i]->s.state==Sop::ONE)
				continue;
			//check after add this logic if var_in overflow
			var_in_inc.clear();
			if (sign)
				set_difference(bdd_node[i]->s.vars.begin(), bdd_node[i]->s.vars.end(), var_in_set.begin(), var_in_set.end(), back_inserter(var_in_inc));
			else
				set_difference(bdd_node[i]->s.vars.begin(), bdd_node[i]->s.vars.end(), var_in_set.begin(), var_in_set.end(), back_inserter(var_in_inc), greater<int>());
			if (var_in_inc.size() + var_in_set.size() > SIMPLE_WIDE_IN)
				continue;

			finish = false;
			for (j=0; j<var_in_inc.size(); j++)
				var_in_set.insert(var_in_inc[j]);
			ASSERT(bdd_node[i]->s.sum.size()>0);
			var_out.push_back(i); //after add this logic, var_in not overflow, select bdd_node[i] for simplify
			bdd_node[i]->s.state = Sop::SIMPLIFIED;
			row += bdd_node[i]->s.sum.size();
			if (row >=SIMPLE_ROW_MAX || var_out.size()>= SIMPLE_WIDE_OUT)
				break;

		}
		//end step1
		if (!finish) {
			vector<int> var_in;
			ostringstream comment;
			var_in.clear();
			copy(var_in_set.begin(), var_in_set.end(), back_inserter(var_in));
			tool.open(var_in.size(), var_out.size());
			comment<<"in:";
			for (i=0; i<var_in.size(); i++)
				comment<<var_in[i]<<' ';
			tool.insert_comment(comment.str());
			comment.clear();
			comment<<"out:";
			for (i=0; i<var_out.size(); i++)
				comment<<var_out[i]<<' ';
			tool.insert_comment(comment.str());
			VI vec_in(var_in.size()), vec_out(var_out.size());
			//Step2: begin to write original vector
			for (i=0; i<var_out.size(); i++) {
				Robdd * logic;
				logic = bdd_node[var_out[i]];
				fill(vec_out.begin(), vec_out.end(), 0);
				vec_out[i] = 1;
				/*
				 * if   var_in is {1, 2, 3, 5, 7}, s.sum[j] is {-2, 3, 7}
				 * then vec_in is {2, 0, 1, 2, 1}
				 * var_out is {1, 3, 5, 7}
				 * vec_out is {1, 0, 0, 0}, {0, 1, 0, 0}
				 */
				for (j=0; j< logic->s.sum.size(); j++) {
					for (k=0, l=0; k<var_in.size(); k++) {
						if (abs(logic->s.sum[j][l]) == var_in[k] && l<logic->s.sum[j].size()) {
							if (logic->s.sum[j][l]>0)
								vec_in[k] =1;
							else
								vec_in[k] =0;
							l++;
						} else
							vec_in[k] = 2;
					}
					tool.write(vec_in, vec_out);
					row--;
				}
				logic->s.sum.clear();
			}
			//end step2
			ASSERT(row==0);
			tool.simply();
			//Step3: begin to read simplify vector
			while (tool.read(vec_in, vec_out)) {
				for (i=0; i<vec_out.size(); i++) {
					VI product;
					if (vec_out[i]!=1)
						continue;
					Robdd * logic;
					logic = bdd_node[var_out[i]];
					product.clear();
					for (j=0; j<vec_in.size(); j++) {
						if (vec_in[j]==1) {
							product.push_back(var_in[j]);
						}
						if (vec_in[j]==0) {
							product.push_back(-var_in[j]);
						}
					}
					logic->s.sum.push_back(product);
				}
			}
			//end Step3
			tool.close();
		}
	}
}

bool Robdd::check_product_always1(VI p, unsigned i)
{
	if (this==zero)
		return false;
	if (this==one)
		return true;
	ASSERT(i<p.size());

	if (var==abs(p[i])) {
		if (p[i]>0)
			return right->check_product_always1(p, i+1); //check v
		else
			return left->check_product_always1(p, i+1);  //check !v
	}
	if (var<abs(p[i]) ^ sign)
		return check_product_always1(p,i+1);
	//now var>abs(p[i]), check for both v and !v
	return left->check_product_always1(p, i) && right->check_product_always1(p, i);
}

bool Robdd::check_product_always0(VI p, unsigned i)
{
	if (this==zero)
		return true;
	if (this==one)
		return false;
	ASSERT(i<p.size());
	if (var==abs(p[i])) {
		if (p[i]>0)
			return right->check_product_always0(p, i+1); //check v
		else
			return left->check_product_always0(p, i+1);  //check !v
	}
	if (var<abs(p[i]) ^ sign)
		return check_product_always0(p,i+1);
	//now var>abs(p[i]), check for both v and !v
		return left->check_product_always0(p, i) && right->check_product_always0(p, i);
}

void Robdd::check()
{

	if (s.state==Sop::NOT_ASSIGN)
		return;
	/*
	for (unsigned i=0; i<s.sum.size(); i++)
		ASSERT(check_product_always1(s.sum[i],0));
	*/
	ASSERT(this==sop_to_bdd(s));
}

vector<VUI> Robdd::get_logic()
{
	vector<VUI> ret;
	VUI product;

	ASSERT(s.state!=Sop::NOT_ASSIGN);
	for (unsigned i=0; i<s.sum.size(); i++) {
		product.clear();
		for (unsigned j=0; j<s.sum[i].size(); j++) {
			if (s.sum[i][j]>0) {
				product.push_back(1);
				product.push_back(tags[s.sum[i][j]-1]);
			} else {
				product.push_back(0);
				product.push_back(tags[-s.sum[i][j]-1]);
			}
		}
		ret.push_back(product);
	}
	return ret;
}

void Robdd::self_test()
{
	Robdd *v1, *v2, *v3, *v4, *v5;
	Robdd * e0, *e1, *e2, *e3;
	vector<Robdd*> ve;
	init();
	v1=leaf_var(1);
	v2=leaf_var(2);
	v3=leaf_var(3);
	v4=leaf_var(4);
	v5=leaf_var(5);
	e0=tree_and_not(v5, v1); //e0=v5!v1
	e1=tree_or(e0, v3); //e1 =v5!v1+v3
	e2=tree_and(e1, v2); //e2 =!v1v2v5+v2v3
	e0=tree_and_not(v1, v3); //e0=v1!v3
	e1=tree_and_not(v2, v4); //e1=v2!v4
	e3=tree_or(e0, e1);  //e3 =v1!v3+v2!v4
	e2=tree_and(e2, e3); //e2 =!v1v2!v4v5+v5!v1v2!v4+v2v3!v4
	e2->compute_sop();
	e2->s.print(cout);
	e1 = tree_not(e2);
	e1->compute_sop();
	e1->s.print(cout);
	cout<<node_set.size()<<'\n';
	e3->compute_sop();
	e3->s.print(cout);
	cout<<node_set.size()<<'\n';
	e2->check();
	e3->check();
	cout<<node_set.size()<<'\n';
	cout<<"optimize\n";
	ve.push_back(e0);
	ve.push_back(e1);
	ve.push_back(e2);
	ve.push_back(e3);
	simplify(ve);
	e1->print(cout);
	e2->print(cout);
	e3->print(cout);
	e1->check();
	e2->check();
	e3->check();
	cout<<"check successful";
}

void Robdd::self_test1()
{
#define TEST_LOOP 25000
#define TEST_DEEP 75
#define TEST_VAR  17
	Robdd *v[TEST_VAR];
	Robdd *e[TEST_VAR];
	vector<Robdd*> ve;
	bool a[TEST_VAR];
	int i, j, command, e0, e1;
	VI all1;

	init();
	for (i=0; i<TEST_VAR; i++) {
		v[i] = leaf_var(i+1);
		if (sign)
			all1.push_back(i+1);
		else
			all1.push_back(TEST_VAR-i);
	}

	srand(1);

	for (j=0; j<TEST_LOOP; j++) {
		for (i=0; i<TEST_VAR; i++) {
			e[i] = v[i];
			a[i] = 1;
		}
		for (i=0; i<TEST_DEEP; i++) {
			command =rand() %4;
			e0 =rand() % TEST_VAR;
			e1 =rand() % TEST_VAR;
			switch (command) {
			case 0:
				e[e0] = tree_and(e[e0], e[e1]);
				a[e0] = a[e0] & a[e1];
				break;
			case 1:
				e[e0] = tree_and_not(e[e0], e[e1]);
				a[e0] = a[e0] & !a[e1];
				break;
			case 2:
				e[e0] = tree_or(e[e0], e[e1]);
				a[e0] = a[e0] | a[e1];
				break;
			case 3:
				e[e0] = tree_not(e[e0]);
				a[e0] = !a[e0];
				break;
			}
		}
		for (i=0; i<TEST_VAR; i++) {
			if (a[i])
				e[i]->check_product_always1(all1, 0);
			else
				e[i]->check_product_always0(all1, 0);
			e[i]->check();
		}
		ve.clear();
		for (i=0; i<TEST_VAR; i++)
			ve.push_back(e[i]);

		simplify(ve);

		for (i=0; i<TEST_VAR; i++)
			e[i]->check();
	}
	cout<<"test success\n";
}
