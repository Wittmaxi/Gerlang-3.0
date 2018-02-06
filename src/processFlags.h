std::vector<char*> targets; 
char* out;

bool doesFileExist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

void addTarget (char* target) {
	if (doesFileExist(target)) {
		targets.push_back (target);
	} else {
		std::cout << "Datei " << target << " wurde nicht gefunden. Compilation abgebrochen" << std::endl;
		exit(-1);
	}
}

void checkArgs (int argc, char** args) {
	for(int i = 0; i < argc; i++) {
		if (args[i] == "-a") {
			out = args[i];
		} else {
			addTarget (args[i]); 
		}

	}
}