#include "filereader.h"
#include <QVector>
#include <fstream>
FileReader::FileReader()
{
    this->_path = "defaultOutput.txt";
    this->output = nullptr;
    this->input = *new QVector<std::string>;
}

FileReader::FileReader(std::string path, QVector<std::string> input)
{
    this->_path = path;
    this->input = input;
}

FileReader::FileReader(std::string path, QVector<std::string> &output)
{
    this->_path = path;
    this->output = &output;
}

void FileReader::SetPath(std::string path)
{
    this->_path = path;
}

std::string FileReader::GetPath()
{
    return this->_path;
}

void FileReader::SetInput(QVector<std::string> input)
{
    this->input = input;
}

void FileReader::SetOutput(QVector<std::string> &output)
{
    this->output = &output;
}

void FileReader::ReadFromFile()
{
    std::fstream fileReader;
    fileReader.open(this->_path, std::ios_base::in);
    if(fileReader.is_open()){
        while(!fileReader.eof()){
            std::string tempString = "";
            fileReader >> tempString;
            this->output->append(tempString);
        }
        //this->output->removeLast();
    }else{
        fileReader.open(this->defaultErrorPath, std::ios_base::app | std::ios_base::out);
        fileReader << "Error with reading file";
    }
}

FileReader::~FileReader()
{

}
