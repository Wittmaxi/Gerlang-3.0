std::vector <std::tuple <items, std::string> > lexerOutput;
std::string file;
int position;

void addToOutput (items item, std::string code = "") {
	lexerOutput.push_back (make_pair (item, code));
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
		case ',':
		case '/':
		case 0x06:
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
	return ((isDelim (input)) || (input == 0x07));
}

std::string readTilNextExpr () {
	std::string outputStr;
	if (isItem (file[position])) {
		if (isDelim (file[position])) {
			outputStr += file[position];
		}
		position++;
		return outputStr;
	}	
	while (!isItem(file[position])) {
		outputStr += file[position];
		position++;	
	}
	return outputStr;
}

bool handleRvals (std::string val) {
	//check if it is a rval and if not so, returns false
	if (isString(val)) {
		addToOutput (items::CHAR_RVAL, getStr (val));
	} else if (isBool (val)) {
		addToOutput (items::BOOL_RVAL, val);
	} else if (isInt (val)) {
		addToOutput (items::INT_RVAL, val);
	} else if (isFloat (val)) {
		addToOutput (items::FLOAT_RVAL, val);
	} else {
		return false;
	}
	return true;
}

bool handleKeyW (std::string expression) {
	//straightforward
	if (expression == "anfang") {
		addToOutput (items::MAIN_FUNC);	
	} else if (expression == "ende") {
		addToOutput (items::SCOPE_END);
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
	} else if (expression[0] == 0x06) {
		addToOutput (items::NEW_LINE);	
	} else if (handleRvals (expression)) {
		//already appended
	}  else {
		addToOutput (items::IDENT, expression);
	} //it must be an identifier, so append it as one
	return true;	
} 

void evalExpression (std::string expression) {
	std::cout << "Current expression: " << expression << std::endl;
	if (isDelim (expression[0]) && expression[0] != 0x06) {
		addToOutput(items::DELIM, expression);
	} else if (expression == "" || expression == " ") {
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
	for (auto i : lexerOutput) {
		std::cout << i << std::endl;
	}	
}

void lex (std::vector<std::string>& input) {
	file = sanitizeFile (input);
	find ();
}
