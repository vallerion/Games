
#include "Figure.h"

void Figure::Clear()
{
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 4; j++)
		figureArray[i][j] = false;
}

void Figure::Create()
{
	Clear();
	rotate = 1;
	srand(time(0));
    int number_figure = rand() % 7;
	switch (number_figure)
	{
	case 0:
        type = line;					// ||||||||
        for (int i = 0; i < 4; i++)		//
            figureArray[0][i] = true;	//
        break;							//
	case 1:
        type = square;                  // ||||
		for (int i = 0; i < 2; i++)		// ||||
        for (int j = 0; j < 2; j++)		//
			figureArray[i][j] = true;	// 
		break;
	case 2:
        type = Lleft;					// ||||||
        for (int i = 0; i < 3; i++)		//     ||
            figureArray[0][i] = true;	//
        figureArray[1][2] = true;		//
		break;
	case 3:
        type = Lright;					// ||||||
		for (int i = 0; i < 3; i++)		// ||
            figureArray[0][i] = true;	//
		figureArray[1][0] = true;		// 
		break;
	case 4:
		type = pyramid;					//   ||
        for (int i = 0; i < 3; i++)		// ||||||
            figureArray[1][i] = true;	//
		figureArray[0][1] = true;		// 
		break;
	case 5:
		type = Zleft;
        figureArray[0][0] = true;		// ||
        figureArray[1][0] = true;		// ||||
        figureArray[1][1] = true;		//   ||
		figureArray[2][1] = true;		// 
		break;
	case 6:
		type = Zright;
        figureArray[1][0] = true;		//   ||
        figureArray[0][1] = true;		// ||||
        figureArray[1][1] = true;		// ||
		figureArray[2][0] = true;		// 
	}
}

void Figure::Rotate()
{
	if (rotate == 4)
        rotate = 0;
	rotate++;

	switch (type)
	{
	case square:
		return;
	case line:
		if (figureArray[0][0])
		{
			Clear();
			for (int i = 0; i < 4; i++)
				figureArray[i][1] = true;
		}
		else
		{
			Clear();
			for (int i = 0; i < 4; i++)
				figureArray[0][i] = true;
		}
		break;
	default:
		bool tempFigArray[4][4];
		for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tempFigArray[i][j] = false;

		for (int j = 2, k = 0; j >= 0; j--, k++)
		for (int i = 0; i < 3; i++)
			tempFigArray[k][i] = figureArray[i][j];

		Clear();

		for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			figureArray[i][j] = tempFigArray[i][j];
		break;
	}
}
