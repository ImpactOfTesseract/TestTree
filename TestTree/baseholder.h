#ifndef BASEHOLDER_H
#define BASEHOLDER_H
#include <vector>
#include <QDebug>

// Абстрактный класс, описывающий контейнер для хранения данных в дереве.
class BaseHolder
{
protected:
    std::vector<BaseHolder*> children;     //коллекция указателей на дочерние узлы для данного узла
public:
    BaseHolder();
    virtual ~BaseHolder() {qInfo() << "oof";}

    void appendChild(BaseHolder* child);   //добавляет в коллекцию дочерних узлов данного узла переданный узел
    void removeChild(BaseHolder* child);   //удаление узла из коллекции дочерних узлов
    BaseHolder* getChild(unsigned long long index); //возвращает указатель на узел с данным индексом из коллекции дочерних узлов
    unsigned long long getChildrenSize();  //возвращает количество дочерних узлов в коллекции
    virtual std::string getValue() = 0;    //pure virtual метод, возвращает значение в виде std::string
    virtual std::string getType() = 0;     //pure virtual метод, возвращает тип контейнера в виде std::string
};

#endif // BASEHOLDER_H
