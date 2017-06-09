#include "FILE.h"

//void BINARFILE::ToFile(string info)
//{
//	file.open(name, ios::out | ios::app | ios::binary);
//	if (!file) throw FILEEXEPTION("Не удалось открыть файл для записи.", 1);
//	size_t size = info.size();
//	file.write(reinterpret_cast<const char *>(&size), sizeof(size));
//	file.write(info.c_str(), size);
//	file.close();
//}

//string BINARFILE::FromFile()
//{
//	file.open(name, ios::in | ios::binary);
//	if (!file) throw FILEEXEPTION("Не удалось открыть файл для чтения.", 1);
//
//	file.seekg(pos);
//	size_t size;
//	file.read(reinterpret_cast<char *>(&size), sizeof(size));
//
//	char *buff = new char[size];
//	file.read(buff, size);
//
//	string st(buff, size);
//
//	pos = file.tellg();
//
//	delete[] buff;
//	file.close();
//	return st;
//}

//void BINARFILE::Clear()
//{
//	file.open(name, ios::in | ios::trunc | ios::binary);
//	if (!file) throw FILEEXEPTION("Не удалось открыть файл", 1);
//	file.close();
//}
//
//bool BINARFILE::End()
//{
//	bool flg;
//	file.open(name, ios::in | ios::binary);
//	flg = file.eof();
//	file.close();
//	return flg;
//}