///////////////////////////////////////////////////////////////////////////////////////
///
///	\file WindowsSystem.h
///  This is a system that wraps everything related to the Windows OS. If you wished,
///  you could have a different system for each OS your game supported.
///	
///	Authors:  Benjamin Ellinger, Chris Peters
///	Copyright 2010, Digipen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////////////
#pragma once //Makes sure this header is only included once

#include "Engine.h"

namespace Framework
{
	///Basic manager for windows. Implements the windows message pump and
	///broadcasts user input messages to all the systems.
	class WindowsSystem : public ISystem
	{
	public:
		WindowsSystem(const char* windowTitle, int ClientWidth, int ClientHeight);	//The constructor
		~WindowsSystem();															//The destructor

		void ActivateWindow();								//Activate the game window so it is actually visible
		virtual void Update(float dt);						//Update the system every frame
		virtual std::string GetName() {return "Windows";}	//Get the string name of the system

		HWND hWnd;											//The handle to the game window
		HINSTANCE hInstance;								//The handle to the instance
		POINTS MousePosition;
	};

	///Message signaling that a key is pressed.
	class MessageCharacterKey : public Message
	{
	public:
		MessageCharacterKey() : Message(Mid::CharacterKey) {};	
		int character;
	};

	///Message signaling that a mouse button state has changed.
	class MouseButton: public Message
	{
	public:
		enum MouseButtonIndexId
		{
			LeftMouse,
			RightMouse
		};
		MouseButton(MouseButtonIndexId button,bool state,Vec2 position) 
			: Message(Mid::MouseButton) ,  MouseButtonIndex(button) , ButtonIsPressed(state), MousePosition(position) {};

		MouseButtonIndexId MouseButtonIndex;
		bool ButtonIsPressed;
		Vec2 MousePosition;
	};

	///Message signaling that the mouse has moved.
	class MouseMove: public Message
	{
	public:
		MouseMove(Vec2 position) : Message(Mid::MouseMove) , MousePosition(position) {};	
		Vec2 MousePosition;
	};

	///Message signaling that a file was dropped onto the window.
	class FileDrop: public Message
	{
	public:
		FileDrop(std::string filename) : Message(Mid::FileDrop) , FileName(filename) {};	
		std::string FileName;
	};

	bool IsShiftHeld();
	bool IsCtrlHeld();
	bool IsAltHeld();
	bool IsUpHeld();
	bool IsDownHeld();
	bool IsLeftHeld();
	bool IsRightHeld();

	extern WindowsSystem* WINDOWSSYSTEM;
}