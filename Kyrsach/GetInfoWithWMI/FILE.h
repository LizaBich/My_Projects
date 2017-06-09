#pragma once
#include <fstream>
#include <iostream>
#include "Exeption.h"

using namespace std;

class BINARFILE
{
	fstream file;
	ios::pos_type pos;
	string name;
public:
	BINARFILE(string n, size_t a = 0) : name(n), pos(a) {}

	void ToFile(string info, int flag)     // заносит строку в файл
	{
		if (flag == 0) file.open(name, ios::out | ios::trunc | ios::binary);
		else file.open(name, ios::out | ios::app | ios::binary);
		if (!file) throw FILEEXEPTION("Не удалось открыть файл для записи.", 1);
		size_t size = info.size();
		file.write(reinterpret_cast<const char *>(&size), sizeof(size));
		file.write(info.c_str(), size);
		file.close();
	}
	string FromFile()             // читает строку из файла
	{
		file.open(name, ios::in | ios::binary);
		if (!file) throw FILEEXEPTION("Не удалось открыть файл для чтения.", 1);

		file.seekg(pos);
		size_t size;
		file.read(reinterpret_cast<char *>(&size), sizeof(size));

		char *buff = new char[size];
		file.read(buff, size);

		string st(buff, size);

		pos = file.tellg();

		delete[] buff;
		file.close();
		return st;
	}

	bool End()                    // проверка на конец файла
	{
		bool flg;
		file.open(name, ios::in | ios::binary);
		flg = file.eof();
		file.close();
		return flg;
	}
};