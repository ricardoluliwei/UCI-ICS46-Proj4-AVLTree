#include <fstream>
#include <iostream>
#include "MyAVLTree.hpp"
#include <sstream>
#include "proj4.hpp"
using namespace std;

void testFind(){
    MyAVLTree<int, string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");
    cout<< tree.find(12) << endl;
    tree.find(12) = "It's me now";
    cout << tree.find(12) << endl;
    cout << tree.toString() <<endl;
}

void testOrder(){
    MyAVLTree<int, string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");
    tree.insert(5, "foo");
    vector<int> inOrder = tree.inOrder();
    for (int i = 0; i < inOrder.size(); i++) {
        cout << inOrder[i] << endl;
    }
}

void testCopy(){
    MyAVLTree<int, string> tree;
    tree.insert(5, "foo");
    tree.insert(3, "sna");
    tree.insert(10, "bar");
    tree.insert(12, "twelve");
    tree.insert(5, "foo");
    vector<int> inOrder = tree.inOrder();
    cout << "Tree 1: " <<endl;
    for (int i = 0; i < inOrder.size(); i++) {
        cout << inOrder[i] << endl;
    }
    
    MyAVLTree<int, string> tree2(tree);
    MyAVLTree<int, string> tree3;
    tree3.insert(-1, "should be deleted");
    tree3 = tree;
    
    tree.insert(1, "here");
    
    cout << &tree <<endl;
    //delete &tree;
    inOrder = tree.inOrder();
    cout << "Tree 1 after insert: " <<endl;
    for (int i = 0; i < inOrder.size(); i++) {
        cout << inOrder[i] << endl;
    }
    
    inOrder = tree2.inOrder();
    cout << "Tree 2: " <<endl;
    for (int i = 0; i < inOrder.size(); i++) {
        cout << inOrder[i] << endl;
    }
    
    inOrder = tree3.inOrder();
    cout << "Tree 3:" <<endl;
    for (int i = 0; i < inOrder.size(); i++) {
        cout << inOrder[i] << endl;
    }
    
}

void testCountWords(){
    std::string quote = "I'm dishonest, and a dishonest man you can ";
    quote += "always trust to be dishonest. Honestly. It's the honest ";
    quote += "ones you want to watch out for, because you can never ";
    quote += "predict when they're going to do something incredibly... stupid.";
    
    std::istringstream stream( quote );
    
    MyAVLTree<std::string, unsigned> tree;
    
    countWords(stream, tree);
    cout << "excpect to be 3: " << tree.find("to") << endl;
    cout << tree.toString() <<endl;
}

int main()
{
    testCountWords();
    return 0;
}

