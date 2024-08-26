#ifndef DEBUG_MACROS_LIB
#define DEBUG_MACROS_LIB

#include "hiddenCringe.hpp"

// enum DataTypes {
//     CHAR_TYPE,
//     CHAR_PTR_TYPE,
//     CONST_CHAR_PTR_TYPE,
//     INT_TYPE, INT_PTR_TYPE,
//     FLOAT_TYPE,
//     DOUBLE_TYPE,
//     LONG_DOUBLE_TYPE,
//     BOOL_TYPE,
//     VOID_PTR_TYPE,
//     UNKNOWN_TYPE,
// };

const char* varToFormat(char);
const char* varToFormat(void*);
const char* varToFormat(bool);
const char* varToFormat(char*);
const char* varToFormat(const char*);
const char* varToFormat(int);

/*

const char* format = varToFormat(x);                                    \
        fprintf(stream, format, x);                                             \

*/

#define OUTPUT_VARIABLE_TO_STREAM(stream, x)                                    \
    do {                                                                        \
        fprintf(stream, "[%s : ", #x);                                          \
        const char* format = varToFormat(x);                                    \
        fprintf(stream, format, x);                                             \
        fprintf(stream, "] ");                                                  \
    } while (0);


#define DBG_TO_STREAM(stream, ...)                                              \
    do {                                                                        \
        _GET_NTH_ARG("ignored", ##__VA_ARGS__, _fe_5, _fe_4,                    \
            _fe_3, _fe_2, _fe_1, _fe_0)                                         \
        (stream, OUTPUT_VARIABLE_TO_STREAM, ##__VA_ARGS__);                     \
        fprintf(stream, "\n");                                                  \
    } while (0)

#define DBG(...) DBG_TO_STREAM(stderr, __VA_ARGS__)


#endif
