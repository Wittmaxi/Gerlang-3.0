char* target; 
char* out;

bool doesFileExist(const std::string file)
{
    std::ifstream infile {file};
    return infile.good();
}

void addTarget (char* _target) {
	std::cout << _target << std::endl;
	std::cout << std::string(target) << std::endl;
	if (doesFileExist(std::string(target))) {
		target = _target;
	} else {
		std::cout << "Datei " << _target << " wurde nicht gefunden. Compilation abgebrochen" << std::endl;
		exit(-1);
	}
}

void checkArgs (int argc, char** args) {
	for(int i = 1; i < argc; i++) {
		if (args[i] == "-a") {
			out = args[i];
		} else {
			addTarget (args[i]); 
		}
	}
	if (target == 0) {
		exit (-1);
	}
}