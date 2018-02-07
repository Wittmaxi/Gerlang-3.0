#include <string>
#include <vector>

std::pair <std::string, std::string> findAssignements (std::string line) {
	std::string s1;
	std::string s2;
	bool afterOperator;
	for (size_t i = 0; i < line.size(); i++)  {
		if (&line[i] == "=") {
			afterOperator != afterOperator;
		} else {
			if (afterOperator) {
				s1 += line[i];
			} else {
				s2 += line[i];
			}
		}
	}
	return std::make_pair (s1, s2);
}

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
		if (input[i] == 32 || input[i] == 9) {
		} else {
			retStr += input[i];
		}
	}
	return retStr;
}
