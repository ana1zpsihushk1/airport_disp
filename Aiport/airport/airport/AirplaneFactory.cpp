#include "AirplaneFactory.h"
#include "AirplaneUtils.h"

std::shared_ptr<Airplane> AirplaneFactory::createAirplane(const std::string& id, const FlightSchedule& schedule)
{
    std::unique_ptr<Role> role = createRandomRole();
    auto plane = std::make_shared<Airplane>(id, std::move(role), sf::seconds(static_cast<float>(schedule.getArrivalInSeconds())));

    plane->setSchedule(schedule);

    std::string name = generatePlaneName(plane->getRoleType());
    plane->setDisplayName(name);

    return plane;
}
