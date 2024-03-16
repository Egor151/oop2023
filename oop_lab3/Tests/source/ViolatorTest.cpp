#include "catch2/catch_all.hpp"
#include "../../lab3/SecurityPlan/Point/include/Point/Point.h"
#include "../../lab3/Violator/include/Violator/Violator.h"
#include "../../lab3/SecurityPlan/Plan/include/Plan/Plan.h"
#include "../../lab3/AI/include/AI/AI.h"
#include "../../lab3/SystemSecurity/Platform/include/Platform/Platform.h"
#include "../../lab3/SystemSecurity/StationaryPlatform/include/StationaryPlatform/StationaryPlatform.h"
#include "../../lab3/CheckNum/include/CheckNum/getNum.h"
#include <sstream>

TEST_CASE("Violator class tests", "[Violator]") {
    SECTION("Initialization") {
        Point initialPoint{1, 1};
        Violator violator("TestViolator", 100, initialPoint);

        REQUIRE(violator.getName() == "TestViolator");
        REQUIRE(violator.getHp() == 100);
        REQUIRE(violator.getPoint() == initialPoint);
    }

    SECTION("Setters and Getters") {
        Point initialPoint{1, 1};
        Violator violator("TestViolator", 100, initialPoint);

        // Test getters
        REQUIRE(violator.getName() == "TestViolator");
        REQUIRE(violator.getHp() == 100);
        REQUIRE(violator.getPoint() == initialPoint);

        // Test setters
        violator.setHp(75);
        REQUIRE(violator.getHp() == 75);

        Point newPoint{2, 2};
        violator.setPoint(newPoint);
        REQUIRE(violator.getPoint() == newPoint);
    }

    SECTION("Move Violator") {
        // Create a Plan for testing
        Plan plan(3, 3);

        Point initialPoint{1, 1};
        Violator violator("TestViolator", 100, initialPoint);

        // Add Violator to the plan
        std::shared_ptr<Violator> violatorPtr = std::make_shared<Violator>(violator);
        plan.get_cell(initialPoint.x, initialPoint.y).add_object_if_absent(violatorPtr);

        // Move Violator to a new valid point
        Point newPoint{2, 2};
        violator.moveViolator(plan, newPoint);

        // Check if the Violator is now at the new point
        REQUIRE(violator.getPoint() == newPoint);
        REQUIRE(plan.get_object_at(newPoint.x, newPoint.y).get() == violatorPtr.get());

        // Move Violator to an invalid point, should throw an exception
        Point invalidPoint{4, 4};
        REQUIRE_THROWS_AS(violator.moveViolator(plan, invalidPoint), std::out_of_range);
    }

}
