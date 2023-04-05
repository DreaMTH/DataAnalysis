#include <QVector>
#ifndef DATALIST_H
#define DATALIST_H


class DataList
{
public:
    DataList();
    DataList(int size);
    void push_back(int propI, QVector<float> values);
    float at(int propI, int valueI);
    int Size();
    QVector<float> operator[](const int index);
    int GetVectorSize(int index);
    int ItemsSize();
private:
    class Node{
    public:
        int propIndex;
        QVector<float> values;
        Node* next;
        Node(int pIndex, QVector<float> &val, Node *nxt = nullptr){
            this->propIndex = pIndex;
            this->values = val;
            this->next = nxt;
        }
    };
    int LessSize();
    Node* m_head;
    int _size;
};

#endif // DATALIST_H
