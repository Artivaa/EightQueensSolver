#include <iostream>
#include <vector>

using namespace std;

const int Size = 8;

bool IsSafe(vector<int>& Board, int Row, int Col)
{
    for (int i = 0; i < Row; i++)
    {
        if (Board[i] == Col || (i - Row) == (Board[i] - Col) || (i - Row) == (Col - Board[i]))
        {
            return false;
        }
    }
    return true;
}

void PrintBoard(vector<int>& Board)
{
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            if (Board[i] == j)
            {
                cout << "Q ";
            }
            else
            {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

void SolveNQueens(vector<int>& Board, int Row, vector<vector<int>>& Solutions)
{
    if (Row == Size)
    {
        Solutions.push_back(Board);
        return;
    }
    for (int Col = 0; Col < Size; Col++)
    {
        if (IsSafe(Board, Row, Col))
        {
            Board[Row] = Col;
            SolveNQueens(Board, Row + 1, Solutions);
            Board[Row] = -1;
        }
    }
}

void FindSymmetricalSolutions(vector<vector<int>>& Solutions)
{
    for (auto& Solution : Solutions)
    {
        PrintBoard(Solution);
        cout << endl;
    }
}

int main()
{
    vector<int> Board(Size, -1);
    vector<vector<int>> Solutions;
    SolveNQueens(Board, 0, Solutions);
    FindSymmetricalSolutions(Solutions);
    return 0;
}
