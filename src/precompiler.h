size_t counter = 0;

void handleInclude (std::vector<std::string>& input) {
	if (input[counter].substr (0, 10) == "~einfügen") {
		std::string fileName = input[counter].substr (10, input [counter].size() -10);
		input[counter].erase (counter, 1);
		fileName = sanitize (fileName);
		if (doesFileExist (fileName)) {
			std::vector<std::string> toAppend = cacheFile (fileName.c_str());
			input.insert (input.begin() + counter, toAppend.begin(), toAppend.end());
		} else {
			std::cout << "Präcompiler | Zeile " << counter << " | Datei " << fileName << " wurde nicht gefunden " << std::endl;
		}
		std::cout << fileName << std::endl;
	}
}

void prec (std::vector<std::string>& input) {
	counter = 0; //prolly not needed
	for (; counter < input.size(); counter++) {
		handleInclude (input);
	}
} 