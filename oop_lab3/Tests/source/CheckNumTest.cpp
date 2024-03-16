#include "catch2/catch_all.hpp"
#include "../../lab3/SecurityPlan/Point/include/Point/Point.h"
#include "../../lab3/Violator/include/Violator/Violator.h"
#include "../../lab3/SecurityPlan/Plan/include/Plan/Plan.h"
#include "../../lab3/AI/include/AI/AI.h"
#include "../../lab3/SystemSecurity/Platform/include/Platform/Platform.h"
#include "../../lab3/SystemSecurity/StationaryPlatform/include/StationaryPlatform/StationaryPlatform.h"
#include "../../lab3/CheckNum/include/CheckNum/getNum.h"
#include <sstream>

TEST_CASE("getNum tests", "[getNum]") {
SECTION("Valid input within the range") {
std::istringstream input("42");
std::cin.rdbuf(input.rdbuf());

int result = getNum<int>(0, 100);

REQUIRE(result == 42);
}

SECTION("Valid input outside the range") {
std::istringstream input("150");
std::cin.rdbuf(input.rdbuf());

int result = getNum<int>(0, 100);

REQUIRE(result == 150);
}

SECTION("Invalid input followed by valid input") {
std::istringstream input("invalid\n42");
std::cin.rdbuf(input.rdbuf());

int result = getNum<int>(0, 100);

REQUIRE(result == 42);
}

SECTION("EOF input") {
std::istringstream input("");
std::cin.rdbuf(input.rdbuf());

REQUIRE_THROWS_AS(getNum<int>(), std::runtime_error);
}

SECTION("Bad input") {
std::istringstream input("not_an_integer");
std::cin.rdbuf(input.rdbuf());

REQUIRE_THROWS_AS(getNum<int>(), std::runtime_error);
}

SECTION("Valid input with a custom range") {
std::istringstream input("75");
std::cin.rdbuf(input.rdbuf());

int result = getNum<int>(50, 100);

REQUIRE(result == 75);
}

SECTION("Invalid input within the range") {
std::istringstream input("invalid");
std::cin.rdbuf(input.rdbuf());

REQUIRE_THROWS_AS(getNum<int>(0, 100), std::runtime_error);
}

SECTION("Invalid input outside the range") {
std::istringstream input("150");
std::cin.rdbuf(input.rdbuf());

REQUIRE_THROWS_AS(getNum<int>(50, 100), std::runtime_error);
}
}