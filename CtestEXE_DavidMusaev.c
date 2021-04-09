#define _CRT_SECURE_NO_WARNINGS
#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct date
{
	int day;
	int month;
	int year;
}date;
typedef struct player
{
	int id;
	char* name;
	int shirtDigit;
	date birthDate;
}player;

typedef struct team
{
	char* teamUniqueName;
	int maxPlayers;
	int playerCounter;
	player* playerList;
	int winCounter;
}team;

void readPlayer(player* newPlayer);//initialize a new player stats into Data Base
void initTeam(team *newTeam);//initialize a new team stats into Data Base
void addPlayer(team *editTeam);//add a new player to a team
team* maxSuccees(team *teamList, int teamCount);//return the team with the highiest number of wins
player* nameLikeA(team *checkThisTeam, int *arrANameSize);//return an array of players in with first letter A in thier names,the players in the same team
int isBirthday(date d);//check if this date equilant to this day
void printPlayer(player checkThisPlayer);//check this player and print his details
void printTeam(team checkThisTeam);//check this team and print it details

void main()
{

	//arg initialization
	int i=0,j=0,numOfteams = 0;
	team *teamList;
	
	//team list initializtion
	printf("\nHello,\nEnter number of teams you want to enter:");
	scanf("%d", &numOfteams);//input:number of teams
	teamList = (team*)calloc(numOfteams, sizeof(team));//memory allocation for team list
	

	//initialzie every team with 2 players and show team info
	for (i = 0; i < numOfteams; i++)
	{
		initTeam(teamList + i);//create a new team

		for (j = 0; j < 2; j++)
		{
			addPlayer(teamList + i);//add new player to the team -Twice
			
		}

		printTeam(*(teamList + i));//print the details about the team
		

	}
	
	printf("\nThe team with highest Win rait is:%s",(maxSuccees(teamList, numOfteams)->teamUniqueName));//which team has the most wins 




	//free mem teams
	free(teamList);


}


//initialize a new player stats into Data Base
void readPlayer(player* newPlayer)
{

	
	//input the Name of the new player
	printf("\nEnter the Name of the player:");
	newPlayer->name = (char*)calloc(1,sizeof(char));
	scanf("%s", newPlayer->name);


	//input of ID of the new player
	printf("\nEnter the ID of the player:");
	scanf("%d", &newPlayer->id);

	//input the digit of the new player
	printf("\nEnter the T-shirt Digit of the player:");
	scanf("%d", &newPlayer->shirtDigit);

	//input Date of birth of the new player
	printf("\nEnter the Birth Date of the player:(dd mm yy)");
	scanf("%d %d %d", &newPlayer->birthDate.day, &newPlayer->birthDate.month, &newPlayer->birthDate.year);




}

//initialize a new team stats into Data Base
void initTeam(team *newTeam)
{
	//input Name of the team
	printf("\nEnter the Name of the Team:");
	newTeam->teamUniqueName = (char*)calloc(1, sizeof(char));
	scanf("%s", newTeam->teamUniqueName);

	//input Max number of players
	printf("\nEnter the Max count of the number of players in this team:");
	scanf("%d", &newTeam->maxPlayers);

	//memory allocation for the Max number of players
	newTeam->playerList = (player*)calloc(newTeam->maxPlayers, sizeof(player));
}

//add a new player to a team
void addPlayer(team *editTeam)
{
	if (editTeam->playerCounter == editTeam->maxPlayers)//if the team is full
	{
		return;
	}
	else//if the team not full
	{
		readPlayer((editTeam->playerList) + editTeam->playerCounter);//add new player to location of 0+num of players
		editTeam->playerCounter++;//count the new player +1 
	}

	   
}

//return the team with the highiest number of wins
team* maxSuccees(team *teamList, int teamCount)//return the team with the highiest number of wins
{
	
	if (teamCount == 0)//exit statement
	{
		return teamList+teamCount;
	}
	
	if (((teamList)+teamCount)->winCounter >= maxSuccees((teamList), teamCount - 1)->winCounter)
	{
		return((teamList+teamCount-1));//if this team has bigger rate of wins - return it 
	}

	else
	{
		return maxSuccees((teamList), teamCount - 1);//else return the team with the bigger rate of wins with a list that  less by 1 of this list size
	}



}

//return an array of players in with first letter A in thier names,the players in the same team
player* nameLikeA(team *checkThisTeam,int *arrANameSize)
{

	//tempory team for being an A  names team
	team *aTeam = (team*)calloc(1, sizeof(team));
	aTeam->playerList = (player*)calloc(checkThisTeam->playerCounter, sizeof(player));
	
	
	int i = 0, aCounter = 0;//initialize the counter 


	while (i < checkThisTeam->playerCounter)//check all the players in the team
	{
		if ((checkThisTeam->playerList+i)->name[0]=='a' || (checkThisTeam->playerList + i)->name[0]=='A')//if its mactched so 
		{
			
			//add to the array
			*((aTeam->playerList) + aCounter) = *(checkThisTeam->playerList + i);
			aCounter++;
		}
		i++;//go to next one

	}
	player *returnList= (player*)realloc(aTeam->playerList, (aCounter) * sizeof(player));//copy all players to new array in the real size

	free(aTeam);//free the tmp team memory

	*arrANameSize = aCounter;//connect to pointer the size of the 'A' names array

	return returnList;
	

}

//check if this date equilant to this day
int isBirthday(date d)
{

	//real time initialize
	time_t now = time(0);
	tm *ltm = localtime(&now);

	if (ltm->tm_mday == d.day && ((ltm->tm_mon)+1) == d.month && (ltm->tm_year+1900) == d.year)//if there is a match to today date
	{
		return TRUE;
	}
	else//if there is NOT a match to today date
	{
		return FALSE;
	}
}


//check this player and print his details
void printPlayer(player checkThisPlayer)
{
	printf("\nPlayer:\nID:%d", checkThisPlayer.id);//show id
	printf("\nName:%s", checkThisPlayer.name);//show name
	printf("\nShirt-Digit:%d", checkThisPlayer.shirtDigit);//show shirt digit
	printf("\nBirth date:%d/%d/%d", checkThisPlayer.birthDate.day, checkThisPlayer.birthDate.month, checkThisPlayer.birthDate.year);//show birth date
	
	if (isBirthday(checkThisPlayer.birthDate) == TRUE)//if its his birthdate
	{
		printf("\nToday his Birth Date");
	}
	
	else//if its not his birthdate
	{
		printf("\nToday it's NOT his Birth Date");
	}
}

//check this team and print it details
void printTeam(team checkThisTeam)
{
	printf("\nTeam:\nName:%s",checkThisTeam.teamUniqueName);//name of the team
	printf("\nNumber of players in present:%d", checkThisTeam.playerCounter);//number of players
	printf("\nNumber of Wins:%d", checkThisTeam.winCounter);//how many wins 

	int i = 0;

	while (i < checkThisTeam.playerCounter)//print the details of all team players
	{
		printPlayer(*(checkThisTeam.playerList+i));
		i++;
		printf("\n");
	}
}