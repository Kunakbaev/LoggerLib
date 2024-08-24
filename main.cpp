#include <stdio.h>

#include "logLib.hpp"

#define X 1

int main() {
    setLoggingLevel(DEBUG);
    stateLogFile("logFile.txt");

    LOG_DEBUG("i am log debug\n");
    LOG_INFO("i am log info\n");
    LOG_WARNING("i am log warn\n");
    LOG_ERROR("i am log error\n");

    destructLogger();
	return 0;
}
