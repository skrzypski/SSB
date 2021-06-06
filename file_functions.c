/**
 * @file file_functions.c
 * @brief
 * Kod źródłowy części programu odpowiedzialnej za zapis danych do plików
**/
#include "globals.h"

void writeString(char* str, FILE* f)
{
	fprintf(f, "%s\n", str);
}

void writeContact()
{
	for (int i = 0; i < contactCount; i++)
	{
		struct Contact* c = contactList + i;
		for (int j = 0; j < queueRemoveContactCount; j++)
		{
			if (c->ID_Contact == *(queueRemoveContact + j))
			{
				c->toRemove = true;
			}
		}
	}
	queueRemoveContact = NULL;
	queueRemoveContactCount = 0;
	FILE* f = fopen("contacts.ssb", "w");
	for (int i = 0; i < contactCount; i++)
	{
		struct Contact c = *(contactList + i);
		if (c.toRemove == false)
		{
			fprintf(f, "%s;%d;%s;%s;%s;\n", c.Owner, c.ID_Contact, c.Name, c.Surname, c.Description);
		}
		else
		{
			toRemoveContactCount++;
			toRemoveContact = realloc(toRemoveContact, toRemoveContactCount * sizeof(int));
			*(toRemoveContact + toRemoveContactCount - 1) = i + 1;
		}
	}
	fclose(f);
}

void writePhone()
{
	FILE* f = fopen("phones.ssb", "w");
	for (int i = 0; i < phoneCount; i++)
	{
		bool toSave = true;
		struct Phone p = *(phoneList + i);
		for (int j = 0; j < toRemoveContactCount; j++)
		{
			if (p.ID_Contact == *(toRemoveContact + j))
			{
				toSave = false;
				break;
			}
		}
		if (toSave)
		{
			if (p.toRemove == false)
			{
				fprintf(f, "%d;%d;%s;\n", p.ID_Phone, p.ID_Contact, p.Number);
			}
		}
	}
	fclose(f);
}

void writeAdress()
{
	FILE* f = fopen("adresses.ssb", "w");
	for (int i = 0; i < adressCount; i++)
	{
		bool toSave = true;
		struct Adress a = *(adressList + i);
		for (int j = 0; j < toRemoveContactCount; j++)
		{
			if (a.ID_Contact == *(toRemoveContact + j))
			{
				toSave = false;
				break;
			}
		}
		if (toSave)
		{
			if (a.toRemove == false)
			{
				fprintf(f, "%d;%d;%s;%s;%s;%s;\n", a.ID_Adress, a.ID_Contact, a.FirstLine, a.SecondLine, a.PostalCode, a.City);
			}
		}
	}
	fclose(f);
}

void writeEmail()
{
	FILE* f = fopen("emails.ssb", "w");
	for (int i = 0; i < emailCount; i++)
	{
		bool toSave = true;
		struct Email e = *(emailList + i);
		for (int j = 0; j < toRemoveContactCount; j++)
		{
			if (e.ID_Contact == *(toRemoveContact + j))
			{
				toSave = false;
				break;
			}
		}
		if (toSave)
		{
			if (e.toRemove == false)
			{
				fprintf(f, "%d;%d;%s;\n", e.ID_Email, e.ID_Contact, e.Mail);
			}
		}
	}
	fclose(f);
}

void writeGroup()
{
	for (int i = 0; i < groupCount; i++)
	{
		struct Group* g = groupList + i;
		for (int j = 0; j < queueRemoveGroupCount; j++)
		{
			if (g->ID_Group == *(queueRemoveGroup + j))
			{
				g->toRemove = true;
			}
		}
	}
	FILE* f = fopen("groups.ssb", "w");
	for (int i = 0; i < groupCount; i++)
	{
		struct Group g = *(groupList + i);
		if (g.toRemove == false)
		{
			fprintf(f, "%s;%d;%s;%s;\n", g.Owner, g.ID_Group, g.Name, g.Description);
		}
		else
		{
			toRemoveGroupCount++;
			toRemoveGroup = realloc(toRemoveGroup, toRemoveGroupCount * sizeof(int));
			*(toRemoveGroup + toRemoveGroupCount - 1) = i + 1;
		}
	}
	fclose(f);
}

void writeRelation()
{
	for (int i = 0; i < relationCount; i++)
	{
		struct Relation* r = relationList + i;
		for (int j = 0; j < queueRemoveRelationCount; j++)
		{
			if (r->ID_Relation == *(queueRemoveRelation + j))
			{
				r->toRemove = true;
			}
		}
	}
	FILE* f = fopen("relations.ssb", "w");
	for (int i = 0; i < relationCount; i++)
	{
		struct Relation r = *(relationList + i);
		if (r.toRemove == false)
		{
			fprintf(f, "%d;%d;%d;\n", r.ID_Relation, r.ID_Contact, r.ID_Group);
		}
		else
		{
			toRemoveRelationCount++;
			toRemoveRelation = realloc(toRemoveRelation, toRemoveRelationCount * sizeof(int));
			*(toRemoveRelation + toRemoveRelationCount - 1) = i + 1;
		}
	}
	fclose(f);
}

void writeUsers()
{
	FILE* f = fopen("users.ssb", "w");
	for (int i = 0; i < userCount; i++)
	{
		if ((userList + i)->toRemove == false)
		{
			fprintf(f, "%s;%s\n", (userList + i)->login, (userList + i)->hash);
		}
	}
	fclose(f);
}

void writeData()
{
	writeUsers();
	writeContact();
	writePhone();
	writeAdress();
	writeEmail();
	writeGroup();
	writeRelation();
}