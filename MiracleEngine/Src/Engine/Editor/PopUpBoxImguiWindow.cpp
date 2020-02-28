#include "PrecompiledHeaders.h"
#include "PopUpBoxImguiWindow.h"



PopUpBoxImguiWindow::PopUpBoxImguiWindow(bool open, ImGuiWindowFlags flags)
	:IBaseImguiWindow("PopUpBox", 400, 200, 500, 200, open, flags, ImGuiCond_Once), _type{nullptr}
{
}

void PopUpBoxImguiWindow::SaveSceneWarning::Warn(PopUpBoxImguiWindow* box)
{
	//"There are some changes made to the Level. "
	ImGui::Text("Do you want to save this Level before moving on to another level?");
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	if (ImGui::Button("Yes"))
	{
		if (MyFactory.GetCurrentScene().empty())
		{
			MyFactory.WindowsDialogSaveLevel();
		}
		else
		{
			MyFactory.De_SerialiseLevel(MyResourceSystem.GeScenePath(MyFactory.GetCurrentScene()));
		}

		box->SetWindowFalse();
		MyFactory.ChangeScene(changeToScene);

		//Pop up box that mentions that scene is saved.
	}
	ImGui::Indent(500);
	ImGui::SameLine();

	if (ImGui::Button("No"))
	{
		box->SetWindowFalse();
		MyFactory.ChangeScene(changeToScene);
	}

	ImGui::Indent(500);
	ImGui::SameLine();
	if (ImGui::Button("Cancel"))
	{
		box->SetWindowFalse();
	}
}

void PopUpBoxImguiWindow::SaveSceneWarning::check(PopUpBoxImguiWindow* box)
{
	//Check Level For Differences
	//if (MyFactory.GetCurrentScene().empty())
		box->SetWindowTrue();

}

void PopUpBoxImguiWindow::RefreshSceneWarning::Warn(PopUpBoxImguiWindow * box)
{
	//"There are some changes made to the Level. "
	ImGui::Text("Do you want to save this Level before refreshing the level?");
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	if (ImGui::Button("Yes"))
	{
		if (MyFactory.GetCurrentScene().empty())
		{
			MyFactory.WindowsDialogSaveLevel();

		}
		else
		{
			MyFactory.De_SerialiseLevel(MyResourceSystem.GeScenePath(MyFactory.GetCurrentScene()));
		}

		box->SetWindowFalse();
		MyFactory.ChangeScene("Restart"); //Refresh the scene

		//Pop up box that mentions that scene is saved.
	}
	ImGui::Indent(500);
	ImGui::SameLine();

	if (ImGui::Button("No"))
	{
		box->SetWindowFalse();
		MyFactory.ChangeScene("Restart");
	}

	ImGui::Indent(500);
	ImGui::SameLine();
	if (ImGui::Button("Cancel"))
	{
		box->SetWindowFalse();
	}

}

void PopUpBoxImguiWindow::RefreshSceneWarning::check(PopUpBoxImguiWindow * box)
{
	box->SetWindowTrue();
}
