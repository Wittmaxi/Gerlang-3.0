#include "helpers/parserutil/scope.h"

std::vector<std::tuple < items, std::string >> lexerTokens;
int positionInLexerToken;
bool hasError;	//dont proceed, if the code didnt pass through the CFG
bool hasMainFunction;
std::vector<scope> scopes; //stack of all the scopes. New scopes get the variables of the ones above
std::vector<std::string> outCode;//the code that the parser outputs
bool isInOutterScope;
std::vector<std::string> totalCode;

//////////UTILITIES

items getToken () { //get the current token
	return std::get <0> (lexerTokens[positionInLexerToken]);
}

std::string getTInfo () { //get the current information to the tokens
	return std::get <1> (lexerTokens[positionInLexerToken]);
}

void wpe(std::string error) { //write a parser error to stdout
	std::cout << "Parser | Fehler: " << error << std::endl;
	hasError = true;
}

bool incPos () {
	positionInLexerToken ++;
	if (positionInLexerToken >= lexerTokens.size()) {
		return false;
	}	
	return true;
}

void decreaseScope () {
	if (scopes.size() == 1) {
		//later : throw errors
	} else {
		totalCode.insert (totalCode.end(), scopes.end()->code.begin(), scopes.end()->code.end());	
		scopes.resize (scopes.size()-1);
		isInOutterScope = (scopes.size () == 1) ? true : false;	
	}
}

///////////PARSE - HELPERS

#include "helpers/parserutil/parseHelpers.h" //include some utilities, that dont NESSECARILY have to be 
					     //in here
////////////IMPLEMENTATION

bool variableDefinition () {
	incPos();
	return true;
}

bool functionDefinition () {
	if (!(getToken() == items::FUNCTION_1)) {
		return false; //it's not a function definition
	}
	
	scope generatedScope (*scopes.end());
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
	bool leaveLoop = true;
	while (leaveLoop) {
		//variable definitions in functions
		std::cout << "varsllooooooppppp" << std::endl;	
		variable currentVar;
		currentVar = parseVariable();
		if ((! currentVar.isInit) && (!(getTInfo() == ")"))) {
			wpe ("Variablendeklaration erwartet.");
		} else { 	
			variables.push_back (std::make_pair (currentVar.name, currentVar.type));
		}
		if (getTInfo () == ",") {

		} else if (getTInfo () == ")") {
			leaveLoop = false;
		} else {
			wpe ("\")\" oder \",\" erwartet, statdessen " + tts (getToken()) + " bekommen.");		
			leaveLoop = false;	
		}
	}
	if (!(incPos())) {
		wpe ("\"ergibt\" erwartet, stattdessen \"Dateiende\" bekommen.");
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
	incPos();
	funcReturnType = getTInfo();
	generatedScope.addVars (variables);
	std::string inputs = "(";
	for (int i = 0; i < variables.size(); i++) {
		if (i != 0) {inputs += ",";}
		inputs += (returnTypeName (std::get <1> (variables[i])));
		inputs += (returnTypeName (std::get <0> (variables[i])));	
	}
	inputs += ")";
	generatedScope.addCode (
		returnTypeName (funcReturnType) + " " +
		functionName + " " +
	 	inputs + " " +
		"{"//the scope of the function				
	);
	scopes.push_back (generatedScope);
	isInOutterScope = false;	
	return hasError;
}

bool endOfScope () {
	if (! (getToken () == items::SCOPE_END)) {
		scopes.end()->code.push_back ("}");
		decreaseScope();
		incPos();	
	}
}

bool innerScopeCalls() {
	if (! isInOutterScope) {
		if ( 
			endOfScope()
		) {
			return true;
		}
		return false;
	} else {
		return false;
	}
}

void beginOfFile () {
	isInOutterScope = true;
	while ((positionInLexerToken < lexerTokens.size()) && !(hasError)) {
		//if the current token is either a function definition or a variable definition
		//as is allowed
		if (functionDefinition () || //infinite amount of function definitions are 
				       	     //allowed
		    innerScopeCalls () ||
		    variableDefinition () //infinite amounts of variable definitionas are allowed
		)     
		{
			//valid command
		} else {
			wpe ("\"Funktionsdefinition\" oder \"variablendeklaration\" erwartet, stattdessen " + tts (getToken()) + " bekommen.");
			hasError = true;
		}
	}
	for (auto i : scopes.end()->code) {
		std::cout << i << std::endl;
	}	
}

void parse (std::vector<std::tuple < items, std::string>> input) {
	//parses and generates the C++ code of the thing.	
	lexerTokens = input;
	scope outterScope;
	scopes.push_back (outterScope);
	beginOfFile ();
}
