#ifndef LAB3_SENSOR_H
#define LAB3_SENSOR_H

#include "Module/Module.h"
#include "Plan/Plan.h"
#include "Violator/Violator.h"

class Sensor : public Module {
public:

    virtual std::vector<std::pair<Point, std::string>> getInfo(Plan &plan, size_t platformX, size_t platformY) = 0;


};


#endif
