#include "PrecompiledHeaders.h"
#include "AnimationImguiWindow.h"

void AnimationImguiWindow::Update()
{
	UpdateTimeDelay(MyFrameRateController.GetFrameTime() / oneSecNs);

	//Get Animation Texture from Animation Resource
	//Get u0,v0, u1, v1 from frame in Animation Resource

	//float width = _currTexture->GetWidth();
	//float height = _currTexture->GetHeight();
	//
	//float scaleW = width / 400.0f;
	//float scaleH = height / 400.0f;
	//
	//float scale;
	//
	//if (scaleW > scaleH)
	//{
	//	scale = scaleW;
	//}
	//else
	//{
	//	scale = scaleH;
	//}

	//ImGui::Image((void*)(intptr_t)(_currTexture)->GetTextureID(), ImVec2(width / scale, height / scale),
		//ImVec2(0, 1), ImVec2(1, 0), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 0.5f));	
	ImGui::Image((void*)(intptr_t)(_currTexture)->GetTextureID(), ImVec2(200, 200),
		ImVec2(u0, v1), ImVec2(u1, v0), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
}
