#include <stdio.h>
#include <stdbool.h>

// #define NO_LOG

#include "../include/logLib.hpp"
#include "../include/debugMacros.hpp"

int main() {
    setLoggingLevel(DEBUG);
    //stateLogFile("logFile.txt");

    int a = 10;
    bool f = false;
    DEBUG_(f);

    printf("bruh\n");
    LOG_FUNC_STARTED();
    LOG_FUNC_FINISHED();

//     const char* constCharPtrVar = "i am const char ptr";
//     int intVar = 10;
//     bool boolVar = true;
//     long double longDoubleVar = 3.141592;
//     FILE* file = getLogFile(); // for file it will output ?, unknown type
//     DEBUG(constCharPtrVar, intVar, boolVar, file);
//
    //enum Levels lo = DEBUG;
    LOG_DEBUG("i am log debug\n");
    LOG_INFO("i am log info\n");
    LOG_WARNING("i am log warn\n");
    LOG_ERROR("i am log error\n");

    destructLogger();
	return 0;
}
