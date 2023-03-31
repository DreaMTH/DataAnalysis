#include "datalist.h"

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
        Node *currentNode = this->m_head;
        while (currentNode != nullptr) {
            currentNode = currentNode->next;
        }
        currentNode->next = new DataList::Node(propI, values);
        this->_size++;
    }else{
        this->m_head = new DataList::Node(propI, values);
    }
}

float DataList::at(int propI, int valueI)
{
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
