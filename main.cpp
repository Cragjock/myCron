#include <iostream>
#include <vector>
#include "lcd_class.h"
#include "pitime.h"

using namespace std;


// NIST
char NL = '\n';
char EL = '\0';
int k=0;
char str_filenm[33];

int (*device_open)(void);
//char* (*alt_pitime)();
int (*alt_pitime)(char*);


void get_NIST(char*);


int main()
{
    cout << "Hello world!" << endl;
    lcddisplay lcdCron;

    lcdCron.lcd_clear();
    get_NIST(str_filenm);
    lcdCron.lcd_write(str_filenm);

    usleep(3000000);


    return 0;
}



void get_NIST(char* nist_data)
{
    vector<string> vec_nist(20);

//  adding NIST read time code ========
    char myTime[80]={0};
    char *mysplit[10];
    //char *myTest;
    char *myTest=(char*)malloc(sizeof(char) * 80);
    char *pch;
    //char *pch = malloc(sizeof(char) * 80);
    int sizecheck;

/*** function pointer ***/
    //sizecheck = buf_pitime(myTime);

    alt_pitime= &buf_pitime;      // This uses socket for NIST
    //alt_pitime= &no_net_pitime;     // This bypasses socket items but returns a time

    sizecheck = alt_pitime(myTime);
    //sizecheck = buf_pitime(myTime);


    //char* testtest= pitime();

/*****
57523 16-05-15 00:58:16 50 0 0 257.3 UTC(NIST) *
len = 51
*****/

    //pch = strtok (myTest," ");
    pch = strtok (myTime," ");
    //pch = strtok (testtest," ");  // this works
    while (pch != NULL)
    {
        //printf ("%s\n",pch);
        mysplit[k]= (char*)malloc(strlen(pch+1));
        strcpy(mysplit[k],pch);
        pch = strtok (NULL, " ");
        k++;
    }
    // format for LCD
    strcat(nist_data,mysplit[7]);      // UTC(NIST)
    strcat(nist_data,"\n");
    strcat(nist_data,mysplit[2]);      // Time
    strcat(nist_data,"\n");
    strcat(nist_data,mysplit[1]);      // date
    printf("strcat\n%s\n",nist_data);

    char* mytest1 = myTest+15;
    *mytest1=NL;
    char* mytest3=myTest+7;

    char* mytest4= myTest+24;
    *mytest4=EL;

    myTest[0]=0x20;     // clear the new line from NIST return

    //lcdCron.lcd_write(nist_data);   //NIST
// ==== NIST end
}

