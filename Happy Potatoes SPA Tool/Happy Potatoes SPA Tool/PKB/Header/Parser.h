#ifndef Parser_h
#define Parser_h

#include <string>
#include <map>
#include <memory>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class PKB;

class Parser {

private:

public:
	static int parse(string filename);
	static bool is_file_exist(string file);
	static bool is_file_empty(ifstream file);
};


#endif