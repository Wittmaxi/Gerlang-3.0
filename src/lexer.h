std::vector <std::tuple <items, std::string> > output;
std::string file;
int position;

void addToOutput (items item, std::string code = "") {
	output.push_back (make_pair (item, code));
}

bool isDelim (char input) {
	switch (input) {
		case '(':
		case '{':
		case '[':
		case ')':
		case ']':
		case '}':
		case '=':
		case '+':
		case '-':
		case '*':
		case '/':
			{
				return true;
			}
		default: 
			{
				return false;
			}
	}
	return false;
}

bool isItem (char input) {
	
	switch (input) {
		case '(':
		case '{':
		case '[':
		case ')':
		case ']':
		case '}':
		case '=':
		case '+':
		case '-':
		case '*':
		case '/':
		case 0x07:
		{
			return true;
			break;
		}
		default: 
			return false;
			break;
	}
	return false;
}

std::string readTilNextExpr () {
	std::string outputStr;	
	while (!(isItem(file[position]))) {
		outputStr += file [position];
		if (!(position >= file.size())) {
			 position++;
		}
	}
	std::cout << std::endl;
	if (isDelim (file[position])) {
		outputStr += file [position];	
	}	
	position++;
	return outputStr;
}

bool handleRvals (std::string val) {
	//check if it is a rval and if not so, returns false
}

bool handleKeyW (std::string expression) {
	//straightforward
	std::cout << "gonna handle expressions" << std::endl;
	if (expression == "anfang") {
		addToOutput (items::MAIN_FUNC);	
	} else if (expression == "funktion") {
		addToOutput (items::FUNCTION_1);
	} else if (expression == "ergibt") {
		addToOutput (items::FUNCTION_2);
	} else if (expression == "gebe") {
		addToOutput (items::RETURN_1);
	} else if (expression == "zurück") {
		addToOutput (items::RETURN_2);
	} else if (expression == "wenn") {
		addToOutput (items::COND);
	} else if (expression == "solange") {
		addToOutput (items::LOOP);
	} else if (expression == "variable") {
		addToOutput (items::VAR_DECL);
	} else if (expression == "zeiger") {
		addToOutput (items::VAR_POINTER);
	} else if (handleRvals (expression)) {
		//already appended
	} else {} //it must be an identifier, so append it as one
	return true;	
} 

void evalExpression (std::string expression) {
	if (isDelim (expression[0]) && expression.size() == 1) {
		addToOutput(items::DELIM, expression);
	} else if (expression[0] == 0x07 && expression.size() == 1) {
		//do nothing
	} else if (handleKeyW(expression)) {
		//keywords are already handled
	} else {
		//handle litterals or identifiers	
	}
}

void find () {
	while (position < file.size()) {
		evalExpression (readTilNextExpr ());
	}	
}

void lex (std::vector<std::string>& input) {
	file = sanitizeFile (input);
	find ();
}
