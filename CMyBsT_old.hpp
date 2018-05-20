#ifndef CMyBsT_hpp
#define CMyBsT_hpp

#include <functional>




template <class value_type, class comporator = std::less<value_type>>
class CMyBsT {
private:
    
    class CMyBsTNode{
    private:
        value_type _value;
        
        CMyBsTNode* _parent_pointer;
        CMyBsTNode* _left_child_pointer;
        CMyBsTNode* _right_child_pointer;
        
    public:
        CMyBsTNode(const value_type& value,
                   CMyBsTNode* parent_pointer = nullptr,
                   CMyBsTNode* left_child_pointer = nullptr,
                   CMyBsTNode* right_child_pointer = nullptr) :
        _value(value),
        _parent_pointer(parent_pointer),
        _left_child_pointer(left_child_pointer),
        _right_child_pointer(right_child_pointer) { }
        
        void setValue(const value_type& value) { _value = value; }
        void setParent(CMyBsTNode* parent_pointer) { _parent_pointer = parent_pointer; }
        void setleftChild(CMyBsTNode* left_child_pointer) { _left_child_pointer = left_child_pointer; }
        void setRightChild(CMyBsTNode* right_child_pointer) { _right_child_pointer = right_child_pointer; }
        
        const value_type& cgetValue() const { return _value; }
        value_type& getValue() { return _value; }
        
        const value_type* cgetValuePointer() const { return &_value; }
        value_type* getValuePointer() { return &_value; }
        
        bool fIsRoot() const { return (_parent_pointer == nullptr); }
        bool fHasLeftChild() const { return (_left_child_pointer != nullptr); }
        bool fHasRightChild() const {return (_right_child_pointer != nullptr); }
        
        CMyBsTNode* getParent() const { return _parent_pointer; }
        CMyBsTNode* getLeftChild() const { return _left_child_pointer; }
        CMyBsTNode* getRightChild() const { return _right_child_pointer; }
        
        bool operator==(const CMyBsTNode& other) { return (_value == other._value); }
        bool operator!=(const CMyBsTNode& other) { return !(*this == other); }
        
        bool operator>(const CMyBsTNode& other) { return (comporator(*this, other)); }
        bool operator<=(const CMyBsTNode& other) { return !(*this > other); }
        
        bool operator<(const CMyBsTNode& other) { return ((*this <= other) && (this != other)); }
        bool operator>=(const CMyBsTNode& other) { return !(*this < other); }
    };
    
    static CMyBsTNode* findNodeByValue(const value_type& value) {
        return nullptr;
    }
    
    
    
    static CMyBsTNode* findNextNode(CMyBsTNode* root, CMyBsTNode* crt, bool& fIsPreFirst, bool& fIsAfterLast) {
        if(fIsPreFirst == true){
            crt = findMin(root, fIsPreFirst, fIsAfterLast);
        }
        else {
            if(fIsAfterLast == false){
                findNextNode();
            }
        }
        return crt;
    }
    static CMyBsTNode* findPrevNode(CMyBsTNode* root, CMyBsTNode* crt, bool& fIsPreFirst, bool& fIsAfterLast) {
        if(fIsAfterLast == true){
            crt = findMax(root, fIsPreFirst, fIsAfterLast);
        }
        else{
            if(fIsPreFirst == false){
                findPrevNode();
            }
        }
        return crt;
    }
    
    
    static CMyBsTNode* findMax(CMyBsTNode* root, bool& fIsPreFirst, bool& fIsAfterLast){
        CMyBsTNode* node;
        if(root == nullptr){
            fIsPreFirst = false;
            fIsAfterLast = true;
            node = nullptr;
        }
        else{
            CMyBsTNode* crt = root;
            while(crt->fHasRightChild()){
                crt = crt->getRightChild();
            }
            node = crt;
        }
        return node;
    }
    static CMyBsTNode* findMin(CMyBsTNode* root, bool& fIsPreFirst, bool& fIsAfterLast){
        CMyBsTNode* node;
        if(root == nullptr){
            fIsPreFirst = false;
            fIsAfterLast = true;
            node = nullptr;
        }
        else{
            CMyBsTNode* crt = root;
            while(crt->fHasLeftChild()){
                crt = crt->getLeftChild();
            }
            node = crt;
        }
        return node;
    }
    
    
public:

