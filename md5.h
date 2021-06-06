/**
 * @file md5.h
 * @brief
 * Plik nagłówkowy biblioteki obliczającej sumę kontrolną MD5
**/
/*****Please include following header files*****/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#pragma warning(disable:4996)
/***********************************************/

/**
 * @brief
 * Struktura pomocnicza wymagana do obliczenia sumy kontrolnej MD5
**/
typedef union uwb {
	unsigned w;
	unsigned char b[4];
} MD5union;

typedef unsigned DigestArray[4]; ///< Definicja tablicy 4 zmiennych typu unsigned

typedef unsigned(*DgstFctn)(unsigned a[]); ///< Definicja wskaźnika na funkcje potrzebną do obliczenia sumy kontrolnej MD5

/**
 * @brief
 * Funkcja pomocnicza wymagana do obliczenia sumy kontrolnej MD5
 * @param abcd[] - tablica zmiennych typu unsigned
 * @return wartość powstała przez wykonane operacje logiczne na liczbach przekazanych jako parametr
**/
unsigned func0(unsigned abcd[]);

/**
 * @brief
 * Funkcja pomocnicza wymagana do obliczenia sumy kontrolnej MD5
 * @param abcd[] - tablica zmiennych typu unsigned
 * @return wartość powstała przez wykonane operacje logiczne na liczbach przekazanych jako parametr
**/
unsigned func1(unsigned abcd[]);

/**
 * @brief
 * Funkcja pomocnicza wymagana do obliczenia sumy kontrolnej MD5
 * @param abcd[] - tablica zmiennych typu unsigned
 * @return wartość powstała przez wykonane operacje logiczne na liczbach przekazanych jako parametr
**/
unsigned func2(unsigned abcd[]);

/**
 * @brief
 * Funkcja pomocnicza wymagana do obliczenia sumy kontrolnej MD5
 * @param abcd[] - tablica zmiennych typu unsigned
 * @return wartość powstała przez wykonane operacje logiczne na liczbach przekazanych jako parametr
**/
unsigned func3(unsigned abcd[]);

/**
 * @brief
 * Funkcja pomocnicza wymagana do obliczenia sumy kontrolnej MD5
 * @param k - wskaźnik na zmienną typu unsigned
 * @return wskaźnik na zmienną typu unsigned
**/
unsigned* calctable(unsigned* k);

/**
 * @brief
 * Funkcja pomocnicza wymagana do obliczenia sumy kontrolnej MD5
 * @param r - zmienna typu unsigned
 * @param N - zmienna typu short
 * @return zmienna typu unsigned
**/
unsigned rol(unsigned r, short N);

/**
 * @brief
 * Funkcja obliczająca sumę kontrolną MD5
 * @param msg - ciąg znaków z którego obliczona będzie suma kontrolna
 * @param mlen - długość ciągu znaków
 * @return suma kontrolna MD5
**/
unsigned* Algorithms_Hash_MD5(const char* msg, int mlen);

/**
 * @brief
 * Funkcja wywołująca funkcje obliczającą sumę kontrolną MD5 i zapisująca we wskaźniku sumę kontrolną MD5 z podanego ciągu znaków
 * @param msg - ciąg znaków z którego obliczona będzie suma kontrolna
 * @param out - wskaźnik w którym zapisana będzie suma kontrolna
 * @see Algorithms_Hash_MD5()
**/
void GetMD5String(const char* msg, char* out);