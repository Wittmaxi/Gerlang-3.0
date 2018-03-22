struct variable {
	std::string type;
	std::string name;
	bool isInit = false;
};

variable parseVariable () { //look for variables
	variable returnVar;
	if (getToken () == items::IDENT) { //the type of the var
		if (!(isInVec<std::string> (getTInfo(), scopes.end()->types) || isStandardType (getTInfo()))) { //the type of vars exists
			returnVar.type = returnTypeName(getTInfo());
			incPos ();
			if (!(getToken () == items::VAR_DECL)) {
				return returnVar;	
			}
			returnVar.isInit = true;
			incPos ();
			if (!(getToken () == items::IDENT)) { //the name
				wpe ("\"Identifizierer\" erwartet, stattdessen " + tts (getToken()) + " bekommen.");
			}
			for (auto i : scopes.end()->variables) { // to be changed later
				if (std::get <0> (i) == getTInfo ()) {
					wpe ("Variablenname " + getTInfo() + " ist schon benutzt.");
				}
			}
			returnVar.name = getTInfo ();		
		} else {
			wpe ("Dateityp " + getTInfo() + " existiert nicht.");
		}
		incPos();
		return returnVar; 
	}
	//if its not a variable
	return returnVar;

}

//std::string parseRvalCode
