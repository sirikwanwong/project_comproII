#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

void print_stage();
void print_list_of_artist();
void booking_system(char temp_list_of_artist[20][100], char temp_list_of_choice[], int total_artist);
void unbook_table(char *file_name);
void print_card(char *artist_name, char *name, char *table_no, int total_amount);
void manage_system_login();
void manage_system();
void manage_table(char *table, char *file_name);
void copy_file(FILE *write, FILE *read);
bool check_artist(char *temp_list_of_choice, char artist_name);
bool check_table(char *table, char *file_name);
bool add_artist();
bool delete_artist();
/*------------------โปรแกรมหลักหน้าแรก----------------------------------*/
void main()
{
    char choice;
    while (true)
    {
        printf("[1] manage system\n");
        printf("[2] Booking\n");
        printf("[3] Exit\n");
        printf("Enter choice : ");
        choice = getch();
        printf("\n");
        if (choice == '1')
            manage_system_login();
        else if (choice == '2')
            print_list_of_artist();
        else if (choice == '3')
        {
            printf("Exit. . .\n");
            break;
        }
        else
            printf("wrong!");
    }
}

void print_stage()
{
    printf("\n\t\t\t\t Maps\t\t\t\n");
    printf("\t\t\\\t\t stage\t\t\t/\n");
    printf("\t\t \\_____________________________________/\n");
}

void print_list_of_artist()
{
    FILE *read = NULL;

    char data[255] = {};
    char choice[10] = {};
    char list_of_artist[20][100];
    int total_artist = 0;
    int i = 0;
    read = fopen("list_of_artist.txt", "r");
    printf("\t\t\t  Orchid Bar\n");
    printf("\t\t   Make a reservation for concert\n");
    printf("\n\t\t_______________________________________\n");
    printf("\t\t\t\t  Play List\t\t\t\n");
    printf("\t\t   Names\t\tSelect\t   Date\n");
    if (read)
    {
        while (fgets(data, 255, read))
        {
            data[strlen(data) - 1] = '\0';
            if ((data[0] >= 65 && data[0] <= 90) || (data[0] >= 97 && data[0] <= 122))
            {
                printf("\t\t%-20s\t [%c]\t", data, data[0]);
                strcpy(list_of_artist[i], data);
                choice[i] = data[0];
                i++;
            }
            else
            {
                printf("%s\n", data);
            }
        }
        total_artist = i;

        printf("\n\t\t _______________________________________\n");
        booking_system(list_of_artist, choice, total_artist);
    }
    else
    {
        printf("File not found!");
    }
}

void booking_system(char temp_list_of_artist[20][100], char temp_list_of_choice[], int total_artist)
{
    char artist_name;
    char temp_artist_name;
    char select_table_booking[3];
    char name[30];
    char phone_number[10];
    int total_amount;
    char file_name[30];
    char file_name_temp[20] = "booking_table.txt";

    printf("Select name : ");
    artist_name = getch();

    file_name[0] = artist_name;
    file_name[1] = '_';

    for (int i = 0; i < strlen(file_name_temp); i++)
    {
        file_name[i + 3] = '\0';
        file_name[i + 2] = file_name_temp[i];
    }

    print_stage();
    unbook_table(file_name);
    if (check_artist(temp_list_of_choice, artist_name))
    {
        temp_artist_name = artist_name;
        printf("Select table you booking : ");
        scanf("%s", select_table_booking);

        if (check_table(select_table_booking, file_name))
        {
            printf("Enter your name : ");
            getchar();
            scanf("%[^\n]", name);

            printf("Phone number : ");
            scanf("%s", phone_number);

            //Check table price
            if (strcmp(select_table_booking, "A01") == 0 || strcmp(select_table_booking, "A02") == 0 || strcmp(select_table_booking, "A03") == 0)
                total_amount = 2500;
            else if (strcmp(select_table_booking, "B01") == 0 || strcmp(select_table_booking, "B02") == 0 || strcmp(select_table_booking, "B03") == 0)
                total_amount = 2000;
            else if (strcmp(select_table_booking, "C01") == 0 || strcmp(select_table_booking, "C02") == 0)
                total_amount == 1500;

            printf("Total amount : %d", total_amount);
            for (int i = 0; i < strlen(temp_list_of_choice); i++)
            {
                if (artist_name == temp_list_of_choice[i])
                {
                    printf("\n\t\t _______________________________________\n");
                    printf("\t\t\t\t%s\n", temp_list_of_artist[i]);
                    printf("\t\t\tName : %s\n", name);
                    printf("\t\t\tTable no : %s\n", select_table_booking);
                    printf("\t\t\t\t\t\t%d B\n", total_amount);
                    printf("\t\t _______________________________________\n");
                    print_card(temp_list_of_artist[i], name, select_table_booking, total_amount);
                    manage_table(select_table_booking, file_name);
                    break;
                }
                else if (i == strlen(temp_list_of_choice) - 1)
                    printf("Not on the list!\n");
            }
        }
        else
        {
            printf("Table is booked/wrong table!\n");
        }
    }
    else
    {
        printf("You enter wrong!\n");
        printf("Please try again...\n");
    }
}

