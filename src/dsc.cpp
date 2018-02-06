#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "processFlags.h"
#include "precompiler.h"
#include "lexer.h"
#include "helpers.h"

int main (int argc, char** args) {
	checkArgs (argc, args);
	for (size_t i = 0; i < targets.size(); i++) {

		prec (targets[i]);
		lex (targets[i]);
	}
}
