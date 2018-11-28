/*********************************************************************
** Program name: Assignment 3,Unit Testing
** Author: Aaron Journot
** Date: 10/23/18
** Description: Unit test 1 for dominion.c tests adventurer implementation
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
#define CARD_NAME "Adventurer"

int main (){

    srand(time(0));

    struct gameState game, test;
    int seed = (rand() % 1000);
    int players = 2;
    int kCards[10] = {feast, adventurer, cutpurse, minion, smithy, tribute, sea_hag, great_hall, baron};
    int p = 0;
    unsigned int i, j, k;
    int supply[17];
    int tSupply[17];
    int failFlag = 0;

    int handPos = 0;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int bonus = 0;
    int cardDelta = 2;
    int discard = 1;
    int treasureDelta = 0;
    int treasureDiscard = 0;

    initializeGame(players, kCards, seed, &game);
    
    printf("\n**********************Testing %s**********************\n", CARD_NAME);

    memcpy(&test, &game, sizeof(struct gameState));
    cardEffect(adventurer, choice1, choice2, choice3, &test, handPos, &bonus);    

    // test number of cards gained, number of cards drawn from deck, and state of other players
    if(TEST_PRINT){
        printf("\nTesting player states:\n");
    }
    
    for(i = p, j = 0; j < players; i++, j++){
        if(i >= players) { i = 0; }

        if(i == p){
            if(TEST_PRINT){
                printf("Player %d State (Hand|Played|Deck+Discard): Expected - %d|%d|%d Actual - %d|%d|%d\n",
                (i + 1), (game.handCount[i] + cardDelta - discard), 
                (game.playedCardCount + discard), (game.discardCount[i] + game.deckCount[i] - cardDelta),
                test.handCount[i], test.playedCardCount, (test.deckCount[i] + test.discardCount[i]));
            }
            // assert((game.handCount[i] + cardDelta - discard) == test.handCount[i]);
            // assert((game.deckCount[i] + (game.discardCount[i] - test.discardCount[i]) - cardDelta) == test.deckCount[i]);
            // assert((game.playedCardCount + discard) == test.playedCardCount);
            // assert((game.discardCount[i] + (game.deckCount[i] - test.deckCount[i]) - cardDelta) == test.discardCount[i]);
            if((game.handCount[i] + cardDelta - discard) != test.handCount[i]){ failFlag = 1; }
            if((game.playedCardCount + discard) != test.playedCardCount){ failFlag = 1; }
            if((game.discardCount[i] + game.deckCount[i] - cardDelta) != (test.discardCount[i] + test.discardCount[i])){ failFlag = 1; }
        }
        else{
            if(TEST_PRINT){
                printf("Player %d State (Hand|Deck|Discard): Expected - %d|%d|%d Actual - %d|%d|%d\n",
                (i + 1), game.handCount[i], game.deckCount[i], game.discardCount[i],
                test.handCount[i], test.deckCount[i], test.discardCount[i]);
            }
            // assert(game.handCount[i] == test.handCount[i]);
            // assert(game.deckCount[i] == test.deckCount[i]);
            // assert(game.discardCount[i] == test.discardCount[i]);
            if(game.handCount[i] != test.handCount[i]){ failFlag = 1; }
            if(game.deckCount[i] != test.deckCount[i]){ failFlag = 1; }
            if(game.discardCount[i] != test.discardCount[i]){ failFlag = 1; }
        }
    }

    // test that cards gained were treasure and that discarded cards were not
    if(TEST_PRINT){
        printf("\nTesting cards gained and discarded:\n");
    }

    for(i = 1; i <= cardDelta; i++){
        int temp = test.hand[p][test.handCount[p] - i];
        if(temp == copper || temp == silver || temp == gold){
            treasureDelta++;
        }
    }

    if(TEST_PRINT){
        printf("Treasures Gained: Expected - %d Actual - %d\n", 2, treasureDelta);
    }
    // assert(treasureDelta == 2);
    if(treasureDelta != 2){ failFlag = 1; }

    for(i = 0; i < test.playedCardCount; i++){
        int temp = test.playedCards[i];
        if(temp == copper || temp == silver || temp == gold){
            treasureDiscard++;
        }
    }

    if(TEST_PRINT){
        printf("Treasures Discarded: Expected - %d Actual - %d\n", 0, treasureDiscard);
    }
    // assert(treasureDiscard == 0);
    if(treasureDiscard != 0){ failFlag = 1; }

    // test state of supply decks
    if(TEST_PRINT){
        printf("\nTesting supply states:\n");
    }

    for(k = 0; k < 17; k++){
        // 0-6 are the base cards
        if(k < 7){
            supply[k] = game.supplyCount[k];
            tSupply[k] = test.supplyCount[k];
        }
        // cards 7-16 are the kingdom cards and are referenced by the kCards[] array
        else if(k >= 7){
            supply[k] = game.supplyCount[kCards[k]];
            tSupply[k] = test.supplyCount[kCards[k]];
        }
    }

    if(TEST_PRINT){
        printf("Supply Card State: Expected - NO CHANGE Actual - ");
        if(memcmp(supply, tSupply, sizeof(supply)) == 0){
            printf("NO CHANGE\n");
        } else{
            printf("CHANGE INDICATED\n");
        }
    }
    // assert(memcmp(supply, tSupply, sizeof(supply)) == 0);
    if(memcmp(supply, tSupply, sizeof(supply)) != 0){ failFlag = 1; }

    // test results
    if(!failFlag){
        printf("\n**********************ALL TESTS PASSED**********************\n\n");
    } else{
        printf("\n************************TESTS FAILED************************\n\n");
    }

    return 0;
}
