#include <stdio.h>
#include <windows.h>
#include <string.h> // Per la funzione strlen()
#include <conio.h>  // Per la funzione di sleep()
#include <stdlib.h>
#include <math.h>

#define ENTER 13
#define BACKSPACE 8

void encrypt(char *text){

	int z = strlen(text);

	for(int i = 0;i < z; i++){
		text[i] += 11;	
		text[i] = text[i] | (char)sqrt(strlen(text) + 2*i);
		text[i] = text[i] ^ (char)sqrt(strlen(text) + 1/3);
	}
}

void getText(char *string, int mode)
{
	char ch = 0;
	int i = 0;

	while(ch!=ENTER){	//13 è il "enter" mentre 8 è il "cancella"
		ch=getch();
		if(ch!=ENTER && ch!=BACKSPACE){
			printf("%c", (mode == 1) ? 42 : ch);
			string[i]=ch;
			i++;
		}
	}
	string[i]='\0';
}


void checkPass(char *password){

	char passText[30] = "\nInserire password: ";
	char pass[100];

	for(unsigned int i = 0;i <= strlen(passText); i++){
		Sleep(40);
		printf("%c",passText[i]);
	}

	getText(pass, 1);	
	encrypt(pass);

	if(strcmp(pass,password) == 0){
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
		printf("\nPassword errata, riprova\n");
		Sleep(1500);
		system("color B");
		checkPass(password);
	}	
}

void login(){

	char logTitle[30] = "\t\t\tLOGIN";
	char askUser[50] = "\n\nInserire nome utente: ";
	char password[100], name[40], fullName[50];

	for(unsigned int i = 0;i <= strlen(logTitle); i++){
		Sleep(60);
		printf(" %c",logTitle[i]);
	}
	Sleep(400);
	logstart: for(unsigned int i = 0;i <= strlen(askUser); i++){
		Sleep(60);
		printf("%c",askUser[i]);
	}
	memset(name,0,strlen(name));
	memset(fullName,0,strlen(fullName));
	strcpy(fullName, "Accounts/");
	getText(name, 0);
	strcat(name, ".txt"); // aggiunge il ".txt"
	strcat(fullName, name);

	FILE *user = fopen(fullName, "r");
	if (user){
		fgets(password, 500, user);
		fclose(user);
		checkPass(password);
	}
	else{ 
		printf("\nL'utente non esiste");
		goto logstart;
	}
}


int main() 
{
	char mainTitle[30] = "\t\tTop Security Programm";
	char name[40], tempPass[40], yesNo[20], fullName[50] = "Accounts/";
	system("color B");
	for(unsigned int i = 0;i <= strlen(mainTitle); i++){
		Sleep(70);
		printf(" %c",mainTitle[i]);
	}

	Sleep(500);
	printf("\n\n\nHai gia un account(y/n)? ");
	gets(yesNo);
	
	while (!(strncmp(yesNo, "y", 1) == 0 || strncmp(yesNo, "n", 1) == 0)){
		printf("Il carrattere inserito non e' valido.\nHai gia un account(y/n)? ");
		gets(yesNo);
	}
	if (yesNo[0] == 'y'){
		//chiedi il nome utente e metti la password pari a quella nel file txt poi fai il controllo password
		Sleep(250);
		system("cls");
		login();
	}
	else{
		char tit[30] = "Creazione nuovo account";
		system("cls");
		printf("\t\t");
		for(unsigned int i = 0;i <= strlen(tit); i++){
			Sleep(50);
			printf(" %c",tit[i]);
		}
		Sleep(400);
		printf("\n\n\nInserire nome utente: ");
		getText(name, 0);
		strcat(name, ".txt"); // aggiunge il ".txt"
		strcat(fullName, name);
		Sleep(400);

		printf("\nInserire password: ");
		getText(tempPass, 1);
		encrypt(tempPass);

		FILE *passKeep = fopen(fullName, "w+");
		fprintf(passKeep, "%s", tempPass);
		fclose(passKeep);
		system("cls");
		login();
	}	
}