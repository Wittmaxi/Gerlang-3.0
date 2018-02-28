class scope {
	void addVars (std::vector<std::tuple<std::string, std::string>> vars) { 
		//takes in a vector of <variablename, typedenominator>
		for (auto i : vars) {
			variables.push_back (i);
		}
	}
	void addVar (std::tuple <std::string, std::string> var) {
		variables.push_back (i);
	}
	bool varExists (std::string name) { //does a specific variable already exist?
		for (auto i : variables) {
			if (std::get <0> (i) == name) {
				return true;
			}
		} 
		return false;
	}
	
	std::vector<std::tuple <std::string, std::string>> variables;
	bool anynome;
	std::vector <std::string> code;
};
