
#pragma once

#include "Figure.h"

class GameField	// класс игрового поля
{
private:
        // фигура
    float currentX, currentY;	// настоящие координаты фигуры
    float speed;	// скорость падения фигуры
    int score;
    int next_figure;

    void AddFigure();	// добавление фигуры на игровое поле

    void ClearPrevious();	// удаление предидущего шага

    bool CheckCollisionLeft();	// проверка столкновений слева

    bool CheckCollisionRight();	// проверка столкновений справа

    void DeleteHorizontalLine(int index_line);

public:
    Figure *figure;
    bool **gameFieldArray;	// указатель на массив указателей / двойной массив - поле
    const int width, height; // размеры поля

    GameField(int, int);

    ~GameField();

    int GetScore();

    bool** NextFigure();

    void CreateFigure();	// создание фигуры

    void SpeedUpFigure();	// ускорение падения фигуры

    void MoveLeftFigure();	// движение влево

    void MoveRightFigure();	// движение вправо

    void MoveRotateFigure();	// поворот фигуры

    void MoveDownFigure();	// движение фигуры вниз

    bool CheckCollisionDown(); // проверка столкновений снизу

    bool CheckGameOver();	// проверка заполнености до "потолка"

    void CheckLine();	// проверка линии
};
