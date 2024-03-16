#ifndef LAB3_VIOLATOR_H
#define LAB3_VIOLATOR_H

#include <string>
#include "Plan/Plan.h"

class Violator: public Object {
private:
    std::string name_;
    size_t hp_;
    Point point_;
public:
    /**
     * @brief The Violator class represents an intruder or violator in the security system.
     *
     * This class provides functionality to manage and retrieve information about the violator, such as its name,
     * health points (HP), and location on the security system plan.
     */
    Violator(std::string name, size_t hp, const Point point);
    /**
     * @brief Retrieves the name of the violator.
     * @return A constant reference to a string representing the name of the violator.
     */
    [[nodiscard]] const std::string &getName() const override;
    /**
     * @brief Sets the name of the violator.
     * @param name The new name for the violator.
     */
    void setName(const std::string &name);
    /**
     * @brief Retrieves the health points (HP) of the violator.
     * @return The current health points of the violator.
     */
    [[nodiscard]] size_t getHp() const;
    /**
     * @brief Sets the health points (HP) of the violator.
     * @param hp The new health points for the violator.
     */
    void setHp(size_t hp);
    /**
     * @brief Retrieves the location (point) of the violator on the security system plan.
     * @return A pointer to the Point object representing the current location of the violator.
     */
    [[nodiscard]] Point getPoint() const;
    /**
     * @brief Sets the location (point) of the violator on the security system plan.
     * @param point A pointer to the Point object representing the new location for the violator.
     */
    void setPoint(Point point);
    /**
     * @brief Moves the violator to a new location on the security system plan.
     *
     * This function updates the location of the violator, checking for valid coordinates and ensuring
     * the new coordinates are not occupied by other objects.
     *
     * @param plan Reference to the Plan object representing the security system layout.
     * @param newPoint A pointer to the Point object representing the new location for the violator.
     * @throws std::logic_error if the violator has no assigned point.
     * @throws std::out_of_range if the new coordinates are out of bounds.
     * @throws std::invalid_argument if the new coordinates are occupied by other objects.
     */
    void moveViolator(Plan &plan, Point &newPoint);

    virtual std::string get_cell_type() override;
};
#endif
