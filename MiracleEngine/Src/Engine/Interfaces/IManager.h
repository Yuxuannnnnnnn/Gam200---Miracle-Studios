#ifndef _IMANAGER_H
#define _IMANAGER_H

class IManager
{
public:
	IManager() = default;
	virtual ~IManager() {}

	virtual void AddObject(size_t uId, void* component = 0) = 0;
	virtual void RemoveObject(size_t uId) = 0;
};

#endif
