char* target; 
char* out;


void addTarget (char* _target) {
	std::string filename (_target);
	if (doesFileExist(filename)) {
		target = _target;
	} else {
		std::cout << "DSC | Datei " << _target << " wurde nicht gefunden. Compilation abgebrochen" << std::endl;
		exit(-1);
	}
}

void checkArgs (int argc, char** args) {
	for(int i = 1; i < argc; i++) {
		std::cout << args[i] << std::endl;
		if (args[i] == "-a") {
			out = args[++i];
		} else {
			addTarget (args[i]); 
		}
	}
	if (target == 0) {
		std::cout << "DSC | Keine Eingabedatei gefunden" << std::endl;
		exit (-1);
	}
}