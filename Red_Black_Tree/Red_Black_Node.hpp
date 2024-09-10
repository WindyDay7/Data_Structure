//  Created by Kadir Emre Oto on 06.08.2018.

#ifndef Red_Black_Node_hpp
#define Red_Black_Node_hpp

#include <string>
#include <algorithm>

// 定义颜色枚举类型
enum Color { RED, BLACK };

template <class T>
struct Red_Black_Node {
    Red_Black_Node* left;
    Red_Black_Node* right;
    Red_Black_Node* parent;
    //记录坐标, 用于打印
    int x, y;
    T value;                    // 节点的值, 红黑树中节点的值是必须可以改变的
    Color node_color;           // 节点的颜色
    bool NIL;                   // 该节点是否是 NIL 节点
    Red_Black_Node(T value, Color node_color, bool NIL);    // 构造函数
    void Set_Color(Color new_color);
    void SetValue(T new_value);
    // 将当前节点的父节点指向新的对应的孩子节点 new_child
    void SetNewChild(Red_Black_Node* new_child);
    Red_Black_Node* LeftRotate();
    Red_Black_Node* RightRotate();
    Red_Black_Node* GetUncle();
    Red_Black_Node* GetSibling();
    Red_Black_Node* GetCloseNephew();
    Red_Black_Node* GetFarNephew();
};

#endif /* Red_Black_Node_hpp */
