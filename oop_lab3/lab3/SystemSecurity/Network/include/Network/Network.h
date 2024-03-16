#ifndef LAB3_NETWORK_H
#define LAB3_NETWORK_H

#include "Platform/Platform.h"
#include "Point/Point.h"
#include "Plan/Plan.h"
#include "Vector.h"
#include "Object/Object.h"
#include <string>


class Network : public Module {
private:
    std::string name_;
    Point &point_;
    size_t radius_;
    Vector<Point> switchingTable_;
    Vector<Point> activeSessions_;
    size_t remainingSessions_;
    bool active_;

public:
    /**
     * @brief The Network class represents a network module in a security plan, facilitating communication
     *        and coordination between various security components.
     *
     * The Network class manages connections, sessions, and partnerships among network modules within its
     * specified radius.
     */
    Network(std::string name, Point &point, size_t radius, bool active, size_t remainingSessions);
    /**
     * @brief Retrieves the type of the network module.
     * @return A string representing the type, which is "Network" in this case.
     */
    [[nodiscard]]  std::string getType() const override;
    /**
     * @brief Retrieves the radius of the network module.
     * @return The radius of the network module.
     */
    [[nodiscard]] size_t getRadius() const;
    /**
     * @brief Gets neighboring partners within the specified radius.
     * @param plan The security plan.
     * @return A vector of points representing the neighboring partners.
     * @throws std::invalid_argument if the module is not active.
     */
    Vector<Point> getNeighboringPartners(Plan &plan);
    /**
     * @brief Gets direct partners for the network node within the plan.
     * @param plan The security plan.
     * @return A vector of points representing the direct partners for the network node.
     * @throws std::invalid_argument if the module is not active.
     */
    Vector<Point> getDirectPartnersForNode(Plan &plan);
    /**
     * @brief Establishes connections to neighbors based on the provided platform's point.
     * @param plan The security plan.
     * @param platform The point representing the platform.
     * @return A vector of points representing the active sessions.
     * @throws std::invalid_argument if the module is not included.
     */
    Vector<Point> getConnectionsToNeighbors(Plan &plan, Point platform1);
    /**
     * @brief Turns on the network module, enabling its functionalities.
     */
    void turnOn() override;
    /**
     * @brief Turns off the network module, disabling its functionalities.
     */
    void turnOff() override;
    /**
     * @brief Default destructor for the Network class.
     */
    ~Network();

};

#endif
