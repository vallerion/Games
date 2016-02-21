
#include "GameField.h"

#include <QDebug>

GameField::GameField(int w, int h) : width(w), height(h)
{
	figure = new Figure();
    srand(time(0));

    score = 0;
    next_figure = rand() % 7;

    gameFieldArray = new bool*[height];
    for (int i = 0; i < height; i++)
        gameFieldArray[i] = new bool[width];

	for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            gameFieldArray[i][j] = false;
}    

GameField::~GameField()
{
	delete figure;
	for (int i = 0; i < height; i++)
		delete[]gameFieldArray[i];
	delete[]gameFieldArray;
}

void GameField::AddFigure()
{
	int x = currentX,
		y = currentY;

	for (int i = 0; i < 4; i++)
	{
        x = currentX;
		for (int j = 0; j < 4; j++)
		{
			if (figure->figureArray[i][j])
                gameFieldArray[y][x] = true;
            x++;
		}
        y++;
	}
}

void GameField::CreateFigure()
{
    speed = 0.2;
    currentX = 1;
    currentY = 0;

    figure->Create(next_figure);
    next_figure = rand() % 7;

	AddFigure();
}

void GameField::SpeedUpFigure()
{
    speed = 0.5;
}

void GameField::MoveLeftFigure()
{
	if (CheckCollisionLeft())
	{
		ClearPrevious();
		currentX--;
		AddFigure();
	}
}

void GameField::MoveRightFigure()
{
    if (CheckCollisionRight())
    {
        ClearPrevious();
        currentX++;
        AddFigure();
    }
}

void GameField::MoveRotateFigure()
{
    if (currentX < 0)
        MoveRightFigure();
    if (currentX + 4 >= width)
        MoveLeftFigure();
	ClearPrevious();
	figure->Rotate();
	AddFigure();
}

void GameField::MoveDownFigure()
{
    ClearPrevious();
    currentY += speed;
    AddFigure();
}

void GameField::ClearPrevious()
{
    int x = currentX,
        y = currentY;

    for (int i = 0; i < 4; i++)
    {
        x = currentX;
        for (int j = 0; j < 4; j++)
        {
            if (figure->figureArray[i][j])
                gameFieldArray[y][x] = false;
            x++;
        }
        y++;
    }
//    for (int i = 0; i < height; i++)
//        for (int j = 0; j < width; j++)
//            gameFieldArray[i][j] = false;
}

