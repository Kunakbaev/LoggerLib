#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>

#include "colourfulPrintLib/colourfullPrint.h"
#include "logLib.h"

static const char* FILE_OPENING_ERROR = "Error: couldn't open file\n";

static char timeBuffer[30] = {};
static char buffer[256] = {};

static enum Levels loggingLevel = INFO;
FILE* logFile = NULL;

const char* getLogMessage(enum Levels level) {
    switch (level) {
        case DEBUG:   return "DEBUG";
        case INFO:    return "INFO";
        case WARNING: return "WARNING";
        case ERROR:   return "ERROR";
        default:      return "INFO";
    }
}

enum Colors getTextColorForLevel(enum Levels level) {
    switch (level) {
        case DEBUG:   return GREEN_COLOR;
        case INFO:    return WHITE_COLOR;
        case WARNING: return YELLOW_COLOR;
        case ERROR:   return RED_COLOR;
        default:      return WHITE_COLOR;
    }
}

void setLoggingLevel(enum Levels level) {
    loggingLevel = level;
}

enum Levels getLoggingLevel() {
    return loggingLevel;
}

const char* getCurrentTimeFormatted() {
    struct timeval currentTime = {};
    gettimeofday(&currentTime, NULL);

    long long mils = (long double)currentTime.tv_usec / 1000; // 1000 - mils in one second
    struct tm *tm_info = localtime(&currentTime.tv_sec);
    assert(tm_info != NULL);

    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", tm_info);
    sprintf(timeBuffer + strlen(timeBuffer), ":%.3Ld", mils);
    return timeBuffer;
}

static int getTrimDx(const char* line, int maxLen) {
    assert(line != NULL);

    size_t len = strlen(line);
    return len > maxLen ? len - maxLen : 0;
}

const char* getLoggingMessage(enum Levels level, const char* fileName, const char* funcName, int line) {
    assert(fileName != NULL);
    assert(funcName != NULL);

    const char* currentTime = getCurrentTimeFormatted();
    const char* logMessage = getLogMessage(level);


// #ifdef NO_INFO
//     printf("no log info\n");
// #else
//     printf("log info\n");
// #endif

    // sprintf(buffer, "%s", currentTime);
    sprintf(buffer, "%-7s from File: %-30.30s, Function: %-20.20s, Line: %-4d at %s   ->   ",
            logMessage, fileName + getTrimDx(fileName, 30),
            funcName + getTrimDx(funcName, 20), line, currentTime);
    return buffer;
}

void stateLogFile(const char* logFileName) {
    assert(logFileName != NULL);

    // we want to add to file, not to clear it every time we relaunch our app
    logFile = fopen(logFileName, "a");
    if (logFile == NULL) {
        // assert(false);
        printError("%s", FILE_OPENING_ERROR);
    }

    //fprintf(logFile, "------------------------------------\n");
    LOG_INFO("New logging session started\n");
}

FILE* getLogFile() {
    return logFile;
}

void destructLogger() {
    if (logFile != NULL)
        fclose(logFile);
}
