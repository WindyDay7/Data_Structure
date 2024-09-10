//  Created by Kadir Emre Oto on 06.08.2018.
#include <iostream>
#include "Red_Black_Tree.hpp"


int main(int argc, const char* argv[]) {

    Red_Black_Tree<int> tree;

    tree.insert(12);
    tree.insert(3);
    tree.insert(5);
    tree.display();
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
    tree.erase(34);

    tree.erase(13);

    tree.erase(27);
    tree.erase(57);
    tree.erase(17);
    tree.erase(7);
    tree.erase(23);
    tree.erase(48);
    tree.erase(3);
    tree.erase(43);
    tree.erase(41);
    // tree.display();
    tree.erase(12);
    // tree.display();
    tree.erase(9);
    // tree.display();
    tree.erase(5);
    tree.erase(63);
    tree.erase(22);
    tree.erase(14);
    tree.display();
    tree.erase(19);
    tree.display();
    // tree.insert(37);
    // tree.insert(29);
    // tree.insert(18);
    // tree.insert(43);

    // tree.insert(39);
    // tree.insert(26);
    // tree.insert(8);
    // tree.insert(1);
    // tree.display();
    return 0;
}