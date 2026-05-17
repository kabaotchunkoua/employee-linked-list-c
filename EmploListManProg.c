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
#include<stdio.h> //printf, scanf, fgets, getchar
#include<stdlib.h> // malloc,free, exit.
#include<string.h>// strcpy, strcmp, strlen , strcspn

#define MAX_NAME 50
#define MAX_MANAGER 50

typedef struct Employee {
char name [MAX_NAME];
int id;
char manager[MAX_MANAGER];
int rank;
struct Employee* next;

}Employee;


Employee* head = NULL;

Employee* create_employee(const char* name, int id, const char* manager, int rank);
int id_exists(int id);
void insert_employee(const char* name, int id, const char* manager);
void display_employee();
void delete_employee(int id);
void delete_employee_list();

Employee* find_by_id(int id);
Employee* find_by_name(const char* name);
int comput_rank_by_name(const char* manager_name);
void recompute_all_ranks();
void update_employee(int id, char* new_name, char* new_manager);
void search_employee(int id);

int count_employees();
int is_employee_list_empty();
void reverse_list();
void sort_employees_by_id();
void sort_employees_by_name();
void sort_employees_by_rank();

void merge_lists(Employee** other_head);
int compare_lists(Employee* list1, Employee* list2);
int verify_list() ;

void save_to_file(const char* filename);
void load_from_file(const char* filename);

void print_menu();

Employee* get_employee_at_index(int index);
void search_by_name(const char* name);
void search_by_index(int index);
void delete_employee_list_second(Employee** list);




int main () {
    int choice, id, index;
    char name [MAX_NAME], manager[MAX_MANAGER], filename[100];
    Employee* secondlist =NULL;

    //Predefined second list for merge/compare
    secondlist = create_employee("Xlice", 201, "CEO", 2);
    secondlist->next =create_employee("Bod", 202, "Xlice", 3);
   
do {
    print_menu();
    if (scanf("%d", &choice)!= 1) {
        while (getchar()!= '\n')
        printf("Invalid input. Enter a number.\n");
    continue;
    }
    getchar();

    switch(choice) {
        case 1 :
        printf("Enter name (one name only): ");
        fgets(name, MAX_NAME, stdin);
        name[strcspn(name, "\n")] = 0;
        printf("Enter ID: ");
        if(scanf("%d", &id)!= 1) { while (getchar()!='\n') break;}
        getchar();
        printf("Enter manager name: ");
        fgets(manager, MAX_MANAGER, stdin);
        manager[strcspn(manager, "\n")] = 0;
        insert_employee(name, id, manager);
        break;
        case 2:
            printf("Enter ID to delete: ");
            scanf("%d", &id);
            delete_employee(id);
            break;
        case 3:
            display_employee();
            break;
        case 4:
            printf("Enter ID: ");
            scanf("%d", &id);
            search_employee(id);
            break;
        case 5:
            printf("Enter name: ");
            fgets(name, MAX_NAME, stdin);
            name[strcspn(name, "\n")] = 0;
            search_by_name(name);
            break;

        case 6:
            printf("Enter index(0-based): ");
            scanf("%d", &index);
            search_by_index(index);
             break;
        case 7:
            printf("Enter ID to update: ");
            scanf("%d", &id);
            getchar();
            printf("New name: ");
            fgets(name, MAX_NAME, stdin);
            name[strcspn(name, "\n")] = 0;
            printf("Enter manager: ");
            fgets(manager, MAX_MANAGER, stdin);
            manager[strcspn(manager, "\n")] =0; 
            update_employee(id, name, manager);
            break;
        case 8: sort_employees_by_name(); break;
        case 9: sort_employees_by_id(); break;
        case 10: sort_employees_by_rank(); break;
        case 11: reverse_list(); break;
        
        case 12:
         printf("Mergeing predefined second list into current...\n");
         merge_lists(&secondlist);
         break;

        case 13:
            {
                int cmp = compare_lists(head, secondlist);
                printf("Comparision result: %s\n", cmp ? "List are identical" : "Lists differ");
                break;
            }
        case 14:
            printf("Total employee %d\n", count_employees());
            break;
        case 15:
            printf(is_employee_list_empty() ? "List is empty.\n" : "List is not empty.\n");
            break;

        case 16:
            delete_employee_list();
            printf("All employees deleted.\n");
            break;
        case 17:
            printf("Enter employee ID: ");
            scanf("%d", &id);
            {
                Employee * e = find_by_id(id);
                if(e) printf("Manager of ID %d: %s\n", id, e->manager);
                else printf("Employee not found.\n");
            }
            break;
        case 18:
             printf("Enter employee ID: ");
            scanf("%d", &id);
            {
                Employee * e = find_by_id(id);
                if(e) printf("Name of ID %d: %s\n", id, e->name);
                else printf("Employee not found.\n");
            }
            break;
        case 19:
            printf("Enter index: ");
            scanf("%d", &index);
            {
                Employee* e = get_employee_at_index(index);
                if (e) printf("ID at index %d: %d\n", index, e->id);
                else printf ("Invalid index.\n");

            }
            break;
        case 20:
         verify_list();
         break;

        case 21:
            printf("Enter filename to save: ");
            fgets(filename, 100, stdin);
            filename[strcspn(filename, "\n")] = 0;
            save_to_file(filename);
            break;
        case 22:
            printf("Enter filename to load: ");
            fgets(filename, 100, stdin);
            filename[strcspn (filename, "\n")] = 0;
            load_from_file(filename);
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice . \n");



    }
    
    
}while(choice!= 0);

delete_employee_list();
delete_employee_list_second(&secondlist);
    
    
    return 0;
}
/* ============================ MENU ==============================*/

