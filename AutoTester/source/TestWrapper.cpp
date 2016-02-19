#include "TestWrapper.h"
#include "Parser.h"
#include "QueryEvaluator.h"

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool TestWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
	// call your parser to do the parsing
  // ...rest of your code...
	Parser::parse(filename);
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...

  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.

	size_t pos;
	query.find_last_of(";");
	string declarationSenctence, QuerySentence;
	declarationSenctence = query.substr(0, pos + 1);
	QuerySentence = query.substr(pos + 1, query.size() - pos);
	ParseResult pr = ParseResult();
	ParseResult mustpr = pr.generateParseResult(declarationSenctence, QuerySentence);
	QueryEvaluator Qe;
	std::vector<std::string> resultsString = Qe.startEvaluator(mustpr);
	results = std::list<std::string>(resultsString.begin(), resultsString.end());
}
