#include "Red_Black_Node.hpp"
#include "Red_Black_Tree.hpp"

template <class T>
int Red_Black_Tree<T>::InsertBalanceAction(Red_Black_Node<T>* node) {
    // 走到根节点了, 将该节点设为根节点, 为黑色
    if (node->parent == nullptr) {
        return 0;
    }
    // 如果当前节点的父节点存在并且为黑色
    if (node->parent->node_color == Color::BLACK) {
        return 1;
    }
    // 如果父节点是红色
    if (node->parent->node_color == Color::RED) {
        // 因为父亲节点是红色节点, 就一定不是根节点, 所以当前节点一定存在叔叔节点
        // 如果叔叔节点为红色
        if (node->GetUncle()->node_color == Color::RED) {
            return 2;
        }
        else {
            // 如果叔叔节点为黑色, 需要判断该节点的旋转方向
            if (node == node->parent->left && node->parent == node->parent->parent->left) {
                return 3;
            }
            else if (node == node->parent->right && node->parent == node->parent->parent->right) {
                return 4;
            }
            else if (node == node->parent->right && node->parent == node->parent->parent->left) {
                return 5;
            }
            else if (node == node->parent->left && node->parent == node->parent->parent->right) {
                return 6;
            }
            return -1;
        }
    }
    return -1;
}

