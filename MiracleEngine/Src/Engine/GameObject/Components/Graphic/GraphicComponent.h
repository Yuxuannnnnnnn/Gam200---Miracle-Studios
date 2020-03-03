#pragma once
#include "../../IComponent.h"
#include "GameObject/IAllocator.h"
#include "Tools/Resource/ResourceSystem.h"

#include "Editor/ImguiFunctions.h"


enum class TypeIdGraphic {
	NONE = 0,

};

class GraphicComponent : public IComponent
{
private:

	std::string _fileName;      
	std::string _shader;
	//RenderLayer _renderlayer; Not Used anymore because Z value is computed in Transformcomponent
	
	// has alpha from PNG
	bool _hasAlpha;

	// has alpha adjustable in programming
	bool _hasAdjustableAlpha; //when the button is ticked, _alphaVal is taken into account
	float _alphaVal;	//alpha value is between 0 to 1

	bool _isFadingOut; //if box is checked, the object will slowly fade out
	bool _isFlickering;//if box is checked, the objecy will randomly flicker on and off

	int _layer;



	float u0, v0;
	float u1, v1;

public:

	void Init();

	inline bool HasAlpha() {return _hasAlpha;}
	inline bool HasAdjustableAlpha(){return _hasAdjustableAlpha;}
	inline bool IsFadingOut(){return _isFadingOut;}
	inline bool IsFlickering(){return _isFlickering;}

	void EnableFadingOut(bool isFading);
	void EnableAdjustableAlpha(bool isAlpha);
	void EnableAlpha(bool isAlpha);
	void EnableFlickering(bool isAlpha);

	void SetAlpha(float alphaValue);
	float GetAlpha();
	unsigned int GetTextureID() const;               // base on asset file name, get the textureID on OpenGL for imgui
	
	const std::string& GetFileName() const;
	void SetFileName(const std::string& filename);


	const std::string& GetShaderType();


	std::string ComponentName() const override;
	void SerialiseComponent(Serialiser& document) override;
	void DeSerialiseComponent(DeSerialiser& prototypeDoc) override;
	void DeSerialiseComponent(rapidjson::Value& prototypeDoc, rapidjson::MemoryPoolAllocator<>& allocator);
	void DeserialiseComponentSceneFile(IComponent* protoCom, rapidjson::Value& value, rapidjson::MemoryPoolAllocator<>& allocator);

	virtual void Inspect() override;
	


	//Constructor
	GraphicComponent();
	virtual ~GraphicComponent();
	GraphicComponent(const GraphicComponent& rhs) = default;
	GraphicComponent& operator=(const GraphicComponent& rhs) = default;


	void RenderLayerResolver();

	int GetTextureState();
	void SetTextureState(int state);

	int GetRenderLayer();

	void SetRenderLayer(int state);


	unsigned& GetTypeId();

	GraphicComponent* CloneComponent() { return new GraphicComponent(*this); }
};












