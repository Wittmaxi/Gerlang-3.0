enum class items{
	DELIM, //delimitors like {, (, [
	//main function
	MAIN_FUNC, //anfang
	SCOPE_END, //ende
	//function declarations
	FUNCTION_1, //funktion
	FUNCTION_2, //ergibt
	//return statements
	RETURN_1,   //gebe
	RETURN_2,   //zurück
	//conditional statements
	COND, //wenn
	//loops
	LOOP, //solange
	//any identifier
	IDENT,
	//rvalues
	BOOL_RVAL,
	CHAR_RVAL,
	INT_RVAL,
	FLOAT_RVAL,
	//variable declarations
	VAR_DECL,
	NEW_LINE,
	VOID //returned in case of nonexistence of token in array
};

std::vector <std::string> types { //vector containing the item types. Will be used later when  
				  //allowing for custom datatypes
	"int",
	"double",
	"char",
	"bool"
};
