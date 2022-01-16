#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include <openssl/crypto.h>
#include <openssl/sha.h>
#include<openssl/opensslconf.h>
#include<openssl/opensslv.h>
//-------------------------------------------------------------------------------------




struct block {
unsigned char prevHash[SHA256_DIGEST_LENGTH];
int PlotNo; //BlockData
char Ownername[15];
long AddharNo;
int Areacode; // plot sorrounded by
int North;
int South;
int East;
int West;

struct block *link;

}*head;
//------------------------------------------------------------------------------------
void homepage();
void addBlock(int, int, char[],int, int, int, int, int);
void verifyBlock(int);
void verifyChain();
void alterNthBlock(int ,int, int, char[],int, int, int, int, int);
int hashCompare(unsigned char*, unsigned char*);
void hashPrinter();
unsigned char* toString(struct block);
void printBlock();
void printAllBlocks();
void ownertransfer();
//------------------------------------------------------------------------------------

void addBlock(int plotno, int areacode, char ownername[],int addhar, int north, int south, int east, int west)
{
    if(head==NULL)
    {

        head=malloc(sizeof(struct block));
        SHA256("",sizeof(""),head->prevHash);
        head->PlotNo = plotno;
        head->Areacode = areacode;
        strcpy(head->Ownername,ownername);
        head->AddharNo = addhar;
        head->North = north;
        head->South = south;
        head->East = east;
        head->West = west;
        return;
    }
    struct block *currentBlock = head;
    while(currentBlock->link)
        currentBlock= currentBlock->link;
    struct block *newBlock=malloc(sizeof(struct block));
        currentBlock->link=newBlock;
        newBlock->PlotNo = plotno;
        newBlock->Areacode = areacode;
        strcpy(newBlock->Ownername,ownername);
        newBlock->AddharNo = addhar;
        newBlock->North = north;
        newBlock->South = south;
        newBlock->East = east;
        newBlock->West = west;
    SHA256(toString(*currentBlock),sizeof(*currentBlock),newBlock->prevHash);
    printf("Registry successfully done!");

}
//-----------------------------------------------------------------------------------
void gotohome()
{
 printf("\nPress Y to go to homepage:");
              char c1;
	scanf("%s",&c1);
	if(c1 =='Y' || c1=='y'){ homepage();}
	 else printf("Thank You");

}
//-----------------------------------------------------------------------------------
void hackBlock()
{
int  m,arc,pn,verid,np,sp,ep,wp;
char owname[15];
	printf("\nEnter Block No:");
	scanf("%d",&m);
	printf("\nEnter Area Code: ");
	scanf("%d",&arc);
	printf("\nEnter Plot No: ");
	scanf("%d",&pn);
	printf("\nEnter New Owner: ");
	getchar();
	fgets(owname,15,stdin);
	printf("\nEnter New Owner's Verfication ID issued by Gov Of India: ");
	scanf("%d",&verid);
	printf("\nEnter Plot surrounding details, Enter Plot Number: ");
	printf("\nEnter North Plot No: ");
	scanf("%d",&np);
	printf("\nEnter South Plot No: ");
	scanf("%d",&sp);
	printf("\nEnter East Plot No: ");
	scanf("%d",&ep);
	printf("\nEnter West Plot No: ");
	scanf("%d",&wp);
	alterNthBlock(m-1,arc,pn,owname,verid,np,sp,ep,wp);
	system("clear");
	printf("\033[1;31m \t\tBlock has been Hacked :) \033[0m\n");
        gotohome();
}
//-----------------------------------------------------------------------------------
void plotsearch(int n){
struct block *curr=head;

for(int i=0;i<n;i++)
{
curr=curr->link;
if(curr==NULL) {
printf("Block %d Does not exists\n",n);
return;
}
}
printBlock(curr);
gotohome();
}
//-----------------------------------------------------------------------------
void verifyBlock(int bn)
{
struct block *curr=head->link,*prev=head;

for(int i=0;i<bn;i++)
{
prev=prev->link;
curr=curr->link;
}
hashPrinter(SHA256(toString(*prev),sizeof(*prev),NULL),SHA256_DIGEST_LENGTH);
        printf(" - ");
        hashPrinter(curr->prevHash,SHA256_DIGEST_LENGTH);

        if(hashCompare(SHA256(toString(*prev),sizeof(*prev),NULL),curr->prevHash)){
           printBlock(curr);
            printf("Property Verified :)\n\n\t Press 1 to transfer ownership \n");
            int d;
            scanf("%d",&d);
            if(d==1){
            ownertransfer(bn);
            }
            else {
            printf("Wrong Input :( Heading to Home\n");
            gotohome();
            }
            }
        else
            printf("\033[1;31m \t\tVerification Failed:( \033[0m\n");
            gotohome();




}
//------------------------------------------------------------------------------------
void verifyChain()
{
	system("clear");
	printf("\t\t\t\t\tPLOT VERIFICATION CHAMBER\n\n");
printf("\t\t\t_________________________________________________________________\n\n");

    if(head==NULL)
    {
        printf("Blockchain is Empty! try again after adding some Blocks\n");
        return;
    }
    struct block *curr=head->link,*prev=head;
    int count=1;


    while(curr)
    {
       printf("[Block: %d]\n\n ",count++);
        printf("Initial Hash: ");
        hashPrinter(SHA256(toString(*prev),sizeof(*prev),NULL),SHA256_DIGEST_LENGTH);
        printf("\n Current Hash: ");
        hashPrinter(curr->prevHash,SHA256_DIGEST_LENGTH);
	printf("\n");
        if(hashCompare(SHA256(toString(*prev),sizeof(*prev),NULL),curr->prevHash))
           printf("\033[1;32m \t\tVerified :) \033[0m\n");
        else
          printf("\033[1;31m \t\tVerification Failed:( \033[0m\n");

        prev=curr;
        curr=curr->link;
    }
}
//-------------------------------------------------------------------------------------

