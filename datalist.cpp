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
    auto Ms = this->GetM();
    for(int i = 0; i < this->_size; i++){
        int m = Ms[i];
        QVector<float> copiedAndSorted = this[0][i];
        std::sort(copiedAndSorted.begin(), copiedAndSorted.end());
        h = (copiedAndSorted.last() - copiedAndSorted.first()) / m;
        classsSizes.push_back(h);
    }
    return classsSizes;
}

QVector<float> DataList::GetClassesAt(const int index)
{
    QVector<float> classes;
    auto temporaryChecker = this[0][index];
    std::sort(temporaryChecker.begin(), temporaryChecker.end());
    float classSizes = this->GetH().at(index);
    int M = this->GetM().at(index);
    for(int i = 0; i < M; i++){
        if(i != 0){
            classes.push_back(classes.at(i - 1) + classSizes);
        }else{
            classes.push_back(temporaryChecker.first()+classSizes);
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

QVector<float> DataList::histoBulding(const int index)
{
    QVector<float> result;
    QVector<float> copiedAndSorted = this[0][index];
    std::sort(copiedAndSorted.begin(), copiedAndSorted.end());
    auto classes = this->GetClassesAt(index);
    for(int i = 0; i < classes.length(); i++){
        float tempProb = 0;
        for(int j = 0; j < this[0][index].length(); j++){
            if(i != 0){
                if(copiedAndSorted.at(j) > classes[i-1] && copiedAndSorted.at(j) <= classes[i]){
                    tempProb++;
                }
            }else{
                if(copiedAndSorted.at(j) <= classes[i]){
                    tempProb++;
                }
            }
        }
        result.push_back(tempProb / this[0][index].length());
    }
    return result;
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
