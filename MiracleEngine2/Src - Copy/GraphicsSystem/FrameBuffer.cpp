#include "PrecompiledHeaders.h"
#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &_id);

}

FrameBuffer::~FrameBuffer()
{
}

void FrameBuffer::Select() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _id);
}

void FrameBuffer::UnSelect() const
{
}
