#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_PATH "apartments.dat"
typedef struct
{
    char firstName[32];
    char lastName[32];
    char leaseStart[16];
    char leaseEnd[16];
    int balance;
}Apartment;

static void createAprt(void);
static void readAprt(void);
static void updateAprt(void);
static void deleteAprt(void);

int main()
{
    FILE *fptr;
    fptr = fopen("apartments.dat","rb");
    if(fptr == NULL)
    {
        fptr = fopen("apartments.dat","wb+");
    }
    fclose(fptr);
    
    char buff[10];
    char letter[2];
    int stay=0;
    while(stay==0)
    {
        printf("\nEnter one of the following letters to perform a function or Q|q to exit");
        printf("\nC|c - Create a new apartment record\nR|r - Read an apartment record");
        printf("\nU|u - Update an apartment record\nD|d = Delete an apartment record\n");
        if(fgets(buff,10,stdin) != NULL)
        {
            sscanf(buff,"%c",letter);
            if(letter[0] == 'C' || letter[0] == 'c')
            {
                createAprt();
            }
            else if(letter[0] == 'R' || letter[0] == 'r')
            {
                readAprt();    
            }
            else if(letter[0]=='U' || letter[0]=='u')
            {
                updateAprt();
            }
            else if(letter[0]=='D'||letter[0]=='d')
            {
                deleteAprt();
            }
            else
            {
                break;
            }

        }
    }
    return 0;
}

static void createAprt()
{
    //printf("\nCreate");
    int aprtNum;
    Apartment newAprt;
    Apartment tempAprt;
    FILE *aprtOpen;
    aprtOpen = fopen(FILE_PATH,"rb+");
    char buff[100];
   
    //while ( (c = getchar()) != '\n' && c != EOF );
    printf("\nEnter the apartment number : ");
    fgets(buff,100,stdin);
    sscanf(buff,"%d",&aprtNum);
    printf("\n%d",aprtNum);
    long offset = aprtNum*sizeof(newAprt);
    fseek(aprtOpen,offset,SEEK_SET);
    int exist = fread(&tempAprt,sizeof(Apartment),1L,aprtOpen);
    if(exist==1 && strcmp(tempAprt.firstName,"deleted") != 0)
    {
        printf("\nERROR: Apartment already exists");
        fclose(aprtOpen);
        return;
    }
    else
    {
        printf("\nEnter the tentant's first name : ");
        fgets(buff,100,stdin);
        sscanf(buff,"%s",newAprt.firstName);

        printf("\nEnter the tentant's last name : ");
        fgets(buff,100,stdin);
        sscanf(buff,"%s",newAprt.lastName);

        printf("\nEnter the start date of the lease : ");
        fgets(buff,100,stdin);
        sscanf(buff,"%s",newAprt.leaseStart);

        printf("\nEnter the end date of the lease : ");
        fgets(buff,100,stdin);
        sscanf(buff,"%s",newAprt.leaseEnd);
        newAprt.balance = 900;
        
        printf("\n%s %s",newAprt.firstName,newAprt.lastName);
     
        fseek(aprtOpen,offset,SEEK_SET);
        fwrite(&newAprt,sizeof(Apartment),1L,aprtOpen);
        fclose(aprtOpen);
        return;
    }
   
    fclose(aprtOpen);
    return;
}

static void readAprt()
{
    //printf("\nRead");
    FILE *aprtOpen;
    Apartment aprtRead;
    char buff[10];
    int aprtNum;
    int exist;
    
    aprtOpen=fopen(FILE_PATH,"rb+");
    if(aprtOpen==NULL)
    {
        printf("\nERROR: could not open file");
        return;
    }

    printf("\nEnter the apartment number : ");
    fgets(buff,10,stdin);
    sscanf(buff,"%d",&aprtNum);
    long offset = aprtNum*sizeof(Apartment);
    fseek(aprtOpen,offset,SEEK_SET);
    exist = fread(&aprtRead,sizeof(Apartment),1L,aprtOpen);
    
    if(exist==0 || strcmp(aprtRead.firstName,"deleted")==0)
    {
        printf("\nERROR: apartment not found");
        fclose(aprtOpen);
        return;
    }

    printf("\nApartment Number : %d ",aprtNum);
    printf("\nTenant Name : %s %s",aprtRead.firstName,aprtRead.lastName);
    printf("\nLease Start : %s\nLease End : %s",aprtRead.leaseStart,aprtRead.leaseEnd);
    printf("\nBalance : %d",aprtRead.balance);
    fclose(aprtOpen);
    return;
}

