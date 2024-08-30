#include "Red_Black_Node.hpp"

template <class T>
Red_Black_Node<T>::Red_Black_Node(T value, Color node_color, bool NIL):value(value), node_color(node_color), NIL(NIL) {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    x = 0; y = 0;
}

// 以当前节点为根节点进行左旋转
template <class T>
Red_Black_Node<T>* Red_Black_Node<T>::LeftRotate() {
    Red_Black_Node* temp = this->right;
    this->right = this->right->left == nullptr? nullptr:this->right->left;
    temp->left = this;
    return temp;
}

// 以当前节点为根节点进行右旋转
template <class T>
Red_Black_Node<T>* Red_Black_Node<T>::RightRotate() {
    Red_Black_Node* temp = this->left;
    this->left = this->left->right == nullptr? nullptr:this->left->right;
    temp->right = this;
    return temp;
}


template <class T>
void Red_Black_Node<T>::Set_Color(Color new_color) {
    this->node_color = new_color;
}

template <class T>
Red_Black_Node<T>* Red_Black_Node<T>::GetUncle() {
    if(this->parent == nullptr || this->parent->parent == nullptr) {
        return nullptr;
    }
    if(this->parent == this->parent->parent->left) {
        return this->parent->parent->right;
    }
    return this->parent->parent->left;
}

template <class T>
Red_Black_Node<T>* Red_Black_Node<T>::GetSibling() {
    if(this->parent == nullptr) {
        return nullptr;
    }
    if(this == this->parent->left) {
        return this->parent->right;
    }
    return this->parent->left;
}

template <class T>
Red_Black_Node<T>* Red_Black_Node<T>::GetCloseNephew() {
    // 如果当前节点存在兄弟节点, 并且兄弟节点不是NIL节点
    // 那么可以获取当前节点的侄子节点
    if(this->GetSibling() != nullptr && !this->GetSibling()->NIL) {
        if(this == this->parent->left) {
            return this->GetSibling()->left;
        }
        return this->GetSibling()->right;
    }
    return nullptr;
}


template <class T>
Red_Black_Node<T>* Red_Black_Node<T>::GetFarNephew() {
    // 如果当前节点存在兄弟节点, 并且兄弟节点不是NIL节点
    // 那么可以获取当前节点的侄子节点
    if(this->GetSibling() != nullptr && !this->GetSibling()->NIL) {
        if(this == this->parent->left) {
            return this->GetSibling()->right;
        }
        return this->GetSibling()->left;
    }
    return nullptr;
}



