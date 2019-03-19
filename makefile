LIB_PATH= ./lib/
#INC=$(LIB_PATTH)/to_string/ $(LIB_PATTH)/bench/
#INC_PARAMS=$(foreach d, $(INC), -I$d)

all: main.cpp
	g++ -g -std=c++17 -I $(LIB_PATH) main.cpp