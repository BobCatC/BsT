#ifndef CBsTStdIterators_h
#define CBsTStdIterators_h

/* 	 Always is included into CBsT.hpp
 *	( inside class CBsT<type_name, comporator> )
 */

template<class iterator_value_type>
class template_iterator{
protected:
	CBsTNode* _root;
	CBsTNode* _node;
	bool _fIsAfterLastNode;
	bool _fIsPrevFirstNode;
	
	void findNext() {
		if(!_fIsAfterLastNode){
			if(_fIsPrevFirstNode){
				_node = findMin(_root);
				if(_node == nullptr){
					_fIsAfterLastNode = true;
				}
				_fIsPrevFirstNode = false;
			}
			else{
				_node = findNextNode(_root, _node);
				if(_node == nullptr){
					_fIsAfterLastNode = true;
				}
			}
		}
	}
	void findPrev(){
		if(!_fIsPrevFirstNode){
			if(_fIsAfterLastNode){
				_node = findMax(_root);
				if(_node != nullptr){
					_fIsAfterLastNode = false;
				}
			}
			else{
				_node = findPrevNode(_root, _node);
				if(_node == nullptr){
					_fIsPrevFirstNode = true;
				}
			}
		}
	}
	
	typedef template_iterator<iterator_value_type> self_type;
	
public:
	template_iterator(CBsTNode* root_node_pointer,
					  CBsTNode* node_pointer,
					  const bool fIsPrevFirst = false,
					  const bool fIsAfterLast = false) :
	_root(root_node_pointer),
	_node(node_pointer),
	_fIsAfterLastNode(fIsAfterLast),
	_fIsPrevFirstNode(fIsPrevFirst) {}
	
	self_type operator++(int junk) { self_type it = *this; findNext(); return it; }
	self_type operator++() { findNext(); return *this; }
	
	self_type operator--(int junk) { self_type it = *this; findPrev(); return it; }
	self_type operator--() { findPrev(); return *this; }
	
	iterator_value_type& operator*() { return _node->getValue(); }
	iterator_value_type* operator->() { return _node->getValuePointer(); }
	
	bool operator==(const self_type& other) {
		if(_fIsPrevFirstNode ^ other._fIsPrevFirstNode ||
		   _fIsAfterLastNode ^ other._fIsAfterLastNode)
			return false;
		
		else return
			(_fIsPrevFirstNode && other._fIsPrevFirstNode) ||
			(_fIsAfterLastNode && other._fIsAfterLastNode) ||
			(*_node == *other._node); }
	
	bool operator!=(const self_type& other) { return !(*this == other); }
	
	bool fIsEndIterator() const { return (_fIsAfterLastNode); }
};


#endif /* CBsTStdIterators_h */
