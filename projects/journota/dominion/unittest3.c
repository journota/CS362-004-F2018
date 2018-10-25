/*********************************************************************
** Program name: Assignment 3,Unit Testing
** Author: Aaron Journot
** Date: 10/23/18
** Description: Unit test 2 for dominion.c tests supplyCount function
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
#define FUNC_NAME "supplyCount"

int main (){

    // initialize game
    // set cards

    srand(time(0));

    struct gameState game, test;
    int seed = (rand() % 1000);
    int players = 2;
    int kCards[10] = {feast, adventurer, cutpurse, minion, smithy, tribute, sea_hag, great_hall, baron};
    int failFlag = 0;

    initializeGame(players, kCards, seed, &game);
    
    printf("\n**********************Testing %s**********************\n", FUNC_NAME);

    // return supply count of cards
    memcpy(&test, &game, sizeof(struct gameState));

    // set supplies to a specific count
    for(unsigned int i = 0; i < 10; i++){
        test.supplyCount[kCards[i]] = i;
    }

    if(TEST_PRINT){
        printf("Testing supply card counts:\n");
    }

    // assert all supply counts
    for(unsigned int i = 0; i < 10; i++){
        // assert(supplyCount(kCards[i], &test) == i);
        if(supplyCount(kCards[i], &test) != i) { failFlag = 1; }
        if(TEST_PRINT){
            printf("Card Number: %d Count: Expected - %d Actual - %d.\n", (i + 1), i, supplyCount(kCards[i], &test));
        }
    }

    if(!failFlag){
        printf("\n**********************ALL TESTS PASSED**********************\n\n");
    } else{
        printf("\n************************TESTS FAILED************************\n\n");
    }

    return 0;
}