void print_menu(){
    printf("\n===================================================");
    printf("\n=========== EMPLOYEE MANAGEMENT MENU ============");
    printf("\n===================================================\n");
    printf("1. Insert employee\n");
    printf("2. Delete employee by ID\n");
    printf("3. Display all employee\n");
    printf("4. search by ID\n");
    printf("5. search by name\n");
    printf("6. search by index\n");
    printf("7. Update employee\n");
    printf("8. Sort by name\n");
    printf("9. Sort by ID\n");
    printf("10. Sort by rank\n");
    printf("11. Reverse list\n");
    printf("12. Merge another list\n");
    printf("13. Compare hierarchy with another list\n");
    printf("14. Count employee\n");
    printf("15. Check if empty\n");
    printf("16. Delete all employee\n");
    printf("17. Get manager by ID\n");
    printf("18. Get name by ID \n");
    printf("19. Get ID index\n");
    printf("20. verify list\n");
    printf("21. Save to CSV\n");
    printf("22. load from CSV\n");
    printf("0. Exit\n");
    printf("\n===================================================| ");
    printf("Choice: ");

}

// Get employee at index
Employee* get_employee_at_index(int index){
    Employee * temp = head;
    int i = 0;
    while(temp && i< index){
        temp = temp->next;
        i++;
    }
    return temp;
}
// Search by name
void search_by_name(const char* name){
    Employee* e = find_by_name(name);
    if(e){
        printf("Found: Name=%s, ID=%d, Manager=%s, Rank=%d\n", e->name, e->id, e->manager, e->rank);

    } else {
        printf("Emlpoyee '%s' not found.\n", name);
    }

}
//search by index
void search_by_index(int index){
    Employee* e = get_employee_at_index(index);
    if(e) {

        printf( "Index %d: Name=%s, ID=%d, Manager=%s, Rank=%d\n", index, e->name, e->id, e->manager, e->rank);

    }else {
        printf("Invalid index.\n");
    }

}
//Free secondlist separately
void delete_employee_list_second(Employee** list) {
    Employee* temp = *list;
    while (temp) {
        Employee * next = temp->next;
        free (temp);
        temp = next;
    }
    *list = NULL;
}

/*Function to create, insert, display, delete employee*/ 

