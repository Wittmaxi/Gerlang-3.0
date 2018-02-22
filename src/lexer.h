std::vector <item> lexer_output; 
std::vector<std::string> *file;
item begin_of_file (items::BEGIN_OF_FILE, "");
int position;

void findMainFunction () {
	if (true);
}

void findFunction () {
	if (true) {

	}
}

void find () {
	for (; position < file->size(); position++) {
		findFunction ();
	}
}

void lex (std::vector<std::string>& input) {
	file = &input;
	find ();
}