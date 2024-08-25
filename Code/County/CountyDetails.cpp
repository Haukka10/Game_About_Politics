#include <random>

#include "CountyDetails.h"
#include "Population/Population.h"
#include "Political Partys/PoliticalPartys.h"


namespace CountyDetails
{
	
	PartyPolis::PartyPoli a;
	County::County()
	{
		// initialization County class 
		srand(time(0));
		BudgetCounty = ((rand() % 100 + 1) * 4) * 1000;
		m_MonenyPerTurn = (BudgetCounty / 1000) / 5;
		// Check is Population::Populations(); is not null
		if (ppl == nullptr)
		{
			//initialization Population::Populations
			ppl = new Population::Populations();

			ppl->LevelOfTech = rand() % 100 + 1;
			ppl->LevelOfWealth = rand() % 100 + 1;
		}
		// Make Player pariy 
		a.NameParty = "Player";

		a.PllForParty = ppl->PoliRate[a.GetPosForPolitical()];
		PlayerParty = &a;

		for (size_t i = 0; i < 9; i++)
		{
			PartyPolis::PartyPoli a;

			a.PllForParty = ppl->PoliRate[a.GetPosForPolitical()];
			m_PoliticalParties.push_back(a);
		}

		ShowPoliticalPartys();

		m_PalamentMembersMax = ppl->VotePopulations / 5;
	}

	Population::Populations& County::SetPopulation()
	{
		return *ppl;
	}

	void County::GetLaw(PoliticalMake::Law law)
	{
		if (m_laws.size() < 4)
			law.ToFinishLaw = 1;
		
		PlayerParty->Popularity += (PlayerParty->AddPopularity()) + 10;

		m_laws.push_back(law);
	}

	void County::ShowPoliticalPartys()
	{
		for (auto p : m_PoliticalParties)
		{
			printf(std::to_string(p.Popularity).c_str());
			printf("\n");
		}
	}

	void County::NextTurn()
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(0, m_PoliticalParties.size() - 1);
		std::uniform_int_distribution<std::mt19937::result_type> Bools(0, 1);
		auto PoliRand = dist6(rng);
		auto GroRand = Bools(rng);
		// set true or false to {IsGrowin}
		m_PoliticalParties[PoliRand].IsGrowing = false;
		m_CountyTechLeveling = GroRand;

		m_PoliticalParties[PoliRand].Popularity += m_PoliticalParties[PoliRand].AddPopularity();

		if (m_PoliticalParties[PoliRand].Popularity < 0)
		{
			m_PoliticalParties.erase(m_PoliticalParties.begin() + PoliRand);
			PartyPolis::PartyPoli a;

			a.PllForParty = ppl->PoliRate[a.GetPosForPolitical()];
			m_PoliticalParties.push_back(a);
		}

		BudgetCounty += m_MonenyPerTurn;
		for (size_t i = 0; i < m_laws.size(); i++)
		{
			m_laws[i].ToFinishLaw--;
			auto s = std::to_string(m_laws[i].SocialRateLaw);
			auto t = std::to_string(m_laws[i].TaxRateLaw);
			t.insert(0, "0.");
			s.insert(0, "0.");

			if (m_laws[i].IsGiveLaw && m_laws[i].ToFinishLaw < 2)
			{
				
				if (m_MonenyPerTurn > 0)
				{
					m_MonenyPerTurn -= int((m_MonenyPerTurn * std::stof(s)));
				}
				else
				{
					m_OnMinus = true;
					BudgetCounty -= int(std::stof(s) * 100);
				}

			}
			if (m_laws[i].IsTaxLaw && m_laws[i].ToFinishLaw < 2)
			{
				m_MonenyPerTurn += int(ppl->PplBudget * std::stof(t));
			}

			if (m_laws[i].ToFinishLaw == 0)
			{
				m_laws.erase(m_laws.begin() + i);
				i = -1;
			}
		}

		if (m_CountyTechLeveling)
		{
			ppl->LevelOfTech += rand() % 10;
			ppl->LevelOfWealth += rand() % 10;
		}
		else
		{
			ppl->LevelOfTech -= rand() % 10;
			ppl->LevelOfWealth -= rand() % 10;
		}

		if (m_OnMinus)
			CountyOnMinus();

		RemingTiemToElectons--;
		printf(std::to_string(RemingTiemToElectons).c_str());
		if (RemingTiemToElectons == 0)
			Elections();
	}

	void County::Elections()
	{
		std::unordered_map<std::string, int> PoliticalPartysInElections;
		PoliticalPartysInElections[PlayerParty->NameParty] = PlayerParty->Popularity;

		for(auto var : m_PoliticalParties)
		{
			if(var.Popularity > 0)
				PoliticalPartysInElections[var.NameParty] = var.Popularity;
		}
		int buffor = 0;
		for (auto p : PoliticalPartysInElections)
		{
			std::string Name = p.first;
			int Ammount = p.second;

			m_DivPalament[Name] = Ammount;
			buffor += Ammount;

			if(Name == "Player")
				if (Ammount >= m_PalamentMembersMax / 2)
				{
					IsPlayerWin = true;
					break;
				}
		}

		RemingTiemToElectons = 10;
	}

	void County::GetPropaganda(char Status)
	{
		if (Status == 'S')
		{
			PlayerParty->Popularity += 25;
			return;
		}
		if (Status == 'F')
		{
			PlayerParty->Popularity -= 25;
		}
	}

	void County::CountyOnMinus()
	{
		ppl->AmmountPopulations -= std::abs(BudgetCounty) * 2;
		ppl->BirthRate -= 2;
	}
}