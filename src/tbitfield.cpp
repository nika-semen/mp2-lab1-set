// Битовое поле (реализация)
#include "tbitfield.h"
#include <cassert>  
#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

//Конструкторы-деструкторы
TBitField::TBitField(int len)
{
	if (len < 0) { cout << "Create bitfield with negative length\n"; throw -1; }
		int x = BITS_IN_ONE_MEM;
		BitLen = len;
		MemLen = (len + x) / x; //нумерация с нуля, 32 бит лежит во втором МеМ
		pMem = new TELEM[MemLen];
		memset(pMem, 0, MemLen * sizeof(TELEM));
	
	 
	//catch (TBitField exception){;}  // обработчик исключений типа const char*  bf.SetBit(-3) throws an exception
	//{std::cerr <<" TBitField bf("<<len<<") "<< exception ; }
	
}
TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	memset(pMem, 0, MemLen * sizeof(TELEM));
}
TBitField::~TBitField()
{
	if(BitLen>=0)
	{delete[] pMem;}
}

// методы реализации
int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int x = BITS_IN_ONE_MEM;
	return  n / x;  //нумерация с нуля, 32 бит лежит во втором МеМ
}
TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{	// n должно быть меьше чем BITS_IN_ONE_MEM
	TELEM x = 1;
	x = x << n; // n принимает значения от 0 до BITS_IN_ONE_MEM-1
	return x;
}

// доступ к битам битового поля
int TBitField::GetLength(void) const // получить длину (к-во битов)
{	
	return BitLen;
}
void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0)||(n> BitLen)){ cout << "Set bit with incorrect index\n"; throw - 1; }
	// проверка на горение !!!!
	int x = GetMemMask(n % BITS_IN_ONE_MEM);
	int y = GetMemIndex(n);
	pMem[y] = pMem[y] | x;
}
void TBitField::ClrBit(const int n) // очистить бит
{ 
	if ((n < 0) || (n > BitLen)) { cout << "Clear bit with incorrect index\n"; throw - 1; }
	// проверка на выключение !!!!
	int x = GetMemMask(n % BITS_IN_ONE_MEM);
	int y = GetMemIndex(n);
	pMem[y] = pMem[y] & (~x);
}
int TBitField::GetBit(const int n) const // получить значение бита
{	if ((n < 0) || (n > BitLen)) { cout << "Get bit with incorrect index\n"; throw - 1; }
	int y = GetMemIndex(n);
	int x = GetMemMask(n % BITS_IN_ONE_MEM);
	x = pMem[y] & x;
	x = x >> (n % BITS_IN_ONE_MEM);
	return x;
}

// битовые операции
TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (this != &bf)
	{
		delete[] pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}
int TBitField::operator==(const TBitField& bf) const // сравнение (!!!!!!!!)
{
	int x = 1, i = 0, n = max(MemLen, bf.MemLen);
	while ((i < n) && (x == 1))
	{
		if (pMem[i] != bf.pMem[i]) { x = 0; }
		i++;
	}
	return x;
}
int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if (*this == bf) { return 0; }
	else { return 1; }
}
TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int n = max(BitLen, bf.BitLen), x;
	TBitField r(n);
	for (int i = 0; i < n; i++)
	{
		x = GetBit(i) | bf.GetBit(i);
		if (x != 0) { r.SetBit(i); }
	} 
	return r; //(!!!!!!!!!!!!!!!!!!)
}
TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int n = max(BitLen, bf.BitLen), x;
	TBitField r(n);
	for (int i = 0; i < n; i++)
	{
		x = GetBit(i) & bf.GetBit(i);
		if (x != 0) { r.SetBit(i); }
	} cout << r;
	return TBitField(r); //(!!!!!!!!!!!!!!!!!!)
}
TBitField TBitField::operator~(void) // отрицание
{
	int n = BitLen, x;
	TBitField r(n);
	for (int i = 0; i < n; i++)
	{
		x = ~GetBit(i);
		if (x != 0) { r.SetBit(i); }
	} cout << r;
	return r;
}

// ввод/вывод
istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	int n = bf.GetLength();
	for (int i = 0; i < n; i++)
	{
		int x;
		istr >> x;
		if (x != 0) { bf.SetBit(i); }
	}
	return istr;
}
ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	int n = bf.GetLength();
	for (int i = 0; i < n; i++)
	{
		if (bf.GetBit(i) == 1) { ostr<<"  "<< i; }
	}
	ostr << "\n";
	return ostr;
}