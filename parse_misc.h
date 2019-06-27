/*
 * parse_misc.h
 *
 *  Created on: Sep 15, 2012
 *      Author: yuchen
 */

#ifndef PARSE_MISC_H_
#define PARSE_MISC_H_

#define YYLTYPE YYLTYPE
typedef struct {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
    int begin_pos;
    int end_pos;
} YYLTYPE;
#endif /* PARSE_MISC_H_ */
