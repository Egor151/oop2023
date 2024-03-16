#include "AI/AI.h"
#include <memory>

AI::AI(Plan &plan) : plan_(plan) {}

size_t AI::generateRandomNumber(size_t min, size_t max) {
    static std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<size_t> distribution(min, max);
    return distribution(generator);
}

void AI::createPlatform() {
    size_t numberOfPlatforms = generateRandomNumber(5, 15);
    std::cout << "Generated " << numberOfPlatforms << " platforms." << std::endl;

    for (size_t i = 0; i < numberOfPlatforms; ++i) {
        std::string platformType = generateRandomNumber(0, 1) == 0 ? "StationaryPlatform" : "MobilePlatform";
        std::cout << "Platform " << i + 1 << ": " << platformType << std::endl;

        Point pointPlace = generateFreePoint();
        if (platformType == "StationaryPlatform") {
            createStationaryPlatform(pointPlace);
        } else {
            createMobilePlatform(pointPlace);
        }
    }
}
Point AI::generateFreePoint() {
    size_t maxAttempts = 10;  // Максимальное количество попыток генерации свободной точки
    for (size_t attempt = 0; attempt < maxAttempts; ++attempt) {
        Point point(generateRandomNumber(0, plan_.get_cols()-1), generateRandomNumber(0, plan_.get_rows()-1));

        // Проверка, свободна ли клетка с этими координатами
        if (!plan_.has_object(point.x, point.y)) {
            return point;
        }
    }

    // Если не удалось найти свободную точку, выбросить исключение или вернуть дефолтное значение
    throw std::runtime_error("Failed to generate a free point.");
}
void AI::createStationaryPlatform(const Point& pointPlace) {
    size_t numModules = generateRandomNumber(1, 4);
    std::shared_ptr<Platform> stationaryPlatform = std::make_shared<StationaryPlatform>("Stationary", pointPlace, numModules);

    for (size_t j = 0; j < numModules; ++j) {
        createRandomModule(stationaryPlatform, const_cast<Point &>(pointPlace));
    }

    platforms_.push_back(stationaryPlatform);
    auto plat = std::dynamic_pointer_cast<Object>(stationaryPlatform);
    plan_.add_object(pointPlace, stationaryPlatform );
}

void AI::createMobilePlatform(const Point& pointPlace) {
    size_t numModules = generateRandomNumber(1, 4);
    size_t speed = generateRandomNumber(1, 3);
    std::shared_ptr<Platform> mobilePlatform = std::make_shared<MobilePlatform>("Mobile", pointPlace, speed, numModules);

    for (size_t j = 0; j < numModules; ++j) {
        createRandomModule(mobilePlatform, const_cast<Point &>(pointPlace));

    }

    platforms_.push_back(mobilePlatform);
    auto plat = std::dynamic_pointer_cast<Object>(mobilePlatform);
    plan_.add_object(pointPlace,mobilePlatform );
}

void AI::createRandomModule(const std::shared_ptr<Platform>& platform, Point& pointPlace) {
    size_t moduleType = generateRandomNumber(0, 2);
    if (moduleType == 0) {

        auto networkModule = std::make_shared<Network>("Network", pointPlace , generateRandomNumber(4,6), false,
                                                       generateRandomNumber(1,5));
        platform->installModule(std::move(networkModule));
    } else if (moduleType == 1) {
        auto armamentModule = std::make_shared<Armament>("Armament", 2, generateRandomNumber(2,4), generateRandomNumber(100, 200),
                                                         false);
        platform->installModule(std::move(armamentModule));
    } else if(moduleType == 2){
        size_t sensorType = generateRandomNumber(0, 1);
        if (sensorType == 0) {
            auto opticalSensor = std::make_shared<Optical>("Optical", generateRandomNumber(2,5));
            platform->installModule(std::move(opticalSensor));
        } else {
            auto xraySensor = std::make_shared<Xray>("Xray", generateRandomNumber(2,5));
            platform->installModule(std::move(xraySensor));
        }
    }
}

