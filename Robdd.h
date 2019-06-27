/*
 * Robdd.h
 *
 *  Created on: Oct 16, 2012
 *      Author: yuchen
 */

#ifndef ROBDD_H_
#define ROBDD_H_

#include "public.h"
#include <set>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<unsigned> VUI;
class Sop {
public:
	typedef enum {
		NOT_ASSIGN=0,
		ASSIGN,
		SIMPLIFIED,
		ZERO,
		ONE
	} SopState;
protected:
	SopState state;
	vector<VI> sum;
	VI vars;
public:
	friend class Robdd;
	void print(ostream& out);
	void check(bool sign);
	Sop();
	virtual ~Sop();
};

class Robdd {
protected:
	Robdd * left;
	Robdd *right;
	int var;
	Sop s;
	static set <Robdd> node_set;  //Contain all Robdd nodes
	static vector<unsigned> tags; //map between var and state or expression's pointer
	static Robdd * find_or_add(const Robdd & tn);
	//if sign=true, abs(s.sum[i][j])>abs(s.sum[i][j-1])
	struct Runtime_less {
		bool operator() (int v1, int v2) {
			return (v1>v2) ^ sign;
		}
	};
public:
	static bool sign; //if sign=true, root var is small, leaf var is big,
	static Robdd *zero, *one;
	Robdd();
	Robdd(int v, Robdd* l, Robdd *r);
	virtual ~Robdd();
	static void init();
	static void self_test();
	static void self_test1();
	static Robdd * leaf_var(unsigned long long tag);
	static Robdd * leaf_var_not(unsigned long long tag);
	static Robdd * tree_not(Robdd *tn);
	static Robdd * tree_and(Robdd * tn1, Robdd * tn2);
	static Robdd * tree_and_not(Robdd * tn1, Robdd * tn2);
	static Robdd * tree_or(Robdd * tn1, Robdd * tn2);
	static Robdd * sop_to_bdd(Sop & s);
	static void simplify(vector<Robdd *> bdd_node);
	bool check_product_always1(VI p, unsigned i);
	bool check_product_always0(VI p, unsigned i);
	void check();
	void print(ostream& out);
	void compute_sop();
	vector<VUI> get_logic();
	bool operator < (const Robdd & tn) const;
};

#endif /* ROBDD_H_ */
