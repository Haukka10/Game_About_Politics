#pragma once

#include "Political Partys/PoliticalPartys.h"
#include "Make Politics/CreatePoli.h"
#include "Population/Population.h"

#include <vector>

namespace CountyDetails
{
	class County
	{
	public:
		County();
		~County() = default;
		//TODO : Show politicalPartys(Fix);
		Population::Populations& SetPopulation();

		void GetLaw(PoliticalMake::Law law);
		void ShowPoliticalPartys();
		void NextTurn();

		std::string NameOfCounty = "";
		Population::Populations* ppl = nullptr;
		PartyPolis::PartyPoli* PlayerParty;

		int BudgetCounty = 0;
		int RemingTiemToElectons = 20;
		bool IsPlayerWin = false;

		void Elections();
		void GetPropaganda(char Status);
	private:

		int m_MonenyPerTurn = 0;
		int m_PalamentMembersMax = 0;

		std::unordered_map<std::string, int> m_DivPalament;

		std::vector<PartyPolis::PartyPoli> m_InGov;

		std::vector<PartyPolis::PartyPoli> m_PoliticalParties;
		std::vector<PoliticalMake::Law> m_laws;

		bool m_CountyTechLeveling = true;
		bool m_OnMinus = false;

		void CountyOnMinus();
	};
}