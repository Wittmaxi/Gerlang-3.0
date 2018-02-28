#include "helpers/parserutil/scope.h"

std::vector<std::tuple < items, std::string >> lexerTokens;
int positionInLexerToken;
std::vector<std::string> currentCode; //thecode for the current Scope
bool hasError;	//dont proceed, if the code didnt pass through the CFG
bool hasMainFunction;
std::vector<scope> scopes; //stack of all the scopes. New scopes get the variables of the ones above
std::vector<std::string> outCode;//the code that the parser outputs

items getToken () { //get the current token
	return std::get <0> (lexerTokens[positionInLexerToken]);
}

std::string getTInfo () { //get the current information to the tokens
	return std::get <1> (lexerTokens[positionInLexerToken]);
}

void wpe(std::string error) { //write a parser error to stdout
	std::cout << "Parser | Fehler :" << error << std::endl;
}

bool incPos () {
	positionInLexerToken ++;
	if (positionInLexerToken >= lexerTokens.size()) {
		return false;
	}	
	return true;
}

void variableDefinition () {
	
}

void functionDefinition () {
	std::string functionName;
	if (!(getToken() == items::FUNCTION_1)) {
		return; //it's not a function definition 
	}
	if (!(incPos)) {
		wpe ("\"Identifizierer\" erwartet, stattdessen \"Dateiende\" gefunden.");
		hasError;	
	} 	
	if (getToken() == items::IDENT) {
		functionName = getTInfo ();	
	} else {
		wpe ("\"Identifizierer\" erwartet, stattdessen " + tts (getToken()) + " bekommen");
	}
	
}

void beginOfFile () {
	while (positionInLexerToken < lexerTokens.size()) {
		functionDefinition (); //infinite amount of function definitions are 
				       //allowed
		variableDefinition (); //infinite amounts of variable definitionas are allowed
	}	
}

void parse (std::vector<std::tuple < items, std::string>> input) {
	//parses and generates the C++ code of the thing.	
	lexerTokens = input;
	beginOfFile ();
}
