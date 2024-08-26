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

#include "debugMacros.hpp"
#include "colourfullPrint.hpp"


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

void setLoggingLevel(enum Levels level);

enum Levels getLoggingLevel();

const char* getCurrentTimeFormatted();

const char* getLoggingMessage(enum Levels level, const char* fileName, const char* funcName, int line);

void stateLogFile(const char* logFileName);

FILE* getLogFile();

void destructLogger();

// #define DO_STUFF(isDebug, level, ...)                                                               \
// do {                                                                                                \
//     changeTextColor(getTextColorForLevel(level));                                                   \
//     FILE* logFile = getLogFile();                                                                   \
//     bool isTransferToFile = !isatty(STDOUT_FILENO);                                                 \
//     FILE* stream = (logFile == NULL || isTransferToFile) ? stderr : logFile;                        \
//                                                                                                     \
//     const char* logMessage = getLoggingMessage(level, __FILE__, __FUNCTION__, __LINE__);            \
//     if (isTransferToFile || logFile != NULL) {                                                      \
//         fprintf(stream, "%s", logMessage);                                                          \
//         printf("biba %d\n", level);\
//         if (isDebug)                                                                                \
//             DBG_TO_STREAM(stream, __VA_ARGS__);                                                     \
//         else                                                                                        \
//             fprintf(stream, __VA_ARGS__);                                                           \
//     } else {                                                                                        \
//         colourfullPrintToStream(stream, "%s", logMessage);                                          \
//         printf("biba %d\n", level);\
//         if (isDebug)                                                                                \
//             colourfullDebugToStream(stream, __VA_ARGS__);                                           \
//         else                                                                                        \
//             colourfullPrintToStream(stream, __VA_ARGS__);                                           \
//     }                                                                                               \
// } while (0)




#ifndef NO_LOG

    #define LOG_MESSAGE(level, ...)                                                                 \
        do {                                                                                        \
            assert(DEBUG < INFO && INFO < WARNING && WARNING < ERROR);                              \
            if (level >= getLoggingLevel()) {                                                        \
                changeTextColor(getTextColorForLevel(level));                                                   \
                FILE* logFile = getLogFile();                                                                   \
                bool isTransferToFile = !isatty(STDOUT_FILENO);                                                 \
                FILE* stream = (logFile == NULL || isTransferToFile) ? stderr : logFile;                        \
                                                                                                                \
                const char* logMessage = getLoggingMessage(level, __FILE__, __FUNCTION__, __LINE__);            \
                if (isTransferToFile || logFile != NULL) {                                                      \
                    fprintf(stream, "%s", logMessage);                                                          \
                    fprintf(stream, __VA_ARGS__);                                                           \
                } else {                                                                                        \
                    colourfullPrintToStream(stream, "%s", logMessage);                                          \
                    colourfullPrintToStream(stream, __VA_ARGS__);                                           \
                }                                                                                               \
            } \
        } while (0)

    #define DEBUG_(...)                                                                 \
        do {                                                                                        \
            assert(DEBUG < INFO && INFO < WARNING && WARNING < ERROR);                              \
            if (getLoggingLevel() == DEBUG) {                                                        \
                changeTextColor(getTextColorForLevel(DEBUG));                                                   \
                FILE* logFile = getLogFile();                                                                   \
                bool isTransferToFile = !isatty(STDOUT_FILENO);                                                 \
                FILE* stream = (logFile == NULL || isTransferToFile) ? stderr : logFile;                        \
                                                                                                                \
                const char* logMessage = getLoggingMessage(DEBUG, __FILE__, __FUNCTION__, __LINE__);            \
                if (isTransferToFile || logFile != NULL) {                                                      \
                    fprintf(stream, "%s", logMessage);                                                          \
                    DBG_TO_STREAM(stream, __VA_ARGS__);                                                           \
                } else {                                                                                        \
                    colourfullPrintToStream(stream, "%s", logMessage);                                          \
                    colourfullDebugToStream(stream, __VA_ARGS__);\
                }                                                                                               \
            } \
        } while (0)
#else
    #define DEBUG_(...)             (void)(0)
    #define LOG_MESSAGE(level, ...) (void)(0)
#endif



// #ifndef NO_LOG
//     #define DEBUG_(...)                                                                             \
//     do {                                                                                            \
//         assert(DEBUG < INFO && INFO < WARNING && WARNING < ERROR);                                  \
//         if (getLoggingLevel() == DEBUG)                                                             \
//             DO_STUFF(true, DEBUG, __VA_ARGS__);                                                     \
//     } while (0)
//
    // #define LOG_MESSAGE(level, ...)                                                                 \
    //     do {                                                                                        \
    //         assert(DEBUG < INFO && INFO < WARNING && WARNING < ERROR);                              \
    //         if (level >= getLoggingLevel())                                                         \
    //             DO_STUFF(false, level, __VA_ARGS__);                                                       \
    //     } while (0)
// #else
//     #define DEBUG_(...)             (void)(0)
//     #define LOG_MESSAGE(level, ...) (void)(0)
// #endif




#ifndef NO_LOG
    #define LOG_DEBUG(...)      LOG_MESSAGE(DEBUG, __VA_ARGS__);
    #define LOG_INFO(...)       LOG_MESSAGE(INFO, __VA_ARGS__);
    #define LOG_WARNING(...)    LOG_MESSAGE(WARNING, __VA_ARGS__);
    #define LOG_ERROR(...)      LOG_MESSAGE(ERROR, __VA_ARGS__);
    #define LOG_FUNC_STARTED()  LOG_MESSAGE(INFO, "function with name: %s started\n", __FUNCTION__);
    #define LOG_FUNC_FINISHED() LOG_MESSAGE(INFO, "function with name: %s finished\n", __FUNCTION__);
#else
    #define LOG_DEBUG(...)      (void)(0)
    #define LOG_INFO(...)       (void)(0)
    #define LOG_WARNING(...)    (void)(0)
    #define LOG_ERROR(...)      (void)(0)
    #define LOG_FUNC_STARTED()  (void)(0)
    #define LOG_FUNC_FINISHED() (void)(0)
#endif

#endif
