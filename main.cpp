#include "CBsT.hpp"
#include <iostream>
#include <sys/time.h>
using namespace std;

int main(){
    CBsT<double, greater<int>> bst;
    for(auto itPreorderDF = bst.beginPreorderDF(); itPreorderDF != bst.end(); ++itPreorderDF){
        cout << *itPreorderDF << ' ';
    }
    bst.insert(5);
    bst.insert(3);
    bst.insert(4);
    bst.insert(2);
    bst.insert(0);
    bst.insert(1);
    bst.insert(-1);
    bst.insert(1.5);
    bst.insert(33);
    bst.insert(0.97);
    bst.insert(1.25);
    bst.insert(1.375);
    bst.insert(-2);
    bst.insert(-3);
    bst.insert(-4);
    bst.insert(-5);
    bst.insert(-6);
    bst.insert(-7);
    bst.insert(-8);
    bst.insert(6.5);
    bst.insert(20);
    bst.insert(15);
    bst.insert(16);
    bst.insert(19);
    bst.insert(18);
    bst.insert(14);
	
	for(auto it : bst){
		cout << it << ' ';
	}
	cout << endl;
	
    cout << "Preorder REC:" << endl;
    bst.printPreorderDF(bst.getRoot());
    cout << endl << "Preorder my:" << endl;
    
    for(auto itPreorderDF = bst.beginPreorderDF(); itPreorderDF != bst.end(); ++itPreorderDF){
        cout << *itPreorderDF << ' ';
    }
	
	
    
    cout << endl << "Inorder REC" << endl;
    bst.printInorderDF(bst.getRoot());
    cout << endl << "Inorder my:" << endl;
    for(auto itInorderDF = bst.beginInorderDF(); itInorderDF != bst.end(); ++itInorderDF){
        cout << *itInorderDF << ' ';
    }
    
    
    cout << endl << "Postorder REC:" << endl;
    bst.printPostorderDF(bst.getRoot());
    
    cout << endl << "Postorder my:" << endl;
    for(auto itPostorderDF = bst.beginPostorderDF(); itPostorderDF != bst.end(); ++itPostorderDF){
        cout << *itPostorderDF << ' ';
    }
    cout << endl;
    
 
    cout << "Breadth-first my:" << endl;
    for(auto itBF = bst.beginBF(); itBF != bst.end(); ++itBF){
        cout << *itBF <<' ';
    }
    cout << endl << endl;
   
    for (auto it : bst) {
        cout << it << ' ';
    }
    cout << endl;
    
	bst.clear();
	bst.insert(1);
	bst.remove(1);
	bst.begin();
	bst.beginBF();
	bst.beginInorderDF();
	bst.beginPostorderDF();
	bst.beginPreorderDF();
	bst.empty();
	bst.size();
	bst.find(1);
	bst.getRoot();
	
    return 0;
}










