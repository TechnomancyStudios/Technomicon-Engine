#pragma once
#include <vector>
#include <bitset>
#include <queue>
#include <iostream>
#include <array>
#include <unordered_map>

using Entity = std::uint32_t;
using ComponentType = std::uint8_t;

const Entity MAX_ENTITIES = 5000;
const ComponentType MAX_COMPONENTS = 32;

//Make a 32 bit ID. Each bit represents a component
using Signature = std::bitset<MAX_COMPONENTS>;

class EntityManager
{
public:
	//Initialize the queue with all possible entity IDs
	EntityManager()
	{
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
			emAvailableEntities.push(entity);
	}

	Entity CreateEntity()
	{
		if (emLivingEntityCount < MAX_ENTITIES)
		{
			//Take ID from the front of the queue
			Entity id = emAvailableEntities.front();
			emAvailableEntities.pop();
			++emLivingEntityCount;
			return id;
		}
		else
		{
			std::cout << "Too many entities!" << std::endl;
			return -1;
		}
		
	}

	void DestroyEntity(Entity entity)
	{
		if (entity < MAX_ENTITIES)
		{
			//Set all of the Signature bits to 0
			emSignature[entity].reset();
			//Put destroyed entity ID at the back of the queue
			emAvailableEntities.push(entity);
			--emLivingEntityCount;
		}
		else
		{
			std::cout << "Entity Out of Range!" << std::endl;
		}
	}

	void SetSignature(Entity entity, Signature signature)
	{
		if (entity < MAX_ENTITIES)
		{
			emSignature[entity] = signature;
		}
		else
		{
			std::cout << "Entity Out of Range!" << std::endl;
		}
	}

	Signature GetSignature(Entity entity)
	{
		if (entity < MAX_ENTITIES)
		{
			return emSignature[entity];
		}
		else
		{
			std::cout << "Entity Out of Range!" << std::endl;
		}
	}

private:
	//Queue of unused entity IDs
	std::queue<Entity> emAvailableEntities{};

	//Array of signatures where the index corresponds to the entity ID
	std::array<Signature, MAX_ENTITIES> emSignature{};

	//Total living entities - used to keep limits on how many exist
	uint32_t emLivingEntityCount{};
};


class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
public:
	void InsertData(Entity entity, T component)
	{
		//Put new entry at end and update the maps
		size_t newIndex = caSize;
		caEntityToIndexMap[entity] = newIndex;
		caIndexToEntityMap[newIndex] = entity;
		caComponentArray[newIndex] = component;
		++caSize;
	}

	

private:
	// The packed array of components (of generic type T),
	// set to a specified maximum amount, matching the maximum number
	// of entities allowed to exist simultaneously, so that each entity
	// has a unique spot.
	std::array<T, MAX_ENTITIES> caComponentArray;

	//Map from an entity ID to an array index
	std::unordered_map<Entity, size_t> caEntityToIndexMap;

	//Map from an array index to an entity ID
	std::unordered_map<size_t, Entity> caIndexToEntityMap;

	//Total size of valid entries in the array
	size_t caSize;
};