#include <QPointF>
#include <QVector>
#ifndef DATALIST_H
#define DATALIST_H


class DataList
{
public:
    /*standartListMethods*/
    DataList();
    DataList(int size);
    void push_back(int propI, QVector<float> values);
    float at(int propI, int valueI);
    int Size();
    QVector<float>& operator[](const int index);
    int GetVectorSize(int index);
    int ItemsSize();
    void clear();
    /*end*/
    /*calc methods*/
    float MuAt(const int index, int order = 1);
    float SigmaAt(const int index, int order = 2);
    float VariatedMoment(const int index, int order = 3);
    float Median(const int index);
    float MAD(const int index);
    float ExscessCoef(const int index);
    float AssymetryCoef(const int index);
    QVector<float> Kvant(const int index);
    /*end*/
    /*DataVisualizationMethods*/
    QVector<float> GetH();
    QVector<float> GetClassesAt(const int index);
    QVector<int> GetM();
    QVector<float> histoBulding(const int index);
    /*end*/
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
