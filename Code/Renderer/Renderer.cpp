#include "Renderer.h"
#include "ImGui/imgui.h"
#include "Make Politics/CreatePoli.h"
#include "Political/PreferringPolitical.h"
#include "County/CountyDetails.h"

#include "string"
#include <format>


namespace Renderer
{
	CountyDetails::County* CP;
	
	void RenderClass::Render()
	{
		if (CP == nullptr)
		{
			CP = new CountyDetails::County();
			CP->ppl->LevelOfTech = rand() % 100 + 1;
			CP->ppl->LevelOfWealth = rand() % 100 + 1;
		}

		if (CP->IsPlayerWin)
		{
			ImGui::Begin("Player Win");
			ImGui::Separator();
			ImGui::Text("You are win the game");
			ImGui::Separator();
			ImGui::End();
			printf("Player win");
		}

		// Make a strings to show stats of county
		std::string Co = std::format("County : {}",CP->NameOfCounty);
		std::string Po = std::format("Population : {}",CP->ppl->AmmountPopulations);
		std::string Bc = std::format("Budget County : {}",CP->BudgetCounty);
		std::string LT = std::format("Level of tech : {}", CP->ppl->LevelOfTech);
		std::string LW = std::format("level of wealth : {}", CP->ppl->LevelOfWealth);
		std::string Pp = std::format("Player Political Party Popularity : {}", CP->PlayerParty->Popularity);

		ImGui::Begin("County Main Windows");

		ImGui::Text(Co.c_str());

		ImGui::Separator();
		ImGui::Text(Po.c_str());

		ImGui::Separator();
		ImGui::Text(Bc.c_str());
		ImGui::Separator();
		ImGui::Text(LT.c_str());
		ImGui::Separator();
		ImGui::Text(LW.c_str());
		ImGui::Separator();
		ImGui::Text(Pp.c_str());
		ImGui::Separator();

		if (ImGui::Button("Open Creator of Laws"))
			OpenMakePolitics = true;


		if (ImGui::Button("Open Propaganda Windows"))
			OpenPropaganda = true;

		ImGui::Separator();
		std::string RE = std::format("Raming Turns to next elections : {}", CP->RemingTiemToElectons);
		ImGui::Text(RE.c_str());
		ImGui::Separator();

		if (OpenMakePolitics)
		{
			RenderMakePolitics();
		}

		if (OpenPropaganda)
		{
			RenderPropagandaWindows();
		}

		if (ImGui::Button("End Turn"))
		{
			CP->NextTurn();
		}
		ImGui::End();
	}

	char NameOfLaw[100];
	char BufforNameOfLaw[100];

	int TaxRate = 0;
	int SocialRate = 0;
	int LeftSlider;
	int RightSlider;
	int bp = 0;

	bool IsTax = false;
	bool IsGive = false;
	bool IsShow = false;

	PerPolitical::PerferringPoli Poli;
	/// <summary>
	/// Render windows to make politics 
	/// </summary>
	void RenderClass::RenderMakePolitics()
	{
		ImGui::Begin("Caeatr");

		ImGui::Separator();

		ImGui::InputText("Name of Law", NameOfLaw, 100);

		ImGui::SliderInt("Ecomic Level", &LeftSlider, -100, 100);
		ImGui::SliderInt("Social Level", &RightSlider, -100, 100);

		ImGui::Separator();

		if (!IsTax)
		{
			ImGui::Checkbox("Social Law", &IsGive);
		}

		if (!IsGive)
		{
			ImGui::Checkbox("Tax Law", &IsTax);
		}

		if (IsTax)
		{
			ImGui::SliderInt("Tax Rate", &TaxRate, 5, 100);
			ImGui::Text("Set Tax Rate in percent");
			SocialRate = 0;
		}

		if (IsGive)
		{
			ImGui::SliderInt("Social Rate", &SocialRate, 5, 100);
			ImGui::Text("Set Social Rate in percent");
			TaxRate = 0;
		}
		
		if (ImGui::Button("Make Law") && NameOfLaw[0] != *"")
		{
			// Make a law and add vector
			PoliticalMake::Law law(NameOfLaw, &LeftSlider, &RightSlider, &TaxRate, &SocialRate, &IsTax, &IsGive);
			Poli.GetLaw(law,CP->SetPopulation());
			CP->GetLaw(law);

			SocialRate = 0;
			TaxRate = 0;

			IsShow = true;
		}

		if (ImGui::Button("Close Creater of Rules"))
			OpenMakePolitics = false;

		if (IsShow)
		{
			ImGui::Separator();
			std::string Op = std::format("Overall Popularity of this law {0} is {1}", Poli.GetName(), Poli.GetPopularityOverall());
			ImGui::Text(Op.c_str());
		}
		ImGui::End();
	}
	char ProStatus = 'N';
	/// <summary>
	/// Progpadgadna Render 
	/// </summary>
	void RenderClass::RenderPropagandaWindows()
	{
		auto cpd = CP->BudgetCounty / 2;
		ImGui::Begin("Propaganda Windows");

		auto p = std::format("Propaganda : {}",CP->ppl->PropagandaStrength);
		ImGui::Text(p.c_str());
		ImGui::SliderInt("Budget to give propaganda program",&bp,0,cpd);
		std::string Status;

		if (ImGui::Button("Add budget and start propagada"))
		{
			// Start Propaganada
			ProStatus = CP->ppl->StartPropaganda();
			CP->BudgetCounty -= cpd;

			//Set status 
			if (ProStatus == 'S')
			{
				Status = "Propaganda status : Success";
				CP->GetPropaganda('S');

			}
			else if (ProStatus == 'C')
			{
				Status = "Propaganda status : In Progress";
			}

			Status = "Propaganda status : Fail";
			CP->GetPropaganda('F');
		}

		ImGui::Text(Status.c_str());

		ImGui::End();
	}
}