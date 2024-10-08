#include "AVLTree_Node.hpp"

template <class T>
AVLTreeNode<T>::AVLTreeNode(T value): value(value){
    count = 1;
    height = 1;
    
    left = nullptr;
    right = nullptr;
}


template <class T>
int AVLTreeNode<T>::balanceFactor() {
    int left_height = this->left == nullptr ? 0 : this->left->height;
    int right_height = this->right == nullptr ? 0 : this->right->height;
    return left_height - right_height;
}


template <class T>
void AVLTreeNode<T>::updateValues() {
    count = (left == nullptr? 0:left->count) + (right == nullptr? 0:right->count) + 1;
    height = std::max((left == nullptr)? 0:left->height, (right == nullptr)? 0:right->height) + 1;
}

// 以当前节点为根节点进行左旋转
template <class T>
AVLTreeNode<T>* AVLTreeNode<T>::left_rotate() {
    AVLTreeNode* temp = this->right;
    this->right = this->right->left == nullptr? nullptr:this->right->left;
    temp->left = this;
    // 更新当前节点与pivot节点的信息
    this->updateValues();
    temp->updateValues();
    return temp;
}

// 以当前节点为根节点进行右旋转
template <class T>
AVLTreeNode<T>* AVLTreeNode<T>::right_rotate() {
    AVLTreeNode* temp = this->left;
    this->left = this->left->right == nullptr? nullptr:this->left->right;
    temp->right = this;
    // 更新当前节点与pivot节点的信息
    this->updateValues();
    temp->updateValues();
    return temp;
}


template class AVLTreeNode<int>;
template class AVLTreeNode<short>;
template class AVLTreeNode<long>;
template class AVLTreeNode<long long>;
// template class AVLTreeNode<std::string>;