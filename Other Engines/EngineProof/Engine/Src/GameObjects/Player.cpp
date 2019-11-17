#include "Player.h"

Player* Player::Clone(Vector3 pos, Vector3 scale, float rotate)
{
	Player* original = dynamic_cast<Player*>(objFab["Player"]);
	Player* temp = new Player();
	temp->_pos = pos;
	temp->_scale = scale;
	temp->_angle = rotate;
	temp->_id = original->_id;
	temp->_Health = original->_Health;
	temp->_Speed = original->_Speed;
	temp->_WeaponListId = original->_WeaponListId;
	return temp;
}