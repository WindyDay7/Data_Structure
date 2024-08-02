#include <iostream>
#include <math.h>
using namespace std;

template<class T, int Order>
struct Node {
    //Node *Parent;
    int NumbersOfKeys; //number of the actual keys
    int position = -1; //to allocate value in the appropriate place
    // key数组, 最多有 Order 个 Keys, T 表示是 Value类型的数组
    T keys[Order];
    // 子节点数组, 最多有 Order 个子节点
    Node* childs[Order + 1];

    Node();
    int Insert(T value);
    int Remove(T value);
    Node* split(Node* node, T* value);
    void Merge(int node_pos, Node* left_node, Node* right_node);
    void Print();
    void PrintUtil(int height, bool checkParent);
    int getHeight();
    ~Node();
};

//Node implementation
template <class T, int Order>
Node<T, Order>::Node() : NumbersOfKeys(0) {
    for (int i = 0; i <= Order; ++i) {
        childs[i] = nullptr;
    }
}

template <class T, int Order>
Node<T, Order>::~Node() {
    for (int i = this->NumbersOfKeys; i >= 0; i--) {
        if (childs[i] != nullptr) {
            // cout << childs[i]->NumbersOfKeys << endl;
            delete childs[i];
            childs[i] = nullptr;
        }
    }
    // cout << this->NumbersOfKeys << endl;
}


template <class T, int Order>
int Node<T, Order>::Insert(T value) {
    //if the node is leaf, 如果该节点是叶子节点
    if (this->childs[0] == nullptr) {
        // position 位置修改, 记录Value
        this->keys[++this->position] = value;
        ++this->NumbersOfKeys;
        // 将数组中的Key 按照Value的大小排序
        for (int i = this->position; i > 0; i--) {
            if (this->keys[i] < this->keys[i - 1]) std::swap(this->keys[i], this->keys[i - 1]);
        }
    }
    //if the node is not leaf
    else {
        // count to get place of child to put the value in it
        int i = 0;
        // 找到插入的位置, 找到包含value范围的Key
        for (; i < this->NumbersOfKeys && value > this->keys[i];) {
            i++;
        }
        // Check if the child is full to split it, 递归的向下, 在对应的位置插入节点
        int check = this->childs[i]->Insert(value);
        // if node full, 回溯判断节点是否满了, 如果满了向上分裂节点
        if (check) {
            // 找出孩子节点Split之后返回的Value, 这个Value插入当前节点
            T mid;
            int TEMP = i;
            Node<T, Order>* newNode = split(this->childs[i], &mid); //Splitted Node to store the values and child that greater than the midValue
            //allocate midValue in correct place, 为向上一层的Value分配正确的位置
            for (; i < this->NumbersOfKeys && mid > this->keys[i];) {
                i++;
            }
            // 将第i个后面的键值对向后移动一位
            for (int j = this->NumbersOfKeys; j > i; j--) this->keys[j] = this->keys[j - 1];
            // 将分裂后的数据写入到index为i的位置
            this->keys[i] = mid;

            ++this->NumbersOfKeys;
            ++this->position;

            //allocate newNode Splitted in the correct place
            int k;
            for (k = this->NumbersOfKeys; k > TEMP + 1; k--)
                this->childs[k] = this->childs[k - 1];
            // 此时 k==TEMP+1, 该节点指向分裂后的新节点, 因为 this->childs[TEMP] 指向的是分裂之前的节点
            this->childs[k] = newNode;
        }
    }
    // 如果这个节点有 order 个Keys, 那么就有order+1个孩子, 满了, 这个节点需要分裂
    if (this->NumbersOfKeys == Order) return 1; //to split it
    else return 0;
}

template <class T, int Order>
Node<T, Order>* Node<T, Order>::split(Node* node, T* med) //mid to store value of mid and use it in insert func
{
    int NumberOfKeys = node->NumbersOfKeys;
    Node<T, Order>* newNode = new Node<T, Order>();
    //Node<T,Order> *newParentNode = new Node<T,Order>(order);
    int midValue = NumberOfKeys / 2;
    *med = node->keys[midValue];
    int i;
    //take the values after mid value
    for (i = midValue + 1; i < NumberOfKeys; ++i)
    {
        newNode->keys[++newNode->position] = node->keys[i];
        newNode->childs[newNode->position] = node->childs[i];
        ++newNode->NumbersOfKeys;
        --node->position;
        --node->NumbersOfKeys;
        node->keys[i] = 0;
        node->childs[i] = nullptr;
    }
    // 孩子节点的个数要比Key的个数多一个
    newNode->childs[newNode->position + 1] = node->childs[i];
    node->childs[i] = nullptr;

    --node->NumbersOfKeys; //because we take mid value...
    --node->position;
    return newNode;
}

