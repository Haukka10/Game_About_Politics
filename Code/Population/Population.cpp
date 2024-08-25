#include "Population.h"
#include "string"
#include <iomanip>
#include "random"

#include "County/CountyDetails.h"

Population::Populations::Populations()
{
	AmmountPopulations = RandomDiv(1000,5657);

	m_Men = AmmountPopulations / 2;
	m_Women = AmmountPopulations / 2;
	//Starting
	PPLAge();
	PoliRate = CalculatePoliRate();
	PopulationConOrPro();
	BirthRate = BirthRateFun();
	VotePopulationsAmmount();
	SetBudget();
}

char Population::Populations::StartPropaganda()
{
	return PropagandaStatus('S'); // Start the Propaganda
}

char Population::Populations::StopPropaganda()
{
	return PropagandaStatus('N'); // Stop the Propaganda
}

void Population::Populations::SetBudget()
{
	PplBudget = (m_Young * 0.90) * BirthRate;
}

void Population::Populations::PopulationConOrPro()
{
	long PPLCon = AmmountPopulations - RandomDiv(AmmountPopulations * 0.25,AmmountPopulations);
	m_ConservativePopulation = PPLCon;

	long PPLPro = AmmountPopulations - PPLCon;
	m_ProgressivismPopulation = PPLPro;
}

void Population::Populations::VotePopulationsAmmount()
{
	VotePopulations = (m_ConservativePopulation + m_ProgressivismPopulation);
	VotePopulations = (int)std::floor(VotePopulations * 0.90);
}

int Population::Populations::BirthRateFun()
{
	float b = 0;

	auto L = (LevelOfTech + LevelOfWealth);
	auto BL = m_Women / 4;

	b = (BL - L) * 1000;

	b = std::floor(b / 100000);
	return (int)b;
}

void Population::Populations::PPLAge()
{
	std::string Pro = std::to_string(LevelOfTech + LevelOfWealth);
	Pro.insert(0,"0.");

	int Buffor = AmmountPopulations;

	m_Young = Buffor * std::stof(Pro);
	m_Older = Buffor - m_Young;
}

std::unordered_map<std::string, int> Population::Populations::CalculatePoliRate()
{
	int PopulationsBuffor = AmmountPopulations;
	std::string s[3] = { "Left","Center","Right" };

	int loopTime = 0;
	int check = 0;
	while (AmmountPopulations != check)
	{
		int i = RandomDiv(0, 2);
		std::string GivePPl;

		if (s[i] != "Delete" && loopTime < 2)
		{
			GivePPl = s[i];
		}
		else
		{
			i = 0;
			for (auto c : s)
			{
				if (c != "Delete")
				{
					GivePPl = c;
					i = std::clamp(i, 0, 2);
					break;
				}
				else
					i++;
			}
		}

		int a = 0;

		if (loopTime < 2)
		{
			a = RandomDiv(1, PopulationsBuffor);
			PoliRate[GivePPl] = a;
		}
		else
		{
			PoliRate[GivePPl] = PopulationsBuffor;
			PopulationsBuffor = 0;
		}

		PopulationsBuffor -= a;

		s[i] = "Delete";
		loopTime++;
		check += PoliRate[GivePPl];
	}
	return PoliRate;
}

char Population::Populations::PropagandaStatus(char currentStatus)
{
	if (currentStatus == 'N')
		return currentStatus;

	char status[3] = {'F','S','C'};
	float rng = RandomDiv(1, 50);

	if (PropagandaStrength < -20)
		rng += 20;

	for (size_t i = 0; i < (m_Young * 0.90); i++)
	{
		rng += 0.005;
	}

	for (size_t i = 0; i < (m_Older * 0.90) / 2; i++)
	{
		rng += 0.025;
	}

	rng = std::clamp((int)rng, 1, 100);

	if (rng < 55)
	{
		PropagandaStrength -= 10;
		return status[0];
	}
	if (rng >= 55 && rng <= 80)
	{
		return status[2];
	}

	PropagandaStrength += 10;

	return status[1];
}

int Population::RandomDiv(int min, int max)
{
	if (min <= 0)
		return 0;

	if (max <= 0)
		return 0;

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max);
	return dist6(rng);
}
