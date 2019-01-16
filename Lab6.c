#include <stdio.h>
#include <math.h>
#include <stdbool.h>

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
    scanf(" %c %c %c", &colour, &row, &col);
    while(positionInBounds(n, row, col) && ((colour != '!') && (row != '!') && (col != '!')))
    {
        int r = row - 'a';
        int c = col - 'a';
        board[r][c] = colour;
        scanf(" %c %c %c", &colour, &row, &col);
    }
    
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
void availableMove(char board[26][26], int n, char colour)
{
    printf("Available moves for %c:\n", colour);
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
                                    printf("%c%c\n", ('a' + row), ('a' + col));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//makes the move on board
void move(char board[26][26], int n, char colour, char row, char col, int dRow, int dCol)
{
    int r = row - 'a';
    int c = col - 'a';
    int count = 0;
    do
    {
        board[r+(count*dRow)][c+(count*dCol)] = colour;
        count++;
    }while(positionInBounds(n, (row + (count * dRow)), (col + (count * dCol))) && 
           board[r+(count*dRow)][c+(count*dCol)] != 'U' && board[r+(count*dRow)][c+(count*dCol)] != colour);
    
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

bool validMove(char board[26][26], int n)
{
    char colour;
    char row;
    char col;
    
    printf("Enter a move:\n");
    scanf(" %c %c %c", &colour, &row, &col);
    if(colour != 'B' && colour != 'W' && !(positionInBounds(n, row, col)))
    {
        printf("Invalid move.\n");
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
                                            printf("Valid move.\n");
                                            move(board, n, colour, row, col, dRow, dCol);
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
    return false;
}

int main(int argc, char **argv)
{
    int dim = 0;
    char board[26][26];
    
    printf("Enter the board dimension: ");
    scanf("%d", &dim);
    printInitBoard(board, dim);
    configure(board, dim);
    availableMove(board, dim, 'W');
    availableMove(board, dim, 'B');
    validMove(board, dim);
    
    return 0;
}