template <class T, int Order>
int Node<T, Order>::Remove(T value) {
    // 如果是叶子节点这一层, 想要删除value节点
    if (this->childs[0] == nullptr) {
        int i = 0;
        // 找到存储值为value的下标, 并将其删除
        while (i < this->NumbersOfKeys && this->keys[i] != value) {
            i++;
        }
        // 如果找不到值为value的下标, 返回错误码 -1
        if (i == this->NumbersOfKeys) {
            return -1;
        }
        for (int j = i; j < this->NumbersOfKeys - 1; j++) {
            this->keys[j] = this->keys[j + 1];
        }
        // 将Key的数量以及最后的一个Key的位置向后
        this->NumbersOfKeys--;
        this->position--;
    }
    else {
        // 如果需要删除中间节点的值为 value 的key. 
        int node_pos = 0;
        // node_pos 对应的节点在对应的Key前面一个位置
        while (node_pos < this->NumbersOfKeys && this->keys[node_pos] <= value) {
            // 如果找到一个节点的值为value, 将该节点与后续节点替换
            if (this->keys[node_pos] == value) {
                this->keys[node_pos] = this->childs[node_pos + 1]->keys[0];
                value = this->childs[node_pos + 1]->keys[0];
                node_pos++;
                break;
            }
            node_pos++;
        }
        int check = this->childs[node_pos]->Remove(value);
        // 如果找不到删除的元素, 啥也不干, 直接返回
        if (check == -1) {
            return -1;
        }
        else if (check == 0) {
            // 成功删除, 普普通通返回一个 0
            return 0;
        }
        else {
            // 如果返回的不是 0 也不是 -1, 那就是 -2, 此时, 需要调整
            // 如果存在兄弟节点的关键字的个数大于 ceil(Order/2)-1, 
            if (node_pos > 0 && this->childs[node_pos - 1]->NumbersOfKeys > ceil(Order / 2.0) - 1) {
                // 向左边兄弟节点借一个key, 父节点的Key下移到当前节点, 左兄弟节点的最后一个元素给父节点
                int temp_pos = this->childs[node_pos]->position;
                this->childs[node_pos]->childs[temp_pos + 1] = this->childs[node_pos]->childs[temp_pos];
                for (int i = temp_pos; i > 0; i--) {
                    this->childs[node_pos]->keys[i] = this->childs[node_pos]->keys[i - 1];
                    this->childs[node_pos]->childs[i] = this->childs[node_pos]->childs[i - 1];
                }
                // 父节点下移动到当前节点的头部
                this->childs[node_pos]->keys[0] = this->keys[node_pos];
                this->childs[node_pos]->position++;
                this->childs[node_pos]->NumbersOfKeys++;
                // 将左兄弟节点的最后一个元素给父节点
                int left_end_pos = this->childs[node_pos - 1]->position;
                this->keys[node_pos] = this->childs[node_pos - 1]->keys[left_end_pos];
                // 将左节点的最后一个子节点移动到当前节点的第一个节点
                this->childs[node_pos]->childs[0] = this->childs[node_pos - 1]->childs[left_end_pos + 1];
                // 左节点的最后一个节点删除
                this->childs[node_pos - 1]->childs[left_end_pos + 1] = nullptr;
                this->childs[node_pos - 1]->position--;
                this->childs[node_pos - 1]->NumbersOfKeys--;
            }
            else if (node_pos < this->NumbersOfKeys && this->childs[node_pos + 1]->NumbersOfKeys > ceil(Order / 2.0) - 1) {
                // 如果向右兄弟节点借一个关键字, 父节点的Key下移动到当前节点最后
                this->childs[node_pos]->NumbersOfKeys++;
                this->childs[node_pos]->position++;
                this->childs[node_pos]->keys[this->childs[node_pos]->position] = this->keys[node_pos];
                // 右兄弟节点的第一个节点向上移动, 移动到父节点
                this->keys[node_pos] = this->childs[node_pos + 1]->keys[0];
                // 将右兄弟节点的第一个孩子节点移动到当前节点的最后一个节点
                this->childs[node_pos]->childs[position + 1] = this->childs[node_pos + 1]->childs[0];
                // 右节点第一个Key与节点被删除, 后面节点向前移动一位
                for (int i = 0; i < this->childs[node_pos + 1]->position; i++) {
                    this->childs[node_pos + 1]->keys[i] = this->childs[node_pos + 1]->keys[i + 1];
                    this->childs[node_pos + 1]->childs[i] = this->childs[node_pos + 1]->childs[i + 1];
                }
                // 最后还要移动最后一位
                int temp_pos = this->childs[node_pos + 1]->position;
                this->childs[node_pos + 1]->childs[temp_pos] = this->childs[node_pos + 1]->childs[temp_pos + 1];
                this->childs[node_pos + 1]->childs[temp_pos + 1] = nullptr;
                this->childs[node_pos + 1]->position--;
                this->childs[node_pos + 1]->NumbersOfKeys--;
            }
            else {
                // 如果两个兄弟节点的关键字的个数也都是 ceil(Order/2)-1. 需要进行合并
                // 如果node_pos的位置在0这一点, 那么只能向右合并节点
                if (node_pos == 0) {
                    this->Merge(node_pos, this->childs[node_pos], this->childs[node_pos + 1]);
                    // 父节点要删除node_pos节点, 后续节点向前移动
                    for (int i = node_pos; i < this->NumbersOfKeys - 1; i++) {
                        this->childs[i + 1] = this->childs[i + 2];
                        this->keys[i] = this->keys[i + 1];
                    }
                }
                // 如果node_pos 在最后一个节点, 那么只能向左合并节点
                // 如果两边都可以, 我们也选择向左合并节点
                else {
                    this->Merge(node_pos - 1, this->childs[node_pos - 1], this->childs[node_pos]);
                    // 父节点要删除node_pos节点, 后续节点向前移动
                    for (int i = node_pos - 1; i < this->NumbersOfKeys - 1; i++) {
                        this->childs[i + 1] = this->childs[i + 2];
                        this->keys[i] = this->keys[i + 1];
                    }

                }
                this->keys[this->position] = 0;
                this->childs[this->position + 1] = nullptr;
                // 删除节点后修改Keys的个数
                this->NumbersOfKeys--;
                this->position--;
            }
        }
    }
    // 如果删除之后的节点的个数大于等于 ceil(Order/2)-1, 直接删除, 不做其余操作. 叶子节点则没有该限制
    if (this->childs[0] == nullptr || this->NumbersOfKeys >= ceil(Order / 2.0) - 1) {
        return 0;
    }
    else {
        // 删除Key之后, 节点的Keys的个数不满足要求, 需要修改
        return -2;
    }
}

