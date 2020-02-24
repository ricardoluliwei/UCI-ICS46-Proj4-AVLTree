#ifndef __PROJ_THREE_AVL_HPP
#define __PROJ_THREE_AVL_HPP

#include "runtimeexcept.hpp"
#include <string>
#include <vector>

class ElementNotFoundException : public RuntimeException 
{
public:
    ElementNotFoundException(const std::string & err) : RuntimeException(err) {}
};

/*
 treeNode used in MyAVLTree, overide operator == , < , >
 */
template<typename Key, typename Value>
struct treeNode{
    Key key;
    Value val;
    treeNode* leftChild;
    treeNode* rightChild;
    treeNode(Key k, Value v) : key(k), val(v), leftChild(NULL), rightChild(NULL){}
    bool operator ==(const treeNode<Key, Value> &node) const {return key == node.key;}
    bool operator < (const treeNode<Key, Value> &node) const {return key < node.key;}
    bool operator > (const treeNode<Key, Value> &node) const {return key > node.key;}
};


template<typename Key, typename Value>
class MyAVLTree
{
    typedef treeNode<Key, Value> Node;
private:
    size_t mSize;
    Node* mRoot;
    
    //helper functions
    
    bool deleteNode(Node* root);
    
    void LLrotation(Node* rotateNode, Node* prev);
    void RRrotation(Node* rotateNode, Node* prev);
    void LRrotation(Node* rotateNode, Node* prev);
    void RLrotation(Node* rotateNode, Node* prev);
    size_t getheight(Node* root);
    void balance(Node* root, Node* prev);
    
    void insert(Node* copy, Node* source);
    void insert(Node* root, const Key & k, const Value &v);
    Value* find(Node* root, const Key & k) const;
    
    void inOrder(Node* root, std::vector<Key> &ans) const;
    void preOrder(Node* root, std::vector<Key> &ans) const;
    void postOrder(Node* root, std::vector<Key> &ans) const;
    
    std::string toString(Node* root, size_t level);
public:
    MyAVLTree();
    
    // In general, a copy constructor and assignment operator
    // are good things to have.
    // For this quarter, I am not requiring these.
    MyAVLTree(const MyAVLTree & st);
    MyAVLTree & operator=(const MyAVLTree & st);
    
    
    // The destructor is, however, required.
    ~MyAVLTree();
    
    // size() returns the number of distinct keys in the tree.
    size_t size() const noexcept;
    
    // isEmpty() returns true if and only if the tree has no values in it.
    bool isEmpty() const noexcept;
    
    // contains() returns true if and only if there
    //  is a (key, value) pair in the tree
    //	that has the given key as its key.
    bool contains(const Key & k) const;
    
    // find returns the value associated with the given key
    // If !contains(k), this will throw an ElementNotFoundException
    // There needs to be a version for const and non-const MyAVLTrees.
    Value & find(const Key & k);
    const Value & find(const Key & k) const;
    
    // Inserts the given key-value pair into
    // the tree and performs the AVL re-balance
    // operation, as described in lecture.
    // If the key already exists in the tree,
    // you may do as you please (no test cases in
    // the grading script will deal with this situation)
    void insert(const Key & k, const Value & v);
    
    // in general, a "remove" function would be here
    // It's a little trickier with an AVL tree
    // and I am not requiring it for this quarter's ICS 46.
    // You should still read about the remove operation
    // in your textbook.
    
    // The following three functions all return
    // the set of keys in the tree as a standard vector.
    // Each returns them in a different order.
    std::vector<Key> inOrder() const;
    std::vector<Key> preOrder() const;
    std::vector<Key> postOrder() const;
    
    std::string toString();
};


//copy constructor, deep copy
template<typename Key, typename Value>
MyAVLTree<Key, Value>::MyAVLTree(const MyAVLTree & st){
    if (st.isEmpty()){
        mSize = 0;
        mRoot = NULL;
        return;
    }
    
    mRoot = new Node(st.mRoot->key, st.mRoot->val);
    insert(mRoot, st.mRoot->leftChild);
    insert(mRoot, st.mRoot->rightChild);
    mSize = st.size();
}

//assignment operator, deep copy
template<typename Key, typename Value>
MyAVLTree<Key, Value> & MyAVLTree<Key, Value>:: operator = (const MyAVLTree & st){
    deleteNode(mRoot);
    
    if (st.isEmpty()){
        mSize = 0;
        mRoot = NULL;
        return *this;
    }
    
    mRoot = new Node(st.mRoot->key, st.mRoot->val);
    insert(mRoot, st.mRoot->leftChild);
    insert(mRoot, st.mRoot->rightChild);
    mSize = st.size();
    
    return *this;
}

