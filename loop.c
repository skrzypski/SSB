/**
 * @file loop.c
 * @brief
 * Kod źródłowy części programu odpowiedzialnej za obsługę poleceń wywoływanych w głównej pętli
**/
#include "globals.h"

void printHelp()
{
	setFg(fg_iWhite);
	printf("help = prints this manual\n");
	printf("about = about the program\n");
	printf("userlist = print all existing users\n");
	printf("useradd [USERNAME]= add user\n");
	printf("userlogin [USERNAME] = login user\n");
	printf("passwd = change actual user password\n");
	printf("deleteme = delete actual user\n");
	printf("logout = logout actual user\n");
	printf("contactadd = add contact\n");
	printf("contactdelete [CONTACT_ID] = delete contact\n");
	printf("groupadd = add group\n");
	printf("groupdelete [GROUP_ID] = delete group\n");
	printf("phoneadd [CONTACT_ID] = add phone number to contact\n");
	printf("emailadd [CONTACT_ID] = add email to contact\n");
	printf("adressadd [CONTACT_ID] = add adress to contact\n");
	printf("edit [CONTACT_ID] = edit contact\n");
	printf("groupassign [CONTACT_ID] [GROUP_ID] = add contact to group\n");
	printf("groupdeassign [RELATION_ID] = remove group from contact\n");
	printf("RELATION_ID is number in the brackets next to group name in contact\n");
	printf("list = print all contacts\n");
	printf("list -k [SEARCH_KEY] = search in contacts and print results\n");
	printf("list -g [ID_GROUP] = print only contacts assigned to given group\n");
	printf("list -s <asc/desc> <name/surname> = print contacts sorted <ASCending/DESCending> by <NAME/SURNAME>\n");
	printf("save = save pending changes\n");
	printf("bye = close program\n");
	setDefault();
}

void printAbout()
{
	setBg(bg_iBlack);
	setFg(fg_iWhite);
	printf("   SSSSSSSSSSSSSSS    SSSSSSSSSSSSSSS BBBBBBBBBBBBBBBBB   \n");
	printf(" SS:::::::::::::::S SS:::::::::::::::SB::::::::::::::::B  \n");
	setFg(fg_iRed);
	printf("S:::::SSSSSS::::::SS:::::SSSSSS::::::SB::::::BBBBBB:::::B \n");
	printf("S:::::S     SSSSSSSS:::::S     SSSSSSSBB:::::B     B:::::B\n");
	setFg(fg_iGreen);
	printf("S:::::S            S:::::S              B::::B     B:::::B\n");
	printf("S:::::S            S:::::S              B::::B     B:::::B\n");
	setFg(fg_iBlue);
	printf(" S::::SSSS          S::::SSSS           B::::BBBBBB:::::B \n");
	printf("  SS::::::SSSSS      SS::::::SSSSS      B:::::::::::::BB  \n");
	setFg(fg_iCyan);
	printf("    SSS::::::::SS      SSS::::::::SS    B::::BBBBBB:::::B \n");
	printf("       SSSSSS::::S        SSSSSS::::S   B::::B     B:::::B\n");
	setFg(fg_iPurple);
	printf("            S:::::S            S:::::S  B::::B     B:::::B\n");
	printf("            S:::::S            S:::::S  B::::B     B:::::B\n");
	setFg(fg_iGold);
	printf("SSSSSSS     S:::::SSSSSSSS     S:::::SBB:::::BBBBBB::::::B\n");
	printf("S::::::SSSSSS:::::SS::::::SSSSSS:::::SB:::::::::::::::::B \n");
	setFg(fg_iWhite);
	printf("S:::::::::::::::SS S:::::::::::::::SS B::::::::::::::::B  \n");
	printf(" SSSSSSSSSSSSSSS    SSSSSSSSSSSSSSS   BBBBBBBBBBBBBBBBB   \n");
	printf("\n");
	setFg(fg_iPurple);
	printf("    ___                             _         _      _    \n");
	printf("   / __\\  ___   _ __   _   _  _ __ (_)  __ _ | |__  | |_  \n");
	printf("  / /    / _ \\ | \'_ \\ | | | || \'__|| | / _` || \'_ \\ | __| \n");
	printf(" / /___ | (_) || |_) || |_| || |   | || (_| || | | || |_  \n");
	printf(" \\____/  \\___/ | .__/  \\__, ||_|   |_| \\__, ||_| |_| \\__| \n");
	printf("               |_|     |___/           |___/              \n");
	setDefault();
	setFg(fg_Gold);
	printf("                                                          \n");
	printf("           contact base developed by SS devTeam           \n");
	printf("                                                          \n");
	printf("            Kacper Skrzypek & Jakub Sokol 2021            \n");
	setDefault();
}

