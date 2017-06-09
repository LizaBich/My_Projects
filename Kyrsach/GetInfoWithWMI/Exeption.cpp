#include "Exeption.h"

ostream & operator<<(ostream & stream, EXEPTION& ob)             // Вывод объекта класса EXEPTION
{
	system("cls");
	stream << "\n    Код ошибки: " << ob.code << endl;
	return stream;
}

ostream & operator<<(ostream & stream, FILEEXEPTION & ob)
{
	system("cls");
	stream << dynamic_cast<EXEPTION &>(ob);
	stream << "    Имя ошибки: " << ob.error_name;
	return stream;
}