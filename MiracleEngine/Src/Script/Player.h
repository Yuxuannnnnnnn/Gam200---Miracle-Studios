#pragma once
#include "GameObject/Components/Logic/IScript2.h"
enum class WeaponId {
	NONE = 0,
	PISTOL = 1,
	SHOTGUN = 2,
	RPG = 3,
};

class Player : public IScript2
{
private:
// Logic Data - General
	bool _god;
	GameObject* _camera;
	int _health, _healthMax;
	int _progress, _progressMax;
	int _progressLevel;
	double _timerGodSwitch, _timerGodSwitchDelay;
// Logic Data - Shield
	bool _shieldOn;
	double _timerShield, _timerShieldDuration;
	double _timerShieldActivateCooldown, _timerShieldCooldown;
// Logic Data - Weapons
	double _timerSwitch, _timerSwitchDelay;
	int _weaponActive;
	int _ammoRpg;
	int _ammoTurret, _maxAmmoTurret;
	int _ammoWall;
	double _timerTurretActivateCooldown, _timerTurretCooldown;
	double _timerShoot;
	double _timerDeploy;
	double _fireratePistol;		// 1.0d == 1sec
	double _firerateShotgun;	// 1sec = d * roundPerSec
	double _firerateRPG;		// d = 1/rps
	double _firerateTurret;
	double _firerateWall;
// Logic Data - Progression
	double _timerProg, _timerProgCooldown;
// Logic Data - Animation
	bool _moving;
	int _animState, _animStatePrev; // 1==StartMove, 2==StartIdle, 3==StartShoot, etc
// Logic - DelayDeathForAnimation
	double _timerDeath, _animTime;
	bool _redTint, _justHit;
	double _dt, hitTintTimer, hitTintDuration;
	double _laserHitTimer, _laserHitDelay;

	GameObject* _healingSparkle, *_hitSpark;

	TransformComponent* _muzzleTransfrom;
	AnimationComponent* _muzzleAnimation;

	TransformComponent* _objTransfrom;

	IScript2* _shieldSkill;
	IScript2* _hitEffect;
	IScript2* _healthBar;
	IScript2* _pauseMenu;
	IScript2* _weaponTab;
public:
	void SerialiseComponent(Serialiser& document) ;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) ;

	virtual void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);

	virtual void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	void Inspect() ;

	Player();

	Player* Clone();

	void Init();
	void LoadResource();
	void Update(double dt);

	void UpdateShield(double dt);
	void WeaponSwitch();
	void WeaponShoot();
	void WeaponShoot_Pistol();
	void WeaponShoot_Shotgun();
	void WeaponShoot_RPG();
	void UpdateCamera();
	void UpdateInput(double dt);
	void UpdateUI();

	int GetHealth();
	void SetHealth(int val);
	int GetHealthMax();
	int GetProgress();
	void SetProgress(int val);
	int GetProgressMax();
	void ProgressIncement(int in = 1);

	int GetProgressLevel() const;

	void DamagePlayer(int dmg = 1);
	void LaserPlayer();
	void OnHit();

	void OnTrigger2DEnter(Collider2D* other);
	void OnCollision2DTrigger(Collider2D* other);
	void OnTrigger2DStay(Collider2D* other);
};