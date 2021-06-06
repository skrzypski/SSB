/**
 * @file globals.h
 * @brief
 * Plik zawierający wszelkie deklaracje zmiennych globalnych oraz łączący pozostałe pliki w jedną całość
**/
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

#include "colors.h"
#include "md5.h"

#include "misc.h"
#include "file_functions.h"
#include "loop.h"

#define INPUT_SIZE 1024 ///< Maksymalny rozmiar wejścia
#define ENTRY_SIZE 128 ///< Maksymalny rozmiar pola

#pragma region structs

/**
 * @brief
 * Struktura kontaktu
**/
struct Contact
{
	char Owner[ENTRY_SIZE]; ///< Właściciel kontaktu
	bool toRemove; ///< Flaga do usunięcia
	unsigned int ID_Contact; ///< ID kontaktu
	char Name[ENTRY_SIZE]; ///< Pole imię
	char Surname[ENTRY_SIZE]; ///< Pole nazwisko
	char Description[INPUT_SIZE]; ///< Pole opis
};

/**
 * @brief
 * Struktura telefonu
**/
struct Phone
{
	bool toRemove; ///< Flaga do usunięcia
	unsigned int ID_Phone; ///< ID telefonu
	unsigned int ID_Contact; ///< ID kontaktu do którego należy telefon
	char Number[10]; ///< Pole numer telefonu
};

/**
 * @brief
 * Struktura adresu
**/
struct Adress
{
	bool toRemove; ///< Flaga do usunięcia
	unsigned int ID_Adress; ///< ID Adresu
	unsigned int ID_Contact; ///< ID kontaktu do którego należy adres
	char FirstLine[ENTRY_SIZE]; ///< Pole pierwsza linijka adresu
	char SecondLine[ENTRY_SIZE]; ///< Pole druga linijka adresu
	char PostalCode[7]; ///< Pole kod pocztowy
	char City[ENTRY_SIZE]; ///< Pole miasto
};

/**
 * @brief 
 * Struktura e-mailu
**/
struct Email
{
	bool toRemove; ///< Flaga do usunięcia
	unsigned int ID_Email; ///< ID E-mailu
	unsigned int ID_Contact; ///< ID kontaktu do którego należy e-mail
	char Mail[ENTRY_SIZE]; ///< Pole e-mail
};

/**
 * @brief 
 * Struktura grupy
**/
struct Group
{
	char Owner[ENTRY_SIZE]; ///< Właściciel grupy
	bool toRemove; ///< Flaga do usunięcia
	unsigned int ID_Group; ///< ID grupy
	char Name[ENTRY_SIZE]; ///< Pole nazwa
	char Description[INPUT_SIZE]; ///< Pole opis
};

/**
 * @brief 
 * Struktura relacji
**/
struct Relation
{
	bool toRemove; ///< Flaga do usunięcia
	unsigned int ID_Relation; ///< ID relacji
	unsigned int ID_Contact; ///< ID kontaktu
	unsigned int ID_Group; ///< ID grupy
};
#pragma endregion

#pragma region globals

char LOGGED_USER[ENTRY_SIZE]; ///< Nazwa zalogowanego użytkownika

bool isSaved; ///< Flaga czy zapisano

/**
 * @brief 
 * Struktura zawierająca wskaźniki na poszczególne pliki w bazie 
**/
struct DB
{
	FILE* users; ///< Plik z użytkownikami
	FILE* contacts; ///< Plik z kontaktami
	FILE* phones; ///< Plik z telefonami
	FILE* emails; ///< Plik z e-mailami
	FILE* adresses; ///< Plik z adresami
	FILE* groups; ///< Plik z grupami
	FILE* relations; ///< Plik z relacjami
} db; ///< Obiekt struktury DB @see struct DB

/**
 * @brief 
 * Struktura użytkownika
**/
struct Users
{
	char login[ENTRY_SIZE]; ///< Pole login
	char hash[33]; ///< Pole suma kontrolna MD5 hasła
	bool toRemove; ///< Flaga do usunięcia
};

struct Users* userList; ///< Lista przechowująca użytkowników
int userCount; ///< Ilość użytkowników

struct Contact* contactList; ///< Lista przechowująca kontakty
int contactCount; ///< Ilość kontaktów
int contactLast; ///< ID ostatniego kontaktu

struct Phone* phoneList; ///< Lista przechowująca telefony
int phoneCount; ///< Ilość telefonów
int phoneLast; ///< ID ostatniego telefonu

struct Adress* adressList; ///< Lista przechowująca adresy
int adressCount; ///< Ilość adresów
int adressLast; ///< ID ostatniego adresu

struct Email* emailList; ///< Lista przechowująca e-maile
int emailCount; ///< Ilość e-maili
int emailLast; ///< ID ostatniego e-maila

struct Group* groupList; ///< Lista przechowująca grupy
int groupCount; ///< Ilość grup
int groupLast; ///< ID ostatniej grupy

struct Relation* relationList; ///< Lista przechowująca relacje
int relationCount; ///< Ilość relacji
int relationLast; ///< ID ostatniej relacji

int* toRemoveContact;  ///< Lista kontaktów do usunięcia
int toRemoveContactCount; ///< Długość listy kontaktów do usunięcia

int* toRemoveGroup; ///< Lista grup do usunięcia
int toRemoveGroupCount; ///< Długość listy grup do usunięcia

int* toRemoveRelation; ///< Lista relacji do usunięcia
int toRemoveRelationCount; ///< Długość listy grup do usunięcia

int* queueRemoveContact;  ///< Lista kontaktów zakolejkowanych do usunięcia
int queueRemoveContactCount; ///< Długość listy kontaktów zakolejkowanych do usunięcia

int* queueRemoveGroup; ///< Lista grup zakolejkowanych do usunięcia
int queueRemoveGroupCount; ///< Długość listy grup zakolejkowanych do usunięcia

int* queueRemoveRelation; ///< Lista relacji zakolejkowanych do usunięcia
int queueRemoveRelationCount; ///< Długość listy relacji zakolejkowanych do usunięcia

#pragma endregion

#endif