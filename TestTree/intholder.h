#ifndef INTHOLDER_H
#define INTHOLDER_H
#include <baseholder.h>

//класс, описывающий контейнер для хранения данных формата char[10] в дереве.
class IntHolder : public BaseHolder
{
private:
    int data;
public:
    IntHolder(int value=0);
    virtual ~IntHolder() override {qInfo() << "oof";}
    virtual std::string getValue() override;
    virtual std::string getType() override;
};

#endif // INTHOLDER_H