void printUsers()
{
	loadUserlist();
	for (int i = 0; i < userCount; i++)
	{
		printf("%s\n", (userList + i)->login);
	}
}

void printGroups()
{
	for (int i = 0; i < groupCount; i++)
	{
		if (strcmp((groupList + i)->Owner, LOGGED_USER) == 0)
		{
			printf("ID: %d - %s: %s\n", (groupList + i)->ID_Group, (groupList + i)->Name, (groupList + i)->Description);
		}
	}
}

void printContacts(char* searchKey)
{
	for (int i = 0; i < contactCount; i++)
	{
		if (strcmp((contactList + i)->Owner, LOGGED_USER) == 0)
		{
			bool toShow = false;
			if (strcmp(searchKey, "null") == 0) toShow = true;
			else
			{
				if (strstr((contactList + i)->Name, searchKey) != NULL) toShow = true;
				if (strstr((contactList + i)->Surname, searchKey) != NULL) toShow = true;
				if (strstr((contactList + i)->Description, searchKey) != NULL) toShow = true;
				int j = 0;
				for (j = 0; j < phoneCount; j++)
				{
					if ((contactList + i)->ID_Contact == (phoneList + j)->ID_Contact)
					{
						if (strstr((phoneList + j)->Number, searchKey) != NULL) toShow = true;
					}
				}
				for (j = 0; j < emailCount; j++)
				{
					if ((contactList + i)->ID_Contact == (emailList + j)->ID_Contact)
					{
						if (strstr((emailList + j)->Mail, searchKey) != NULL) toShow = true;
					}
				}
				for (j = 0; j < adressCount; j++)
				{
					if ((contactList + i)->ID_Contact == (adressList + j)->ID_Contact)
					{
						if (strstr((adressList + j)->FirstLine, searchKey) != NULL) toShow = true;
						if (strstr((adressList + j)->SecondLine, searchKey) != NULL) toShow = true;
						if (strstr((adressList + j)->PostalCode, searchKey) != NULL) toShow = true;
						if (strstr((adressList + j)->City, searchKey) != NULL) toShow = true;
					}
				}
				for (j = 0; j < relationCount; j++)
				{
					if ((contactList + i)->ID_Contact == (relationList + j)->ID_Contact)
					{
						for (int k = 0; k < groupCount; k++)
						{
							if ((relationList + j)->ID_Group == (groupList + k)->ID_Group)
							{
								if (strstr((groupList + k)->Name, searchKey) != NULL) toShow = true;
							}
						}

					}
				}
			}
			if (toShow)
			{
				printf("ID: %d\n", (contactList + i)->ID_Contact);
				printf("Name: %s\n", (contactList + i)->Name);
				printf("Surname: %s\n", (contactList + i)->Surname);
				printf("Description: %s\n", (contactList + i)->Description);
				int j = 0;
				for (j = 0; j < phoneCount; j++)
				{
					if ((contactList + i)->ID_Contact == (phoneList + j)->ID_Contact)
					{
						if ((phoneList + j)->toRemove == false)
						{
							printf("Phone: %s\n", (phoneList + j)->Number);
						}
					}
				}
				for (j = 0; j < emailCount; j++)
				{
					if ((contactList + i)->ID_Contact == (emailList + j)->ID_Contact)
					{
						if ((emailList + j)->toRemove == false)
						{
							printf("E-Mail: %s\n", (emailList + j)->Mail);
						}
					}
				}
				for (j = 0; j < adressCount; j++)
				{
					if ((contactList + i)->ID_Contact == (adressList + j)->ID_Contact)
					{
						if ((adressList + j)->toRemove == false)
						{
							printf("Adress:\n");
							printf("%s\n", (adressList + j)->FirstLine);
							if (strcmp((adressList + j)->SecondLine, "null") != 0) printf("%s\n", (adressList + j)->SecondLine);
							printf("%s, %s\n", (adressList + j)->PostalCode, (adressList + j)->City);
						}
					}
				}
				bool anyGroup = false;
				for (j = 0; j < relationCount; j++)
				{
					if ((contactList + i)->ID_Contact == (relationList + j)->ID_Contact)
					{
						for (int k = 0; k < groupCount; k++)
						{
							if ((relationList + j)->ID_Group == (groupList + k)->ID_Group)
							{
								if (anyGroup == false)
								{
									printf("Groups: ");
									anyGroup = true;
								}
								printf("%s(%d) ", (groupList + k)->Name, (relationList + j)->ID_Relation);
							}
						}

					}
				}
				printf("\n\n");
			}
		}
	}
}

