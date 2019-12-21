#include "Animation.h"
#include "PrecompiledHeaders.h"



Animation::Animation()
{
	/*frame.push_back(new Frame(1.0f / 12, 0.0f, 2.0f / 12, 1.0f));
	frame.push_back(new Frame(2.0f / 12, 0.0f, 3.0f / 12, 1.0f));
	frame.push_back(new Frame(3.0f / 12, 0.0f, 4.0f / 12, 1.0f));
	frame.push_back(new Frame(4.0f / 12, 0.0f, 5.0f / 12, 1.0f));
	frame.push_back(new Frame(5.0f / 12, 0.0f, 6.0f / 12, 1.0f));
	frame.push_back(new Frame(6.0f / 12, 0.0f, 7.0f / 12, 1.0f));
	frame.push_back(new Frame(7.0f / 12, 0.0f, 8.0f / 12, 1.0f));
	frame.push_back(new Frame(8.0f / 12, 0.0f, 9.0f / 12, 1.0f));*/
}

void Animation::Select()
{
	(*frame)[_currentFrame]->Select();
}

bool Animation::load(std::string path)
{
	frame = new std::vector<Frame*>();

	Serialiser file(path);

	size_t NumOfFrames = file["NoofFrames"].GetInt();


	/*frame->push_back(new Frame(1.0f / 12, 0.0f, 2.0f / 12, 1.0f));
	frame->push_back(new Frame(2.0f / 12, 0.0f, 3.0f / 12, 1.0f));
	frame->push_back(new Frame(3.0f / 12, 0.0f, 4.0f / 12, 1.0f));
	frame->push_back(new Frame(4.0f / 12, 0.0f, 5.0f / 12, 1.0f));
	frame->push_back(new Frame(5.0f / 12, 0.0f, 6.0f / 12, 1.0f));
	frame->push_back(new Frame(6.0f / 12, 0.0f, 7.0f / 12, 1.0f));
	frame->push_back(new Frame(7.0f / 12, 0.0f, 8.0f / 12, 1.0f));
	frame->push_back(new Frame(8.0f / 12, 0.0f, 9.0f / 12, 1.0f));
*/

	Frame* ptr = nullptr;
	float uv[4];	//buffer to contain the uv values temporary

	for (int i = 1; i <= NumOfFrames; i++)
	{
		// Array of U0, V0, U1, V1 - Array of 4 floats
		for (int a = 0; a < 4; a++)
		{
			uv[a] = file[std::to_string(i).c_str()][a].GetFloat();
		}

		ptr = new Frame(uv[0], uv[1], uv[2], uv[3]);

		(*frame).push_back(ptr);
	}

	return true;
}

void Animation::unload()
{
	for (auto it : (*frame))
	{
		delete it;
	}

	(*frame).clear();

	delete frame;
}