#ifndef DEBUG_MACROS_LIB
#define DEBUG_MACROS_LIB

enum DataTypes {
    CHAR_TYPE,
    CHAR_PTR_TYPE,
    CONST_CHAR_PTR_TYPE,
    INT_TYPE, INT_PTR_TYPE,
    FLOAT_TYPE,
    DOUBLE_TYPE,
    LONG_DOUBLE_TYPE,
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

#define _fe_0(_stream, _call, x, ...)
#define _fe_1(_stream, _call, x, ...) _call(_stream, x)
#define _fe_2(_stream, _call, x, ...) _call(_stream, x) _fe_1(_stream, _call, __VA_ARGS__)
#define _fe_3(_stream, _call, x, ...) _call(_stream, x) _fe_2(_stream, _call, __VA_ARGS__)
#define _fe_3(_stream, _call, x, ...) _call(_stream, x) _fe_2(_stream, _call, __VA_ARGS__)
#define _fe_4(_stream, _call, x, ...) _call(_stream, x) _fe_3(_stream, _call, __VA_ARGS__)
#define _fe_5(_stream, _call, x, ...) _call(_stream, x) _fe_4(_stream, _call, __VA_ARGS__)

#define OUTPUT_VARIABLE_TO_STREAM(stream, x)                                    \
    do {                                                                        \
        fprintf(stream, "[%s : ", #x);                                          \
        enum DataTypes type = typename(x);                                      \
        const char* format = "";                                                \
        switch (type) {                                                         \
            case CHAR_TYPE:             format = "%c";      break;              \
            case CHAR_PTR_TYPE:                                                 \
            case CONST_CHAR_PTR_TYPE:   format = "%s";      break;              \
            case INT_TYPE:                                                      \
            case BOOL_TYPE:             format = "%d";      break;              \
            case FLOAT_TYPE:                                                    \
            case DOUBLE_TYPE:           format = "%g";      break;              \
            case LONG_DOUBLE_TYPE:      format = "%Lg";     break;              \
            default:                    format = "?";       break;              \
        };                                                                      \
        fprintf(stream, format, x);                                             \
        fprintf(stream, "] ");                                                  \
    } while (0);



#define _GET_NTH_ARG(_1, _2, _3, _4, _5, _6, N, ...) N

#define DBG_TO_STREAM(stream, ...)                                              \
    do {                                                                        \
        _GET_NTH_ARG("ignored", ##__VA_ARGS__, _fe_5, _fe_4,                    \
            _fe_3, _fe_2, _fe_1, _fe_0)                                         \
        (stream, OUTPUT_VARIABLE_TO_STREAM, ##__VA_ARGS__);                     \
        fprintf(stream, "\n");                                                  \
    } while (0)

#define DBG(...) DBG_TO_STREAM(stderr, __VA_ARGS__)


#endif
