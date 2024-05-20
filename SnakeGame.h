// SnakeGame.h
#pragma once

#include <iostream>
#include <conio.h> // Для использования _kbhit() и _getch()
#include <windows.h> // Для использования функции Sleep()
#include <string>
#include <ctime> // Для работы с временем
#include <fstream> // Для работы с файлами
#include <iomanip> // Для форматирования вывода

// Класс для представления игры "Змейка"
class SnakeGame {
private:
    bool gameOver; // Флаг, указывающий, закончилась ли игра
    bool doorOpened; // Флаг, указывающий, открылась ли дверь
    bool victory; // Флаг, указывающий, победил ли игрок
    const int width; // Ширина игрового поля
    const int height; // Высота игрового поля
    int x, y, fruitX, fruitY, score; // Координаты змейки и фрукта, счет игрока
    int tailX[100], tailY[100]; // Массивы для хранения координат хвоста змейки
    int nTail; // Длина хвоста
    std::string playerName; // Имя игрока

    // Переменные для мяча
    bool ballActive;
    int ballX, ballY;
    int ballDirX, ballDirY;

    time_t lastFruitTime; // Время последнего появления фрукта

    // Перечисление для направления движения змейки
    enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
    eDirection dir;

    HANDLE hConsole; // Дескриптор консоли

    // Метод для сохранения результатов в файл
    void SaveResults() {
        std::ofstream file("results.txt", std::ios::app); // Открываем файл для добавления данных в конец
        if (file.is_open()) {
            file << std::left << std::setw(20) << playerName << score << std::endl; // Записываем имя игрока и его счет
            file.close(); // Закрываем файл
        }
        else {
            std::cout << "Ошибка при открытии файла!" << std::endl; // Выводим сообщение об ошибке, если не удалось открыть файл
        }
    }

public:
    // Конструктор класса
    SnakeGame(int w, int h);

    // Методы игры
    void Setup(); // Настройка начальных параметров игры
    void Draw(); // Отрисовка игрового поля
    void Input(); // Обработка ввода пользователя
    void InputName(); // Ввод имени игрока
    void Restart(); // Перезапуск игры
    void Logic(); // Логика игры
    void RunGame(); // Запуск игры
    void ShowCursor(bool show); // Показать/скрыть курсор консоли
};