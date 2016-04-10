#include <vector>
#include <string>
#include "ParseResult.h"
using namespace std;

class QueriesAnswerStorage {
public:
	void SetResultTable(vector<vector<string>>);
	int GetResultTablePos(string);
	vector<vector<string>> GetResultsTable();
	void SetSelect(vector<string>);
	void SetTable(string);
	bool HasKey(string);
	vector<string> MergeResults();
	void clear();
	void SetNoClause(vector<string>);
	vector<string> GetNoClause();
	vector<pair<std::string, std::string>> GetSelectParameter();
	string GetWithTableElement(string);
	string GetSelectType(string);
	QueriesAnswerStorage();
	~QueriesAnswerStorage();
protected:

	static std::unordered_map<std::string, int> ClausesParameterPositionInTable;
	static vector<vector<string>> ResultsTable;
	static vector<pair<std::string,std::string>> SelectParameter;
	static std::unordered_map<std::string, std::string> WithTable;
	static vector<string> NoClause;
	static unordered_map<string, vector<string>> WithMap;
};