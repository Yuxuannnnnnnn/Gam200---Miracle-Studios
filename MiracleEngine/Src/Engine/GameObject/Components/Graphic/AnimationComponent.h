#pragma once

#include "SystemAnimation/Animation.h"
#include <map>
#include <string>
#include "Tools/Resource/ResourceSystem.h"
#include "Editor/ImguiFunctions.h"




/* 
	animationcomponent: we want have each seperate time delay for each individual animation, e.g. run, walk, idle

	each seperate spritesheet have its own time delay and max number of frames

	each update loop, animation system will call UpdateTimeDelay, pass in dt.
*/


class AnimationComponent: public IComponent
{
	// let designer choose timedelay for individual anim

	// _timeDelay = the time delay for specific anim, can be diff for run and walk

	// _currentTimeDelay decrease every loop 

	// maxFrame = max number of frame for specific anim, can be diff for run and walk


private:



//For editor Variables

	typedef float timeDelay;
	typedef std::string AnimationName;
	typedef std::string AnimationFile;

	std::map<AnimationName, AnimationFile> animationFileNameList;
	std::map<AnimationName, timeDelay> _animations;	//Each animation has its own timedelay

	std::string _startingAnim;	//AnimationName

	// let me know if got problem if vector change to map, i, e animation doesnt run.
	//std::vector<std::string> _animations;

//For Smart component Variables
	bool _playAtCreation;
	bool _loop;

	bool _playOnce; 
	bool _animationPlaying;
	
	float _timeDelay;	//Factor to change from one frame to another frame
	float _currentTimeDelay; //Use to countdown the timeDelay of the specific frame
	int _currFrame;
	int _maxFrame;	//cap of the current animation



	std::string _currentAnim; //Logic Animation script will only touch and change this variable //Json FileName

	std::string _currenAnimName;
	Animation* _currAnimationResource;	//only for optimisation

public:
	//float _timeDelay;	//remove

	void SetAnimationPlaying(bool set);

	//Updates currentTimeDelay, as delay reaches 0, change to another frame
	//When reaches max frame, frame start from 0 again.
	void UpdateTimeDelay(float dt);


	// get current playing animation
	std::string& GetCurrAnim();

	inline int GetCurrFrame() { return _currFrame; }


	Texture2D* GetCurrentTexture();

	Animation* GetAnimationResource();

	int GetCurrentFrame();



	int GetMaxFrame();
	float GetTimeDelay();
	void SetTimeDelay(float time);

	bool IsPlayingOnce();
	void SetPlayingOnce(bool);
	// Starting get from seriailize file, i.e starting anim delay and maxframe. when current changed, update this fn
// called when switching animation from idle to run, etc
	//void GetTimeDelayFromCurrentAnim(/* take in args if needed */)
	//{
	//	// TODO:: get timedelay and max frame from current anim serialized file
	//	// _timeDelay = ...
	//	_currentTimeDelay = _timeDelay;
	//	_currFrame = _maxFrame;
	//}


//Only for Logic Animation script--------------------------------------
	void SetCurrentAnim(const std::string& AniamtionType);
	void SetCurrentAnimOnce(const std::string& AnimationType);
	bool IsAnimationPlaying();


//---------------------------------------------------------------------


private:
	void SetStartFrame();
	void SetMaxFrame(int maxFrame);
	void ResetCurrTimeDelay();
	void SetTimeDelay(std::string AnimationName);
	void setCurrentAnimation(std::string AnimationName);
	void SetAnimationResource();

public:
	virtual void Inspect() override;

	const std::map<AnimationName, AnimationFile>& GetAnimationDataFileList() const;
	
	AnimationComponent(GameObject* parent = nullptr, size_t uId = 0, IComponent* component = nullptr);

	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	std::string ComponentName() const override;

	void Init() override;
	virtual void LoadResource() override;

//Editor or Serialisation
	//void AddAnimation(std::string animationType)
	//{
	//	_animations.insert(std::pair <AnimationName, timeDelay >(animation, delay));
	//	animationFileNameList.insert(std::pair < std::string, timeDelay >(animation, delay));
	//}

	//~AnimationComponent();

	AnimationComponent* CloneComponent() { return new AnimationComponent(*this); }
};













