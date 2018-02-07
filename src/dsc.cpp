#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "helpers.h"
#include "processFlags.h"
#include "precompiler.h"
#include "lexer.h"

std::vector<std::string> list_variables;
std::vector<std::string> list_functions;
std::vector<std::string> code_variables;
std::vector<std::string> code_processes;

int main (int argc, char** args) {
	checkArgs (argc, args);
	std::vector<std::string> file = cacheFile (target);
	prec (file);
	lex (file);
}
