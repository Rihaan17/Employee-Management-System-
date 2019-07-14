#include <stdio.h>
#include <string.h>

void add_employee();
int search_id( int employee_id );
void update_info( int employee_id );
void delete_employee( int employee_id );
double display_avd_salary();
void search_join_date( int day, int month, int year );
double max_sal();
int count_rank( char rank[] );
void search_name( char name[50] );

struct joining_date {
    int date;
    int month;
    int year;
};

struct employee_struct {
    int employee_id;
    char employee_name[50];
    char rank[50];
    float salary;
    char phone_no[50];
    struct joining_date joining_date;
};

struct employee_struct employees[500];
int key = 0;

int main()
{
    struct employee_struct employee;
    int option, flag = 1, id, day, month, year, i, rankCount = 0;
    double result = 0;
    char name[50], rank[50];

    while ( 1 ) {
        option = menu();
        switch ( option ) {
            case -1:
                flag = 0;
                break;
            case 1:
                add_employee();
                break;
            case 2:
                printf("Enter your id: ");
                scanf("%d", &id);
                search_id( id );
                break;
            case 3:
                printf("Enter your id: ");
                scanf("%d", &id);
                update_info( id );
                break;
            case 4:
                printf("Enter your id: ");
                scanf("%d", &id);
                delete_employee( id );
                break;
            case 5:
                result = display_avd_salary();
                printf("Average Salary: %lf\n", result);
                break;
            case 6:
                printf("Enter your date: ");
                scanf("%d-%d-%d", &day, &month, &year);
                search_join_date( day, month, year );
                break;
            case 7:
                result = max_sal();
                for ( i = 0; i <= key; i++ ) {
                    if ( result == employees[i].salary ) {
                        printf("%d ", employees[i].employee_id);
                    }
                }
                printf("\n");
                break;
            case 8:
                printf("Enter your Rank:");
                getchar();
                gets(rank);
                rankCount = count_rank( rank );
                printf("The number of employees of this rank is %d\n", rankCount);
                break;
            case 9:
                printf("Enter your name: ");
                getchar();
                gets(name);
                search_name( name );
                break;
        }
        if ( flag == 0 ) {
            break;
        }
    }

    return 0;
}

int menu()
{
    int option;

    printf("1. Add new employee\n");
    printf("2. Search an employee by id\n");
    printf("3. Update employee info\n");
    printf("4. Delete employee\n");
    printf("5. Display average salary\n");
    printf("6. Search employee ids after a given joining date\n");
    printf("7. Search employee ids having maximum salary\n");
    printf("8. Search total no of employees by designation\n");
    printf("9. Search employee ids having the given name\n");
    printf("Enter -1 to exit.\n");

    scanf("%d", &option);

    return option;

}

void add_employee()
{
    int i, idFlag = 1, phoneFlag = 1;

    struct employee_struct employee;

    printf("Employee ID:");
    scanf("%d", &employee.employee_id);

    for ( i = 0; i < key; i++ ) {
        if( employees[i].employee_id == employee.employee_id ) {
            idFlag = 0;
            printf("Please provide an unique ID!\n");
            return;
        }
    }

    printf("Name of the employee:");
    getchar();
    gets(employee.employee_name);

    printf("Designation of the employee:");
    gets(employee.rank);

    printf("Salary of the employee:");
    scanf( "%f", &employee.salary );

    printf("Phone no of the employee:");
    getchar();
    gets(employee.phone_no);

    for ( i = 0; i < key; i++ ) {
        if( strcmp( employees[i].phone_no, employee.phone_no ) == 0 ) {
            phoneFlag = 0;
            printf("Please provide an unique Phone number!\n");
            return;
        }
    }

    printf("Joining date of the employee (dd-mm-yyyy):");
    scanf( "%d-%d-%d", &employee.joining_date.date, &employee.joining_date.month, &employee.joining_date.year );

    employees[key++] = employee;
}

int search_id(int id)
{
    int i, flag = 0;

    for ( i = 0; i <= key; i++ ) {
        if ( employees[i].employee_id == id ) {
            flag = 1;
            printf("ID: %d\n", employees[i].employee_id);
            printf("Name: %s\n", employees[i].employee_name);
            printf("Designation: %s\n", employees[i].rank);
            printf("Salary: %f\n", employees[i].salary);
            printf("Phone: %s\n", employees[i].phone_no);
            printf("Joining Date: %d-%d-%d\n\n", employees[i].joining_date.date, employees[i].joining_date.month, employees[i].joining_date.year);
            return i;
        }
    }

    if ( flag == 0 ) {
        printf("Not Found\n");
        return -1;
    }
}

void update_info( int id )
{
    struct employee_struct employee;
    int result, i, idFlag = 1, phoneFlag = 1;

    result = search_id( id );

    if ( result != -1 ) {
        printf("Employee ID:");
        scanf("%d", &employee.employee_id);

        for ( i = 0; i < key; i++ ) {
            if( employees[i].employee_id == employee.employee_id ) {
                idFlag = 0;
                printf("Please provide an unique ID!\n");
                return;
            }
        }

        printf("Name of the employee:");
        getchar();
        gets(employee.employee_name);

        printf("Designation of the employee:");
        gets(employee.rank);

        printf("Salary of the employee:");
        scanf( "%f", &employee.salary );

        printf("Phone no of the employee:");
        getchar();
        gets(employee.phone_no);

        for ( i = 0; i < key; i++ ) {
            if( strcmp( employees[i].phone_no, employee.phone_no ) == 0 ) {
                phoneFlag = 0;
                printf("Please provide an unique Phone number!\n");
                return;
            }
        }

        printf("Joining date of the employee (dd-mm-yyyy):");
        scanf( "%d-%d-%d", &employee.joining_date.date, &employee.joining_date.month, &employee.joining_date.year );

        employees[result] = employee;

        printf("Updated Successfully.\n");
    }
    else {
        printf("Not Exists.\n");
    }
}

void delete_employee( int id )
{
    struct employee_struct employee;
    int result, i;

    result = search_id( id );

    if ( result != -1 ) {
        for ( i = result; i < key; i++ ) {
            employees[i] = employees[i+1];
        }
    }
}

double display_avd_salary()
{
    int i, sum = 0;
    double result;

    for ( i = 0; i < key; i++ ) {
        sum = sum + employees[i].salary;
    }

    result = sum / i;
    return result;

}

void search_join_date( int day, int month, int year )
{
    int i;

    for ( i = 0; i < key; i++ ) {
        if ( employees[i].joining_date.year > year ) {
            printf("%d\n", employees[i].employee_id);
        }
        else if ( employees[i].joining_date.year == year ) {
            if ( employees[i].joining_date.month > month ) {
                printf("%d\n", employees[i].employee_id);
            }
            else if ( employees[i].joining_date.month == month ) {
                if( employees[i].joining_date.date > day ) {
                    printf("%d\n", employees[i].employee_id);
                }
            }
        }
    }
}

double max_sal()
{
    double max = employees[0].salary;
    int i;

    for ( i = 0; i < key; i++ ) {
        if ( employees[i].salary > max ) {
            max = employees[i].salary;
        }
    }

    return max;
}

int count_rank( char rank[] )
{
    int i, counter = 0;

    for ( i = 0; i < key; i++ ) {
        if( strcmp( employees[i].rank, rank ) == 0 ) {
            counter++;
        }
    }

    return counter;

}

void search_name( char name[] )
{
    int i;

    for ( i = 0; i < key; i++ ) {
        if( strcmp( employees[i].employee_name, name ) == 0 ) {
            printf("ID: %d\n", employees[i].employee_id);
        }
    }
}