    template<class iterator_value_type>
    class template_iterator{
    private:
        CMyBsTNode* _root_node_pointer;
        CMyBsTNode* _node_pointer;
        bool _fIsAfterLast;
        bool _fIsPreFirst;
        
        void findNext(){
            _node_pointer = findNextNode(_root_node_pointer, _node_pointer, _fIsPreFirst, _fIsAfterLast);
        }
        void findPrev(){
            _node_pointer = findPrevNode(_root_node_pointer, _node_pointer, _fIsPreFirst, _fIsAfterLast);
        }
       
        
        typedef template_iterator<iterator_value_type> self_type;
    public:
        template_iterator(CMyBsTNode* root_node_pointer,
                          CMyBsTNode* node_pointer,
                          const bool fIsPreFirst = false,
                          const bool fIsAfterLast = false) :
        _root_node_pointer(root_node_pointer),
        _node_pointer(node_pointer),
        _fIsAfterLast(fIsAfterLast),
        _fIsPreFirst(fIsPreFirst) {}
        
        self_type operator++() { self_type it = *this; findNext(); return it; }
        self_type operator++(int junk) { findNext(); return *this; }
        
        self_type operator--() { self_type it = *this; findPrev(); return it; }
        self_type operator--(int junk) { findPrev(); return *this; }
        
        iterator_value_type& operator*() { return _node_pointer->getValue(); }
        iterator_value_type* operator->() { return _node_pointer->getValuePointer(); }
        
        bool operator==(const self_type& other) {
            if(_fIsPreFirst ^ other._fIsPreFirst || _fIsAfterLast ^ other._fIsAfterLast)
                return false;
            else return
            (_fIsAfterLast && other._fIsAfterLast) ||
            (_fIsPreFirst && other._fIsPreFirst) ||
            (*_node_pointer == *other._node_pointer); }
        
        bool operator!=(const self_type& other) { return !(*this == other); }
    };
   
    typedef template_iterator<value_type> iterator;
    typedef template_iterator<const value_type> const_iterator;
    
    CMyBsT() : _root(nullptr), _size(0) {}
    CMyBsT(const CMyBsT& other);
    CMyBsT(CMyBsT& other);
    
    iterator begin() { iterator it(_root, nullptr, true, false); ++it; return it; }
    const_iterator cbegin() const { const_iterator cit(_root, nullptr, true, false); ++cit; return cit; }
    
    iterator end() { return iterator(_root, nullptr, false, true); }
    const_iterator cend() { return const_iterator(_root, nullptr, false, true); }
    
    iterator insert(const value_type& value) { return iterator(0, 0); }
    iterator remove(const value_type& value) { return iterator(_root, nullptr, false, true); }
    iterator find(const value_type& value) {
        CMyBsTNode* node = findNodeByValue(value);
        if(node == nullptr)
            return iterator(_root, nullptr, false, true);
        else
            return iterator(_root, node, false, false); }
    
    const_iterator cfind(const value_type& value) const {
        CMyBsTNode* node = findNodeByValue(value);
        if(node == nullptr)
            return const_iterator(_root, nullptr, false, true);
        else
            return const_iterator(_root, node, false, false); }
    
    bool empty() const { return (_size == 0); }
    size_t size() const { return _size; }
    
private:
    CMyBsTNode* _root;
    size_t _size;
    
};

template<class value_type, class comporator = std::less<value_type>>
class Class1{
public:
    class subClass1{
        value_type i;
    };
    int func();
};

#endif /* CMyBsT_hpp */