void printSorted(char* dir, char* field)
{
	struct Contact* contactSorted = (struct Contact*)malloc(contactCount * sizeof(struct Contact));
	for (int i = 0; i < contactCount; i++)
	{
		contactSorted[i] = contactList[i];
	}
	for (int i = 0; i < contactCount; i++)
	{
		for (int j = 1; j < contactCount - i; j++)
		{
			if (strcmp(dir, "asc") == 0)
			{
				if (strcmp(field, "name") == 0)
				{
					if (strcmp(contactSorted[j - 1].Name, contactSorted[j].Name) > 0)
					{
						swap(&contactSorted[j - 1], &contactSorted[j]);
					}
				}
				else if (strcmp(field, "surname") == 0)
				{
					if (strcmp(contactSorted[j - 1].Surname, contactSorted[j].Surname) > 0)
					{
						swap(&contactSorted[j - 1], &contactSorted[j]);
					}
				}
			}
			else if (strcmp(dir, "desc") == 0)
			{
				if (strcmp(field, "name") == 0)
				{
					if (strcmp(contactSorted[j - 1].Name, contactSorted[j].Name) < 0)
					{
						swap(&contactSorted[j - 1], &contactSorted[j]);
					}
				}
				else if (strcmp(field, "surname") == 0)
				{
					if (strcmp(contactSorted[j - 1].Surname, contactSorted[j].Surname) < 0)
					{
						swap(&contactSorted[j - 1], &contactSorted[j]);
					}
				}
			}
		}
	}
	for (int i = 0; i < contactCount; i++)
	{
		if (strcmp((contactList + i)->Owner, LOGGED_USER) == 0)
		{
			printf("ID: %d\n", (contactSorted + i)->ID_Contact);
			printf("Name: %s\n", (contactSorted + i)->Name);
			printf("Surname: %s\n", (contactSorted + i)->Surname);
			printf("Description: %s\n", (contactSorted + i)->Description);
			int j = 0;
			for (j = 0; j < phoneCount; j++)
			{
				if ((contactSorted + i)->ID_Contact == (phoneList + j)->ID_Contact)
				{
					printf("Phone: %s\n", (phoneList + j)->Number);
				}
			}
			for (j = 0; j < emailCount; j++)
			{
				if ((contactSorted + i)->ID_Contact == (emailList + j)->ID_Contact)
				{
					printf("E-Mail: %s\n", (emailList + j)->Mail);
				}
			}
			for (j = 0; j < adressCount; j++)
			{
				if ((contactSorted + i)->ID_Contact == (adressList + j)->ID_Contact)
				{
					printf("Adress:\n");
					printf("%s\n", (adressList + j)->FirstLine);
					if (strcmp((adressList + j)->SecondLine, "null") != 0) printf("%s\n", (adressList + j)->SecondLine);
					printf("%s, %s\n", (adressList + j)->PostalCode, (adressList + j)->City);
				}
			}
			bool anyGroup = false;
			for (j = 0; j < relationCount; j++)
			{
				if ((contactSorted + i)->ID_Contact == (relationList + j)->ID_Contact)
				{
					for (int k = 0; k < groupCount; k++)
					{
						if ((relationList + j)->ID_Group == (groupList + k)->ID_Group)
						{
							if (anyGroup == false)
							{
								printf("Groups: ");
								anyGroup = true;
							}
							printf("%s(%d) ", (groupList + k)->Name, (relationList + j)->ID_Relation);
						}
					}

				}
			}
			printf("\n\n");
		}
	}
}

