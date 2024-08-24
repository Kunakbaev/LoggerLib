#define _GET_NTH_ARG(_1, _2, _3, _4, _5, _6, N, ...) N

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

#define OUTPUT_VARIABLE(x)                       \
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
            case INT_TYPE: case BOOL_TYPE:       \
                printf("%d", x);                 \
                break;                           \
            case FLOAT_TYPE:                     \
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

#define DBG(...)                                                                            \
    do {                                                                                    \
        _GET_NTH_ARG("ignored", ##__VA_ARGS__, _fe_5, _fe_4, _fe_3, _fe_2, _fe_1, _fe_0)    \
        (OUTPUT_VARIABLE, ##__VA_ARGS__);                                                   \
        printf("\n");                                                                       \
    } while (0)









// ---------------------------------        SAME MACROS BUT FOR THE STREAM (FILE, STDERR, STDOUT)       ------------------------------------------

#define _fe_0_stream(_stream, _call, x, ...)
#define _fe_1_stream(_stream, _call, x, ...) _call(_stream, x)
#define _fe_2_stream(_stream, _call, x, ...) _call(_stream, x) _fe_1_stream(_stream, _call, __VA_ARGS__)
#define _fe_3_stream(_stream, _call, x, ...) _call(_stream, x) _fe_2_stream(_stream, _call, __VA_ARGS__)
#define _fe_3_stream(_stream, _call, x, ...) _call(_stream, x) _fe_2_stream(_stream, _call, __VA_ARGS__)
#define _fe_4_stream(_stream, _call, x, ...) _call(_stream, x) _fe_3_stream(_stream, _call, __VA_ARGS__)
#define _fe_5_stream(_stream, _call, x, ...) _call(_stream, x) _fe_4_stream(_stream, _call, __VA_ARGS__)

#define OUTPUT_VARIABLE_TO_STREAM(stream, x)          \
    do {                                                  \
        fprintf(stream, "[%s : ", #x);                    \
        enum TYPES type = typename(x);                    \
        switch (type) {                                   \
            case CHAR_TYPE:                               \
                fprintf(stream, "%c", x);                 \
                break;                                    \
            case CHAR_PTR_TYPE:                           \
                fprintf(stream, "%s", x);                 \
                break;                                    \
            case CONST_CHAR_PTR_TYPE:                     \
                fprintf(stream, "%s", x);                 \
                break;                                    \
            case INT_TYPE: case BOOL_TYPE:                \
                fprintf(stream, "%d", x);                 \
                break;                                    \
            case FLOAT_TYPE:                              \
                fprintf(stream, "%g", x);                 \
                break;                                    \
            case DOUBLE_TYPE:                             \
                fprintf(stream, "%g", x);                 \
                break;                                    \
            case LONG_DOUBLE_TYPE:                        \
                fprintf(stream, "%Lg", x);                \
                break;                                    \
            default:                                      \
                fprintf(stream, "?");                     \
                break;                                    \
        };                                                \
        fprintf(stream, "] ");                            \
    } while (0);

#define DBG_TO_STREAM(stream, ...)                                                          \
    do {                                                                                    \
        _GET_NTH_ARG("ignored", ##__VA_ARGS__, _fe_5_stream, _fe_4_stream,                  \
            _fe_3_stream, _fe_2_stream, _fe_1_stream, _fe_0_stream)                         \
        (stream, OUTPUT_VARIABLE_TO_STREAM, ##__VA_ARGS__);                                 \
        fprintf(stream, "\n");                                                              \
    } while (0)
