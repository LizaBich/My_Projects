#include "Exeption.h"

ostream & operator<<(ostream & stream, EXEPTION& ob)             // ����� ������� ������ EXEPTION
{
	system("cls");
	stream << "\n    ��� ������: " << ob.code << endl;
	return stream;
}

ostream & operator<<(ostream & stream, FILEEXEPTION & ob)
{
	system("cls");
	stream << dynamic_cast<EXEPTION &>(ob);
	stream << "    ��� ������: " << ob.error_name;
	return stream;
}