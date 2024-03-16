#ifndef LAB3_MOBILEPLATFORM_H
#define LAB3_MOBILEPLATFORM_H

#include "StationaryPlatform/StationaryPlatform.h"
#include <iostream>

class MobilePlatform : public StationaryPlatform {
private:
    size_t speed_;
public:
    /**
     * @brief The MobilePlatform class represents a mobile security platform that can move within a security plan.
     *
     * This class is derived from the StationaryPlatform class, inheriting its properties and adding mobility features.
     */
    MobilePlatform(std::string name, Point point, size_t speed, size_t numberOfModules);

    /**
     * @brief Retrieves the speed of the mobile platform.
     * @return The speed of the mobile platform.
     */
    [[nodiscard]] size_t getSpeed() const;

    [[nodiscard]] const std::string &getName() const override;

    std::string get_cell_type() override;

    [[nodiscard]] Point getPoint() const;

    //void setPoint(Point *point);

    void moveTo(Plan &plan, size_t newX, size_t newY);
};

#endif
