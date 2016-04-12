
#include <string>
#include <vector>
#include "ParseResult.h"
class QueryEvaluator
{
public:
	vector<string> GetAllOfTheNotStored();
	vector<string> startEvaluator(ParseResult mustPr);
	bool SelectBool = false;
	bool NoClause = false;
	bool SelectNotStored();
	bool CheckWith(With with);
	bool GetAnswerForRightWith(string left, string right);
	bool GetAnswerForLeftWith(string left, string right);
	bool GetAnswerForBothWith(string left, string right);
	vector<string> GetAllOfWithClause(string);
	void clear();
	string RemoveQuotations(string s);
	int ChangeStringToInt(string);
	string ChangeIntToString(int);
	bool HaveQuotation(string);
	pair<string, string> SplitString(string s);
	bool assessClauses(std::vector<Clause> ClausesVector, std::vector<std::string> SelectParameterVector,
		PatternSet PS, vector<With> WithClauses);
	bool assessParseResult(ParseResult pr);
	bool IsSynonym(char c);
	bool CheckSynonym(string, string, char, char, string);
	bool GetResultsForBothSynonym(string, string, char, char, string);
	bool GetResultsForFirstSynonym(string, string, char, char, string);
	bool GetResultsForSecondSynonym(string, string, char, char, string);
	bool CheckTrueOrFalse(string, string, char, char, string);
	vector<string> GetAll(char Type);
	vector<string> GetAllSecondSynonymFromPKB(string P1, string P2, char P1Type, char P2Type, string clausesType);
	vector<string> GetAllFirstSynonymFromPKB(string P1, string P2, char P1Type, char P2Type, string clausesType);
	bool CheckIsResultsFromPkb(string P1, string P2, char P1Type, char P2Type, string clausesType);
	string GetStringType(char c);
	bool CheckTempResultSize(vector<string> v);
	bool GetResultsForNoClause(vector<pair<string, string>>);
	vector<string> GetP2Blank(string ClauseType);
	vector<string> GetP1Blank(string clausesType);
	bool DoNormalClause(vector<Clause> ClausesVector);
	bool DoWithClause(vector<With> W);
	bool ReturnResultsExist(vector<bool> RE);
	bool DoPatterns(PatternSet);
	vector<string> CheckPattern(string type, string name, string P1, string p2, string p3);

	// constructors
	QueryEvaluator();
	~QueryEvaluator();
	vector<string> NoResults;


private:

};

