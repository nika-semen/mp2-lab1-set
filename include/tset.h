// Множество (заголовочный файл)
#ifndef __SET_H__
#define __SET_H__
#include "tbitfield.h"

class TSet
{ private:
    int MaxPower;       // максимальная мощность множества
    TBitField BitField; // битовое поле для хранения характеристического вектора
 public:
    TSet(int mp);
    TSet(const TSet &s);       // конструктор копирования
    TSet(const TBitField &bf); // конструктор преобразования типа
    operator TBitField();      // преобразование типа к битовому полю
    // доступ к битам
    int GetMaxPower(void) const;     // максимальная мощность множества
    void InsElem(const int Elem);       // включить элемент в множество
    void DelElem(const int Elem);       // удалить элемент из множества
    int IsMember(const int Elem) const; // проверить наличие элемента в множестве
    // перегрузка операций
    int operator== (const TSet &s) const; // сравнение
    int operator!= (const TSet &s) const; // сравнение
    TSet& operator=(const TSet &s);  // присваивание
    TSet operator+ (const int Elem); // объединение с элементом элемент должен быть из того же универса
    TSet operator- (const int Elem); // разность с элементом элемент должен быть из того же универса
    TSet operator+ (const TSet &s);  // объединение
    TSet operator* (const TSet &s);  // пересечение
    TSet operator~ (void);           // дополнение
     // ввод и вывод
    friend istream &operator>>(istream &istr, TSet &bf);
    friend ostream &operator<<(ostream &ostr, const TSet &bf);
};
#endif