void alterNthBlock(int n ,int plotno, int areacode, char ownername[],int addhar, int north, int south, int east, int west)
{

    struct block *curr=head;
    if(curr==NULL)
    {
        printf("Nth block does not exists\n");
        return;
    }
    int count=0;
    while(count!=n)
    {
        if(curr->link == NULL && count != n)
        {
            printf("Nth block does not exits \n");
            return;
        }
        else if(count == n)
            break;
        curr=curr->link;
        count++;
    }
        printf("Before: ");
        printBlock(curr);
        curr->PlotNo = plotno;
        curr->Areacode = areacode;
        strcpy(curr->Ownername,ownername);
        curr->AddharNo = addhar;
        curr->North = north;
        curr->South = south;
        curr->East = east;
        curr->West = west;
        printf("\nAfter: ");
        printBlock(curr); // print data of current block
}
//-------------------------------------------------------------------------------------
void updateChain()
{
struct block *curr=head,*prev;
    if(curr==NULL)
    {
        printf("BlockChain is empty!\n");
        return;

    }
    while(1)
    {   prev=curr;
        curr=curr->link;
        if(curr==NULL)
        return;
        if(!hashCompare(SHA256(toString(*prev),sizeof(*prev),NULL),curr->prevHash))
        {
            hashPrinter(
            SHA256(toString(*prev),sizeof(*prev),curr->prevHash),SHA256_DIGEST_LENGTH);
         printf("\n");
        }

    }
}
//--------------------------------------------------------------------------------------

