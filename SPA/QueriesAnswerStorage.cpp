#include ".\QueriesAnswerStorage.h"
#include <vector>

void QueriesAnswerStorage::BooleanClausesQueryResultsPush(bool Bool)
{
	BooleanClausesQueryResults.push_back(Bool);
}

void QueriesAnswerStorage::VariableClausesQueryResultsPush(std::vector<std::string> InVectorString)
{
	VariableClausesQueryResults.push_back(InVectorString);
}

void QueriesAnswerStorage::ProcedureClausesQueryResultsPush(std::vector<std::string> InVectorString)
{
	ProcedureClausesQueryResults.push_back(InVectorString);
}

void QueriesAnswerStorage::StmtLineClausesQueryResultsPush(std::vector<int> InIntVector)
{
	StmtLineClausesQueryResults.push_back(InIntVector);
}

void QueriesAnswerStorage::PatternClausesQueryResultsPush(std::vector<int> InIntVector)
{
	PatternClausesQueryResults.push_back(InIntVector);
}

void QueriesAnswerStorage::FinalStringVectorPush(std::string s)
{
	finalStringVector.push_back(s);
}

std::vector<bool> QueriesAnswerStorage::BooleanClausesQueryResultsGet()
{
	return BooleanClausesQueryResults;
}

std::vector<std::vector<std::string>> QueriesAnswerStorage::VariableClausesQueryResultsGet()
{
	return VariableClausesQueryResults;
}

std::vector<std::vector<std::string>> QueriesAnswerStorage::ProcedureClausesQueryResultsGet()
{
	return ProcedureClausesQueryResults;
}

std::vector<std::vector<int>> QueriesAnswerStorage::StmtLineClausesQueryResultsGet()
{
	return StmtLineClausesQueryResults;
}

std::vector<std::vector<int>> QueriesAnswerStorage::PatternClausesQueryResultsGet()
{
	return PatternClausesQueryResults;
}

std::vector<std::string> QueriesAnswerStorage::finalStringVectorGet()
{
	return finalStringVector;
}
