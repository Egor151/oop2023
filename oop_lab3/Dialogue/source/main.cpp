#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Plan/Plan.h"
#include "Violator/Violator.h"
#include "AI/AI.h"
#include "Obstacles/Obstacles.h"
#include "CreateTab/CreateTab.h"
#include "CheckNum/getNum.h"


int main() {
    try {
        std::cout << "Enter the number of rows for the plan: ";
        auto rows = getNum<size_t>(1);  // Minimum row value is set to 1

        std::cout << "Enter the number of columns for the plan: ";
        auto cols = getNum<size_t>(1);  // Minimum column value is set to 1

        Plan plan(rows, cols);
        std::shared_ptr<Violator> violator = std::make_shared<Violator>("user", 100, plan.get_entrance());

        auto object = std::dynamic_pointer_cast<Object>(violator);
        plan.add_object(plan.get_entrance(), object);

        CreateTabTest createTab(plan, {{"Obstacles",          '#'},
                                       {"StationaryPlatform", 'S'},
                                       {"Armament",           'a'},
                                       {"Optical",            'o'},
                                       {"Xray",               'x'},
                                       {"Network",            'n'},
                                       {"MobilePlatform",     'M'},
                                       {"Violator",           'V'}}, violator);


        createTab.save_object();
        createTab.game_loop();
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }
    return 0;
}
