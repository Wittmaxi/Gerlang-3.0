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

class item {
public: 
	item (items _item) {
		held_item = _item;
	}

	item (items _item, std::string _code) {
		held_item = _item;
		aditional = _code;
	}

	item (items _item, std::string _code, item& _subitem) {
		held_item = _item;
		aditional = _code;
		subItems.push_back(&_subitem);
	}

	void addItem (item& _item) {
		subItems.push_back (&_item);
	}

	items held_item; 
	std::vector <item*> subItems;
	std::string aditional;	
};

std::vector <std::string> types {
	"int",
	"double",
	"char",
	"bool"
};