bool GameField::CheckCollisionLeft()
{
	switch (figure->type)
	{
	case 0: // line
		if (figure->rotate == 1 || figure->rotate == 3)
		{
            if ((int)currentX == 0 || gameFieldArray[(int)currentY][int(currentX - 1)])
				return false;
            return true;
		}
        else if (figure->rotate == 2 || figure->rotate == 4)
		{
            for (int i = 0; i < 4; i++)
            if (currentX < 0 || gameFieldArray[int(currentY + i)][(int)currentX])
                return false;
            return true;
		}
	case 1: // square
        if (currentX == 0 || gameFieldArray[(int)currentY][int(currentX - 1)] || gameFieldArray[int(currentY + 1)][int(currentX - 1)])
			return false;
        return true;
	case 2: // Lleft
		if (figure->rotate == 1)
		{
            if (currentX == 0 || gameFieldArray[int(currentY)][int(currentX - 1)] || gameFieldArray[int(currentY + 1)][int(currentX + 1)])
				return false;
            return true;
		}
		else if (figure->rotate == 2)
		{
			for (int i = 0; i < 3; i++)
            if (currentX == 0 || gameFieldArray[int(currentY + i)][int(currentX - 1)])
				return false;
			return true;
		}
		else if (figure->rotate == 3)
		{
            if (currentX == 0 || gameFieldArray[int(currentY + 1)][int(currentX - 1)] || gameFieldArray[int(currentY + 2)][int(currentX - 1)])
				return false;
            return true;
		}
		else if (figure->rotate == 4)
		{
            if (currentX < 0 || gameFieldArray[int(currentY + 2)][(int)currentX] || gameFieldArray[int(currentY + 1)][int(currentX + 1)] || gameFieldArray[(int)currentY][int(currentX + 1)])
				return false;
            return true;
		}
	case 3: // Lright
		if (figure->rotate == 1)
		{
            if (currentX == 0 || gameFieldArray[(int)currentY][int(currentX - 1)] || gameFieldArray[int(currentY + 1)][int(currentX - 1)])
				return false;
            return true;
		}
		else if (figure->rotate == 2)
		{
			for (int i = 0; i < 3; i++)
            if (currentX == 0 || gameFieldArray[int(currentY + i)][int(currentX - 1)])
				return false;
			return true;
		}
		else if (figure->rotate == 3)
		{
            if (currentX == 0 || gameFieldArray[int(currentY + 2)][int(currentX - 1)] || gameFieldArray[int(currentY + 1)][int(currentX + 1)])
				return false;
            return true;
		}
		else if (figure->rotate == 4)
		{
            if (currentX < 0 || gameFieldArray[(int)currentY][(int)currentX] || gameFieldArray[int(currentY + 1)][int(currentX + 1)] || gameFieldArray[int(currentY + 2)][int(currentX + 1)])
				return false;
            return true;
		}
	case 4: // pyramid
		if (figure->rotate == 1)
		{
            if (currentX == 0 || gameFieldArray[(int)currentY][(int)currentX] || gameFieldArray[int(currentY + 1)][int(currentX - 1)])
				return false;
            return true;
		}
		else if (figure->rotate == 2)
		{
            if (currentX == 0 || gameFieldArray[(int)currentY][(int)currentX] || gameFieldArray[int(currentY + 1)][int(currentX - 1)] || gameFieldArray[int(currentY + 2)][(int)currentX])
				return false;
            return true;
		}
		else if (figure->rotate == 3)
		{
            if (currentX == 0 || gameFieldArray[int(currentY + 1)][int(currentX - 1)] || gameFieldArray[int(currentY + 2)][(int)currentX])
				return false;
            return true;
		}
		else if (figure->rotate == 4)
		{
			for (int i = 0; i < 3; i++)
            if (currentX < 0 || gameFieldArray[int(currentY + i)][(int)currentX])
				return false;
			return true;
		}
	case 5: // Zleft
		if (figure->rotate == 1)
		{
            if (currentX == 0 || gameFieldArray[(int)currentY][int(currentX - 1)] || gameFieldArray[int(currentY + 1)][int(currentX - 1)] || gameFieldArray[int(currentY + 2)][(int)currentX])
				return false;
            return true;
		}
		else if (figure->rotate == 2)
		{
            if (currentX == 0 || gameFieldArray[int(currentY + 1)][(int)currentX] || gameFieldArray[int(currentY + 2)][int(currentX - 1)])
				return false;
            return true;
		}
		else if (figure->rotate == 3)
		{
            if (currentX < 0 || gameFieldArray[(int)currentY][(int)currentX] || gameFieldArray[int(currentY + 1)][(int)currentX] || gameFieldArray[int(currentY + 2)][int(currentX + 1)])
				return false;
            return true;
		}
		else if (figure->rotate == 4)
		{
            if (currentX == 0 || gameFieldArray[(int)currentY][(int)currentX] || gameFieldArray[int(currentY + 1)][int(currentX - 1)])
				return false;
            return true;
		}
	case 6: // Zright
		if (figure->rotate == 1)
		{
            if (currentX == 0 || gameFieldArray[(int)currentY][(int)currentX] || gameFieldArray[int(currentY + 1)][int(currentX - 1)] || gameFieldArray[int(currentY + 2)][int(currentX - 1)])
				return false;
            return true;
		}
		else if (figure->rotate == 2)
		{
			if (currentX == 0 || gameFieldArray[int(currentY + 1)][int(currentX - 1)] || gameFieldArray[int(currentY + 2)][(int)currentX])
				return false;
            return true;
		}
		else if (figure->rotate == 3)
		{
            if (currentX < 0 || gameFieldArray[(int)currentY][int(currentX + 1)] || gameFieldArray[int(currentY + 1)][(int)currentX] || gameFieldArray[int(currentY + 2)][(int)currentX])
				return false;
            return true;
		}
		else if (figure->rotate == 4)
		{
            if (currentX == 0 || gameFieldArray[(int)currentY][int(currentX - 1)] || gameFieldArray[int(currentY + 1)][(int)currentX])
				return false;
            return true;
		}
	}
	return false;
}

