#ifndef CBsTNode_h
#define CBsTNode_h

/* 	 Always is included into CBsT.hpp
 *	( inside class CBsT<type_name, comporator> )
 */

class CBsTNode{
public:
	CBsTNode(const value_type& value,
			 CBsTNode* parent_pointer = nullptr,
			 CBsTNode* left_child_pointer = nullptr,
			 CBsTNode* right_child_pointer = nullptr) :
	_value(value),
	_parent_pointer(parent_pointer),
	_left_child_pointer(left_child_pointer),
	_right_child_pointer(right_child_pointer) { }
	
	void setValue(const value_type& value) { _value = value; }
	void setParent(CBsTNode* parent_pointer) { _parent_pointer = parent_pointer; }
	void setLeftChild(CBsTNode* left_child_pointer) { _left_child_pointer = left_child_pointer; }
	void setRightChild(CBsTNode* right_child_pointer) { _right_child_pointer = right_child_pointer; }
	
	const value_type& cgetValue() const { return _value; }
	value_type& getValue() { return _value; }
	
	const value_type* cgetValuePointer() const { return &_value; }
	value_type* getValuePointer() { return &_value; }
	
	bool fIsRoot() const { return (_parent_pointer == nullptr); }
	bool fHasLeftChild() const { return (_left_child_pointer != nullptr); }
	bool fHasRightChild() const { return (_right_child_pointer != nullptr); }
	bool fIsLeftChild() const { return (this == _parent_pointer->getLeftChild()); }
	
	CBsTNode* getParent() const { return _parent_pointer; }
	CBsTNode* getLeftChild() const { return _left_child_pointer; }
	CBsTNode* getRightChild() const { return _right_child_pointer; }
	
	bool operator==(const CBsTNode& other) { return (_value == other._value); }
	bool operator!=(const CBsTNode& other) { return !(*this == other); }
	
	bool operator>(const CBsTNode& other) { comporator comp; return (comp(_value, other._value)); }
	bool operator<=(const CBsTNode& other) { return !(*this > other); }
	
	bool operator<(const CBsTNode& other) { return ((*this <= other) && (*this != other)); }
	bool operator>=(const CBsTNode& other) { return !(*this < other); }
	
private:
	
	value_type _value;
	
	CBsTNode* _parent_pointer;
	CBsTNode* _left_child_pointer;
	CBsTNode* _right_child_pointer;
};

#endif /* CBsTNode_h */