void unbook_table(char *file_name)
{
    FILE *read, *create;
    read = fopen(file_name, "r");
    if (!read)
    {
        fclose(read);
        create = fopen(file_name, "w");
        fprintf(create, "00000000");
        fclose(create);
        read = fopen(file_name, "r");
    }
    char data;
    int i = 0;
    while (!feof(read))
    {
        data = fgetc(read);
        if (i == 0)
            printf("\t\t  [A01] ");
        else if (i == 1)
            printf("\t [A02] ");
        else if (i == 2)
            printf("\t[A03] ");
        else if (i == 3)
            printf("\t\t  [B01] ");
        else if (i == 4)
            printf("\t [B02] ");
        else if (i == 5)
            printf("\t[B03] ");
        else if (i == 6)
            printf("\t\t\t  [C01] ");
        else if (i == 7)
            printf("\t[C02] ");

        if (data == '0')
            printf("unbook ");
        else if (data == '1')
            printf("booked ");
        if (i == 2 || i == 5 || i == 7)
            printf("\n");
        i++;
    }
    printf("\n\t\t RowA = 2,500 bath\t(people <= 5)\n");
    printf("\t\t RowB = 2,000 bath\t(people <= 5)\n");
    printf("\t\t RowC = 1,000 bath\t(people <= 5)\n");

    fclose(read);
}

void print_card(char *artist_name, char *name, char *table_no, int total_amount)
{
    FILE *write;
    write = fopen("booking_card.txt", "ab+");
    fprintf(write, "_______________________________________\n\n");
    fprintf(write, "\t\t%s\n", artist_name);
    fprintf(write, "\tName : %s\n", name);
    fprintf(write, "\tTable no : %s\n", table_no);
    fprintf(write, "\t\t\t\t%d ฿\n", total_amount);
    fprintf(write, "_______________________________________\n");
    fclose(write);
}

//Manage system
void manage_system_login()
{
    char username[20];
    char password[20];
    char c;
    int i = 0;
    printf("Username : ");
    scanf("%s", username);
    printf("Password : ");
    while (true)
    {
        c = getch();
        //Check press Enter
        if (c == 13)
            break;
        password[i] = c;
        printf("*");
        i++;
    }
    password[i] = '\0';
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
        manage_system();
    else
        printf("\nUsername/Password is incorrect!\n");
}

