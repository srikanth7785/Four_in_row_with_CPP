#include<iostream>
using namespace std;

string winner = "none";
string grid[7][7];

void create()
{
    for(int i = 0 ; i < 7; i++)
    {
        for(int j = 0 ; j < 7; j++)
        {
            grid[i][j] = '_';
        }
    }
}

void display()
{
    cout << "1\t2\t3\t4\t5\t6\t7\n";
    for(int i = 0 ; i < 7 ; i++)
    {
        for(int j = 0 ; j < 7; j++)
        {
            cout << grid[i][j] << "\t";
        }
        cout << endl << endl;
    }
}

int insert(int col, int player)
{
    int i;
    for(i = 0 ; i < 7; i++)
    {
        if(grid[i][col] != "_")
        break;
    }
    if(i == 0)
    {
        cout << "Invalid Input..Please Enter valid Input..!";
        return 0;
    }
    else
    {
        grid[i-1][col] = player == 1 ? 'G' : 'R';
        return 1;
    }
}

int north(int row,int col)
{
    // cout << endl << "north" << row << " " << col << endl;
    return row > 2 ? grid[row][col] == grid[row-1][col] && grid[row-1][col] == grid[row-2][col] && grid[row-2][col] == grid[row-3][col] : 0;
}

int east(int row,int col)
{
    // cout << "east" << row << " " << col << endl;
    return col < 5 ? grid[row][col] == grid[row][col+1] && grid[row][col+1] == grid[row][col+2] && grid[row][col+2] == grid[row][col+3] : 0;
}

int northeast(int row,int col)
{
    // cout << "northeast" << row << " " << col << endl;
    return row > 2 && col < 5 ? grid[row][col] == grid[row-1][col+1] && grid[row-1][col+1] == grid[row-2][col+2] && grid[row-2][col+2] == grid[row-3][col+3] : 0;
}

int northwest(int row,int col)
{
    // cout << "northwest" << row << " " << col << endl;
    return row > 2 && col > 2 ? grid[row][col] == grid[row-1][col-1] && grid[row-1][col-1] == grid[row-2][col-2] && grid[row-2][col-2] == grid[row-3][col-3] : 0;
}

int checkWinner()
{
    cout << "Checking Winner" << endl;
    for(int i = 6 ; i >= 3 ; i--)
    {
        for(int j = 0 ; j < 7; j++)
        {
            int complete = 0;


            if(grid[i][j] != "_")
            {
                complete = complete || north(i,j);

                if(j <= 3)
                {
                    complete = complete || east(i,j);
                    complete = complete || northeast(i,j);
                }

                if(j >= 3)
                {
                    complete = complete || northwest(i,j);
                }

                if(complete == 1)
                {
                    winner = grid[i][j] == "G" ? "Green" : "Red";
                    return 1;
                }
            }

        }
    }
    return 0;
}

int main()
{
    int currentPlayer = 1,isInserted;
    int empty_cells = 49;
    int col;
    create();
    while(empty_cells > 0 && winner == "none")
    {
        display();
        cout << "Empty cells : " << empty_cells << endl;
        cout << "Enter Column to insert Player" << currentPlayer << " coin : " ;
        cin >> col;
        col = col - 1;
        if(col < 7)
        {
            isInserted = insert(col,currentPlayer);
            cout << "Inserted or not : " << isInserted << endl;
            empty_cells = isInserted ? --empty_cells : empty_cells;
            if(empty_cells < 43)
            checkWinner();
            currentPlayer = currentPlayer == 1 ? 2 : 1;
        }
        else
        {
            cout << "Invalid Input..Please give a valid Input\n" ;
        }
    }
    if(winner == "none")
    {
        cout << "DRAW Match" << endl;
        display();
    }
    else
    {
        cout << winner << " is winner...^__^ ^__^" << endl;
        display();
    }   
    return 0;
}