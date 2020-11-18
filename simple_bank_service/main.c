#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Global Variables
char g_name[20];
int g_age;
char g_sex[5];
float g_amount;
// function prototype
int welcome();
int create_account();
int deposite();
int withdraw();
int details();
int cont();
int show();
// main function
int main(){
welcome();
return 0;
}
// welcome
int welcome(){
int choice;
show();
printf("1) Create Account\n");
printf("2) Look at your Account\n");
printf("3) Deposite Money\n");
printf("4) Withdraw Money\n");
printf("5) Exit\n");
printf("\n\nEnter your choice:");
scanf("%d", &choice);
// switch case
switch(choice){
case 1:
system("clear");
show();
create_account();
break;
case 2:
system("clear");
show();
details();

break;
case 3:
system("clear");
show();
deposite();
break;
case 4:
system("clear");
show();
withdraw();
break;
case 5:
exit(1);
break;

default:
show();
printf("Please Enter valid Number !! \n\n");
// Asking to continue
char ans[3];
printf("Do you want to continue(yes/no)?: ");
scanf("%s",&ans);
if((strcmp(ans,"yes")) == 0 || (strcmp(ans,"Yes"))== 0 || (strcmp(ans,"YES")) == 0){
welcome();
}
if((strcmp(ans,"no")) == 0 || (strcmp(ans,"No"))== 0 || (strcmp(ans,"NO")) == 0){
show();
printf("\t\t\t Thanks for your visit");
printf("\n\t\t\t ----------------------\n\n\n");
exit(1);
}
else{
printf("Invalid Input!!\n\n");
exit(1);
}

break;
}
}

