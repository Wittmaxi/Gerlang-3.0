bool doesFileExist(const std::string file)
{
	std::ifstream infile{file};
	return infile.good();
}

std::vector<std::string> cacheFile(const char *target)
{
	std::ifstream file{std::string(target)};
	std::vector<std::string> output;
	while (!(file.eof()))
	{
		std::string line;
		getline(file, line);
		output.push_back(line);
	}
	return output;
}

std::string sanitize(std::string input)
{
	std::string retStr;
	for (int i = 0; i < input.size(); i++)
		if (!(input[i] == 32 || input[i] == 9))
			retStr += input[i];
	return retStr;
}

void printVect(std::vector<std::string> T)
{
	for (auto i : T)
		std::cout << i << std::endl;
}

template <typename T>
bool isInVec(T item, std::vector<T> toFindIn)
{
	for (T i : toFindIn)
		if (i == item)
			return true;
	return false;
}

bool isStandardType(std::string name)
{
	if (name == "boolesche" ||
		name == "ganzzahl" ||
		name == "charakter" ||
		name == "fliesskomma")
		return true;
	return false;
}

std::string returnTypeName(std::string name)
{
	if (isStandardType(name))
		if (name == "boolesche")
			return std::string("bool");
		else if (name == "ganzzahl")
			return std::string("int");
		else if (name == "charakter")
			return std::string("char");
		else if (name == "fliesskomma")
			return std::string("float");
	return name;
}
