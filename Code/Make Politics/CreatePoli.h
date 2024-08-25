#pragma once
#include "string"

namespace PoliticalMake
{
	class Law
	{
	public:
		Law(std::string Name, int* PosOfEcomic, int* PosOfSocial, int* TaxRate, int* SocialRate, bool* IsTax, bool* IsGive);

		std::string NameOfLaw = "NoP";
		unsigned int ToFinishLaw;

		int PosOfEcomicLaw;
		int PosOfSocialLaw;

		unsigned int TaxRateLaw = 0;
		unsigned int SocialRateLaw = 0;

		bool IsTaxLaw;
		bool IsGiveLaw;

	private:
		bool m_MixPos;
		int CalculateToTimeFinish();
	};

}