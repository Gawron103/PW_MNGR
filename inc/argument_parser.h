#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include "types.h"

typedef bool bParseStatus_t;

bParseStatus_t bParseArgs(const uint8_t u8FlagsCount, char** cFlags, stRequest_T** stOutRequest);

/* TMP FUNC */
void printRequest(stRequest_T* stRequest);
// eOperation_T getOperation(const char cOperation);
// bool validate_input(const size_t uiFlagsCount, char **cFlags);

#endif /* ARGUMENT_PARSER_H */


/*
GET CREDENTIALS
./manager -c google.pl
index: 0	flag: ./manager
index: 1	flag: -c
index: 2	flag: google.pl
*/

/*
GET LOGIN
./manager -l google.pl
index: 0	flag: ./manager
index: 1	flag: -l
index: 2	flag: google.pl
*/

/*
GET PW
./manager -p google.pl
index: 0	flag: ./manager
index: 1	flag: -pw
index: 2	flag: google.pl
*/

/*
GET SIZE
./manager -s
index: 0	flag: ./manager
index: 1	flag: -s
*/

/*
ADD CREDENTIALS
./manager -n pjoter pjoterpw google.pl
index: 0	flag: ./manager
index: 1	flag: -a
index: 2	flag: google.pl
index: 3	flag: pjoter
index: 4	flag: pjoterpw
*/

/*
GET ALL
./manager -a
index: 0	flag: ./manager
index: 1	flag: -a
*/

/*
minimum args -> 2
maximum args -> 5
*/
