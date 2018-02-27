
class consOutOfRange () {
	virtual const char* what () const throw(
	{
		return "Cons Cells - An Item that is out of the range was searched for";
	}	
} COOR;


template <T> //the type to write about
	     //will mostly be string or tuple 
class Cell {	
	T& contained;
	Cell next = NULL;
	bool full = false;
	public:
	T& getElement () {
		return contained;
	}
	void append (T& element) { //append 
				   //to the next
				   //available
				   //cons-cell
		if (!(full)) {
			contained = element;
		} else {
			if (next == NULL) {
				next = Cell <T>;
			}
			next.append (element);
		}
	} 
	Cell getContainedCell () {
		return next;
	}
	T& getOnIndex (int index) { //get an item
				    //having a specific
				    //index in the tree
		if (index == 0) {
			return contained;
		} else {
			if (full) {
				return next.getOnIndex (index-1);
			} else {
				throw COOR;
			}
		}	
	}	
};


