#include "AVL_Tree.hpp"
#include "AVL_Show.hpp"

template<class T>
void AVLTree<T>::display(AVLTreeNode<T>* root) {
    initCoordinate(root);
    const int widthZoom = 3;
    printf("width zoom: %d\n", widthZoom);
    Canvas::resetBuffer();
    std::queue<AVLTreeNode<T> *> q;
    q.push(root);
    int x, y;
    std::string sval;
    while (!q.empty())
    {
        auto p = q.front();
        q.pop();
        bool l = (p->left != nullptr);
        bool r = (p->right != nullptr);
        x = p->x, y = p->y, sval = std::to_string(p->value);
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
                        widthZoom * (p->right->x - x) + std::to_string(p->right->value).length());
        }
        if (l || r)
            Canvas::put(2 * y + 1, widthZoom * x + sval.length() / 2, "|");
    }
    Canvas::draw();
}

template<class T>
void AVLTree<T>::initX(AVLTreeNode<T> *p, int &x)
{
    if (p == nullptr)
        return;
    initX(p->left, x);
    p->x = x++;
    initX(p->right, x);
}

template<class T>
void AVLTree<T>::initY(AVLTreeNode<T> *root)
{
    if (root == nullptr)
        return;

    typedef std::pair<AVLTreeNode<T> *, int> Node;

    root->y = 1;

    std::queue<Node> q;
    q.push(Node(root, root->y));
    while (!q.empty())
    {
        auto p = q.front();
        q.pop();
        if (p.first->left != nullptr)
        {
            p.first->left->y = p.second + 1;
            q.push(Node(p.first->left, p.second + 1));
        }
        if (p.first->right != nullptr)
        {
            p.first->right->y = p.second + 1;
            q.push(Node(p.first->right, p.second + 1));
        }
    }
}

template<class T>
void AVLTree<T>::initCoordinate(AVLTreeNode<T> *root)
{
    int x = 0;
    initX(root, x);
    initY(root);
}

char Canvas::buffer[Canvas::HEIGHT][Canvas::WIDTH + 1];
template class AVLTree<int>;
template class AVLTree<short>;
template class AVLTree<long>;
template class AVLTree<long long>;
// template class AVLTree<std::string>;
template class AVLTreeNode<int>;
template class AVLTreeNode<short>;
template class AVLTreeNode<long>;
template class AVLTreeNode<long long>;
// template class AVLTreeNode<std::string>;
