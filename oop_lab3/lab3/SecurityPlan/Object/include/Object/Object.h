#ifndef LAB3_OBJECT_H
#define LAB3_OBJECT_H

#include <memory>

class Object {
public:

    virtual std::string get_cell_type() = 0;

    virtual ~Object() = default;

    [[nodiscard]] virtual const std::string & getName() const = 0;

};

#endif
