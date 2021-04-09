#pragma once
#include<QString>
#include<QVector>

class KMP{
public:
    bool kmpCompare(QString searchedStr,QString subStr);
    ~KMP(){};
};
