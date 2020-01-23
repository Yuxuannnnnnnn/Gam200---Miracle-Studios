#pragma once





class PopUpBoxImguiWindow : public IBaseImguiWindow
{

public:

	class Warning
	{
	public:
		virtual void Warn(PopUpBoxImguiWindow* box) = 0;
		virtual void check(PopUpBoxImguiWindow* box) = 0;
	};

	class SaveSceneWarning : public Warning
	{
		//static std::string Name;

		std::string changeToScene;
	public:

		SaveSceneWarning(const std::string& scene)
		{
			changeToScene = scene;
		}

		void Warn(PopUpBoxImguiWindow* box) override;

		void check(PopUpBoxImguiWindow* box) override;

	};
	//std::string SaveSceneWarning::Name{ "SaveSceneWarning" };


private:
	Warning* _type;

public:

	PopUpBoxImguiWindow(bool open = false,	//Set the settings for the imgui windows
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse);

	void Update() override
	{
		_type->Warn(this);
	}

	template<typename type>
	void SetPopUpBox(type* Type)
	{	
		if (_type)
			delete _type;

		_type = Type;
		_type->check(this);
	}

	~PopUpBoxImguiWindow()
	{
		if (_type)
			delete _type;
	}


};




