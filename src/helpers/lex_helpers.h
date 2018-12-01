std::pair <std::string, std::string> findAssignements (std::string line) {
	std::string s1;
	std::string s2;
	bool afterOperator = false;
	for (size_t i = 0; i < line.size(); i++) 
		if (line[i] == '=') 
			afterOperator = true;
		else 
			if (afterOperator)
				s2 += line[i];
			else
				s1 += line[i];
	return std::make_pair (s1, s2);
}

bool isString (std::string input) {
	return ((input[0] == '\"') and (input[input.size()-1] == '\"'));
}

std::string getStr (std::string input) {
	return input.substr (1, input.size() -2);
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

std::string sanitizeFile (std::vector<std::string> file) {
	char cchar;	
	std::string outputString;
	for (int i = 0; i < file.size(); i++) { 
		for (int j = 0; j < file[i].size(); j++) {
			cchar = file[i][j];
			if ((cchar == 0x09)) 
				cchar = 0x07;
			else if (cchar == ' ')
				cchar = 0x07;
			else if (cchar == '#' || cchar == '~')
				break;
			outputString += cchar;
		}
		outputString += 0x06;
	}
	std::cout << outputString << std::endl;
	return outputString; 
}

bool isBool (std::string val) {
	if ((val == "wahr") || (val == "falsch"))
		return true;
	return false;
}

bool isInt (std::string val) {
	for (int i = 0; i < val.size(); i++)
		if ((val[i] > '9') || (val[i] < '0'))
			return false;	
	return (val.size() > 0) ? true : false;
}

bool isFloat (std::string val) {
	bool hasPoint = false;
	for (int i = 0; i < val.size(); i++) {
		if (val[i] == '.') {
			if (hasPoint == true) {
				return false;
			} else {
				hasPoint = true;
			}
		} else if ((val[i] > '9') || (val[i] < '0')) { //check if character value doesnt 
							  //correspond with normal character values
							  //for integers/numbers
			return false;	
		}
	}
	return hasPoint;
}

std::string tts (items toPrint) { //token to string
	items token = toPrint;
	std::string typeN;
	if (token == items::DELIM)
		typeN = "Abgrenzer";
	 else if (token == items::MAIN_FUNC) 
		typeN = "Haupt-Funktion";
	 else if (token == items::FUNCTION_1)
		typeN = "Funktion";
	 else if (token == items::FUNCTION_2)
		typeN = "Funktionsrückgabe";
	 else if (token == items::RETURN_1) 
	 	typeN = "Rückgabe 1";
	 else if (token == items::RETURN_2)
		typeN = "Rückgabe 2";
	 else if (token == items::COND) 
		typeN = "Vergleich";
	 else if (token == items::LOOP)
		typeN = "Schleife";
	 else if (token == items::IDENT)
		typeN = "Identifizierer";
	 else if (token == items::BOOL_RVAL)
		typeN = "Booleanwert";
	 else if (token == items::CHAR_RVAL)
		typeN = "Charakterwert";
	 else if (token == items::INT_RVAL) 
	 	typeN = "Ganzzahlwert";
	 else if (token == items::FLOAT_RVAL)
		typeN = "Fliesskommawert";
	 else if (token == items::VAR_DECL) 
	 	typeN = "Variablendeklaration";
	 else if (token == items::SCOPE_END)
		typeN = "Blockende";
	 else if (token == items::NEW_LINE) 
		typeN = "Neue Zeile";
	 else if (token == items::VOID) 
		typeN = "Nichts";
	
	return typeN;
}


std::ostream& operator<< (std::ostream& os, std::tuple<items, std::string> toPrint) {
	items token = std::get <0> (toPrint);
	os << "token: " << tts (token) << " - additional info: " << std::get <1> (toPrint); 
	return os;
}