void manage_system()
{
    char choice;
    printf("\n[1] Add artist\n");
    printf("[2] Delete artist\n");
    choice = getch();
    if (choice == '1')
        if (add_artist())
            printf("Add successfully\n");
        else
            printf("Add fail...\n");
    else if (choice == '2')
        if (delete_artist())
            printf("Delete successfully\n");
        else
            printf("Delete fail...\n");
}
void manage_table(char *table, char *file_name)
{
    FILE *read, *write;
    read = fopen(file_name, "r");
    write = fopen("temp_booking_table.txt", "w");
    char data = '\0';
    int current_position = 0, destination = 0;

    if (strcmp(table, "A01") == 0)
        destination = 1;
    else if (strcmp(table, "A02") == 0)
        destination = 2;
    else if (strcmp(table, "A03") == 0)
        destination = 3;
    else if (strcmp(table, "B01") == 0)
        destination = 4;
    else if (strcmp(table, "B02") == 0)
        destination = 5;
    else if (strcmp(table, "B03") == 0)
        destination = 6;
    else if (strcmp(table, "C01") == 0)
        destination = 7;
    else if (strcmp(table, "C02") == 0)
        destination = 8;

    while (!feof(read))
    {
        data = fgetc(read);
        current_position++;

        if (current_position == destination)
        {
            fprintf(write, "1");
            continue;
        }

        fprintf(write, "%c", data);
    }
    fclose(read);
    fclose(write);
    read = fopen("temp_booking_table.txt", "r");
    write = fopen(file_name, "w");
    copy_file(write, read);
}

bool add_artist()
{
    FILE *write;
    write = fopen("list_of_artist.txt", "ab+");
    if(!write)
        return false;

    char name[30];
    char day[10];
    char month[10];
    char year[10];
    printf("Artist name : ");
    getchar();
    scanf("%[^\n]", name);
    printf("Day(dd) : ");
    scanf("%s", day);
    printf("Month(mm) : ");
    scanf("%s", month);
    printf("Year(yyyy) : ");
    scanf("%s", year);
    fprintf(write, "%s\n", name);
    fprintf(write, "%s/%s/%s\n", day, month, year);
    fclose(write);
    return true;
}

bool delete_artist()
{
    FILE *read, *write;
    char data[255];
    read = fopen("list_of_artist.txt", "r");
    write = fopen("temp_list_of_artist.txt", "w");
    int delete_choice;
    int current_position = 0, destination = 1;
    int i = 1;
    //update data
    while (fgets(data, 254, read))
    {
        if ((data[0] >= 65 && data[0] <= 90) || (data[0] >= 97 && data[0] <= 122))
        {
            printf("[%d] %s", i++, data);
        }
    }
    fclose(read);

    printf("\nDelete -> ");
    scanf("%d", &delete_choice);
    destination = delete_choice * 2;
    read = fopen("list_of_artist.txt", "r");
    while (fgets(data, 255, read))
    {
        current_position++;
        if (current_position != destination - 1 && current_position != destination)
            fprintf(write, "%s", data);
    }
    fclose(write);
    fclose(read);
    read = fopen("temp_list_of_artist.txt", "r");
    write = fopen("list_of_artist.txt", "w");
    copy_file(write, read);
    return true;
}

void copy_file(FILE *write, FILE *read)
{
    char data[255];
    while (fgets(data, 254, read))
    {
        fprintf(write, "%s", data);
    }
    fclose(write);
    fclose(read);
}

bool check_artist(char *temp_list_of_choice, char artist_name)
{
    for (int i = 0; i < strlen(temp_list_of_choice); i++)
    {
        if (artist_name == temp_list_of_choice[i])
            return true;
    }
    return false;
}

bool check_table(char *table, char *file_name)
{
    FILE *read;
    read = fopen(file_name, "r");
    char data;
    int current_position = 1, destination = 0;
    if (strcmp(table, "A01") == 0)
        destination = 1;
    else if (strcmp(table, "A02") == 0)
        destination = 2;
    else if (strcmp(table, "A03") == 0)
        destination = 3;
    else if (strcmp(table, "B01") == 0)
        destination = 4;
    else if (strcmp(table, "B02") == 0)
        destination = 5;
    else if (strcmp(table, "B03") == 0)
        destination = 6;
    else if (strcmp(table, "C01") == 0)
        destination = 7;
    else if (strcmp(table, "C02") == 0)
        destination = 8;

    while (!feof(read))
    {
        data = fgetc(read);
        if (current_position == destination)
            if (data == '0')
                return true;
        current_position++;
    }
    return false;
}
