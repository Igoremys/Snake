//main.cpp
#include "SnakeGame.h"
using namespace std;

// ����������� ������ SnakeGame
SnakeGame::SnakeGame(int w, int h) : width(w), height(h) {}

// ��������� ��������� ���������� ����
void SnakeGame::Setup() {
    // ������������� ����������
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

// ��������� �������� ����
void SnakeGame::Draw() {
    system("cls"); // ������� ������ �������
    // ��������� ������� �������
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    // ��������� �������� ���� � �������� �� ���
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O"; // ������
            else if (i == fruitY && j == fruitX)
                cout << "F"; // �����
            else if (i == ballY && j == ballX && ballActive)
                cout << "B"; // ���
            else if (i == 0 && j == width / 2 && doorOpened)
                cout << "D"; // �����
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o"; // ����� ������
                        print = true;
                    }
                }
                if (!print)
                    cout << " "; // ������ ������������
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    // ��������� ������ ������� � ���������� � ����� � ����� ������
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
    cout << "Player: " << playerName << endl;

    // ����� ��������� � ������ ��� ���������
    if (victory)
    {
        cout << "������!" << endl;
    }
    else if (gameOver)
    {
        cout << "���������!" << endl;
    }
}

// ��������� ����� ������������
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

// ���� ����� ������
void SnakeGame::InputName() {
    cout << "������� ��� �������: ";
    cin >> playerName;
}

// ���������� ����
void SnakeGame::Restart() {
    gameOver = false;
    doorOpened = false;
    victory = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    SaveResults(); // ��������� ���������� ����� �������
    score = 0;
    nTail = 0;
    playerName = "";
    InputName();
}

// ������ ����
void SnakeGame::Logic() {
    // ���������� ��������� ������ ������
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

    // ��������� ����� ����������� �������� ������
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

    // �������� �� ������������ � ��������� ����
    if (x >= width || x < 0 || y >= height || y < 0)
    {
        gameOver = true;
        Draw();
    }

    // �������� �� ������������ � ������� ������
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
            Draw();
        }

    // �������� �� �������� ������
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        lastFruitTime = time(0);
        nTail++;
    }

    // �������� �� ��������� ������ ������ ����� ������������ �����
    if (time(0) - lastFruitTime > 10)
    {
        fruitX = rand() % width;
        fruitY = rand() % height;
        lastFruitTime = time(0);
    }

    // �������� �� ������������ � �����
    if (x == ballX && y == ballY && ballActive)
    {
        gameOver = true;
        Draw();
    }


    // �������� �� �������� �����
    if (score >= 20)
        doorOpened = true;

    // �������� �� ���������� ������� �����
    if (doorOpened && x == width / 2 && y == 0)
    {
        victory = true;
        gameOver = true;
        Draw();
    }

    // �������� ����
    if (ballActive)
    {
        ballX += ballDirX;
        ballY += ballDirY;

        // �������� �� ������������ ���� � ��������� ����
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

// ������ ����
void SnakeGame::RunGame() {
    Setup();
    InputName();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(10); // �������� ��� ���������� ��������� ����

        // ���������� ���� ��� ����������
        if (gameOver) {
            SaveResults(); // ��������� ���������� ����� ����������� ����
            cout << "������ ������� ��� ���? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                Restart();
            }
        }
    }
}

// ������� ������� ���������
int main() {
    setlocale(LC_ALL, "Rus"); // ��������� ������ ��� ����������� ����������� ������ �� ������� �����
    SnakeGame game(30, 15); // �������� ������� ����
    game.RunGame(); // ������ ����
    return 0;
}