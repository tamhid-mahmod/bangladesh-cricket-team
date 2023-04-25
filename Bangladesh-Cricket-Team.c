#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 100

// player structure
typedef struct BangladeshCricketTeam {
    char fName[STRING_SIZE];
    int age;
    char role[STRING_SIZE];
    int odiMatches;
    int totalRun;
    int highestRun;
    float avgRun;
    float value;
} plyr;

// functions prototype
void allOptions();
void tableHead(char *title);
void tableBody(plyr player);
void error(char *message);
void allPlyrs(plyr *players, int numberOfPlayers);
int getPlyrByName(plyr *players, int numberOfPlayers, char *fName);
int getMostExpPlyrIndex(plyr *players, int numberOfPlayers);
int getNewComPlyrIndex(plyr *players, int numberOfPlayers);
int getTopScorPlyrIndex(plyr *players, int numberOfPlayers);
int getHardHitPlyrIndex(plyr *players, int numOfPlyrs);
int getHighRunTkrPlyrIndex(plyr *players, int numOfPlyrs);
int getMostValPlyrIndex(plyr *players, int numOfPlyrs);
void allAllrounderPlyrs(plyr *players, int numberOfPlayers);

int main() {
    // get input file name from user
    char filename[STRING_SIZE];
    printf("Please Enter The Input File Name : ");
    gets(filename);

    // open input file
    FILE *fp = fopen(filename, "r");
    if(!fp) {
        error("Failed to open input file");
        exit(1);
    }

    // Read number of players from input file
    int numOfPlyrs;
    fscanf(fp, "%d\n", &numOfPlyrs);

    // Allocate memory for array of players
    plyr *players = (plyr*) malloc(numOfPlyrs * sizeof(plyr));
    
    // Read player data from input file and store in struct array
    for(int i = 0; i < numOfPlyrs; i++) {
        fscanf(fp, "%[^\n]\n", players[i].fName);
        fscanf(fp, "%d\n", &players[i].age);
        fscanf(fp, "%[^\n]\n", players[i].role);
        fscanf(fp, "%d\n", &players[i].odiMatches);
        fscanf(fp, "%d\n", &players[i].totalRun);
        fscanf(fp, "%d\n", &players[i].highestRun);
    }
    fclose(fp);

    int ch;
    do {
        allOptions();
        printf("Please Enter Your Choice : ");
        scanf("%d", &ch);
        getchar(); // Consume the newline character

        switch(ch) {
            case 1:
                allPlyrs(players, numOfPlyrs);
                break;
            case 2: {
                char fName[STRING_SIZE];
                printf("Please Enter Player name: ");
                fgets(fName, STRING_SIZE, stdin);
                fName[strcspn(fName, "\n")] = '\0'; // remove trailing newline

                int plyrIndex = getPlyrByName(players, numOfPlyrs, fName);

                if(plyrIndex != -1) {
                    tableHead("Particular player information");
                    tableBody(players[plyrIndex]);
                }
                else {
                    error("Player information not found!");
                }
                break;
            }
            case 3: {
                int mostExpPlyrIndex = getMostExpPlyrIndex(players, numOfPlyrs);
                tableHead("MOST Experienced Player");
                tableBody(players[mostExpPlyrIndex]);
                break;
            }
            case 4: {
                int newComPlyrIndex = getNewComPlyrIndex(players, numOfPlyrs);
                tableHead("New Commer Player");
                tableBody(players[newComPlyrIndex]);
                break;
            }
            case 5: {
                int topScorPlyrIndex = getTopScorPlyrIndex(players, numOfPlyrs);
                tableHead("Top Scorer Player");
                tableBody(players[topScorPlyrIndex]);
                break;
            }
            case 6: {
                int hardHitPlyrIndex = getHardHitPlyrIndex(players, numOfPlyrs);
                tableHead("Hard Hitter Player");
                tableBody(players[hardHitPlyrIndex]);
                break;
            }
            case 7: {
                int highTkrPlyrIndex = getHighRunTkrPlyrIndex(players, numOfPlyrs);
                tableHead("Highest Run Taker Player");
                tableBody(players[highTkrPlyrIndex]);
                break;
            }
            case 8: {
                int mostValPlyrIndex = getMostValPlyrIndex(players, numOfPlyrs);
                tableHead("MOST Valuable Player");
                tableBody(players[mostValPlyrIndex]);
                break;
            }
            case 9:
                allAllrounderPlyrs(players, numOfPlyrs);
                break;
            default:
                error("Wrong choice!");
        }
    }
    while(ch != 10);
    free(players);
    return 0;
}

// print all options
void allOptions() {
    printf("1. Show All Players\n");
    printf("2. Show A Particular player information\n");
    printf("3. Show the MOST Experienced Player (MEP)\n");
    printf("4. Show the New Commer Player (NCP)\n");
    printf("5. Show the Top Scorer Player (TSP)\n");
    printf("6. Show the Hard Hitter Player (HHP)\n");
    printf("7. Show the Highest Run Taker Player (HRTP)\n");
    printf("8. Show the MOST Valuable Player (MVP)\n");
    printf("9. Show the Allrounders\n");
    printf("10. Exit/Quit\n");
}

