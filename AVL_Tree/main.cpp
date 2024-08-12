//  Created by Kadir Emre Oto on 06.08.2018.
#include <iostream>
#include "AVL_Tree.hpp"


int main(int argc, const char* argv[]) {

    AVLTree<int> tree;

    tree.insert(12);
    tree.insert(3);
    tree.insert(5);
    tree.insert(43);
    tree.insert(13);
    tree.insert(23);
    tree.insert(7);
    tree.insert(22);
    tree.insert(41);
    tree.insert(19);
    tree.insert(27);
    tree.insert(9);
    tree.insert(14);
    tree.erase(3);
    tree.display();
    tree.erase(23);
    // tree.erase("KEO");
    tree.display();
    tree.erase(13);
    tree.erase(12);
    tree.display();
    tree.erase(19);
    
    tree.erase(9);
    tree.display();
    tree.erase(7);
    tree.display();
    return 0;
}