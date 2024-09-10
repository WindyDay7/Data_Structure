#include "Red_Black_Tree.hpp"
#include "Red_Black_Show.hpp"

template<class T>
void Red_Black_Tree<T>::display(Red_Black_Node<T>* root) {
    initCoordinate(root);
    const int widthZoom = 3;
    printf("width zoom: %d\n", widthZoom);
    Canvas::resetBuffer();
    std::queue<Red_Black_Node<T>*> q;
    q.push(root);
    int x, y;
    std::string sval;
    while (!q.empty())
    {
        auto p = q.front();
        q.pop();
        bool l = (p->left != nullptr);
        bool r = (p->right != nullptr);
        if (p->node_color == Color::RED) {
            x = p->x, y = p->y, sval = std::to_string(0 - p->value);
        }
        else {
            x = p->x, y = p->y, sval = std::to_string(p->value);
        }
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
            if (p->node_color == Color::RED) {
                Canvas::put(2 * y + 1, widthZoom * x, '_',
                    widthZoom * (p->right->x - x) + std::to_string(0 - p->right->value).length());
            }
            else {
                Canvas::put(2 * y + 1, widthZoom * x, '_',
                    widthZoom * (p->right->x - x) + std::to_string(p->right->value).length());
            }

        }
        if (l || r)
            Canvas::put(2 * y + 1, widthZoom * x + sval.length() / 2, "|");
    }
    Canvas::draw();
}

template<class T>
void Red_Black_Tree<T>::initX(Red_Black_Node<T>* p, int& x)
{
    if (p == nullptr)
        return;
    initX(p->left, x);
    p->x = x++;
    initX(p->right, x);
}

template<class T>
void Red_Black_Tree<T>::initY(Red_Black_Node<T>* root)
{
    if (root == nullptr)
        return;

    typedef std::pair<Red_Black_Node<T>*, int> Node;

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
void Red_Black_Tree<T>::initCoordinate(Red_Black_Node<T>* root)
{
    int x = 0;
    initX(root, x);
    initY(root);
}

char Canvas::buffer[Canvas::HEIGHT][Canvas::WIDTH + 1];
template class Red_Black_Tree<int>;
template class Red_Black_Tree<short>;
template class Red_Black_Tree<long>;
template class Red_Black_Tree<long long>;
// template class Red_Black_Tree<std::string>;
template class Red_Black_Node<int>;
template class Red_Black_Node<short>;
template class Red_Black_Node<long>;
template class Red_Black_Node<long long>;
// template class Red_Black_TreeNode<std::string>;
