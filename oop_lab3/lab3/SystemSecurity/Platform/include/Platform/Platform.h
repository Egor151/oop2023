#ifndef LAB3_PLATFORM_H
#define LAB3_PLATFORM_H

#include <string>
#include <vector>
#include <memory>
#include "Object/Object.h"
#include "Module/Module.h"
#include "Armament/Armament.h"
#include "Sensor/Sensor.h"
#include "Network/Network.h"

class Platform: public Object {
public:
    [[nodiscard]] virtual Point getPoint() = 0;

    virtual void installModule(std::shared_ptr<Module> module) = 0;

    virtual void removeModule(size_t index) = 0;

    virtual ~Platform() = default;

    [[nodiscard]] virtual const std::vector<std::shared_ptr<Module>> getModules() const = 0;
};

#endif
