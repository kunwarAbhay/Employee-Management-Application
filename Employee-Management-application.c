#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

// Creating a Employee information structure
// Stores the information about a particular Employee
struct emp{
int id;
char name[50];
int age;
float salary;
};

//creating a employee variable
struct emp e;

// Store size of the Employee structure
long int size = sizeof(e);

// Initially, co-ordinate will be (0,0)
COORD cord = {0,0};
// function to set the co-ordinate of cursor
void gotoxy(int x,int y){
   cord.X = x;
   cord.Y = y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cord);
}


/* FILE pointers to store address of file opened for operations */
FILE *fp, *ft;

/* Add the records of Employee in the Employee Information file */
void addrecord(){
   system("cls");// Clears all the output/text on the screen
   system("color 3F");// Set color for Text and Background
   fseek(fp,0,SEEK_END);// Move the cursor to end of the file

   /* Add the employee information in the file until 'n' */
   char another = 'y';
   while(another == 'y')
   {
      printf("Enter name :");
      fflush(stdin);
      gets(e.name);

      printf("Enter age : ");scanf("%d",&e.age);
      printf("Enter salary : ");scanf("%f",&e.salary);
      printf("Enter EMP-ID : ");scanf("%d",&e.id);

      fwrite(&e,size,1,fp);

      printf("Want to add another record y/n : ");
      fflush(stdin);
      scanf("%c",&another);
   }
}

/* Delete the record of the specified Employee from the file */
void deleterecord(){
   system("cls");// Clears the console screen
   system("color 3F");// Set text/background color of console

   char empname[50];// Stores the name of the Employee to be deleted
   /* Run the loop until another == 'n' i.e, when user don't want to delete specific Employee record */
   char another = 'y';
   int flag = 0;// flag == 1 will indicate record found
   while(another == 'y')
   {
       printf("Enter employee name to delete : ");
       fflush(stdin);
       gets(empname);

      /*
         We will create a temporary file
         It will store the all the Employee record EXCEPT the Employee record to be deleted
         Now this file have all the employee record EXCEPT the Employee record to be deleted 
         In the end we will rename this file to data.txt(All Employee record) --> specified Employee record deleted
      */
       ft = fopen("temp.txt","wb");// Open a temporary file
       rewind(fp);// Set the cursor of the file pointer to the beggining of the Employee record file

      /* Read employee record file
         write into temporary file
         but if the employee name to be deleted is found then,
         skip the whole information of that employee i.e, Don't write in temporary file
      */
       while(fread(&e,size,1,fp)==1)
       {
           if(strcmp(e.name,empname)!=0)
           {
               fwrite(&e,size,1,ft);
               flag = 1;
           }
       }

      if(flag == 0)
         printf("%s NOT FOUND in the record!",empname);
      else
         printf("%s record deleted successfully!",empname);

       fclose(fp);
       fclose(ft);
       remove("data.txt"); /* ====== This function removes the file given as argument ======== */
       rename("temp.txt","data.txt"); /* ====== This function renames the file given as argument ===== */
       fp = fopen("data.txt","rb+");// Set the pointer again to newly created file(data.txt-->Employee records)

       printf("Want to delete another record y/n : ");
       fflush(stdin);
       scanf("%c",&another);
   }
}

/* Display record of all the Employee */
void displayrecord(){
   system("cls"); // Clear the console screen
   system("color 3F"); // Set text/background color

   // Sets file pointer to start of the file
   // then read all the records
   rewind(fp);

   printf("\n===================================================================================================================\n");
   printf("NAME\t\t\t\t\t\tAGE\t\tSALARY\t\t\t\t\tID");
   printf("\n===================================================================================================================\n");

      while(fread(&e,size,1,fp)==1)
      {
         printf("\n%-48s%-16d%-26.2f\t\t%-10d",e.name,e.age,e.salary,e.id);
      }

   printf("\n\n\n");
   printf("                                      ");system("pause");// Hold the screen 
}

