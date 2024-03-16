#include "catch2/catch_all.hpp"
#include "Plan/Plan.h"
#include "Violator/Violator.h"
#include "../../lab3/CreateTab/include/CreateTab/CreateTab.h"
#include <sstream>
#include <iostream>
// Mock for cin buffer
struct CinBufferMock {
    CinBufferMock(std::istringstream& iss) {
        std::cin.rdbuf(iss.rdbuf());
    }

    ~CinBufferMock() {
        // Restore cin buffer after the test
        std::cin.rdbuf(originalCinBuffer);
    }

    std::streambuf* originalCinBuffer = std::cin.rdbuf();
};
TEST_CASE("CreateTabTest class tests", "[CreateTabTest]") {
    SECTION("Initialization") {
        Plan plan(5, 5);
        std::map<std::string, char> info{{"Platform", 'P'}, {"Violator", 'V'}, {"Network", 'N'}};
        std::shared_ptr<Violator> violator = std::make_shared<Violator>("TestViolator", 100, Point(1, 1));

        CreateTabTest createTab(plan, info, violator);

        REQUIRE(createTab.plan_.get_rows() == 5);
        REQUIRE(createTab.plan_.get_cols() == 5);
        REQUIRE(createTab.info_ == info);
        REQUIRE(createTab.ai_.plan_.get_rows() == 5);
        REQUIRE(createTab.ai_.plan_.get_cols() == 5);
        REQUIRE(createTab.violator_->getName() == "TestViolator");
        REQUIRE(createTab.violator_->getHp() == 100);
        REQUIRE(createTab.violator_->getPoint().x == 1);
        REQUIRE(createTab.violator_->getPoint().y == 1);
    }

    SECTION("Print Table") {
        Plan plan(3, 3);
        std::map<std::string, char> info{{"Platform", 'P'}, {"Violator", 'V'}, {"Network", 'N'}};
        std::shared_ptr<Violator> violator = std::make_shared<Violator>("TestViolator", 100, Point(1, 1));
        CreateTabTest createTab(plan, info, violator);

        std::ostringstream output;
        // Redirect cout to the output stream for comparison
        auto coutBuffer = std::cout.rdbuf(output.rdbuf());

        createTab.print_table();

        // Reset cout to the standard output stream
        std::cout.rdbuf(coutBuffer);

        std::string expectedOutput = "PPP\nPVP\nPPP\n";
        REQUIRE(output.str() == expectedOutput);
    }

    // Add more test cases for save_object, interactWithConsole, and game_loop as needed.

    SECTION("Save Object") {
        Plan plan(5, 5);
        std::map<std::string, char> info{{"Platform", 'P'}, {"Violator", 'V'}, {"Network", 'N'}};
        std::shared_ptr<Violator> violator = std::make_shared<Violator>("TestViolator", 100, Point(1, 1));
        CreateTabTest createTab(plan, info, violator);

        // Assuming createPlatform is correct, tested in AI class tests.
        createTab.save_object();

        REQUIRE(createTab.ai_.platforms_.size() > 0);
    }

    SECTION("Interact With Console - Move Up") {
        Plan plan(3, 3);
        std::map<std::string, char> info{{"Platform", 'P'}, {"Violator", 'V'}, {"Network", 'N'}};
        std::shared_ptr<Violator> violator = std::make_shared<Violator>("TestViolator", 100, Point(1, 1));
        CreateTabTest createTab(plan, info, violator);

        std::istringstream input("U\n");  // Simulate user input
        CinBufferMock cinBufferMock(input);

        createTab.interactWithConsole();

        REQUIRE(createTab.violator_->getPoint().x == 0);
        REQUIRE(createTab.violator_->getPoint().y == 1);
    }

    SECTION("Interact With Console - Invalid Direction") {
        Plan plan(3, 3);
        std::map<std::string, char> info{{"Platform", 'P'}, {"Violator", 'V'}, {"Network", 'N'}};
        std::shared_ptr<Violator> violator = std::make_shared<Violator>("TestViolator", 100, Point(1, 1));
        CreateTabTest createTab(plan, info, violator);

        std::ostringstream output;
        // Redirect cerr to the output stream for comparison
        auto cerrBuffer = std::cerr.rdbuf(output.rdbuf());

        std::istringstream input("InvalidDirection\n");  // Simulate user input
        CinBufferMock cinBufferMock(input);

        createTab.interactWithConsole();

        // Reset cerr to the standard error stream
        std::cerr.rdbuf(cerrBuffer);

        REQUIRE(output.str().find("Invalid direction.") != std::string::npos);
    }

}