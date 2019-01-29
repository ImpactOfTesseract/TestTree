#include "baseholder.h"


BaseHolder::BaseHolder()
{
}


void BaseHolder::appendChild(BaseHolder* child){
    this->children.push_back(child);
}

void BaseHolder::removeChild(BaseHolder* child){
    for(std::vector<BaseHolder*>::iterator it = this->children.begin(); it != this->children.end();){
        if (*it == child){
            it = this->children.erase(it);
        } else {
            ++it;
        }
    }
}

BaseHolder* BaseHolder::getChild(unsigned long long index){
    if(index<=this->children.size() - 1){
        return this->children[index];
    }
    else return this->children[this->children.size() - 1];
}

unsigned long long BaseHolder::getChildrenSize(){
    return this->children.size();
}
