std::vector <item> lexer_output; 
std::string accum = ""; //accumulates the parse

void addItem (item _input) {
	accum = "";
	lexer_output.push_back (_input);
}

void find () {
	accum = sanitize(accum);
	std::cout << "accum = " << accum << std::endl;
	if (accum == "anfang") {
		addItem (item(items::BEGIN_FUNC, accum));
	}
	if (accum == "ende") {
		addItem (item(items::END, accum));
	}
	if (isOperator(accum.c_str()[0])) {
		addItem (item(getOperator (accum.c_str()[0]), accum));
	}
}

void lex (std::vector<std::string>& input) {
	for (auto i : input) {
		for (int j = 0; j < i.size(); j++) {
			accum += i[j];
			find ();
		}
	}
}