//destructor, delete every node in the tree
template<typename Key, typename Value>
MyAVLTree<Key,Value>:: ~MyAVLTree()
{
    deleteNode(mRoot);
}

//constructor, default tree is an empty tree.
template<typename Key, typename Value>
MyAVLTree<Key,Value>::MyAVLTree()
{
    mSize = 0;
    mRoot = NULL;
}

// size() returns the number of distinct keys in the tree.
template<typename Key, typename Value>
size_t MyAVLTree<Key, Value>::size() const noexcept
{
    return mSize;
}

// return true is the tree is empty
template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::isEmpty() const noexcept
{
    return mSize == 0;
}

//helper function to delete the tree lead by "root"
template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::deleteNode(Node* root){
    if (!root)
        return false;
    deleteNode(root->leftChild);
    deleteNode(root->rightChild);
    delete root;
    mSize--;
    return true;
}

//helper function to find the treeNode with the key "k", in the tree "root"
template<typename Key, typename Value>
Value* MyAVLTree<Key, Value>::find(Node* root, const Key & k) const
{
    if (!root)
        return NULL;
    
    if (root->key == k)
        return &(root->val);
    
    if(k < root->key)
        return find(root->leftChild, k);
    
    return find(root->rightChild, k);
}


//return true if MyAVLTree contains the key "k"
template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::contains(const Key &k) const
{
    return find(mRoot, k) != NULL ;
}

//return the value of the treeNode with a Key "k"
//throw ElementNotFoundException if the tree does not contains "k"
template<typename Key, typename Value>
Value & MyAVLTree<Key, Value>::find(const Key & k)
{
    if (!contains(k))
        throw ElementNotFoundException("Element Not Found");
    
    return *find(mRoot, k);
}

//return the value of the treeNode with a Key "k"
//throw ElementNotFoundException if the tree does not contains "k"
template<typename Key, typename Value>
const Value & MyAVLTree<Key, Value>::find(const Key & k) const
{
    if (!contains(k))
        throw ElementNotFoundException("Element Not Found");
    
    return *find(mRoot, k);
}

//insert a new node(k,v) into the tree
//do nothing if the tree contians a Key "k"
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::insert(const Key & k, const Value & v)
{
    
    if (contains(k))
        return;
    
    if (isEmpty()) {
        mRoot = new Node(k, v);
        mSize++;
        return;
    }
    
    insert(mRoot, k, v);
    mSize++;
    balance(mRoot, NULL);
}

//helper function
//used to insert a new node(k, v) into a tree with the root
//root must not be empty, k, v should not exist in the tree
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::insert(Node* root, const Key & k, const Value & v)
{
    if (k < root->key) {
        if (!root->leftChild) {
            root->leftChild = new Node(k, v);
            return;
        }
        return insert(root->leftChild, k, v);
    }
    
    if (!root->rightChild) {
        root->rightChild = new Node(k, v);
        return;
    }
    
    return insert(root->rightChild, k, v);
}

//helper function for deep copy
//copy every node from "source" to "copy"
//"copy" should not be NULL
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::insert(Node* copy, Node*source){
    if (!source)
        return;
    
    //pre-order
    insert(copy, source->key, source->val);
    insert(copy, source->leftChild);
    insert(copy, source->rightChild);
}

//helper function
//inorder tranverse the tree and push the Keys into the vector
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::inOrder(Node* root, std::vector<Key> &ans) const
{
    if (!root)
        return;
    
    inOrder(root->leftChild, ans);
    ans.push_back(root->key);
    inOrder(root->rightChild, ans);
}

//inorder tranverse the tree and push the Keys into the vector
template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::inOrder() const
{
    std::vector<Key> ans;
    inOrder(mRoot, ans);
    return ans;
}

//helper function
//preorder tranverse the tree and push the Keys into the vector
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::preOrder(Node* root, std::vector<Key> &ans) const
{
    if (!root)
        return;
    
    ans.push_back(root->val);
    preOrder(root->leftChild, ans);
    preOrder(root->rightChild, ans);
}

//preorder tranverse the tree and push the Keys into the vector
template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::preOrder() const
{
    std::vector<Key> ans;
    preOrder(mRoot, ans);
    return ans;
}

//helper function
//postorder tranverse the tree and push the Keys into the vector
template<typename Key, typename Value>
void MyAVLTree<Key, Value>::postOrder(Node* root, std::vector<Key> &ans) const
{
    if (!root)
        return;
    
    postOrder(root->leftChild, ans);
    postOrder(root->rightChild, ans);
    ans.push_back(root->val);
}

