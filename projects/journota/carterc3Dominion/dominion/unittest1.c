/*********************************************************************
** Program name: Assignment 3,Unit Testing
** Author: Aaron Journot
** Date: 10/23/18
** Description: Unit test 1 for dominion.c tests isGameOver function
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
#define FUNC_NAME "isGameOver"

int main (){

    srand(time(0));

    struct gameState game, test;
    int seed = (rand() % 1000);
    int players = 2;
    int kCards[10] = {feast, adventurer, cutpurse, minion, smithy, tribute, sea_hag, great_hall, baron};
    int testNum;
    int failFlag = 0;

    initializeGame(players, kCards, seed, &game);
    
    printf("\n**********************Testing %s**********************\n", FUNC_NAME);
    
    // test state of supply decks
    if(TEST_PRINT){
        printf("\nTesting supply states and game status:\n");
    }

    // test case a (province supply count empty) | Game should end
    memcpy(&test, &game, sizeof(struct gameState));
    test.supplyCount[province] = 0;
    if(TEST_PRINT){
        printf("Province Supply Count: %d Game Over (1=Yes, 0=No): Expected - %d Actual - %d\n",
        test.supplyCount[province], 1, isGameOver(&test));
    }
    // assert(isGameOver(&test)); 
    if(!isGameOver(&test)){ failFlag = 1; } 

    // test case b (province supply count not empty) | Game should not end
    memcpy(&test, &game, sizeof(struct gameState));
    if(TEST_PRINT){
        printf("Province Supply Count: %d Game Over (1=Yes, 0=No): Expected - %d Actual - %d\n",
        test.supplyCount[province], 0, isGameOver(&test));
    }
    // assert(!isGameOver(&game));
    if(isGameOver(&game)){ failFlag = 1; }

    // test state of supply decks
    if(TEST_PRINT){
        printf("\nTesting supply states of additional cards and game status:\n");
    }

    // test case b1-b3
    memcpy(&test, &game, sizeof(struct gameState));
    testNum = 3; /*this will allow a test for <3 or >=3 empty piles*/
    for(unsigned int i = 0; i < testNum; i++){
        test.supplyCount[kCards[i]] = 0;

        if(i < 2){
            if(TEST_PRINT){
                printf("Province Supply Count: %d Supply Decks Empty: %d Game Over (1=Yes, 0=No): Expected - %d Actual - %d\n",
                test.supplyCount[province], (i + 1), 0, isGameOver(&test));
            }
            // assert(!isGameOver(&test));
            if(isGameOver(&test)){ failFlag = 1; }
        }
        if(i >= 2){
            if(TEST_PRINT){
                printf("Province Supply Count: %d Supply Decks Empty: %d Game Over (1=Yes, 0=No): Expected - %d Actual - %d\n",
                test.supplyCount[province], (i + 1), 1, isGameOver(&test));
            }
            // assert(isGameOver(&test));
            if(!isGameOver(&test)){ failFlag = 1; }
        }
    }
    
    if(!failFlag){
        printf("\n**********************ALL TESTS PASSED**********************\n\n");
    } else{
        printf("\n************************TESTS FAILED************************\n\n");
    }

    return 0;
}
