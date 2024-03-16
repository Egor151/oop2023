#ifndef LAB3_OBSTACLES_H
#define LAB3_OBSTACLES_H

#include <string>
#include "Object/Object.h"

class Obstacles : public Object {
private:

    std::string name_;

public:
    /**
     * @brief The Obstacles class represents a generic obstacle within a security plan.
     *
     * The class provides a basic structure for obstacles with a name and the ability to retrieve
     * the cell type based on the object's runtime type.
     */
    explicit Obstacles(std::string name);
    /**
     * @brief Retrieves the cell type of the obstacle.
     * @return A string representing the cell type based on the object's runtime type.
     */
    std::string get_cell_type() override;
    /**
     * @brief Retrieves the name of the obstacle.
     * @return A constant reference to the name of the obstacle.
     */
    [[nodiscard]] const std::string &getName() const override;
};

#endif
