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
    tree.insert(14);
    tree.insert(17);
    tree.insert(34);
    tree.insert(48);
    tree.insert(63);

    tree.insert(57);
    tree.insert(24);
    tree.insert(75);
    tree.insert(67);
    tree.display();
    tree.erase(67);
    tree.erase(24);
    tree.display();
    tree.erase(34);

    tree.erase(13);
    // tree.display();
    // tree.erase(27);
    tree.display();
    return 0;
}