bool GameField::CheckCollisionRight()
{
	switch (figure->type)
	{
	case 0: // line
		if (figure->rotate == 1 || figure->rotate == 3)
		{
            if (gameFieldArray[(int)currentY][int(currentX + 4)] || (int)currentX == width - 4)
				return false;
            return true;
		}
        else if (figure->rotate == 2 || figure->rotate == 4)
		{
            for (int i = 0; i < 4; i++)
            if (gameFieldArray[int(currentY + i)][int(currentX + 2)] || (int)currentX == width - 2)
                return false;
            return true;
		}
	case 1: // square
        if (gameFieldArray[(int)currentY][int(currentX + 2)] || gameFieldArray[int(currentY + 1)][int(currentX + 2)] || currentX == width - 2)
			return false;
        return true;
	case 2: // Lleft
		if (figure->rotate == 1)
		{
            if (gameFieldArray[int(currentY)][int(currentX + 3)] || gameFieldArray[int(currentY + 1)][int(currentX + 3)] || currentX == width - 3)
				return false;
            return true;
		}
		else if (figure->rotate == 2)
		{
            if (gameFieldArray[(int)currentY][int(currentX + 2)] || gameFieldArray[int(currentY + 1)][int(currentX + 1)] || gameFieldArray[int(currentY + 2)][int(currentX + 1)] || currentX == width - 2)
				return false;
            return true;
		}
		else if (figure->rotate == 3)
		{
            if (gameFieldArray[int(currentY + 1)][int(currentX + 1)] || gameFieldArray[int(currentY + 2)][int(currentX + 3)] || currentX == width - 3)
				return false;
            return true;
		}
		else if (figure->rotate == 4)
		{
            if (gameFieldArray[(int)currentY][int(currentX + 3)] || gameFieldArray[int(currentY + 1)][int(currentX + 3)] || gameFieldArray[int(currentY + 2)][int(currentX + 3)] || currentX == width - 3)
				return false;
            return true;
		}
	case 3: // Lright
		if (figure->rotate == 1)
		{
            if (gameFieldArray[(int)currentY][int(currentX + 3)] || gameFieldArray[int(currentY + 1)][int(currentX + 1)] || currentX == width - 3)
				return false;
            return true;
		}
		else if (figure->rotate == 2)
		{
            if (gameFieldArray[(int)currentY][int(currentX + 1)] || gameFieldArray[int(currentY + 1)][int(currentX + 1)] || gameFieldArray[int(currentY + 2)][int(currentX + 2)] || currentX == width - 2)
				return false;
            return true;
		}
		else if (figure->rotate == 3)
		{
            if (gameFieldArray[int(currentY + 1)][int(currentX + 3)] || gameFieldArray[int(currentY + 2)][int(currentX + 3)] || currentX == width - 3)
				return false;
            return true;
		}
		else if (figure->rotate == 4)
		{
            if (gameFieldArray[(int)currentY][int(currentX + 3)] || gameFieldArray[int(currentY + 1)][int(currentX + 3)] || gameFieldArray[int(currentY + 2)][int(currentX + 3)] || currentX == width - 3)
				return false;
            return true;
		}
	case 4: // pyramid
		if (figure->rotate == 1)
		{
            if (gameFieldArray[(int)currentY][int(currentX + 2)] || gameFieldArray[int(currentY + 1)][int(currentX + 3)] || currentX == width - 3)
				return false;
            return true;
		}
		else if (figure->rotate == 2)
		{
            if (gameFieldArray[(int)currentY][int(currentX + 2)] || gameFieldArray[int(currentY + 1)][int(currentX + 2)] || gameFieldArray[int(currentY + 2)][int(currentX + 2)] || currentX == width - 2)
				return false;
            return true;
		}
		else if (figure->rotate == 3)
		{
            if (gameFieldArray[int(currentY + 1)][int(currentX + 3)] || gameFieldArray[int(currentY + 2)][int(currentX + 2)] || currentX == width - 3)
				return false;
            return true;
		}
		else if (figure->rotate == 4)
		{
            if (gameFieldArray[(int)currentY][int(currentX + 2)] || gameFieldArray[int(currentY + 1)][int(currentX + 3)] || gameFieldArray[int(currentY + 2)][int(currentX + 2)] || currentX == width - 3)
				return false;
            return true;
		}
	case 5: // Zleft
		if (figure->rotate == 1)
		{
            if (gameFieldArray[(int)currentY][int(currentX + 1)] || gameFieldArray[int(currentY + 1)][int(currentX + 2)] || gameFieldArray[int(currentY + 2)][int(currentX + 2)] || currentX == width - 2)
				return false;
            return true;
		}
		else if (figure->rotate == 2)
		{
            if (gameFieldArray[int(currentY + 1)][int(currentX + 3)] || gameFieldArray[int(currentY + 2)][int(currentX + 2)] || currentX == width - 3)
				return false;
            return true;
		}
		else if (figure->rotate == 3)
		{
            if (gameFieldArray[(int)currentY][int(currentX + 2)] || gameFieldArray[int(currentY + 1)][int(currentX + 3)] || gameFieldArray[int(currentY + 2)][int(currentX + 3)] || currentX == width - 3)
				return false;
            return true;
		}
		else if (figure->rotate == 4)
		{
            if (gameFieldArray[(int)currentY][int(currentX + 3)] || gameFieldArray[int(currentY + 1)][int(currentX + 2)] || currentX == width - 3)
				return false;
            return true;
		}
	case 6: // Zright
		if (figure->rotate == 1)
		{
            if (gameFieldArray[(int)currentY][int(currentX + 2)] || gameFieldArray[int(currentY + 1)][int(currentX + 2)] || gameFieldArray[int(currentY + 2)][int(currentX + 1)] || currentX == width - 2)
				return false;
            return true;
		}
		else if (figure->rotate == 2)
		{
            if (gameFieldArray[int(currentY + 1)][int(currentX + 2)] || gameFieldArray[int(currentY + 2)][int(currentX + 3)] || currentX == width - 3)
				return false;
            return true;
		}
		else if (figure->rotate == 3)
		{
            if (gameFieldArray[(int)currentY][int(currentX + 3)] || gameFieldArray[int(currentY + 1)][int(currentX + 3)] || gameFieldArray[int(currentY + 2)][int(currentX + 2)] || currentX == width - 3)
				return false;
            return true;
		}
		else if (figure->rotate == 4)
		{
            if (gameFieldArray[(int)currentY][int(currentX + 2)] || gameFieldArray[int(currentY + 1)][int(currentX + 3)] || currentX == width - 3)
				return false;
            return true;
		}
	}
	return false;
}

