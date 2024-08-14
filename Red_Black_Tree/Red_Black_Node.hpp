//  Created by Kadir Emre Oto on 06.08.2018.

#ifndef Red_Black_Node_hpp
#define Red_Black_Node_hpp

#include <string>
#include <algorithm>

// 定义颜色枚举类型
enum Color { RED, BLACK };

template <class T>
struct Red_Black_Node {
    Red_Black_Node *left;
    Red_Black_Node *right;
    Red_Black_Node *parent;
    //记录坐标, 用于打印
    int x, y;
    T value;        // 节点的值, 红黑树中节点的值是必须可以改变的
    Color node_color;           // 节点的颜色
    Red_Black_Node(T value);
    void updateValues();
    int Balance_Action();       // 返回红黑树需要进行的不同类型的操作
    void Set_Color(Color new_color);
    Red_Black_Node* left_rotate();
    Red_Black_Node* right_rotate();
};

#endif /* Red_Black_Node_hpp */
