//  Created by Kadir Emre Oto on 06.08.2018.

#ifndef AVLTreeNode_hpp
#define AVLTreeNode_hpp

#include <string>
#include <algorithm>

template <class T>
struct AVLTreeNode {
    AVLTreeNode *left;
    AVLTreeNode *right;
    //记录坐标, 用于打印
    int x, y;
    const T value;
    int count;  // how many nodes are there in this subtree
    int height;  // 树的高度
    
    AVLTreeNode(T value);
    void updateValues();
    int balanceFactor();
    
    AVLTreeNode* left_rotate();
    AVLTreeNode* right_rotate();
};

#endif /* AVLTreeNode_hpp */