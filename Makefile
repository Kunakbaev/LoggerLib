CC=g++
CFLAGS := -D _DEBUG -lm -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -pie -fPIE -Werror=vla
# CFLAGS = -D _DEBUG
# CFLAGS += -fsanitize=address

# ASK: for some reason 'lib' prefix must be added to the file name
MY_LIBS_PATH := /usr/local/lib/
MY_LIB_NAME  := libmy_loglib

# [[fallthrough]]

# 1) libRun -> variable; testRun -> variable
# 2) build directory -> variable, -o flags for each compilation
# 3) @> @^ @< $<
# 4) PHONY - что делает

SOURCE_DIR        := source
LIB_RUN_NAME      := loggingLib
BUILD_DIR         := building

ifeq ($(DEBUG), 0)
	ASSERT_DEFINE = -DNDEBUG
endif

.PHONY: $(LIB_RUN_NAME) run $(BUILD_DIR) clean

# -------------------------   LIB RUN   -----------------------------

SRC := $(wildcard ./$(SOURCE_DIR)/*.cpp)
OBJ := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(notdir ${SRC}))

# running all commands without output (@ at the beginning)
$(LIB_RUN_NAME): $(OBJ) $(LOGGER_OBJ) $(SORTING_ALGOS_OBJ)
	@$(CC) $^ -o $(BUILD_DIR)/$(LIB_RUN_NAME) $(CFLAGS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(BUILD_DIR)
	@$(CC) -c $< $(CFLAGS) -o $@ $(ASSERT_DEFINE)

run: $(LIB_RUN_NAME)
	@$(BUILD_DIR)/$(LIB_RUN_NAME)

# ASK: how does it work? expor LD_LIBRARY_PATH=/usr/local/bin:$$LD_LIBRARY_PATH, just temprorarily stores info to var? config just saves changes?
install:
	@echo installing logger lib .so lib file
	$(CC) -shared -o $(MY_LIB_NAME).so -lm -fPIC $(SRC)
	@echo i hope this is safe command and there is nothing to worry about
	sudo mv $(MY_LIB_NAME).so $(MY_LIBS_PATH)/$(MY_LIB_NAME).so
	export LD_LIBRARY_PATH=/usr/local/bin:$$LD_LIBRARY_PATH
	sudo ldconfig




# -------------------------   HELPER TARGETS   ---------------------------

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/$(LIB_RUN_NAME)

# g++ -o main.exe main.cpp quadraticEquationLib/quadraticEquation.cpp testsGeneratorLib/testsGenerator.cpp colourfullPrintLib/colourfullPrint.cpp -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -pie -fPIE -Werror=vla
