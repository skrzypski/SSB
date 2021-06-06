/**
 * @file file_functions.h
 * @brief
 * Plik nagłówkowy części programu odpowiedzialnej za zapis danych do plików
**/
#ifndef _FILE_FUNCTIONS_H_
#define _FILE_FUNCTIONS_H_

#include <stdio.h>

/**
 * @brief
 * Funkcja zapisująca dany ciąg znaków do podanego pliku
 * @param str - ciąg znaków do zapisania
 * @param f - wskaźnik do pliku
**/
void writeString(char* str, FILE* f);

/**
 * @brief
 * Funkcja zapisująca kontakty do pliku contacts.ssb
 * Jeżeli kontakt jest w kolejce do usunięcia to go nie zapisuje
 * @see deleteContact()
**/
void writeContact();

/**
 * @brief
 * Funkcja zapisująca telefony do pliku phones.ssb
 * Jeżeli telefon należy do usuwanego kontaktu to nie zapisuje tego telefonu
 * @see deleteContact()
**/
void writePhone();

/**
 * @brief
 * Funkcja zapisująca adresy do pliku adresses.ssb
 * Jeżeli adres należy do usuwanego kontaktu to nie zapisuje tego adresu
 * @see deleteContact()
**/
void writeAdress();

/**
 * @brief
 * Funkcja zapisująca e-maile do pliku emails.ssb
 * Jeżeli e-mail należy do usuwanego kontaktu to nie zapisuje tego e-maila
 * @see deleteContact()
**/
void writeEmail();

/**
 * @brief
 * Funkcja zapisująca grupy do pliku groups.ssb
 * Jeżeli grupa jest w kolejce do usunięcia to jej nie zapisuje
 * @see deleteGroup()
**/
void writeGroup();

/**
 * @brief
 * Funkcja zapisująca relacje do pliku relations.ssb
 * Jeżeli relacja jest w kolejce do usunięcia to jej nie zapisuje
 * Jeżeli zostanie usunięty kontakt lub grupa to są usuwane kaskadowo wszystkie relacje powiązane z kontaktem lub grupą
 * @see relationDelete()
 * @see deleteContact()
 * @see deleteGroup()
**/
void writeRelation();

/**
 * @brief
 * Funkcja zapisująca użytkowników do pliku users.ssb
**/
void writeUsers();

/**
 * @brief
 * Funkcja wywołująca po kolei wszystkie funkcje zapisujące dane
 * @see	writeUsers();
 * @see writeContact();
 * @see writePhone();
 * @see writeAdress();
 * @see writeEmail();
 * @see writeGroup();
 * @see writeRelation();
**/
void writeData();

#endif