#include <stdio.h>
#include <stdbool.h>

#define NO_LOG_INFO

//#include "logLib.h"
//#include "colourfulPrintLib/colourfullPrint.h"

#define _GET_NTH_ARG(_1, _2, _3, _4, _5, _6, N, ...) N

//#define CNT_OF_ARGS(...) _GET_NTH_ARG("ignored", ##__VA_ARGS__, 5, 4, 3, 2, 1, 0)

#define _fe_0(_call, x, ...)

#define _fe_1(_call, x, ...) _call(x)

#define _fe_2(_call, x, ...) _call(x) _fe_1(_call, __VA_ARGS__)

#define _fe_3(_call, x, ...) _call(x) _fe_2(_call, __VA_ARGS__)

#define _fe_3(_call, x, ...) _call(x) _fe_2(_call, __VA_ARGS__)

#define _fe_4(_call, x, ...) _call(x) _fe_3(_call, __VA_ARGS__)

#define _fe_5(_call, x, ...) _call(x) _fe_4(_call, __VA_ARGS__)



enum TYPES {
    CHAR_TYPE, CHAR_PTR_TYPE, CONST_CHAR_PTR_TYPE,
    INT_TYPE, INT_PTR_TYPE,
    FLOAT_TYPE, DOUBLE_TYPE, LONG_DOUBLE_TYPE,
    BOOL_TYPE,
    VOID_PTR_TYPE,
    UNKNOWN_TYPE,
};

/*

long int: "long int",           unsigned long int: "unsigned long int",      \
long long int: "long long int", unsigned long long int: "unsigned long long int", \
unsigned int: "unsigned int",           \
short int: "short int",         unsigned short int: "unsigned short int",     \
signed char: "signed char",            \

*/

#define typename(x) _Generic((x),                                               \
             char: CHAR_TYPE,                        int: INT_TYPE,             \
            float: FLOAT_TYPE,                    double: DOUBLE_TYPE,          \
      long double: LONG_DOUBLE_TYPE,              char *: CHAR_PTR_TYPE,        \
      const char*: CONST_CHAR_PTR_TYPE,             bool: BOOL_TYPE,            \
           void *: VOID_PTR_TYPE,                  int *: INT_PTR_TYPE,         \
          default: UNKNOWN_TYPE)

#define DO_BRUH(x)                           \
do {                                         \
    printf("[%s : ", #x);                    \
    enum TYPES type = typename(x);           \
    switch (type) {                          \
        case CHAR_TYPE:                      \
            printf("%c", x);                 \
            break;                           \
        case CHAR_PTR_TYPE:                  \
            printf("%s", x);                 \
            break;                           \
        case CONST_CHAR_PTR_TYPE:            \
            printf("%s", x);                 \
            break;                           \
        case INT_TYPE: case BOOL_TYPE:  \
            printf("%d", x);                 \
            break;                           \
        case FLOAT_TYPE:                          \
            printf("%g", x);                 \
            break;                           \
        case DOUBLE_TYPE:                    \
            printf("%g", x);                 \
            break;                           \
        case LONG_DOUBLE_TYPE:               \
            printf("%Lg", x);                \
            break;                           \
        default:                             \
            printf("?");                     \
            break;                           \
    };                                       \
    printf("] ");                            \
} while (0);

#define DBG(...) _GET_NTH_ARG("ignored", ##__VA_ARGS__, _fe_5, _fe_4, _fe_3, _fe_2, _fe_1, _fe_0)(DO_BRUH, ##__VA_ARGS__);

int main() {
    const char* constCharPtrVar = "fdaslkfjd";
    int intVar = 10;
    bool boolVar = true;
    long double longDoubleVar = 3.141592;
    DBG(intVar, boolVar, longDoubleVar, constCharPtrVar);
    printf("\n");

    // int cnt = CNT_OF_ARGS(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    // printf("cnt : %d\n", cnt);




//     setLoggingLevel(DEBUG);
//     //stateLogFile("logFile.txt");
//
//     enum Levels lo = DEBUG;
//
//     int a = 5, b = 8, c = 13;
//     const char* x = "fdsa";
//     DBG(a, b, c, x);
//
//     LOG_DEBUG("i am log debug\n");
//     LOG_INFO("i am log info\n");
//     LOG_WARNING("i am log warn\n");
//     LOG_ERROR("i am log error\n");
//
//     destructLogger();
	return 0;
}
