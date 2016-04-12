#include "TestWrapper.h"
#include "./PKB/Header/Parser.h"
#include "./PQL/Header/QueryEvaluator.h"

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
	Parser::parse(filename);
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results) {
	// call your evaluator to evaluate the query here
	int pos = query.find_last_of(";", query.size());
	string declarationSentence, querySentence;
	declarationSentence = query.substr(0, pos + 1);
	pos++;
	querySentence = query.substr(pos, query.size() - pos);

	ParseResult parser = ParseResult();
	ParseResult generatedParseResult = parser.generateParseResult(declarationSentence, querySentence);
	if (generatedParseResult.getSelectParameter().size()==0) {
		vector<string> NoResults;
		results = results;
	}
	else {
		QueryEvaluator evaluator;
		cout << "I am here4" << endl;
		// store the answers to the query in the results list (it is initially empty)
		std::vector<std::string> resultsEvaluated = evaluator.startEvaluator(generatedParseResult);
		// each result must be a string.
		results = std::list<std::string>(resultsEvaluated.begin(), resultsEvaluated.end());
	}
}