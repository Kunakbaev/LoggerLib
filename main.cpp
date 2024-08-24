#include <stdio.h>
#include <unistd.h>

#include "logLib.hpp"

#define X 1

int main() {
    LOG_DEBUG("i am log debug\n");
    LOG_INFO("i am log info\n");
    LOG_WARNING("i am log warn\n");
    LOG_ERROR("i am log error\n");

    // if (isatty(STDOUT_FILENO)) {
    //     LOG_INFO("standart output to terminal\n");
    // } else {
    //     LOG_INFO("standart output to file\n");
    // }
	return 0;
}
