#ifndef LAB3_CELL_H
#define LAB3_CELL_H

#include "Point/Point.h"
#include "Object/Object.h"

#include <vector>
#include <memory>



class Cell {
private:
    std::shared_ptr<Object> object_;
    Point point_;
public:
    [[nodiscard]] std::pair<Point, std::string> get_info() const;
    /**
    * @brief Default constructor for the Cell class.
    *
    * Initializes the Cell object with nullptr for both object_ and point_.
    */
    Cell();
    /**
    * @brief Parameterized constructor for the Cell class.
    *
    * Initializes the Cell object with the given object and point.
    *
    * @param object A pointer to the Object associated with the Cell.
    * @param point A pointer to the Point representing the coordinates of the Cell.
    */
    explicit Cell(std::shared_ptr<Object> object, const Point &point);
    /**
     * @brief Set the Object associated with the Cell.
     *
     * @param object A pointer to the Object to be associated with the Cell.
     */
    void set_object(std::shared_ptr<Object> object);

    void set_point(Point point);
    /**
     * @brief Add an Object to the Cell if it is currently empty.
     *
     * If the Cell already has an associated Object, an exception is thrown.
     *
     * @param object A pointer to the Object to be added to the Cell.
     * @throw std::invalid_argument If the Cell already has an associated Object.
     */

    void add_object_if_absent(std::shared_ptr<Object> object);
    /**
     * @brief Check if the Cell has an associated Object.
     *
     * @return True if the Cell has an associated Object, false otherwise.
     */

    [[nodiscard]] bool has_object() const;
    /**
    * @brief Get the Object associated with the Cell.
    *
    * @return A pointer to the Object associated with the Cell.
    */

    [[nodiscard]] std::shared_ptr<Object> get_object();
    /**
     * @brief Get the type of the Cell as a string.
     *
     * The type includes the coordinates of the Point and the class name.
     *
     * @return A string representing the type of the Cell.
     */

    [[nodiscard]] std::string get_cell_type() const;
};

#endif
