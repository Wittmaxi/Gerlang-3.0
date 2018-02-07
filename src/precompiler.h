size_t counter = 0;

void handleInclude (std::vector<std::string>& input) {
	if (input[counter].substr (0, 10) == "~einfügen") {
		std::string fileName = input[counter].substr (10, input [counter].size() -10);
		sanitize (fileName);
		std::cout << fileName << std::endl;
	}
}

void prec (std::vector<std::string>& input) {
	for (; counter < input.size(); counter++) {
		handleInclude (input);
	}
} 