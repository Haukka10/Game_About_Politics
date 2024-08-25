#pragma once

#include "string"

namespace PartyPolis
{
	class PartyPoli
	{
	public:
		PartyPoli();

		std::string GetPosForPolitical();
		int AddPopularity();
		int GetPopularity();

		std::string NameParty;

		int Popularity = 0;
		int PllForParty;

		bool IsGrowing = true;
	private:

		std::string m_PosFor[3] = { "Left","Center","Right" };
	};
}