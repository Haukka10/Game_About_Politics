#include "CreatePoli.h"

#include <cmath>
#include <algorithm>


namespace PoliticalMake
{
	Law::Law(std::string Name, int* PosOfEcomic, int* PosOfSocial, int* TaxRate, int* SocialRate, bool* IsTax, bool* IsGive)
	{
		NameOfLaw = Name;
		PosOfEcomicLaw = *PosOfEcomic;
		PosOfSocialLaw = *PosOfSocial;

		IsTaxLaw = *IsTax;
		IsGiveLaw = *IsGive;

		TaxRateLaw = *TaxRate;
		SocialRateLaw = *SocialRate;

		ToFinishLaw = CalculateToTimeFinish();
	}

	int Law::CalculateToTimeFinish()
	{
		double a = (PosOfEcomicLaw - PosOfSocialLaw) / 2;

		a = std::abs(a);
		a--;

		return std::clamp((int)a, 1, 15);
	}
}
