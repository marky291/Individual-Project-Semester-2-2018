#include "stdafx.h"
#include "CFootballTable.h"

using namespace std;

void CFootballTable::Header(string tablename)
{
	system("cls");

	LineBreak('-');

	std::cout << m_Indentation << setfill(' ') << setw(GetLineWidth()) << left << "Showing " + tablename << endl;

	LineBreak('-');

	std::cout << m_Indentation
		<< setfill(' ') << setw(m_SpaceValue) << left << "#"
		<< setfill(' ') << setw(m_SpaceName) << left << "Team"
		<< setfill(' ') << setw(m_SpaceValue) << right << "Pl"
		<< setfill(' ') << setw(m_SpaceValue) << right << "F"
		<< setfill(' ') << setw(m_SpaceValue) << right << "A"
		<< setfill(' ') << setw(m_SpaceValue) << right << "GD"
		<< setfill(' ') << setw(m_SpaceValue) << right << "Pts"
		<< endl;

	LineBreak('-');
}

void CFootballTable::Footer(int resultCount)
{
	LineBreak('-');

	std::cout << m_Indentation << setfill(' ') << setw(GetLineWidth()) << right << std::to_string(resultCount) + " Results found." << endl;

	LineBreak('-');

	std::cout << endl << endl << endl;
}

void CFootballTable::TeamStanding(CFootballTeam& team)
{
	std::cout << m_Indentation
		<< setfill(' ') << setw(m_SpaceValue) << left << 0
		<< setfill(' ') << setw(m_SpaceName) << left << team.GetName()
		<< setfill(' ') << setw(m_SpaceValue) << right << team.GetGamesPlayed()
		<< setfill(' ') << setw(m_SpaceValue) << right << team.GetGoalsFor()
		<< setfill(' ') << setw(m_SpaceValue) << right << team.GetGoalsAgainst()
		<< setfill(' ') << setw(m_SpaceValue) << right << team.GetGoalDifference()
		<< setfill(' ') << setw(m_SpaceValue) << right << team.GetPoints()
		<< endl;
}

void CFootballTable::LineBreak(char fillCharacters)
{
	std::cout << m_Indentation << setfill(fillCharacters) << setw(GetLineWidth()) << left << "" << endl;
}

unsigned int CFootballTable::GetLineWidth()
{
	return (m_SpaceValue * 6) + (m_SpaceName * 1);
}
