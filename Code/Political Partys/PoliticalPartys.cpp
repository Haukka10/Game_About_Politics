#include "Political Partys/PoliticalPartys.h"

#include "random"

namespace PartyPolis
{
	PartyPoli::PartyPoli()
	{
		Popularity = GetPopularity();
		auto c = 'a' + rand() % 26;
		NameParty = c;
	}

	std::string PartyPoli::GetPosForPolitical()
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 2);

		auto c = m_PosFor[dist6(rng)];

		return c;
	}

	int PartyPoli::AddPopularity()
	{
		srand(time(0));
		int r = rand() % 100 + 15;

		if (!IsGrowing)
		{
			r *= (-1);
		}

		r = std::clamp(r, -90, 90);

		return r;
	}

	int PartyPoli::GetPopularity()
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 100);

		int r = dist6(rng);
		r -= rand() % 10;

		return std::clamp(r,1,90);
	}
}