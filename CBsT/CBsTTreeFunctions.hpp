#ifndef CBsTTreeFunctions_hpp
#define CBsTTreeFunctions_hpp

/* 	 Always is included into CBsT.hpp
 *	( inside class CBsT<type_name, comporator> )
 */

private:

	static CBsTNode* findMax(CRootNode *root) {
		CBsTNode* crt = root;
		if(crt != nullptr){
			while(crt->hasRightChild()){
				crt = crt->getRightChild();
			}
		}
		return crt;
	}

	static CBsTNode* findMin(CRootNode *root) {
		CBsTNode* crt = root;
		if(crt != nullptr){
			while(crt->hasLeftChild()){
				crt = crt->getLeftChild();
			}
		}
		return crt;
	}

	static CBsTNode* findNextNode(CRootNode* root, CBsTNode* start){
		CBsTNode* crt = nullptr;
		if(start->hasRightChild()){
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

	static CBsTNode* findPrevNode(CRootNode* root, CBsTNode* start){
		CBsTNode* crt = nullptr;
		if(start->hasLeftChild()){
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

	static CBsTNode* insertNode(CRootNode* root, const value_type& value){
		CBsTNode* crt;
		CBsTNode* new_node = nullptr;
		CBsTNode nodeValue(value); // created just for comparing *crt and value
		crt = root;
	
		if(crt == nullptr){
			// tree is empty
			new_node = new CRootNode(value);
		}
		else{
			while(true){
				if(nodeValue > *crt){
					if(crt->hasRightChild()){
						crt = crt->getRightChild();
						continue;
					}
					else{
						crt->setRightChild(new_node = new CBsTNode(value, crt));
						break;
					}
				}
				if(nodeValue < *crt){
					if(crt->hasLeftChild()){
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

	// return new root of the tree
	static CRootNode* removeNodeByValue(CRootNode* root, value_type& value){
		return removeNode(findNode(root, value));
	}

	// return new root of the tree
	static CRootNode* removeNodeByPointer(CRootNode* root, CBsTNode* node_pointer){
		CBsTNode* removable, *next;
		CParentNode* parent;
		bool fLeft;
	
		removable = node_pointer;
		if(removable == nullptr){
			return root;
		}
	
		if(!removable->hasLeftChild() && !removable->hasRightChild()){
			if(removable->isRoot()){
				root = nullptr;
			}
			else{
				parent = removable->getParent();
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
			if(removable->hasRightChild() ^ removable->hasLeftChild()){
				if(removable->hasRightChild()){
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

	static CBsTNode* findNode(CRootNode* root, const value_type& value){
		CBsTNode* crt = root;
		CBsTNode nodeValue(value);
	
		while(crt != nullptr){
			if(nodeValue == *crt){
				break;
			}
			if(nodeValue > *crt){
				if(crt->hasRightChild()){
					crt = crt->getRightChild();
				}
				else{
					crt = nullptr;
				}
			}
			else{
				if(crt->hasLeftChild()){
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
		CLeftChildNode* left;
		CRightChildNode* right;
		if(crt == nullptr)
			return;
		left = crt->getLeftChild();
		right = crt->getRightChild();
		delete crt;
		freeMemOfTree(left);
		freeMemOfTree(right);
	}

	static CBsTNode* copyTree(const CBsTNode* crtOther, const CParentNode* parent) {
		CBsTNode* crt = nullptr;
		if(crtOther != nullptr){
			crt = new CBsTNode(crtOther->cgetValue(), parent);
			crt->setLeftChild(copyTree(crtOther->getLeftChild(), crt));
			crt->setRightChild(copyTree(crtOther->getRightChild(), crt));
		}
		return crt;
	}


#endif /* CBsTTreeFunctions_hpp */








