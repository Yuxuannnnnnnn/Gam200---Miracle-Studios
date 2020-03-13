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
// boss will need a slow rotate to player, NOT snap to face player

Do above half heath shoot laser, then under half spin shoot.
	if ok then try 100-75 normal laser, 75-50||40 rapid shot, remaining spint shoot with critical health anims
	
Init()

//SND:: Plays the background music for the game --> MusicBGM1
	Boss_inactive_to_active_sprite --> Boss_Idle_sprite 
When start laser charge
SND:: Plays the charging sound effect --> Charging
	Boss_Idle_sprite --> Boss_Laser_Charge_up_sprite
Once laser charged & now shoot laser
	Boss_Laser_Charge_up_sprite --> freeze last frame of prev anim
		+ Laser_Blast_Sprite (actual laser)
SND:: Plays the laser shot sound effect --> LaserShot
	Boss_Laser_Charge_up_sprite --> Laser_Blasting_small(body single frame) OR freeze to last frame of prev anim
		+ Laser_Blast_Sprite (actual laser)
Once shoot laser finish & return to IDLE
	Laser_Blasting_small(body single frame) --> Boss_Laser_after_shoot_transform_back_sprite --> Boss_Idle_sprite
On HP < 50, change from IDLE to IDLE_RAGE
//SND:: Plays the sound effect for shooting bullets --> SingleShot
	Boss_Idle_sprite --> Boss_Transform_into_rage_sprite --> Boss_Rage_idle_sprite
When want to shoot bullet
	Boss_Rage_idle_sprite --> Boss_rage_transform_to_shoot_style_sprite --> Boss_Shoot_style_sprite OR Boss_Shoot_style_low_HP_sprite
	While shooting, continue with the last anim from above
Once shooting end
	Boss_Shoot_style_sprite OR Boss_Shoot_style_low_HP_sprite --> Boss_shoot_style_transform_to_rage_sprite -->
		Boss_Rage_idle_sprite OR Boss_Rage_idle_low_HP_sprite

On DEATH depending on which mode its in, use the right death anim


start up anim 2 not showing right one
shoot idle not being played
transform anims not playing

*/

enum class Boss_State {
	NONE = 0,
	DEATH,
	STARTUP,
	IDLE, //3
	IDLE_END,
	LASER_CHARGE,//5
	LASER_SHOOT, // rmb this one got anim disable
	LASER_SHOOT_END,
	IDLE_RAGE, //8
	IDLE_RAGE_END,
	TRANSFORMING, //10
	TRANSFORMING_END,
	SPIN_SHOOTBULLET, //12
	SPIN_SHOOTBULLET_END,


	LASER_CHARGE_RAPID, // for now not used
	COUNT
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
	bool _init, _healthHalfStart, _healthHalfEnd, _deathStart,
		_transforming;

	GameObject* playerPtr, *subObj;
	int playerId;
	double _dt;

	// AnimNames for when calling particualr animations
	std::vector<std::string>::iterator _CurrAnimChainItr;
	std::vector<std::string> _CurrAnimChain, _NextAnimChain;
	// anims are at end of this class

public:
	Boss();
	~Boss();
	Boss* Clone();

	void Init();
	void Update(double dt);

	void UpdateState();
	void RunState();
	
	bool PlayAnimChain(std::vector<std::string> animChain, bool overwrite = false);
	// need as ShaoX for the last frame of each sheet.
	// need have an array of lastFrameSprites
	// whenever PlayAnimChain change to next in chain, need set the next lastFrameSprites
	// ((GraphicComponent*)GetParentPtr()->GetComponent(ComponentId::CT_Graphic))->SetFileName("Spawner_Platform_unlit.png");

	void StartUp();
	void Idle();
	void IdleRage();
	void Death();
	void SpinShoot();
	void SpinAround();
	void ShootBullet();
	void TrackAndChargeLaser();
	void LookAtPlayer();
	void LaserCharge(double speedUp = 1.0);
	void LaserShoot();
	void Transform();
	void TransformNextAnim();
	
	void OnCollision2DTrigger(Collider2D* other);

	void SerialiseComponent(Serialiser& document);
	void DeSerialiseComponent(DeSerialiser& prototypeDoc);
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);
	void Inspect();

private:
	std::vector<std::string> _StartUp = { // Boss_inactive_to_active_sprite
	"StartUp1",
	"StartUp2" };
	std::vector<std::string> _Idle = { // Boss_Idle_sprite
		"Idle1",
		"Idle2",
		"Idle3" };
	std::vector<std::string> _IdleRage = { // Boss_Rage_idle_sprite
		"IdleRage1",
		"IdleRage2",
		"IdleRage3" };
	std::vector<std::string> _IdleRageLow = { // Boss_Rage_idle_low_HP_sprite
		"IdleRage1Low",
		"IdleRage2Low",
		"IdleRage3Low" };
	std::vector<std::string> _LaserCharge = { // Boss_Laser_Charge_up_sprite
		"Laser1",
		"Laser2",
		"Laser3",
		"Laser4",
		"Laser5" };
	std::vector<std::string> _TransformLaserToIdle = { // Boss_Laser_after_shoot_transform_back_sprite
		"TransformLaserToIdle1",
		"TransformLaserToIdle2",
		"TransformLaserToIdle3" };
	std::vector<std::string> _TransformIdleToIdleRage = { // Boss_Transform_into_rage_sprite2
		"TransformIdleToIdleRage1",
		"TransformIdleToIdleRage2",
		"TransformIdleToIdleRage3" };
	std::vector<std::string> _TransformIdleRageToShoot = { // Boss_rage_transform_to_shoot_style_sprite 
		"TransformIdleRageToShooting1",
		"TransformIdleRageToShooting2"
	};
	std::vector<std::string> _TransformShootToIdleRage = { // Boss_shoot_style_transform_to_rage_sprite 
		"TransformShootingToIdleRage1",
		"TransformShootingToIdleRage2"
	};
	std::vector<std::string> _Shooting = { // Boss_Shoot_style_sprite
		"Shooting" };
	std::vector<std::string> _ShootingLowHP = { // Boss_Shoot_style_low_HP_sprite
		"ShootingLowHP1",
		"ShootingLowHP2" };
	std::vector<std::string> _DeathIdle = { // Boss_Rage_idle_death_sprite
		"DeathIdle1",
		"DeathIdle2",
		"DeathIdle3",
		"DeathIdle4",
		"DeathIdle5",
		"DeathIdle6",
		"DeathIdle7",
		"DeathIdle8" };
	std::vector<std::string> _DeathShooting = { // Boss_Shoot_style_Death_sprite
		"DeathShooting1",
		"DeathShooting2",
		"DeathShooting3",
		"DeathShooting4",
		"DeathShooting5",
		"DeathShooting6" };
};

#endif
