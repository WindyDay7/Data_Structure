#include "AVL_Tree.hpp"
#include "AVLTree_Node.hpp"
#include <vector>
#include <algorithm>


template<class T>
bool AVLTree<T>::empty() const {
    return root == nullptr;
}

template<class T>
void AVLTree<T>::display(AVLTreeNode<T>* cur) {
    const int widthZoom = 3;
    printf("width zoom: %d\n", widthZoom);
    Canvas::resetBuffer();
    std::queue<AVLTreeNode<T> *> q;
    q.push(root);
    int x, y, val;
    std::string sval;
    while (!q.empty())
    {
        auto p = q.front();
        q.pop();
        bool l = (p->left != nullptr);
        bool r = (p->right != nullptr);
        x = p->x, y = p->y, val = p->val, sval = to_string(p->val);
        Canvas::put(2 * y, widthZoom * x, sval);
        if (l)
        {
            q.push(p->left);
            Canvas::put(2 * y + 1, widthZoom * p->left->x, '_', 
                        widthZoom * (x - p->left->x) + sval.length() / 2);
        }
        if (r)
        {
            q.push(p->right);
            Canvas::put(2 * y + 1, widthZoom * x, '_',
                        widthZoom * (p->right->x - x) + to_string(p->right->val).length());
        }
        if (l || r)
            Canvas::put(2 * y + 1, widthZoom * x + sval.length() / 2, "|");
    }
    Canvas::draw();
}

template <class T>
int AVLTree<T>::find(T value) const{
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
    // 更新从叶子节点到根节点的高度与count, 高度可能会修改, count一定会+1
    for(AVLTreeNode<T>*& avltree_node: path) {
        avltree_node->updateValues();
    }
    for(int i = 0; i<path.size(); i++) {
        AVLTreeNode<T>* avltree_node = path[i];
        // 前面的节点可能存在调整, 需要更新节点的信息
        avltree_node->updateValues();
        if(avltree_node->balanceFactor() == 2) {
            if(path[i-1]->balanceFactor() == 1) {
                avltree_node->right_rotate();
            }
            else {
                path[i-1]->left_rotate();
                avltree_node->right_rotate();
            }
        }
        else if (avltree_node->balanceFactor() == -2) {
            if(path[i-1]->balanceFactor() == -1) {
                avltree_node->left_rotate();
            }
            else {
                path[i-1]->right_rotate();
                avltree_node->right_rotate();
            }
        }
    }
    return;
}

template<class T>
void AVLTree<T>::insert(T value) {
    std::vector<AVLTree<T>*> insert_path;
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
    new_node->height = insert_path.back()->height+1;
    // 将新的节点插入到叶子节点的左节点还是右节点
    if(insert_path.back()->value < value) {
        insert_path.back()->right = new_node;
    }
    else {
        insert_path.back()->left = new_node;
    }
    // 需要平衡的节点都在该路径上
    balance(std::move(insert_path));
}





