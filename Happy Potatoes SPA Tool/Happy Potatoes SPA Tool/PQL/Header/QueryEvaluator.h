#ifndef QUERYeVALUATOR_H
#define QUERYeVALUATOR_H

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

