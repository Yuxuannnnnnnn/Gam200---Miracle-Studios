#include "PrecompiledHeaders.h"

DataHealth::DataHealth() : parentLogic{ nullptr } { std::cout << "Ctor: DataHealth. \n"; }
DataHealth::~DataHealth() {}
std::string DataHealth::ComponentName() const { return std::string("Data_Health"); }
void DataHealth::SerialiseComponent(Serialiser& document) {}
void DataHealth::DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
void DataHealth::Inspect() {}

DataAmmo::DataAmmo() : parentLogic{ nullptr } { std::cout << "Ctor: DataAmmo. \n"; }
DataAmmo::~DataAmmo() {}
std::string DataAmmo::ComponentName() const { return std::string("DataAmmo"); }
void DataAmmo::SerialiseComponent(Serialiser& document) {}
void DataAmmo::DeSerialiseComponent(DeSerialiser& prototypeDoc) {}
void DataAmmo::Inspect() {}