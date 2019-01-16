#include <stdio.h>
#include <math.h>
#include <stdbool.h>

//this program allows for a player and computer to play an entire reversi game
//this program utilizes the given algorithm for the computer

//print the board at start
void printInitBoard(char board[26][26], int n)
{
    printf("  ");
    int i;
    for(i = 0; i < n; i++)
    {
        printf("%c", 97+i);
    }
    printf("\n");
    int j;
    for(j = 0; j < n; j++)
    {
        printf("%c ", 97+j);
        int k;
        for(k = 0; k < n; k++)
        {
            if((j == ((n/2)-1) && k == ((n/2)-1)) || (j == (n/2) && k == (n/2)))
            {
                board[j][k] = 'W';
                printf("%c", board[j][k]);
            }
            else if((j == ((n/2)-1) && k == (n/2)) || (j == (n/2) && k == ((n/2)-1)))
            {
                board[j][k] = 'B';
                printf("%c", board[j][k]);
            }
            else
            {
                board[j][k] = 'U';
                printf("%c", board[j][k]);
            }
        }
        printf("\n");
    }
}

void printBoard(char board[26][26], int n)
{
    printf("  ");
    int i;
    for(i = 0; i < n; i++)
    {
        printf("%c", 97+i);
    }
    printf("\n");
    int j;
    for(j = 0; j < n; j++)
    {
        printf("%c ", 97+j);
        int k;
        for(k = 0; k < n; k++)
        {
            printf("%c", board[j][k]);
        }
        printf("\n");
    }
}