void printContactsGroups(int ID_Group)
{
	for (int i = 0; i < contactCount; i++)
	{
		if (strcmp((contactList + i)->Owner, LOGGED_USER) == 0)
		{
			bool toShow = false;
			for (int j = 0; j < relationCount; j++)
			{
				if ((contactList + i)->ID_Contact == (relationList + j)->ID_Contact)
				{
					for (int k = 0; k < groupCount; k++)
					{
						if ((relationList + j)->ID_Group == (groupList + k)->ID_Group)
						{
							if (ID_Group == (groupList + k)->ID_Group) toShow = true;
						}
					}

				}
			}
			if (toShow)
			{
				printf("ID: %d\n", (contactList + i)->ID_Contact);
				printf("Name: %s\n", (contactList + i)->Name);
				printf("Surname: %s\n", (contactList + i)->Surname);
				printf("Description: %s\n", (contactList + i)->Description);
				int j = 0;
				for (j = 0; j < phoneCount; j++)
				{
					if ((contactList + i)->ID_Contact == (phoneList + j)->ID_Contact)
					{
						if ((phoneList + j)->toRemove == false)
						{
							printf("Phone: %s\n", (phoneList + j)->Number);
						}
					}
				}
				for (j = 0; j < emailCount; j++)
				{
					if ((contactList + i)->ID_Contact == (emailList + j)->ID_Contact)
					{
						if ((emailList + j)->toRemove == false)
						{
							printf("E-Mail: %s\n", (emailList + j)->Mail);
						}
					}
				}
				for (j = 0; j < adressCount; j++)
				{
					if ((contactList + i)->ID_Contact == (adressList + j)->ID_Contact)
					{
						if ((adressList + j)->toRemove == false)
						{
							printf("Adress:\n");
							printf("%s\n", (adressList + j)->FirstLine);
							if (strcmp((adressList + j)->SecondLine, "null") != 0) printf("%s\n", (adressList + j)->SecondLine);
							printf("%s, %s\n", (adressList + j)->PostalCode, (adressList + j)->City);
						}
					}
				}
				bool anyGroup = false;
				for (j = 0; j < relationCount; j++)
				{
					if ((contactList + i)->ID_Contact == (relationList + j)->ID_Contact)
					{
						for (int k = 0; k < groupCount; k++)
						{
							if ((relationList + j)->ID_Group == (groupList + k)->ID_Group)
							{
								if (anyGroup == false)
								{
									printf("Groups: ");
									anyGroup = true;
								}
								printf("%s(%d) ", (groupList + k)->Name, (relationList + j)->ID_Relation);
							}
						}

					}
				}
				printf("\n\n");
			}
		}
	}
}

void deleteContact(int id)
{
	bool owned = false;
	for (int i = 0; i < contactCount; i++)
	{
		if (id == contactList[i].ID_Contact)
		{
			if (strcmp(LOGGED_USER, contactList[i].Owner) == 0)
			{
				owned = true;
			}
		}
	}
	if (!owned)
	{
		err("Contact do not exists!");
		return;
	}
	queueRemoveContactCount++;
	queueRemoveContact = (int*)realloc(queueRemoveContact, queueRemoveContactCount * sizeof(int));
	*(queueRemoveContact + queueRemoveContactCount - 1) = id;
	save();
}

