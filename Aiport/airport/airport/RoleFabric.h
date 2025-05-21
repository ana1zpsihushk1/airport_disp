#pragma once
#include <memory>
#include <cstdlib>
#include <ctime>
#include "Role.h"
#include "WideBody.h"
#include "NarrowBody.h"
#include "Regional.h"
#include "Local.h"
#include "Cargo.h"

inline std::unique_ptr<Role> createRandomRole()
{
    std::srand(time(nullptr));
    int r = std::rand() % 4;

    switch (r)
    {
    case 0: return std::make_unique<WideBody>(100, 3, 5, 2.0f);
    case 1: return std::make_unique<NarrowBody>(80, 2, 4, 2.0f);
    case 2: return std::make_unique<Regional>(60, 2, 3, 2.0f);
    case 3: return std::make_unique<Local>(40, 1, 2, 2.0f);
    default: return std::make_unique<Cargo>(100, 3, 5, 2.0f);
    }
}

inline std::unique_ptr<Role> createRoleByType(const std::string& type)
{
    if (type == "WideBody")    return std::make_unique<WideBody>(100, 3, 5, 2.0f);
    if (type == "NarrowBody")  return std::make_unique<NarrowBody>(80, 2, 4, 2.0f);
    if (type == "Regional")    return std::make_unique<Regional>(60, 2, 3, 2.0f);
    if (type == "Local")       return std::make_unique<Local>(40, 1, 2, 2.0f);
    if (type == "Cargo")       return std::make_unique<Cargo>(100, 3, 5, 2.0f);

    throw std::invalid_argument("Unknown role type: " + type);
}