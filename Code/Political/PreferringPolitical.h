#pragma once
#include "string"
#include "vector"

#include "Population/Population.h"
#include <Make Politics/CreatePoli.h>

namespace PerPolitical
{
	class PerferringPoli
	{
	public:
		PerferringPoli() = default;

		void GetLaw(PoliticalMake::Law law, Population::Populations& pp);
		float GetPopularityOverall();

		std::string GetName();

	private:
		std::string Name;

		float m_PopularityOverall = 0;
		float CalculatePopularityOverall(PoliticalMake::Law law, Population::Populations& pp);
	};
}