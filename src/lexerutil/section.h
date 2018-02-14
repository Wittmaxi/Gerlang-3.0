class context {
public:
	std::vector<std::pair<std::string, int>> variables;
	std::vector<context> subcontexts;
};