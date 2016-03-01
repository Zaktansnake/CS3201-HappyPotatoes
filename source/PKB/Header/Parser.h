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

public:
	static int parse(string filename);

private:
};

#endif