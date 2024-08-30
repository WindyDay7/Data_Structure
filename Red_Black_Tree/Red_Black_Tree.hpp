//  Created by Kadir Emre Oto on 06.08.2018.

#ifndef Red_Black_Tree_hpp
#define Red_Black_Tree_hpp

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Red_Black_Node.hpp"

template <class T>
class Red_Black_Tree {
    int _size;
    Red_Black_Node<T> *root;
    
    int InsertBalanceAction(Red_Black_Node<T>* node);
    void InsertBalanceAdjust(Red_Black_Node<T>* node);
    int RemoveBalanceAction(Red_Black_Node<T>* node);
    void RemoveBalanceAdjust(Red_Black_Node<T>* node);
    
    void display(Red_Black_Node<T>* root);

    // 用于可视化平衡二叉树
    void initX(Red_Black_Node<T> *p, int &x);
    void initY(Red_Black_Node<T> *root);
    void initCoordinate(Red_Black_Node<T> *root);
    
public:
    Red_Black_Tree();
    ~Red_Black_Tree();
    
    void insert(T value);
    void erase(T value);
    
    void clear();
    bool empty() const;

    int find(T value) const;

    void display();
};

#endif /* Red_Black_Tree_hpp */