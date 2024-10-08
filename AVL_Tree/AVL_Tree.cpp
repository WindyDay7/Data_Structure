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
        // 如果左子树的高度比右子树的高度大2, 那么需要调整
        if (avltree_node->balanceFactor() == 2) {
            // 如果这棵子树的左子树需要调整, 进行调整
            if (avltree_node->left->balanceFactor() == -1) {
                avltree_node->left = avltree_node->left->left_rotate();
            }
            // 这里需要判断返回的子树的根节点是父节点的左子树还是右子树
            if (path[i + 1]->left == avltree_node) {
                path[i + 1]->left = avltree_node->right_rotate();
            }
            else {
                path[i + 1]->right = avltree_node->right_rotate();
            }
        }
        else if (avltree_node->balanceFactor() == -2) {
            if (avltree_node->right->balanceFactor() == 1) {
                avltree_node->right = avltree_node->right->right_rotate();
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
    AVLTreeNode<T>* direct = root;              // 遍历访问的节点
    AVLTreeNode<T>* temp_node = nullptr;        // 临时保存需要删除的节点
    AVLTreeNode<T>* pre_direct = nullptr;       // 删除节点的直接后续节点(叶子节点)的父节点
    AVLTreeNode<T>* pre_delete = nullptr;       // 被删除节点的父节点
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
    // 临时保存需要删除的节点
    temp_node = direct;
    // 如果删除的节点左右子树都没有, 也就是删除叶子节点
    if (direct->left == nullptr && direct->right == nullptr) {
        if(pre_delete->value > value) {
            pre_delete->left = nullptr;
        }
        else {
            pre_delete->right = nullptr;
        }
        delete direct;
        balance(find_path);
        return;
    }
    // 设置被保存的节点
    pre_direct = pre_delete;
    // 如果当前节点存在右子树
    if(direct->right != nullptr) {
        // 找到该节点的右子树的最左节点, 将该节点替换需要删除的节点
        pre_direct = direct;
        direct = direct->right;
    }
    else {
        pre_direct = direct;
        direct = direct->left;
    }
    // 找到被删除节点的直接后续节点, 这个节点就是叶子节点
    while (direct != nullptr && direct->left != nullptr) {
        change_path.emplace_back(direct);
        pre_direct = direct;
        direct = direct->left;
    }
    // 找到需要替换的节点, 将这个节点与需要删除的节点替换
    pre_direct->left = direct->right;             // 将叶子节点隔开
    // 如果被删除的节点是根节点
    if (pre_delete != nullptr) {
        if (pre_delete->value < value) {
            pre_delete->right = direct;
        }
        else {
            pre_delete->left = direct;
        }
    }
    // 替换需要删除的节点
    if(temp_node->left == direct) {
        direct->left = nullptr;
    }
    else {
        direct->left = temp_node->left;
    }
    if(temp_node->right == direct) {
        direct->right = nullptr;
    }
    else {
        direct->right = temp_node->right;
    }
    // 将替换后的节点删除
    temp_node->left = nullptr;
    temp_node->right = nullptr;
    delete temp_node;
    // 将后续节点添加到修改路径中
    find_path.emplace_back(direct);
    find_path.insert(find_path.end(), change_path.begin(), change_path.end());
    balance(find_path);
    return;
}


template class AVLTree<int>;
template class AVLTree<short>;
template class AVLTree<long>;
template class AVLTree<long long>;
// template class AVLTree<std::string>;


