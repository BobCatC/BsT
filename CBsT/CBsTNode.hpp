#ifndef CBsTNode_h
#define CBsTNode_h

/* 	 Always is included into CBsT.hpp
 *	( inside class CBsT<type_name, comporator> )
 */

private:

	class CBsTNode;

	typedef CBsTNode CRootNode;
	typedef CBsTNode CParentNode;
	typedef CBsTNode CLeftChildNode;
	typedef CBsTNode CRightChildNode;


	class CBsTNode{
	public:
		CBsTNode(const value_type& value,
				 CParentNode* parent_pointer = nullptr,
				 CLeftChildNode* left_child_pointer = nullptr,
				 CRightChildNode* right_child_pointer = nullptr) :
		_value(value),
		_parent_pointer(parent_pointer),
		_left_child_pointer(left_child_pointer),
		_right_child_pointer(right_child_pointer) { }
	
		void setValue(const value_type& value) { _value = value; }
		void setParent(CParentNode* parent_pointer) { _parent_pointer = parent_pointer; }
		void setLeftChild(CLeftChildNode* left_child_pointer) { _left_child_pointer = left_child_pointer; }
		void setRightChild(CRightChildNode* right_child_pointer) { _right_child_pointer = right_child_pointer; }
	
		const value_type& cgetValue() const { return _value; }
		value_type& getValue() { return _value; }
	
		const value_type* cgetValuePointer() const { return &_value; }
		value_type* getValuePointer() { return &_value; }
	
		bool isRoot() const { return (_parent_pointer == nullptr); }
		bool hasLeftChild() const { return (_left_child_pointer != nullptr); }
		bool hasRightChild() const { return (_right_child_pointer != nullptr); }
		bool isLeftChild() const { return (this == _parent_pointer->getLeftChild()); }
	
		CParentNode* getParent() const { return _parent_pointer; }
		CLeftChildNode* getLeftChild() const { return _left_child_pointer; }
		CRightChildNode* getRightChild() const { return _right_child_pointer; }
	
		bool operator==(const CBsTNode& other) { return (_value == other._value); }
		bool operator!=(const CBsTNode& other) { return !(*this == other); }
	
		bool operator>(const CBsTNode& other) { comporator comp; return (comp(_value, other._value)); }
		bool operator<=(const CBsTNode& other) { return !(*this > other); }
	
		bool operator<(const CBsTNode& other) { return ((*this <= other) && (*this != other)); }
		bool operator>=(const CBsTNode& other) { return !(*this < other); }
	
	private:
	
		value_type _value;
	
		CParentNode* _parent_pointer;
		CLeftChildNode* _left_child_pointer;
		CRightChildNode* _right_child_pointer;
	};

#endif /* CBsTNode_h */











