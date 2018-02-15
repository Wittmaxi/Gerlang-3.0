std::vector <items> output; 
std::vector <std::string> rvals;
std::vector <std::string> varnames;
std::string accum = ""; //accumulates the parse

void find () {
	if (accum == "anfang") {
		output.push_back (items::BEGIN_FUNC);
	}
	if (accum == "ende") {
		output.push_back (items::END);
	}
	if (isOperator(accum [accum.size() -1])) {
		output.push_back (items::RVAL);
		output.push_back (getOperator (accum [accum.size() -1]));
		rvals.push_back (accum.substr (0, accum.size() -2));
	}
}

void lex (std::vector<std::string>& input) {
	for (auto i : input) {
		for (int j = 0; j < i.size(); j++) {
			accum += i[j];
		}
	}
}