#ifndef BUFFERWORK_H
#define BUFFERWORK_H
using namespace std;

struct Stroka
{
public:
	char Mark = '#'; //Ã¿– ≈–
	char* Str;
	Stroka(int n)
	{
		int m = n + 1;
		Str = new char[m];
	}
	Stroka() : Stroka(5) {};
};

struct Text
{
public:
	char Mark = '#'; //Ã¿– ≈–	
	Stroka** Txt;

	int blockNumX = 0;
	int blockNumY = 0;

	int blockSizeN;
	int blockSizeM;

	Text(int n, int m)
	{
		blockSizeN = n;
		blockSizeM = m;

		Txt = new Stroka * [n];
		for (int i = 0; i < n; i++)
		{
			Stroka* str = new Stroka(m);

			//delete *(Txt + i);
			*(Txt + i) = str;
		}

	};
	Text() : Text(5, 5) {};
};

struct matrix2d
{
	int matrixSizeN;
	int matrixSizeM;
	int** matrix;
	matrix2d(int n, int m)
	{
		matrixSizeN = n;
		matrixSizeM = m;

		matrix = new int* [n];
		for (int i = 0; i < n; i++)
		{
			*(matrix + i) = new int[m];
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				*(*(matrix + i) + j) = 0;
			}
		}
	}
	matrix2d() : matrix2d(5, 2) {};
};

void printbuffer(Text* buffer, fstream& foutput);

bool blockLineFinished(int** matrix, int height);

void bufferChanger(Text* buffer1, matrix2d* matrix, bool& strokaEnded, bool fileended);

void bufferFillMarkers(Text* buffer, int i1, int i2, int j);

void deleteBuffer(Text* buffer, bool full);

void deleteMatrix(matrix2d* matrix, bool full);

void extendMatrix(int*& matrix, int newword, int totalWords);

void printAllWords(int* matrix, int totalWordNumber, fstream& foutput);

#endif