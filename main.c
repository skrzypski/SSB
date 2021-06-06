/**
 * @mainpage
 * <center>
 * Strona zawiera dokumentacje kodu źródłowego programu <h1>SSB</h1> (Skrzypek's & Sokół's contact Base)<br/>
 * Kod źródłowy: https://github.com/skrzypski/SSB
 * </center>
**/
/**
 * @file main.c
 * @brief
 * Plik zawierający główny kod źródłowy
**/
#include "globals.h"
/**
* @brief
* Funkcja inicjalizująca zmienne globalne
**/
void init_globals()
{
	 userList = NULL;
	 userCount = 0;

	 contactList = NULL;
	 contactCount = 0;
	 contactLast = 0;

	 phoneList = NULL;
	 phoneCount = 0;
	 phoneLast = 0;

	 adressList = NULL;
	 adressCount = 0;
	 adressLast = 0;

	 emailList = NULL;
	 emailCount = 0;
	 emailLast = 0;

	 groupList = NULL;
	 groupCount = 0;
	 groupLast = 0;

	 relationList = NULL;
	 relationCount = 0;
	 relationLast = 0;

	 toRemoveContact = NULL;
	 toRemoveContactCount = 0;

	 toRemoveGroup = NULL;
	 toRemoveGroupCount = 0;

	 toRemoveRelation = NULL;
	 toRemoveRelationCount = 0;

	 queueRemoveContact = NULL;
	 queueRemoveContactCount = 0;

	 queueRemoveGroup = NULL;
	 queueRemoveGroupCount = 0;

	 queueRemoveRelation = NULL;
	 queueRemoveRelationCount = 0;
}

/**
* @brief
* Funkcja ładująca ustawienia poczatkowe, sprawdzajaca dostęp do plików i ładująca dane
**/
void setup()
{
	init_globals();

	strcpy(LOGGED_USER, "SSB");
	srand(time(NULL));
	isSaved = false;
	bool errorFlag = false;

	if ((db.users = fopen("users.ssb", "a+")) == NULL) errorFlag = true;
	if ((db.contacts = fopen("contacts.ssb", "a+")) == NULL) errorFlag = true;
	if ((db.phones = fopen("phones.ssb", "a+")) == NULL) errorFlag = true;
	if ((db.emails = fopen("emails.ssb", "a+")) == NULL) errorFlag = true;
	if ((db.adresses = fopen("adresses.ssb", "a+")) == NULL) errorFlag = true;
	if ((db.groups = fopen("groups.ssb", "a+")) == NULL) errorFlag = true;
	if ((db.relations = fopen("relations.ssb", "a+")) == NULL) errorFlag = true;

	if (errorFlag)
	{
		setFg(fg_iRed);
		printf("Blad odczytu plikow!\n");
		system("pause");
		exit(0);
	}

	loadData();
	save();
}

