#include <iostream>
#include<iomanip>	
#include <fstream>
#include "filework.h"
#include "bufferwork.h"
using namespace std;


int main()
{
	int N = 3;
	int M = 3;

	int totalWordNumber = 0;
	int* TotalWords = new int[1];

	char c = '\0';
	bool strokaEnded = false;
	bool fileEnded = false;

	setlocale(LC_ALL, "Russian");
	fstream finput;
	fstream foutput("output.txt", ios::out | ios::trunc);

	finput.open("input.txt", ios::in);
	finput.unsetf(ios::skipws);

	if (badfile(finput))
	{
		cout << "Файл битый или пустой." << endl;
	}
	else
	{
		//cout << "Введите символ маркера";
		//cin >> c;
		Text* buffer = new Text(N, M);
		matrix2d* PositionMatrix = new matrix2d(N, 2);
		matrix2d* WordsLength = new matrix2d(N, 1);
		while (true)
		{
			finput.open("input.txt", ios::in);
			coreReader(buffer, finput, PositionMatrix, fileEnded, strokaEnded);
			finput.close();

			printbuffer(buffer, foutput);
			findwords(buffer, WordsLength, TotalWords, strokaEnded, totalWordNumber, foutput);
			bufferChanger(buffer, PositionMatrix, strokaEnded, fileEnded);

			if (fileEnded && strokaEnded)
			{
				deleteMatrix(PositionMatrix, true);
				deleteMatrix(WordsLength, true);
				deleteBuffer(buffer, true);
				break;
			}
		}
		if (totalWordNumber == 0)
		{
			cout << "\nСлов не было найдено!";
			foutput << "\nСлов не было найдено!";
		}
		else
		{
			foutput << "\nВсего было найдено слов: " << totalWordNumber;
			cout << "\nВсего было найдено слов: " << totalWordNumber << endl << endl;
			printAllWords(TotalWords, totalWordNumber, foutput);
		}
		delete[] TotalWords;
	}
	return 0;
}