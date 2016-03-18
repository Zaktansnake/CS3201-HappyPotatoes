#ifndef QueryEvaluator_h
#define QueryEvaluator_h
#include <string>
#include <vector>

class QueryEvaluator
{
public:

	// constructors
	QueryEvaluator();
	~QueryEvaluator();

protected:

	std::vector<bool> BooleanClausesQueryResults;
	//all the variable results for all conditions in a single query will be stored here
	std::vector<std::vector<std::string>> VariableClausesQueryResults;
	//all the procedure results for all conditions in a single query will be stored here
	std::vector<std::vector<std::string>> ProcedureClausesQueryResults;
	//all the stmtline results for all conditions in a single query will be stored here
	std::vector<std::vector<int>> StmtLineClausesQueryResults;
	//all the assignment results for all patterns
	std::vector<std::vector<int>> PatternClausesQueryResults;
	//the final string that is suppose to be printed
	std::vector<std::string> finalStringVector;
};

#endif