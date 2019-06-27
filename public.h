/*
 * public.h
 *
 *  Created on: May 29, 2011
 *      Author: yuchen
 */

#ifndef PUBLIC_H_
#define PUBLIC_H_


#include <iostream>
#include <string>
#include <sstream>
#define MY_DBG

#ifndef ASSERT
#ifdef MY_DBG
#define ASSERT(x) do {if (!(x)) {cerr<<"wrong at "<<__FILE__<<' '<<__LINE__; while(1);}} while(0)
#else
#define ASSERT(x) do {if (!(x)) {std::ostringstream s; s<<"wrong at "<<__FILE__<<' '<<__LINE__; throw MyException(s.str()); }} while(0)
#endif
#endif


class MyException : public std::exception {
	std::string s;
public:
	MyException(std::string ss) : s(ss) {}
	virtual ~MyException() throw() {}
	virtual const char* what() const throw() { return s.c_str(); }
};

#endif /* PUBLIC_H_ */