template <class T, int Order>
void Node<T, Order>::Merge(int node_pos, Node* left_node, Node* right_node) {
    // 将父节点放入左边节点的末尾
    left_node->keys[++left_node->position] = this->keys[node_pos];
    left_node->NumbersOfKeys++;
    // 将右节点的所有键值对以及节点合并到左节点
    int move_node = 0;
    for (move_node = 0; move_node < right_node->NumbersOfKeys; move_node++) {
        left_node->childs[++left_node->position] = right_node->childs[move_node];
        left_node->keys[left_node->position] = right_node->keys[move_node];
        ++left_node->NumbersOfKeys;
        right_node->keys[move_node] = 0;
        right_node->childs[move_node] = nullptr;
    }
    right_node->NumbersOfKeys = 0;
    // 将右边孩子节点的最后一个节点移动到左孩子节点
    left_node->childs[left_node->position + 1] = right_node->childs[move_node];
    right_node->childs[move_node] = nullptr;
    return;
}


template <class T, int Order>
void Node<T, Order>::Print() {
    int height = this->getHeight(); //number of levels  -> log (n)
    for (int i = 1; i <= height; ++i) //50 levels maximum
    {
        //O(n)
        if (i == 1)PrintUtil(i, true);
        else PrintUtil(i, false);
        cout << endl;
    }
    cout << endl;
}

