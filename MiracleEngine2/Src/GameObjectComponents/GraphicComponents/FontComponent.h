#pragma once


#include <string>


class FontComponent : public IComponentSystem
{
public:
	void SerialiseComponent(Serialiser& document) override;
	
	void SetFontID(int num);



	std::string ComponentName() const override;

	std::string& GetFontString();


	virtual void Inspect() override;


private:
	int _fontID;
	std::string _fontString;
};