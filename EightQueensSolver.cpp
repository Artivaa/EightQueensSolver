#include <iostream>
#include <limits>

using namespace std;

const int N = 8;
int Board[N][N];

// Инициализация доски
void InitializeBoard()
{
    for (int Row = 0; Row < N; ++Row)
    {
        for (int Col = 0; Col < N; ++Col)
        {
            Board[Row][Col] = 0;
        }
    }
}

// Вывод доски
void PrintBoard()
{
    for (int Row = 0; Row < N; ++Row)
    {
        for (int Col = 0; Col < N; ++Col)
        {
            cout << (Board[Row][Col] ? "Q " : ". ");
        }
        cout << endl;
    }
    cout << endl;
}

// Проверка безопасности позиции (Row, Col)
bool IsSafe(int Row, int Col)
{
    for (int i = 0; i < Row; ++i)
    {
        if (Board[i][Col])
        {
            return false; // Проверка столбца
        }
        if (Col - (Row - i) >= 0 && Board[i][Col - (Row - i)])
        {
            return false; // Проверка диагонали (\)
        }
        if (Col + (Row - i) < N && Board[i][Col + (Row - i)])
        {
            return false; // Проверка диагонали (/)
        }
    }
    return true;
}

// Решение задачи о N ферзях с начальным положением
bool SolveNQueens(int Row)
{
    if (Row == N)
    {
        cout << "Решение найдено:" << endl;
        PrintBoard();
        return true;
    }

    for (int Col = 0; Col < N; ++Col)
    {
        if (IsSafe(Row, Col))
        {
            Board[Row][Col] = 1;
            cout << "Размещаем ферзя на позиции (" << Row << ", " << Col << "):" << endl;
            PrintBoard();

            if (SolveNQueens(Row + 1))
            {
                return true;
            }

            Board[Row][Col] = 0; // Откат
            cout << "Убираем ферзя с позиции (" << Row << ", " << Col << "):" << endl;
            PrintBoard();
        }
    }
    return false;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    InitializeBoard();

    int initialCol;
    cout << "Введите столбец (0-" << N - 1 << ") для первого ферзя: ";
    cin >> initialCol;

    if (cin.fail() || initialCol < 0 || initialCol >= N)
    {
        cout << "Неверный ввод." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 1;
    }

    if (IsSafe(0, initialCol))
    {
        Board[0][initialCol] = 1;
        cout << "Начальное положение ферзя на позиции (0, " << initialCol << "):" << endl;
        PrintBoard();

        if (!SolveNQueens(1))
        {
            cout << "Решение не найдено." << endl;
        }
    }
    else
    {
        cout << "Начальное положение небезопасно (невозможно в первой строке)." << endl;
    }

    return 0;
}