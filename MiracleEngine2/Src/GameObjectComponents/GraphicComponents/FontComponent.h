#pragma once





class FontComponent : public IComponentSystem
{
public:
	void SetFontID(int num)
	{
		_fontID = num;
	}


	void SerialiseComponent(Serialiser& document) override;

	std::string ComponentName() const override
	{
		return "Font Component";
	}

	virtual void Inspect() override
	{
		
	}


private:
	int _fontID;
};