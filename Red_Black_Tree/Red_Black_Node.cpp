#include "Red_Black_Node.hpp"

template <class T>
Red_Black_Node<T>::Red_Black_Node(T value, Color node_color, bool NIL) :value(value), node_color(node_color), NIL(NIL) {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    x = 0; y = 0;
}

// 以当前节点为根节点进行左旋转
template <class T>
Red_Black_Node<T>* Red_Black_Node<T>::LeftRotate() {
    Red_Black_Node* temp_parent = this->parent;
    Red_Black_Node* temp = this->right;
    this->right->left->parent = this;
    this->right = this->right->left;
    this->parent = temp;
    temp->left = this;
    if (temp_parent != nullptr) {
        if (this == temp_parent->left) {
            temp_parent->left = temp;
        }
        else {
            temp_parent->right = temp;
        }
        temp->parent = temp_parent;
    }
    else {
        temp->parent = nullptr;
    }
    return temp;
}

// 以当前节点为根节点进行右旋转
template <class T>
Red_Black_Node<T>* Red_Black_Node<T>::RightRotate() {
    Red_Black_Node* temp_parent = this->parent;
    Red_Black_Node* temp = this->left;
    this->left->right->parent = this;
    this->left = this->left->right;
    this->parent = temp;
    temp->right = this;
    if (temp_parent != nullptr) {
        if (this == temp_parent->left) {
            temp_parent->left = temp;
        }
        else {
            temp_parent->right = temp;
        }
        temp->parent = temp_parent;
    }
    else {
        temp->parent = nullptr;
    }
    return temp;
}


template <class T>
void Red_Black_Node<T>::Set_Color(Color new_color) {
    this->node_color = new_color;
}

template <class T>
void Red_Black_Node<T>::SetValue(T new_value) {
    this->value = new_value;
}

// 为当前节点的父节点设置一个新的孩子节点, 当前节点仍然指向这个父节点
template <class T>
void Red_Black_Node<T>::SetNewChild(Red_Black_Node* new_child) {
    if (this->parent == nullptr) {
        return;
    }
    if (this == this->parent->left) {
        this->parent->left = new_child;
    }
    else {
        this->parent->right = new_child;
    }
    new_child->parent = this->parent;
}

template <class T>
Red_Black_Node<T>* Red_Black_Node<T>::GetUncle() {
    if (this->parent == nullptr || this->parent->parent == nullptr) {
        return nullptr;
    }
    if (this->parent == this->parent->parent->left) {
        return this->parent->parent->right;
    }
    return this->parent->parent->left;
}

template <class T>
Red_Black_Node<T>* Red_Black_Node<T>::GetSibling() {
    if (this->parent == nullptr) {
        return nullptr;
    }
    if (this == this->parent->left) {
        return this->parent->right;
    }
    return this->parent->left;
}

template <class T>
Red_Black_Node<T>* Red_Black_Node<T>::GetCloseNephew() {
    // 如果当前节点存在兄弟节点, 并且兄弟节点不是NIL节点
    // 那么可以获取当前节点的侄子节点
    if (this->GetSibling() != nullptr && !this->GetSibling()->NIL) {
        if (this == this->parent->left) {
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
    if (this->GetSibling() != nullptr && !this->GetSibling()->NIL) {
        if (this == this->parent->left) {
            return this->GetSibling()->right;
        }
        return this->GetSibling()->left;
    }
    return nullptr;
}

template class Red_Black_Node<int>;
template class Red_Black_Node<short>;
template class Red_Black_Node<long>;
template class Red_Black_Node<long long>;

