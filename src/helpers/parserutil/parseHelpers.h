bool operator==(std::tuple<items, std::string> _1, items _2)
{
	return (std::get<0>(_1) == _2);
}
bool operator!=(std::tuple<items, std::string> _1, items _2)
{
	return (std::get<0>(_1) != _2);
}

bool identAlreadyExists(std::string identName)
{
	for (auto i : scopes[scopes.size() - 1].variables)
		if (std::get<0>(i) == identName)
			return true;
	for (auto i : scopes[scopes.size() - 1].functions)
		if (i.name == identName)
			return true;
	return false;
}

bool identValid(std::string identName)
{
	return !(identAlreadyExists(identName));
}

struct variable
{
	std::string type;
	std::string name;
	bool isInit = false;
};

bool isRval(items item)
{
	if (item == items::BOOL_RVAL || item == items::CHAR_RVAL || item == items::INT_RVAL || item == items::FLOAT_RVAL)
		return true;
	return false;
}

variable parseVariable()
{
	variable returnVar;
	if (getToken() == items::IDENT)
	{
		if (isInVec<std::string>(getTInfo(), scopes[scopes.size() - 1].types) || isStandardType(getTInfo()))
		{
			returnVar.type = returnTypeName(getTInfo());
			incPos();
			if (!(getToken() == items::VAR_DECL))
				return returnVar;
			returnVar.isInit = true;
			incPos();
			if (!(getToken() == items::IDENT))
				wpe("\"Identifizierer\" erwartet, stattdessen " + tts(getToken()) + " bekommen.");
			if (!identValid(getTInfo()))
				wpe("Variablenname " + getTInfo() + " ist ungültig oder schon benutzt.");
			returnVar.name = getTInfo();
		}
		else
			return returnVar;
		incPos();
		return returnVar;
	}
	return returnVar;
}

void getLineTokens()
{
	currentLine.clear(); //empty the last line
	while (lexerTokens[positionInLexerToken] != items::NEW_LINE)
	{
		currentLine.push_back(lexerTokens[positionInLexerToken]);
		positionInLexerToken++;
	}
	++positionInLexerToken;
	positionInLine = 0;
}
