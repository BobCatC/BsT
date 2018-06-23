/*				CBsT.hpp
 *		This is the main file of BST
 */

#ifndef CBsT_hpp
#define CBsT_hpp
#include <queue>
#include <iostream>

template <class value_type, class comporator = std::less<value_type>>
class CBsT{
private:

#include "CBsTNode.hpp"
	
#include "CBsTTreeFunctions.hpp"
	
#include "CBsTStdIterators.hpp"
	
public:
	
#include "CBsTTraversalIterators.hpp"
	
	typedef template_iterator<const value_type> const_iterator;
	
	CBsT() { _root = nullptr; _size = 0; }
	CBsT(const CBsT& bst) { _root = copyTree(bst._root, nullptr); }
	~CBsT() { freeMemOfTree(_root); }
	
	
	const_iterator begin() const {
		CBsTNode* crt;
		crt = findMin(_root);
		return const_iterator(_root, crt, false, crt == nullptr ? true : false);
	}
	
	iteratorInorderDF beginInorderDF() const { return iteratorInorderDF(_root); }
	iteratorPreorderDF beginPreorderDF() const { return iteratorPreorderDF(_root); }
	iteratorPostorderDF beginPostorderDF() const { return iteratorPostorderDF(_root); }
	iteratorBF beginBF() const { return iteratorBF(_root); }
	
	// END iterator is usable for ALL times of iterators
	// (both usual and traversal iterators)
	const_iterator end() const {
		return const_iterator(_root, nullptr, false, true);
	}
	
	
	const_iterator insert(const value_type& value) {
		CBsTNode* node = findNode(_root, value);
		if(node == nullptr){
			node = insertNode(_root, value);
			if(_root == nullptr){
				_root = node;
			}
			++_size;
		}
		return const_iterator(_root, node);
	}
	
	void remove(const value_type& value){
		CBsTNode* node = findNode(_root, value);
		if(node != nullptr){
			_root = removeNodeByPointer(_root, node);
			--_size;
		}
	}
	
	const_iterator find(const value_type& value) const {
		bool fFound = true;
		CBsTNode* crt;
		crt = findNode(_root, value);
		fFound = crt == nullptr ? false : true;
		return const_iterator(_root, crt, false, !fFound);
	}
	
	void clear() {
		freeMemOfTree(_root);
		_root = nullptr;
		_size = 0;
	}
	
	
	bool empty() const { return (_size == 0); }
	size_t size() const { return (_size); }

private:
	CBsTNode* _root;
	size_t _size;
};

#endif /* CBsT_hpp */












