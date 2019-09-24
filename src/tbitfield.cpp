// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
		throw "EROR";
	BitLen = len;
	MemLen = (len - 1) / (8 * sizeof(TELEM)) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int index = 0;
	if (n >= 0 && n < BitLen)
	{
		index = (n / (sizeof(TELEM) * 8));
	}
	else
		throw "Неверно введен бит!!!";
	return index;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{																							//????
	int s = 0; 										//сдвиг
	if (n >= 0 && n < BitLen)
	{
		s = n - GetMemIndex(n) * 8 * sizeof(TELEM);		
	}
	else
		throw "Неверно введен бит!!!";
	TELEM mask = 1 >> s;
	return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= 0 && n < BitLen)
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
	else
		throw "Индекс введен неправильно!!!";
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n < BitLen)
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));
	else
		throw "Индекс введен неправильно!!!";
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= 0 && n < BitLen)
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & GetMemMask(n);
	else
		throw "Индекс введен неправильно!!!";
	return pMem[GetMemIndex(n)];
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete[] pMem;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[GetMemIndex(i)] = bf.pMem[GetMemIndex(i)];
		}
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;						// разная длина, значит точно не равны
	else
	{
		for (int i = 0; i < bf.MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
				return 0;						//не равны, если хоть один элемент отличается
		}
		return 1;						//равны
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 1;						// разная длина, значит точно не равны
	else
	{
		for (int i = 0; i < bf.MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
				return 1;						//не равны, если хоть один элемент отличается
		}
		return 0;						// равны
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = BitLen;
	if (BitLen < bf.BitLen)
		len = bf.BitLen;
	TBitField a(len);
	for (int i = 0; i < MemLen; i++)
		a.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		a.pMem[i] |= bf.pMem[i];
	return a;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = BitLen;
	if (BitLen < bf.BitLen)
		len = bf.BitLen;
	TBitField a(len);
	for (int i = 0; i < MemLen; i++)
		a.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		a.pMem[i] &= bf.pMem[i];
	return a;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField a(BitLen);
	for (int i = 0; i < BitLen; i++)
	{
		if (GetBit(i) == 0)
			a.SetBit(i);
	}
	return a;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char a;
	for (int i = 0; i < bf.BitLen; i++)
	{
		istr >> a;
		if (a == 0)
			bf.ClrBit(i);
		if (a == 1)
			bf.SetBit(i);
		else
			throw "Неправильно введена а";
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	char a;
	for (int i = 0; i < bf.BitLen; i++)
	{
		a = bf.GetBit(i);
		ostr << a;
	}
	return ostr;
}
