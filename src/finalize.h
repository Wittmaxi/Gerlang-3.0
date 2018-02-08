std::vector <std::string> finalCode;

void genMain () {
	finalCode.push_back ("int main () {");
	finalCode.insert (finalCode.end(), code_mainFunction.begin(), code_mainFunction.end());	
	finalCode.push_back ("}");
}

void writeToOutFile () {
	std::ofstream outFile (std::string(out), std::ofstream::out);
	for (auto i : finalCode) {
		outFile << i << std::endl;
	}
}

void finalize () {
	finalCode.insert (finalCode.end(), code_includes.begin(), code_includes.end());
	finalCode.insert (finalCode.end(), code_variables.begin(), code_variables.end());
	finalCode.insert (finalCode.end(), code_processes.begin(), code_processes.end());
	genMain();
	writeToOutFile();
	printVect (finalCode);
}
