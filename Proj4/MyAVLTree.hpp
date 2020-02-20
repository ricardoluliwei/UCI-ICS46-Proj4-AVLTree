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

template<typename Key, typename Value>
struct treeNode{
    size_t height;
    Key key;
    Value val;
    treeNode* leftChild;
    treeNode* rightChild;
    treeNode(Key k, Value v) : height(0), key(k), val(v), leftChild(NULL), rightChild(NULL){}
};


template<typename Key, typename Value>
class MyAVLTree
{
    typedef treeNode<Key, Value> Node;
private:
    size_t mSize;
    Node* mRoot;
    
    void LLrotation();
    void RRrotation();
    void LRrotation();
    void RLrotation();
    
    void insert(Node* root, const Key & k, const Value & v);
    Value* find(Node* root, const Key & k) const;
    void inOrder(Node* root, std::vector<Key> &ans) const;
    void preOrder(Node* root, std::vector<Key> &ans) const;
    void postOrder(Node* root, std::vector<Key> &ans) const;
public:
    MyAVLTree();
    
    // In general, a copy constructor and assignment operator
    // are good things to have.
    // For this quarter, I am not requiring these.
    //	MyAVLTree(const MyAVLTree & st);
    //	MyAVLTree & operator=(const MyAVLTree & st);
    
    
    // The destructor is, however, required.
    ~MyAVLTree()
    {
        // TODO
    }
    
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
    
    
};


template<typename Key, typename Value>
MyAVLTree<Key,Value>::MyAVLTree()
{
    mSize = 0;
    mRoot = NULL;
}

template<typename Key, typename Value>
size_t MyAVLTree<Key, Value>::size() const noexcept
{
    return mSize;
}

template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::isEmpty() const noexcept
{
    return mSize == 0;
}

template<typename Key, typename Value>
Value* MyAVLTree<Key, Value>::find(Node* root, const Key & k) const
{
    if (!root)
        return NULL;
    
    if (root->key == k)
        return &(root->val);
    
    Value* left = find(root->leftChild, k);
    if (left)
        return left;
    
    return find(root->rightChild, k);
}


template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::contains(const Key &k) const
{
    return find(mRoot, k) != NULL ;
}




template<typename Key, typename Value>
Value & MyAVLTree<Key, Value>::find(const Key & k)
{
    if (!contains(k))
        throw ElementNotFoundException("Element Not Found");
    
    return *find(mRoot, k);
}


template<typename Key, typename Value>
const Value & MyAVLTree<Key, Value>::find(const Key & k) const
{
    if (!contains(k))
        throw ElementNotFoundException("Element Not Found");
    
    return *find(mRoot, k);
}


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
    
}

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


template<typename Key, typename Value>
void MyAVLTree<Key, Value>::inOrder(Node* root, std::vector<Key> &ans) const
{
    if (!root)
        return;
    inOrder(root->leftChild, ans);
    ans.push_back(root->key);
    inOrder(root->rightChild, ans);
}

template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::inOrder() const
{
    std::vector<Key> ans;
    inOrder(mRoot, ans);
    return ans;
}


template<typename Key, typename Value>
void MyAVLTree<Key, Value>::preOrder(Node* root, std::vector<Key> &ans) const
{
    if (!root)
        return;
    
    ans.push_back(root->val);
    preOrder(root->leftChild, ans);
    preOrder(root->rightChild, ans);
}

template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::preOrder() const
{
    std::vector<Key> ans;
    preOrder(mRoot, ans);
    return ans;
}


template<typename Key, typename Value>
void MyAVLTree<Key, Value>::postOrder(Node* root, std::vector<Key> &ans) const
{
    if (!root)
        return;
    
    postOrder(root->leftChild, ans);
    postOrder(root->rightChild, ans);
    ans.push_back(root->val);
}

template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::postOrder() const
{
    std::vector<Key> ans;
    postOrder(mRoot, ans);
    return ans;
}






#endif 
