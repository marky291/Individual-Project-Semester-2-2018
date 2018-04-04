#pragma once

#include "CFootballTeam.h"

using namespace std;

class CFootballTable
{
	private:
	const unsigned int m_SpaceName = 25;
	const unsigned int m_SpaceValue = 7;
	const std::string m_Indentation = "\t\t\t";

	// Allows dynamic width changes.
	unsigned int GetLineWidth();

	public:
		void Header(string tablename);
		void Footer(int resultCount);
		void TeamStanding(CFootballTeam& team);
		void LineBreak(char fillCharacters);

};