// Множество - реализация через битовые поля (реализация)
#include "tset.h"

//Конструкторы-деструкторы
TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}
TSet::TSet(const TBitField& bf) : BitField(bf.GetLength()) // конструктор преобразования типа
{
	MaxPower = bf.GetLength();
}

// методы реализации
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
	BitField.SetBit(Elem); //нужна проверка на максимальный элемент?
}
void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

//перегрузка операции
TSet::operator TBitField()
{
	return BitField;
}
TSet& TSet::operator=(const TSet& s) // присваивание
{
	if (this != &s)
	{
		MaxPower = s.MaxPower;
		BitField = s.BitField;
	}
	return *this;
}
int TSet::operator==(const TSet& s) const // сравнение
{
	if ((BitField == s.BitField)&&(MaxPower==s.MaxPower)){ return 1; }
	else { return 0; }
}
int TSet::operator!=(const TSet& s) const // сравнение
{
	if ((BitField == s.BitField)&&(MaxPower == s.MaxPower)){ return 0; }
	else { return 1; }
}
TSet TSet::operator+(const TSet& s) // объединение
{ 
	int n = max(MaxPower, s.MaxPower);
	TBitField bf(n);
	bf = BitField | (s.BitField);
	TSet s1(n);
	s1.BitField = bf;
	return s1;

}
TSet TSet::operator+(const int Elem) // объединение с элементом
{
	int n;
	if(Elem > MaxPower) {throw - 1;}
	else 
	{
	  BitField.SetBit(Elem);
	  return *this;
	}
}
TSet TSet::operator-(const int Elem) // разность с элементом
{
	TBitField bf = BitField;
	bf.ClrBit(Elem);
	return TSet(bf);
}
TSet TSet::operator*(const TSet& s) // пересечение
{
	int n = max(MaxPower, s.MaxPower);
	TBitField bf = BitField & (s.BitField);
	TSet s1(n);
	s1.BitField = bf;
	return s1;
}
TSet TSet::operator~(void) // дополнение
{
	BitField = ~BitField;
	return *this;
}

// перегрузка ввода/вывода
istream& operator>>(istream& istr, TSet& s) // ввод
{
	return istr;
}
ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{  
	ostr << s.BitField;
	return ostr;
}
