size_t counter = 0;

void handleInclude (std::vector<std::string>& input) {
	if (input[counter].substr (0, 10) == "~einfügen") {
		std::string fileName = input[counter].substr (10, input [counter].size() -10);
		input.erase (input.begin() + counter);
		fileName = sanitize (fileName);
		if (doesFileExist (fileName)) {
			std::vector<std::string> toAppend = cacheFile (fileName.c_str());
			input.insert (input.begin() + counter, toAppend.begin(), toAppend.end());
		} else {
			std::cout << "Präcompiler | Zeile " << counter << " | Datei " << fileName << " wurde nicht gefunden " << std::endl;
		}
	}
}

void handleDefine (std::vector<std::string>& input) {
	if (input[counter].substr (0, 11) == "~definieren") {
		std::cout << "wird definiert" << std::endl;
		std::string definition = input[counter].substr (11, input [counter].size() -11);
		definition = sanitize (definition);
		std::pair<std::string, std::string> assign = findAssignements (definition);
		std::string s1 = std::get <0> (assign);
		std::string s2 = std::get <1> (assign);
		if (isString (s2)) {
			generateVar (s1, getStr(s2), 2, true);
		}
	}
}

void prec (std::vector<std::string>& input) {
	counter = 0; //prolly not needed
	for (; counter < input.size(); counter++) {
		handleInclude (input);
		handleDefine (input);
	}
	for (size_t i = 0; i < input.size(); i++) {
		std::cout << input[i] << std::endl;
	}
}