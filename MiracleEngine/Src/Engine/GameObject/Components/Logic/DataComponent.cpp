#include "PrecompiledHeaders.h"

DataComponent::DataComponent() { std::cout << "DEBUG:\t Ctor: DataComponent. \n"; }
DataComponent::~DataComponent() {}
std::string DataComponent::ComponentName() const { return std::string("Data_Health"); }
void DataComponent::SerialiseComponent(Serialiser& document) {}
void DataComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
void DataComponent::Inspect() {}

DataMoveComponent::DataMoveComponent() { std::cout << "DEBUG:\t Ctor: DataMove. \n"; }
DataMoveComponent::~DataMoveComponent() {}
std::string DataMoveComponent::ComponentName() const { return std::string("Data_Health"); }
void DataMoveComponent::SerialiseComponent(Serialiser& document) {}
void DataMoveComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
void DataMoveComponent::Inspect() {}

DataHealth::DataHealth() { std::cout << "DEBUG:\t Ctor: DataHealth. \n"; }
DataHealth::~DataHealth() {}
std::string DataHealth::ComponentName() const { return std::string("Data_Health"); }
void DataHealth::SerialiseComponent(Serialiser& document) {}
void DataHealth::DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
void DataHealth::Inspect() {}