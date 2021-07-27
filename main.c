#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

typedef struct{
    char FirstName[20];
    char LastName[20];
    int age;
    char *gender;
}UserInfo;


void EncryptHeader(char header[5],char FileName[12]){

    char ClassChoice, Row, line[256], AvaRows[3]; FILE *fp;int veh, RowChoice, i = 0, LineNumber, AvRows, j;

    fp = fopen(FileName,"r");
    if(fp == NULL)
        {printf("\nno trip information found, please try again later.");exit(1);}

    for(veh = 0 ; veh < 11 ; veh++)
        header[0] = fgetc(fp);
    //setting vehicle type


    system("cls");
    printf("which class do you choose?(f/b/e) :");
    scanf(" %c",&ClassChoice); //setting class
    while((ClassChoice != 'f')&&(ClassChoice != 'b')&&(ClassChoice != 'e'))
    {
        printf("\nincorrect choice, please try again\n");
        printf("which class do you choose?(f/b/e) :");
        scanf(" %c",&ClassChoice);

    }

    /**********first class**********/
// TODO (Nassim#4#): add error possibilities
    if(ClassChoice == 'f')
    {
        LineNumber = 11;
        while((fgets(line, sizeof(line), fp)!= NULL))
        {
            if(i == LineNumber)
               {printf("\n%s",line);
                break;}
            else i++;

        }
        header[1] = 'w';//setting seat
        j = 0;
        for(i = 7; i < 9; i++)
        {
            AvaRows[j] = line[i];
            j++;
        }
        AvRows = atoi(AvaRows);

        printf("\nchoose row number : ");
        scanf("%i" , &RowChoice);//setting row
        while((RowChoice > AvRows)||(RowChoice < 1 ))
        {
            printf("\nyour choice is incorrect, please try again\n");
            printf("\nchoose row number : ");
            scanf("%i" , &RowChoice);
        }
        if(RowChoice > 9)
        {
            itoa(RowChoice,&header[2],10);
            header[4] = 'F';//setting class
        }
        else
        {
        itoa(RowChoice,&Row,10);
        header[2] = Row;
        header[3] = 'F';//setting class
        }
    }
    /**********second class***********/
    else if(ClassChoice == 'b')
    {
        printf("\nwindow or aisle seat?(w/a) :");
        scanf(" %c",&header[1]);
        while((header[1] != 'w')&&(header[1] != 'a'))
        {
            printf("\nwrong choice, please try again\n");
            printf("\nwindow or aisle seat?(w/a) :");
            scanf(" %c",&header[1]);
        }

        LineNumber = 7;
        while((fgets(line, sizeof(line), fp)!= NULL))
        {
            if(i == LineNumber)
               {printf("\n%s",line);
                break;}
            else i++;

        }
        j = 0;
        for(i = 7; i < 9; i++)
        {
            AvaRows[j] = line[i];
            j++;
        }
        AvRows = atoi(AvaRows);

        printf("\nchoose row number : ");
        scanf("%i" , &RowChoice);
        while((RowChoice > AvRows)||(RowChoice < 1 ))
        {
            printf("\nyour choice is incorrect, please try again\n");
            printf("\nchoose row number : ");
            scanf("%i" , &RowChoice);
        }
        if(RowChoice > 9)
        {
            itoa(RowChoice,&header[2],10);
            header[4] = 'B';
        }
        else
        {
        itoa(RowChoice,&Row,10);
        header[2] = Row;
        header[3] = 'B';
        }
    }
    /********third class********/
    else if(ClassChoice == 'e')
    {
        printf("\nwindow, middle or aisle seat?(w/m/a)");
        scanf(" %c",&header[1]);
        while((header[1] != 'w')&&(header[1] != 'a')&&(header[1] != 'm'))
        {
            printf("\nwrong choice, please try again\n");
            printf("\nwindow, middle or aisle seat?(w/m/a)");
            scanf(" %c",&header[1]);
        }

        LineNumber = 2;
        while((fgets(line, sizeof(line), fp)!= NULL))
        {
            if(i == LineNumber)
               {printf("\n%s",line);
                break;}
            else i++;

        }
        j = 0;
        for(i = 7; i < 9; i++)
        {
            AvaRows[j] = line[i];
            j++;
        }
        AvRows = atoi(AvaRows);

        printf("\nchoose row number : ");
        scanf("%i" , &RowChoice);
        while((RowChoice > AvRows)||(RowChoice < 1 ))
        {
            printf("\nyour choice is incorrect, please try again\n");
            printf("\nchoose row number : ");
            scanf("%i" , &RowChoice);
        }
        if(RowChoice > 9)
        {
            itoa(RowChoice,&header[2],10);
            header[4] = 'E';
        }
        else
        {
        itoa(RowChoice,&Row,10);
        header[2] = Row;
        header[3] = 'E';
        }
    }
fclose(fp);
}
void EncryptMid(char MidPart[15]){
    int unique, size; FILE *fp;char FileLine[15],GenLine[15];

    try_again: //when the code already exists

    srand(time(0));
/*********used the math formula rand()*(b-a)+a for the random number generator***********/
        unique = (rand()*(99999999999999-10000000000000)+10000000000000);
        if(unique < 0)
            unique = unique * (-1);
        GenLine[0] = unique;
    itoa(unique, GenLine, 10);


    fp = fopen( "UNIQUE_INDERTIFIER.txt","r+");
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);//getting size to be used in the while loop
    fseek(fp, 0L, SEEK_SET);
    while(size != 0)
       {
        fgets(FileLine, sizeof(FileLine), fp);
        if(strcmp(FileLine,GenLine) == 0) /***compares if generated code is already used***/
        {
            printf("UI ALREADY IN USE, retrying...");
            goto try_again;//if used it sends tit back to try again

        }
        size--;
       }
       fputc('\n',fp);
       fputs(GenLine,fp);
       for(int i = 0; i < 15; i++)
       {
           MidPart[i] = GenLine[i]; //returning the generated code
       }
