/*********************************************************************
** Program name: Assignment 3,Unit Testing
** Author: Aaron Journot
** Date: 10/23/18
** Description: Unit test 2 for dominion.c tests handCard function
*********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#define TEST_PRINT 1
#define FUNC_NAME "handCard"

int main (){

    srand(time(0));

    struct gameState game, test;
    int seed = (rand() % 1000);
    int players = 2;
    int kCards[10] = {feast, adventurer, cutpurse, minion, smithy, tribute, sea_hag, great_hall, baron};
    int p = 0;
    int failFlag = 0;

    initializeGame(players, kCards, seed, &game);
    
    printf("\n**********************Testing %s**********************\n", FUNC_NAME);

    // game initialized, each player should have 5 cards in hand
    memcpy(&test, &game, sizeof(struct gameState));

    for(unsigned int i = 0; i < 6; i++){
        // assert(test.hand[p][i] == handCard(i, &test));
        if(test.hand[p][i] != handCard(i, &test)){ failFlag = 1; }
        if(TEST_PRINT){
            printf("Player: %d Card Position: %d Value: Expected - %d Actual - %d.\n", (p + 1), (i + 1), test.hand[p][i], handCard(i, &test));
        }
    }

    if(!failFlag){
        printf("\n**********************ALL TESTS PASSED**********************\n\n");
    } else{
        printf("\n************************TESTS FAILED************************\n\n");
    }
    

    return 0;
}