void deleteGroup(int id)
{
	bool owned = false;
	for (int i = 0; i < groupCount; i++)
	{
		if (id == groupList[i].ID_Group)
		{
			if (strcmp(LOGGED_USER, groupList[i].Owner) == 0)
			{
				owned = true;
			}
		}
	}
	if (!owned)
	{
		err("Group do not exists!");
		return;
	}
	queueRemoveGroupCount++;
	queueRemoveGroup = (int*)realloc(queueRemoveGroup, queueRemoveGroupCount * sizeof(int));
	*(queueRemoveGroup + queueRemoveGroupCount - 1) = id;
	save();
}

void relationDelete(int id)
{
	queueRemoveRelationCount++;
	queueRemoveRelation = (int*)realloc(queueRemoveRelation, queueRemoveRelationCount * sizeof(int));
	*(queueRemoveRelation + queueRemoveRelationCount - 1) = id;
	save();
}

void logout()
{
	strcpy(LOGGED_USER, "SSB");
	succ("Logout succesful!");
}

void deleteMe()
{
	for (int i = 0; i < userCount; i++)
	{
		if (strcmp(LOGGED_USER, (userList + i)->login) == 0)
		{
			(userList + i)->toRemove = true;
			succ("User deleted!");
			logout();
			writeUsers();
			break;
		}
	}
}

void passwd()
{
	if (strcmp(LOGGED_USER, "SSB") == 0)
	{
		err("User not logged!");
	}
	else
	{
		char* oldPass = NULL;
		for (int i = 0; i < userCount; i++)
		{
			if (strcmp(LOGGED_USER, (userList + i)->login) == 0)
			{
				oldPass = &((userList + i)->hash);
				break;
			}
		}
		char actualPass[33];
		getPass("Old password:", actualPass);
		if (oldPass != NULL)
		{
			if (strcmp(oldPass, actualPass) == 0) //jezeli takie same
			{
				char fpass[33];
				char spass[33];
				getPass("New password: ", fpass);
				getPass("Confirm password: ", spass);
				if (strcmp(fpass, spass) == 0) //wprowadzone hasla takie same
				{
					strcpy(oldPass, fpass);
					writeUsers();
					succ("Changed succesful!");
				}
				else
				{
					err("Passwords do not match!");
				}
			}
			else
			{
				err("Wrong password!");
			}
		}
	}
}

void addContact()
{
	char name[ENTRY_SIZE];
	char surname[ENTRY_SIZE];
	char description[INPUT_SIZE];
	printf("Name: ");
	fgets(name, ENTRY_SIZE, stdin);
	printf("Surname: ");
	fgets(surname, ENTRY_SIZE, stdin);
	printf("Description: ");
	fgets(description, INPUT_SIZE, stdin);
	name[strlen(name) - 1] = NULL;
	surname[strlen(surname) - 1] = NULL;
	description[strlen(description) - 1] = NULL;
	contactCount++;
	contactList = realloc(contactList, contactCount * sizeof(struct Contact));
	strcpy((contactList + contactCount - 1)->Owner, LOGGED_USER);
	(contactList + contactCount - 1)->toRemove = false;
	contactLast++;
	(contactList + contactCount - 1)->ID_Contact = contactLast;
	strcpy((contactList + contactCount - 1)->Name, name);
	strcpy((contactList + contactCount - 1)->Surname, surname);
	strcpy((contactList + contactCount - 1)->Description, description);
	isSaved = false;
	save();
}

void addPhone(int ID)
{
	if (ID > contactLast)
	{
		err("Contact not exists!");
		return;
	}
	bool exists = false;
	for (int i = 0; i < contactCount; i++)
	{
		if (ID == (contactList + i)->ID_Contact && strcmp(LOGGED_USER, (contactList + i)->Owner) == 0)
		{
			exists = true;
		}
		if (exists == true) break;
	}
	if (exists == false)
	{
		err("Contact not exists!");
		return;
	}
	char phone[11];
	printf("Phone: ");
	fgets(phone, 11, stdin);
	phone[strlen(phone) - 1] = NULL;
	phoneCount++;
	phoneList = realloc(phoneList, phoneCount * sizeof(struct Phone));
	phoneLast++;
	(phoneList + phoneCount - 1)->ID_Phone = phoneLast;
	(phoneList + phoneCount - 1)->ID_Contact = ID;
	strcpy((phoneList + phoneCount - 1)->Number, phone);
	isSaved = false;
	save();
}