// show
show(){
// header
system("clear");
printf("\n\t\t\tMamba Bank Limited");
printf("\n\t\t\t------------------\n\n");}
// details
int details(){

FILE *fp;
char t_name[20];
int t_age;
char t_sex[5];
float t_amount;
char name_copy[10];
// asking user name
printf("Enter Your Name:");
scanf("%s",&g_name);
show();
strcpy(name_copy,g_name);
// checking whether account exist or not
fp = fopen(strcat(name_copy,".txt"),"r+");
// if account doesn't exit
if(fp == NULL){
show();
printf("Your Account Doesn't exist \n\n");
char ans[3];
// asking to create new account
printf("Do you want to create new account(yes/no)?: ");
scanf("%s",&ans);
if((strcmp(ans,"yes")) == 0 || (strcmp(ans,"Yes"))== 0 || (strcmp(ans,"YES")) == 0){
create_account();
}
if((strcmp(ans,"no")) == 0 || (strcmp(ans,"No"))== 0 || (strcmp(ans,"NO")) == 0){
show();
printf("\t\tThanks for your visit\n");
printf("\t\t-----------------------\n\n\n");
}
else{
printf("Invalid Input!!\n\n");
exit(1);

}


}
// if account exist
else{
//for name
fseek(fp,5,1);
fscanf(fp,"%s",&t_name);
//for age
fseek(fp,5,1);
fscanf(fp,"%d",&t_age);
//for sex
fseek(fp,5,1);
fscanf(fp,"%s",&t_sex);
//for amount
fseek(fp,8,1);
fscanf(fp,"%f",&t_amount);
// copying t_amount to a
float a = t_amount;
// to change to writing mode
rewind(fp);
fseek(fp,5,1);
fscanf(fp,"%s",&t_name);
//for age
fseek(fp,5,1);
fscanf(fp,"%d",&t_age);
//for sex
fseek(fp,5,1);
fscanf(fp,"%s",&t_sex);
//for amount
fseek(fp,8,1);
fscanf(fp,"%.2f",&t_amount);
// display details
show();
printf("\n\n\t\t\tAccount Details\n");
printf("\t\t       -----------------\n");
printf("\nName:  %s\nAge:  %d\nSex:  %s\nAmount:  %.1f\n\n\n\n",t_name, t_age, t_sex,t_amount);
// Asking to continue
char ans[3];
printf("Do you want to continue(yes/no)?: ");
scanf("%s",&ans);
if((strcmp(ans,"yes")) == 0 || (strcmp(ans,"Yes"))== 0 || (strcmp(ans,"YES")) == 0){
welcome();
}
if((strcmp(ans,"no")) == 0 || (strcmp(ans,"No"))== 0 || (strcmp(ans,"NO")) == 0){
show();
printf("\t\t\t Thanks for your visit");
printf("\n\t\t\t ----------------------\n\n\n");
exit(1);
}
else{
printf("Invalid Input!!\n\n");
exit(1);
}


fclose(fp);



}



}
// withdraw
int withdraw(){
FILE *fp;
char t_name[20];
int t_age;
char t_sex[5];
float t_amount;
char name_copy[10];
printf("Enter Your Name:");
scanf("%s",&g_name);
strcpy(name_copy,g_name);
fp = fopen(strcat(name_copy,".txt"),"r+");
// checking whether account exist or not
// if account doesn't exist
if(fp == NULL){
show();
printf("\t\tYour Account Doesn't exist\n");
printf("\t\t---------------------------\n\n");

char ans[3];
printf("Do you want to create new account(yes/no)?: ");
scanf("%s",&ans);
if((strcmp(ans,"yes")) == 0 || (strcmp(ans,"Yes"))== 0 || (strcmp(ans,"YES")) == 0){
create_account();
}
if((strcmp(ans,"no")) == 0 || (strcmp(ans,"No"))== 0 || (strcmp(ans,"NO")) == 0){
show();
printf("\t\t  Thanks for your visit\n\n\n");
}
else{
printf("Invalid Input!!\n\n");
exit(1);

}
}
// if account exist
else{
//for name
fseek(fp,5,1);
fscanf(fp,"%s",&t_name);
//for age
fseek(fp,5,1);
fscanf(fp,"%d",&t_age);
//for sex
fseek(fp,5,1);
fscanf(fp,"%s",&t_sex);
//for amount
fseek(fp,8,1);
fscanf(fp,"%f",&t_amount);
// copying t_amount to a
float a = t_amount;
// to change to writing mode
rewind(fp);
fseek(fp,5,1);
fscanf(fp,"%s",&t_name);
//for age
fseek(fp,5,1);
fscanf(fp,"%d",&t_age);
//for sex
fseek(fp,5,1);
fscanf(fp,"%s",&t_sex);
//for amount
fseek(fp,8,1);
float amount_to_withdraw;
show();
printf("Enter amount to withdraw:");
scanf("%f",&amount_to_withdraw);
a = a - amount_to_withdraw;
// checking whether balance is less than withdrawl amount or not
// if balance is more than withdrawl amount
if(a > 0){
fprintf(fp,"%.2f",a);
fclose(fp);
show();
printf("\n\n\t\t\tWithdrawn Sucessfully");
printf("\n\t\t\t---------------------\n\n\n");
// asking user to continue
char ans[3];
printf("\nDo you want to see your account information(yes/no)?: ");
scanf("%s",&ans);
if((strcmp(ans,"yes")) == 0 || (strcmp(ans,"Yes"))== 0 || (strcmp(ans,"YES")) == 0){
show();
details();
}
if((strcmp(ans,"no")) == 0 || (strcmp(ans,"No"))== 0 || (strcmp(ans,"NO")) == 0){
exit(1);
}
else{
printf("Invalid Input!!\n\n");
exit(1);

}

}
// if balance is not enough
else{
show();
printf("\n\n\t\tYou Don't have enought balance");
printf("\n\t\t-----------------------------\n\n\n");

char ans[3];
printf("\nDo you want to see your account information(yes/no)?: ");
scanf("%s",&ans);
if((strcmp(ans,"yes")) == 0 || (strcmp(ans,"Yes"))== 0 || (strcmp(ans,"YES")) == 0){
show();
details();
}
if((strcmp(ans,"no")) == 0 || (strcmp(ans,"No"))== 0 || (strcmp(ans,"NO")) == 0){
exit(1);
}
else{
printf("Invalid Input!!\n\n");
exit(1);

}


}

}
fclose(fp);

}
// for deposite
int deposite(){
FILE *fp;
char t_name[20];
int t_age;
char t_sex[5];
float t_amount;
char name_copy[10];
printf("Enter Your Name:");
scanf("%s",&g_name);
strcpy(name_copy,g_name);
fp = fopen(strcat(name_copy,".txt"),"r+");
if(fp == NULL){
show();
printf("\t\tYour Account Doesn't exist\n");
printf("\t\t---------------------------\n\n");

char ans[3];
printf("Do you want to create new account(yes/no)?: ");
scanf("%s",&ans);
if((strcmp(ans,"yes")) == 0 || (strcmp(ans,"Yes"))== 0 || (strcmp(ans,"YES")) == 0){
create_account();
}
if((strcmp(ans,"no")) == 0 || (strcmp(ans,"No"))== 0 || (strcmp(ans,"NO")) == 0){
show();
printf("\t\t  Thanks for your visit\n\n\n");
}
else{
printf("Invalid Input!!\n\n");
exit(1);

}


}
else{
//for name
fseek(fp,5,1);
fscanf(fp,"%s",&t_name);
//for age
fseek(fp,5,1);
fscanf(fp,"%d",&t_age);
//for sex
fseek(fp,5,1);
fscanf(fp,"%s",&t_sex);
//for amount
fseek(fp,8,1);
fscanf(fp,"%f",&t_amount);
// copying t_amount to a
float a = t_amount;
// to change to writing mode
rewind(fp);
fseek(fp,5,1);
fscanf(fp,"%s",&t_name);
//for age
fseek(fp,5,1);
fscanf(fp,"%d",&t_age);
//for sex
fseek(fp,5,1);
fscanf(fp,"%s",&t_sex);
//for amount
fseek(fp,8,1);
float amount_to_deposite;
show();
printf("Enter amount to deposite:");
scanf("%f",&amount_to_deposite);
a = a + amount_to_deposite;
fprintf(fp,"%f",a);
fclose(fp);
show();
printf("\n\n\t\t\tDeposited Sucessfully");
printf("\n\t\t\t---------------------\n\n");

/// asking whether user want to see their account information or not
char ans[3];
printf("Do you want to see your account information(yes/no)?: ");
scanf("%s",&ans);
if((strcmp(ans,"yes")) == 0 || (strcmp(ans,"Yes"))== 0 || (strcmp(ans,"YES")) == 0){
show();
details();
}
if((strcmp(ans,"no")) == 0 || (strcmp(ans,"No"))== 0 || (strcmp(ans,"NO")) == 0){
exit(1);
}
else{
printf("Invalid Input!!\n\n");

}

}
fclose(fp);

}
// create account
int create_account(){
float a = 0;
show();
printf("\nCreate New Account:");
printf("\n------------------\n\n");
char name_copy[20],name_copy2[20];
puts("Enter your name:");
gets(g_name);
gets(g_name);
strcpy(name_copy, g_name);
strcpy(name_copy2,g_name);
puts("Enter your age:");
scanf("%d",&g_age);
puts("Enter sex:");
scanf("%s",&g_sex);
FILE *fp2;
fp2 = fopen(strcat(name_copy,".txt"),"r");
if(fp2 != NULL){
fclose(fp2);
show();
printf("\t\t\t Account Already Exist\n");
printf("\t\t\t-----------------------\n\n");
char ans[3];
printf("Do you want to continue(yes/no)?: ");
scanf("%s",&ans);
if((strcmp(ans,"yes")) == 0 || (strcmp(ans,"Yes"))== 0 || (strcmp(ans,"YES")) == 0){
welcome();
}
if((strcmp(ans,"no")) == 0 || (strcmp(ans,"No"))== 0 || (strcmp(ans,"NO")) == 0){
show();
printf("\t\t\tThanks for your visit\n");
printf("\t\t\t---------------------\n\n\n");
exit(1);
}
else{
printf("Invalid Input!!\n\n");
exit(1);

}

}
else{
FILE *fp;
fp = fopen(strcat(name_copy2,".txt"),"w");
if(fp == NULL){
printf("File cannot be created !");
}
else{

fprintf(fp,"Name:%s\nAge:%d\nSex:%s\nAmount:%f",g_name,g_age,g_sex,a);
fclose(fp);
show();
printf("\n\t\t\t Account Created Sucessfully");
printf("\n\t\t\t-----------------------------\n\n");

char ans[3];
printf("Do you want to see your account information(yes/no)?: ");
scanf("%s",&ans);
if((strcmp(ans,"yes")) == 0 || (strcmp(ans,"Yes"))== 0 || (strcmp(ans,"YES")) == 0){
show();
details();
}
if((strcmp(ans,"no")) == 0 || (strcmp(ans,"No"))== 0 || (strcmp(ans,"NO")) == 0){
show();
printf("\t\t\tThanks for your visit\n");
printf("\t\t\t---------------------\n\n\n");
exit(1);
}
else{
printf("Invalid Input!!\n\n");
exit(1);

}
}
fclose(fp);


}
}
