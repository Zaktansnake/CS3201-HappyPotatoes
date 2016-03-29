
#include <string>
#include <vector>
#include "ParseResult.h"
class QueryEvaluator
{
public:

	vector<string> startEvaluator(ParseResult mustPr);
	
	// constructors
	QueryEvaluator();
	~QueryEvaluator();

protected:
	vector<string> NoResults;

private:
	bool Follows(string, string, string, string, bool, string, string);
	bool Modifies(string, string, string, string, bool, string, string);
	bool FollowsStar(string, string, string, string, bool, string, string);
	bool Next(string, string, string, string, bool, string, string);
	bool NextStar(string, string, string, string, bool, string, string);
	bool Parents(string, string, string, string, bool, string, string);
	bool ParentsStar(string, string, string, string, bool, string, string);
	bool Uses(string, string, string, string, bool, string, string);
	int ChangeStringToInt(string);
	string ChangeIntToString(int);
	bool HaveQuotation(string);
	bool IsNumber(string);
};

