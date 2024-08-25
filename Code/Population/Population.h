#pragma once

#include <unordered_map>
#include <string>

namespace Population
{
	class Populations
	{
	public:
		Populations();

		long AmmountPopulations;
		int BirthRate;

		int LevelOfTech = 0;
		int LevelOfWealth = 0;

		int VotePopulations;
		int NotVotePopulations;

		int PropagandaStrength = 0;
		unsigned int PplBudget = 0;

		char StartPropaganda();
		char StopPropaganda();
		void SetBudget();
		void PPLAge();

		std::unordered_map<std::string, int> PoliRate = { {"Left",0}, {"Center",0},{"Right",0} };

	private:

		unsigned int m_ConservativePopulation;
		unsigned int m_ProgressivismPopulation;

		unsigned int m_Older;
		unsigned int m_Young;

		unsigned int m_Men;
		unsigned int m_Women;


		void PopulationConOrPro();
		void VotePopulationsAmmount();

		int BirthRateFun();

		std::unordered_map<std::string, int> CalculatePoliRate();
		char PropagandaStatus(char currentStatus = 'N');
	};

	int RandomDiv(int min, int max);
}