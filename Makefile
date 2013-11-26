MSL=src/msl/file_util.cpp src/msl/json.cpp src/msl/string_util.cpp
SRCS=src/date.cpp src/task.cpp src/task_list.cpp src/unit_tests.cpp $(MSL)
OPTS=-O -Wall
LIBS=
COMPILER=g++
OUT=bin

all: unit_tests

unit_tests: $(SRCS)
	$(COMPILER) $(CFLAGS) $(SRCS) $(LIBS) $(OPTS) -o $(OUT)/$@

clean:
	rm -rf $(OUT)/unit_tests