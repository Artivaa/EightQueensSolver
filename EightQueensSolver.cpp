#include <iostream>

const int N = 8;
int Board[N][N];

// Функция для инициализации шахматной доски
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

// Функция для вывода текущего состояния доски
void PrintBoard()
{
    for (int Row = 0; Row < N; ++Row)
    {
        for (int Col = 0; Col < N; ++Col)
        {
            std::cout << (Board[Row][Col] ? "Q " : ". ");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Функция для проверки, можно ли поставить ферзя на позицию (Row, Col)
bool IsSafe(int Row, int Col)
{
    for (int i = 0; i < Row; ++i)
    {
        // Проверка столбца
        if (Board[i][Col])
        {
            return false;
        }

        // Проверка диагонали (\)
        if (Col - (Row - i) >= 0 && Board[i][Col - (Row - i)])
        {
            return false;
        }

        // Проверка диагонали (/)
        if (Col + (Row - i) < N && Board[i][Col + (Row - i)])
        {
            return false;
        }
    }
    return true;
}

// Массив, задающий порядок обхода столбцов, чтобы прийти к нужной расстановке
int ColOrder[N] = { 4, 2, 0, 6, 1, 7, 5, 3 };

// Функция для решения задачи о 8 ферзях
bool SolveNQueens(int Row)
{
    if (Row == N)
    {
        // Решение найдено; выводим доску
        std::cout << "Решение найдено:" << std::endl;
        PrintBoard();
        return true;
    }

    // Перебираем столбцы в заданном порядке
    for (int k = 0; k < N; ++k)
    {
        int Col = ColOrder[k];
        if (IsSafe(Row, Col))
        {
            Board[Row][Col] = 1;
            std::cout << "Размещаем ферзя на позиции (" << Row << ", " << Col << "):" << std::endl;
            PrintBoard();

            if (SolveNQueens(Row + 1))
            {
                return true;
            }

            // Если установка ферзя не привела к решению, откатываемся
            Board[Row][Col] = 0;
            std::cout << "Убираем ферзя с позиции (" << Row << ", " << Col << "):" << std::endl;
            PrintBoard();
        }
    }
    return false;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    InitializeBoard();
    if (!SolveNQueens(0))
    {
        std::cout << "Решение не найдено." << std::endl;
    }
    return 0;
}
