#include <string>
#include <vector>

bool doesFileExist(const std::string file)
{
    std::ifstream infile {file};
    return infile.good();
}

std::vector<std::string> cacheFile (char* target) {
	std::ifstream file {std::string (target)};
	std::vector<std::string> output;
	while (!(file.eof ())) {
		std::string line;
		getline (file, line);
		output.push_back (line);
	}
	return output;
}

void sanitize (std::string& input) {
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == 10) {
			input.erase (i, 1);
		}
	}
	std::cout << input << std::endl;
}
