#include "helpers/parserutil/scope.h"

std::vector<std::tuple < items, std::string >> lexerTokens;
int positionInLexerToken;
std::vector<std::string> currentCode; //thecode for the current Scope
bool hasError;	//dont proceed, if the code didnt pass through the CFG
bool hasMainFunction;
std::vector<scope> scopes; //stack of all the scopes. New scopes get the variables of the ones above
scope currentScope; //the scope we are currently working in
std::vector<std::string> outCode;//the code that the parser outputs

bool incPos (bool endAllowed) {

}

items getToken () { //get the current token
	return std::get <0> (lexerTokens[positionInLexerToken]);
}

std::string getTInfo () { //get the current information to the tokens
	return std::get <1> (lexerTokens[positionInLexerToken]);
}

void wpe(std::string error) { //write a parser error to stdout
	std::cout << "Parser | Fehler :" << error << std::endl;
	hasError = true;
}

bool incPos () {
	positionInLexerToken ++;
	if (positionInLexerToken >= lexerTokens.size()) {
		return false;
	}	
	return true;
}

bool variableDefinition () {
	
}

bool functionDefinition () {
	if (!(getToken() == items::FUNCTION_1)) {
		return false; //it's not a function definition
	}
	
	scope generatedScope{};
	generatedScope.addVars (currentScope.variables);
	std::string functionName; //the name of da function
	std::vector<std::tuple < std::string, std::string >> variables; //the input variables. <name, type>
	std::string funcReturnType;

	if (!(incPos())) {
		wpe ("\"Identifizierer\" erwartet, stattdessen \"Dateiende\" gefunden.");
	} 	
	if (getToken() == items::IDENT) {
		functionName = getTInfo ();	
	} else {
		wpe ("\"Identifizierer\" erwartet, stattdessen " + tts (getToken()) + " bekommen.");
	}
	if (!(incPos())) {
		wpe ("\"(\" erwartet, stattdessen \"Dateiende\" gefunden");
	}	
	if (!(getToken () == items::DELIM && getTInfo () == "(")) {
		wpe ("\"(\" erwartet, stattdessen " + tts (getToken()) + " bekommen.");
	}
	if (!incPos ()) {
		wpe ("\"Variablendeklaration\" oder \")\" erwartet, stattdessen " + tts (getToken()) +
" bekommen.");
	}
	while ((getToken () != items::IDENT && getTInfo () != ")") && positionInLexerToken) {
		//variable definitions in functions
		std::string type = getTInfo();
		std::string name;
	
		if (!((getToken () == items::IDENT))) {
			if (!incPos ()) {
				wpe ("\"variable\" erwartet, stattessen \"Dateiende\" gefunden.");
			}						
			if (!(getToken () != items::VAR_DECL)) {
				wpe ("\"variable\" erwartet, stattdessen " + tts(getToken()) + " bekommen.");
			}
			if (!incPos ()) {
				wpe ("\"identifizierer\" erwartet, stattdessen \"Dateiende\" gefunden.");
			}		
			if (!(getToken() != items::IDENT)) {
				wpe ("\"Identifizierer\" erwartet, stattdessen " + tts(getToken()) + " bekommen.");
			}
			name = getTInfo ();
		} 
		if (getTInfo () == ",") {

		} else if (getTInfo () == ")") {

		} else {
			wpe ("\")\" oder \",\" erwartet, statdessen " + tts (getToken()) + " bekommen.");			
		}
		variables.push_back (std::make_pair (name, type));
	}
	if (!(getToken () == items::FUNCTION_2)) {
		wpe ("\"ergibt\" erwartet, statdessen " + tts (getToken()) + " bekommen");
	}	
	if (!(incPos())) {
		wpe ("\"Identifizierer\" erwartet, stattdessen \"Dateiende\" bekommen.");
	}
	if (!(getToken () == items::IDENT)) {
		wpe ("\"Identifizierer\" erwartet, stattdessen " + tts (getToken()) + " bekommen");	
	}
	funcReturnType = getTInfo();
	generatedScope.addVars (variables);
	//generatedScope.addCode ();	
	return hasError;
}

void beginOfFile () {
	while ((positionInLexerToken < lexerTokens.size()) && !(hasError)) {
		//if the current token is either a function definition or a variable definition
		//as is allowed
		if (functionDefinition () || //infinite amount of function definitions are 
				       	     //allowed
		    variableDefinition ())   //infinite amounts of variable definitionas are allowed
		{
			//valid command
		} else {
			wpe ("\"Funktionsdefinition\" oder \"variablendeklaration\" erwartet, stattdessen " + tts (getToken()) + " bekommen.");
			hasError = true;
		}
	}	
}

void parse (std::vector<std::tuple < items, std::string>> input) {
	//parses and generates the C++ code of the thing.	
	lexerTokens = input;
	currentScope = scope();
	scopes.push_back (currentScope);
	beginOfFile ();
}
