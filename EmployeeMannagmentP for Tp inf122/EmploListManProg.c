/******************************************************************

*Employee list Management programme
*KABAO TCHUNKOUA PLACIDE NOËL
*NOUBOSSÉ FOFOU ANGE
*MBAKOP TCHAKOUNTE DALILA RAYE
*YAYA KENGNE NATHALIE
*TASSI NDOUNKEU JACK DYLAN
*MEGAPTCHE DJILO DANNY LIONNEL
*NDZANA ESSOMBA RENÉ MARCELLIN
*ADONG HABIB SAMUEL
*NTAM SMITH
*NGAMENI NGANGOUM CHRISTIAN BRICE
* implements employee management using linked list operations.
*******************************************************************
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_MANAGER 50

/* Employee structure */
typedef struct Employee {
    char name[MAX_NAME];
    int id;
    char manager[MAX_MANAGER];   // direct manager's name
    int rank;                    // hierarchy level: 1 = highest (CEO)
    struct Employee* next;
} Employee;

/* Global list head */
Employee* head = NULL;
// The Main method is by loop calls functions via menu selection.
int main()
{
    
}