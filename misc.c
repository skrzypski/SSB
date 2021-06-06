/**
 * @file misc.c
 * @brief
 * Kod źródłowy części programu zawierającej wszelkie funkcje pomocnicze
**/
#include "globals.h"

bool save()
{
	fclose(db.users);
	fclose(db.contacts);
	fclose(db.phones);
	fclose(db.emails);
	fclose(db.adresses);
	fclose(db.groups);
	fclose(db.relations);
	return true;
}

void succ(char* str)
{
	setFg(fg_iGreen);
	printf("%s\n", str);
	setDefault();
}

void err(char* str)
{
	setFg(fg_iRed);
	printf("%s\n", str);
	setDefault();
}

int getId(char* str)
{
	char* buff;
	buff = strtok(str, " ");
	buff = strtok(NULL, " ");
	return atoi(buff);
}

void getPass(char* prompt, char* out)
{
	char input[INPUT_SIZE];
	printf("%s", prompt);
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	fgets(input, INPUT_SIZE, stdin);
	SetConsoleMode(hStdin, mode);
	input[strlen(input) - 1] = NULL;
	GetMD5String(input, out);
	printf("\n");
}

void loadUserlist()
{
	db.users = fopen("users.ssb", "r");
	userCount = 0;
	int count = 0;
	char input_line[ENTRY_SIZE];
	while (fgets(input_line, ENTRY_SIZE, db.users)) count++;
	fclose(db.users);
	db.users = fopen("users.ssb", "r");
	if (count != 0)
	{
		userList = (struct Users*)malloc(count * sizeof(struct Users));
		while (fgets(input_line, ENTRY_SIZE, db.users))
		{
			userCount++;
			(userList + userCount - 1)->toRemove = false;
			input_line[strlen(input_line) - 1] = NULL;
			char* buffer;
			buffer = strtok(input_line, ";");
			int tokCount = 0;
			while (buffer != NULL)
			{
				if (tokCount == 0) strcpy((userList + userCount - 1)->login, buffer);
				if (tokCount == 1) strcpy((userList + userCount - 1)->hash, buffer);
				tokCount++;
				buffer = strtok(NULL, ";");
			}
		}
	}
	fclose(db.users);
}

