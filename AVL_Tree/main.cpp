//  Created by Kadir Emre Oto on 06.08.2018.
#include <iostream>
#include "AVL_Tree.hpp"


int main(int argc, const char * argv[]) {

    AVLTree<int> tree;
    
    tree.insert(12);
    tree.insert(3);
    tree.insert(5);
    tree.insert(43);
    
    // tree.erase("KEO");
    tree.display();
    
    // std::cout << tree.lower_bound("Keo") << std::endl;
    // std::cout << tree.find_max() << std::endl;
    // std::cout << tree.size() << std::endl;
    // std::cout << tree.empty() << std::endl;
    // tree.clear();
    // std::cout << tree.empty() << std::endl;
    
    return 0;
}