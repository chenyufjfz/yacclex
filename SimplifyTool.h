/*
 * SimplifyTool.h
 *
 *  Created on: Oct 24, 2012
 *      Author: yuchen
 */

#ifndef SIMPLIFYTOOL_H_
#define SIMPLIFYTOOL_H_

#include "public.h"
#include <vector>
#include <stdio.h>
using namespace std;

class SimplifyTool {
protected:
	int in_num, out_num, simple_loop;
	FILE * org_vec_file, * opt_vec_file;
public:
	void open(int var_in_num, int var_out_num);
	void write(const vector <int> & vec_in, const vector <int> & vec_out);
	void insert_comment(string comment);
	bool read(vector <int> & vec_in, vector <int> & vec_out);
	void simply();
	void close();
	SimplifyTool();
	virtual ~SimplifyTool();
};

#endif /* SIMPLIFYTOOL_H_ */
