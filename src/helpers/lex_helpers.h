std::pair <std::string, std::string> findAssignements (std::string line) {
	std::string s1;
	std::string s2;
	bool afterOperator = false;
	for (size_t i = 0; i < line.size(); i++)  {
		if (line[i] == '=') {
			afterOperator = true;
		} else {
			if (afterOperator) {
				s2 += line[i];
			} else {
				s1 += line[i];
			}
		}
	}
	return std::make_pair (s1, s2);
}

bool isString (std::string input) {
	return ((input[0] == '\"') and (input[input.size()-1] == '\"'));
}

std::string getStr (std::string input) {
	return input.substr (1, input.size() -2);
}

bool varExists (std::string varName) {
	for (size_t i = 0; i < list_variables.size(); i++) {
		if (std::get <0> (list_variables[i]) == varName) {
			return true;
		}
	}
	return false;
}

int varIndex (std::string varName) {
	for (size_t i = 0; i < list_variables.size(); i++) {
		if (std::get <0> (list_variables[i]) == varName) {
			return i;
		}
	}
	return -1;
}

bool typeExists (std::string typeName) {
	for (size_t i = 0; i < types.size(); i++) {
		if (types[i] == typeName) {
			return true;
		}
	}
	return false;
}

int typeIndex (std::string typeName) {
	for (size_t i = 0; i < types.size(); i++) {
		if (types[i] == typeName) {
			return i;
		}
	}
	return -1;
}

bool isOperator (char op) {
	switch (op) {
		case '+':
		case '-':
		case '/':
		case '*':
		case '%':
			{
				return true;
				break;
			}
		default:
			{
				return false;
			}
	}
}

items getOperator (char op) {
	switch (op) {
		case '+':
			return items::OPERATOR_PLUS;
			break;
		case '-':
		case '/':
		case '*':
		case '%':
			break;
	}
}

	std::string removeComments (std::string input) {
	std::string outputString;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '#') {return outputString;}
		outputString += input[i];
	}
	return outputString;
}

std::string sanitizeFile (std::vector<std::string> file) { //takes a file, removes all spaces; nlines
							   //and tabulators; replacing them with a unicode 
							   //character that isnt used in text (0x07)
							   //thus creating a sole string
	char cchar;	
	std::string outputString;
	for (int i = 0; i < file.size(); i++) { 
		for (int j = 0; j < file[i].size(); j++) {
			cchar = file[i][j];
			if ((cchar == 0x09)) {  //if the string is a character 
				                //that has to be skipped
				cchar = 0x07;
			}
			if (cchar == ' ') {
				while (file[i][j -1] == ' ' && j < file[i].size()) {
					j++;
				}
				cchar = 0x07;
			}
			outputString += cchar;
		}
		outputString += 0x07; //for new lines. 
	}b
	std::cout << outputString << std::endl;
	return outputString; 
}

bool isDelim (char input) {
	switch (input) {

	}
}
