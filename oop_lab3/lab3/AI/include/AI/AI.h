#ifndef LAB3_AI_H
#define LAB3_AI_H

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "Platform/Platform.h"
#include "Plan/Plan.h"
#include "Violator/Violator.h"
#include "Module/Module.h"
#include "Sensor/Sensor.h"
#include "Object/Object.h"
#include "Optical/Optical.h"
#include "Xray/Xray.h"
#include "StationaryPlatform/StationaryPlatform.h"
#include "MobilePlatform/MobilePlatform.h"
class AI {
public:
    AI() = default;
    AI( Plan &plan);
    static size_t generateRandomNumber(size_t min, size_t max);
    void createStationaryPlatform(const Point& pointPlace);
    void createMobilePlatform(const Point& pointPlace);
    static void createRandomModule(const std::shared_ptr<Platform>& platform, Point& pointPlace);
    void createPlatform();
    Point findViolator();
    void neutralizeViolator(Point& point, Violator &violator);
    Vector<std::shared_ptr<Platform>> findActivePlatform();
    void movePlatforms();
    Point generateFreePoint();
    AI(const AI& ai) : platforms_(ai.platforms_), plan_(ai.plan_) {}

    std::vector<std::shared_ptr<Platform>> platforms_;
    Plan &plan_;
};

#endif