//checks to see if a current position is on the board
bool positionInBounds(int n, char row, char col)
{
    if(((row - 'a') <= n) && ((col - 'a') <= n) && ((row - 'a') >= 0) && ((col - 'a') >= 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//sets up the board however the user wants
void configure(char board[26][26], int n)
{
    char colour;
    char row;
    char col;
    
    printf("Enter board configuration:\n");
    scanf(" %c%c%c", &colour, &row, &col);
    while(positionInBounds(n, row, col) && ((colour != '!') && (row != '!') && (col != '!')))
    {
        int r = row - 'a';
        int c = col - 'a';
        board[r][c] = colour;
        scanf(" %c%c%c", &colour, &row, &col);
    }
    
    printBoard(board, n);
}

//checks to see if a move is legal in a certain direction
bool checkLegalInDirection(char board[26][26], int n, char row, char col, char colour, int deltaRow, int deltaCol)
{
    int r = row - 'a';
    int c = col - 'a';
    int count = 0;
    while(positionInBounds(n, ('a' + r + (count * deltaRow)), ('a' + c + (count * deltaCol))) && board[r+(count*deltaRow)][c+(count*deltaCol)] != colour && board[r+(count*deltaRow)][c+(count*deltaCol)] != 'U')
    {
        count++;
        if(positionInBounds(n, ('a' + r + (count * deltaRow)), ('a' + c + (count * deltaCol))) && board[r+(count*deltaRow)][c+(count*deltaCol)] == colour)
        {
            return true;
        }
    }
    return false;
}

//checks all available moves a player has
bool availableMove(char board[26][26], int n, char colour)
{
    //printf("Available moves for %c:\n", colour);
    int count = 0;
    int row;
    for(row = 0; row < n; row++)
    {
        int col;
        for(col = 0; col < n; col++)
        {
            if(board[row][col] == 'U')
            {
                int dRow;
                for(dRow = -1; dRow < 2; dRow++)
                {
                    int dCol;
                    for(dCol = -1; dCol < 2; dCol++)
                    {
                        if(!(dRow == 0 && dCol == 0))
                        {
                            if(positionInBounds(n, ('a' + row + dRow), ('a' + col + dCol)))
                            {
                                if(checkLegalInDirection(board, n, ('a' + row + dRow), ('a' + col + dCol), colour, dRow, dCol))
                                {
                                    //printf("%c%c\n", ('a' + row), ('a' + col));
                                    count++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(count > 0)
        return true;
    else
        return false;
}

//makes the move on board
void move(char board[26][26], int n, char colour, char row, char col)
{
    int r = row - 'a';
    int c = col - 'a';
    int dRow;
    for(dRow = -1; dRow < 2; dRow++)
    {
        int dCol;
        for(dCol = -1; dCol < 2; dCol++)
        {
            if(!(dRow == 0 && dCol == 0))
            {
                int count = 0;
                if(checkLegalInDirection(board, n, (row + dRow), (col + dCol), colour, dRow, dCol))
                {
                    do
                    {
                        board[r+(count*dRow)][c+(count*dCol)] = colour;
                        count++;
                    }while(positionInBounds(n, (row + (count * dRow)), (col + (count * dCol))) && 
                           board[r+(count*dRow)][c+(count*dCol)] != 'U' && board[r+(count*dRow)][c+(count*dCol)] != colour);
                }
            }
        }
    }
    printBoard(board, n);
}

//checks the score of placing the computer's piece on a certian position
void checkScore(char board[26][26], int n, char row, char col, char colour, int scores[], int index)
{
    int r = row - 'a';
    int c = col - 'a';
    int score = 0;
    int dRow;
    for(dRow = -1; dRow < 2; dRow++)
    {
        int dCol;
        for(dCol = -1; dCol < 2; dCol++)
        {
            if(!(dRow == 0 && dCol == 0))
            {
                int count = 0;
                while(positionInBounds(n, ('a' + r + (count * dRow)), ('a' + c + (count * dCol))) && board[r+(count*dRow)][c+(count*dCol)] != colour && 
                      board[r+(count*dRow)][c+(count*dCol)] != 'U' && board[r+(count*dRow)][c+(count*dCol)] != colour)
                {
                    count++;
                    score++;
                }
            }
        }
    }
    scores[index] = score;
}

//logic for inputting the best computer move on the board (using the given algorithm)
void computerMove(char board[26][26], int n, char colour)
{
    char rows[60] = {0};
    char cols[60] = {0};
    int scores[60] = {0};
    int count = 0;
    int row;
    for(row = 0; row < n; row++)
    {
        int col;
        for(col = 0; col < n; col++)
        {
            if(board[row][col] == 'U')
            {
                int dRow;
                for(dRow = -1; dRow < 2; dRow++)
                {
                    int dCol;
                    for(dCol = -1; dCol < 2; dCol++)
                    {
                        if(!(dRow == 0 && dCol == 0))
                        {
                            if(positionInBounds(n, ('a' + row + dRow), ('a' + col + dCol)))
                            {
                                if(checkLegalInDirection(board, n, ('a' + row + dRow), ('a' + col + dCol), colour, dRow, dCol))
                                {
                                    rows[count] = 'a' + row;
                                    cols[count] = 'a' + col;
                                    checkScore(board, n, ('a' + row + dRow), ('a' + col + dCol), colour, scores, count);
                                    count++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    int largestScore = 0;
    int index = 0;
    int i;
    for(i = 0; i <= count; i++)
    {
        if(scores[i] >= largestScore)
        {
            if(scores[i] == largestScore)
            {
                if(rows[i] <= rows[index])
                {
                    if(rows[i] == rows[index])
                    {
                        if(cols[i] <= cols[index])
                        {
                            largestScore = scores[i];
                            index = i;
                        }
                    }
                    else
                    {
                        largestScore = scores[i];
                        index = i;
                    }
                }
            }
            else
            {
                largestScore = scores[i];
                index = i;
            }
        }
    }
    char r = rows[index];
    char c = cols[index];
    printf("Computer places %c at %c%c.\n", colour, r, c);
    move(board, n, colour, r, c);
}

//logic for inputting the human player's move on the board
bool humanMove(char board[26][26], int n, char colour)
{
    char row;
    char col;
    
    printf("Enter move for colour %c (RowCol): ", colour);
    scanf(" %c%c", &row, &col);
    if(!positionInBounds(n, row, col))
    {
        printf("Invalid move.\n");
        return false;
    }
    else
    {
        int r;
        for(r = 0; r < n; r++)
        {
            int c;
            for(c = 0; c < n; c++)
            {
                if(board[r][c] == 'U')
                {
                    int dRow;
                    for(dRow = -1; dRow < 2; dRow++)
                    {
                        int dCol;
                        for(dCol = -1; dCol < 2; dCol++)
                        {
                            if(!(dRow == 0 && dCol == 0))
                            {
                                if(positionInBounds(n, ('a' + r + dRow), ('a' + c + dCol)))
                                {
                                    if(checkLegalInDirection(board, n, ('a' + r + dRow), ('a' + c + dCol), colour, dRow, dCol))
                                    {
                                        if(row == ('a' + r) && col == ('a' + c))
                                        {
                                            //printf("Valid move.\n");
                                            move(board, n, colour, row, col);
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        printf("Invalid move.\n");
    }
    return false;
}

//runs the reversi game
int main(int argc, char **argv)
{
    int dim = 0;
    char board[26][26];
    char computerColour;
    bool validMove = true;
    
    printf("Enter the board dimension: ");
    scanf(" %d", &dim);
    printf("Computer plays (B/W) : ");
    scanf(" %c", &computerColour);
    printInitBoard(board, dim);
    do
    {
        if(computerColour == 'W')
        {
            if(!availableMove(board, dim, 'W'))
            {
                validMove = humanMove(board, dim, 'B');
                if(availableMove(board, dim, 'W') || availableMove(board, dim, 'B'))
                    printf("W player has no valid move.\n");
            }
            else if(!availableMove(board, dim, 'B'))
            {
                printf("B player has no valid move.\n");
                computerMove(board, dim, computerColour);
            }
            else
            {
                validMove = humanMove(board, dim, 'B');
                if(validMove)
                    computerMove(board, dim, computerColour);
            }
        }
        else
        {
            if(!availableMove(board, dim, 'W'))
            {
                computerMove(board, dim, computerColour);
                if(availableMove(board, dim, 'W') || availableMove(board, dim, 'B'))
                    printf("W player has no valid move.\n");
            }
            else if(!availableMove(board, dim, 'B'))
            {
                if(availableMove(board, dim, 'W'))
                {
                    printf("B player has no valid move.\n");
                    validMove = humanMove(board, dim, 'W');
                }
            }
            else
            {
                computerMove(board, dim, computerColour);
                validMove = humanMove(board, dim, 'W');
            }
        }
    }while((availableMove(board, dim, 'W') || availableMove(board, dim, 'B')) && validMove);

    int b = 0;
    int w = 0;
    int i;
    for(i = 0; i < dim; i++)
    {
        int j;
        for(j = 0; j < dim; j++)
        {
            if(board[i][j] != 'U')
            {
                if(board[i][j] == 'B')
                    b++;
                else
                    w++;
            }
        }
    }
    if(b == w)
        printf("Draw!\n");
    else if (b > w)
        printf("B player wins.\n");
    else
        printf("W player wins.\n");
    
    return 0;
}
