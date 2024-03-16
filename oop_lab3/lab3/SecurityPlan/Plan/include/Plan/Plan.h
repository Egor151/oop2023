#ifndef LAB3_PLAN_H
#define LAB3_PLAN_H

#include "Cell/Cell.h"
#include <vector>

class Plan {
private:
    std::vector<std::vector<Cell>> matrix_;
    Point entrance_;
    Point exit_;
public:
    /**
     * @brief Default constructor for the Plan class.
     */
    Plan();
    /**
     * @brief Parameterized constructor for the Plan class.
     *
     * Initializes the Plan with a matrix of cells with the specified number of rows and columns.
     *
     * @param rows The number of rows in the Plan.
     * @param cols The number of columns in the Plan.
     */
    Plan(size_t rows, size_t cols);

    void deleteObject(Point &point);

    //void set_object(Point  &point, std::string &type);
    /**
     * @brief Add an Object to the Plan at the specified coordinates.
     *
     * If the specified coordinates are out of bounds, an exception is thrown.
     *
     * @param point The Point representing the coordinates where the Object should be added.
     * @param object A pointer to the Object to be added to the Plan.
     * @throw std::invalid_argument If the specified coordinates are out of bounds.
     */

    void add_object(const Point &point, std::shared_ptr<Object> object);

    std::pair<Point, std::string> get_cell_t(size_t x, size_t y) const;
    /**
     * @brief Get the number of rows in the Plan.
     *
     * @return The number of rows in the Plan.
     */
    [[nodiscard]] size_t get_rows() const;
    /**
     * @brief Get the number of columns in the Plan.
     *
     * @return The number of columns in the Plan.
     */
    [[nodiscard]] size_t get_cols() const;
    /**
     * @brief Get a reference to the Cell at the specified coordinates.
     *
     * @param x The x-coordinate of the cell.
     * @param y The y-coordinate of the cell.
     * @return A reference to the Cell at the specified coordinates.
     */
    [[nodiscard]] Cell &get_cell(size_t x, size_t y);
    /**
     * @brief Check if there is an Object at the specified coordinates.
     *
     * @param x The x-coordinate of the cell.
     * @param y The y-coordinate of the cell.
     * @return True if there is an Object at the specified coordinates, false otherwise.
     */
    [[nodiscard]] bool has_object(size_t x, size_t y) const;
    /**
     * @brief Get the type of the cell at the specified coordinates.
     *
     * The type includes the coordinates of the Point and the class name.
     *
     * @param x The x-coordinate of the cell.
     * @param y The y-coordinate of the cell.
     * @return A string representing the type of the cell at the specified coordinates.
     */

    [[nodiscard]] std::string get_cell_type(size_t x, size_t y) const;
    /**
     * @brief Get a pointer to the Object at the specified coordinates.
     *
     * If the specified coordinates are out of bounds, an exception is thrown.
     *
     * @param x The x-coordinate of the cell.
     * @param y The y-coordinate of the cell.
     * @return A pointer to the Object at the specified coordinates.
     * @throw std::out_of_range If the specified coordinates are out of bounds.
     */
    std::shared_ptr<Object>  get_object_at(size_t x, size_t y);

    /**
     * @brief Set the entrance point for the Plan.
     *
     * @param entrance The entrance point to set.
     */
    void set_entrance(const Point &entrance);
    /**
    * @brief Get the entrance point of the Plan.
    *
    * @return The entrance point.
    */
    [[nodiscard]] Point get_entrance() const;
    /**
     * @brief Set the exit point for the Plan.
     *
     * @param exit The exit point to set.
     */
    void set_exit(const Point &exit);

    /**
     * @brief Get the exit point of the Plan.
     *
     * @return The exit point.
     */
    [[nodiscard]] Point get_exit() const;

    void printPlanVisual() const;



};

#endif
