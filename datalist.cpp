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
    int counter = 0;
    Node *currentNode = this->m_head;
    while(currentNode != nullptr){
        if(counter == index){
            return currentNode->values;
        }
        currentNode = currentNode->next;
        counter++;
    }
    throw QException();
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
