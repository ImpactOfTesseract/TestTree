#include "chararrayholder.h"
#include "string"
#include <QDebug>

CharArrayHolder::CharArrayHolder(char value[10]){
    for (int i = 0; i < 10; i++){
        this->data[i] = value[i];
    }
}

std::string CharArrayHolder::getValue(){
    char temp[11]; //создаётся временная переменная для добавления нуль-символа в конец массива для корректного конвертирования в std::string
    temp[10] = '\0';
    for(int i = 0; i < 10; i++){
        temp[i] = this->data[i];
    }
    return  std::string(temp);
}

std::string CharArrayHolder::getType(){
    return "Char[10]";
}
