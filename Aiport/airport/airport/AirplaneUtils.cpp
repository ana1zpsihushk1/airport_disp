#include <random>

#include "AirplaneUtils.h"

std::string generatePlaneName(const std::string& typeCode)
{
	static std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(0, 9);

	std::string name = typeCode + "-";
	for (int i = 0; i < 4; ++i)
		name += std::to_string(dist(rng));

	return name;
}
