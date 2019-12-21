#include "PrecompiledHeaders.h"



DataComponent::DataComponent() :
	parentLogic{ nullptr }
{}

DataComponent::~DataComponent() {}

void DataComponent::SerialiseComponent(Serialiser& document) {}
void DataComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
void DataComponent::Inspect() {}
