#include "CreateTab/CreateTab.h"
#include <map>
#include <iostream>


CreateTabTest::CreateTabTest(Plan plan, std::map<std::string, char> info, std::shared_ptr<Violator> violator) : info_(
        std::move(info)), ai_(plan_), violator_(std::move(violator)) {
    plan_ = std::move(plan);

}

void CreateTabTest::print_table() {
    auto entrance = plan_.get_entrance();
    auto exit = plan_.get_exit();
    for (long i = -1; i <= (long) plan_.get_rows(); i++) {
        for (long j = -1; j <= (long) plan_.get_cols(); j++) {

            if (i == -1 || j == -1 || i == plan_.get_rows() || j == plan_.get_cols()) {
                std::cout << "*";
                if ((i - 1) == (long) entrance.x && (j - 1) == (long) entrance.y ||
                    (i - 1) == (long) exit.x && (j - 1) == (long) exit.y) {
                    std::cout << "|";
                }
                continue;
            }
            if (plan_.has_object(i, j)) {
                std::string name = plan_.get_cell_t(i, j).second;

                std::cout << info_[name];

            } else {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
}

void CreateTabTest::save_object() {
    ai_.createPlatform();
}

void CreateTabTest::interactWithConsole() {
    std::cout << "Enter the direction to move (U/D/L/R): ";
    char direction;
    std::cin >> direction;

    // Очистка буфера ввода, чтобы избежать проблем с дальнейшим вводом
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Point newPoint = violator_->getPoint();

    switch (direction) {
        case 'U':
            newPoint.x = std::max(newPoint.x, static_cast<size_t>(1)) - 1;
            break;
        case 'D':
            newPoint.x = std::min(newPoint.x + 1, plan_.get_rows() - 1);
            break;
        case 'L':
            newPoint.y = std::max(newPoint.y, static_cast<size_t>(1)) - 1;
            break;
        case 'R':
            newPoint.y = std::min(newPoint.y + 1, plan_.get_cols() - 1);
            break;
        default:
            std::cerr << "Invalid direction. Please enter U, D, L, or R." << std::endl;
            return;
    }

    try {
        violator_->moveViolator(plan_, newPoint);
        std::cout << "Violator moved successfully to (" << newPoint.x << ", " << newPoint.y << ")." << std::endl;
    } catch (const std::out_of_range &e) {
        std::cerr << e.what() << std::endl;
    }
}

void CreateTabTest::game_loop() {
    bool finish = false;
    while (!finish) {
        print_table();
        interactWithConsole();
        std::thread moveThread(&AI::movePlatforms,  std::ref(ai_));

        if (violator_->getPoint() == plan_.get_exit()) {
            finish = true;
            std::cout << "YOU WIN" << std::endl;
        } else if(violator_->getHp() <= 0) {
            finish = true;
            std::cout << "GAME OVER: You lost. Violator's health is 0." << std::endl;
        }
        moveThread.join();
    }
}