void addEMail(int ID)
{
	if (ID > contactLast)
	{
		err("Contact not exists!");
		return;
	}
	bool exists = false;
	for (int i = 0; i < contactCount; i++)
	{
		if (ID == (contactList + i)->ID_Contact && strcmp(LOGGED_USER, (contactList + i)->Owner) == 0)
		{
			exists = true;
		}
		if (exists == true) break;
	}
	if (exists == false)
	{
		err("Contact not exists!");
		return;
	}
	char mail[ENTRY_SIZE];
	printf("E-Mail: ");
	fgets(mail, ENTRY_SIZE, stdin);
	mail[strlen(mail) - 1] = NULL;
	emailCount++;
	emailList = realloc(emailList, emailCount * sizeof(struct Email));
	emailLast++;
	(emailList + emailCount - 1)->ID_Email = emailLast;
	(emailList + emailCount - 1)->ID_Contact = ID;
	strcpy((emailList + emailCount - 1)->Mail, mail);
	isSaved = false;
	save();
}

void addAdress(int ID)
{
	if (ID > contactLast)
	{
		err("Contact not exists!");
		return;
	}
	bool exists = false;
	for (int i = 0; i < contactCount; i++)
	{
		if (ID == (contactList + i)->ID_Contact && strcmp(LOGGED_USER, (contactList + i)->Owner) == 0)
		{
			exists = true;
		}
		if (exists == true) break;
	}
	if (exists == false)
	{
		err("Contact not exists!");
		return;
	}
	char fline[ENTRY_SIZE];
	char sline[ENTRY_SIZE];
	char postal[8];
	char city[ENTRY_SIZE];
	printf("Adress first line: ");
	fgets(fline, ENTRY_SIZE, stdin);
	fline[strlen(fline) - 1] = NULL;
	printf("Adress second line (if empty type \"null\"): ");
	fgets(sline, ENTRY_SIZE, stdin);
	sline[strlen(sline) - 1] = NULL;
	printf("Postal code (format: dd-ddd): ");
	fgets(postal, 8, stdin);
	postal[strlen(postal) - 1] = NULL;
	printf("City: ");
	fgets(city, ENTRY_SIZE, stdin);
	city[strlen(city) - 1] = NULL;
	adressCount++;
	adressList = realloc(adressList, adressCount * sizeof(struct Adress));
	adressLast++;
	(adressList + adressCount - 1)->ID_Adress = adressLast;
	(adressList + adressCount - 1)->ID_Contact = ID;
	strcpy((adressList + adressCount - 1)->FirstLine, fline);
	strcpy((adressList + adressCount - 1)->SecondLine, sline);
	strcpy((adressList + adressCount - 1)->PostalCode, postal);
	strcpy((adressList + adressCount - 1)->City, city);
	isSaved = false;
	save();
}

void addGroup()
{
	char name[ENTRY_SIZE];
	char desc[INPUT_SIZE];
	printf("Name: ");
	fgets(name, ENTRY_SIZE, stdin);
	name[strlen(name) - 1] = NULL;
	printf("Description: ");
	fgets(desc, INPUT_SIZE, stdin);
	desc[strlen(desc) - 1] = NULL;
	groupCount++;
	groupList = realloc(groupList, groupCount * sizeof(struct Group));
	groupLast++;
	(groupList + groupCount - 1)->ID_Group = groupLast;
	(groupList + groupCount - 1)->toRemove = false;
	strcpy((groupList + groupCount - 1)->Owner, LOGGED_USER);
	strcpy((groupList + groupCount - 1)->Name, name);
	strcpy((groupList + groupCount - 1)->Description, desc);
	isSaved = false;
	save();
}

