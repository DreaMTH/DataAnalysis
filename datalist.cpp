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

float DataList::MuAt(const int index, int order)
{
    float result = 0.0f;
    for(int i = 0; i < (*this)[index].length(); i++){
    result += std::pow((*this)[index].at(i), order);
    }
    return result / (*this)[index].length();

}

float DataList::SigmaAt(const int index, int order)
{
    float mu = this->MuAt(index);
    float result = 0.0f;
    for(int i = 0; i < (*this)[index].length(); i++){
        result += std::pow((*this)[index].at(i) - mu, order);
    }
    return std::sqrt(result/(*this)[index].length());
}

float DataList::VariatedMoment(const int index, int order)
{
    if((*this)[index].size() > 1000){
        return 0.0f;
    }else{
        float result = 0;
        float p = 1.0f / (*this)[index].size();
        for(int i = 0; i < (*this)[index].size(); i++){
        result += std::pow((*this)[index].at(i) - this->MuAt(index), order) * p;
        }
        return result / (*this)[index].size();
    }

}

float DataList::Median(const int index)
{
    QVector<float> temporaryVector((*this)[index].length());
    std::partial_sort_copy(std::begin((*this)[index]), std::end((*this)[index]), std::begin(temporaryVector), std::end(temporaryVector));
    return temporaryVector.at((int)(temporaryVector.length() / 2));
}

float DataList::MAD(const int index)
{
    if((*this)[index].length() <= 1000){
        QVector<float> tempVector;
        for(int i = 0; i < (*this)[index].size(); i++){
            for(int j = i; j < (*this)[index].size() - 1; j++){
                tempVector.push_back(0.5 * ((*this)[index].at(i) + (*this)[index].at(j)));
            }
        }
        std::sort(tempVector.begin(), tempVector.end());
        return tempVector[(int)(tempVector.length() / 2)];
    }else{
        return 0.0f;
    }

}

float DataList::ExscessCoef(const int index)
{
    float result;
    float fMoment = this->SigmaAt(index, 4);
    float sigma = this->SigmaAt(index);
    result = fMoment / std::pow(sigma, 4);
    return result;
}

float DataList::AssymetryCoef(const int index)
{
    float thrMoment = this->VariatedMoment(index);
    float sigma = this->SigmaAt(index);
    return thrMoment / std::pow(sigma, 3);
}

QVector<float> DataList::Kvant(const int index)
{
    QVector<float> result;
    float TstKv = 1.64;
    float Mu = this->MuAt(index);
    float sigma = this->SigmaAt(index);
    float ask = this->AssymetryCoef(index);
    float sqtL = sigma / (*this)[index].size();
    float qs = sigma / std::sqrt(2 * (*this)[index].size());
    result.append(Mu - TstKv * sqtL); //results
    result.append(Mu + TstKv * sqtL);
    result.append(sigma - TstKv * qs);
    result.append(sigma + TstKv * qs);
    //result.append(ask - TestKv  )

    return result;
}

QVector<float> DataList::GetH()
{
    QVector<float> classsSizes;

    float h;
    auto Ms = this->GetM();
    for(int i = 0; i < this->_size; i++){
        int m = Ms[i];
        QVector<float> copiedAndSorted = (*this)[i];
        std::sort(copiedAndSorted.begin(), copiedAndSorted.end());
        h = (copiedAndSorted.last() - copiedAndSorted.first()) / m;
        classsSizes.push_back(h);
    }
    return classsSizes;
}

QVector<float> DataList::GetClassesAt(const int index)
{
    QVector<float> classes;
    auto temporaryChecker = (*this)[index];
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
        int currentSize = (*this)[i].size();
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
    QVector<float> copiedAndSorted = (*this)[index];
    std::sort(copiedAndSorted.begin(), copiedAndSorted.end());
    auto classes = this->GetClassesAt(index);
    for(int i = 0; i < classes.length(); i++){
        float tempProb = 0;
        for(int j = 0; j < (*this)[index].length(); j++){
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
        result.push_back(tempProb / (*this)[index].length());
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
