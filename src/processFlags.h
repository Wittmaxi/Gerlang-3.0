char* target; 
char* out;
bool genBench = false;

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
		std::string current (args[i]);
		std::cout << current << std::endl;
		if (current == "-a") {
			out = args[++i];
		} else if (current == "-genBenchFile") {
		 	genBench = true;      
		} else {
			addTarget (args[i]); 
		}
	}
	if (target == 0) {
		std::cout << "DSC | Keine Eingabedatei gefunden" << std::endl;
		exit (-1);
	}
}
