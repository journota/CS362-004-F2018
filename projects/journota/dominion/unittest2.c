/*********************************************************************
** Program name: Assignment 3,Unit Testing
** Author: Aaron Journot
** Date: 10/23/18
** Description: Unit test 2 for dominion.c tests gainCard function
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
#define FUNC_NAME "gainCard"

int main (){

    srand(time(0));

    struct gameState game, test;
    int seed = (rand() % 1000);
    int players = 2;
    int kCards[10] = {feast, adventurer, cutpurse, minion, smithy, tribute, sea_hag, great_hall, baron};
    int r;
    int testCard;
    int failFlag = 0;

    initializeGame(players, kCards, seed, &game);
    
    printf("\n**********************Testing %s**********************\n", FUNC_NAME);

    // test state of supply decks
    if(TEST_PRINT){
        printf("\nTesting supply states and response:\n");
    }

    // test if card not in supply
    memcpy(&test, &game, sizeof(struct gameState));
    r = (rand() % 10);
    testCard = kCards[r];
    test.supplyCount[testCard] = 0;
    if(TEST_PRINT){
        printf("Testing with %d card count in supply: ", test.supplyCount[testCard]);
        if(gainCard(testCard, &test, 0, 1) == -1){ printf("PASSED\n"); }
        else{ printf("FAILED\n"); }
    }
    // assert(gainCard(testCard, &test, 0, 1) == -1); 
    if(gainCard(testCard, &test, 0, 1) != -1){ failFlag = 1; } 

    // test branches where card is in supply
    if(TEST_PRINT){
        printf("\nTesting with >0 card count in supply:\n");
    }

    for(unsigned int p = 0; p < players; p++){
        memcpy(&test, &game, sizeof(struct gameState));
        for(unsigned int q = 0; q < 3; q++){    /*3 = flag options*/

            // set test card
            r = (rand() % 10);
            testCard = kCards[r];

            // 0 = test adding to discard
            if(q == 0){
                if(TEST_PRINT){
                    printf("Testing adding card to discard of player %d: ", p + 1);
                }

                // assert gain card works
                // assert(gainCard(testCard, &test, q, p) == 0);
                if(gainCard(testCard, &test, q, p) != 0){ failFlag = 1; }

                // assert discard counts for each player, p should change, others should not
                for(unsigned int s = 0; s < players; s++){
                    // if(s == p){ assert(test.discardCount[s] == game.discardCount[s] + 1); }
                    // else{ assert(test.discardCount[s] == game.discardCount[s]); }
                    if(s == p){ if(test.discardCount[s] != game.discardCount[s] + 1){ failFlag = 1; }; }
                    else{ if(test.discardCount[s] != game.discardCount[s]){ failFlag = 1; }; }
                }

                // assert card is the correct card in the right position
                // assert(test.discard[p][test.discardCount[p] - 1] == testCard);
                if(test.discard[p][test.discardCount[p] - 1] != testCard){ failFlag = 1; }

                if(TEST_PRINT){
                    printf("PASSED\n");
                }
                
            }

            // 1 = test adding to deck
            if(q == 1){
                if(TEST_PRINT){
                    printf("Testing adding card to deck of player %d: ", p + 1);
                }

                // assert gain card works
                // assert(gainCard(testCard, &test, q, p) == 0);
                if(gainCard(testCard, &test, q, p) != 0){ failFlag = 1; }

                // assert deck counts for each player, p should change, others should not
                for(unsigned int s = 0; s < players; s++){
                    // if(s == p){ assert(test.deckCount[s] == game.deckCount[s] + 1); }
                    // else{ assert(test.deckCount[s] == game.deckCount[s]); }
                    if(s == p){ if(test.deckCount[s] != game.deckCount[s] + 1){ failFlag = 1; }; }
                    else{ if(test.deckCount[s] != game.deckCount[s]){ failFlag = 1; }; }
                }

                // assert card is the correct card in the right position
                // assert(test.deck[p][test.deckCount[p] - 1] == testCard);
                if(test.deck[p][test.deckCount[p] - 1] != testCard){ failFlag = 1; }

                if(TEST_PRINT){
                    printf("PASSED\n");
                }
            }

            // 2 = test adding to hand
            if(q == 2){
                if(TEST_PRINT){
                    printf("Testing adding card to hand of player %d: ", p + 1);
                }

                // assert gain card works
                // assert(gainCard(testCard, &test, q, p) == 0);
                if(gainCard(testCard, &test, q, p) != 0){ failFlag = 1; }

                // assert hand counts for each player, p should change, others should not
                for(unsigned int s = 0; s < players; s++){
                    // if(s == p){ assert(test.handCount[s] == game.handCount[s] + 1); }
                    // else{ assert(test.handCount[s] == game.handCount[s]); }
                    if(s == p){ if(test.handCount[s] != game.handCount[s] + 1){ failFlag = 1; }; }
                    else{ if(test.handCount[s] != game.handCount[s]){ failFlag = 1; }; }
                }

                // assert card is the correct card in the right position
                // assert(test.hand[p][test.handCount[p] - 1] == testCard);
                if(test.hand[p][test.handCount[p] - 1] != testCard){ failFlag = 1; }

                if(TEST_PRINT){
                    printf("PASSED\n");
                }
            }
        }

    }

    if(!failFlag){
        printf("\n**********************ALL TESTS PASSED**********************\n\n");
    } else{
        printf("\n************************TESTS FAILED************************\n\n");
    }

    return 0;
}