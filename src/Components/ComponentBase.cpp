#include "Components/ComponentBase.h"

#include <iostream>

std::string ComponentBase::getMessage() {
    std::string output;

    if(messages.size() > 0) {
        output = messages.front();
        messages.pop_front();
    }
    else
        output = "NOMESSAGE";
    return output;
}