// center text in box
void centerTextInBox(char *text, int boxLength)
{
    int textLength = strlen(text);
    int paddingLength = (boxLength - textLength - 2) / 2;
    printf("|%*s%s%*s|", paddingLength, " ", text, paddingLength + ((boxLength - textLength - 2) % 2), " ");
    printf("\n");
}

// display player table head
void tableHead(char *title) {
    printf("+-----------------------------------------------------------------------------------------------------+\n");
    centerTextInBox(title, 103);
    printf("+-----------------------------------------------------------------------------------------------------+\n");
    printf("| %-25s | %-4s | %-25s | %-9s | %-10s | %-11s |\n", "Name", "Age", "Role", "ODI Match", "Total Runs", "Highest Run");
    printf("+-----------------------------------------------------------------------------------------------------+\n");
}

// display player table body
void tableBody(plyr player) {
    printf("| %-25s ", player.fName);
    printf("| %-4d ", player.age);
    printf("| %-25s ", player.role);
    printf("| %-9d ", player.odiMatches);
    printf("| %-10d ", player.totalRun);
    printf("| %-11d |", player.highestRun);
    printf("\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
}

// display error message
void error(char *message) {
    int length = strlen(message);
    int i;

    printf(" ");
    for (i = 0; i < length + 2; i++) {
        printf("-");
    }
    printf("\n");

    printf("! ");
    printf("%s", message);
    printf(" !\n");

    printf(" ");
    for (i = 0; i < length + 2; i++) {
        printf("-");
    }
    printf("\n");
}

// print all players
void allPlyrs(plyr *players, int numberOfPlayers) {
    tableHead("All Players");
    for(int i = 0; i < numberOfPlayers; i++) {
        tableBody(players[i]);
    }
}

// get the player index by name
int getPlyrByName(plyr *players, int numberOfPlayers, char *fName) {
    for(int i = 0; i < numberOfPlayers; i++) {
        if(strcmp(players[i].fName, fName) == 0) {
            return i;
        }
    }
    return -1;
}

// get the most experienced player index
int getMostExpPlyrIndex(plyr *players, int numberOfPlayers) {
    int maxODI = players[0].odiMatches, plyrIndex = 0;
    
    for(int i = 1; i < numberOfPlayers; i++) {
        if(players[i].odiMatches > maxODI) {
            maxODI = players[i].odiMatches;
            plyrIndex = i;
        }
    }
    return plyrIndex;
}

// get the new commer player index
int getNewComPlyrIndex(plyr *players, int numberOfPlayers) {
    int minAge = players[0].age, plyrIndex = 0;
    
    for(int i = 1; i < numberOfPlayers; i++) {
        if(players[i].age < minAge) {
            minAge = players[i].age;
            plyrIndex = i;
        }
    }
    return plyrIndex;
}

// get the top scorer player index
int getTopScorPlyrIndex(plyr *players, int numOfPlyrs) {
    int maxTotalRun = players[0].totalRun, plyrIndex = 0;
    
    for(int i = 1; i < numOfPlyrs; i++) {
        if(players[i].totalRun > maxTotalRun) {
            maxTotalRun = players[i].totalRun;
            plyrIndex = i;
        }
    }
    return plyrIndex;
}

// get the hard hitter player index
int getHardHitPlyrIndex(plyr *players, int numOfPlyrs) {
    // calculate the average run per match for each player
    for (int i = 0; i < numOfPlyrs; i++) {
        players[i].avgRun = (float) players[i].totalRun / players[i].odiMatches;
    }

    float maxAvgRun = players[0].avgRun;
    int plyrIndex = 0;

    for(int i = 1; i < numOfPlyrs; i++) {
        if(players[i].avgRun > maxAvgRun) {
            maxAvgRun = players[i].avgRun;
            plyrIndex = i;
        }
    }
    return plyrIndex;
}

// get the highest run taker player index
int getHighRunTkrPlyrIndex(plyr *players, int numOfPlyrs) {
    int maxHighestRun = players[0].highestRun, plyrIndex = 0;
    
    for(int i = 1; i < numOfPlyrs; i++) {
        if(players[i].highestRun > maxHighestRun) {
            maxHighestRun = players[i].highestRun;
            plyrIndex = i;
        }
    }
    return plyrIndex;
}

// get the most valuable player index
int getMostValPlyrIndex(plyr *players, int numOfPlyrs) {
    // calculate the value of each player using the formula
    for (int i = 0; i < numOfPlyrs; i++) {
        players[i].value = players[i].age + players[i].odiMatches + players[i].highestRun + ((float)players[i].totalRun / players[i].odiMatches) + ((float)players[i].highestRun / players[i].age) + (strcmp(players[i].role, "Allrounder") == 0 ? 50 : 0);
    }
    
    float maxValue = players[0].value;
    int plyrIndex = 0;

    for(int i = 1; i < numOfPlyrs; i++) {
        if(players[i].value > maxValue) {
            maxValue = players[i].value;
            plyrIndex = i;
        }
    }
    return plyrIndex;
}

// print the all Allrounders
void allAllrounderPlyrs(plyr *players, int numberOfPlayers) {
    tableHead("All Allrounder Players");
    for(int i = 0; i < numberOfPlayers; i++) {
        if(strcmp(players[i].role, "Allrounder") == 0)
        tableBody(players[i]);
    }
}