void hashPrinter(unsigned char hash[], int length)
{
    for(int i=0;i<length;i++)
        printf("%02x",hash[i]);

        printf("\n");
}
//----------------------------------------------------------------------------------
int hashCompare(unsigned char *str1, unsigned char *str2)
{
    for(int i=0;i<SHA256_DIGEST_LENGTH;i++)
        if(str1[i]!=str2[i])
            return 0;
        return 1;
}
//-------------------------------------------------------------------------------------
void printBlock(struct block *curr)
{
printf("\n\t\tAreacode: %d\nPlotNo: %d\nOwnername: %s\nAddharNo: %ld\n\nNorth Side Plot: %d\nSouth Side Plot:: %d\nEast Side Plot:%d\nWest Side Plot:%d\n\n Hash: ",curr->Areacode,curr->PlotNo,curr->Ownername,curr->AddharNo,curr->North,curr->South,curr->East,curr->West);
     hashPrinter(curr->prevHash,sizeof(curr->prevHash));

}
//-------------------------------------------------------------------------------------
void printAllBlocks()
{
    struct block *curr=head;
    int count=0;
    while(curr)
    {
        printBlock(curr);
        curr=curr->link;
    }
}
//-------------------------------------------------------------------------------------
void newreg()
{
system("clear");
printf("\t\t\t\t\tADD NEW PLOT TO THE BLOCKCHAIN DATABASE\n\n");
printf("\t\t\t_________________________________________________________________\n\n");
        int arc,pn,np,sp,ep,wp;
        long verid;
	char owname[15];
	printf("\nEnter Area Code: ");
	scanf("%d",&arc);
	printf("\nEnter Plot No: ");
	scanf("%d",&pn);
	printf("\nEnter Owner: ");
	getchar();
	fgets(owname,15,stdin);
	printf("\nEnter Owner Verfication ID issued by Gov Of India: ");
	scanf("%ld",&verid);
	printf("\nEnter Plot surrounding details, Enter Plot Number: ");
	printf("\nEnter North Plot No: ");
	scanf("%d",&np);
	printf("\nEnter South Plot No: ");
	scanf("%d",&sp);
	printf("\nEnter East Plot No: ");
	scanf("%d",&ep);
	printf("\nEnter West Plot No: ");
	scanf("%d",&wp);
	addBlock(pn,arc,owname,verid,np,sp,ep,wp);
	printf("\n\t\tsuccessfully added to blockchain based database\n");
	char c;
	printf("If you want to go to homepage: Press Y-");
	scanf("%s",&c);
	if(c =='Y' || c=='y') homepage();
	else printf("**THANK YOU**");

}
//-------------------------------------------------------------------------------------
void ownertransfer(int n)
{
system("clear");
printf("\t\t\t***********************|| Transfer ownership ||***********************\n\n");
int  arc,pn,np,sp,ep,wp;
char owname[15];
    long verid;
struct block *curr=head;
	printf("\nEnter New Owner: ");
	getchar();
        fgets(owname,15,stdin);
	printf("\nEnter New Owner's Verfication ID issued by Gov Of India: ");
	scanf("%ld",&verid);
	for(int i=0;i<=n;i++) curr=curr->link;
	alterNthBlock(n+1,curr->Areacode,curr->PlotNo,owname,verid,curr->North,curr->South,curr->East,curr->West);
	updateChain();
	homepage();
}
//------------------------------------------------------------------------------------
void registry()
{
system("clear");
printf("\t\t\t\t_____________________________________________________________\n\n");
printf("\t\t\t\t\tBlockchain based Land Registry System\n");	printf("\t\t\t\t*************************************************************\n\n\n");
printf("\t\t\t1.Registred Plot\n\t\t\t2.New Plot\n\t\t\t3.Back\n\n\t\t Enter Choice: ");
int a;
scanf("%d",&a);
switch(a)
{
	case 1: printf("Enter Block No: ");
	int bc;
	scanf("%d",&bc);
	verifyBlock(bc-1);

	break;

	case 2:
	newreg();
	printf("The plot has been added to the database, Now you can transfer ownership\n Please select Chioce: 1 on the next screen\n");
	registry();
	break;
	case 3: homepage(); break;
	default: printf("Wrong input\n");
	break;
	homepage();
}
}
//------------------------------------------------------------------------------------
unsigned char* toString(struct block b)
{
    unsigned char *str=malloc(sizeof(unsigned char)*sizeof(b));
    memcpy(str,&b,sizeof(b));
    return str;

}
//--------------------------------------------------------------------------------------
void homepage()
{
	system("clear");

	printf("\t\t\t\t_____________________________________________________________\n\n");
	printf("\t\t\t\t\tWelcome to Blockchain based Land Registry system\n");
	printf("\t\t\t\t*************************************************************\n\n\n");
        int c,areacode,bn;
        int n;
        printf("\t_________________________________________________________________\n\n");
        printf("\t\t\t1. NEW REGISTRY \n\t\t\t2. PLOT VERIFICATION\n\t\t\t3. Explore Block \n\t\t\t4. LIST ALL REGISTRED PLOTS\n\t\t\t5. Add New Plot details to  Database\n\t\t\t6. Hack Demo\n\t\t\t+. Exit\n\t\t\t\t\t\t\t:by Prince Kumar :)");
        printf("\n\t_________________________________________________________________\n\n");

        printf("\n\t\tChoice: ");
        scanf("%d",&c);
        switch(c){
        case 1:registry();
        break;
        case 2: verifyChain();
        	gotohome();
        break;
        case 3:printf("\n\tEnter Block Number: ");
                   scanf("%d",&bn);
                   plotsearch(bn);
                   gotohome();
                   break;
        case 4:
                    system("clear");
                    printf("\t\t\t\t\tREGISTERD PLOTS\n\n");
                    printAllBlocks();
                    gotohome();
                    break;
        case 5:
                printf("How many blocks to enter: ");
                scanf("%d",&n);
            for(int i=0; i<n;i++)
            {
        int arc,pn,np,sp,ep,wp;
        long verid;
	char owname[15];
	printf("\nEnter Area Code: ");
	scanf("%d",&arc);
	printf("\nEnter Plot No: ");
	scanf("%d",&pn);
	printf("\nEnter Owner: ");
	getchar();
	fgets(owname,15,stdin);
	printf("\nEnter Owner Verfication ID issued by Gov Of India: ");
	scanf("%ld",&verid);
	printf("\nEnter Plot surrounding details, Enter Plot Number: ");
	printf("\nEnter North Plot No: ");
	scanf("%d",&np);
	printf("\nEnter South Plot No: ");
	scanf("%d",&sp);
	printf("\nEnter East Plot No: ");
	scanf("%d",&ep);
	printf("\nEnter West Plot No: ");
	scanf("%d",&wp);
	addBlock(pn,arc,owname,verid,np,sp,ep,wp);
	printf("Plot has been added\n");
              }
              printf("Press Y to go to homepage:");
              char c1;
	scanf("%s",&c1);
	if(c1 =='Y' || c1=='y') homepage();

	else {
	system("clear");
	printf("**THANK YOU**");
            }
                  break;
         case 6: hackBlock();
                 gotohome();
          break;

        default:printf("\t\t\t**THANK YOU**\n");
                    break;
}

}
//---------------------------------------------------------------------------------
//main function

int main()
{
system("clear");

   homepage();
   return 0;
}

//*********************************************************************************
//run command in linux
//gcc blockchain-based-land-registry-system.c -o blockchain-based-land-registry-system.c.o -lcrypto
// ./blockchain-based-land-registry-system.c.o

