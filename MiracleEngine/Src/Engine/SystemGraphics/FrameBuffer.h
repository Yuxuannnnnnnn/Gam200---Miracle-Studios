#pragma once

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void Select() const;
	void UnSelect() const;
private:

	GLuint _id;

};