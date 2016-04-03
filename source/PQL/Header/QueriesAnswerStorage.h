#include <vector>
#include <string>
#include "ParseResult.h"
using namespace std;

class QueriesAnswerStorage {
public:
	void SetSelect(vector<string>);
	void SetTable(string);
	bool HasKey(string);
	void update(string, vector<string>);
	vector<string> MergeResults();
	vector<string> GetColFromResultsTable(string);
	void SetWithTable(vector<With>);
	void clear();
	void SetNoClause(vector<string>);
	vector<string> GetNoClause();
	vector<pair<std::string, std::string>> GetSelectParameter();
	QueriesAnswerStorage();
	~QueriesAnswerStorage();
protected:

	static std::unordered_map<std::string, int> ClausesParameterPositionInTable;
	static vector<vector<string>> ResultsTable;
	static vector<pair<std::string,std::string>> SelectParameter;
	static std::unordered_map<std::string, std::string> WithTable;
	static vector<string> NoClause;
};