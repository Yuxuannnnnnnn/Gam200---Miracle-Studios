#pragma once


// struct for handling window size
class ScreenSize final {

private:
	int _ResX, _ResY;
	bool _Fullscreen;

public:
	ScreenSize();

	~ScreenSize() = default;

	ScreenSize(const ScreenSize&) = delete;
	ScreenSize& operator=(const ScreenSize&) = delete;
	/**
	\brief Read start up info for application
			Will get following values:
			- Resolution (X, Y)
			- Fullscreen On/Off
	*/
	void FileRead_StartUp();

	int GetResX() const;
	int GetResY() const;
};