template <class T>
void Red_Black_Tree<T>::InsertBalanceAdjust(Red_Black_Node<T>* node) {
    Red_Black_Node<T>* temp_node = nullptr;
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
        temp_node = this->parent->parent->RightRotate();
        if (node->parent->parent->parent == nullptr) {
            this->root = temp_node;
        }
        break;
    case 4:
        node->Set_Color(Color::RED);
        node->parent->Set_Color(Color::BLACK);
        node->parent->parent->Set_Color(Color::RED);
        temp_node = this->parent->parent->LeftRotate();
        if (node->parent->parent->parent == nullptr) {
            this->root = temp_node;
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
    while (direct != nullptr && direct->value != value && !direct->NIL) {
        pre_direct = direct;
        if (direct->value < value) {
            direct = direct->right;
        }
        else {
            direct = direct->left;
        }
    }
    // 如果这个节点不是NIL节点, 该值已存在
    if (!direct->NIL) {
        return;
    }
    // 新建插入的节点
    Red_Black_Node<T>* new_node = new Red_Black_Node<T>(value, Color::RED, false);
    if (this->root == nullptr) {
        this->root = new_node;
        Red_Black_Node<T>* new_left_node = new Red_Black_Node<T>(0, Color::BLACK, true);
        Red_Black_Node<T>* new_right_node = new Red_Black_Node<T>(0, Color::BLACK, true);
        this->root->left = new_left_node;
        this->root->right = new_right_node;
        return;
    }
    if (direct == pre_direct->left) {
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
    InsertBalanceAdjust(new_node);
}

template <class T>
int Red_Black_Tree<T>::RemoveBalanceAction(Red_Black_Node<T>* node) {
    if (node->node_color == Color::RED) {
        return 1;
    }
    else {
        if ((node->left->NIL && !node->right->NIL && node->right->node_color == Color::RED) || (node->right->NIL && !node->left->NIL && node->left->node_color == Color::RED)) {
            return 2;
        }
        // 如果父节点不存在
        if (node->parent == nullptr) {
            return 3;
        }
        // 如果父节点为红色
        else if (node->parent->node_color == Color::RED) {
            // 父节点为红色一定存在邻近侄子节点, 或者邻近侄子节点为NIL节点, 黑色节点
            if (node->GetCloseNephew()->node_color == Color::BLACK) {
                return 4;
            }
            if (node->GetCloseNephew()->node_color == Color::RED) {
                return 5;
            }
        }
        // 如果父节点为黑色
        else {
            // 如果兄弟节点为红色, 进行一次转换后进入父节点为红色的场景
            if (node->GetSibling()->node_color == Color::RED) {
                return 6;
            }
            // 如果兄弟节点是黑色
            if (node->GetSibling()->node_color == Color::BLACK) {
                // 如果远侄子节点是红色, 需要进行一次旋转
                if (node->GetFarNephew()->node_color == Color::RED) {
                    return 7;
                }
                else {
                    // 如果兄弟节点是黑色, 邻近侄子节点是红色
                    if (node->GetCloseNephew()->node_color == Color::RED) {
                        return 8;
                    }
                    else {
                        return 9;
                    }
                }
            }
        }
    }
    return -1;
}


template <class T>
void Red_Black_Tree<T>::RemoveBalanceAdjust(Red_Black_Node<T>* node) {
    Red_Black_Node<T>* node_child = node->left->NIL ? node->right : node->left;
    Red_Black_Node<T>* temp_node = nullptr;
    switch (this->RemoveBalanceAction(node)) {
    case 1:
        node->SetNewChild(node_child);
        break;
    case 2:
        if (node->left->NIL) {
            node->right->Set_Color(Color::BLACK);
        }
        else {
            node->left->Set_Color(Color::BLACK);
        }
        node->SetNewChild(node_child);
        break;
    case 3:
        this->root = node_child;
        break;
    case 4:
        if (node == node->parent->left) {
            temp_node = node->parent->LeftRotate();
        }
        else {
            temp_node = node->parent->RightRotate();
        }
        if (node->parent->parent == nullptr) {
            this->root = temp_node;
        }
        // 在树的结构中删除当前节点
        node->SetNewChild(node_child);
        break;
    case 5:
        node->parent->Set_Color(Color::BLACK);
        if (node == node->parent->left) {
            node->parent->left = node_child;
            temp_node = node->parent->LeftRotate();
        }
        else {
            node->GetSibling()->LeftRotate();
            temp_node = node->parent->RightRotate();
        }
        // 如果父节点就是根节点, 那么旋转之后的节点为新的根节点
        if (node->parent->parent == nullptr) {
            this->root = temp_node;
        }
        // 在树的结构中删除当前节点
        node->SetNewChild(node_child);
        break;
    case 6:
        node->parent->Set_Color(Color::RED);
        node->GetSibling()->Set_Color(Color::BLACK);
        if (node == node->parent->left) {
            temp_node = node->parent->LeftRotate();
        }
        else {
            temp_node = node->parent->RightRotate();
        }
        if (node->parent->parent == nullptr) {
            this->root = temp_node;
        }
        RemoveBalanceAdjust(node);
        return;
        break;
    case 7:
        node->GetFarNephew()->Set_Color(Color::BLACK);
        if (node == node->parent->left) {
            temp_node = node->parent->LeftRotate();
        }
        else {
            temp_node = node->parent->RightRotate();
        }
        if (node->parent->parent == nullptr) {
            this->root = temp_node;
        }
        // 在树的结构中删除当前节点
        node->SetNewChild(node_child);
        break;
    case 8:
        if (node == node->parent->left) {
            node->GetSibling()->LeftRotate();
            temp_node = node->parent->RightRotate();
        }
        else {
            node->GetSibling()->RightRotate();
            temp_node = node->parent->LeftRotate();
        }
        if (node->parent->parent == nullptr) {
            this->root = temp_node;
        }
        // 在树的结构中删除当前节点
        node->SetNewChild(node_child);
        break;
    case 9:
        node->GetSibling()->Set_Color(Color::RED);
        node->SetNewChild(node_child);
        node->parent = node->parent->parent;
        // 如果当前节点是父节点的左子节点
        if (node == node->parent->left) {
            if (node->left->NIL) {
                node->parent->left = node->right;
                node->right->parent = node->parent;
                // 此时还未修改node.parent
                node->right = node->parent;
                // 如果node节点的父节点是根节点
                if (node->parent->parent == nullptr) {
                    node->parent = nullptr;
                    this->root = node;
                }
                else {
                    node->parent = node->parent->parent;
                    if (node->parent == node->parent->left) {
                        node = node->parent->left;
                    }
                    else {
                        node = node->parent->right;
                    }
                }
            }
            else {
                // 如果当前节点的左节点为非 NIL 节点
                node->parent->left = node->left;
                node->left->parent = node->parent;
                // 此时还未修改node.parent
                node->left = node->parent;
                // 如果node节点的父节点是根节点
                if (node->parent->parent == nullptr) {
                    node->parent = nullptr;
                    this->root = node;
                }
                else {
                    node->parent = node->parent->parent;
                    if (node->parent == node->parent->left) {
                        node = node->parent->left;
                    }
                    else {
                        node = node->parent->right;
                    }
                }
            }
        }
        // 如果当前节点是父节点的右子节点
        else {
            if (node->left->NIL) {
                // 因为当前节点是父节点的右子节点
                node->parent->right = node->right;
                node->right->parent = node->parent;
                // 此时还未修改node.parent
                node->right = node->parent;
                // 如果node节点的父节点是根节点
                if (node->parent->parent == nullptr) {
                    node->parent = nullptr;
                    this->root = node;
                }
                else {
                    node->parent = node->parent->parent;
                    if (node->parent == node->parent->left) {
                        node = node->parent->left;
                    }
                    else {
                        node = node->parent->right;
                    }
                }
            }
            else {
                // 如果当前节点的左节点为非 NIL 节点
                node->parent->right = node->left;
                node->left->parent = node->parent;
                // 此时还未修改node.parent
                node->left = node->parent;
                // 如果node节点的父节点是根节点
                if (node->parent->parent == nullptr) {
                    node->parent = nullptr;
                    this->root = node;
                }
                else {
                    node->parent = node->parent->parent;
                    if (node->parent == node->parent->left) {
                        node = node->parent->left;
                    }
                    else {
                        node = node->parent->right;
                    }
                }
            }
        }
        break;

    default:
        break;
    }
    if (node != nullptr) {
        node->left = node->left->NIL ? node->left : nullptr;
        node->right = node->right->NIL ? node->right : nullptr;
        node->parent = nullptr;
        delete node;
        node = nullptr;
    }
}

template <class T>
void Red_Black_Tree<T>::erase(T value) {
    Red_Black_Node<T>* delete_node = nullptr;
    Red_Black_Node<T>* pre_delete_node = nullptr;
    Red_Black_Node<T>* find_node = this->root;
    while (find_node != nullptr && find_node->value != value && !find_node->NIL) {
        if (find_node->value < value) {
            find_node = find_node->right;
        }
        else {
            find_node = find_node->left;
        }
    }
    // 如果找不到要删除的节点, 那么直接返回, 要删除的节点不存在
    if (find_node->NIL) {
        return;
    }
    // 找到该节点的直接后续节点
    // 如果左子树或者右子树为空, 那么可以直接删除该节点, 将后续节点补上来
    if (find_node->left->NIL || find_node->right->NIL) {
        delete_node = find_node;
        RemoveBalanceAdjust(delete_node);
        return;
    }
    // 找到当前节点的右子树节点
    delete_node = find_node->right;
    // 找到右子树的最左边的叶子节点, 作为直接后续节点
    while (!delete_node->left->NIL) {
        delete_node = delete_node->left;
    }
    find_node->SetValue(delete_node->value);
    RemoveBalanceAdjust(delete_node);
    return;
}