Vector<std::shared_ptr<Platform>> AI::findActivePlatform() {
    Vector<std::shared_ptr<Platform>> connectedPlatforms;
    for (auto &platform : platforms_) {
        const std::vector<std::shared_ptr<Module>> modules = platform->getModules();
        bool isConnected = false;

        for(const auto &module : modules) {
            if (auto network = dynamic_pointer_cast<Network>(module)) {
                network->turnOn();
                Vector<Point> neighbors  = network->getNeighboringPartners(plan_);

                if(!neighbors.IsEmpty()) {
                    Vector<Point> connections = network->getConnectionsToNeighbors(plan_, platform->getPoint());
                    if(!connections.IsEmpty()) {
                        connectedPlatforms.PushBack(std::shared_ptr<Platform>(platform));
                        isConnected = true;
                        break;
                    } else {
                        Vector<Point> directPartners  = network->getDirectPartnersForNode(plan_);
                        for(size_t j = 0; j < directPartners.Size(); ++j) {
                            const auto &directPartner = directPartners[j];
                            Vector<Point> partnerConnections = network->getConnectionsToNeighbors(plan_, directPartner);
                            if(!partnerConnections.IsEmpty()) {
                                connectedPlatforms.PushBack(std::shared_ptr<Platform>(platform));
                                isConnected = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (!isConnected) {
            throw std::runtime_error("Failed to establish connection with platform.");
        }
    }
    return connectedPlatforms;
}

void AI::neutralizeViolator(Point &point, Violator &violator) {
    auto activePlatform = findActivePlatform();
    for( size_t i = 0; i < activePlatform.Size(); ++i) {
        auto & currentPlatform = activePlatform[i];
        const std::vector<std::shared_ptr<Module>> modules = currentPlatform->getModules();

        for(const auto &module : modules) {
            if (auto armamentModule  = dynamic_pointer_cast<Armament>(module)) {
                armamentModule ->turnOn();
                armamentModule->neutralizeTheIntruder(plan_, point.x, point.y,
                                                      const_cast<Violator &>(violator));
                armamentModule->turnOff();
            }
        }
    }
}

Point AI::findViolator() {
    auto activePlatform = findActivePlatform();
    for( size_t i = 0; i < activePlatform.Size(); ++i) {
        auto & platform = activePlatform[i];
        const std::vector<std::shared_ptr<Module>> modules = platform->getModules();
        for(const auto &module : modules) {
            if (auto sensorModule = dynamic_pointer_cast<Sensor>(module)) {
                sensorModule->turnOn();
                std::vector<std::pair<Point, std::string>> detectedObject = sensorModule->getInfo(plan_, platform->getPoint().x, platform->getPoint().y);
                for(auto &j: detectedObject) {
                    if(j.second == "Violator") {
                        neutralizeViolator(j.first, dynamic_cast<Violator&>(*plan_.get_object_at(j.first.x, j.first.y)));
                        return j.first;
                    }
                }

            }
        }
    }
    // Если не найден Violator, возвращаем некоторую дефолтную точку
    return {0, 0};
}

void AI::movePlatforms() {
    for(auto& platform : platforms_) {
        auto mobilePlatform = std::dynamic_pointer_cast<MobilePlatform>(platform);
        if(mobilePlatform) {
            size_t newX = mobilePlatform->getPoint().x;
            size_t newY = mobilePlatform->getPoint().y;
            size_t speed = generateRandomNumber(1, 3);
            size_t direction = generateRandomNumber(0, 3);

            switch (direction) {
                case 0: // Вверх
                    newY = std::min(newY + speed, plan_.get_rows() - 1);
                    break;
                case 1: // Вниз
                    newY = std::max(newY, speed);
                    break;
                case 2: // Влево
                    newX = std::max(newX, speed);
                    break;
                case 3: // Вправо
                    newX = std::min(newX + speed, plan_.get_cols() - 1);
                    break;
            }

            if (!plan_.has_object(newX, newY)) {
                mobilePlatform->moveTo(plan_, newX, newY);
            }
            findActivePlatform();
        }
        findViolator();
    }
}


