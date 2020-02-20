#include <fstream>
#include <iostream>
#include "MyAVLTree.hpp"
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
}

int main()
{
    testFind();
    return 0;
}

