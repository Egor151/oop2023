#ifndef OOP_LAB3_CREATETAB_H
#define OOP_LAB3_CREATETAB_H

#include <map>
#include "Plan/Plan.h"
#include "AI/AI.h"
#include "Violator/Violator.h"

class CreateTabTest {
public:
    explicit CreateTabTest(Plan plan, std::map<std::string,char> info, std::shared_ptr<Violator> violator);

    void print_table();
    void save_object();
    void interactWithConsole();
    void game_loop();

    std::shared_ptr<Violator> violator_;
    Plan plan_;
    std::map<std::string,char> info_;
    AI ai_;
};
#endif
