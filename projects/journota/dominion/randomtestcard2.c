/*********************************************************************
** Program name: Assignment 4, Random Testing
** Author: Aaron Journot
** Date: 11/14/18
** Description: Random test 1 for dominion.c tests great hall implementation
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

#define TEST_PRINT 0
#define CARD_NAME "Great Hall"
#define TEST_COUNT 50
#define CARD_LIMIT 50
#define HAND_LIMIT 5

int main (){

    // test counter & static vars
    srand(time(0));
    unsigned int d; 
    struct gameState game, test;
    int supply[17];
    int tSupply[17];
    int bonus = 0;
    int cardDelta = 1;
    int discard = 1;
    int p = 0;
    int handPos = 0;
    int failCtr = 0;

    // randomization of kingdom cards does not matter as they do not affect the outcome of the affects of great hall
    int kCards[10] = {feast, adventurer, cutpurse, minion, smithy, tribute, sea_hag, great_hall, baron};

    // randomization of choice does not matter as these do not affect great hall
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;

    // set randomization seed
    int seed = (rand() % 1000);

    // print header
    printf("\n**********************Testing %s**********************\n", CARD_NAME);

    // random test loop
    for (d = 0; d < TEST_COUNT; d++){

        // randomize plyers (2-4)
        int players = (2 + rand() % 3);

        // initialize base game state
        initializeGame(players, kCards, seed, &game);

        // initialize variables with static or indetermined values
        int failFlag = 0;
        unsigned int i, j, k, m, n;
        int actionDelta = 1;

        // determine victory cards
        // int victoryCards;
        // if (players == 2){
        //     victoryCards = 8;
        // } else{
        //     victoryCards = 12;
        // }

        // determine cardpool (10*n-1 curse; 230 copper, silver, gold, kingdom; 3*n starting estate, 3*victoryCards)
        // int cardPool = ((10 * (players - 1)) + 230 + (3 * players) + (3 * victoryCards));

        // initialize player states with random counts and cards
        for (m = 0; m < players; m++){

            // number of cards in player's hand can differ due to multiple actions or cards that result in a discard (e.g. cutpurse)
            game.handCount[m] = (1 + rand() % HAND_LIMIT);

            // initialize other counts
            game.deckCount[m] = (10 + rand() % CARD_LIMIT);
            game.discardCount[m] = (10 + rand() % CARD_LIMIT);

            // set hand
            for (n = 0; n < game.handCount[m]; n++){
                int tempCard = rand() % 17;
                // if 0th position card, set cutpurse, if 0-7, set from base cards,
                // otherwise set from in-game kingdom cards
                if (n == 0){
                    game.hand[m][n] = cutpurse;
                } else if (tempCard < 7){
                    game.hand[m][n] = tempCard;
                } else{
                    game.hand[m][n] = kCards[tempCard];
                }
            }

            // set deck
            for (n = 0; n < game.deckCount[m]; n++){
                int tempCard = rand() % 17;
                // if 0-7, set from base cards, otherwise set from in-game kingdom cards
                if (tempCard < 7){
                    game.deck[m][n] = tempCard;
                } else{
                    game.deck[m][n] = kCards[tempCard];
                }
            }

            // set discard
            for (n = 0; n < game.discardCount[m]; n++){
                int tempCard = rand() % 17;
                // if 0-7, set from base cards, otherwise set from in-game kingdom cards
                if (tempCard < 7){
                    game.discard[m][n] = tempCard;
                } else{
                    game.discard[m][n] = kCards[tempCard];
                }
            }
        }

        // copy game state
        memcpy(&test, &game, sizeof(struct gameState));

        // play card
        cardEffect(great_hall, choice1, choice2, choice3, &test, handPos, &bonus);

        // test number of cards gained, number of cards drawn from deck, and state of other players
        if(TEST_PRINT){
        printf("\nTesting player states:\n");
        }
        
        for(i = p, j = 0; j < players; i++, j++){
            if(i >= players) { i = 0; }

            if(i == p){
                if(TEST_PRINT){
                    printf("Player %d State (Hand|Deck|Played|Discard): Expected - %d|%d|%d|%d Actual - %d|%d|%d|%d\n",
                    (i + 1), (game.handCount[i] + cardDelta - discard), (game.deckCount[i] - cardDelta),
                    (game.playedCardCount + discard), game.discardCount[i],
                    test.handCount[i], test.deckCount[i], test.playedCardCount, test.discardCount[i]);
                }
                if((game.handCount[i] + cardDelta - discard) != test.handCount[i]){ failFlag = 1; }
                if((game.deckCount[i] - cardDelta) != test.deckCount[i]){ failFlag = 1; }
                if((game.playedCardCount + discard) != test.playedCardCount){ failFlag = 1; }
                if(game.discardCount[i] != test.discardCount[i]){ failFlag = 1; }
            }
            else{
                if(TEST_PRINT){
                    printf("Player %d State (Hand|Deck|Discard): Expected - %d|%d|%d Actual - %d|%d|%d\n",
                    (i + 1), game.handCount[i], game.deckCount[i], game.discardCount[i],
                    test.handCount[i], test.deckCount[i], test.discardCount[i]);
                }
                if(game.handCount[i] != test.handCount[i]){ failFlag = 1; }
                if(game.deckCount[i] != test.deckCount[i]){ failFlag = 1; }
                if(game.discardCount[i] != test.discardCount[i]){ failFlag = 1; }
            }
        }

        // test that cards gained were treasure and that discarded cards were not
        if(TEST_PRINT){
            printf("\nTesting actions gained:\n");
        }
        // assert(actionDelta == (test.numActions - game.numActions));
        if(actionDelta != (test.numActions - game.numActions)){ failFlag = 1; }
        if(TEST_PRINT){
            printf("Actions Gained: Expected - %d Actual - %d\n", actionDelta, test.numActions - game.numActions);
        }
        
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
        if(failFlag){
            failCtr++;
        }
    }

    printf("Tests: Total - %d Passed - %d Failed - %d\n\n", TEST_COUNT, (TEST_COUNT - failCtr), failCtr);

    return 0;
}