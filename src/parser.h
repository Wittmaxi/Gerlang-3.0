#include "helpers/parserutil/scope.h"

std::vector<std::tuple < items, std::string >> lexerTokens;
std::vector <std::tuple < items, std::string >> currentLine;
int positionInLexerToken;
int positionInLine;
int lineNumber;
bool hasError;	//dont proceed, if the code didnt pass through the CFG
bool hasMainFunction;
std::vector<scope> scopes; //stack of all the outterScope(). New scopes get the variables of the ones above
std::vector<std::string> outCode;//the code that the parser outputs
bool isInOutterScope;
std::vector<std::string> totalCode;

//////////UTILITIES

scope& outterScope () {
	return scopes[scopes.size()-1];
}

items getToken () { //get the current token
	if (positionInLine < currentLine.size())
		return std::get <0> (currentLine[positionInLine]);
	return items::VOID;
}

std::string getTInfo () { //get the current information to the tokens
	if (positionInLine < currentLine.size())
		return std::get <1> (currentLine[positionInLine]);
	return "";
}

void wpe(std::string error) { //write a parser error to stdout
	std::cout << "Parser | Fehler, Zeile " << lineNumber << " : " << error << std::endl;
	hasError = true;
}

bool incPos () {
	//	if (positionInLine > currentLine.size()) {
	//		return false;
	//		hasError = true;
	//	}	
	positionInLine++;
	return true;
}

void decreaseScope () {
	if (scopes.size() == 1) {
		wpe ("\"ende\" bekommen, aber kein Block zum schliessen gefunden.");	
	} else {	
		scopes.resize (scopes.size()-1);
		isInOutterScope = (scopes.size () == 0) ? true : false;	
	}
}

///////////PARSE - HELPERS

#include "helpers/parserutil/parseHelpers.h" //include some utilities, that dont NESSECARILY have to be 
//in this exact file

/////////IMPLEMENTATION

bool mainFunction () {
	if (getToken() == items::MAIN_FUNC) {

		if (hasMainFunction) {
			wpe ("Zu viele anfangs-funktionen gefunden.");
		}
		scopes.push_back (scope (outterScope()));
		totalCode.push_back ("int main () {");
		hasMainFunction = true;
		incPos();
		return true;
	}
	return false;
}

bool variableDefinition () {
	variable currVar = parseVariable();
	std::string code = "";
	if (currVar.isInit == true) { //ITS A VARIABLE!
		code += currVar.type;
		code += " " + currVar.name;	
		if (getToken() == items::DELIM && getTInfo () != "=") {
		}
		code += ";";	//semicolon, being there
		//No matter if there is an
		//operation
		totalCode.push_back (code);
	}
	incPos();	
	return true;
}

bool functionDefinition () {
	std::cout << tts (getToken()) << std::endl;
	if (!(getToken() == items::FUNCTION_1)) {
		return false; //it's not a function definition
	}
	std::string functionName; //the name of da function
	std::vector<std::tuple < std::string, std::string >> variables; //the input variables. <name, type>
	std::string funcReturnType;

	if (!(incPos())) {
		wpe ("\"Identifizierer\" erwartet, stattdessen \"Dateiende\" gefunden.");
	} 	
	if (getToken() == items::IDENT) {
		if (identValid (getTInfo ())) {
			functionName = getTInfo ();
		} else {
			wpe ("Funktionsname " + getTInfo() + " ist ungültig oder schon benutzt");
		}
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
	//incPos();
	funcReturnType = getTInfo();
	outterScope().functions.push_back (make_pair (functionName, funcReturnType));
	scope generatedScope (scopes[scopes.size()-1], true);
	for (auto i : generatedScope.functions) {
		std::cout << "kekse" << std::get <0> (i) << std::endl;
	}
	generatedScope.addVars (variables);
	std::string inputs = "(";
	for (int i = 0; i < variables.size(); i++) {
		if (i != 0) {inputs += ",";}
		inputs += (returnTypeName (std::get <1> (variables[i])));
		inputs += (returnTypeName (std::get <0> (variables[i])));	
	}
	inputs += ")";
	totalCode.push_back (
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
	if (getToken () == items::SCOPE_END) {
		std::cout << "hi" << std::endl;
		totalCode.push_back ("}");
		decreaseScope();
		incPos();
		return true;	
	}
	return false;
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
		getLineTokens();
		std::cout << "><><><><><><" << std::endl;
		for (auto i: currentLine) {
			std::cout << i << std::endl;
		}
		std::cout << "<><><><><><>" << std::endl;
		lineNumber ++;
		if (		
				mainFunction ()       ||
				functionDefinition () || //infinite amount of function definitions are 
				//allowed
				innerScopeCalls ()    ||
				variableDefinition () //infinite amounts of variable definitionas are allowed
		) {
			if (!hasError) {
				if (positionInLine < currentLine.size()) {
					wpe ("\"Neue Zeile\" erwartet, stattdessen " + tts (getToken()) + " bekommen.");
				}		
			}
			//valid command
		} else {
			wpe ("Unerwarteterweise " + tts (getToken()) + " bekommen.");
			hasError = true;
		}
		std::cout << "PLT" << positionInLexerToken << std::endl;
	}
	if (! hasMainFunction) {
		wpe ("Keine anfangs-funktion im Programm gefunden.");
	}
	for (auto i : totalCode) {
		std::cout << i << std::endl;
	}	

}

bool parse (std::vector<std::tuple < items, std::string>> input) { //returns wether parsing was successful
	//parses and generates the C++ code of the thing.	
	lexerTokens = input;
	scope outterScope;
	scopes.push_back (outterScope);
	beginOfFile ();
	return hasError;
}
