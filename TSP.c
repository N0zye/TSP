#include <stdio.h>
#include <windows.h>
#include <string.h> // Per la funzione strlen()
#include <conio.h>  // Per la funzione di sleep()
#include <stdlib.h>
#include <math.h>

#define ENTER 13
#define BACKSPACE 8

const char* encrypt(char *text){
	for(unsigned int i = 0;i < strlen(text); i++){
		text[i] += 11;	
		text[i] = text[i] | (char)sqrt(strlen(text) + 2*i);
		text[i] = text[i] ^ (char)sqrt(strlen(text));
	}
	return text;
}

void getText(char *string) // Mode 1 è la modalità "hide"
{
	char ch = 0;
	int i = 0;
	while(ch!=ENTER){	//13 è il "enter" mentre 8 è il "cancella"
		ch=getch();
		if(ch!=ENTER && ch!=BACKSPACE){
			printf("*");
			string[i]=ch;
			i++;
		}
	}
	string[i]='\0';
}

void printText(char *string, int SleepDuration)
{
	for(unsigned int i = 0;i <= strlen(string); i++){
		Sleep(SleepDuration);
		(SleepDuration % 2 == 0) ? printf("%c",string[i]) : printf(" %c",string[i]);
	}
}

void login()
{
	system("cls"); // nuova pagina

	char realPass[100], userPass[100], userName[30], fullPath[50];

	printText("\t\t\t\tLOGIN", 61);
	Sleep(400);
	logstart:
	printText("\n\nInserire nome utente: ", 60);
	memset(userName,0,strlen(userName));
	memset(fullPath,0,strlen(fullPath));
	strcpy(fullPath, "Accounts/");
	gets(userName);
	strcat(userName, ".txt"); // aggiunge il ".txt"
	strcat(fullPath, userName); // aggiunge il "Accounts/"
	printText("Inserire password: ", 60);
	getText(userPass);

	FILE *user = fopen(fullPath, "r");
	fgets(realPass, 500, user);
	fclose(user);
	if (user && strcmp(encrypt(userPass),realPass) == 0){
		for (int i = 0; i < 5; i++){
			Sleep(350);
			(i % 2 == 0) ? system("color 0A") : system("color 04");
		}
		printf("\n\nPassword corretta");
		Sleep(1500);
		system("cls");
		printf("Devo mettere qualcosa qua");
	}
	else{
		for (int i = 0; i < 5; i++){
				Sleep(350);
				(i % 2 == 0) ? system("color 04") : system("color 0A");
			} 
		printf("\nUtente o Password errati\n");
		goto logstart;
	}
}

int main() 
{
	char userName[40], userPass[40], yesNo[20], fullPath[50] = "Accounts/";
	system("color B");
	printText("\t\t\t\tTop Security Programm", 61);

	Sleep(500);
	printText("\n\n\nHai gia un account(y/n)? ", 60);
	gets(yesNo);
	
	while (!(strncmp(yesNo, "y", 1) == 0 || strncmp(yesNo, "yes", 1) == 0 || strncmp(yesNo, "n", 1) == 0 || strncmp(yesNo, "no", 1) == 0)){
		printf("Il carrattere inserito non e' valido.\nHai gia un account(y/n)? ");
		gets(yesNo);
	}
	if (yesNo[0] == 'y'){
		Sleep(250);
		system("cls");
		login();
	}
	else{
		system("cls");
		printText("\t\t\tCreazione nuovo account", 71);
		Sleep(400);
		printf("\n\n\nInserire nome utente: ");
		gets(userName);
		strcat(userName, ".txt"); // aggiunge il ".txt"
		strcat(fullPath, userName);
		Sleep(400);
		printf("Inserire password: ");
		getText(userPass);

		FILE *passKeep = fopen(fullPath, "w+");
		fprintf(passKeep, "%s", encrypt(userPass));
		fclose(passKeep);
		login();
	}	
}