void assignGroup(int ID_Contact, int ID_Group)
{
	if (ID_Contact > contactLast)
	{
		err("Contact not exists!");
		return;
	}
	bool cexists = false;
	for (int i = 0; i < contactCount; i++)
	{
		if (ID_Contact == (contactList + i)->ID_Contact && strcmp(LOGGED_USER, (contactList + i)->Owner) == 0)
		{
			cexists = true;
		}
		if (cexists == true) break;
	}
	if (cexists == false)
	{
		err("Contact not exists!");
		return;
	}
	if (ID_Group > groupLast)
	{
		err("Group not exists!");
		return;
	}
	bool gexists = false;
	for (int i = 0; i < groupCount; i++)
	{
		if (ID_Group == (groupList + i)->ID_Group && strcmp(LOGGED_USER, (groupList + i)->Owner) == 0)
		{
			gexists = true;
		}
		if (gexists == true) break;
	}
	if (gexists == false)
	{
		err("Group not exists!");
		return;
	}
	relationCount++;
	relationList = realloc(relationList, relationCount * sizeof(struct Relation));
	relationLast++;
	(relationList + relationCount - 1)->ID_Relation = relationLast;
	(relationList + relationCount - 1)->ID_Contact = ID_Contact;
	(relationList + relationCount - 1)->ID_Group = ID_Group;
	isSaved = false;
	save();
}

bool createUser(char* str)
{
	if (strcmp(LOGGED_USER, "SSB") != 0)
	{
		err("User logged!");
		return false;
	}
	bool userExists = false;
	char username[128];
	char* buff;
	int counter = 0;
	buff = strtok(str, " ");
	while (buff != NULL)
	{
		if (counter == 1) strcpy(username, buff);
		counter++;
		if (counter == 2) break;
		buff = strtok(NULL, " ");
	}
	if (counter != 2)
	{
		err("Too few arguments!");
		return false;
	}
	loadUserlist();
	if (userCount != 0)
	{
		for (int i = 0; i < userCount; i++)
		{
			if (strcmp(username, (userList + i)->login) == 0)
			{
				userExists = true;
				break;
			}
		}
	}
	if (userExists)
	{
		err("User exists!");
		return false;
	}
	char fpass[33];
	char spass[33];
	getPass("Password:", fpass);
	if (strcmp(fpass, "d41d8cd98f00b204e9800998ecf8427e") == 0) //check if pass is empty
	{
		err("Password cannot be empty!");
		return false;
	}
	getPass("Confirm password:", spass);
	if (strcmp(fpass, spass) != 0)
	{
		err("Passwords do not match!");
		return false;
	}
	char users_entry[128];
	sprintf(users_entry, "%s;%s", username, fpass);
	db.users = fopen("users.ssb", "a");
	writeString(users_entry, db.users);
	fclose(db.users);
	loadUserlist();
	isSaved = false;
	return true;
}

bool loginUser(char* str)
{
	loadUserlist();
	if (strcmp(LOGGED_USER, "SSB") != 0)
	{
		err("User logged!");
		return;
	}
	char username[128];
	char* buff;
	int counter = 0;
	buff = strtok(str, " ");
	while (buff != NULL)
	{
		if (counter == 1) strcpy(username, buff);
		counter++;
		if (counter == 2) break;
		buff = strtok(NULL, " ");
	}
	if (counter != 2)
	{
		err("Too few arguments!");
		return false;
	}
	bool userExists = false;
	char userHash[33];
	for (int i = 0; i < userCount; i++)
	{
		if (strcmp(username, (userList + i)->login) == 0)
		{
			userExists = true;
			strcpy(userHash, (userList + i)->hash);
		}
	}
	if (userExists == false)
	{
		err("User not exists!");
		return false;
	}
	char pass[33];
	getPass("Password: ", pass);
	if (strcmp(pass, userHash) == 0)
	{
		succ("Login succesful!");
		strcpy(LOGGED_USER, username);
		return true;
	}
	else
	{
		err("Wrong password!");
		return false;
	}
}

