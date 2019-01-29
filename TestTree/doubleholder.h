#ifndef DOUBLEHOLDER_H
#define DOUBLEHOLDER_H
#include <baseholder.h>

//класс, описывающий контейнер для хранения данных формата double в дереве.
class DoubleHolder : public BaseHolder
{
private:
    double data;
public:
    DoubleHolder(double value=0);
    virtual ~DoubleHolder() override {qInfo() << "oof";}
    virtual std::string getValue() override;
    virtual std::string getType() override;
};

#endif // DOUBLEHOLDER_H
