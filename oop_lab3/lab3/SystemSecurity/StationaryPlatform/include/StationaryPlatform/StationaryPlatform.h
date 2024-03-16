#ifndef LAB3_STATIONARYPLATFORM_H
#define LAB3_STATIONARYPLATFORM_H

#include <string>
#include <vector>
#include <memory>
#include "Platform/Platform.h"
#include "Module/Module.h"
#include "Point/Point.h"
#include "Object/Object.h"

class StationaryPlatform : public Platform {
protected:
    std::string name_;
    size_t numberOfModules_;
    Point &point_;
    std::vector<std::shared_ptr<Module>> modules_;
public:
    [[nodiscard]] Point getPoint() override;
    /**
     * @brief The StationaryPlatform class represents a stationary platform in a security system.
     *
     * This class provides functionality to manage modules on a stationary platform, including installation and removal.
     */
    StationaryPlatform(std::string name, const Point &point, size_t numberOfModules);
    /**
     * @brief Installs a module at the specified index on the stationary platform.
     * @param module Pointer to the module to be installed.
     * @param index Index where the module should be installed.
     * @throws std::invalid_argument if the index is out of range or the slot is already occupied.
     */
    void installModule(std::shared_ptr<Module> module) override;
    /**
     * @brief Removes the module at the specified index from the stationary platform.
     * @param index Index of the module to be removed.
     * @throws std::invalid_argument if the index is out of range or there is no module at the specified index.
     */
    void removeModule(size_t index) override;
    /**
     * @brief Sets the number of modules on the stationary platform.
     * @param numberOfModules The new number of modules.
     */
    void setNumberOfModules(size_t numberOfModules);
    /**
     * @brief Retrieves the number of modules on the stationary platform.
     * @return The number of modules as a size_t value.
     */
    [[nodiscard]] size_t getNumberOfModules() const;
    /**
     * @brief Retrieves the name of the stationary platform.
     * @return A constant reference to a string representing the name of the stationary platform.
     */
    [[nodiscard]] const std::string &getName() const override;
    /**
     * @brief Default destructor for the StationaryPlatform class.
     */
    ~StationaryPlatform();

    std::string get_cell_type() override;

    virtual const std::vector<std::shared_ptr<Module>> getModules() const override;
};

#endif
