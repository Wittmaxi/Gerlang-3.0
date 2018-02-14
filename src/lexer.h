std::vector <items> output; 
std::string accum = ""; //accumulates the parse

void find () {
	if () {
		
	}
}

void lex (std::vector<std::string>& input) {
	for (auto i : input) {
		for (int j = 0; j < i.size(); j++) {
			accum += std::string (i[j]);
		}
	}
}