#include <string>
#include <vector>

std::vector<std::string> cacheFile (char* target) {
	std::ifstream file {std::string (target)};
	std::vector<std::string> output;
	while (!(file.eof ())) {
		std::string line;
		file >> line;
		output.push_back (line);
	}
	return output;
}