#ifndef FILEREADER_H
#define FILEREADER_H


#include <string>
#include <QVector>
class FileReader
{
public:
    FileReader();
    FileReader(std::string path, QVector<std::string> input);
    FileReader(std::string path, QVector<std::string> &output);
    void SetPath(std::string path);
    std::string GetPath();
    void SetInput(QVector<std::string> input);
    void SetOutput(QVector<std::string> &output);
    void ReadFromFile();
    ~FileReader();
private:
    const std::string defaultErrorPath = "debugInformation.txt";
    std::string _path;
    QVector<std::string> *output;
    QVector<std::string> input;
};

#endif // FILEREADER_H
