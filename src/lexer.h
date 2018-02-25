std::vector <std::tuple <items, std::string> > output;
std::string file;
int position;

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
	switch (file[position]) {
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
			outputStr += file [position];	
			break;
		}
	}
	position++;
	return outputStr;
}

void evalExpression (std::string expression) {
	switch (expression[0]) {
		case 0x07: break;
		//to check tomorrow	
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
