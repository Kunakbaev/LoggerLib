#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "colourfulPrintLib/colourfullPrint.hpp"

static char buffer[256];

const char* getCurrentTimeFormatted() {
    struct timeval currentTime = {};
    gettimeofday(&currentTime, NULL);

    long long mils = (long double)currentTime.tv_usec / 1000; // 1000 - mils in one second
    struct tm *tm_info = localtime(&currentTime.tv_sec);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    sprintf(buffer + strlen(buffer), ":%.3Ld", mils);
    return buffer;
}

#define LOG_MESSAGE(message, textColor, ...)                                \
    do {                                                                    \
        changeTextColor(textColor);                                         \
        const char* currentTime = getCurrentTimeFormatted();                \
        colourfullPrint("%s from File: %s, Function: %s, Line: %d at %s   ->   ", \
            message, __FILE__, __FUNCTION__, __LINE__, currentTime);        \
        colourfullPrint(__VA_ARGS__);                                       \
    } while (0);


#define LOG_ERROR(...) LOG_MESSAGE("ERROR", RED_COLOR, __VA_ARGS__);

#define LOG_WARN(...) LOG_MESSAGE("WARN", YELLOW_COLOR, __VA_ARGS__);

#define LOG_INFO(...) LOG_MESSAGE("INFO", WHITE_COLOR, __VA_ARGS__);
