#ifndef LOG_LIB
#define LOG_LIB

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>
#include <unistd.h>

#include "colourfulPrintLib/colourfullPrint.hpp"


// level of logging can be set, log is happening only if log level is >= that setted
// level of logging

/*

ENUM vals should be only in this order
These levels of logging are sorted by how "dangerous" they are.
So DEBUG is not problem at all and ERROR is very serious.

*/

enum Levels {
    DEBUG   = 0,
    INFO    = 1,
    WARNING = 2,
    ERROR   = 3,
};

const char* getLogMessage(Levels level);

Colors getTextColorForLevel(Levels level);

void setLoggingLevel(Levels level);

Levels getLoggingLevel();

const char* getCurrentTimeFormatted();

const char* getLoggingMessage(Levels level, const char* fileName, const char* funcName, int line);

void stateLogFile(const char* logFileName);

FILE* getLogFile();

void destructLogger();

#define LOG_MESSAGE(level, ...)                                                                     \
    do {                                                                                            \
        assert(DEBUG < INFO && INFO < WARNING && WARNING < ERROR);                                  \
        if (level >= getLoggingLevel()) {                                                           \
            changeTextColor(getTextColorForLevel(level));                                           \
            FILE* logFile = getLogFile();                                                           \
            bool isTransferToFile = !isatty(STDOUT_FILENO);                                         \
            FILE* stream = (logFile == NULL || isTransferToFile) ? stderr : logFile;                  \
            printf("is transfer : %d\n", isTransferToFile);                    \
                                                                                                    \
            if (isTransferToFile || logFile != NULL) {                                        \
                fprintf(stream, "%s", getLoggingMessage(level, __FILE__, __FUNCTION__, __LINE__));  \
                fprintf(stream, __VA_ARGS__);                                                       \
                printf("file %d\n", stream == logFile);                                             \
            } else {                                                                                \
                colourfullPrintToStream(stderr, "%s",                                               \
                getLoggingMessage(level, __FILE__, __FUNCTION__, __LINE__));                        \
                colourfullPrintToStream(stderr, __VA_ARGS__);                                       \
            }                                                                                       \
        }                                                                                           \
    } while (0);

#define LOG_DEBUG(...) LOG_MESSAGE(DEBUG, __VA_ARGS__);

#define LOG_INFO(...) LOG_MESSAGE(INFO, __VA_ARGS__);

#define LOG_WARNING(...) LOG_MESSAGE(WARNING, __VA_ARGS__);

#define LOG_ERROR(...) LOG_MESSAGE(ERROR, __VA_ARGS__);

#endif
