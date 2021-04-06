#pragma once
#include<QString>
#include<QVector>

class KMP{
private:
    QString searched_Str;
    QString sub_Str;
public:
    KMP(){
        searched_Str = "";
        sub_Str = "";
    }

    bool kmpCompare(QString searchedStr,QString subStr);
    ~KMP(){};
};
