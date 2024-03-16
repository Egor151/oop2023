#include <utility>
#include <memory>
#include "Network/Network.h"

Network::Network(std::string name, Point &point, size_t radius, bool active, size_t remainingSessions) :
        name_(std::move(name)),
        point_(point),
        radius_(radius),
        remainingSessions_(remainingSessions),
        active_(active){

}
[[nodiscard]] std::string Network::getType() const {
    return "Network";
}

[[nodiscard]] size_t Network::getRadius() const {
    return radius_;
}

//получить список непосредственно доступных партнеров
Vector<Point> Network::getNeighboringPartners(Plan &plan) {
    if (!active_) {
        throw std::invalid_argument("Module isn`t included");
    }
    switchingTable_.Clear();
    for (int x = abs((int)point_.x - (int)radius_); x <= abs( (int)point_.x + (int)radius_) && x < plan.get_rows(); x++) {
        for (int y = abs((int)point_.y - (int)radius_); y <= abs((int)point_.y + (int)radius_) && y < plan.get_cols(); y++) {
            if (y == point_.y && x == point_.x) continue;
            if (plan.get_cell_type(x, y) == "Network") {
                switchingTable_.PushBack(Point(x, y));
            }
        }
    }
    return switchingTable_;
}
//запросить/выдать список доступных партнеров у соседних модулей
Vector<Point> Network::getDirectPartnersForNode(Plan &plan) {
    if (!active_) {
        throw std::invalid_argument("Module isn`t included");
    }
    auto neighbors = getNeighboringPartners(plan);
    Vector<Point> ans;

    for (size_t i = 0; i < neighbors.Size(); ++i) {
        Point neighborPoint = neighbors[i];
        std::shared_ptr obj = plan.get_object_at(neighborPoint.x, neighborPoint.y);
        auto networkNeighbor = dynamic_pointer_cast<Network>(obj);

        if (networkNeighbor) {
            Vector<Point> partnerPoints = networkNeighbor->getNeighboringPartners(plan);
            for (size_t j = 0; j < partnerPoints.Size(); ++j) {
                ans.PushBack(partnerPoints[j]);
            }
        }
    }
    return ans; // выводит всех соседей, соседа к главному
}
//установить непосредственное соединение или канал связи
Vector<Point> Network::getConnectionsToNeighbors(Plan& plan, Point platform) {
    if (!active_) {
        throw std::invalid_argument("Module isn't included");
    }
    auto neighbors = getNeighboringPartners(plan);
    bool flag = false;
    for(size_t i = 0; i < neighbors.Size(); ++i) {
        if(platform == neighbors[i]){
            flag = true;
            break;
        }
    }
    if(flag && !activeSessions_.Find(platform)){
        activeSessions_.PushBack(platform);
        remainingSessions_--;
        return activeSessions_;
    } else {
        flag = false;
        auto connections = getDirectPartnersForNode(plan);
        for(size_t i = 0; i < connections.Size(); ++i) {
            if(platform == connections[i]){
                flag = true;
                break;
            }
        }
        if(flag && !activeSessions_.Find(platform)){
            activeSessions_.PushBack(platform);
            remainingSessions_ -= 2;
            return activeSessions_;
        }
    }
    return activeSessions_;
}

void Network::turnOn() {
    active_ = true;
}

void Network::turnOff() {
    active_ = false;
}

Network::~Network() = default;

