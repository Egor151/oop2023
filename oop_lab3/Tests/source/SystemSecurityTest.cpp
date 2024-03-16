#include "catch2/catch_all.hpp"
#include "../../lab3/SecurityPlan/Point/include/Point/Point.h"
#include "../../lab3/Violator/include/Violator/Violator.h"
#include "../../lab3/SecurityPlan/Plan/include/Plan/Plan.h"
#include "../../lab3/AI/include/AI/AI.h"
#include "../../lab3/SystemSecurity/Platform/include/Platform/Platform.h"
#include "../../lab3/SystemSecurity/StationaryPlatform/include/StationaryPlatform/StationaryPlatform.h"
#include "../../lab3/SystemSecurity/Xray/include/Xray/Xray.h"
#include <sstream>
class MockModule : public Module {
public:
    void turnOn() override {}
    void turnOff() override {}
    [[nodiscard]] std::string getType() const override {
        return "MockModule";
    }
};
TEST_CASE("Xray class tests", "[Xray]") {
    SECTION("Initialization") {
        Xray xray("TestXray", 3);

        REQUIRE(xray.getName() == "TestXray");
        REQUIRE(xray.getRadius() == 3);
        REQUIRE(xray.getType() == "Xray");
        REQUIRE_FALSE(xray.isTurnedOn1());
    }

    SECTION("Turn On/Off") {
        Xray xray("TestXray", 3);

        xray.turnOn();
        REQUIRE(xray.isTurnedOn1());

        xray.turnOff();
        REQUIRE_FALSE(xray.isTurnedOn1());
    }

    SECTION("Initialization") {
        Optical optical("TestOptical", 3);

        REQUIRE(optical.getName() == "TestOptical");
        REQUIRE(optical.getRadius() == 3);
        REQUIRE(optical.getType() == "Optical");
        REQUIRE_FALSE(optical.isTurnedOn1());
    }

    SECTION("Turn On/Off") {
        Optical optical("TestOptical", 3);

        optical.turnOn();
        REQUIRE(optical.isTurnedOn1());

        optical.turnOff();
        REQUIRE_FALSE(optical.isTurnedOn1());
    }

    SECTION("Initialization and Turn On/Off") {
        Xray xray("TestXray", 3);

        REQUIRE(xray.getName() == "TestXray");
        REQUIRE(xray.getRadius() == 3);
        REQUIRE(xray.getType() == "Xray");
        REQUIRE_FALSE(xray.isTurnedOn1());

        xray.turnOn();
        REQUIRE(xray.isTurnedOn1());

        xray.turnOff();
        REQUIRE_FALSE(xray.isTurnedOn1());

        Optical optical("TestOptical", 3);

        REQUIRE(optical.getName() == "TestOptical");
        REQUIRE(optical.getRadius() == 3);
        REQUIRE(optical.getType() == "Optical");
        REQUIRE_FALSE(optical.isTurnedOn1());

        optical.turnOn();
        REQUIRE(optical.isTurnedOn1());

        optical.turnOff();
        REQUIRE_FALSE(optical.isTurnedOn1());
    }


    SECTION("getInfo when Turned Off") {
        Plan plan(5, 5);
        Optical optical("TestOptical", 1);

        // optical is turned off by default

        // Assuming you have a method to set objects in the plan
        plan.add_object(Point(1, 1), std::make_shared<StationaryPlatform>("Stationary", Point(1, 1), 4));

        REQUIRE_THROWS_AS(optical.getInfo(plan, 1, 1), std::invalid_argument);
    }

    SECTION("getInfo when Turned Off") {
        Plan plan(5, 5);
        Xray xray("TestXray", 1);

        // xray is turned off by default

        // Assuming you have a method to set objects in the plan
        plan.add_object(Point(1, 1), std::make_shared<MobilePlatform>("Mobile", Point(1, 1), 3, 7));

        REQUIRE_THROWS_AS(xray.getInfo(plan, 1, 1), std::invalid_argument);
    }SECTION("Initialization") {
        Point point(1, 2);
        StationaryPlatform platform("TestPlatform", point, 3);

        REQUIRE(platform.getName() == "TestPlatform");
        REQUIRE(platform.getPoint() == point);
        REQUIRE(platform.getNumberOfModules() == 3);
    }

    SECTION("get_cell_type") {
        StationaryPlatform platform("TestPlatform", Point(1, 2), 3);

        REQUIRE(platform.get_cell_type() == "StationaryPlatform");
    }

    SECTION("setNumberOfModules") {
        StationaryPlatform platform("TestPlatform", Point(1, 2), 3);
        platform.setNumberOfModules(5);

        REQUIRE(platform.getNumberOfModules() == 5);
    }

    SECTION("installModule") {
        StationaryPlatform platform("TestPlatform", Point(1, 2), 3);
        auto module = std::make_shared<Optical>("Optical", 5);

        platform.installModule(module);

        REQUIRE(platform.getNumberOfModules() == 3);  // Assuming 1 module is already installed
    }

    SECTION("installModule - out of range") {
        StationaryPlatform platform("TestPlatform", Point(1, 2), 1);
        Point point(2, 4);
        auto module1 = std::make_shared<Network>("Network", point, 6, false, 5);

        auto module2 = std::make_shared<Armament>("Armament", 2, 3, 150, false);

        platform.installModule(module1);

        REQUIRE_THROWS_AS(platform.installModule(module2), std::invalid_argument);
    }

    SECTION("removeModule") {
        StationaryPlatform platform("TestPlatform", Point(1, 2), 3);
        auto module1 = std::make_shared<Armament>("Armament", 2, 4, 100,
                                                  false);
        auto module2 = std::make_shared<Optical>("Optical", 5);
        platform.installModule(std::move(module2));

        platform.installModule(module1);
        platform.installModule(module2);

        platform.removeModule(1);

        REQUIRE(platform.getNumberOfModules() == 3);
    }

    SECTION("removeModule - out of range") {
        StationaryPlatform platform("TestPlatform", Point(1, 2), 1);
        Point point(1,1);
        auto module =std::make_shared<Network>("Network", point , (6), false,
                                               3);

        platform.installModule(module);

        REQUIRE_THROWS_AS(platform.removeModule(1), std::out_of_range);
    }SECTION("Xray Initialization and Turn On/Off") {
        Xray xray("TestXray", 3);

        REQUIRE(xray.getName() == "TestXray");
        REQUIRE(xray.getRadius() == 3);
        REQUIRE(xray.getType() == "Xray");
        REQUIRE_FALSE(xray.isTurnedOn1());

        xray.turnOn();
        REQUIRE(xray.isTurnedOn1());

        xray.turnOff();
        REQUIRE_FALSE(xray.isTurnedOn1());
    }

    SECTION("Optical Initialization and Turn On/Off") {
        Optical optical("TestOptical", 3);

        REQUIRE(optical.getName() == "TestOptical");
        REQUIRE(optical.getRadius() == 3);
        REQUIRE(optical.getType() == "Optical");
        REQUIRE_FALSE(optical.isTurnedOn1());

        optical.turnOn();
        REQUIRE(optical.isTurnedOn1());

        optical.turnOff();
        REQUIRE_FALSE(optical.isTurnedOn1());
    }

    SECTION("getInfo when Xray Turned Off") {
        Plan plan(5, 5);
        Xray xray("TestXray", 1);

        // xray is turned off by default

        // Assuming you have a method to set objects in the plan
        plan.add_object(Point(1, 1), std::make_shared<MobilePlatform>("Mobile", Point(1, 1), 4, 3));

        REQUIRE_THROWS_AS(xray.getInfo(plan, 1, 1), std::invalid_argument);
    }



    SECTION("getInfo when Optical Turned Off") {
        Plan plan(5, 5);
        Optical optical("TestOptical", 1);

        // optical is turned off by default

        // Assuming you have a method to set objects in the plan
        plan.add_object(Point(1, 1), std::make_shared<StationaryPlatform>("Stationary", Point(1, 1), 4));

        REQUIRE_THROWS_AS(optical.getInfo(plan, 1, 1), std::invalid_argument);
    }



    SECTION("StationaryPlatform Initialization and Module Management") {
        Point point(1, 2);
        StationaryPlatform platform("TestPlatform", point, 3);

        REQUIRE(platform.getName() == "TestPlatform");
        REQUIRE(platform.getPoint() == point);
        REQUIRE(platform.getNumberOfModules() == 3);

        SECTION("get_cell_type") {
            REQUIRE(platform.get_cell_type() == "StationaryPlatform");
        }

        SECTION("setNumberOfModules") {
            platform.setNumberOfModules(5);
            REQUIRE(platform.getNumberOfModules() == 5);
        }

        SECTION("installModule") {
            auto module = std::make_shared<Armament>("Armament", 3, 5, 190,
                                                     false);
            platform.installModule(module);
            REQUIRE(platform.getNumberOfModules() == 3);  // Assuming 1 module is already installed
        }

        SECTION("Initialization") {
            Point point(1, 2);
            MobilePlatform mobilePlatform("TestMobilePlatform", point, 5, 3);

            REQUIRE(mobilePlatform.getName() == "TestMobilePlatform");
            REQUIRE(mobilePlatform.getSpeed() == 5);
            REQUIRE(mobilePlatform.getNumberOfModules() == 3);
            REQUIRE(mobilePlatform.get_cell_type() == "MobilePlatform");
        }


        SECTION("MoveTo out of bounds") {
            Plan plan(5, 5);
            MobilePlatform mobilePlatform("TestMobilePlatform", Point(1, 1), 3, 2);

            // Attempt to move the platform to an out-of-bounds position
            REQUIRE_THROWS_AS(mobilePlatform.moveTo(plan, 5, 5), std::out_of_range);
        }
        SECTION("MockModule Initialization") {
            MockModule mockModule;

            REQUIRE(mockModule.getType() == "MockModule");
        }

        SECTION("Turn On/Off") {
            MockModule mockModule;

            mockModule.turnOn();
            // Add appropriate checks based on your implementation details

            mockModule.turnOff();
            // Add appropriate checks based on your implementation details
        }
        SECTION("Initialization") {
            Obstacles obstacles("TestObstacles");

            REQUIRE(obstacles.getName() == "TestObstacles");
            REQUIRE(obstacles.get_cell_type() == "Obstacles");
        }

    }
    SECTION("Initialization") {
        Armament armament("TestArmament", 10, 5, 100, true);

        REQUIRE(armament.getName() == "TestArmament");
        REQUIRE(armament.getTime() == 10);
        REQUIRE(armament.getRadius() == 5);
        REQUIRE(armament.getEnergy() == 100);
        REQUIRE(armament.isEnergySupply());
    }

    SECTION("Getter and Setter Methods") {
        Armament armament("TestArmament", 10, 5, 100, true);

        armament.setName("UpdatedName");
        armament.setTime(20);
        armament.setRadius(8);
        armament.setEnergy(150);

        REQUIRE(armament.getName() == "UpdatedName");
        REQUIRE(armament.getTime() == 20);
        REQUIRE(armament.getRadius() == 8);
        REQUIRE(armament.getEnergy() == 150);
    }

    SECTION("getType Method") {
        Armament armament("TestArmament", 10, 5, 100, true);

        REQUIRE(armament.getType() == "Armament");
    }

    SECTION("Turn On/Off") {
        Armament armament("TestArmament", 10, 5, 100, true);

        armament.turnOff();
        REQUIRE_FALSE(armament.isEnergySupply());

        armament.turnOn();
        REQUIRE(armament.isEnergySupply());
    }

    SECTION("Neutralize The Intruder") {
        Plan plan(10, 10);
        Violator violator("TestViolator", 100, Point(5, 5));

        Armament armament("TestArmament", 10, 3, 50, true);

        // Assuming you have a method to set objects in the plan
        plan.add_object(Point(5, 5), std::make_shared<Violator>("TestViolator", 100, Point(5, 5)));

        // Turn on armament
        armament.turnOn();

        auto result = armament.neutralizeTheIntruder(plan, 5, 5, violator);

        // Check the result based on your expected behavior
        REQUIRE(result.first <= 100);  // Adjust based on your expected result for Violator HP
        REQUIRE(result.second <= 50);  // Adjust based on your expected result for remaining energy
    }

    SECTION("Neutralize The Intruder - Module Not Included") {
        Plan plan(10, 10);
        Violator violator("TestViolator", 100, Point(5, 5));

        Armament armament("TestArmament", 10, 3, 50, false);

        // Assuming you have a method to set objects in the plan
        plan.add_object(Point(5, 5), std::make_shared<Violator>("TestViolator", 100, Point(5, 5)));

        // Turn off armament (module not included)
        armament.turnOff();

        REQUIRE_THROWS_AS(armament.neutralizeTheIntruder(plan, 5, 5, violator), std::invalid_argument);
    }
    SECTION("Initialization") {
        Optical optical("TestOptical", 3);

        REQUIRE(optical.getName() == "TestOptical");
        REQUIRE(optical.getRadius() == 3);
        REQUIRE(optical.getType() == "Optical");
        REQUIRE_FALSE(optical.isTurnedOn1());
    }

    SECTION("Turn On/Off") {
        Optical optical("TestOptical", 3);

        optical.turnOn();
        REQUIRE(optical.isTurnedOn1());

        optical.turnOff();
        REQUIRE_FALSE(optical.isTurnedOn1());
    }



    SECTION("getInfo when Turned Off") {
        Plan plan(5, 5);
        Optical optical("TestOptical", 1);

        // optical is turned off by default

        // Assuming you have a method to set objects in the plan
        Point point(2,2);
        plan.add_object(Point(1, 1), std::make_shared<MobilePlatform>("TestMobilePlatform", point, 5, 3));

        REQUIRE_THROWS_AS(optical.getInfo(plan, 1, 1), std::invalid_argument);
    }

//    SECTION("ban_cells") {
//        Optical optical("TestOptical", 3);
//
//        std::vector<std::vector<size_t>> cells(5, std::vector<size_t>(5, 1));
//        optical.ban_cells(2, 2, cells);
//
//        // Modify this based on your expected result after banning cells
//        REQUIRE(cells == std::vector<std::vector<size_t>>{
//                {0, 0, 0, 1, 1},
//                {0, 0, 0, 1, 1},
//                {0, 0, 0, 1, 1},
//                {1, 1, 1, 1, 1},
//                {1, 1, 1, 1, 1}
//        });
//    }

    SECTION("ban_cells - out of bounds") {
        Optical optical("TestOptical", 3);

        std::vector<std::vector<size_t>> cells(5, std::vector<size_t>(5, 1));

        // Call ban_cells with coordinates out of bounds
        REQUIRE_NOTHROW(optical.ban_cells(6, 6, cells));
    }
    SECTION("Default constructor and size") {
        Vector<int> vec;
        REQUIRE(vec.Size() == 0);
        REQUIRE(vec.IsEmpty());
    }

    SECTION("Initializer list constructor") {
        Vector<int> vec = {1, 2, 3, 4, 5};
        REQUIRE(vec.Size() == 5);
        REQUIRE(vec[0] == 1);
        REQUIRE(vec[4] == 5);
    }

    SECTION("Copy constructor") {
        Vector<int> original = {1, 2, 3};
        Vector<int> copy(original);

        REQUIRE(copy.Size() == 3);
        REQUIRE(copy[0] == 1);
        REQUIRE(copy[2] == 3);
    }

    SECTION("Move constructor") {
        Vector<int> original = {1, 2, 3};
        Vector<int> moved(std::move(original));

        REQUIRE(moved.Size() == 3);
        REQUIRE(moved[0] == 1);
        REQUIRE(moved[2] == 3);

        // Original should be in a valid but unspecified state after moving
        REQUIRE(original.Size() == 0);
    }

    SECTION("Copy assignment operator") {
        Vector<int> original = {1, 2, 3};
        Vector<int> copy;
        copy = original;

        REQUIRE(copy.Size() == 3);
        REQUIRE(copy[0] == 1);
        REQUIRE(copy[2] == 3);
    }

    SECTION("Move assignment operator") {
        Vector<int> original = {1, 2, 3};
        Vector<int> moved;
        moved = std::move(original);

        REQUIRE(moved.Size() == 3);
        REQUIRE(moved[0] == 1);
        REQUIRE(moved[2] == 3);

        // Original should be in a valid but unspecified state after moving
        REQUIRE(original.Size() == 0);
    }

    SECTION("Access elements using subscript operator") {
        Vector<int> vec = {1, 2, 3};
        REQUIRE(vec[0] == 1);
        REQUIRE(vec[1] == 2);
        REQUIRE(vec[2] == 3);
    }

    SECTION("Reserve capacity") {
        Vector<int> vec = {1, 2, 3};
        vec.Reserve(10);

        REQUIRE(vec.Size() == 3);
        REQUIRE(vec.Capacity() >= 10);
    }

    SECTION("Resize vector") {
        Vector<int> vec = {1, 2, 3};
        vec.Resize(5);

        REQUIRE(vec.Size() == 5);
        REQUIRE(vec[3] == 0x73747365);  // Default-initialized elements
        REQUIRE(vec[4] == 0);
    }

    SECTION("Push back element") {
        Vector<int> vec = {1, 2, 3};
        vec.PushBack(4);

        REQUIRE(vec.Size() == 4);
        REQUIRE(vec[3] == 4);
    }

    SECTION("Pop back element") {
        Vector<int> vec = {1, 2, 3};
        vec.PopBack();

        REQUIRE(vec.Size() == 2);
        REQUIRE(vec[0] == 1);
        REQUIRE(vec[1] == 2);
    }

    SECTION("Clear vector") {
        Vector<int> vec = {1, 2, 3};
        vec.Clear();

        REQUIRE(vec.Size() == 0);
        REQUIRE(vec.IsEmpty());
    }

    SECTION("Check if vector contains a value") {
        Vector<int> vec = {1, 2, 3};

        REQUIRE(vec.Contains(2));
        REQUIRE_FALSE(vec.Contains(4));
    }

    SECTION("Find value in vector") {
        Vector<int> vec = {1, 2, 3};

        REQUIRE(vec.Find(2));
        REQUIRE_FALSE(vec.Find(4));
    }

    SECTION("Check if vector is empty") {
        Vector<int> vec;
        Vector<int> nonEmptyVec = {1, 2, 3};

        REQUIRE(vec.IsEmpty());
        REQUIRE_FALSE(nonEmptyVec.IsEmpty());
    }

    SECTION("Iterator") {
        Vector<int> vec = {1, 2, 3};

        SECTION("Begin and End") {
            auto it = vec.Begin();
            auto end = vec.End();

            REQUIRE(*it == 1);
            REQUIRE(it != end);

            ++it;
            REQUIRE(*it == 2);
            REQUIRE(it != end);

            ++it;
            REQUIRE(*it == 3);
            REQUIRE(it != end);

            ++it;
            REQUIRE(it == end);
        }

        SECTION("Iterator arithmetic") {
            auto it = vec.Begin();
            auto end = vec.End();

            REQUIRE(*(it + 1) == 2);
            REQUIRE(*(it + 2) == 3);
            REQUIRE((it + 3) == end);

            REQUIRE(*(end - 1) == 3);
            REQUIRE(*(end - 2) == 2);
            REQUIRE(*(end - 3) == 1);
        }

        SECTION("Iterator comparison") {
            auto it1 = vec.Begin();
            auto it2 = vec.Begin();
            auto end = vec.End();

            REQUIRE(it1 == it2);
            REQUIRE_FALSE(it1 != it2);

            ++it1;
            REQUIRE(it1 != it2);
            REQUIRE_FALSE(it1 == it2);

            it2 = end;
            REQUIRE(it1 != it2);
            REQUIRE_FALSE(it1 == it2);
        }
    }
    SECTION("Initialization") {
        Point point(2, 3);
        Network network("TestNetwork", point, 5, true, 10);

        REQUIRE(network.getType() == "Network");
        REQUIRE(network.getRadius() == 5);
        REQUIRE(network.getRemainingSessions() == 10);
        REQUIRE(network.isActive());
    }

    SECTION("Get neighboring partners") {
        Plan plan(5, 5);  // Assuming a 5x5 plan
        Point point(2, 2);
        Network network("TestNetwork", point, 1, true, 10);

        // Add some neighboring networks to the plan
        plan.add_object(point.x - 1, point.y, std::make_shared<Network>("Neighbor1", Point(point.x - 1, point.y), 1, true, 5));
        plan.add_object(point.x, point.y - 1, std::make_shared<Network>("Neighbor2", Point(point.x, point.y - 1), 1, true, 7));

        Vector<Point> neighbors = network.getNeighboringPartners(plan);

        REQUIRE(neighbors.Size() == 2);
        REQUIRE(neighbors[0] == Point(point.x - 1, point.y));
        REQUIRE(neighbors[1] == Point(point.x, point.y - 1));
    }

    SECTION("Get direct partners for node") {
        Plan plan(5, 5);  // Assuming a 5x5 plan
        Point point(2, 2);
        Network network("TestNetwork", point, 1, true, 10);

        // Add a neighboring network and its neighbors to the plan
        plan.add_object(point.x - 1, point.y, std::make_shared<Network>("Neighbor1", Point(point.x - 1, point.y), 1, true, 5));
        plan.add_object(point.x - 1, point.y - 1, std::make_shared<Network>("Neighbor2", Point(point.x - 1, point.y - 1), 1, true, 7));
        plan.add_object(point.x - 1, point.y + 1, std::make_shared<Network>("Neighbor3", Point(point.x - 1, point.y + 1), 1, true, 3));

        Vector<Point> directPartners = network.getDirectPartnersForNode(plan);

        REQUIRE(directPartners.Size() == 3);
        REQUIRE(directPartners[0] == Point(point.x - 1, point.y));
        REQUIRE(directPartners[1] == Point(point.x - 1, point.y - 1));
        REQUIRE(directPartners[2] == Point(point.x - 1, point.y + 1));
    }



}
