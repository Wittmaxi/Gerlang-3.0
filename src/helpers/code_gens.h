void generateVar (std::string name, std::string content, int typeIndex, bool isConst, bool isArray, int arraySize = 0) {
	std::string code;
	list_variables.push_back (make_pair (name, typeIndex));
	std::cout << list_variables.size() << std::endl;
	if (isConst) {
		code += "const ";
	}
	code += types[typeIndex] + " " + name;
	if (isArray) {
		code += "[" + std::to_string(arraySize) + "]";
	}
	code += " = " + content + ";";
	code_variables.push_back (code);
}

void addInclude (std::string include) {
	if (!(isInVec <std::string> (include, list_includes))) {
		list_includes.push_back (include);
		code_includes.push_back ("#include <" + include + ">");
	}
}