#include "AVL_Tree.hpp"
#include "AVLTree_Node.hpp"

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

    while (!stack.empty()) {
        AVLTreeNode<T>* node = stack.back();
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
    AVLTreeNode<T>* direct = root;
    int idx = 0;
    while (direct != nullptr && direct->value != value) {
        if (direct->value < value) {
            idx += direct->left == nullptr ? 0 : direct->left->count + 1;
            direct = direct->right;
        }
        else {
            direct = direct->left;
        }
    }
    if (direct == nullptr) {
        return -1;
    }
    return idx + direct->left == nullptr ? 0 : direct->left->count;
}

template <class T>
void AVLTree<T>::balance(std::vector<AVLTreeNode<T>*>& path) {
    // 将路径设置为从下到上, 从叶子节点到根节点
    std::reverse(path.begin(), path.end());
    // 新建一个假的根节点作为当前根节点的根节点
    AVLTreeNode<T>* pre_root = new AVLTreeNode<T>(path.back()->value);
    pre_root->left = path.back();
    path.emplace_back(pre_root);
    for (size_t i = 0; i < path.size() - 1; i++) {
        AVLTreeNode<T>* avltree_node = path[i];
        // 更新从叶子节点到根节点的高度与count, 高度可能会修改, count一定会+1
        // 前面的节点可能存在调整, 需要更新节点的信息
        avltree_node->updateValues();
        if (avltree_node->balanceFactor() == 2) {
            if (path[i - 1]->balanceFactor() == -1) {
                avltree_node->left = path[i - 1]->left_rotate();
            }
            if (path[i + 1]->left == avltree_node) {
                path[i + 1]->left = avltree_node->right_rotate();
            }
            else {
                path[i + 1]->right = avltree_node->right_rotate();
            }
        }
        else if (avltree_node->balanceFactor() == -2) {
            if (path[i - 1]->balanceFactor() == 1) {
                avltree_node->right = path[i - 1]->right_rotate();
            }
            if (path[i + 1]->left == avltree_node) {
                path[i + 1]->left = avltree_node->left_rotate();
            }
            else {
                path[i + 1]->right = avltree_node->left_rotate();
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
    while (direct != nullptr && direct->value != value) {
        insert_path.emplace_back(direct);
        if (direct->value < value) {
            direct = direct->right;
        }
        else {
            direct = direct->left;
        }
    }
    // 如果这个节点已经存在, 直接返回
    if (direct != nullptr) {
        return;
    }
    // 新建插入的节点
    AVLTreeNode<T>* new_node = new AVLTreeNode<T>(value);
    if (root == nullptr) {
        root = new_node;
        return;
    }
    // 将新的节点插入到叶子节点的左节点还是右节点
    if (insert_path.back()->value < value) {
        insert_path.back()->right = new_node;
    }
    else {
        insert_path.back()->left = new_node;
    }
    // 需要平衡的节点都在该路径上
    balance(insert_path);
}

template<class T>
void AVLTree<T>::erase(T value) {
    std::vector<AVLTreeNode<T>*> find_path;
    std::vector<AVLTreeNode<T>*> change_path;
    AVLTreeNode<T>* direct = root;
    AVLTreeNode<T>* temp_node = nullptr;
    AVLTreeNode<T>* pre_direct = nullptr;
    AVLTreeNode<T>* pre_delete = nullptr;
    // 找到插入的节点
    while (direct != nullptr && direct->value != value) {
        find_path.emplace_back(direct);
        pre_delete = direct;
        if (direct->value < value) {
            direct = direct->right;
        }
        else {
            direct = direct->left;
        }
    }
    // 找不到该节点
    if (direct == nullptr) {
        std::cout << "The Value would bd deleted not found in the tree" << std::endl;
        return;
    }
    // 找到该节点的右子树的最左节点, 将该节点替换需要删除的节点
    if (direct->right == nullptr) {
        balance(find_path);
        return;
    }
    direct = direct->right;
    pre_direct = direct;
    while (direct != nullptr && direct->left != nullptr) {
        find_path.emplace_back(direct);
        pre_direct = direct;
        direct = direct->left;
    }
    // 找到需要替换的节点, 将这个节点与需要删除的节点替换
    pre_direct->left = nullptr;
    // 如果被删除的节点是根节点
    if (pre_delete != nullptr) {
        if (pre_delete->value < value) {
            pre_delete->left = direct;
        }
        else {
            pre_delete->right = direct;
        }
    }
    // 替换需要删除的节点
    direct->left = temp_node->left;
    direct->right = temp_node->right;
    // 将替换后的节点删除
    temp_node->left = nullptr;
    temp_node->right = nullptr;
    delete temp_node;
}


template class AVLTree<int>;
template class AVLTree<short>;
template class AVLTree<long>;
template class AVLTree<long long>;
// template class AVLTree<std::string>;