Employee* create_employee(const char* name, int id, const char* manager, int rank){
    Employee* newEmpl = malloc(sizeof(Employee));
    if(!newEmpl) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strncpy(newEmpl->name, name, MAX_NAME-1);
    newEmpl->name[MAX_NAME-1] = '\0';
    newEmpl->id = id;
    strncpy(newEmpl->manager, manager, MAX_MANAGER-1);
    newEmpl->manager[MAX_MANAGER-1] = '\0';
    newEmpl->rank =rank;
    return newEmpl;
}
int id_exists(int id){
    Employee* temp = head;
    while(temp){
        if(temp->id == id) return 1;
        temp = temp->next;
    }
return 0;
}
void insert_employee(const char* name, int id, const char* manager){
    if(id_exists(id)){
        printf("Error: Employee with ID %d already exists.\n", id);
        return;
    }
    Employee* newemp = create_employee(name, id, manager, 1);

    newemp->next = head;
    head = newemp;
    // recompute_all_ranks();
    printf("Inserted %s with ID %d\n", name , id);
}
void display_employee(){
    if (head == NULL){
        printf("No employee to display.\n");
        return;
    }

    printf("\n%-20s %-10s %-20s %-5s\n", "Name", "ID", "Manager", "Rank");
    printf("----------------------------------------------------------\n");
    Employee* temp = head;
    while (temp) {
        printf("%-20s %-10d %-20s %-5d\n",temp->name, temp->id, temp->manager, temp->rank);
        temp = temp->next;
    }

}
void delete_employee(int id){
    Employee* temp = head;
    Employee* prev = NULL;
    
    while(temp && temp->id != id){
        prev = temp;
        temp = temp -> next;
    }

    if ( temp == NULL){
        printf("Employee not found.\n");
        return;
    }

    if (prev == NULL ) head = temp -> next;
    else prev-> next = temp -> next;

    free(temp);
    printf("Employee deleted.\n");
}
void delete_employee_list(){

    Employee* temp = head;
    while(temp){
       Employee* next = temp->next;
       free(temp);
       temp = next;
    }
    head = NULL;
}
/*Search and update*/

