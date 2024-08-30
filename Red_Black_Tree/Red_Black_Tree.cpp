#include "Red_Black_Node.hpp"
#include "Red_Black_Tree.hpp"

template <class T>
int Red_Black_Tree<T>::InsertBalanceAction(Red_Black_Node<T>* node) {
    // 走到根节点了, 将该节点设为根节点, 为黑色
    if(node->parent == nullptr) {
        return 0;
    }
    // 如果当前节点的父节点存在并且为黑色
    if(node->parent->node_color == Color::BLACK) {
        return 1;
    }
    // 如果父节点是红色
    if(node->parent->node_color == Color::RED) {
        // 因为父亲节点是红色节点, 就一定不是根节点, 所以当前节点一定存在叔叔节点
        // 如果叔叔节点为红色
        if(node->GetUncle()->node_color == Color::RED) {
            return 2;
        }
        else {
            // 如果叔叔节点为黑色, 需要判断该节点的旋转方向
            if(node == node->parent->left && node->parent == node->parent->parent->left) {
                return 3;
            }
            else if(node == node->parent->right && node->parent == node->parent->parent->right) {
                return 4;
            }
            else if(node == node->parent->right && node->parent == node->parent->parent->left) {
                return 5;
            }
            else if(node == node->parent->left && node->parent == node->parent->parent->right) {
                return 6;
            }
            return -1;
        }
    }
    return -1;
}

template <class T>
void Red_Black_Tree<T>::InsertBalanceAdjust(Red_Black_Node<T>* node) {
    switch (this->InsertBalanceAction(node))
    {
    case 0:
        node->Set_Color(Color::BLACK);
        break;
    case 1:
        node->Set_Color(Color::RED);
        break;
    case 2:
        node->Set_Color(Color::RED);
        node->parent->Set_Color(Color::BLACK);
        node->GetUncle()->Set_Color(Color::BLACK);
        InsertBalanceAdjust(node->parent->parent);
        break;
    case 3:
        node->Set_Color(Color::RED);
        node->parent->Set_Color(Color::BLACK);
        node->parent->parent->Set_Color(Color::RED);
        if(node->parent->parent->parent == nullptr) {
            this->root = node->parent->parent->RightRotate();
        }
        else if(node->parent->parent->parent->left == node->parent->parent) {
            node->parent->parent->parent->left = node->parent->parent->RightRotate();
        }
        else if(node->parent->parent->parent->right == node->parent->parent){
            node->parent->parent->parent->right = node->parent->parent->RightRotate();
        }
        break;
    case 4:
        node->Set_Color(Color::RED);
        node->parent->Set_Color(Color::BLACK);
        node->parent->parent->Set_Color(Color::RED);
        if(node->parent->parent->parent == nullptr) {
            this->root = node->parent->parent->LeftRotate();
        }
        else if(node->parent->parent->parent->left == node->parent->parent) {
            node->parent->parent->parent->left = node->parent->parent->LeftRotate();
        }
        else if(node->parent->parent->parent->right == node->parent->parent){
            node->parent->parent->parent->right = node->parent->parent->LeftRotate();
        }
        break;
    case 5:
        node->Set_Color(Color::RED);
        node->parent->parent->Set_Color(Color::RED);
        node->parent->parent->left = node->parent->LeftRotate();
        // 实际问题被转换为case3 解决
        InsertBalanceAdjust(node->left);
        break;
    case 6:
        node->Set_Color(Color::RED);
        node->parent->parent->Set_Color(Color::RED);
        node->parent->parent->right = node->parent->RightRotate();
        // 实际问题被转换为case4 解决
        InsertBalanceAdjust(node->right);
    default:
        break;
    }
}

template <class T>
void Red_Black_Tree<T>::insert(T value) {
    Red_Black_Node<T>* direct = this->root;
    Red_Black_Node<T>* pre_direct = this->root;
    while(direct != nullptr && direct->value != value && !direct->NIL) {
        pre_direct = direct;
        if(direct->value < value) {
            direct = direct->right;
        }
        else {
            direct = direct->left;
        }
    }
    // 如果这个节点不是NIL节点, 该值已存在
    if(!direct->NIL) {
        return;
    }
    // 新建插入的节点
    Red_Black_Node<T>* new_node = new Red_Black_Node<T>(value, Color::RED, false);
    if(this->root == nullptr) {
        this->root = new_node;
        Red_Black_Node<T>* new_left_node = new Red_Black_Node<T>(0, Color::BLACK, true);
        Red_Black_Node<T>* new_right_node = new Red_Black_Node<T>(0, Color::BLACK, true);
        this->root->left = new_left_node;
        this->root->right = new_right_node;
        return;
    }
    if(direct == pre_direct->left) {
        Red_Black_Node<T>* new_right_node = new Red_Black_Node<T>(0, Color::BLACK, true);
        new_node->left = pre_direct->left;
        new_node->right = new_right_node;
        pre_direct->left = new_node;
    }
    else {
        Red_Black_Node<T>* new_left_node = new Red_Black_Node<T>(0, Color::BLACK, true);
        new_node->right = pre_direct->right;
        new_node->left = new_left_node;
        pre_direct->right = new_node;
    }
}




