#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Engine.h"
#include "definitions.h"

int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	Engine engine(SCREEN_WIDTH, SCREEN_HEIGHT, "Airport Simulator");
	return 0;
}