#include <fstream>
#include <iostream>
#include "bufferwork.h"
using namespace std;

void printbuffer(Text* buffer, fstream& foutput)
{
	bool notEmpty = false;
	for (int i = 0; i < buffer->blockSizeN; i++)
	{
		if (*((*(buffer->Txt + i))->Str + 0) != buffer->Mark)
		{
			notEmpty = true;
		}
	}
	if (notEmpty)
	{
		cout << "Номер блока по X: " << buffer->blockNumX << endl;
		cout << "Номер блока по Y: " << buffer->blockNumY << endl;

		foutput << "Номер блока по X: " << buffer->blockNumX << endl;
		foutput << "Номер блока по Y: " << buffer->blockNumY << endl;
		for (int i = 0; i < buffer->blockSizeN; i++)
		{
			for (int j = 0; j < buffer->blockSizeM + 1; j++)
			{
				if (*((*(buffer->Txt + i))->Str + j) == buffer->Mark)
				{
					//cout << *((*(buffer->Txt + i))->Str + j) << " ";
					//foutput << *((*(buffer->Txt + i))->Str + j) << " ";
					break;
				}
				else
				{
					cout << *((*(buffer->Txt + i))->Str + j) << " ";
					foutput << *((*(buffer->Txt + i))->Str + j) << " ";
				}
			}
			cout << endl;
			foutput << endl;
		}
	}
	else
	{
		foutput << "Номер блока по X: " << buffer->blockNumX << endl;
		foutput << "Номер блока по Y: " << buffer->blockNumY << endl;
		foutput << "Данный блок состоит только из технических символов, как например символы перехода на новую строку.\n\n";
	}
}

void bufferFillMarkers(Text* buffer, int i1, int i2, int j) //МАРКЕР
{
	for (int null_i = i1; null_i < i2 + 1; null_i++)
	{
		*((*(buffer->Txt + null_i))->Str + 0) = buffer->Mark;
	}
}

bool blockLineFinished(int** matrix, int height)
{
	int m = 1;
	for (int i = 0; i < height; i++)
	{
		m = m * *(*(matrix + i) + 0);
	}
	if (m == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void nullifyMatrix(matrix2d* matrix)
{
	for (int i = 0; i < matrix->matrixSizeN; i++)
	{
		*(*(matrix->matrix + i) + 0) = 0;
	}
}

void bufferChanger(Text* buffer, matrix2d* matrix, bool& strokaEnded, bool fileended)
{
	if (strokaEnded)
	{
		if (!(fileended && strokaEnded))
		{
			strokaEnded = false;
		}
		buffer->blockNumX = 0;
		buffer->blockNumY++;
		nullifyMatrix(matrix);
	}
	else
	{
		buffer->blockNumX++;
	}

	deleteBuffer(buffer, false);

	for (int i = 0; i < buffer->blockSizeN; i++)
	{
		Stroka* str = new Stroka(buffer->blockSizeM);
		*(buffer->Txt + i) = str;
	}
}

void deleteBuffer(Text* buffer, bool full)
{
	for (int i = 0; i < buffer->blockSizeN; i++)
	{
		delete[] * (buffer->Txt + i);
	}
	if (full)
	{
		delete[] buffer->Txt;
		delete buffer;
	}
}

void deleteMatrix(matrix2d* matrix, bool full)
{
	for (int i = 0; i < matrix->matrixSizeN; i++)
	{
		delete[] * (matrix->matrix + i);
	}
	delete[] matrix->matrix;

	if (full)
	{
		delete matrix;
	}
}

void extendMatrix(int*& matrix, int newword, int totalWords)
{
	int* arr = new int[totalWords];
	if (totalWords == 1)
	{
		*(arr + 0) = newword;
	}
	else
	{
		for (int i = 0; i < totalWords - 1; i++)
		{
			*(arr + i) = *(matrix + i);
		}
		*(arr + totalWords - 1) = newword;
	}
	delete[] matrix;
	matrix = arr;
}

void printAllWords(int* matrix, int totalWordNumber, fstream& foutput)
{
	cout << "Найденные длины слов: ";
	foutput << "Найденные длины слов: ";
	for (int i = 0; i < totalWordNumber; i++)
	{
		cout << *(matrix + i);
		foutput << *(matrix + i);
		if (i != totalWordNumber - 1)
		{
			cout << ", ";
			foutput << ", ";
		}
	}
}