#include "KMP.h"


void prefixFunction(const QString &buff_str, QVector<int> &pi){ //алгоритм Кнута-Морриса-Прата
    for (int i = 1; i < buff_str.length(); i++) {
            int j = pi[i - 1];

            while (j > 0 && buff_str[i] != buff_str[j]) {
                j = pi[j - 1];
            }

            if (buff_str[i] == buff_str[j]) {
                pi[i] = j + 1;
            }
            else {
                pi[i] = j;
            }
        }

}

bool KMP::kmpCompare(QString searchedStr, QString subStr){
    searchedStr = searchedStr.toLower(); //для более точного сравнения, чтобы нам не мешали
    subStr = subStr.toLower();

    QString buff_str = subStr+"#"+searchedStr;
    QVector<int> pi(buff_str.length(), 0); //выделение памяти

    prefixFunction(buff_str, pi);

    int t_len = subStr.length();

    for (int i = 0; i < searchedStr.length(); i++) {
        if (pi[t_len + 1 + i] == t_len) {
            return true;
        }

    }
    return false;

}
