#ifndef _TRANSFORM_MANAGER_H
#define _TRANSFORM_MANAGER_H

#include <unordered_map>
#include "Components/TransformComponent.h"

#include "Interfaces/IManager.h"

class TransformManager final : public IManager
{
private:
	std::unordered_map< size_t, TransformComponent*> _transformList;

public:
	TransformManager() = default;
	virtual ~TransformManager() {}

	TransformManager(const TransformManager& rhs) = delete;
	TransformManager& operator= (const TransformManager& rhs) = delete;

	void AddObject(size_t uId, void* component = 0);
	void RemoveObject(size_t uId);

	TransformComponent* GetTransform(size_t uId);

	static void UpdateTransformMartix(TransformComponent* transform);
	static Mtx44 GetTransformMartix(TransformComponent* transform);
};

#endif
