#ifndef CBsTTraversalIterators_h
#define CBsTTraversalIterators_h
/*
 	It's inside class
 	CBsT<value_type, comporator>
*/
#define crt_node iterator_traversal::_crt

class iterator_traversal{
protected:
	CBsTNode* _crt;
	bool _fIsAfterLastNode;
	virtual void findNext() { }
	typedef iterator_traversal self_type;
	
	bool next() {
		if(_crt == nullptr)
			return false;
		findNext();
		return ( _crt != nullptr );
	}
	
	void goNext() {
		if(!_fIsAfterLastNode){
			if(!next()){
				_fIsAfterLastNode = true;
			}
		}
	}
	
public:
	iterator_traversal(CBsTNode* root) : _crt(root), _fIsAfterLastNode(root == nullptr) {}
	
	const value_type& getValue() const { return _crt->getValue(); }
	
	const value_type& operator*() { return _crt->getValue(); }
	bool operator==(const template_iterator<const value_type>& it) { return ( _fIsAfterLastNode && it.fIsEndIterator() ); }
	bool operator!=(const template_iterator<const value_type>& it) { return !( *this == it ); }
};

class iteratorPreorderDF : public iterator_traversal{
private:
	enum EInstruction{
		go_down_left,
		go_once_down_right,
		go_up
	}instruction;
	
	void findNext() override {
		switch (instruction) {
			case go_down_left:
				if(crt_node->fHasLeftChild()){
					crt_node = crt_node->getLeftChild();
				}
				else{
					instruction = go_once_down_right;
					findNext();
				}
				break;
			case go_once_down_right:
				if(crt_node->fHasRightChild()){
					crt_node = crt_node->getRightChild();
					instruction = go_down_left;
				}
				else{
					instruction = go_up;
					findNext();
				}
				break;
			case go_up:
				if(!crt_node->fIsRoot()){
					if(crt_node->fIsLeftChild()){
						instruction = go_once_down_right;
						crt_node = crt_node->getParent();
						findNext();
					}
					else{
						instruction = go_up;
						crt_node = crt_node->getParent();
						findNext();
					}
				}
				else{
					crt_node = nullptr;
				}
				break;
		}
	}
public:
	typedef iteratorPreorderDF self_type;
	iteratorPreorderDF(CBsTNode* root) : iterator_traversal(root) {
		instruction = go_down_left;
	}
	
	self_type operator++() {
		iterator_traversal::goNext();
		return *this;
	}
	self_type operator++(int junk) {
		self_type it = *this;
		iterator_traversal::goNext();
		return it;
	}
};

class iteratorPostorderDF : public iterator_traversal {
private:
	enum EInstruction{
		go_down_left,
		go_once_down_right,
		go_up
	}instruction;
	
	void findNext() override {
		switch (instruction) {
			case go_down_left:
				while(crt_node->fHasLeftChild()){
					crt_node = crt_node->getLeftChild();
				}
				instruction = go_once_down_right;
				findNext();
				break;
			case go_once_down_right:
				if(crt_node->fHasRightChild()){
					crt_node = crt_node->getRightChild();
					instruction = go_down_left;
					findNext();
				}
				else{
					instruction = go_up;
					return;
				}
				break;
			case go_up:
				if(crt_node->getParent() != nullptr){
					if(crt_node->fIsLeftChild()){
						instruction = go_once_down_right;
						crt_node = crt_node->getParent();
						findNext();
					}
					else{
						instruction = go_up;
						crt_node = crt_node->getParent();
						return;
					}
				}
				else{
					crt_node = nullptr;
				}
				break;
		}
	}
public:
	typedef iteratorPostorderDF self_type;
	iteratorPostorderDF(CBsTNode* root) : iterator_traversal(root) {
		instruction = go_down_left;
		findNext();
	}
	self_type operator++() {
		iterator_traversal::goNext();
		return *this;
	}
	self_type operator++(int junk) {
		self_type it = *this;
		iterator_traversal::goNext();
		return it;
	}
};

class iteratorInorderDF : public iterator_traversal {
private:
	enum EInstruction{
		go_down_left,
		go_once_down_right,
		go_up
	}instruction;
	
	void findNext() override {
		switch (instruction) {
			case go_down_left:
				while(crt_node->fHasLeftChild()){
					crt_node = crt_node->getLeftChild();
				}
				instruction = go_once_down_right;
				break;
			case go_once_down_right:
				if(crt_node->fHasRightChild()){
					crt_node = crt_node->getRightChild();
					instruction = go_down_left;
					findNext();
				}
				else{
					instruction = go_up;
					findNext();
				}
				break;
			case go_up:
				if(crt_node->getParent() != nullptr){
					if(crt_node->fIsLeftChild()){
						instruction = go_once_down_right;
						crt_node = crt_node->getParent();
						return;
					}
					else{
						instruction = go_up;
						crt_node = crt_node->getParent();
						findNext();
						return;
					}
				}
				else{
					crt_node = nullptr;
				}
				
				break;
		}
	}
public:
	typedef iteratorInorderDF self_type;
	iteratorInorderDF(CBsTNode* root) : iterator_traversal(root) {
		instruction = go_down_left;
		findNext();
	}
	
	self_type operator++() {
		iterator_traversal::goNext();
		return *this;
	}
	self_type operator++(int junk) {
		self_type it = *this;
		iterator_traversal::goNext();
		return it;
	}
};

class iteratorBF : public iterator_traversal {
private:
	std::queue<CBsTNode*> firstStack, secondStack;
	std::queue<CBsTNode*>& inputStack;
	std::queue<CBsTNode*>& outputStack;
	
	void findNext() override {
		if(inputStack.size() != 0){
			crt_node = inputStack.front();
			
			inputStack.pop();
			if(crt_node->fHasLeftChild()){
				outputStack.push(crt_node->getLeftChild());
			}
			if(crt_node->fHasRightChild()){
				outputStack.push(crt_node->getRightChild());
			}
		}
		else{
			if(outputStack.size() != 0){
				const std::queue<CBsTNode*>& c = inputStack;
				inputStack = outputStack;
				outputStack = c;
				while(outputStack.size() != 0){
					outputStack.pop();
				}
				findNext();
			}
			else{
				crt_node = nullptr;
			}
		}
	}
public:
	typedef iteratorBF self_type;
	
	iteratorBF(CBsTNode* root) :
	inputStack(firstStack),
	outputStack(secondStack),
	iterator_traversal(root) {
		inputStack.push(root);
		findNext();
	}
	
	self_type operator++() {
		iterator_traversal::goNext();
		return *this;
	}
	self_type operator++(int junk) {
		self_type it = *this;
		iterator_traversal::goNext();
		return it;
	}
};


#endif /* CBsTTraversalIterators_h */
