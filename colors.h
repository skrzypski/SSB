/**
 * @file colors.h
 * @brief
 * Plik nagłówkowy biblioteki ułatwiającej zmiany kolorów tekstu i tła
**/
#ifndef _COLORS_H_
#define _COLORS_H_

#include <windows.h>

/**
 * @brief
 * Typ wyliczeniowy przechowujący możliwe kolory tekstu
**/
enum ForeGround
{
    fg_Black, ///< Czarny
    fg_Blue,  ///< Niebieski
    fg_Green, ///< Zielony
    fg_Cyan, ///< Błętkitny
    fg_Red, ///< Czerwony
    fg_Purple, ///< Fioletowy
    fg_Gold, ///< Złoty
    fg_White, ///< Biały
    fg_iBlack, ///< Intensywnie czarny
    fg_iBlue, ///< Intensywnie niebieski
    fg_iGreen, ///< Intensywnie zielony
    fg_iCyan, ///< Intensywnie błękitny
    fg_iRed, ///< Intensywnie czerwony
    fg_iPurple, ///< Intensywnie fioletowy
    fg_iGold, ///< Intensywnie złoty
    fg_iWhite ///< Intensywnie biały
};

/**
 * @brief
 * Typ wyliczeniowy przechowujący możliwe kolory tła
**/
enum BackGround
{
    bg_Black, ///< Czarny
    bg_Blue,  ///< Niebieski
    bg_Green, ///< Zielony
    bg_Cyan, ///< Błętkitny
    bg_Red, ///< Czerwony
    bg_Purple, ///< Fioletowy
    bg_Gold, ///< Złoty
    bg_White, ///< Biały
    bg_iBlack, ///< Intensywnie czarny
    bg_iBlue, ///< Intensywnie niebieski
    bg_iGreen, ///< Intensywnie zielony
    bg_iCyan, ///< Intensywnie błękitny
    bg_iRed, ///< Intensywnie czerwony
    bg_iPurple, ///< Intensywnie fioletowy
    bg_iGold, ///< Intensywnie złoty
    bg_iWhite ///< Intensywnie biały
};

/**
 * @brief
 * Funkcja pozwalająca zmienić kolor tekstu
 * @param fg - kolor tekstu
 * @see enum ForeGround
**/ 
void setFg(enum ForeGround fg);

/**
 * @brief
 * Funkcja pozwalająca zmienić kolor tła
 * @param bg - kolor tła
 * @see enum BackGround
**/ 
void setBg(enum BackGround bg);

/**
 * @brief
 * Funkcja pozwalająca zmienić kolor tekstu i kolor tła
 * @param fg - kolor tekstu
 * @param bg - kolor tła
 * @see enum ForeGround
 * @see enum BackGround
**/ 
void setFgBg(enum ForeGround fg, enum BackGround bg);

/**
 * @brief
 * Funkcja pozwalająca zmienić kolor tła i kolor tekstu
 * @param bg - kolor tła
 * @param fg - kolor tekstu
 * @see enum BackGround
 * @see enum ForeGround
**/
void setBgFg(enum BackGround bg, enum ForeGround fg);

/**
 * @brief
 * Funkcja przywracająca domyślny kolor tekstu i tła
**/
void setDefault();

#endif