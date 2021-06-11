/**
 * @file loop.h
 * @brief
 * Plik nagłówkowy części programu odpowiedzialnej za obsługę poleceń wywoływanych w głównej pętli
**/
#ifndef _LOOP_H_
#define _LOOP_H_

/**
 * @brief
 * Funkcja wyświetlająca pomoc
**/
void printHelp();

/**
 * @brief
 * Funkcja wyświetlająca informacje o programie
**/
void printAbout();

/**
 * @brief
 * Funkcja wyświetlająca listę dodanych użytkowników
**/
void printUsers();

/**
 * @brief
 * Funkcja wyświetlająca listę grup
**/
void printGroups();

/**
 * @brief
 * Funkcja wyświetlająca kontakty rosnąco po ID z możliwością wyszukiwania
 * @param searchKey - klucz do wyszukiwania, jeżeli klucz "null" to pomija wyszukiwanie
**/
void printContacts(char* searchKey);

/**
 * @brief
 * Funkcja wyświetlająca kontakty posortowane rosnąco/malejąco według imienia/nazwiska
 * @param dir - kierunek sortowania <"asc" - rosnąco / "desc" - malejąco>
 * @param field - pole do sortowania <"name" - imię / "surname" - nazwisko>
**/
void printSorted(char* dir, char* field);

/**
 * @brief
 * Funkcja wyświetlająca kontakty należące do podanej grupy
 * @param ID_Group - ID grupy
**/
void printContactsGroups(int ID_Group);

/**
 * @brief
 * Funkcja dodająca relacje do kolejki do usunięcia
 * Usuwanie realizowane w funkcji zapisu do pliku
 * @param id - ID relacji do usunięcia
 * @see writeRelation()
**/
void relationDelete(int id);

/**
 * @brief
 * Funkcja dodająca kontakt do kolejki do usunięcia
 * Usuwanie realizowane w funkcji zapisu do pliku
 * @param id - ID kontaktu do usunięcia
 * @see writeContact()
**/
void deleteContact(int id);

/**
 * @brief
 * Funkcja dodająca grupę do kolejki do usunięcia
 * Usuwanie realizowane w funkcji zapisu do pliku
 * @param id - ID grupy do usunięcia
 * @see writeGroup()
**/
void deleteGroup(int id);

/**
 * @brief
 * Funkcja wylogowująca zalogowanego użytkownika
**/
void logout();

/**
 * @brief
 * Funkcja usuwająca zalogowanego użytkownika
**/
void deleteMe();

/**
 * @brief
 * Funkcja zmieniająca hasło zalogowanego użytkownika
**/
void passwd();

/**
 * @brief
 * Funkcja dodająca kontakt do bazy
**/
void addContact();

/**
 * @brief
 * Funkcja dodająca numer telefonu do kontaktu o podanym ID
 * @param ID - ID kontaktu do którego przypisany będzie numer telefonu
**/
void addPhone(int ID);

/**
 * @brief
 * Funkcja dodająca adres e-mail do kontaktu o podanym ID
 * @param ID - ID kontaktu do którego przypisany będzie numer telefonu
**/
void addEMail(int ID);

/**
 * @brief
 * Funkcja dodająca adres pocztowy do kontaktu o podanym ID
 * @param ID - ID kontaktu do którego przypisany będzie numer telefonu
**/
void addAdress(int ID);

/**
 * @brief
 * Funkcja dodająca grupę do bazy
**/
void addGroup();

/**
 * @brief
 * Funkcja przypisująca kontakt do grupy
 * @param ID_Contact - ID kontaktu
 * @param ID_Group - ID grupy
**/
void assignGroup(int ID_Contact, int ID_Group);

/**
 * @brief
 * Funkcja tworząca użytkownika
 * @param str - ciąg znaków zawierający polecenie i login
 * @return true jeżeli dodawanie się powiedzie
 * @return false jeżeli dodawanie się nie powiedzie
**/
bool createUser(char* str);

/**
 * @brief
 * Funkcja logująca użytkownika
 * @param str - ciag znaków zawierający polecenie i login
 * @return true jeżeli logowanie się powiedzie
 * @return false jeżeli logowanie się nie powiedzie
**/
bool loginUser(char* str);

/**
 * @brief
 * Funkcja edytująca kontakt
 * @param ID_Contact - ID kontaktu do edycji
**/
void editContact(int ID_Contact);

#endif