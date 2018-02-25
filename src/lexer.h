std::vector <std::tuple <items, std::string> > output;
std::string file;
int position;

std::string readTilNextExpr () {
	std::string outputStr;	
	while (file[position] != 0x07) {
		outputStr += file [position];
		position++;
	}
	return outputStr;
}

void evalExpression (std::string expression) {

}

void find () {
	
}

void lex (std::vector<std::string>& input) {
	file = sanitizeFile (input);
	find ();
}
