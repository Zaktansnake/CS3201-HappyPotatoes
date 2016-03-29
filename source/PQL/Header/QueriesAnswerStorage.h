#include <vector>
#include <string>
using namespace std;

class QueriesAnswerStorage {
public:
	void SetSelect(vector<string>);
	void SetTable(string);
	bool HasKey(string);
	void update(string, vector<string>);
	vector<string> MergeResults();
	vector<string> GetColFromResultsTable(string);
	void clear();
	QueriesAnswerStorage();
	~QueriesAnswerStorage();
protected:

	static std::unordered_map<std::string, int> ClausesParameterPositionInTable;
	static vector<vector<string>> ResultsTable;
	static vector<pair<std::string,std::string>> SelectParameter;

};