template <class T, int Order>
void Node<T, Order>::PrintUtil(int height, bool checkRoot)
{
    //to print all values in the level
    if (height == 1 || checkRoot) {
        for (int i = 0; i < this->NumbersOfKeys; i++) {
            if (i == 0) cout << "|";
            cout << this->keys[i];
            if (i != this->NumbersOfKeys - 1) cout << "|";
            if (i == this->NumbersOfKeys - 1) cout << "|" << " ";
        }
    }

    else {
        for (int i = 0; i <= this->NumbersOfKeys; i++) {
            this->childs[i]->PrintUtil(height - 1, false);
            //cout<<endl<<" ";
        }
    }

}

template <class T, int Order>
int Node<T, Order>::getHeight() {
    int COUNT = 1;
    Node<T, Order>* Current = this;//current point to root
    while (true) {
        //is leaf
        if (Current->childs[0] == nullptr) {
            return COUNT;
        }
        Current = Current->childs[0];
        COUNT++;
    }
}

/////////////////////////////////////////////////////////////


//BTree protoType Function
template <class T, int Order>
class BTree
{
private:
    Node<T, Order>* Root;
    int order;
    int count = 0;//to count number of elements

public:
    BTree();
    void Insert(T value);
    void Remove(T value);
    void Print() const;
    ~BTree();
};
/////////////////////////////////////////////////////////////


//BTree implementation
template <class T, int Order>
BTree<T, Order>::BTree() {
    this->Root = nullptr;
}

template <class T, int Order>
void BTree<T, Order>::Insert(T value) {
    count++;
    //if Tree is empty
    if (this->Root == nullptr) {
        this->Root = new Node<T, Order>();
        this->Root->keys[++this->Root->position] = value;
        this->Root->NumbersOfKeys = 1;
    }
    //if tree not empty
    else {
        // 如果根节点插入之后需要分裂, 表示B树的层数需要加一
        int check = Root->Insert(value);
        if (check) {
            T mid;
            // 将Root节点分裂
            Node<T, Order>* splittedNode = this->Root->split(this->Root, &mid);
            Node<T, Order>* newNode = new Node<T, Order>();
            newNode->keys[++newNode->position] = mid;
            newNode->NumbersOfKeys = 1;
            // 将原来的Root与分裂的节点作为新的根节点的左右子节点
            newNode->childs[0] = Root;
            newNode->childs[1] = splittedNode;
            this->Root = newNode;
        }
    }
}

template <class T, int Order>
void BTree<T, Order>::Remove(T value) {
    count--;
    if (this->Root == nullptr) {
        return;
    }
    int check = Root->Remove(value);
    // 如果需要调整, 需要注意, 根节点的子节点的个数限制是至少为两个, 所以只有一个的时候才会报错
    if (check == -2) {
        if (this->Root->NumbersOfKeys == 0) {
            // 只有一个叶子节点, 根节点的唯一叶子节点变成根节点
            this->Root = this->Root->childs[0];
        }
    }
    return;
}


template <class T, int Order>
void BTree<T, Order>::Print() const
{
    if (Root != nullptr)
        Root->Print();
    else cout << "The B-Tree is Empty" << endl;
}


template <class T, int Order>
BTree<T, Order>::~BTree() {
    delete Root;
}

////////////////////////////////////////////////////////////
int main()
{

    // Construct a BTree of order 3, which stores int data
    BTree<int, 3> t1;
    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(0);
    t1.Insert(4);
    t1.Insert(3);
    t1.Insert(2);
    t1.Print(); // Should output the following on the screen:
    /*
    1,4
      0
      2,3
      5
    */
    // Construct a BTree of order 5, which stores char data
    BTree<char, 5> t;
    // Look at the example in our lecture:
    t.Insert('G');
    t.Insert('I');
    t.Insert('B');
    t.Insert('J');
    t.Insert('C');
    t.Insert('A');
    t.Insert('K');
    t.Insert('E');
    t.Insert('D');
    t.Insert('S');
    t.Insert('T');
    t.Insert('R');
    t.Insert('L');
    t.Insert('F');
    t.Insert('H');
    t.Insert('M');
    t.Insert('N');
    t.Insert('P');
    t.Remove('F');
    t.Insert('Q');
    t.Remove('M');
    t.Remove('L');
    t.Remove('G');
    t.Remove('P');
    t.Remove('R');
    // t.Remove('F');
    t.Print(); // Should output the following on the screen:
    //t.traverse();
    /*
    K
      C,G
        A,B
        D,E,F
        H,I,J
      N,R
        L,M
        P,Q
        S,T
    */
    return 0;
}