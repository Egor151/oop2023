#ifndef LAB3_OPTICAL_H
#define LAB3_OPTICAL_H

#include "Sensor/Sensor.h"
#include "Plan/Plan.h"
#include "Violator/Violator.h"
#include "Obstacles/Obstacles.h"
#include "Module/Module.h"

class Optical : public Sensor {
private:
    std::string name_;
    size_t radius_;
    bool isTurnedOn;

public:
    bool isTurnedOn1() const;
    /**
     * @brief The Optical class represents an optical module in a security system.
     *
     * This class provides functionality to detect objects within a specified radius when the module is turned on.
     * It restricts visibility in cells containing objects, allowing for a more realistic optical detection scenario.
     */
    Optical(std::string name, size_t radius);
    /**
     * @brief Retrieves the type of the optical module.
     * @return A constant string representing the type of the optical module.
     */
    [[nodiscard]]  std::string getType() const override;
    /**
     * @brief Retrieves the name of the optical module.
     * @return A string representing the name of the optical module.
     */
    [[nodiscard]] std::string getName() const;
    /**
     * @brief Retrieves the detection radius of the optical module.
     * @return The detection radius as a size_t value.
     */
    [[nodiscard]] size_t getRadius() const;
    /**
     * @brief Retrieves information about detected objects within the module's detection radius.
     * @param plan Reference to the security plan containing information about the environment.
     * @param platformX X-coordinate of the platform hosting the optical module.
     * @param platformY Y-coordinate of the platform hosting the optical module.
     * @return A vector of strings containing the types of objects detected within the module's radius.
     * @throws std::invalid_argument if the optical module is not turned on.
     */
    std::vector<std::pair<Point, std::string>> getInfo(Plan &plan, size_t platformX, size_t platformY) override;
    /**
     * @brief Turns on the optical module, enabling object detection.
     */
    void turnOn() override;
    /**
     * @brief Turns off the optical module, disabling object detection.
     */
    void turnOff() override;
    /**
     * @brief Default destructor for the Optical class.
     */
    ~Optical();

/**
 * @brief Bans cells within the visibility range of an object, restricting further detection in those cells.
 * @param x X-coordinate of the object in the security plan.
 * @param y Y-coordinate of the object in the security plan.
 * @param cells 2D vector representing the visibility status of cells in the module's range.
 */
static void ban_cells(size_t x, size_t y, std::vector<std::vector<size_t>> &cells);
};

#endif