#include "catch2/catch_all.hpp"
#include "../../lab3/SecurityPlan/Point/include/Point/Point.h"
#include "../../lab3/Violator/include/Violator/Violator.h"
#include "../../lab3/SecurityPlan/Plan/include/Plan/Plan.h"
#include "../../lab3/AI/include/AI/AI.h"
#include "../../lab3/SystemSecurity/Platform/include/Platform/Platform.h"
#include "../../lab3/SystemSecurity/StationaryPlatform/include/StationaryPlatform/StationaryPlatform.h"
#include "../../lab3/CheckNum/include/CheckNum/getNum.h"
#include <sstream>
class TestObject : public Object {
public:
    explicit TestObject(std::string name) : name_(std::move(name)) {}

    std::string get_cell_type() override {
        return "TestObjectType";
    }

    const std::string &getName() const override {
        return name_;
    }

private:
    std::string name_;
};
TEST_CASE("Point class tests", "[Point]") {
    SECTION("Initialization") {
        Point point1;
        REQUIRE(point1.x == 0);
        REQUIRE(point1.y == 0);

        Point point2(3, 5);
        REQUIRE(point2.x == 3);
        REQUIRE(point2.y == 5);
    }

    SECTION("Equality Operator") {
        Point point1(2, 4);
        Point point2(2, 4);
        Point point3(1, 3);

        REQUIRE(point1 == point2);
        REQUIRE_FALSE(point1 == point3);
    }

    SECTION("Inequality Operator") {
        Point point1(2, 4);
        Point point2(2, 4);
        Point point3(1, 3);

        REQUIRE_FALSE(point1 != point2);
        REQUIRE(point1 != point3);
    }

    SECTION("Get String Representation") {
        Point point(2, 4);
        REQUIRE(point.get_string() == "(2, 4)");
    }
    SECTION("GetName") {
        std::unique_ptr<Object> object = std::make_unique<TestObject>("TestObject");
        REQUIRE(object->getName() == "TestObject");
    }

        // Add more test cases for other methods or behaviors of your specific derived class from Object.
    SECTION("Default Constructor") {
        Cell cell;
        REQUIRE_FALSE(cell.has_object());
    }

    SECTION("Constructor with Object and Point") {
        Point point(1, 1);
        std::shared_ptr<Object> object = std::make_shared<TestObject>("TestObject");
        Cell cell(object, point);

        REQUIRE(cell.has_object());
        REQUIRE(cell.get_object() == object);
        REQUIRE(cell.get_cell_type() == "(1, 1): Cell");
    }

    SECTION("Set Object") {
        Cell cell;
        std::shared_ptr<Object> object = std::make_shared<TestObject>("TestObject");
        cell.set_object(object);

        REQUIRE(cell.has_object());
        REQUIRE(cell.get_object() == object);
    }

    SECTION("Set Point") {
        Cell cell;
        Point point(2, 2);
        cell.set_point(point);

        REQUIRE(cell.get_cell_type() == "(2, 2): Cell");
    }

    SECTION("Has Object") {
        Cell cell;
        REQUIRE_FALSE(cell.has_object());

        std::shared_ptr<Object> object = std::make_shared<TestObject>("TestObject");
        cell.set_object(object);
        REQUIRE(cell.has_object());
    }

    SECTION("Get Cell Type") {
        Cell cell;
        REQUIRE(cell.get_cell_type() == "(-1, -1): Cell");

        Point point(3, 3);
        cell.set_point(point);
        REQUIRE(cell.get_cell_type() == "(3, 3): Cell");
    }

    SECTION("Get Info") {
        Cell cell;
        std::shared_ptr<Object> object = std::make_shared<TestObject>("TestObject");
        cell.set_object(object);

        auto info = cell.get_info();
        REQUIRE(info.first == Point(-1, -1));
        REQUIRE(info.second == "TestObjectType");
    }

    SECTION("Add Object If Absent") {
        Cell cell;
        std::shared_ptr<Object> object = std::make_shared<TestObject>("TestObject");

        REQUIRE_NOTHROW(cell.add_object_if_absent(object));
        REQUIRE(cell.has_object());
        REQUIRE(cell.get_object() == object);

        // Adding another object should throw an exception
        REQUIRE_THROWS_AS(cell.add_object_if_absent(object), std::invalid_argument);
    }
    SECTION("Default Constructor") {
        Plan plan;
        REQUIRE(plan.get_rows() == 0);
        REQUIRE(plan.get_cols() == 0);
    }

    SECTION("Constructor with Rows and Columns") {
        Plan plan(3, 4);
        REQUIRE(plan.get_rows() == 3);
        REQUIRE(plan.get_cols() == 4);
    }

    SECTION("Get Cell Type") {
        Plan plan(2, 2);
        REQUIRE(plan.get_cell_type(0, 0) == "(0, 0): Cell");

        Point point(1, 1);
        plan.add_object(point, std::make_shared<TestObject>("TestObject"));
        REQUIRE(plan.get_cell_type(1, 1) == "(1, 1): Cell");
    }

    SECTION("Add Object") {
        Plan plan(2, 2);
        Point point(1, 1);
        std::shared_ptr<Object> object = std::make_shared<TestObject>("TestObject");

        REQUIRE_NOTHROW(plan.add_object(point, object));

        // Adding another object to the same point should throw an exception
        REQUIRE_THROWS_AS(plan.add_object(point, object), std::invalid_argument);
    }

    SECTION("Get Cell") {
        Plan plan(2, 2);
        Cell& cell = plan.get_cell(1, 1);

        REQUIRE(cell.get_cell_type() == "(1, 1): Cell");
    }

    SECTION("Has Object") {
        Plan plan(2, 2);
        Point point(1, 1);

        REQUIRE_FALSE(plan.has_object(1, 1));

        plan.add_object(point, std::make_shared<TestObject>("TestObject"));
        REQUIRE(plan.has_object(1, 1));
    }

    SECTION("Delete Object") {
        Plan plan(2, 2);
        Point point(1, 1);
        plan.add_object(point, std::make_shared<TestObject>("TestObject"));

        REQUIRE(plan.has_object(1, 1));

        plan.deleteObject(point);
        REQUIRE_FALSE(plan.has_object(1, 1));
    }

    SECTION("Get Object At") {
        Plan plan(2, 2);
        Point point(1, 1);
        std::shared_ptr<Object> object = std::make_shared<TestObject>("TestObject");
        plan.add_object(point, object);

        REQUIRE(plan.get_object_at(1, 1) == object);

        // Accessing an out-of-bounds coordinate should throw an exception
        REQUIRE_THROWS_AS(plan.get_object_at(3, 3), std::out_of_range);
    }

    SECTION("Set and Get Entrance") {
        Plan plan(3, 3);
        Point entrance(1, 1);
        plan.set_entrance(entrance);

        REQUIRE(plan.get_entrance() == entrance);
    }

    SECTION("Set and Get Exit") {
        Plan plan(3, 3);
        Point exit(2, 2);
        plan.set_exit(exit);

        REQUIRE(plan.get_exit() == exit);
    }
}