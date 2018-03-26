void writeToOutFile () {
	std::ofstream outFile (std::string(out), std::ofstream::out);
	for (auto i : totalCode) {
		outFile << i << std::endl;
	}
}

void finalize () {
	writeToOutFile();
}

void genStressTest () {
	std::ofstream outFile ("./test/main.ds", std::ofstream::out);
	for (int i = 0; i < 100000; i++) {
		outFile << "funktion _" << i << "_hallo () ergibt ganzzahl" << std::endl;
		outFile << "ende" << std::endl;
	}
}
