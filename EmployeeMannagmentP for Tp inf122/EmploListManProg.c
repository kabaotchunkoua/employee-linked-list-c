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

Employee *create_employee(const char*name, int id, const char* manager, int rank){
    Employee* newEmpl = (Employee*)malloc(sizeof(Employee)){

        if (!newEmpl){
            printf("Memory allocation failed\n");
            exit(1)
        }
        strcpy(newEmpl->name, name);
        newEmpl->id = id;
        strcpy(newEmpl->management, management);
        newEmpl->rank = rank;
        newEmpl->next =NULL;
        return newEmpl;
    }

}

int id_exists(int id){
    Employee * temp = head;
    while(temp){
        if (temp->id == id ) return 1;
        temp = temp->next;

    }
    return 0;
}

Employee *find_by_name(const char* name){
    Employee *tmep= head;
    while(tmep){
        if(strcmp(tmep->name, name) == 0) return tmep;
        tmep = tmep->next;
    }
    return NULL;
}
Employee *find_by_id(int id){
    Employee *temp = head;
    while(temp){
        if(temp -> id == id) return temp;
        temp = temp->next;
    }
    return NULL;
}

// to the comput the rank based on manager name
int compute_rank(const char* manager){
    if(manager == NULL || strlen(manager) == 0) return 1;
    Employee* mngr = find_by_name(manager);
    if(mngr) return mngr->rank +1;
    printf("Warning: Manager '%s' not found. Setting rank = 1. \n", manager);
    return 1; 
}



// The Main method is by loop calls functions via menu selection.
int main()
{

}