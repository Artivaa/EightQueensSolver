#include <iostream>
#include <limits>

using namespace std;

const int BOARD_SIZE = 8; // Размер доски N x N
int Board[BOARD_SIZE][BOARD_SIZE]; // Статический массив для представления доски

// Функция для инициализации доски
void initializeBoard()
{
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            Board[row][col] = 0; // 0 означает, что клетка пуста
        }
    }
}

// Функция для вывода текущего состояния доски в консоль
void printBoard()
{
    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            cout << (Board[row][col] ? "Q " : ". "); // Q - ферзь, . - пустая клетка
        }
        cout << endl;
    }
    cout << endl;
}

// Функция для проверки, безопасно ли разместить ферзя в позиции (row, col)
bool isSafe(int row, int col)
{
    // Проверка столбца выше текущей строки
    for (int i = 0; i < row; ++i)
    {
        if (i >= 0 && i < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && Board[i][col])
        {
            return false; // Найден ферзь в том же столбце
        }
    }

    // Проверка диагонали вверх влево
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j)
    {
        if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && Board[i][j])
        {
            return false; // Найден ферзь на диагонали
        }
    }

    // Проверка диагонали вверх вправо
    for (int i = row, j = col; i >= 0 && j < BOARD_SIZE; --i, ++j)
    {
        if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && Board[i][j])
        {
            return false; // Найден ферзь на диагонали
        }
    }

    return true; // Позиция безопасна
}

// Рекурсивная функция для решения задачи о N ферзях
bool solveNQueens(int row)
{
    if (row == BOARD_SIZE)
    {
        cout << "Решение найдено:" << endl;
        printBoard();
        return true; // Все ферзи успешно размещены
    }

    for (int col = 0; col < BOARD_SIZE; ++col)
    {
        if (isSafe(row, col))
        {
            Board[row][col] = 1; // Размещаем ферзя
            cout << "Размещаем ферзя на позиции (" << row << ", " << col << "):" << endl;
            printBoard();

            if (solveNQueens(row + 1))
            {
                return true; // Если удалось разместить ферзей в следующих строках, решение найдено
            }

            Board[row][col] = 0; // Откат: убираем ферзя и пробуем следующий столбец
            cout << "Убираем ферзя с позиции (" << row << ", " << col << "):" << endl;
            printBoard();
        }
    }
    return false; // Если в текущей строке не удалось найти безопасную позицию, решения нет
}

int main()
{
    setlocale(LC_ALL, "Rus"); // Хотя в коде все на английском, эта строка оставлена для совместимости, если locale важна

    initializeBoard(); // Инициализация статической доски

    int initialCol;
    cout << "Введите столбец (0-" << BOARD_SIZE - 1 << ") для первого ферзя: ";
    cin >> initialCol;

    // Проверка ввода пользователя
    if (cin.fail() || initialCol < 0 || initialCol >= BOARD_SIZE)
    {
        cout << "Неверный ввод. Пожалуйста, введите число от 0 до " << BOARD_SIZE - 1 << "." << endl;
        cin.clear(); // Сброс флагов ошибок
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера ввода
        return 1; // Выход с кодом ошибки
    }

    if (isSafe(0, initialCol))
    {
        Board[0][initialCol] = 1; // Размещаем первого ферзя в указанном столбце первой строки
        cout << "Начальное положение ферзя на позиции (0, " << initialCol << "):" << endl;
        printBoard();

        if (!solveNQueens(1))
        {
            cout << "Решение не найдено." << endl;
        }
    }
    else
    {
        cout << "Начальное положение небезопасно (невозможно в первой строке)." << endl;
    }

    return 0; // Успешное завершение программы
}