static void updateAprt()
{
    FILE *aprtOpen;
    int aprtNum;
    Apartment tempAprt;
    int exist;
    char buff[100];
    long offset;
    char firstName[32];
    char lastName[32];
    char leaseStart[16];
    char leaseEnd[16];
    int balance;


    aprtOpen = fopen(FILE_PATH,"rb+");
    if(aprtOpen == NULL)
    {
        printf("\nERROR: could not open file");
        return;
    }
    
    printf("\nEnter the apartment number : ");
    fgets(buff,100,stdin);
    sscanf(buff,"%d",&aprtNum);
    offset = aprtNum*sizeof(Apartment);
    fseek(aprtOpen,offset,SEEK_SET);
    exist = fread(&tempAprt,sizeof(Apartment),1L,aprtOpen);

    if(exist ==0 || strcmp(tempAprt.firstName,"deleted")==0)
    {
        printf("\nERROR: apartment not found");
        fclose(aprtOpen);
        return;
    }
    
    printf("\nEnter the tentant's first name :");
    fgets(buff,100,stdin);
    sscanf(buff,"%s",firstName);
    if(strcmp(firstName,"")!=0)
        snprintf(tempAprt.firstName,sizeof(tempAprt.firstName),"%s",firstName);
    else
        snprintf(tempAprt.firstName,sizeof(tempAprt.firstName),"%s","");

    printf("\nEnter the tentant's last name :");
    fgets(buff,100,stdin);
    sscanf(buff,"%s",lastName);
    if(strcmp(lastName,"")!=0)
        snprintf(tempAprt.lastName,sizeof(tempAprt.lastName),"%s",lastName);
    else
        snprintf(tempAprt.lastName,sizeof(tempAprt.lastName),"%s","");

    printf("\nEnter the lease start date :");
    fgets(buff,100,stdin);
    sscanf(buff,"%s",leaseStart);
    if(strcmp(leaseStart,"")!=0)
        snprintf(tempAprt.leaseStart,sizeof(tempAprt.leaseStart),"%s",leaseStart);
    else
        snprintf(tempAprt.leaseStart,sizeof(tempAprt.leaseStart),"%s","");

    printf("\nEnter the lease end date :");
    fgets(buff,100,stdin);
    sscanf(buff,"%s",leaseEnd);
    if(strcmp(firstName,"")!=0)
        snprintf(tempAprt.leaseEnd,sizeof(tempAprt.leaseEnd),"%s",leaseEnd);
    else
        snprintf(tempAprt.leaseEnd,sizeof(tempAprt.leaseEnd),"%s","");

    printf("\nEnter the balance :");
    fgets(buff,100,stdin);
    sscanf(buff,"%d",&balance);
    if(strcmp(firstName,"")!=0)
        tempAprt.balance=balance;
    else
        tempAprt.balance=0;

    fseek(aprtOpen,offset,SEEK_SET);
    fwrite(&tempAprt,sizeof(Apartment),1L,aprtOpen);
    fclose(aprtOpen);
}

static void deleteAprt()
{
    FILE *aprtOpen;
    int aprtNum;
    int exist;
    Apartment tempAprt;
    char buff[10];
    long offset;
    
    aprtOpen = fopen(FILE_PATH,"rb+");
    if(aprtOpen==NULL)
    {
        printf("\nERROR: apartment could not be found");
        fclose(aprtOpen);
        return;
    }
    
    printf("\nEnter the apartment number : ");
    fgets(buff,10,stdin);
    sscanf(buff,"%d",&aprtNum);
    offset=aprtNum*sizeof(Apartment);
    fseek(aprtOpen,offset,SEEK_SET);
    exist = fread(&tempAprt,sizeof(Apartment),1L,aprtOpen);
    
    if(exist == 0 || strcmp(tempAprt.firstName,"deleted")==0)
    {
        printf("\nERROR: apartment not found");
        fclose(aprtOpen);
        return;
    }
    
    
    snprintf(tempAprt.firstName,sizeof(tempAprt.firstName),"%s","deleted");
    snprintf(tempAprt.lastName,sizeof(tempAprt.lastName),"%s","");
    snprintf(tempAprt.leaseStart,sizeof(tempAprt.leaseStart),"%s","");
    snprintf(tempAprt.leaseEnd,sizeof(tempAprt.leaseEnd),"%s","");
    tempAprt.balance=0;
    
    fseek(aprtOpen,offset,SEEK_SET);
    fwrite(&tempAprt,sizeof(Apartment),1L,aprtOpen);
    fclose(aprtOpen);
    return;
}
