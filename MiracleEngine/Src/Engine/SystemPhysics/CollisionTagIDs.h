#pragma once

enum class ColliderTag {
	NONE = 0,
	PLAYER ,
	BULLET,
	ENEMY,
	TURRET,
	DESTORYABLE_BUILDING,
	BUILDING,
	BULLET_E,
	PICK_UPS,
	EDGES,
	BOSS,
	SPAWNER,

	TOTAL_TAG
};

inline const char* ToString(ColliderTag type) //Convert TypeIdComponent Enum to const char* - For Use only in Imgui
{
	switch (type)
	{
	case ColliderTag::NONE:			return "NONE";
	case ColliderTag::PLAYER:			return "PLAYER";
	case ColliderTag::BULLET:			return "BULLET";
	case ColliderTag::ENEMY:			return "ENEMY";
	case ColliderTag::TURRET:			return "TURRET";
	case ColliderTag::DESTORYABLE_BUILDING:			return "DESTORYABLE BUILDING";
	case ColliderTag::BUILDING:			return "BUILDING";
	case ColliderTag::BULLET_E:			return "ENEMY BULLET";
	case ColliderTag::PICK_UPS:			return "PICK UPS";
	case ColliderTag::EDGES:			return "EDGES";
	case ColliderTag::BOSS:			return "BOSS";
	case ColliderTag::SPAWNER:			return "SPAWNER";

	default:      return "[Unknown ColliderTag]";
	}
}