#include "doubleholder.h"
#include "string"

DoubleHolder::DoubleHolder(double value)
{
    this->data = value;
}

std::string DoubleHolder::getValue(){
    return std::to_string(this->data);
}

std::string DoubleHolder::getType(){
    return "Double";
}