void loadData()
{
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

	db.contacts = fopen("contacts.ssb", "r");
	db.phones = fopen("phones.ssb", "r");
	db.emails = fopen("emails.ssb", "r");
	db.adresses = fopen("adresses.ssb", "r");
	db.groups = fopen("groups.ssb", "r");
	db.relations = fopen("relations.ssb", "r");;
	char buffer[1024];
	int tokCount;
	char* tokBuff;
	while (fgets(buffer, 1024, db.contacts))
	{
		contactCount++;
		contactList = realloc(contactList, contactCount * sizeof(struct Contact));
		(contactList + contactCount - 1)->toRemove = false;
		tokCount = -1;
		tokBuff = strtok(buffer, ";");
		while (tokBuff != NULL)
		{
			tokCount++;
			if (tokCount == 0) strcpy((contactList + contactCount - 1)->Owner, tokBuff);
			else if (tokCount == 1) (contactList + contactCount - 1)->ID_Contact = atoi(tokBuff);
			else if (tokCount == 2) strcpy((contactList + contactCount - 1)->Name, tokBuff);
			else if (tokCount == 3) strcpy((contactList + contactCount - 1)->Surname, tokBuff);
			else if (tokCount == 4) strcpy((contactList + contactCount - 1)->Description, tokBuff);
			tokBuff = strtok(NULL, ";");
		}
	}
	if (contactCount != 0) contactLast = (contactList + contactCount - 1)->ID_Contact;
	while (fgets(buffer, 1024, db.phones))
	{
		phoneCount++;
		phoneList = realloc(phoneList, phoneCount * sizeof(struct Phone));
		(phoneList + phoneCount - 1)->toRemove = false;
		tokCount = -1;
		tokBuff = strtok(buffer, ";");
		while (tokBuff != NULL)
		{
			tokCount++;
			if (tokCount == 0) (phoneList + phoneCount - 1)->ID_Phone = atoi(tokBuff);
			else if (tokCount == 1) (phoneList + phoneCount - 1)->ID_Contact = atoi(tokBuff);
			else if (tokCount == 2) strcpy((phoneList + phoneCount - 1)->Number, tokBuff);
			tokBuff = strtok(NULL, ";");
		}
	}
	if (phoneCount != 0) phoneLast = (phoneList + phoneCount - 1)->ID_Phone;
	while (fgets(buffer, 1024, db.emails))
	{
		emailCount++;
		emailList = realloc(emailList, emailCount * sizeof(struct Email));
		(emailList + emailCount - 1)->toRemove = false;
		tokCount = -1;
		tokBuff = strtok(buffer, ";");
		while (tokBuff != NULL)
		{
			tokCount++;
			if (tokCount == 0) (emailList + emailCount - 1)->ID_Email = atoi(tokBuff);
			else if (tokCount == 1) (emailList + emailCount - 1)->ID_Contact = atoi(tokBuff);
			else if (tokCount == 2) strcpy((emailList + emailCount - 1)->Mail, tokBuff);
			tokBuff = strtok(NULL, ";");
		}
	}
	if (emailCount != 0) emailLast = (emailList + emailCount - 1)->ID_Email;
	while (fgets(buffer, 1024, db.adresses))
	{
		adressCount++;
		adressList = realloc(adressList, adressCount * sizeof(struct Adress));
		(adressList + adressCount - 1)->toRemove = false;
		tokCount = -1;
		tokBuff = strtok(buffer, ";");
		while (tokBuff != NULL)
		{
			tokCount++;
			if (tokCount == 0) (adressList + adressCount - 1)->ID_Adress = atoi(tokBuff);
			else if (tokCount == 1) (adressList + adressCount - 1)->ID_Contact = atoi(tokBuff);
			else if (tokCount == 2) strcpy((adressList + adressCount - 1)->FirstLine, tokBuff);
			else if (tokCount == 3) strcpy((adressList + adressCount - 1)->SecondLine, tokBuff);
			else if (tokCount == 4) strcpy((adressList + adressCount - 1)->PostalCode, tokBuff);
			else if (tokCount == 5) strcpy((adressList + adressCount - 1)->City, tokBuff);
			tokBuff = strtok(NULL, ";");
		}
	}
	if (adressCount != 0) adressLast = (adressList + adressCount - 1)->ID_Adress;
	while (fgets(buffer, 1024, db.groups))
	{
		groupCount++;
		groupList = realloc(groupList, groupCount * sizeof(struct Group));
		(groupList + groupCount - 1)->toRemove = false;
		tokCount = -1;
		tokBuff = strtok(buffer, ";");
		while (tokBuff != NULL)
		{
			tokCount++;
			if (tokCount == 0) strcpy((groupList + groupCount - 1)->Owner, tokBuff);
			else if (tokCount == 1) (groupList + groupCount - 1)->ID_Group = atoi(tokBuff);
			else if (tokCount == 2) strcpy((groupList + groupCount - 1)->Name, tokBuff);
			else if (tokCount == 3) strcpy((groupList + groupCount - 1)->Description, tokBuff);
			tokBuff = strtok(NULL, ";");
		}
	}
	if (groupCount != 0) groupLast = (groupList + groupCount - 1)->ID_Group;
	while (fgets(buffer, 1024, db.relations))
	{
		relationCount++;
		relationList = realloc(relationList, relationCount * sizeof(struct Relation));
		(relationList + relationCount - 1)->toRemove = false;
		tokCount = -1;
		tokBuff = strtok(buffer, ";");
		while (tokBuff != NULL)
		{
			tokCount++;
			if (tokCount == 0) (relationList + relationCount - 1)->ID_Relation = atoi(tokBuff);
			else if (tokCount == 1) (relationList + relationCount - 1)->ID_Contact = atoi(tokBuff);
			else if (tokCount == 2) (relationList + relationCount - 1)->ID_Group = atoi(tokBuff);
			tokBuff = strtok(NULL, ";");
		}
	}
	if (relationCount != 0) relationLast = (relationList + relationCount - 1)->ID_Relation;
	save();
}

void swap(struct Contact* c1, struct Contact* c2)
{
	struct Contact temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}