#ifndef LAB3_ARMAMENT_H
#define LAB3_ARMAMENT_H

#include <iostream>
#include <random>
#include "Module/Module.h"
#include "Violator/Violator.h"
#include "Plan/Plan.h"

class Armament : public Module {
private:
    std::default_random_engine randomEngine;
    std::string name_;
    size_t time_;
    size_t radius_;
    size_t energy_;
    bool energySupply_;
public:
    /**
     * @brief Constructor for the Armament class.
     * @param name The name of the armament.
     * @param time Time required for the armament module to be operational.
     * @param radius The radius within which the armament can detect and neutralize intruders.
     * @param energy The initial energy level of the armament.
     * @param energySupply A boolean indicating whether the armament module is currently supplied with energy.
     */
    explicit Armament(std::string name, size_t time, size_t radius, size_t energy, bool energySupply);
    /**
     * @brief Retrieves the time required for the armament module to be operational.
     * @return The time required for the armament module to be operational.
     */
    [[nodiscard]] size_t getTime() const;
    /**
     * @brief Retrieves the detection radius of the armament.
     * @return The radius within which the armament can detect and neutralize intruders.
     */
    [[nodiscard]] size_t getRadius() const;
    /**
     * @brief Retrieves the current energy level of the armament.
     * @return The current energy level of the armament.
     */
    [[nodiscard]] size_t getEnergy() const;
    /**
     * @brief Checks if the armament has an energy supply.
     * @return A boolean indicating whether the armament module is currently supplied with energy.
     */
    [[nodiscard]] bool isEnergySupply() const;
    /**
    * @brief Retrieves the name of the armament.
    * @return A constant reference to the name of the armament.
    */
    [[nodiscard]] const std::string &getName() const;
    /**
     * @brief Retrieves the type of the armament.
     * @return A constant string representing the type of the armament.
     */
    [[nodiscard]] std::string getType() const override;
    /**
     * @brief Sets a new operational time for the armament.
     * @param time The new time required for the armament module to be operational.
     */
    void setTime(size_t time);
    /**
     * @brief Sets a new detection radius for the armament.
     * @param radius The new radius within which the armament can detect and neutralize intruders.
     */
    void setRadius(size_t radius);
    /**
     * @brief Sets a new energy level for the armament.
     * @param energy The new energy level for the armament.
     */
    void setEnergy(size_t energy);
    /**
     * @brief Sets a new name for the armament.
     * @param name A string representing the new name for the armament.
     */
    void setName(const std::string &name);
    /**
    * @brief Charges the armament for a specified duration.
    * @param charging A boolean indicating whether the armament is being charged.
    * @throws std::runtime_error if there is not enough energy to turn on the weapons during charging.
    */
    void chargeArmament(bool charging) const;
//    /**
//     * @brief Checks if a violator is detected within the specified radius.
//     * @param plan A reference to the security plan in which the armament operates.
//     * @param platformX, platformY Coordinates of the platform where the armament is located.
//     * @return A boolean indicating whether a violator is detected within the armament's detection radius.
//     */
//    bool isViolatorDetected(Plan &plan, size_t platformX, size_t platformY) const;
    /**
     * @brief Attempts to neutralize an intruder within the specified radius.
     * @param plan A reference to the security plan in which the armament operates.
     * @param platformX, platformY Coordinates of the platform where the armament is located.
     * @param violator A reference to the violator to be neutralized.
     * @return A pair containing the remaining HP of the intruder and the remaining energy of the armament.
     * @throws std::invalid_argument if the module isn't included.
     */
    auto neutralizeTheIntruder(Plan &plan, size_t platformX, size_t platformY, Violator &violator) -> std::pair<size_t, size_t>;
    /**
     * @brief Turns on the armament module.
     */
    void turnOn() override;
    /**
     * @brief Turns off the armament module.
     */
    void turnOff() override;
    /**
     * @brief Destructor for the Armament class.
     */
    ~Armament();

};

#endif
