#ifndef LAB3_X_RAY_H
#define LAB3_X_RAY_H

#include "Sensor/Sensor.h"
#include "Plan/Plan.h"
#include "Violator/Violator.h"

class Xray : public Sensor {
private:
    std::string name_;
    size_t radius_;
    bool isTurnedOn;
public:
    bool isTurnedOn1() const;

    /**
     * @brief The Xray class represents an X-ray module in a security system.
     *
     * This class provides functionality to gather information about the environment within a specified radius
     * from the platform when the module is turned on.
     */
    Xray(std::string name, size_t radius);
    /**
     * @brief Retrieves the name of the X-ray module.
     * @return A constant reference to a string representing the name of the X-ray module.
     */
    [[nodiscard]] std::string getName() const;
    /**
     * @brief Retrieves the radius of the X-ray module.
     * @return The radius as a size_t value.
     */
    [[nodiscard]] size_t getRadius() const;
    /**
     * @brief Retrieves the type of the module.
     * @return A constant string indicating the type of the module, which is "Xray" in this case.
     */
    [[nodiscard]] std::string getType() const override;
    /**
     * @brief Gathers information about the environment within the specified radius from the platform.
     * @param plan Reference to the Plan object representing the security system layout.
     * @param platformX X-coordinate of the platform's location.
     * @param platformY Y-coordinate of the platform's location.
     * @return A vector of strings containing information about the cells within the radius.
     * @throws std::invalid_argument if the module is not turned on.
     */
    std::vector<std::pair<Point, std::string>> getInfo(Plan &plan, size_t platformX, size_t platformY) override;
    /**
     * @brief Turns on the X-ray module.
     */
    void turnOn() override;
    /**
     * @brief Turns off the X-ray module.
     */
    void turnOff() override;
    /**
     * @brief Default destructor for the Xray class.
     */
    ~Xray();

};

#endif
