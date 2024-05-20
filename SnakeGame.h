// SnakeGame.h
#pragma once

#include <iostream>
#include <conio.h> // ��� ������������� _kbhit() � _getch()
#include <windows.h> // ��� ������������� ������� Sleep()
#include <string>
#include <ctime> // ��� ������ � ��������
#include <fstream> // ��� ������ � �������
#include <iomanip> // ��� �������������� ������

// ����� ��� ������������� ���� "������"
class SnakeGame {
private:
    bool gameOver; // ����, �����������, ����������� �� ����
    bool doorOpened; // ����, �����������, ��������� �� �����
    bool victory; // ����, �����������, ������� �� �����
    const int width; // ������ �������� ����
    const int height; // ������ �������� ����
    int x, y, fruitX, fruitY, score; // ���������� ������ � ������, ���� ������
    int tailX[100], tailY[100]; // ������� ��� �������� ��������� ������ ������
    int nTail; // ����� ������
    std::string playerName; // ��� ������

    // ���������� ��� ����
    bool ballActive;
    int ballX, ballY;
    int ballDirX, ballDirY;

    time_t lastFruitTime; // ����� ���������� ��������� ������

    // ������������ ��� ����������� �������� ������
    enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
    eDirection dir;

    HANDLE hConsole; // ���������� �������

    // ����� ��� ���������� ����������� � ����
    void SaveResults() {
        std::ofstream file("results.txt", std::ios::app); // ��������� ���� ��� ���������� ������ � �����
        if (file.is_open()) {
            file << std::left << std::setw(20) << playerName << score << std::endl; // ���������� ��� ������ � ��� ����
            file.close(); // ��������� ����
        }
        else {
            std::cout << "������ ��� �������� �����!" << std::endl; // ������� ��������� �� ������, ���� �� ������� ������� ����
        }
    }

public:
    // ����������� ������
    SnakeGame(int w, int h);

    // ������ ����
    void Setup(); // ��������� ��������� ���������� ����
    void Draw(); // ��������� �������� ����
    void Input(); // ��������� ����� ������������
    void InputName(); // ���� ����� ������
    void Restart(); // ���������� ����
    void Logic(); // ������ ����
    void RunGame(); // ������ ����
    void ShowCursor(bool show); // ��������/������ ������ �������
};