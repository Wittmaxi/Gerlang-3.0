void generateVar (std::string name, std::string content, int typeIndex, bool isConst, bool isArray) {
	std::string code;
	list_variables.push_back (make_pair (name, typeIndex));
	if (isConst) {
		code += "const";
	}
	code += name + "=";
	if (isArray) {
		code += "[]";
	}
	code += content;
	code_variables.push_back (code);
}