#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

std::vector<std::pair<std::string, int>> list_variables;
std::vector<std::pair<std::string, int>> list_functions;
std::vector<std::pair<std::string, int>> customTypeIndexes;
std::vector<std::string> list_includes;
std::vector<std::string> code_includes;
std::vector<std::string> code_variables;
std::vector<std::string> code_processes;
std::vector<std::string> code_mainFunction;

#include "lexerutil/itemTypes.h"
#include "helpers.h"
#include "processFlags.h"
#include "precompiler.h"
#include "lexer.h"
#include "finalize.h"

int main (int argc, char** args) {
	checkArgs (argc, args);
	std::vector<std::string> file = cacheFile (target);
	prec (file);
	lex (file);
	std::cout << "hello #hi -> " << removeComments (std::string("hello #hi"));
	std::cout << "hello -> " << removeComments (std::string("hello"));
	finalize();
}