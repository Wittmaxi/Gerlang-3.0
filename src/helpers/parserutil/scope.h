class function
{
  public:
	function(std::string name_, std::string outtype_)
	{
		name = name_;
		outtype = outtype_;
	}
	std::string name;
	std::string outtype;
	std::vector<std::string> inputs;
};

struct scope
{
	scope()
	{
	}
	scope(const scope &other, const bool i)
	{
		types = other.types;
		variables = other.variables;
		functions = other.functions;
	}
	void addVars(std::vector<std::tuple<std::string, std::string>> vars)
	{
		for (const auto &i : vars)
			variables.push_back(i);
	}
	void addVar(std::tuple<std::string, std::string> var)
	{
		variables.push_back(var);
	}
	bool varExists(std::string name)
	{
		for (const auto& i : variables)
			if (std::get<0>(i) == name)
				return true;
		return false;
	}
	bool funcExists(std::string name)
	{
		for (auto i : functions)
			if (i.name == name)
				return true;
		return false;
	}
	std::string getType(std::string name)
	{
		if (varExists(name))
			return varType(name);
		else if (funcExists(name))
			return funcType(name);
		else 
			throw "Neither Var nor Func name Found -- internal problem";
	}
	std::string varType(std::string name)
	{ //assuming the var exists
		for (auto i : variables)
			if (std::get<0>(i) == name)
				return std::get<1>(i);
	}
	std::string funcType(std::string name)
	{
		for (auto i : functions)
			if (i.name == name)
				return i.outtype;
	}
	function getFunc(std::string name)
	{
		for (auto i : functions)
			if (i.name == name)
				return i;
	}
	std::vector<std::string> types;								 
	std::vector<std::tuple<std::string, std::string>> variables; 
	std::vector<function> functions;							 
	bool anynome;
};