bool GameField::CheckCollisionDown()
{
	switch (figure->type)
	{
	case 0: // line
		if (figure->rotate == 1 || figure->rotate == 3)
		{
			for (int i = 0; i < 4; i++)
            if ((int)currentY == height - 1 || gameFieldArray[int(currentY + 1)][int(currentX + i)])
				return false;
			return true;
		}
		else if (figure->rotate == 2 || figure->rotate == 4)
		{
            if ((int)currentY == height - 4 || gameFieldArray[int(currentY + 4)][int(currentX + 1)])
				return false;
			return true;
		}
	case 1: // square
        if ((int)currentY == height - 2 || gameFieldArray[int(currentY + 2)][(int)currentX] || gameFieldArray[int(currentY + 2)][int(currentX + 1)])
			return false;
        return true;
	case 2: // Lleft
		if (figure->rotate == 1)
		{
            if ((int)currentY == height - 2 || gameFieldArray[int(currentY + 1)][(int)currentX] || gameFieldArray[int(currentY + 1)][int(currentX + 1)] || gameFieldArray[int(currentY + 2)][int(currentX + 2)])
				return false;
            return true;
		}
		else if (figure->rotate == 2)
		{
            if ((int)currentY == height - 3 || gameFieldArray[int(currentY + 3)][(int)currentX] || gameFieldArray[int(currentY + 1)][int(currentX + 1)])
				return false;
            return true;
		}
		else if (figure->rotate == 3)
		{
			for (int i = 0; i < 3; i++)
            if ((int)currentY == height - 3 || gameFieldArray[int(currentY + 3)][int(currentX + i)])
				return false;
            return true;
		}
		else if (figure->rotate == 4)
		{
            if ((int)currentY == height - 3 || gameFieldArray[int(currentY + 3)][int(currentX + 1)] || gameFieldArray[int(currentY + 3)][int(currentX + 2)])
				return false;
            return true;
		}
	case 3: // Lright
		if (figure->rotate == 1)
		{
            if ((int)currentY == height - 2 || gameFieldArray[int(currentY + 2)][(int)currentX] || gameFieldArray[int(currentY + 1)][int(currentX + 1)] || gameFieldArray[int(currentY + 1)][int(currentX + 2)])
				return false;
            return true;
		}
		else if (figure->rotate == 2)
		{
            if ((int)currentY == height - 3 || gameFieldArray[int(currentY + 3)][(int)currentX] || gameFieldArray[int(currentY + 3)][int(currentX + 1)])
				return false;
            return true;
		}
		else if (figure->rotate == 3)
		{
			for (int i = 0; i < 3; i++)
            if ((int)currentY == height - 3 || gameFieldArray[int(currentY + 3)][int(currentX + i)])
				return false;
			return true;
		}
		else if (figure->rotate == 4)
		{
            if ((int)currentY == height - 3 || gameFieldArray[int(currentY + 1)][int(currentX + 1)] || gameFieldArray[int(currentY + 3)][int(currentX + 2)])
				return false;
            return true;
		}
	case 4: // pyramid
		if (figure->rotate == 1)
		{
			for (int i = 0; i < 3; i++)
            if ((int)currentY == height - 2 || gameFieldArray[int(currentY + 2)][int(currentX + i)])
				return false;
			return true;
		}
		else if (figure->rotate == 2)
		{
            if ((int)currentY == height - 3 || gameFieldArray[int(currentY + 2)][(int)currentX] || gameFieldArray[int(currentY + 3)][int(currentX + 1)])
				return false;
            return true;
		}
		else if (figure->rotate == 3)
		{
            if ((int)currentY == height - 3 || gameFieldArray[int(currentY + 2)][(int)currentX] || gameFieldArray[int(currentY + 3)][int(currentX + 1)] || gameFieldArray[int(currentY + 2)][int(currentX + 2)])
				return false;
            return true;
		}
		else if (figure->rotate == 4)
		{
            if ((int)currentY == height - 3 || gameFieldArray[int(currentY + 3)][int(currentX + 1)] || gameFieldArray[int(currentY + 2)][int(currentX + 2)])
				return false;
            return true;
		}
	case 5: // Zleft
		if (figure->rotate == 1)
		{
            if ((int)currentY == height - 3 || gameFieldArray[int(currentY + 2)][(int)currentX] || gameFieldArray[int(currentY + 3)][int(currentX + 1)])
				return false;
            return true;
		}
		else if (figure->rotate == 2)
		{
            if ((int)currentY == height - 3 || gameFieldArray[int(currentY + 3)][(int)currentX] || gameFieldArray[int(currentY + 3)][int(currentX + 1)] || gameFieldArray[int(currentY + 2)][int(currentX + 2)])
				return false;
            return true;
		}
		else if (figure->rotate == 3)
		{
            if ((int)currentY == height - 3 || gameFieldArray[int(currentY + 2)][int(currentX + 1)] || gameFieldArray[int(currentY + 3)][int(currentX + 2)])
				return false;
            return true;
		}
		else if (figure->rotate == 4)
		{
            if ((int)currentY == height - 2 || gameFieldArray[int(currentY + 2)][(int)currentX] || gameFieldArray[int(currentY + 2)][int(currentX + 1)] || gameFieldArray[int(currentY + 1)][int(currentX + 2)])
				return false;
            return true;
		}
	case 6: // Zright
		if (figure->rotate == 1)
		{
            if ((int)currentY == height - 3 || gameFieldArray[int(currentY + 3)][(int)currentX] || gameFieldArray[int(currentY + 2)][int(currentX + 1)])
				return false;
            return true;
		}
		else if (figure->rotate == 2)
		{
            if ((int)currentY == height - 3 || gameFieldArray[int(currentY + 2)][(int)currentX] || gameFieldArray[int(currentY + 3)][int(currentX + 1)] || gameFieldArray[int(currentY + 3)][int(currentX + 2)])
				return false;
            return true;
		}
		else if (figure->rotate == 3)
		{
            if ((int)currentY == height - 3 || gameFieldArray[int(currentY + 3)][int(currentX + 1)] || gameFieldArray[int(currentY + 2)][int(currentX + 2)])
				return false;
            return true;
		}
		else if (figure->rotate == 4)
		{
            if ((int)currentY == height - 2 || gameFieldArray[int(currentY + 1)][(int)currentX] || gameFieldArray[int(currentY + 2)][int(currentX + 1)] || gameFieldArray[int(currentY + 2)][int(currentX + 2)])
				return false;
            return true;
		}
	}
    return false;
}

bool GameField::CheckGameOver()
{
    for (int j = 0; j < width; j++)
    if (gameFieldArray[0][j])
		return true;
	return false;
}

void GameField::CheckLine()
{
    int count = 0;

    for (int i = 0; i < height; i++)
	{
		count = 0;
        for (int j = 0; j < width; j++)
		{
            if (gameFieldArray[i][j])
				count++;
            if (count == width)
            {
                DeleteHorizontalLine(i);
                score++;
            }
		}
    }
}

void GameField::DeleteHorizontalLine(int index_line)
{
    for (int j = 0; j < width; j++)
        gameFieldArray[index_line][j] = false;

    for (int i = index_line; i > 0; i--)
    for (int j = 0; j < width; j++)
        gameFieldArray[i][j] = gameFieldArray[i - 1][j];

    for (int j = 0; j < width; j++)
        gameFieldArray[0][j] = false;
}

int GameField::GetScore()
{
    return score;
}

bool **GameField::NextFigure()
{
    return figure->GetFigure(next_figure);
}
