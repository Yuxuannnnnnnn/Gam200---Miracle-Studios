#pragma once
#ifndef _FONT_MANAGER_H
#define _FONT_MANAGER_H

#include <unordered_map>
#include "Components/FontComponent.h"

#include "Interfaces/IManager.h"

class FontManager final : public IManager
{
private:
	std::unordered_map< size_t, FontComponent*> _fontList;

public:
	FontManager() = default;
	virtual ~FontManager() {}

	FontManager(const FontManager& rhs) = delete;
	FontManager& operator= (const FontManager& rhs) = delete;

	void AddObject(size_t uId, void* component = 0) { (void)uId; (void)component; };
	void RemoveObject(size_t uId) { (void)uId; };
};

#endif
