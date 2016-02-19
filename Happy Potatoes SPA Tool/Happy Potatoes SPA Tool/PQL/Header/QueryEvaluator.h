#ifndef QueryEvaluator_h
#define QueryEvaluator_h

#include <string>
#include <vector>
#include "../Header/ParseResult.h"

class QueryEvaluator
{
public:

    static vector<string> startEvaluator(ParseResult);
	QueryEvaluator();
	~QueryEvaluator();
};
#endif
