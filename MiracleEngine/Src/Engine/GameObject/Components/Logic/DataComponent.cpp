#include "PrecompiledHeaders.h"



DataComponent::DataComponent() :
	parentLogic{ nullptr }
{}

DataComponent::~DataComponent() {}
std::string DataComponent::ComponentName() const
{return std::string("empty");}
void DataComponent::SerialiseComponent(Serialiser& document) {}
void DataComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
void DataComponent::Inspect() {
	std::cout << "DataComponent::Inspect() \n";
}

std::string DataHealth::ComponentName() const { return std::string("Data_Health"); }
void DataHealth::SerialiseComponent(Serialiser& document) {}
void DataHealth::DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
void DataHealth::Inspect() {}

std::string DataAmmo::ComponentName() const { return std::string("Data_Health"); }
void DataAmmo::SerialiseComponent(Serialiser& document) {}
void DataAmmo::DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
void DataAmmo::Inspect() {}