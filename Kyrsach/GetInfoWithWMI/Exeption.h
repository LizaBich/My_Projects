#pragma once
#include <iostream>
#include <string>

using namespace std;


class EXEPTION
{
	int code;                                                    // код ошибки
public:
	EXEPTION(int a = 0) : code(a)
	{}
	~EXEPTION()
	{}
	friend ostream &operator<< (ostream &stream, EXEPTION &ob);
};

class FILEEXEPTION : public EXEPTION
{
	std::string error_name;                                            // переменная с названием ошибки
public:
	FILEEXEPTION(std::string str, int c = 0) : EXEPTION(c)
	{
		this->error_name = str;
	}
	~FILEEXEPTION() {}
	friend ostream &operator<< (ostream &stream, FILEEXEPTION &ob);
	void ShowError();
};
