/**
 * @file misc.h
 * @brief
 * Plik nagłówkowy części programu zawierającej wszelkie funkcje pomocnicze
**/
#ifndef _MISC_H_
#define _MISC_H_

/**
 * @brief
 * Funkcja zapisująca dane
 * @return true jeżeli zapisywanie przebiegło pomyślnie
**/
bool save();

/**
 * @brief 
 * Funkcja wyświetlająca tekst w kolorze komunikatu o sukcesie
 * @param str - tekst do wyświetlenia
**/
void succ(char* str);

/**
 * @brief 
 * Funkcja wyświetlająca tekst w kolorze komunikatu o błędzie
 * @param str - tekst do wyświetlenia
**/
void err(char* str);

/**
 * @brief
 * Funkcja wyciągająca parametr ID z ciągu znaków
 * @param str - tekst z którego zostanie wyciągnięty parametr
**/
int getId(char* str);

/**
 * @brief
 * Funkcja zwracająca sumę kontrolną MD5 hasła wprowadzonego przez użytkownika z wyłączonym pokazywaniem wejścia
 * @param prompt - tekst do wyświetlenia
 * @param out - wskaźnik przekazujący zmienną do zapisania sumy kontrolnej hasła
 * @see GetMD5String()
**/
void getPass(char* prompt, char* out);

/**
 * @brief
 * Funkcja wczytująca listę istniejących użytkowników i ich zaszyfrowane hasła z pliku users.ssb
**/
void loadUserlist();

/**
 * @brief 
 * Funkcja wczytująca całą bazę kontaktów do programu
**/
void loadData();

/**
 * @brief
 * Funkcja zamieniająca dwa kontakty miejscami w tablicy. Używana przy sortowaniu.
 * @see printSorted()
**/
void swap(struct Contact* c1, struct Contact* c2);

#endif