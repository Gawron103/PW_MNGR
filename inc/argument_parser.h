#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include "types.h"

/**
 * @brief Type for checking parse status
 * 
 */
typedef uint8_t bParseStatus_t;

bParseStatus_t bParseArgs(const uint8_t u8FlagsCount, char** cFlags, stRequest_T** stOutRequest);

#endif /* ARGUMENT_PARSER_H */
