std::vector <std::tuple <items, std::string> > output;
std::vector<std::string> *file;
int line, col;

void readTilNextExpr () {
	int i = col;
	for (; i < file->at(line).size(); i++) {
		
	}	
}

void evalExpression (std::string expression) {
	if (expression == "funktion") {
	
	}
}

void find () {
	line = col = 0;
	for (; line < file->size(); line ++) {
		for (; col < file->at (line).size(); col++) {
			int before = col;
			readTilNextExpr();
		        std::string currentExpression = file->at(line).substr(before, col);
			evalExpression (currentExpression);
		}
	}
}

void lex (std::vector<std::string>& input) {
	file = &input;
	find ();
}
