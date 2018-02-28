std::vector<std::tuple < items, std::string >> lexerTokens;
int positionInLexerToken;

void functionDefinition () {

}

void beginOfFile () {
	
}

void parse (std::vector<std::tuple < items, std::string>> input) {
	//parses and generates the C++ code of the thing.	
	lexerTokens = input;
	beginOfFile ();
}
