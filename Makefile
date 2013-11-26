SRCS=src/date.cpp src/task.cpp src/unit_tests.cpp
OPTS=-O -Wall
LIBS=
COMPILER=g++
OUT=bin

all: unit_tests

unit_tests: $(SRCS)
	$(COMPILER) $(CFLAGS) $(SRCS) $(LIBS) $(OPTS) -o $(OUT)/$@

clean:
	rm -rf $(OUT)/unit_tests