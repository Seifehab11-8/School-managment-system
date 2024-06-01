#include<stdio.h>
#include<stdint.h>

//creating a typedef structure to the student info.
typedef struct 
{
    int32_t ID;
    char name[300];
    char date_of_birth[20];
    char major[100];
    char semester[50];
}school_database_t;
/*==================================================*/
void displayRecords(school_database_t*arr);
void addNewRecords(school_database_t*arr);
void deleteRecord (school_database_t* arr);
void searchData (school_database_t* arr);
/*==================================================*/
//variable to store 10 student data
school_database_t students[10];

int main(){
    uint32_t order;
    while(1){
        printf("Display all records -->1\n");
        printf("Add new records     -->2\n");
        printf("Delete a record     -->3\n");
        printf("Search for st ID    -->4\n");
        printf("Exit application    -->0\n");
        printf("============================\nEnter your option here: ");
        
        if(!scanf("%d",&order)){
            printf("You have entered an invalid input, Exiting...\n");
            return 0;
        }
        if(order==1){
            displayRecords(students);
        }else if(order==2){
            addNewRecords(students);
        }else if(order==3){
            deleteRecord(students);
        }else if(order==4){
            searchData(students);
        }else if(!order){
            printf("\nThank you for using the DATABASE\nExiting...\n");
            return 0;
        }else{
            printf("You've entered a Wrong Option, Try Again...\n");
        }
    }
}
void displayRecords(school_database_t*arr){
    uint32_t flag=0;
    for(uint32_t i=0 ;i<10; i++){
        if(!((arr+i)->ID)){
            flag++;
            continue; //skip the iterations in which the user didn't input
        }
        printf("Student %d\n===============================\n",i+1);
        printf("ID: %d\n",(arr+i)->ID);
        printf("full name: %s\n",(arr+i)->name);
        printf("Date of Birth: %s\n",(arr+i)->date_of_birth);
        printf("Semester: %s\n",(arr+i)->semester);
        printf("===============================\n");
    }
    if(flag==10){
        printf("==========================\n");
        printf("The Database is Empty\n==========================\n");
    }
}

void addNewRecords(school_database_t* arr){
    uint32_t flag1=0,flag2=0;
    for(uint32_t i=0 ;i<10;i++){
        if(!((arr+i)->ID)){
            printf("Enter student ID: ");
            if(!scanf("%d",(&(arr[i]).ID))){
                printf("you've entered invalid input\n");
                return 0;
            }
            if(!((arr+i)->ID)){
                printf("You have entered invalid ID\n");
                ((arr+i)->ID)=0;
                break;
            }
            for(uint32_t j=0; j<10;j++){
                if(i==j){
                    continue;
                }
                if(((arr+i)->ID)==((arr+j)->ID)){
                    printf("These is a duplicate ID. INVALID\n");
                    ((arr+i)->ID)=0;
                    flag2++;
                }
            }
            if(flag2){
                break;
            }
            printf("Enter student full name: ");
            getchar();// I dont know but seems to be a \n sended from somewhere that was causing errors
            scanf("%[^\n]s",(arr+i)->name);
            printf("Enter student birth date dd/mm/yy: ");
            getchar();
            scanf("%[^\n]s",(arr+i)->date_of_birth);
            printf("Enter student Major: ");
            getchar();
            scanf("%[^\n]s",(arr+i)->major);
            printf("Enter student Semester: ");
            getchar();
            scanf("%[^\n]s",(arr+i)->semester);
            printf("===============================\n");
            break;
        }
        flag1++;
    }
    if(flag1==10){
        printf("===============================\n");
        printf("The Database is full please delete some users");
        printf("===============================\n");
    }
}
void deleteRecord (school_database_t* arr){
    uint32_t IDsearch,flag=0;
    printf("Enter student ID: ");
    scanf("%d",&IDsearch);
    for(uint32_t i=0;i<10;i++){
        if((arr[i].ID)==IDsearch){
            arr[i].ID=0;
            printf("========================The user have been deleted Successfully\n");
            printf("========================\n");
            break;
        }else{
            flag++;
        }
    }
    if(flag==10){
        printf("There is no ID with the input you entered\n");
    }
}
void searchData (school_database_t* arr){
    uint32_t IDsearch,flag=0;
    printf("Enter student ID: ");
    scanf("%d",&IDsearch);
    for(uint32_t i=0;i<10;i++){
        if((arr[i].ID)==IDsearch){
            printf("Student %d\n===============================\n",i+1);
            printf("ID: %d\n",(arr+i)->ID);
            printf("full name: %s\n",(arr+i)->name);
            printf("Date of Birth: %s\n",(arr+i)->date_of_birth);
            printf("Semester: %s\n",(arr+i)->semester);
            printf("===============================\n");
            break;
        }else{
            flag++;
        }
    }
    if(flag==10){
        printf("===============================\n");
        printf("There is no ID with the input you Entered\n");
        printf("===============================\n");
    }
}