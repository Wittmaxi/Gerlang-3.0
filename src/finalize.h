void writeToOutFile () {
	std::ofstream outFile (std::string(out), std::ofstream::out);
	for (auto i : totalCode) {
		outFile << i << std::endl;
	}
}

void finalize () {
	writeToOutFile();
}
