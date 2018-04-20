#include "stdafx.h"
#include "CFootballTable.h"

using namespace std;

/**
 * The dynamic width based on wall width for small columns in the table.
 * 
 * @return integer of the character spaces column small will use.
 */
int CFootballTable::ColumnSmall()
{
	return CDisplay::LineWidth() / m_SmallColumnWidth;
}

/**
 * The dynamic width based on wall width for large columns in the table.
 * 
 * @return integer of the character spaces column large will use.
 */
int CFootballTable::ColumnLarge()
{
	return 0;
}

/**
 * Table header will generate and display the column titles and a description of what it might hold.
 * 
 * @param tablename the name that describes the data (category) that will be shown.
 * 
 * @return void.
 */
void CFootballTable::Heading(string tablename)
{
	system("cls");

	Linebreak('-');
	
	CDisplay::Message("Showing " + tablename);

	Linebreak('-');

	Padding();

	std::cout
		<< setfill(' ') << setw(CFootballTable::ColumnSmall()) << left << "#"
		<< setfill(' ') << setw(CFootballTable::ColumnSmall()) << left << "Team"
		<< setfill(' ') << setw(CFootballTable::ColumnSmall()) << right << "Pl"
		<< setfill(' ') << setw(CFootballTable::ColumnSmall()) << right << "F"
		<< setfill(' ') << setw(CFootballTable::ColumnSmall()) << right << "A"
		<< setfill(' ') << setw(CFootballTable::ColumnSmall()) << right << "GD"
		<< setfill(' ') << setw(CFootballTable::ColumnSmall()) << right << "Pts"
		<< endl;

	Linebreak('-');
}

/**
 * Table standing will generate and display the column data of the passed team.
 * 
 * @param team object of the team that will be used for display.
 * 
 * @return void.
 */
void CFootballTable::TeamStanding(CFootballTeam& team)
{
	Padding();

	std::cout
		<< setfill(' ') << setw(CFootballTable::ColumnSmall()) << left << team.GetLeaguePosition()
		<< setfill(' ') << setw(CFootballTable::ColumnSmall()) << left << team.GetName()
		<< setfill(' ') << setw(CFootballTable::ColumnSmall()) << right << team.GetGamesPlayed()
		<< setfill(' ') << setw(CFootballTable::ColumnSmall()) << right << team.GetGoalsFor()
		<< setfill(' ') << setw(CFootballTable::ColumnSmall()) << right << team.GetGoalsAgainst()
		<< setfill(' ') << setw(CFootballTable::ColumnSmall()) << right << team.GetGoalDifference()
		<< setfill(' ') << setw(CFootballTable::ColumnSmall()) << right << team.GetPoints()
		<< endl;
}

/**
 * Table Footer will generate and display the tables footer, which will show the results found.
 * 
 * @param resultCount the number of results that have been passed through to the table.
 * 
 * @return void
 */
void CFootballTable::Footer(int resultCount)
{
	Linebreak('-');

	CDisplay::Padding();

	cout << setw(CDisplay::LineWidth()) << setfill(' ') << right << std::to_string(resultCount) + " Results found.";

	cout << endl;

	Linebreak('-');

	cout << endl;
}