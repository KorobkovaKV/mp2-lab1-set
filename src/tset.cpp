// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{

}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower), MaxPower(s.MaxPower)
{
	
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{

}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem > 0 && Elem < MaxPower)
		BitField.SetBit(Elem);
	else
		throw "Элемент не принадлежит мн-ву!!!";
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem > 0 && Elem < MaxPower)
		BitField.ClrBit(Elem);
	else
		throw "Элемент не принадлежит мн-ву!!!";
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (this != &s)
	{
		MaxPower = s.MaxPower;
		BitField = s.BitField;
	}
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower)
		return 0;
	else
	{
		if (BitField != s.BitField)
			return 0;
		return 1;
	}
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower)
		return 1;
	else
	{
		if (BitField != s.BitField)
			return 1;
		return 0;
	}
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int m = MaxPower;
	if (MaxPower < s.MaxPower)
		m = s.MaxPower;
	TSet u(m);
	u.BitField = BitField | s.BitField;
	return u;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem<0 || Elem>MaxPower)
		throw "Выход за пределы множества!!!";
	TSet a(MaxPower);
	a.BitField.SetBit(Elem);
	return a;

}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem<0 || Elem>MaxPower)
		throw "Выход за пределы множества!!!";
	TSet a(MaxPower);
	a.BitField.ClrBit(Elem);
	return a;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	int m = MaxPower;
	if (MaxPower < s.MaxPower)
		m = s.MaxPower;
	TSet a(m);
	a.BitField = BitField & s.BitField;
	return a;
}

TSet TSet::operator~(void) // дополнение
{
	return ~BitField;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	istr >> s.BitField;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.BitField;
	return ostr;
}
