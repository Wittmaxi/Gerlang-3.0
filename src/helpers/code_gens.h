void generateVar (std::string name, std::string content, int typeIndex, bool isConst, bool isArray) {
	std::string code;
	list_variables.push_back (make_pair (name, typeIndex));
	if (isConst) {
		code += "const ";
	}
	code += types[typeIndex];
	if (isArray) {
		code += "[]";
	}
	code += " " + name;
	code += " = " + content;
	code_variables.push_back (code);
}

void addInclude (std::string include) {
	if (!(isInVec <std::string> (include, list_includes))) {
		list_includes.push_back (include);
		code_includes.push_back ("#include <" + include + ">");
	}
}