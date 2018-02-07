#include <string>
#include <vector>

bool doesFileExist(const std::string file)
{
    std::ifstream infile {file};
    return infile.good();
}

std::vector<std::string> cacheFile (const char* target) {
	std::ifstream file {std::string (target)};
	std::vector<std::string> output;
	while (!(file.eof ())) {
		std::string line;
		getline (file, line);
		output.push_back (line);
	}
	return output;
}

std::string sanitize (std::string input) {
	std::string retStr;
	for (int i = 0; i < input.size(); i++) {
		std::cout << " Char " << i << " : " << (int) input[i] << std::endl;
		if (input[i] == 32 || input[i] == 9) {
		} else {
			retStr += input[i];
		}
	}
	std::cout << retStr << std::endl;
	return retStr;
}
