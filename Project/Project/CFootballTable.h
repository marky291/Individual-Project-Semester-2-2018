#pragma once

#include "CDisplay.h"
#include "CFootballTeam.h"

using namespace std;

class CFootballTable : public CDisplay
{

	// Quick maths.
		static const int m_SmallColumnWidth = 7;
		static const int m_LargeColumnsWidth = 0;

	private:
		static int ColumnSmall();
		static int ColumnLarge();

	public:
		static void Heading(string tablename);
		static void Footer(int resultCount);
		static void TeamStanding(CFootballTeam& team);

};