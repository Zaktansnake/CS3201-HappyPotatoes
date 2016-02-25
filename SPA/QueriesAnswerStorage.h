#include <vector>
#include <string>

class QueriesAnswerStorage {

	public:

		std::vector<bool> BooleanClausesQueryResults;
		std::vector<std::vector<std::string>> VariableClausesQueryResults;
		std::vector<std::vector<std::string>> ProcedureClausesQueryResults;
		std::vector<std::vector<int>> StmtLineClausesQueryResults;
		std::vector<std::vector<int>> PatternClausesQueryResults;
		std::vector<std::string> finalStringVector;
	
		//push methods
		void BooleanClausesQueryResultsPush(bool Bool);
		void VariableClausesQueryResultsPush(std::vector<std::string> InVectorString);
		void ProcedureClausesQueryResultsPush(std::vector<std::string> InVectorString);
		void StmtLineClausesQueryResultsPush(std::vector<int> InIntVector);
		void PatternClausesQueryResultsPush(std::vector<int> InIntVector);
		void FinalStringVectorPush(std::string InIntVector);
		
		//get methods
		std::vector<bool> BooleanClausesQueryResultsGet();
		std::vector<std::vector<std::string>> VariableClausesQueryResultsGet();
		std::vector<std::vector<std::string>> ProcedureClausesQueryResultsGet();
		std::vector<std::vector<int>> StmtLineClausesQueryResultsGet();
		std::vector<std::vector<int>> PatternClausesQueryResultsGet();
		std::vector<std::string> finalStringVectorGet();

	
};


