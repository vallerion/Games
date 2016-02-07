#ifndef FIGURE_H
#define FIGURE_H

#include <time.h>
#include <cstdlib>

class Figure
{
private:
	void Clear();	// метод очистки массива фигуры

public:
	bool figureArray[4][4]; // массив 4х4 фигуры
	enum { line, square, Lleft, Lright, pyramid, Zleft, Zright }type;	// перечисление возможный фигур
	int rotate;	// счетчик положения фигуры

	void Create();	// создание
	void Rotate();	// поворот
};

#endif // FIGURE_H