void editContact(int ID_Contact)
{
	struct Contact* e = NULL;
	for (int i = 0; i < contactCount; i++)
	{
		if (ID_Contact == (contactList + i)->ID_Contact && strcmp(LOGGED_USER, (contactList + i)->Owner) == 0)
		{
			e = contactList + i;
			break;
		}
	}
	if (e == NULL)
	{
		err("Contact not found!");
		return;
	}
	char newData[ENTRY_SIZE];
	char newDesc[INPUT_SIZE];
	succ("To change acutal field write new data");
	succ("To not change data press ENTER");
	succ("To delete field other than Name, Surname or Description write \"del\"");
	succ("To delete whole address write: \"del\" in the adress first line");
	succ("To delete second line of address write: \"null\"");
	printf("Name(%s): ", e->Name);
	fgets(newData, ENTRY_SIZE, stdin);
	newData[strlen(newData) - 1] = NULL;
	if (strcmp(newData, "") != 0)
	{
		strcpy(e->Name, newData);
	}
	printf("Surname(%s): ", e->Surname);
	fgets(newData, ENTRY_SIZE, stdin);
	newData[strlen(newData) - 1] = NULL;
	if (strcmp(newData, "") != 0)
	{
		strcpy(e->Surname, newData);
	}
	printf("Description(%s): ", e->Description);
	fgets(newDesc, INPUT_SIZE, stdin);
	newDesc[strlen(newDesc) - 1] = NULL;
	if (strcmp(newDesc, "") != 0)
	{
		strcpy(e->Description, newDesc);
	}
	int i;
	for (i = 0; i < phoneCount; i++)
	{
		if (e->ID_Contact == (phoneList + i)->ID_Contact)
		{
			printf("Phone(%s): ", (phoneList + i)->Number);
			fgets(newData, 11, stdin);
			newData[strlen(newData) - 1] = NULL;
			if (strcmp(newData, "") != 0)
			{
				if (strcmp(newData, "del") != 0)
				{
					strcpy((phoneList + i)->Number, newData);
				}
				else if (strcmp(newData, "del") == 0)
				{
					(phoneList + i)->toRemove = true;
				}
			}
		}
	}
	for (i = 0; i < emailCount; i++)
	{
		if (e->ID_Contact == (emailList + i)->ID_Contact)
		{
			printf("E-mail(%s): ", (emailList + i)->Mail);
			fgets(newData, ENTRY_SIZE, stdin);
			newData[strlen(newData) - 1] = NULL;
			if (strcmp(newData, "") != 0)
			{
				if (strcmp(newData, "del") != 0)
				{
					strcpy((emailList + i)->Mail, newData);
				}
				else if (strcmp(newData, "del") == 0)
				{
					(emailList + i)->toRemove = true;
				}
			}
		}
	}
	for (i = 0; i < adressCount; i++)
	{
		if (e->ID_Contact == (adressList + i)->ID_Contact)
		{
			printf("Adress first line(%s): ", (adressList + i)->FirstLine);
			fgets(newData, ENTRY_SIZE, stdin);
			newData[strlen(newData) - 1] = NULL;
			if (strcmp(newData, "") != 0)
			{
				if (strcmp(newData, "del") != 0)
				{
					strcpy((adressList + i)->FirstLine, newData);
				}
				else if (strcmp(newData, "del") == 0)
				{
					(adressList + i)->toRemove = true;
				}
			}
			if ((adressList + i)->toRemove != true)
			{
				printf("Adress second line(%s): ", (adressList + i)->SecondLine);
				fgets(newData, ENTRY_SIZE, stdin);
				newData[strlen(newData) - 1] = NULL;
				if (strcmp(newData, "") != 0)
				{
					if (strcmp(newData, "del") != 0)
					{
						strcpy((adressList + i)->SecondLine, newData);
					}
				}
				printf("Postal code(%s): ", (adressList + i)->PostalCode);
				fgets(newData, 8, stdin);
				newData[strlen(newData) - 1] = NULL;
				if (strcmp(newData, "") != 0)
				{
					if (strcmp(newData, "del") != 0)
					{
						strcpy((adressList + i)->PostalCode, newData);
					}
				}
				printf("City(%s): ", (adressList + i)->City);
				fgets(newData, ENTRY_SIZE, stdin);
				newData[strlen(newData) - 1] = NULL;
				if (strcmp(newData, "") != 0)
				{
					if (strcmp(newData, "del") != 0)
					{
						strcpy((adressList + i)->City, newData);
					}
				}
			}
		}
	}
	save();
}