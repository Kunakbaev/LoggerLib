#include <stdio.h>

#include "logLib.cpp"

int main() {
    for (int i = 0; i < 1000; ++i) {
    LOG_ERROR("i am log error\n");
    LOG_WARN("i am log warn\n");
	LOG_INFO("i am log info\n");
    }

    LOG_MESSAGE("bruh + fail", BLUE_COLOR, "biba i boba\n");
	return 0;
}
