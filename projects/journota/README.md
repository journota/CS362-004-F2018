Assignment-2 submission notes

The following changes were made:
    doninion.c
        Refactoring of the cardEffect function to call individual functions for:
            Smithy, Adventurer, Baron, Cutpurse, and Village
        Added function definitions and refactored code for each new function
    dominion_helpers.h 
        Addition of function calls to dominion_helpers header file

The following bugs were introduced for testing:
    dominion.c
        1368: state->handCount[i] was changed in order that the hand counter
        would look at the incorrect array parameters
        1394: state->coins += 4 was changed so that the player would always be reset
        to four coins instead of gaining four coins
        1446: i < 3 was changed so that the player would not be able to draw cards
        but the function would still exit properly
        1487: z-1>0 was changed so that the card at index [1] would remain in the
        player's hand