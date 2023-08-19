#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int pwd;
void displayall();
typedef struct node  //node structure for implementing to store transaction history
{
    char name[20];
    int acno;
    int amt;
    char statement[50];
    char pan[10];
    struct  node *link;
}NODE;
NODE *first=NULL,*last=NULL,*second=NULL;
void neft(NODE **);
int savehistory(NODE **, char *);
NODE* search(int );
void insert();
void create();
void deleteac();
void wd(NODE **);
void dp(NODE **);
void display(int );
void showhistory(NODE **);
int mb=500;
void create() // this function will create accounts in bank
{
    NODE *temp,*nn;
    int i,n;
    printf("Enter the number of new users:                          \t ");
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        nn=(NODE*)malloc(sizeof(NODE));
        printf("\nComplete the details in the below form\n");
        printf("__\n");
        printf("\nEnter your name as in Adhar card :                \t");
        scanf("%s",nn->name);
        printf("\n Enter the amount you want to deposit(>500):      \t");
        scanf("%d",&nn->amt);
        printf("\nAssign account number to this new user:           \t");
        scanf("%d",&nn->acno);
        if(first==NULL)
        {
           nn->link=NULL;
           first=nn;
           last=nn;
        }
        else
        {
            temp=first;
            while(temp->link!=NULL)
                temp=temp->link;
            temp->link=nn;
            nn->link=NULL;
            last=nn;
        }
    }
}
NODE* search(int ac) // it wil helps to search an account 
{
    NODE *temp=first;
    while(temp!=NULL && temp->acno!=ac)
    temp=temp->link;
    if(temp==NULL)
    return NULL;
    else
    return temp;
}
void insert()    //it will helps to insert an account 
{
     printf("\nEnter password:\n");
    scanf("%d",&pwd);
    printf("\n");
    if(pwd==123)
    {
    NODE *temp,*nn;
    int ac;
     nn=(NODE*)malloc(sizeof(NODE));
     printf("\n");
     printf("\nEnter aacount holder name as in Adhar card :                \t");
     scanf("%s",nn->name);
     printf("\n Enter the amount he/she wants to deposit(>500):      \t");
     scanf("%d",&nn->amt);
     printf("\nAssign account number to this new user:           \t");
     scanf("%d",&nn->acno);
     if(nn->amt>50000)
        {
            printf("\nPlease enter your pan details \t:");
            scanf("%s",nn->pan);
        }
        if(first==NULL)
        {
           nn->link=NULL;
           first=nn;
           last=nn;
        }
        else
        {
            temp=first;
            while(temp->link!=NULL)
                temp=temp->link;
            temp->link=nn;
            nn->link=NULL;
            last=nn;
        }
        printf("\n Account added succesfully\n");
}
    else printf("\n!!!! WRONG PASSWORD   !!!!\n");
}
void deleteac()  //to delete an account from the bank this function will use
{
     printf("\nEnter password:\n");
    scanf("%d",&pwd);
    printf("\n");
    if(pwd==123)
    {
   int ac,count=0;
   NODE *temp,*prev;
   printf("\nEnter account number which should be deleted\t:");
   label:
   scanf("%d",&ac);
   count++;
   temp=first;
   prev=NULL;
   while(temp!=NULL && temp->acno!=ac)
   {
    prev=temp;
    temp=temp->link;
   }
   if(temp==NULL)
   {
   printf("\nInvalid account number \n");
   if(count<=3)
        {
        printf("\nPlease reenter the account number:\t");
        goto label;
        }
    else
    return;
   }
   else
   {
        if(first->acno==ac)
    {   
        first=first->link;
        printf("\n Account deleted succesfully\n");
        printf("And Rs.%d is returned to beneficiary",temp->amt);
        free(temp);
        return;
    }
   prev->link=temp->link;
   printf("\n Account deleted succesfully\n");
   printf("And Rs.%d is returned to beneficiary",temp->amt);
   free(temp);
   } 
}
    else printf("\n !!! WRONG PASSWORD !!!\n");
}
void display(int ac)   // this function is used to display an particular account
{
	NODE *temp;
	temp=search(ac);
    if(temp==NULL)
    {
        printf("\nInvalid ac\n");
        return;
    }
    printf("   Balance is:RS.%d\t in account %d",temp->amt,ac);
}
void displayall()   // this function will display all the account holder name and their balance 
{
     printf("\nEnter password:\n");
    scanf("%d",&pwd);
    printf("\n");
    if(pwd==123)
    {
	NODE *temp;
    int c=0;
		if(first==NULL)
	{
		printf("\nList is empty\n");
		return;
	}
	printf("\n");
    printf("_ SAVINGS BANK_\n ");
	printf("\n");
	printf("ACCOUNT HOLDER|\tACCOUNT NUMBER|\t TOTAL BALANCE        |   \n");
	printf("--------------|\t--------------|\t----------------------|\n");
    temp=first;
    while(temp!=NULL)
    {
	printf("    %s     \t      %d        \t     Rs. %d       \n",temp->name,temp->acno,temp->amt);
    temp=temp->link;
    c++;
    }
    printf("\n");
    printf("\tNumber of customers in our bank :       %d    \n",c);
}else printf("\n !!! WRONG PASSWORD !!!\n");
}
//This function will deduct the money withdrawn from the balance
void wd(NODE **second) 
{
    NODE *found;
    int amount,ac,count=0;
    char withdrawstmt[50];
    printf("\nEnter account number\t:");
    label1:
    scanf("%d",&ac);
    count++;
    found=search(ac);
    if(found==NULL)
    {
        printf("\nInvalid account number\n");
        if(count<=3)
        {
            printf("Please reenter the account number\n");
            goto label1;
        }
    }
    label2:
    printf("\nEnter the amount you want to withdraw\t:");
    scanf("%d",&amount);
    if((found->amt-amount)>mb)
    {
    found->amt=found->amt-amount;
    snprintf(withdrawstmt,sizeof(withdrawstmt),"RS.%d withdrawn from account number %d\n",amount,ac); //saving formatted string in withdrawStmt character array
    savehistory(second,withdrawstmt);
    display(ac);
    }
    else{
    printf("\nMinimum balance is %d and you have to maintain minimum balance \n ",mb);
    goto label2;
    }
}
void dp(NODE **second) //This function will add the money deposited to the balance
{
    NODE *found;
     char depositstmt[50];
    int amount,ac,count=0;
    printf("\nEnter account number:\t");
    label:
    scanf("%d",&ac);
    count++;
    found=search(ac);
    if(found==NULL)
    {
        printf("\nInvalid account number\n");
        if(count<=3)
        {
        printf("\nPlease reenter the account number:\t");
        goto label;
         }else{
    return;
         }
    }
    printf("\nEnter the amount you want to deposit:\t");
    scanf("%d",&amount);
    if(amount>0)
    {
    found->amt=found->amt+amount;
    if(found->amt>50000)
        {
            printf("\nPlease enter your pan details:\t");
            scanf("%s",found->pan);
        }    //  saving formatted string in depositStmt character array
    snprintf(depositstmt,sizeof(depositstmt),"RS.%d deposited to account number %d\n",amount,ac);
    savehistory(second,depositstmt);
    }
    else{printf("\n in valid amount entered\n");}
    display(ac);
}
int savehistory(NODE **second, char *str) //This function will save a transaction statement
 {
    NODE *temp;
    temp = (NODE *)malloc(sizeof(NODE));
    strcpy(temp->statement, str);
    if (NULL == *second) {
        *second = temp;
    }
     NODE *p;
        p = *second;
        while (NULL != p->link) {
            p = p->link;
 }
        p->link = temp;
         temp->link = NULL;
}
void showhistory(NODE **second)    //This function will display the transaction history
 {
    NODE *temp;
    temp = *second;
    if (temp ==NULL) {
        printf("\n   No transaction history...\n");
    } else {
        printf("\nTransaction History\n-------------------\n\n");
        while (NULL!=temp) {
            printf("%s\n", temp->statement);
            temp = temp->link;
        }
    }
}
void neft(NODE **second)   // this function is used to neft amount from one a/c to another a/c
{   int ac1,ac2,c=0,count=0,amount;
    NODE *found,*flag;
    char trans[1000];
    printf("\nEnter the account number from which you have to transfer:\t");
    label1:
    scanf("%d",&ac1);
    count++;
    found=search(ac1);
    if(found==NULL)
    {
        printf("\nInvalid account number\n");
        if(count<=3)
        {
        printf("\nPlease reenter the account number:\t");
        goto label1;
         }else{
    return;
         }
    }
     printf("\nEnter the account number to which you have to transfer:\t");
    label2:
    scanf("%d",&ac2);
    c++;
    flag=search(ac2);
    if(flag==NULL)
    {
        printf("\nInvalid account number\n");
        if(c<=3)
        {
        printf("\nPlease reenter the account number:\t");
        goto label2;
         }else{
    return;
         }
    }
    label3:
    printf("\nEnter the amount:\t");
    scanf("%d",&amount);
    if(amount>0){
    if((found->amt-amount)>mb)
    found->amt=found->amt-amount;
    else{
    printf("\nMinimum balance is %d and you have to maintain minimum balance \n ",mb);
    goto label3;
    }
    flag->amt=flag->amt+amount;
    if(found->amt>50000)
        {
            printf("\nPlease enter your pan details:\t");
            scanf("%s",flag->pan);
        }
    snprintf(trans,sizeof(trans),"RS.%d is succesfully nefted from account number %d to  %d\n",amount,ac1,ac2);
    savehistory(second,trans);
    display(ac1);
    printf("\n");
    display(ac2);
    }
}
void main()
{
    int c,ch,ac;
    create();
    printf("\n");
    do{
        printf("\n");
        printf("   OPTIONS ONLY FOR ADMIN \t         OPTIONS ONLY FOR A/C HOLDER\n");
        printf("===========================\t        ============================\n");
    printf("\nPress \t                               Press \n  1:TO insert an account\t             5:check balance\n  2:delete an account\t                     6:Withdraw\n  3:show transaction history\t             7:Deposit\n  4:display all account holder\t             8:Neft\n  5:Display\n");
    printf("\n _ To exit from menu bar press 9_ **\n");
    printf("\n");
    printf("enter the number :\t");
    scanf("%d",&c);
    switch(c)
    {
        case 1:insert();
                break;
        case 2:deleteac();
                break;
        case 3:showhistory(&second);
               break;
         case 4:displayall();
               break;
         case 5:printf("\nEnter the account number:\t");
            scanf("%d",&ac);
            display(ac);
            break;
         case 6:wd(&second);
               break;
         case 7:dp(&second);
                 break;
        case 8:neft(&second);
                break;
        case 9:printf("  THANK YOU ");
               exit(0);
    }}while(c!=0);
}
