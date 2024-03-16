#ifndef LAB3_MODULE_H
#define LAB3_MODULE_H

#include <iostream>

class Module {
public:
    virtual void turnOn() = 0;

    virtual void turnOff() = 0;

    [[nodiscard]] virtual std::string getType() const = 0;

};

#endif
