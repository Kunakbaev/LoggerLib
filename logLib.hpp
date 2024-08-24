#ifndef LOG_LIB
#define LOG_LIB

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "colourfulPrintLib/colourfullPrint.hpp"


// level of logging can be set, log is happening only if log level is >= that setted
// level of logging

enum Levels {
    DEBUG   = 0,
    INFO    = 1,
    WARNING = 2,
    ERROR   = 3,
};

const char* getLogMessage(Levels level);

Colors getTextColorForLevel(Levels level);

void setLoggingLevel();

Levels getLoggingLevel();

const char* getCurrentTimeFormatted();

const char* getLoggingMessage(Levels level, const char* fileName, const char* funcName, int line);

#define LOG_MESSAGE(level, ...)                                \
    do {                                                                    \
        changeTextColor(getTextColorForLevel(level));                           \
        printf("is : %d\n", X); \
        if (isatty(STDOUT_FILENO)) {                    \
            colourfullPrintToStream(stderr, "%s",             \
            getLoggingMessage(level, __FILE__, __FUNCTION__, __LINE__));        \
            colourfullPrintToStream(stderr, __VA_ARGS__); \
        } else { \
            fprintf(stderr, "%s", getLoggingMessage(level, __FILE__, __FUNCTION__, __LINE__));        \
            fprintf(stderr, __VA_ARGS__); \
        } \
    } while (0);

#define LOG_DEBUG(...) LOG_MESSAGE(DEBUG, __VA_ARGS__);

#define LOG_INFO(...) LOG_MESSAGE(INFO, __VA_ARGS__);

#define LOG_WARNING(...) LOG_MESSAGE(WARNING, __VA_ARGS__);

#define LOG_ERROR(...) LOG_MESSAGE(ERROR, __VA_ARGS__);

#endif
