#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <tuple>
#include <exception>
#include "lexerutil/itemTypes.h"
#include "helpers.h"
#include "processFlags.h"
#include "precompiler.h"
#include "lexer.h"
#include "parser.h"
#include "finalize.h"

int main (int argc, char** args) {
	checkArgs (argc, args);
	std::vector<std::string> file = cacheFile (target);
	prec (file);
	lex (file);
}
