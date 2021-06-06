/**
 * @file colors.c
 * @brief
 * Kod źródłowy biblioteki ułatwiającej zmiany kolorów tekstu i tła
**/
#include "colors.h"
#include <windows.h>

void setFg(enum ForeGround fg)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg); 
}

void setBg(enum BackGround bg)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * bg);
}

void setFgBg(enum ForeGround fg, enum BackGround bg)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * bg + fg);

}

void setBgFg(enum BackGround bg, enum ForeGround fg)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * bg + fg);
}

void setDefault()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}