/* Modify records of the specified Employee */
void modifyrecord(){
   system("cls");// clear the console
   system("color 3F");// Set text/background color

   char empname[50];// Store the Employee name to be modified
   /* Modify record until another == 'n' */
   char another = 'y';
   while(another == 'y')
   {
       printf("Enter employee name to modify : ");
       fflush(stdin);
       gets(empname);

       rewind(fp);// Set the file pointer to beggining of the file(Employee record file)
       /* Read file until end  of file is reached or Employee name is found in the record file*/
       while(fread(&e,size,1,fp)==1)
       {
           if(strcmp(e.name,empname)==0)
           {
              // Employee name to modify found in the file
               printf("Enter new name : ");gets(e.name);// new name
               fflush(stdin);
               printf("Enter new age : ");scanf("%d",&e.age);// new age
               printf("Enter new salary : ");scanf("%f",&e.salary);// new salary
               printf("Enter new EMP-ID : ");scanf("%d",&e.id);// new id

               fseek(fp,-size,SEEK_CUR);// Now move the cursor back by size(size of emp structure)
               fwrite(&e,size,1,fp);// Write new record in place of previous record
               break;
           }
       }

       printf("Want to modify another record y/n : ");
       fflush(stdin);
       scanf("%c",&another);
   }

}

/* Main driver Code */
int main(){
  
   //opening the file
   fp = fopen("data.txt","rb+");// Not open in wb+ mode otherwise data will be erased
   if(fp == NULL)
   {
     // File doesn't exist
     // Hence create a new file and open it
     fp = fopen("data.txt","wb+");
     if(fp == NULL)
     {
      // Unable to open in wb+ mode
      printf("\nCan't open file...");
      exit(1);
     }
   }


   system("color 4F");// Set text/background color

   /* Home */
   printf("\n\n\n");
   printf("\n                                  ===============================                                                    ");
   printf("\n                                  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                                                    ");
   printf("\n                                  ===============================                                                    ");
   printf("\n                     [|:::>:::>:::>::> EMPLOYEE RECORD SYSTEM <::<:::<:::<:::|]                                      ");
   printf("\n                                  ===============================                                                    ");
   printf("\n                                  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                                                    ");
   printf("\n                                  ===============================                                                    ");
   printf("\n\n\n                                                                             Developer : @Kunwar_Abhay_Rai\n\n");

   printf("                                     "); system("pause");/* Hold the screen */ printf("                    ");

   /* Implementing a loader */
   printf("\n\n\n\n                                       ");
   for(int i=0;i<20;i++)
   {
      for(int j=0;j<100000000;j++);
      printf("%c",223);
   }

   int choice;// Store the menu choice
   /* Stops when exit option is choosed, programme also will also end at the same time */
   while(1)
   {
      system("cls");// Clear console
      system("color 4F");// Set text/background color
      /* Menu for file operation */
      gotoxy(30,10);
      printf("\n 1. ADD RECORD\n");
      gotoxy(30,12);
      printf("\n 2. DELETE RECORD\n");
      gotoxy(30,14);
      printf("\n 3. DISPLAY RECORD\n");
      gotoxy(30,16);
      printf("\n 4. MODIFY RECORD\n");
      gotoxy(30,18);
      printf("\n 5. EXIT\n");
      gotoxy(30,20);
      printf("\nENTER YOUR COICE... : ");
      fflush(stdin);
      scanf("%d",&choice);

      // Run file operation according to user choice
      switch(choice)
      {
         case 1:
            //Add Employee record
            addrecord();
            break;
         case 2:
            //Delete Employee record
            deleterecord();
            break;
         case 3:
            //Display Employee record
            displayrecord();
            break;
         case 4:
            //Modify Employee record
            modifyrecord();
            break;
         case 5:
            //Exit the program
            exit(1);
            break;
         default:
            printf("\nINVALID INPUT");
      }
   }

   return 0;

}