fclose(fp);
}

void UserData(UserInfo *CurrentUser, char code[25])
{
    int response;char confirmation;FILE *saving;

    unconfirmed: //reenter if a mistake is done
    system("cls");

    printf("please enter your first name :\n");
    scanf("%s",CurrentUser->FirstName);
    printf("please enter your last name :\n");
    scanf("%s",CurrentUser->LastName);
    //entering name

    printf("please enter your age :\n");
    scanf("%d",&(CurrentUser->age));
    //entering age

    wrong_input://mistake or wrong choice

    printf("please select your gender: \n1:male\n2:female\n");
    scanf("%i",&response);
    if(response == 1)
        CurrentUser->gender = "male";
    else if(response == 2)
        CurrentUser->gender = "female";
    else {printf("wrong choice, please try again\n");
        goto wrong_input;
    }
    //entering gender
    system("cls");//clearing screen for a clean display of data
    printf("please confirm all your entries :\n\n");
    printf("\nname: %s %s", CurrentUser->FirstName, CurrentUser->LastName);
    printf("\nage: %i",CurrentUser->age);
    printf("\ngender: %s",CurrentUser->gender);
    printf("\n\nconfirm all entries?:(y/n)");//confirmation for the entered data, else it will restart
    scanf(" %c", &confirmation);
    if(confirmation == 'y')
    {

        saving = fopen("reservations.txt","a");
        fprintf(saving,"%s ;%s ;%i ;%s ;%s\n",CurrentUser->FirstName, CurrentUser->LastName, CurrentUser->age, CurrentUser->gender, code);
        fclose(saving);saving = NULL;

        printf("\n\n                 CONFIRMED\n\n");
    }
    else goto unconfirmed;


}

