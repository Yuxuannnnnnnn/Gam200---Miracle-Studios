#pragma once


// struct for handling window size
class ScreenSize final {

public:
	int _ResX, _ResY;
	bool _Fullscreen;

	ScreenSize(): _ResX{ 0 }, _ResY{ 0 }, _Fullscreen{ false }
	{}

	~ScreenSize() {}

	ScreenSize(const ScreenSize&) = delete;
	ScreenSize& operator=(const ScreenSize&) = delete;
	/**
	\brief Read start up info for application
			Will get following values:
			- Resolution (X, Y)
			- Fullscreen On/Off
	*/
	void FileRead_StartUp();
};