/**
* @brief
* Główna pętla programu obsługująca komendy i wywołująca odpowiednie funkcje. Wywołuje funkcję init_globals()
* @see init_globals()
**/
void loop()
{
	while (1)
	{
		setDefault();
		printf("[");
		setFg(fg_Gold);
		printf("%s", LOGGED_USER);
		setDefault();
		printf("] ");
		char input[INPUT_SIZE];
		fgets(input, INPUT_SIZE, stdin);
		input[strlen(input) - 1] = NULL;
		if (strcmp(input, "help") == 0)
		{
			printHelp();
		}
		else if (strcmp(input, "about") == 0)
		{
			printAbout();
		}
		else if (strcmp(input, "contactadd") == 0)
		{
			addContact();
		}
		else if (strcmp(input, "groupadd") == 0)
		{
			addGroup();
		}
		else if (strcmp(input, "list") == 0)
		{
			printContacts("null");
		}
		else if (strstr(input, "list -k ") != NULL && input[0] == 'l' && input[3] == 't')
		{
			char* key = strtok(input, " ");
			key = strtok(NULL, " ");
			key = strtok(NULL, " ");
			printContacts(key);
		}
		else if (strstr(input, "list -s ") != NULL && input[0] == 'l' && input[3] == 't')
		{
			char* buff = strtok(input, " ");
			int counter = 0;
			char* dir = NULL;
			char* field = NULL;
			while (buff != NULL)
			{
				counter++;
				buff = strtok(NULL, " ");
				if (counter == 2) dir = buff;
				if (counter == 3) field = buff;
			}
			printSorted(dir, field);
		}
		else if (strstr(input, "list -g ") != NULL && input[0] == 'l' && input[3] == 't')
		{
			char* gid = strtok(input, " ");
			gid = strtok(NULL, " ");
			gid = strtok(NULL, " ");
			printContactsGroups(atoi(gid));
		}
		else if (strstr(input, "contactdelete ") != NULL && input[0] == 'c' && input[12] == 'e')
		{
			char* cid = strtok(input, " ");
			cid = strtok(NULL, " ");
			deleteContact(atoi(cid));
		}
		else if (strstr(input, "groupdelete ") != NULL && input[0] == 'g' && input[10] == 'e')
		{
			char* cid = strtok(input, " ");
			cid = strtok(NULL, " ");
			deleteGroup(atoi(cid));
		}
		else if (strcmp(input, "userlist") == 0)
		{
			printUsers();
		}
		else if (strcmp(input, "deleteme") == 0)
		{
			deleteMe();
		}
		else if (strcmp(input, "passwd") == 0)
		{
			passwd();
		}
		else if (strcmp(input, "grouplist") == 0)
		{
			printGroups();
		}
		else if (strcmp(input, "logout") == 0)
		{
			logout();
		}
		else if (strcmp(input, "save") == 0)
		{
			writeData();
			isSaved = save();
			loadData();
			if (isSaved)
			{
				succ("Saved sucefully!");
			}
			else
			{
				err("Data save error!");
			}
		}
		else if (strcmp(input, "bye") == 0)
		{
			if (isSaved)
			{
				succ("Bye :)");
				exit(0);
			}
			else
			{
				err("There are pending changes!");
				int chr = 97 + rand() % 26;
				char msg[54];
				sprintf(msg, "Press \'%c\' to exit without saving", chr);
				succ(msg);
				err("Press other key to return to the menu");
				if (getch() == chr)
				{
					exit(0);
				}
				else
				{
					continue;
				}
			}
		}
		else if (strstr(input, "useradd ") != NULL && input[0] == 'u' && input[6] == 'd')
		{
			if (createUser(input))
			{
				succ("User added succesfully!");
			}
			else
			{
				err("User add error!");
			}

		}
		else if (strstr(input, "userlogin ") != NULL && input[0] == 'u' && input[8] == 'n' && strcmp("userlogin", input) != 0)
		{
			loginUser(input);
		}
		else if (strstr(input, "phoneadd ") != NULL && input[0] == 'p' && input[4] == 'e' && strcmp("phoneadd", input) != 0)
		{
			addPhone(getId(input));
		}
		else if (strstr(input, "emailadd ") != NULL && input[0] == 'e' && input[4] == 'l' && strcmp("emailadd", input) != 0)
		{
			addEMail(getId(input));
		}
		else if (strstr(input, "adressadd ") != NULL && input[0] == 'a' && input[5] == 's' && strcmp("adressadd", input) != 0)
		{
			addAdress(getId(input));
		}
		else if (strstr(input, "groupassign ") != NULL && input[0] == 'g' && input[10] == 'n')
		{
			char* buff;
			buff = strtok(input, " ");
			buff = strtok(NULL, " ");
			int idc = atoi(buff);
			buff = strtok(NULL, " ");
			int idg = atoi(buff);
			assignGroup(idc, idg);
		}
		else if (strstr(input, "groupdeassign ") != NULL && input[0] == 'g' && input[12] == 'n')
		{
			char* cid = strtok(input, " ");
			cid = strtok(NULL, " ");
			relationDelete(atoi(cid));
		}
		else if (strstr(input, "edit ") != NULL && input[0] == 'e' && input[3] == 't')
		{
			editContact(getId(input));
		}
		else
		{
			err("Unknown command!");
		}
	}
}

/**
* @brief
* Funkcja czyszcząca zarezerwowaną pamięć
**/
void cleanup()
{
	free(userList);
	free(contactList);
	free(phoneList);
	free(adressList);
	free(emailList);
	free(groupList);
	free(relationList);
	free(toRemoveContact);
	free(toRemoveGroup);
	free(toRemoveRelation);	
	free(queueRemoveContact);
	free(queueRemoveGroup);
	free(queueRemoveRelation);
}

/**
* @brief
* Funkcja main, wywołująca funkcje setup() oraz loop()
* @see setup()
* @see loop()
**/
int main()
{
	setup();
	loop();
	cleanup();
	return 0;
}