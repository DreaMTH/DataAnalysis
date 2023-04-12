#include "datalist.h"
#include <stdexcept>
#include <QException>
DataList::DataList()
{
    this->_size = 0;
    this->m_head = nullptr;
}
DataList::DataList(int size){
    this->_size = size;
    this->m_head = nullptr;
}

void DataList::push_back(int propI, QVector<float> values)
{
    if(this->m_head != nullptr){
        DataList::Node *currentNode = this->m_head;
        while (currentNode->next != nullptr) {
            currentNode = currentNode->next;
        }
        currentNode->next = new DataList::Node(propI, values);

    }else{
        this->m_head = new DataList::Node(propI, values);
    }
    this->_size++;
}

float DataList::at(int propI, int valueI)
{
    if(propI > this->_size){
        throw std::out_of_range("DataList: index is out of range");
    }
    if(propI != 0){
        Node *currentNode = this->m_head;
        for(size_t i = 0; i < (size_t)propI; i++){
            currentNode = currentNode->next;
        }
        return currentNode->values.at(valueI);
    }else{
        return this->m_head->values.at(valueI);
    }
}

int DataList::Size()
{
    return this->_size;
}

QVector<float> &DataList::operator [](const int index)
{
    if(index > this->_size){
        throw("invalid operation. bounds array");
    }else{
        Node *currentNode = this->m_head;
        for(int i = 0; i < index; i++){
            currentNode = currentNode->next;
        }
        return currentNode->values;
    }
}

int DataList::GetVectorSize(int index)
{
    if(index == 0){
        return this->m_head->values.size();
    }else if(index > this->_size){
        throw std::out_of_range("DataList: index is out of range");
    }else if(index < 0){
        throw std::invalid_argument("DataList: index is sub zero");
    }else{
    Node *currentNode = this->m_head;
    for(int i = 0; i <= index; i++){
        currentNode = currentNode->next;
    }
    return currentNode->values.size();
    }
}

int DataList::ItemsSize()
{
    return this->LessSize();
}

void DataList::clear()
{

}

QVector<float> DataList::GetH()
{
    QVector<float> classsSizes;
    float h;
    int currentSize;
    for(int i = 0; i < this->_size; i++){
        int m;
        currentSize = this[0][i].size();
        if(currentSize <= 100){
            m = (int)std::sqrt(currentSize);
        }else{
            m = (int)std::cbrt(currentSize);
        }
        h = (this[0][i].last() - this[0][i].first()) / m;
        classsSizes.push_back(h);
    }
    return classsSizes;
}

QVector<QVector<float> > DataList::GetClasses()
{
    QVector<QVector<float> > classes;
    QVector<float> classSizes = this->GetH();
    QVector<int> M = this->GetM();
    for(int i = 0; i < M.size(); i++){
        for(int j = 0; j < M[i]; j++){
            if(j != 0){
                classes[i].push_back(classes[i][j-1] + classSizes[i]);
            }else{
                classes[i].push_back(this[0][i].first());
            }
        }

    }
    return classes;
}

QVector<int> DataList::GetM()
{
    QVector<int> m;
    for(int i = 0; i < this->_size; i++){
        int currentSize = this[0][i].size();
        if(currentSize <= 100){
            m.push_back((int)std::sqrt(currentSize));
        }else{
            m.push_back((int)std::cbrt(currentSize));
        }
    }
    return m;
}

int DataList::LessSize()
{
    QVector<int> *items = new QVector<int>;
    Node *currentNode = this->m_head;
    for(int i = 0; i < this->_size; i++){
        items->push_back(currentNode->values.size());
    }
    int result = *std::min_element(items->begin(), items->end());
    //delete items;
    //delete currentNode;
    return result;
}