//postorder tranverse the tree and push the Keys into the vector
template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::postOrder() const
{
    std::vector<Key> ans;
    postOrder(mRoot, ans);
    return ans;
}

//caculate the height of the node "root"
template <typename Key, typename Value>
size_t MyAVLTree<Key, Value>::getheight(Node* root) {
    if (!root)
        return 0;
    
    size_t left = getheight(root->leftChild);
    size_t right = getheight(root->rightChild);
    
    return (left < right ? right : left) + 1;
}


/*
 A
 / \
 B   h
 / \
 h+1 h
 */
template <typename Key, typename Value>
void MyAVLTree<Key, Value>::LLrotation(Node* rotateNode, Node* prev){
    Node* b = rotateNode->leftChild;
    if (!prev) {
        mRoot = b;
    } else if (prev->leftChild == rotateNode) {
        prev->leftChild = b;
    } else {
        prev->rightChild = b;
    }
    
    rotateNode->leftChild = b->rightChild;
    b->rightChild = rotateNode;
}

/*
 A
 / \
 h   B
 / \
 h  h+1
 */
template <typename Key, typename Value>
void MyAVLTree<Key, Value>::RRrotation(Node* rotateNode, Node* prev){
    Node* b = rotateNode->rightChild;
    if (!prev) {
        mRoot = b;
    } else if (prev->leftChild == rotateNode) {
        prev->leftChild = b;
    } else {
        prev->rightChild = b;
    }
    
    rotateNode->rightChild = b->leftChild;
    b->leftChild = rotateNode;
}


/*
 A
 / \
 B   h
 / \
 h   C
 / \
 h   h
 */
template <typename Key, typename Value>
void MyAVLTree<Key, Value>::LRrotation(Node* rotateNode, Node* prev){
    Node* c = rotateNode->leftChild->rightChild;
    if (!prev) {
        mRoot = c;
    } else if (prev->leftChild == rotateNode) {
        prev->leftChild = c;
    } else {
        prev->rightChild = c;
    }
    
    rotateNode->leftChild->rightChild = c->leftChild;
    c->leftChild = rotateNode->leftChild;
    rotateNode->leftChild = c->rightChild;
    c->rightChild = rotateNode;
    
}

/*
 A
 / \
 h   B
 / \
 C   h
 / \
 h   h
 */
template <typename Key, typename Value>
void MyAVLTree<Key, Value>::RLrotation(Node* rotateNode, Node* prev){
    Node* c = rotateNode->rightChild->leftChild;;
    if (!prev) {
        mRoot = c;
    } else if (prev->leftChild == rotateNode) {
        prev->leftChild = c;
    } else {
        prev->rightChild = c;
    }
    
    rotateNode->rightChild->leftChild = c->rightChild;
    c->rightChild = rotateNode->rightChild;
    rotateNode->rightChild = c->leftChild;
    c->leftChild = rotateNode;
}

//Balance the tree
//need to be called after every insert and delete
template <typename Key, typename Value>
void MyAVLTree<Key, Value>::balance(Node* root, Node* prev){
    if (!root)
        return;
    
    //inorder
    
    if (root->leftChild)
        balance(root->leftChild, root);
    
    if (root->rightChild)
        balance(root->rightChild, root);
    
    size_t leftHeight = getheight(root->leftChild);
    size_t rightHeight = getheight(root->rightChild);
    
    if (leftHeight > rightHeight && leftHeight - rightHeight > 1) {
        if (getheight(root->leftChild->leftChild) < getheight(root->leftChild->rightChild)) {
            LRrotation(root, prev);
            return;
        }
        LLrotation(root, prev);
        return;
    }
    
    if (rightHeight > leftHeight && rightHeight - leftHeight > 1) {
        if (getheight(root->rightChild->rightChild) < getheight(root->rightChild->leftChild)) {
            RLrotation(root, prev);
            return;
        }
        RRrotation(root, prev);
        return;
    }
}

//helper function
//return a inorder tranverse tree with the key
//Bugs exists when the Key is not a string or char
template<typename Key, typename Value>
std::string MyAVLTree<Key, Value>::toString(Node* root, size_t level){
    if (!root) {
        return "";
    }
    std::string ans = toString(root->leftChild, level + 1);
    ans += "\n";
    for (int i = 0; i < level; i++) {
        ans += "            ";
    }
    ans += root->key;
    ans += toString(root->rightChild, level + 1);
    return ans;
}

//return a inorder tranverse tree with the key
//Bugs exists when the Key is not a string or char
template<typename Key, typename Value>
std::string MyAVLTree<Key, Value>::toString(){
    return toString(mRoot, 0);
}

#endif 
