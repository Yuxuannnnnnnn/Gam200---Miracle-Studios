#include "PrecompiledHeaders.h"

DataComponent::DataComponent() { std::cout << "DEBUG:\t Ctor: DataComponent. \n"; }
DataComponent::~DataComponent() {}
std::string DataComponent::ComponentName() const { return std::string("Data_Health"); }
void DataComponent::SerialiseComponent(Serialiser& document) {}
void DataComponent::DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
void DataComponent::Inspect() {}

DataMove::DataMove() { std::cout << "DEBUG:\t Ctor: DataMove. \n"; }
DataMove::~DataMove() {}
std::string DataMove::ComponentName() const { return std::string("Data_Health"); }
void DataMove::SerialiseComponent(Serialiser& document) {}
void DataMove::DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
void DataMove::Inspect() {}

DataHealth::DataHealth() { std::cout << "DEBUG:\t Ctor: DataHealth. \n"; }
DataHealth::~DataHealth() {}
std::string DataHealth::ComponentName() const { return std::string("Data_Health"); }
void DataHealth::SerialiseComponent(Serialiser& document) {}
void DataHealth::DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
void DataHealth::Inspect() {}