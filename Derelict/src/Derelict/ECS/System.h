#pragma once
#include "EntityComponentSystem.h"

#include <set>
#include <unordered_map>
#include <memory>

class System
{
public:
	std::set<Entity> m_Entities;
};

class SystemManager
{
public:

private:
	std::unordered_map<const char*, Signature> m_Signatures;
	std::unordered_map<const char*, std::shared_ptr<System>> m_Systems;
};