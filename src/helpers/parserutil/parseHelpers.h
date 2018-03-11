struct variable {
	std::string type;
	std::string name;
};

variable parseVariable () { //look for variables
	variable returnVar;
	if (!(getToken () == items::IDENT)) { //the type of the var
		if (!(isInVec<std::string> (getTInfo(), currentScope.types))) { //the type of vars exists
			
		}
	}
}

