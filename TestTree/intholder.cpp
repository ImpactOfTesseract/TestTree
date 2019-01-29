#include "intholder.h"
#include "string"

IntHolder::IntHolder(int value)
{
    this->data = value;
}

std::string IntHolder::getValue(){
    return std::to_string(this->data);
}

std::string IntHolder::getType(){
    return "Integer";
}
