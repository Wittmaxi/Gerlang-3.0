enum class items{
	BEGIN_OF_FILE,
	BEGIN_FUNC,//the entire document - more like a "wrapper"
	END,
	FUNCTION_DECL,
	FUNC_TYPE_1,
	FUNCT_TYPE_2,
	RVAL,
	OPERATOR_PLUS
};

std::vector <std::string> types { //vector containing the item types. Will be used later when  
				  //allowing for custom datatypes
	"int",
	"double",
	"char",
	"bool"
};
