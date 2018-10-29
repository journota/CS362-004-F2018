#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // create an array of characters with all applicable characters in test plus one
    char c[10] = {'[','(','{',' ','a','x','}',')',']','*'};
    // use rand to generate a random int between 0-9
    int i = rand() % 10;
    // return the randomly-generated character
    return c[i];
}

char *inputString()
{
    // create an array of characters with all applicable characters in test plus one (excluding '\0')
    char c[5] = {'r','e','s','t','p'};
    // create a second character array that will randomly build the final string
    char *cstring = malloc(sizeof(char) * 6);
    // loop through all 6 characters in the string and assign a random letter
    unsigned int i;
    for (i = 0; i < 5; i++){
      cstring[i] = c[(rand() % 5)];
    }
    // append '\0' to the end of the character string
    cstring[5] = '\0';
    return cstring;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
