#ifndef CHARARRAYHOLDER_H
#define CHARARRAYHOLDER_H
#include <baseholder.h>


//класс, описывающий контейнер для хранения данных формата char[10] в дереве.
class CharArrayHolder : public BaseHolder
{
private:
    char data[10];
public:
    CharArrayHolder(char value[10]);
    virtual ~CharArrayHolder() override {qInfo() << "oof";}
    virtual std::string getValue() override;
    virtual std::string getType() override;
};

#endif // CHARARRAYHOLDER_H
