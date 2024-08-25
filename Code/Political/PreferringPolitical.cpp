#include "PreferringPolitical.h"
#include "Population/Population.h"

#include <algorithm>
#include <cmath>
#include <format>

namespace PerPolitical
{
	void PerferringPoli::GetLaw(PoliticalMake::Law law, Population::Populations& pp)
	{
		Name = law.NameOfLaw;

		//FIXME : Save to files 
		std::string a = std::format("Add Law {0}", law.NameOfLaw);
		printf(a.c_str());
		m_PopularityOverall = CalculatePopularityOverall(law,pp);
	}

	float PerferringPoli::GetPopularityOverall()
	{
		return m_PopularityOverall;
	}

	std::string PerferringPoli::GetName()
	{
		return Name;
	}
	/// <summary>
	/// Calculate Popularity Overall bead on Poli rate left and right 
	/// </summary>
	/// <param name="law"></param>
	/// <param name="pp"></param>
	/// <returns></returns>
	float PerferringPoli::CalculatePopularityOverall(PoliticalMake::Law law, Population::Populations& pp)
	{
		float output;
		double popularityLeft = std::log(pp.PoliRate["Left"]) + (law.PosOfEcomicLaw + law.PosOfSocialLaw);
		double popularityRight = std::log(pp.PoliRate["Right"]) + std::cos(law.PosOfEcomicLaw + law.PosOfSocialLaw);

		output = (float)(popularityLeft - popularityRight) / 2;

		if (law.PosOfEcomicLaw < 20 && law.PosOfEcomicLaw > -20)
		{
			output += (float)std::log(pp.PoliRate["Center"]) - law.PosOfEcomicLaw;
		}

		if (law.PosOfSocialLaw < 20 && law.PosOfSocialLaw > -20)
		{
			output += (float)std::log(pp.PoliRate["Center"]) - law.PosOfSocialLaw;
		}

		if (output == -INFINITY && output == INFINITY)
		{
			printf("INF !!!");
			output = (float)(popularityLeft - popularityRight) / 2;
		}

		if (law.IsTaxLaw)
		{
			if(pp.PoliRate["Left"] > pp.PoliRate["Right"])
				output += (float)std::lerp(0, law.TaxRateLaw, 0.5);
			else
				output -= (float)std::lerp(0, law.TaxRateLaw, 0.5);
		}

		if (law.IsGiveLaw)
		{
			if (pp.PoliRate["Left"] < pp.PoliRate["Right"])
				output -= (float)std::lerp(0, law.TaxRateLaw, 0.5);
			else
				output += (float)std::lerp(0, law.TaxRateLaw, 0.5);
		}
		//Make a 0.- numebr for %
		int RoundDown = (int)std::floor(std::abs(output));
		RoundDown = std::clamp(RoundDown, 0, 100);

		auto c = std::to_string(RoundDown);
		c.insert(0, "0.");

		return std::stof(c);
	}
}
