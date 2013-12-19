MSL_UT=src/msl/file_util.cpp src/msl/json.cpp src/msl/string_util.cpp src/msl/time_util.cpp
SRCS_UT=src/date.cpp src/task.cpp src/task_list.cpp src/unit_tests.cpp $(MSL_UT)
LIBS_UT=

MSL_DY=src/msl/2d.cpp src/msl/2d_util.cpp src/msl/file_util.cpp src/msl/glut_input.cpp src/msl/glut_ui.cpp src/msl/json.cpp src/msl/sprite.cpp src/msl/string_util.cpp src/msl/time_util.cpp
SRCS_DY=src/date.cpp src/task.cpp src/task_list.cpp src/main.cpp src/menu_bar.cpp src/task_ui.cpp src/task_list_ui.cpp $(MSL_DY)
LIBS_DY= -lGL -lGLU -lglut -lGLEW -lSOIL -lftgl

OPTS=-O -Wall
COMPILER=g++
OUT=bin

all: unit_tests drudgery

unit_tests: $(SRCS_UT)
	$(COMPILER) $(CFLAGS) $(SRCS_UT) $(LIBS_UT) $(OPTS) -o $(OUT)/$@

drudgery: $(SRCS_DY)
	$(COMPILER) $(CFLAGS) $(SRCS_DY) $(LIBS_DY) $(OPTS) -o $(OUT)/$@ -ggdb

clean:
	rm -rf $(OUT)/$@