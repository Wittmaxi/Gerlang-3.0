class scope {
public: //since i'm the only user of scope, it might as well be public
	scope () {

	}
	scope (const scope& other, const bool i) { //copy all the variables/functions etc
						   // the bool is just so that the scope function 
						   // triggered by normal copying of scope 
		types = other.types;
		variables = other.variables;
	}
	void addVars (std::vector<std::tuple<std::string, std::string>> vars) { 
		//takes in a vector of <variablename, typedenominator>
		for (auto i : vars) {
			variables.push_back (i);
		}
	}
	void addVar (std::tuple <std::string, std::string> var) {
		variables.push_back (var);
	}
	bool varExists (std::string name) { //does a specific variable already exist?
		for (auto i : variables) {
			if (std::get <0> (i) == name) {
				return true;
			}
		} 
		return false;
	}

	std::string getVarType (std::string name) {
		for (auto i : variables) {
			if (std::get <0> (i) == name) {
				return std::get<1> (i);
			}
		} 
		return "";
	}
	std::vector<std::string> types; //important for later	
	std::vector<std::tuple <std::string, std::string>> variables;
	bool anynome;
};
