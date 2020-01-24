#include "PrecompiledHeaders.h"
#include "IMouseHandler.h"


IMouseHandler::IMouseHandler() : _input{&MyInputSystem}
{

}

const Vec3& IMouseHandler::GetMousePos() const
{
	return _input->GetMouseScreenPos();
}