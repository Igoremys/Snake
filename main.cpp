//main.cpp
#include "SnakeGame.h"
using namespace std;

// Конструктор класса SnakeGame
SnakeGame::SnakeGame(int w, int h) : width(w), height(h) {}

// Настройка начальных параметров игры
void SnakeGame::Setup() {
    // Инициализация переменных
    gameOver = false;
    doorOpened = false;
    victory = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    ballActive = true;
    ballX = rand() % width;
    ballY = rand() % height;
    score = 0;
    nTail = 0;
    playerName = "";
    ballDirX = 1;
    ballDirY = 1;
    lastFruitTime = time(0);
}

// Отрисовка игрового поля
void SnakeGame::Draw() {
    system("cls"); // Очистка экрана консоли
    // Отрисовка верхней границы
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    // Отрисовка игрового поля и объектов на нем
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O"; // Змейка
            else if (i == fruitY && j == fruitX)
                cout << "F"; // Фрукт
            else if (i == ballY && j == ballX && ballActive)
                cout << "B"; // Мяч
            else if (i == 0 && j == width / 2 && doorOpened)
                cout << "D"; // Дверь
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o"; // Хвост змейки
                        print = true;
                    }
                }
                if (!print)
                    cout << " "; // Пустое пространство
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    // Отрисовка нижней границы и информации о счете и имени игрока
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
    cout << "Player: " << playerName << endl;

    // Вывод сообщения о победе или поражении
    if (victory)
    {
        cout << "Победа!" << endl;
    }
    else if (gameOver)
    {
        cout << "Поражение!" << endl;
    }
}

// Обработка ввода пользователя
void SnakeGame::Input() {
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

// Ввод имени игрока
void SnakeGame::InputName() {
    cout << "Введите ваш никнейм: ";
    cin >> playerName;
}

// Перезапуск игры
void SnakeGame::Restart() {
    gameOver = false;
    doorOpened = false;
    victory = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    SaveResults(); // Сохраняем результаты перед сбросом
    score = 0;
    nTail = 0;
    playerName = "";
    InputName();
}

// Логика игры
void SnakeGame::Logic() {
    // Обновление положения хвоста змейки
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Обработка ввода направления движения змейки
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // Проверка на столкновение с границами поля
    if (x >= width || x < 0 || y >= height || y < 0)
    {
        gameOver = true;
        Draw();
    }

    // Проверка на столкновение с хвостом змейки
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
            Draw();
        }

    // Проверка на съедание фрукта
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        lastFruitTime = time(0);
        nTail++;
    }

    // Проверка на появление нового фрукта через определенное время
    if (time(0) - lastFruitTime > 10)
    {
        fruitX = rand() % width;
        fruitY = rand() % height;
        lastFruitTime = time(0);
    }

    // Проверка на столкновение с мячом
    if (x == ballX && y == ballY && ballActive)
    {
        gameOver = true;
        Draw();
    }


    // Проверка на открытие двери
    if (score >= 20)
        doorOpened = true;

    // Проверка на достижение змейкой двери
    if (doorOpened && x == width / 2 && y == 0)
    {
        victory = true;
        gameOver = true;
        Draw();
    }

    // Движение мяча
    if (ballActive)
    {
        ballX += ballDirX;
        ballY += ballDirY;

        // Проверка на столкновение мяча с границами поля
        if (ballX >= width || ballX < 0)
        {
            ballDirX = -ballDirX;
        }
        if (ballY >= height || ballY < 0)
        {
            ballDirY = -ballDirY;
        }
    }
}

// Запуск игры
void SnakeGame::RunGame() {
    Setup();
    InputName();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(10); // Задержка для управления скоростью игры

        // Перезапуск игры при завершении
        if (gameOver) {
            SaveResults(); // Сохраняем результаты перед завершением игры
            cout << "Хотите сыграть еще раз? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                Restart();
            }
        }
    }
}

// Главная функция программы
int main() {
    setlocale(LC_ALL, "Rus"); // Установка локали для корректного отображения текста на русском языке
    SnakeGame game(30, 15); // Создание объекта игры
    game.RunGame(); // Запуск игры
    return 0;
}