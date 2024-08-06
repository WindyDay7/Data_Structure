#include "AVL_Tree.hpp"

template<class T>
bool AVLTree<T>::empty() const {
    return root == nullptr;
}

template <class T>
AVLTree<T>::AVLTree() {
    root = nullptr;
    _size = 0;
}

template <class T>
AVLTree<T>::~AVLTree() {
    clear();
}

template <class T>
void AVLTree<T>::clear() {
    std::vector<AVLTreeNode<T>*> stack;
    
    if (root != nullptr)
        stack.push_back(root);
    
    while (!stack.empty()){
        AVLTreeNode<T> *node = stack.back();
        stack.pop_back();
        
        if (node->left != nullptr)
            stack.push_back(node->left);
        
        if (node->right != nullptr)
            stack.push_back(node->right);
        
        _size--;
        delete node;
    }
    
    root = nullptr;
}

template <class T>
void AVLTree<T>::display() {
    printf("\n");
    if (root != nullptr)
        display(root);
    else
        printf("Empty");
    printf("\n");
}


template <class T>
int AVLTree<T>::find(T value) const {
    AVLTreeNode<T> *direct = root;
    int idx = 0;
    while (direct != nullptr && direct->value != value) {
        if(direct->value < value) {
            idx += direct->left==nullptr? 0:direct->left->count +1;
            direct = direct->right;
        }
        else {
            direct = direct->left;
        }
    }
    if(direct == nullptr) {
        return -1;
    }
    return idx + direct->left==nullptr? 0:direct->left->count;
}

template <class T>
void AVLTree<T>::balance(std::vector<AVLTreeNode<T>*>& path) {
    // 将路径设置为从下到上, 从叶子节点到根节点
    std::reverse(path.begin(), path.end());
    // 新建一个假的根节点作为当前根节点的根节点
    AVLTreeNode<T>* pre_root = new AVLTreeNode<T>(path.back()->value);
    pre_root->left = path.back();
    for(size_t i = 0; i<path.size()-1; i++) {
        AVLTreeNode<T>* avltree_node = path[i];
        // 更新从叶子节点到根节点的高度与count, 高度可能会修改, count一定会+1
        // 前面的节点可能存在调整, 需要更新节点的信息
        avltree_node->updateValues();
        if(avltree_node->balanceFactor() == 2) {
            if(path[i-1]->balanceFactor() == -1) {
                avltree_node->left = path[i-1]->left_rotate();
            }
            else {
                if(path[i+1]->left == avltree_node) {
                    path[i+1]->left=avltree_node->right_rotate();
                }
                else {
                    path[i+1]->right=avltree_node->right_rotate();
                }
            }
        }
        else if (avltree_node->balanceFactor() == -2) {
            if(path[i-1]->balanceFactor() == 1) {
                avltree_node->right = path[i-1]->right_rotate();
            }
            else {
                if(path[i+1]->left == avltree_node) {
                    path[i+1]->left=avltree_node->left_rotate();
                }
                else {
                    path[i+1]->right=avltree_node->left_rotate();
                }
            }
        }
    }
    root = pre_root->left;
    pre_root->left = nullptr;
    delete pre_root;
    return;
}

template<class T>
void AVLTree<T>::insert(T value) {
    std::vector<AVLTreeNode<T>*> insert_path;
    AVLTreeNode<T>* direct = root;
    // 找到插入的节点
    while(direct!=nullptr && direct->value != value) {
        insert_path.emplace_back(direct);
        if(direct->value < value) {
            direct = direct->right;
        }
        else {
            direct = direct->left;
        }
    }
    // 如果这个节点已经存在, 直接返回
    if(direct != nullptr) {
        return;
    }
    // 新建插入的节点
    AVLTreeNode<T>* new_node = new AVLTreeNode<T>(value);
    if(root == nullptr) {
        root = new_node;
        return;
    }
    new_node->height = insert_path.back()->height+1;
    // 将新的节点插入到叶子节点的左节点还是右节点
    if(insert_path.back()->value < value) {
        insert_path.back()->right = new_node;
    }
    else {
        insert_path.back()->left = new_node;
    }
    // 需要平衡的节点都在该路径上
    balance(insert_path);
}





