#pragma once
#include "GameObject/Components/Logic/IScript.h"

#ifndef BOSS_H
#define	BOSS_H

class Node; // forward declare

/*

// set render layer of BOSS above bullet
// bullet shooting @ the 4 diagonal corners
// death will have mutliple sprite sheets,
	will need to do the way that will play 1 anim after another

Do above half heath shoot laser, then under half spin shoot.
	if ok then try 100-75 normal laser, 75-50||40 rapid shot, remaining spint shoot with critical health anims

Init()
	Boss_inactive_to_active_sprite --> Boss_Idle_sprite
When start laser charge
	Boss_Idle_sprite --> Boss_Laser_Charge_up_sprite
Once laser charged & now shoot laser
	Boss_Laser_Charge_up_sprite --> freeze last frame of prev anim
		+ Laser_Blast_Sprite (actual laser)
Once shoot laser finish & return to IDLE
	Laser_Blasting_small(body single frame) --> Boss_Laser_after_shoot_transform_back_sprite --> Boss_Idle_sprite

On HP < 50, change from IDLE to IDLE_RAGE
	Boss_Idle_sprite --> Boss_Transform_into_rage_sprite --> Boss_Rage_idle_sprite
When want to shoot bullet
	Boss_Rage_idle_sprite --> Boss_rage_transform_to_shoot_style_sprite --> Boss_Shoot_style_sprite OR Boss_Shoot_style_low_HP_sprite
	While shooting, continue with the last anim from above
Once shooting end
	Boss_Shoot_style_sprite OR Boss_Shoot_style_low_HP_sprite --> Boss_shoot_style_transform_to_rage_sprite -->
		Boss_Rage_idle_sprite OR Boss_Rage_idle_low_HP_sprite

On DEATH depending on which mode its in, use the right death anim
*/

enum class Boss_State {
	NONE = 0,
	STARTUP,
	IDLE,
	IDLE_END,
	IDLE_RAGE,
	IDLE_RAGE_END,
	TRANSFORMING,
	TRANSFORMING_END,
	DEATH,

	SPIN_SHOOTBULLET,
	LASER_CHARGE,
	LASER_CHARGE_RAPID, // for now not used
	LASER_SHOOT,
};

class Boss : public IScript2
{
private:
// Logic Data - General
	int health, healthMax, healthHalf, healthQuart;
	double startUpTimer, idleTimer, idleDuration;

	int ammo, ammoMax;
	double bulletTimer, shootROF, bulletSpeed;
	float rotationspeed;

	double laserChargeTimer, laserChargeDuration,
		laserFlashTimer, laserFlashDuration,
		laserAliveTimer, laserAliveDuration;
	int laserRapidFireNumOfShots, rapidFireShotCount;
	double laserRapidChargeSpeedUp;


	int _state, _statePrev, _stateNext;
	bool _laserChargeStart, _laserFlashStart, _laserShootStart;
	bool _init, _transformStart, _healthHalfStart, _deathStart;

	GameObject* playerPtr, *subObj;
	int playerId;
	double _dt;

	// AnimNames for when calling particualr animations
	std::vector<std::string>::iterator _AnimChainItr;
	std::vector<std::string> _StartUp = { "","","" };
	std::vector<std::string> _Idle = { "","","" };
	std::vector<std::string> _IdleRage = { "","","" };
public:
	Boss();
	~Boss();
	Boss* Clone();

	void Init();
	void Update(double dt);

	void UpdateState();
	void RunState();
	
	void PlayAnimChain(std::vector<std::string>& in);
	bool PlayAnimChainNext(std::vector<std::string>& idleAnim, std::vector<std::string>::iterator animChainItr);

	void StartUp();
	void Idle();
	void IdleRage();
	void Death();
	void SpinAround();
	void ShootBullet();
	void LookAtPlayer();
	void LaserCharge(double speedUp = 1.0);
	void LaserShoot();
	void Transform();
	
	void OnCollision2DTrigger(Collider2D* other);

	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);
	void Inspect();
};

#endif
