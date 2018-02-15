enum class items{
	BEGIN_FUNC,//the entire document - more like a "wrapper"
	END,
	FUNCTION_DECL,
	FUNC_TYPE_1,
	FUNCT_TYPE_2,
	RVAL,
	OPERATOR_PLUS
};

std::vector <std::string> types {
	"int",
	"double",
	"char",
	"bool"
};