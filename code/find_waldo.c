/******************************************************************************************
*Assignment Name:    Lab 3: Find Waldo Game
*Course:             C Language CST8234
*Source Files:       find_waldo.c
******************************************************************************************/

/******************************************************************************************
*Filename:           find_waldo.c
*Version:            1
*Course:             C Language CST8234
*Assignment Name:    Lab 2: Decrypt
*Purpose:            Create a game to find waldo in a two dimensional array
******************************************************************************************/

#include "find_waldo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * This uses the kickstarter code provided.
 * Kick-start code for the Find Waldo Game
 *
 * @author Gerald.Hurdle@AlgonquinCollege.com
 *
 */

int gWaldoColumn;
int gWaldoRow;

/******************************************************************************************
*Function name:              main
*Purpose:                    Main function for the program - Find waldo game
*Function In parameters:     None
*Function Out parameters:    An integer for function success
*Version:                    1
*Author:                     mos & Gerald Hurdle
******************************************************************************************/
int main()
{
  char world[MAX_ROWS][MAX_COLS];
  int rounds = -1;
  int i;
  int rowGuess;
  int colGuess;
  int returnCode;

  /* Intialize for rand() function; should only be called once. */
  srand(time(NULL));

  resetWorld(world);

  /* set waldos position, make sure it is not at debug position outside of debug */
  gWaldoRow = hideWaldoAtRow();
  gWaldoColumn = hideWaldoAtColumn();
#ifdef DEBUG
  /* do nothing */
#else
  while (gWaldoRow == DEBUG_ROW)
  {
    gWaldoRow = hideWaldoAtRow();
  }
  while (gWaldoColumn == DEBUG_COL)
  {
    gWaldoColumn = hideWaldoAtColumn();
  }
#endif

  /* ask for rounds needed and validate */
  while ((rounds < 1) || (rounds > MAX_ROUNDS))
  {
    rounds = -1;
    printf("Enter the number of rounds you need to find Waldo (0 to quit; 10 max): ");
    returnCode = scanf("%d", &rounds);
    /* validate */
    if (returnCode != 1)
    {
      printf("Error - enter number of rounds between 1 and 10 \n");
      rounds = -1;
    }
    else if (rounds == 0)
    {
      return EXIT_FAILURE;
    }
    else if ((rounds < 1) || (rounds > MAX_ROUNDS))
    {
      printf("Error - enter number of rounds between 1 and 10 \n");
    }
    while (getchar() != '\n')
      ;
  }

  /* print world then ask for guesses */
  printWorld(world);

  for (i = 1; i <= rounds; i++)
  {
    rowGuess = -1;
    /* ask for guesses and validate */
    while ((rowGuess == -1))
    {
      printf("\nRound %d of %d. Enter row and column (control-d to quit): ", i, rounds);
      returnCode = scanf("%d %d", &rowGuess, &colGuess);

      if (returnCode == EOF)
      {
        printf("Control-D\n");
        return EXIT_FAILURE;
      }

      /* validate */
      if (returnCode != 2)
      {
        printf("Error - enter a row (int) and column (int). \n");
        rowGuess = -1;
      }
      else if (rowGuess == -1 && colGuess == -1)
      {
        printf("Hint: %d %d\n", gWaldoRow, gWaldoColumn);
      }
      else if (rowGuess < 1 || rowGuess > MAX_ROWS)
      {
        printf("Error: row must be in the range 1 to 10 \n");
        rowGuess = -1;
      }
      else if (colGuess < 1 || colGuess > MAX_COLS)
      {
        printf("Error: column must be in the range 1 to 10 \n");
        rowGuess = -1;
      }

      while (getchar() != '\n')
      {
      }
    }
    /* check if the guess is correct correct */
    if (isWaldoAt(world, rowGuess, colGuess) == 0)
    {
      printWorld(world);
      printf("Miss!\n");
    }
    else
    {
      printWorld(world);
      printf("Huzzah... you found Waldo!\n");
      return EXIT_SUCCESS;
    }
  }

  /* if rounds end and reach here, failed to find waldo */
  printf("LOST - you can't find Waldo in %d round like you said.\n", rounds);
  return EXIT_FAILURE;
}

/******************************************************************************************
*Function name:              hideWaldoAtColumn
*Purpose:                    Returns a column position to hide Waldo at
*Function In parameters:     None
*Function Out parameters:    An int for the column position
*Version:                    1
*Author:                     mos & Gerald Hurdle
******************************************************************************************/
int hideWaldoAtColumn()
{
#ifdef DEBUG
  return DEBUG_COL;
#else
  /* returns a random number up to max column size for positioning */
  int position;
  position = rand() % (MAX_COLS + 1);
  return position;
#endif
}

/******************************************************************************************
*Function name:              hideWaldoAtRow
*Purpose:                    Returns a row position to hide Waldo at
*Function In parameters:     None
*Function Out parameters:    An int for the row position
*Version:                    1
*Author:                     mos & Gerald Hurdle
******************************************************************************************/
int hideWaldoAtRow()
{
#ifdef DEBUG
  return DEBUG_ROW;
#else
  /* returns a random number up to max column size for positioning */
  int position;
  position = rand() % (MAX_COLS + 1);
  return position;
#endif
}

/******************************************************************************************
*Function name:              isWaldoAt
*Purpose:                    Compares the guessed column and row position to waldos position and changes the array accordingly
*Function In parameters:     Array of stars, the guessed row, the guessed column
*Function Out parameters:    An integer for guess success
*Version:                    1
*Author:                     mos & Gerald Hurdle
******************************************************************************************/
int isWaldoAt(char world[][MAX_COLS], int row, int column)
{
  /* If waldo is at the position, change it to W return 1, otherwise m and 0 */
  if (row == gWaldoRow && column == gWaldoColumn)
  {
    world[row - 1][column - 1] = 'W';
    return 1;
  }

  world[row - 1][column - 1] = 'm';
  return 0;
}

/******************************************************************************************
*Function name:              printWorld
*Purpose:                    Prints the supplied array
*Function In parameters:     The array to print
*Function Out parameters:    None
*Version:                    1
*Author:                     mos & Gerald Hurdle
******************************************************************************************/
void printWorld(char world[][MAX_COLS])
{
  int c;
  int r;

  /* prints heading then world */
  printf("   ");
  for (r = 1; r < MAX_COLS; r++)
  {
    printf("%2d ", r);
  }
  printf(" %2d\n", MAX_COLS);

  for (r = 0; r < MAX_ROWS; r++)
  {
    printf("%2d ", (r + 1));
    for (c = 0; c < MAX_COLS; c++)
    {
      printf(" %c ", world[r][c]);
    }
    printf("\n");
  }
}

/******************************************************************************************
*Function name:              resetWorld
*Purpose:                    Populates the array with stars
*Function In parameters:     The array to change
*Function Out parameters:    None
*Version:                    1
*Author:                     mos & Gerald Hurdle
******************************************************************************************/
void resetWorld(char world[][MAX_COLS])
{
  int c;
  int r;
  /* uses a for loop to put a star in each index */
  for (r = 0; r < MAX_ROWS; r++)
  {
    for (c = 0; c < MAX_COLS; c++)
    {
      world[r][c] = '*';
    }
  }
}
