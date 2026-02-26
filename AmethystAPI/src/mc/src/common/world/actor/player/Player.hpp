/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>

class UserEntityIdentifierComponent;

class Player {
public:
	MC const UserEntityIdentifierComponent* getUserIdentity() const;
	MC UserEntityIdentifierComponent* getUserIdentity();
};
