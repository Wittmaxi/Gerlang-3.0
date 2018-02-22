enum class items{
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
	item (items _item, std::string _code) {
		held_item = _item;
		code = _code;
	}

	item (items _item, std::string _code, item& _subitem) {
		held_item = _item;
		code = _code;
		subItem.push_back(_subitem);
	}

	addItem (items& _item) {
		subItems.push_back (_item)
	}

	items held_item; 
	std::vector <item*> subItems = NULL;
	std::string code;	
};

std::vector <std::string> types {
	"int",
	"double",
	"char",
	"bool"
};