void FirstPage(char FileName[10], char Line[70])
{
    FILE *StrdFile, *ChosenFile;char trip[70], code[10], DOC[5] = ".txt";int choice, i = 1,j;

    StrdFile = fopen("trips.txt","r");

    printf("WELCOME: OUR AVAILABLE TRIPS:\n");//displaying trips
    while(fgets(trip,sizeof(trip),StrdFile) != NULL)
        {
        printf("%i.",i);
        printf("%s\n",trip);
        i++;
        }
    printf("\nPLEASE ENTER THE NUMBER OF THE TRIP YOU CHOOSE : ");//choosing a trip
    scanf("%d",&choice);

    system("cls");

    char h, LocalLine[70]; int count = 0;

    fseek(StrdFile, 0L, SEEK_SET);//returns to the start of the file from printing the contents
    while(count != choice)
        {
            fgets(Line,70*sizeof(char),StrdFile);//going to the line of the chosen trip
            count++;

        }
    i = 0; j = 1;
    while((i < 5)||(j < 6))
    {
        code[i] = Line[j];//taking the code from the chosen trip
        i++;j++;
    }
    i = 5;j = 0;
    while((i < 8)||(j < 5))
    {
        code[i] = DOC[j];//adding the prefix ".txt" to th code to be able to open the file
        i++;j++;
    }
    ChosenFile = fopen(code,"r");
    if(ChosenFile == NULL)
        printf("ERROR: trip information not found.");
    /***********displaying prices***********/
    printf("The prices of each class for this trip are :\n");
    i = 1;
    while(fgets(LocalLine, sizeof(LocalLine), ChosenFile) != NULL)
    {
        if(i == 2)
            printf("\n%s",LocalLine);
        if(i ==7)
            printf("\n%s",LocalLine);
        if(i == 11)
            printf("\n%s",LocalLine);
        i++;
    }
    printf("\n\nto continue press any key\n");
    scanf(" %c",&h);

    strcpy(FileName, code);

    fclose(StrdFile);StrdFile = NULL;
    fclose(ChosenFile);ChosenFile = NULL;
}

void Ticket(char header[5], char code[25], char Line[70], UserInfo *CurrentUser)
{
    char Date[11], Time[6], Flight[50], Class[30], c, Seat[5];FILE *fp;int i, j = 0;

    /*******everything needed from variable Line: Date, Time, Flight*******/
    {


    while(Line[i] != '.')
        i++;
    i++;
    while(j < 10)
    {
        Date[j] = Line[i];
        j++;i++;
    }

    while(Line[i] != ';')
        i++;
    j = 0;i++;
    while(j < 5)
    {
       Time[j] = Line[i];
       j++;i++;
    }

    i = 9;j = 0;
    while(Line[i] != ' ')
    {
        Flight[j] = Line[i];
        i++;j++;
    }

    }

    /************everything needed from variable header: class, seat**********/
    {
        i = 0;j = 0;
        for(i = 1;i < 5; i++)
        {
            Seat[j] = header[i];
            j++;
        }

        c = header[4];
        if((c != 'E')&&(c != 'F')&&(c != 'B'))
            c = header[5];
        if(c == 'F')
            strcpy(Class, "FIRST");
        else if(c == 'B')
            strcpy(Class, "BUSINESS");
        else if(c == 'E')
            strcpy(Class, "ECONOMY");

    }


    fp = fopen("ticket.txt","w");

    fprintf(fp,"                                     TICKET                              \n");
    fprintf(fp,"                                                                    \n");
    fprintf(fp,"                                                                    \n");
    fprintf(fp,"   NAME: %s %s           DATE: %s       TIME: %s      \n", CurrentUser->FirstName, CurrentUser->LastName, Date, Time);
    fprintf(fp,"                                                                    \n");
    fprintf(fp,"   CLASS: %s        FLIGHT: %s       SEAT: %s                    \n", Class, Flight, Seat);
    fprintf(fp,"                                                                    \n");
    fprintf(fp,"                                 %s          \n",code);

    fclose(fp);fp = NULL;

}

int main()
{
    char header[5], code[25], FileName[10], MidPart[15], Line[70];UserInfo *CurrentUser;int i;

    FirstPage(FileName, Line);

    /**********to avoid having too many variables in the function array pointers were used in both function***********/
    EncryptHeader(header,FileName);//creates the first part of the code

    EncryptMid(MidPart);//creates the second part of the code


    while(i < 6){
        code[i] = header[i];//to put the first part of the code
        i++;
                }


    strcat(code , MidPart);//to put the second part of the code
    strncat(code , FileName, 5);//to put the third part of the code

    UserData(CurrentUser, code);

    Ticket(header,code,Line,CurrentUser);
    system("cls");
    printf("\n\n        YOUR TICKET HAS BEEN RELEASED    \n\n\n\n");

    return 0;
}
