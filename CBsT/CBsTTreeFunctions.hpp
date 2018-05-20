#ifndef CBsTTreeFunctions_hpp
#define CBsTTreeFunctions_hpp

/* 	 Always is included into CBsT.hpp
 *	( inside class CBsT<type_name, comporator> )
 */

static CBsTNode* findMax(CBsT::CBsTNode *root) {
	CBsTNode* crt = root;
	if(crt != nullptr){
		while(crt->fHasRightChild()){
			crt = crt->getRightChild();
		}
	}
	return crt;
}

static CBsTNode* findMin(CBsT::CBsTNode *root) {
	CBsTNode* crt = root;
	if(crt != nullptr){
		while(crt->fHasLeftChild()){
			crt = crt->getLeftChild();
		}
	}
	return crt;
}

static CBsTNode* findNextNode(CBsTNode* root, CBsTNode* start){
	CBsTNode* crt = nullptr;
	if(start->fHasRightChild()){
		crt = findMin(start->getRightChild());
	}
	else{
		crt = start->getParent();
		while(crt != nullptr && start == crt->getRightChild()){
			start = crt;
			crt = crt->getParent();
		}
	}
	return crt;
}

static CBsTNode* findPrevNode(CBsTNode* root, CBsTNode* start){
	CBsTNode* crt = nullptr;
	if(start->fHasLeftChild()){
		crt = findMax(start->getLeftChild());
	}
	else{
		crt = start->getParent();
		while(crt != nullptr && start == crt->getLeftChild()){
			start = crt;
			crt = crt->getParent();
		}
	}
	return crt;
}

static CBsTNode* insertNode(CBsTNode* root, const value_type& value){
	CBsTNode* crt;
	CBsTNode* new_node = nullptr;
	CBsTNode nodeValue(value); // created just for comparing *crt and value
	crt = root;
	
	if(crt == nullptr){
		// tree is empty
		new_node = new CBsTNode(value);
	}
	else{
		while(true){
			if(nodeValue > *crt){
				if(crt->fHasRightChild()){
					crt = crt->getRightChild();
					continue;
				}
				else{
					crt->setRightChild(new_node = new CBsTNode(value, crt));
					break;
				}
			}
			if(nodeValue < *crt){
				if(crt->fHasLeftChild()){
					crt = crt->getLeftChild();
					continue;
				}
				else{
					crt->setLeftChild(new_node = new CBsTNode(value, crt));
					break;
				}
			}
			if(nodeValue == *crt){
				new_node = nullptr;
				break;
			}
		}
	}
	return new_node;
}

static CBsTNode* removeNodeByValue(CBsTNode* root, value_type& value){
	return removeNode(findNode(root, value));
}

// return new root of the tree
static CBsTNode* removeNodeByPointer(CBsTNode* root, CBsTNode* node_pointer){
	CBsTNode* removable, *next, *parent;
	bool fLeft;
	
	removable = node_pointer;
	if(removable == nullptr){
		return root;
	}
	
	if(!removable->fHasLeftChild() && !removable->fHasRightChild()){
		if(removable->fIsRoot()){
			root = nullptr;
		}
		else{
			CBsTNode* parent = removable->getParent();
			if(parent->getLeftChild() == removable){
				parent->setLeftChild(nullptr);
			}
			else{
				parent->setRightChild(nullptr);
			}
		}
		delete removable;
	}
	else{
		if(removable->fHasRightChild() ^ removable->fHasLeftChild()){
			if(removable->fHasRightChild()){
				next = removable->getRightChild();
			}
			else{
				next = removable->getLeftChild();
			}
			
			parent = removable->getParent();
			if(parent != nullptr && parent->getLeftChild() == removable){
				fLeft = true;
			}
			else{
				fLeft = false;
			}
			delete removable;
			
			if(parent == nullptr){
				next->setParent(nullptr);
				root = next;
			}
			else{
				next->setParent(parent);
				if(fLeft){
					parent->setLeftChild(next);
				}
				else{
					parent->setRightChild(next);
				}
			}
			
		}
		else{
			next = findNextNode(root, removable);
			value_type val = next->getValue();
			root = removeNodeByPointer(root, next);
			removable->setValue(val);
		}
	}
	
	return root;
}

static CBsTNode* findNode(CBsTNode* root, const value_type& value){
	CBsTNode* crt = root;
	CBsTNode nodeValue(value);
	
	while(crt != nullptr){
		if(nodeValue == *crt){
			break;
		}
		if(nodeValue > *crt){
			if(crt->fHasRightChild()){
				crt = crt->getRightChild();
			}
			else{
				crt = nullptr;
			}
		}
		else{
			if(crt->fHasLeftChild()){
				crt = crt->getLeftChild();
			}
			else{
				crt = nullptr;
			}
		}
	}
	return crt;
}

static void freeMemOfTree(CBsTNode* crt){
	CBsTNode* left, *right;
	if(crt == nullptr)
		return;
	left = crt->getLeftChild();
	right = crt->getRightChild();
	delete crt;
	freeMemOfTree(left);
	freeMemOfTree(right);
}

static CBsTNode* copyTree(const CBsTNode* crtOther, const CBsTNode* parent) {
	CBsTNode* crt = nullptr;
	if(crtOther != nullptr){
		crt = new CBsTNode(crtOther->cgetValue(), parent);
		crt->setLeftChild(copyTree(crtOther->getLeftChild(), crt));
		crt->setRightChild(copyTree(crtOther->getRightChild(), crt));
	}
	return crt;
}


#endif /* CBsTTreeFunctions_hpp */
