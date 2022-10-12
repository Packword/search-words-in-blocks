#ifndef FILEWORK_H
#define FILEWORK_H
#include <fstream>
#include "bufferwork.h"
using namespace std;

bool badfile(fstream& finput);

void coreReader(Text* buffer, fstream& finput, matrix2d* matrix, bool& fileEnded, bool& blocklineEnded);

void findwords(Text* buffer, matrix2d* wordsLength, int*& totalWords, bool strokaEnded, int& totalWordNumber, fstream& foutput);
#endif