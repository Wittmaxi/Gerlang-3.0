int counter = 0;

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

void handlePrint (std::vector <std::string>& input) {
	if (input[counter].substr (0, 10) == "~schreiben") {
		if (varExists(sanitize(input[counter].substr (11, input[counter].size() - 11)))) {
			code_mainFunction.push_back ("std::cout <<" + input[counter].substr (11, input[counter].size() - 11) + "<<std::endl;");	
			addInclude ("iostream");		
		} else {
			code_mainFunction.push_back ("std::cout <<\"" + input[counter].substr (11, input[counter].size() - 11) + "\"<<std::endl;");
			addInclude ("iostream");
		}
	}
}

void handleDefine (std::vector<std::string>& input) {
	if (input[counter].substr (0, 11) == "~definieren") {
		std::string definition = input[counter].substr (11, input [counter].size() -11);
		input.erase (input.begin() + counter);
		definition = sanitize (definition);
		std::pair<std::string, std::string> assign = findAssignements (definition);
		std::string s1 = std::get <0> (assign);
		std::string s2 = std::get <1> (assign);
		if (isString (s2)) {
			if (getStr(s2).size() > 1) {
				generateVar (s1, s2, 2, true, true, s2.size());
			} else {
				generateVar (s1, s2, 2, true, false, 0);
			}
		} else {
				generateVar (s1, getStr(s2), 0, true, false, s2.size());			
		}
	}
}

void prec (std::vector<std::string>& input) {
	counter = 0; //prolly not needed
	for (; counter < input.size(); counter++) {
		std::cout << input[counter] << std::endl;
		if (input[counter] != "") {
			handleDefine (input);
			handlePrint (input);
			handleInclude (input);
		}
	}
}