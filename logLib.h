#ifndef LOG_LIB
#define LOG_LIB

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>
#include <unistd.h>
#include <stdbool.h>

#include "debugMacros.h"
#include "colourfulPrintLib/colourfullPrint.h"


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

const char* getLogMessage(enum Levels level);

enum Colors getTextColorForLevel(enum Levels level);

bool isGoodLogLevel(enum Levels level, int no_debug, int no_info, int no_warning, int no_error);

void setLoggingLevel(enum Levels level);

enum Levels getLoggingLevel();

const char* getCurrentTimeFormatted();

const char* getLoggingMessage(enum Levels level, const char* fileName, const char* funcName, int line);

void stateLogFile(const char* logFileName);

FILE* getLogFile();

void destructLogger();

#ifdef NO_LOG_DEBUG
#define NO_DEBUG 1
#else
#define NO_DEBUG 0
#endif

#ifdef NO_LOG_INFO
#define NO_INFO 1
#else
#define NO_INFO 0
#endif

#ifdef NO_LOG_WARNING
#define NO_WARNING 1
#else
#define NO_WARNING 0
#endif

#ifdef NO_LOG_ERROR
#define NO_ERROR 1
#else
#define NO_ERROR 0
#endif





#define DEBUG(...)                                                                              \
do {                                                                                            \
    assert(DEBUG < INFO && INFO < WARNING && WARNING < ERROR);                                  \
    if (getLoggingLevel() == DEBUG && !NO_DEBUG) {                                              \
        printf("no info: %d\n", NO_INFO);                                               \
        changeTextColor(getTextColorForLevel(DEBUG));                                           \
        FILE* logFile = getLogFile();                                                           \
        bool isTransferToFile = !isatty(STDOUT_FILENO);                                         \
        FILE* stream = (logFile == NULL || isTransferToFile) ? stderr : logFile;                \
                                                                                                \
        const char* logMessage = getLoggingMessage(DEBUG, __FILE__, __FUNCTION__, __LINE__);    \
        if (isTransferToFile || logFile != NULL) {                                              \
            fprintf(stream, "%s", logMessage);                                                  \
            DBG_TO_STREAM(stream, __VA_ARGS__);                                                 \
        } else {                                                                                \
            colourfullPrintToStream(stream, "%s", logMessage);                                  \
            colourfullDebugToStream(stream, __VA_ARGS__);                                       \
        }                                                                                       \
    }                                                                                           \
} while (0)

#define LOG_MESSAGE(level, ...)                                                                     \
    do {                                                                                            \
        assert(DEBUG < INFO && INFO < WARNING && WARNING < ERROR);                                  \
        if (isGoodLogLevel(level, NO_DEBUG, NO_INFO, NO_WARNING, NO_ERROR)) {                                                           \
            changeTextColor(getTextColorForLevel(level));                                           \
            FILE* logFile = getLogFile();                                                           \
            bool isTransferToFile = !isatty(STDOUT_FILENO);                                         \
            FILE* stream = (logFile == NULL || isTransferToFile) ? stderr : logFile;                \
                                                                                                    \
            const char* logMessage = getLoggingMessage(level, __FILE__, __FUNCTION__, __LINE__);    \
            if (isTransferToFile || logFile != NULL) {                                              \
                fprintf(stream, "%s", logMessage);                                                  \
                fprintf(stream, __VA_ARGS__);                                                       \
            } else {                                                                                \
                colourfullPrintToStream(stream, "%s", logMessage);                                  \
                colourfullPrintToStream(stream, __VA_ARGS__);                                       \
            }                                                                                       \
        }                                                                                           \
    } while (0);

#define LOG_DEBUG(...) LOG_MESSAGE(DEBUG, __VA_ARGS__);

#define LOG_INFO(...) LOG_MESSAGE(INFO, __VA_ARGS__);

#define LOG_WARNING(...) LOG_MESSAGE(WARNING, __VA_ARGS__);

#define LOG_ERROR(...) LOG_MESSAGE(ERROR, __VA_ARGS__);

#endif
