#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "colourfulPrintLib/colourfullPrint.hpp"
#include "logLib.hpp"

static char timeBuffer[30] = {};
static char buffer[256] = {};

Levels loggingLevel = {};

const char* getLogMessage(Levels level) {
    switch (level) {
        case DEBUG:   return "DEBUG";
        case INFO:    return "INFO";
        case WARNING: return "WARNING";
        case ERROR:   return "ERROR";
        default:      return "INFO";
    }
}

Colors getTextColorForLevel(Levels level) {
    switch (level) {
        case DEBUG:   return GREEN_COLOR;
        case INFO:    return WHITE_COLOR;
        case WARNING: return YELLOW_COLOR;
        case ERROR:   return RED_COLOR;
        default:      return WHITE_COLOR;
    }
}

void setLoggingLevel(Levels level) {
    loggingLevel = level;
}

Levels getLoggingLevel() {
    return loggingLevel;
}

const char* getCurrentTimeFormatted() {
    struct timeval currentTime = {};
    gettimeofday(&currentTime, NULL);

    long long mils = (long double)currentTime.tv_usec / 1000; // 1000 - mils in one second
    struct tm *tm_info = localtime(&currentTime.tv_sec);

    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", tm_info);
    sprintf(timeBuffer + strlen(timeBuffer), ":%.3Ld", mils);
    return timeBuffer;
}

static int getTrimDx(const char* line, int maxLen) {
    size_t len = strlen(line);
    return len > maxLen ? len - maxLen : 0;
}

const char* getLoggingMessage(Levels level, const char* fileName, const char* funcName, int line) {
    buffer[0] = '\0';
    for (int i = 0; i < 256; ++i)
        buffer[i] = '\0';
    const char* currentTime = getCurrentTimeFormatted();
    const char* logMessage = getLogMessage(level);

    // sprintf(buffer, "%s", currentTime);
    sprintf(buffer, "%-7s from File: %-30.30s, Function: %-20.20s, Line: %-4d at %s   ->   ",
            logMessage, fileName + getTrimDx(fileName, 30),
            funcName + getTrimDx(funcName, 20), line, currentTime);
    return buffer;
}