Employee* find_by_id(int id){
    Employee* temp = head;
    while(temp){
        if (temp->id == id) return temp;
        temp = temp ->next;
    }
    return NULL;
}
Employee* find_by_name(const char* name){
    Employee* temp = head;
    while(temp){
        if(strcmp(temp->name, name ) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}
int comput_rank_by_name(const char* manager_name){
    if(strlen(manager_name)==0 || strcmp(manager_name, "CEO") == 0)
     return 1;

    Employee* mgr = find_by_name(manager_name);
    if (mgr) return mgr->rank + 1;

    printf("Warning: Manager '%s' not found. Setting rank = 1.\n", manager_name);
    return 1;
}
void recompute_all_ranks(){
    Employee* temp = head;
    while(temp){
        temp->rank = comput_rank_by_name(temp->manager);
        temp = temp->next;
    }
}
void update_employee(int id, char* new_name, char* new_manager){
    Employee* emp = find_by_id(id);
    if(!emp){
        printf("Employee with ID %d not found.\n", id);
        return;
    }
    strncpy(emp->name, new_name, MAX_NAME-1);
    strncpy(emp->manager, new_manager, MAX_MANAGER-1);
    recompute_all_ranks();
    printf("Employee ID %d update.\n", id);

}
void search_employee(int id){
    Employee* emp = find_by_id(id);
    if(emp){
        printf("Found: Name=%s, ID=%d, Manager=%s, Rank=%d\n", emp->name, emp->id, emp->manager, emp->rank);

    }else{
        printf("Employee with ID %d not found.\n", id);
    }
}
// Sorting, revers, count, empty check

int count_employees() {
    int cnt = 0;
    Employee* temp = head;
    while (temp) {cnt++; temp = temp ->next;}
    return cnt;
}

int is_employee_list_empty() {return head == NULL;}

void reverse_list(){
    Employee* prev = NULL;
    Employee* curr = head;
    Employee* next = NULL;
    while(curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
    printf("list reversed.\n");
}
/*Bubble sort by swapping data.*/
void sort_employees_by_id(){
    if(!head || !head->next) return;

    int swapped;
    Employee* ptr1;
    Employee* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while(ptr1->next != lptr){
            if(ptr1->id > ptr1->next->id){

                int tmp_id = ptr1->id;
                ptr1->id = ptr1->next->id;
                ptr1->next->id = tmp_id;

               char tmp_name[MAX_NAME];
                strcpy(tmp_name, ptr1->name);
                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->next->name, tmp_name);

                char tmp_mgr[MAX_MANAGER];
                strcpy(tmp_mgr, ptr1->manager);
                strcpy(ptr1->manager, ptr1->next->manager);
                strcpy(ptr1->next->manager, tmp_mgr);

                int tmp_rank = ptr1->rank;
                ptr1->rank = ptr1->next->rank;
                ptr1->next->rank = tmp_rank;


                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    printf("List sorted by ID.\n");
}
void sort_employees_by_name(){
    if(!head || !head->next) return;
    int swapped;
    Employee* ptr1;
    Employee* lptr = NULL;

    do{ 
        swapped = 0;
        ptr1 = head;
        while(ptr1->next != lptr){
            if(strcmp(ptr1->name , ptr1->next->name) > 0){

                 int tmp_id = ptr1->id;
                ptr1->id = ptr1->next->id;
                ptr1->next->id = tmp_id;
                
                char tmp_name[MAX_NAME];
                strcpy(tmp_name, ptr1->name);
                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->next->name, tmp_name);

                char tmp_mgr[MAX_MANAGER];
                strcpy(tmp_mgr, ptr1->manager);
                strcpy(ptr1->manager, ptr1->next->manager);
                strcpy(ptr1->next->manager, tmp_mgr);

                int tmp_rank = ptr1->rank;
                ptr1->rank = ptr1->next->rank;
                ptr1->next->rank = tmp_rank;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr =ptr1;

    }while(swapped);
    printf("List sorted by NAME.\n");
}

void sort_employees_by_rank(){
    if(!head || !head->next) return;
    
    int swapped;

    Employee* ptr1;
    Employee* lptr = NULL;

    do{
        swapped = 0;
        ptr1 = head;
        while(ptr1->next != lptr){
            if(ptr1->rank> ptr1->next->rank){

               int tmp_id = ptr1->id;
                ptr1->id = ptr1->next->id;
                ptr1->next->id = tmp_id;
  
                char tmp_name[MAX_NAME];
                strcpy(tmp_name, ptr1->name);
                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->next->name, tmp_name);

                char tmp_mgr[MAX_MANAGER];
                strcpy(tmp_mgr, ptr1->manager);
                strcpy(ptr1->manager, ptr1->next->manager);
                strcpy(ptr1->next->manager, tmp_mgr);

                int tmp_rank = ptr1->rank;
                ptr1->rank = ptr1->next->rank;
                ptr1->next->rank = tmp_rank;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;

    }while(swapped);
    printf("List sorted by RANK (ascending).\n");
}
/* merge, compare and verify*/
void merge_lists(Employee** other_head) {
    if(*other_head == NULL){
        printf("Nothing to merge.\n");
        return;
    }
    if(head == NULL) {
        head = *other_head;
        *other_head = NULL;
        recompute_all_ranks();
        printf("Lists merged.\n");
        return;
    }
    Employee* tail = head;
    while (tail->next) {
        tail = tail->next;
    }

    tail->next = *other_head;
    *other_head = NULL;

    recompute_all_ranks();
    printf("Lists merged.\n");

}

int compare_lists(Employee* list1, Employee* list2){
  while (list1 && list2){
    if (list1 -> id != list2->id || strcmp(list1->name, list2->name) != 0 ||  strcmp(list1->manager, list2->manager) != 0 || list1->rank != list2->rank)  return 0;
   
    list1 = list1->next;
    list2 = list2->next;
  }
  return (list1 == NULL && list2 == NULL);

}

int verify_list() {
    int errors = 0;
    Employee* i = head;

    while(i){
        Employee* j = i->next;
        while(j){
            if(i->id == j->id) {
                printf("Error: Duplicate ID %d found [%s and %s]\n.", i->id, i->name, j->name);
                errors++;
            }
            j = j -> next;
        }
        if(strlen(i->manager) > 0 && find_by_name(i->manager) == NULL) {
            printf("Warning: Manager '%s' for %s not found\n", i->manager, i->name);
            errors++;
        }
        i = i->next;
    }
    if(errors == 0){
        printf("List verification passed. No errors. No erros found.\n");

    } else {
        printf("Verification done. %d issue(s) found.\n",  errors);
    }
    return errors;
}
void save_to_file(const char* filename){
    FILE* f = fopen(filename, "w");
    if(!f){
        printf("Error: Cannot open %s for writing\n", filename);
        return;
    }

    Employee* temp = head;
    while (temp) {
        fprintf(f, "%s, %d, %s\n", temp->name, temp->id, temp->manager);
        temp = temp->next;
    }
    fclose(f);
    printf("Saved %d employees to %s\n", count_employees(), filename);
}

void load_from_file(const char* filename) {
    FILE* f = fopen(filename, "r");
    if(!f) {
        printf("Error: Cannot open %s for reading\n", filename);
        return;
    }
    delete_employee_list(); 

    char line[150];
    while(fgets(line, sizeof(line), f)) {

        char name [MAX_NAME];

        int id;

        char manager [MAX_MANAGER] ={0};

        if(sscanf(line, "%49[^,],%d, %49[^\n]", name, &id, manager) >= 2){

            char *m = manager;
            while(*m == ' ') m++;
            insert_employee(name, id, m);
          }
    }
    fclose(f);
    recompute_all_ranks();
    printf("Loaded employee from %s\n", filename);
}
