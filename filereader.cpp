#include <fstream>
#include "filework.h"
#include <stdio.h>
#include <iostream>
using namespace std;
bool badfile(fstream& finput)
{
	if (finput.bad() || finput.peek() == ifstream::traits_type::eof())
	{
		finput.close();
		return true;
	}
	finput.close();
	return false;
}

void coreReader(Text* buffer, fstream& finput, matrix2d* matrix, bool& fileEnded, bool& blocklineEnded)
{
	int posX = buffer->blockNumX;
	int posY = buffer->blockNumY;
	char c = '\0';

	int k = 0;
	for (int i = 0; i < buffer->blockSizeN; i++)
	{
		switch (i)

		{
		case 0: //i == 0
			if ((posY == 0) && (posX == 0))
			{
				finput.seekg(0, ios::beg);
				break;
			}
			else
				if (posX == 0)
				{
					finput.seekg(*(*(matrix->matrix + buffer->blockSizeN - 1) + 1), ios::beg);
					break;
				}
				else
				{
					finput.seekg(*(*(matrix->matrix + i) + 1), ios::beg);
					break;
				}

		default:
			if (posX == 0) //i не равно 0
			{
				char tempc = '\0';
				finput.seekg(-1, ios::cur);
				while (true)
				{
					finput >> tempc;
					if (tempc == '\n')
					{
						break;
					}
					if (finput.eof())
					{
						finput.clear();
						for (int e_i = i; e_i < buffer->blockSizeN; e_i++)
						{
							*(*(matrix->matrix + e_i) + 0) = 1;
						}
						bufferFillMarkers(buffer, i, buffer->blockSizeN - 1, 0);

						if (blockLineFinished(matrix->matrix, buffer->blockSizeN))
						{
							blocklineEnded = true;
						}
						return;
					}
				}
				break;
			}
			else
			{
				finput.seekg(*(*(matrix->matrix + i) + 1), ios::beg);
				break;
			}
		}

		for (int j = 0; j < buffer->blockSizeM; j++) //Считывание 5 символов строки
		{
			if (*(*(matrix->matrix + i) + 0) == 1)
			{
				//*(*(buffer->Txt + i) + 0) = buffer->Mark;
				*((*(buffer->Txt + i))->Str + 0) = buffer->Mark;
				if (blockLineFinished(matrix->matrix, buffer->blockSizeN))
				{
					blocklineEnded = true;
				}
				continue;
			} //Если skipN = 1, строка заполянется NULL и идёт переход на следующий i.

			finput >> c;

			if (finput.eof())
			{
				finput.clear();
				fileEnded = true;

				*((*(buffer->Txt + i))->Str + j) = buffer->Mark;
				if (i < buffer->blockSizeN - 1)
				{
					bufferFillMarkers(buffer, i + 1, buffer->blockSizeN - 1, 0);
				}

				for (int e_i = i; e_i < buffer->blockSizeN; e_i++)
				{
					*(*(matrix->matrix + e_i) + 0) = 1;
				}

				if (blockLineFinished(matrix->matrix, buffer->blockSizeN))
				{
					blocklineEnded = true;
					return;
				}
				break;
			}//Заполнения остатка буффера NULL

			if (c == '\n')
			{

				//*(*(buffer->Txt + i) + j) = buffer->Mark; //МАРКЕР
				*((*(buffer->Txt + i))->Str + j) = buffer->Mark;


				if (i == buffer->blockSizeN - 1) //Переход с конца старого блока на начало нового
				{
					*(*(matrix->matrix + i) + 1) = finput.tellg();
				}

				*(*(matrix->matrix + i) + 0) = 1; //Строка не имеет продолжения
				if (blockLineFinished(matrix->matrix, buffer->blockSizeN))
				{
					blocklineEnded = true;
					if (i < buffer->blockSizeN - 1)
					{
						bufferFillMarkers(buffer, i + 1, buffer->blockSizeN - 1, 0);
					}
					return;
				}
				break;
			}

			if (j == buffer->blockSizeM - 1)
			{
				*(*(matrix->matrix + i) + 1) = finput.tellg();
				*((*(buffer->Txt + i))->Str + j + 1) = buffer->Mark;
			}

			if (*(*(matrix->matrix + i) + 0) == 0) //Запись символа в буффер
			{
				*((*(buffer->Txt + i))->Str + j) = c;
			}

		}
	}
}

void findwords(Text* buffer, matrix2d* wordsLength, int*& totalWords, bool strokaEnded, int& totalWordNumber, fstream& foutput)
{
	if (buffer->blockNumX == 0)
	{
		for (int i = 0; i < buffer->blockSizeN; i++)
		{
			*(*(wordsLength->matrix + i) + 0) = 0;
		}
	}

	for (int i = 0; i < buffer->blockSizeN; i++)
	{
		char c = '\0';
		for (int j = 0; j < buffer->blockSizeM + 1; j++)
		{
			c = *((*(buffer->Txt + i))->Str + j);

			if (c == ' ')
			{
				if (*(*(wordsLength->matrix + i) + 0) != 0)
				{
					totalWordNumber++;
					extendMatrix(totalWords, *(*(wordsLength->matrix + i) + 0), totalWordNumber);
					//cout << ">>Найдено слово длины " << *(*(wordsLength->matrix + i) + 0) << endl;
					//foutput << ">>Найдено слово длины " << *(*(wordsLength->matrix + i) + 0) << endl;
					*(*(wordsLength->matrix + i) + 0) = 0;
				}
				continue;
			}

			if (c == buffer->Mark)
			{
				if (strokaEnded && ((*(*(wordsLength->matrix + i) + 0)) != 0))
				{
					totalWordNumber++;
					extendMatrix(totalWords, *(*(wordsLength->matrix + i) + 0), totalWordNumber);
					//cout << ">>Найдено слово длины " << *(*(wordsLength->matrix + i) + 0) << endl;
					//foutput << ">>Найдено слово длины " << *(*(wordsLength->matrix + i) + 0) << endl;
				}
				break;
			}

			(*(*(wordsLength->matrix + i) + 0))++;
		}
	}
}