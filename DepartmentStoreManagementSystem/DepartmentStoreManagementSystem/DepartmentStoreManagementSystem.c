/****
 * Copyleft (L) 2021 CENG - All Rights Not Reserved
 * You may use, distribute and modify this code.
 ****/

/**
 * @file   DepartmentStoreManagementSystem.sln
 * @Author Ridvan KARASUBASÝ
 * @date   24 November 2021
 * @brief  <b>Department Store Management System</b>
 *
 * DepartmentStoreManagementSystem
 * 
 * @see http://bilgisayar.mmf.erdogan.edu.tr/en/
 * 
 */

#define _CRT_SECURE_NO_WARNINGS

//LEARNPROGRAMO-PROGRAMMING MADE SIMPLE
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>

//files included
#include "translate.h"
#include "message.h"

#define ANS 15
#define ACS 4
COORD coord = { 0,0 }; // this is global variable
void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
/*declaration of checking functions*/
void c_code(char[]);
int check(char[]);

/*structure declaration*/
typedef struct
{
    char name[ANS], code[ACS];
    float rate;
    int quantity;
} rec;
rec item;

/*declaration of display functions*/
void curser(int);
void dbill();
void d_mainmenu();
void display(rec*, int, int);
void window(int, int, int, int);
void dis_con();
void d_search();
void highlight(int, int);

/*declaration of main menu functions*/
void bill();
void edit();
void add();
void del();
//new void created
void lang();
void exit();

/*declaration of display submenu functions*/
void d_code();
void d_rate();
void d_quan();
void d_all();

/*start of main*/
int main()
{
    //this variable keeps language setting that stored in file
    char langConfig[2 + 1] = { 0 };
    //language selection from console 0=en 1=tr
    int  langSelection = 0;

    //get current language setting from lang.conf file its "en" or "tr"
    getTranslateLang(langConfig);

    //set application language setting but setting is not set to file
    setTranslateLang(langConfig, false);

    d_mainmenu();
    return 0;
}

void d_mainmenu()
{
    int i;
    char ch;
    const char* menu[] = { "   Calculate Bill","   Add Goods","   Edit Goods","   Display All ","   Search", "   Delete Goods","   Change Language","   Exit" };
    system("cls");
    //textbackground(11);
    //textcolor(0);
    //_setcursortype(_NOCURSOR);
    window(25, 55, 20, 32);
    gotoxy(36, 18);
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(main_menu);
    printf("\n");
    for (i = 0; i <= 7; i++)
    {
        gotoxy(30, 22 + i + 1);
        printf("%s\n\n\n", menu[i]);
    }
    curser(8);
}

void d_search()
{
    char ch;
    int i;
    //const char* menu[] = { "   By Code","   By Rate","   By Quantity","   Back to main menu" };
    system("cls");
    //textbackground(11);
    //textcolor(0);
    window(25, 50, 20, 32);
    gotoxy(33, 18);
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(search_menu);
    printf("\n");


    for (i = 0; i <= 3; i++)
    {
        gotoxy(30, 22 + i + 1);

        switch (i)
        {
        case 0: printf("%s\n\n\n", "   By Code"); break;
        case 1: printf("%s\n\n\n", "   By Rate"); break;
        case 2: printf("%s\n\n\n", "   By Quantity"); break;
        case 3: printf("%s\n\n\n", "   Back to main menu"); break;
        default:
            break;
        }

        //printf("%s\n\n\n", menu[i]);
    }
    curser(4);
}

/*function for cursor movement*/
void curser(int no)
{
    int count = 1;
    char ch = '0';
    gotoxy(30, 23);
    while (1)
    {
        switch (ch)
        {
        case 80:
            count++;
            if (count == no + 1) count = 1;
            break;
        case 72:
            count--;
            if (count == 0) count = no;
            break;
        }
        highlight(no, count);
        ch = _getch();
        if (ch == '\r')
        {
            if (no == 8)
            {
                if (count == 1) bill();
                else if (count == 2) add();
                else if (count == 3) edit();
                else if (count == 4) d_all();
                else if (count == 5) d_search();
                else if (count == 6) del();
                else if (count == 7) lang();
                else   exit(0);
            }
            if (no == 4)
            {
                if (count == 1) d_code();
                else if (count == 2)d_rate();
                else if (count == 3) d_quan();
                else d_mainmenu();
            }
        }
    }
}

void highlight(int no, int count)
{
    if (no == 4)
    {
        //textbackground(11);
        //textcolor(0);
        gotoxy(30, 23);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(by_code1);
        gotoxy(30, 24);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(by_rate1);
        gotoxy(30, 25);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(by_quantity1);
        gotoxy(30, 26);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(back_to_main_menu1);
        //textcolor(0);
        //textbackground(2);
        switch (count)
        {
        case 1:
            gotoxy(30, 23);
            //if the selected language is Turkish, tr.dat works, otherwise en.dat works
            printTranslateLang(by_code2);
            break;
        case 2:
            gotoxy(30, 24);
            //if the selected language is Turkish, tr.dat works, otherwise en.dat works
            printTranslateLang(by_rate2);
            break;
        case 3:
            gotoxy(30, 25);
            //if the selected language is Turkish, tr.dat works, otherwise en.dat works
            printTranslateLang(by_quantity2);
            break;
        case 4:
            gotoxy(30, 26);
            //if the selected language is Turkish, tr.dat works, otherwise en.dat works
            printTranslateLang(back_to_main_menu2);
            break;
        }
    }

    if (no == 8)
    {
        //textbackground(11);
        //textcolor(0);
        gotoxy(30, 23);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(calculate_bill1);
        gotoxy(30, 24);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(add_goods1);
        gotoxy(30, 25);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(edit_goods1);
        gotoxy(30, 26);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(display_all1);
        gotoxy(30, 27);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(search1);
        gotoxy(30, 28);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(delete_goods1);
        gotoxy(30, 29);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(change_language1);
        gotoxy(30, 30);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(exit1);
        //textcolor(0);
        //textbackground(2);
        switch (count)
        {
        case 1:
            gotoxy(30, 23);
            //if the selected language is Turkish, tr.dat works, otherwise en.dat works
            printTranslateLang(calculate_bill2);
            break;
        case 2:
            gotoxy(30, 24);
            //if the selected language is Turkish, tr.dat works, otherwise en.dat works
            printTranslateLang(add_goods2);
            break;
        case 3:
            gotoxy(30, 25);
            //if the selected language is Turkish, tr.dat works, otherwise en.dat works
            printTranslateLang(edit_goods2);
            break;
        case 4:
            gotoxy(30, 26);
            //if the selected language is Turkish, tr.dat works, otherwise en.dat works
            printTranslateLang(display_all2);
            break;
        case 5:
            gotoxy(30, 27);
            //if the selected language is Turkish, tr.dat works, otherwise en.dat works
            printTranslateLang(search2);
            break;
        case 6:
            gotoxy(30, 28);
            //if the selected language is Turkish, tr.dat works, otherwise en.dat works
            printTranslateLang(delete_goods2);
            break;
        case 7:
            gotoxy(30, 29);
            //if the selected language is Turkish, tr.dat works, otherwise en.dat works
            printTranslateLang(change_language2);
            break;
        case 8:
            gotoxy(30, 30);
            //if the selected language is Turkish, tr.dat works, otherwise en.dat works
            printTranslateLang(exit2);
            break;
        }
    }
}

void bill()
{
    char x[4] = { 0 };
    int j = 29, q = 0, size = 0, i = 1;
    float total = 0, gtotal = 0;
    FILE* file;
    file = fopen("record.txt", "r+b");
    rewind(file);
    system("cls");
    dbill();
    gotoxy(26, 15);
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(enter_end_to_finish_input);
    while (1)
    {
        gotoxy(25, 18);
        printf("                    ");
        gotoxy(25, 19);
        printf("                    ");
        gotoxy(25, 18);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(enter_item_code);
        scanf("%s", x);
        if (strcmp(x, "end") == 0)
            break;
        gotoxy(25, 19);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(enter_quantity);
        scanf("%d", &q);
        rewind(file);
        while (fread(&item, sizeof(item), 1, file))
        {
            if ((strcmp(item.code, x) == 0))
            {
                total = item.rate * q;
                gotoxy(11, j);
                printf("%4d", i);
                printf("%9s", item.name);
                printf("%13d", q);
                printf("%15.2f", item.rate);
                printf("%13.2f", total);
                gtotal = gtotal + total;
                size = sizeof(item);
                item.quantity = item.quantity - q;
                j += 2;
                i++;
                fseek(file, -size, SEEK_CUR);
                fwrite(&item, sizeof(item), 1, file);
                break;
            }
        }
    }
    if (gtotal != 0)
    {
        gotoxy(30, j + 5);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(total_amount);
        printf(" % 6.2f", gtotal);
    }
    fclose(file);
    _getch();
    d_mainmenu();
}
/*function to display bill window*/
void dbill()
{
    int i;
    gotoxy(20, 10);
    //;
    for (i = 1; i <= 10; i++)
        printf("*");
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(fashion_wear);
    for (i = 1; i <= 10; i++)
        printf("*");
    printf("\n\n");
    gotoxy(30, 11);
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(department_store);
    //textcolor(1);
    gotoxy(32, 25);
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(customers_bill);
    //textcolor(8);
    gotoxy(13, 27);
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(sn_);

}
/*function to add records*/
void add()
{
    FILE* file;
    char y[ACS], x[12];
    system("cls");
    //textbackground(11);
    //textcolor(0);
    gotoxy(25, 25);
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(enter_new_record);
    while (toupper(_getche()) == 'Y')
    {
        system("cls");
        file = fopen("record.txt", "ab");
        c_code(y);
        strcpy(item.code, y);
        gotoxy(22, 28);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(enter_rate_of_the_item);
        scanf("%f", &item.rate);
        gotoxy(22, 30);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(enter_quantity_of_the_item);
        scanf("%d", &item.quantity);
        gotoxy(22, 32);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(enter_name_of_the_item);
        scanf("%s", item.name);
        fseek(file, 0, SEEK_END);
        fwrite(&item, sizeof(item), 1, file);
        fclose(file);
        gotoxy(22, 34);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(enter_new_record_);

    }
    d_mainmenu();
}

/*function to check availability of code*/
void c_code(char y[])
{
    int flag;
    FILE* file;
    file = fopen("record.txt", "rb");
    while (1)
    {
        system("cls");
        window(20, 58, 23, 36);
        gotoxy(32, 18);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(add_articles);
        flag = 1;
        rewind(file);
        gotoxy(22, 25);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(enter_new_code_of_the_article);
        scanf(" %[^\n]", y);
        while (fread(&item, sizeof(item), 1, file) == 1)
        {
            if (strcmp(y, item.code) == 0)
            {
                flag = 0;
                gotoxy(26, 30);
                //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                printTranslateLang(code_already_exists);
                gotoxy(29, 32);
                //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                printTranslateLang(enter_again);
                _getch();
                break;
            }
        }
        if (flag == 1)
            break;
    }
}

/*function for editing*/
void edit()
{
    int flag = 0, choice;
    char x[ACS], y[ACS];
    FILE* file = NULL;
    int size;
    system("cls");
    //textcolor(0);
    //textbackground(11);
    window(20, 63, 20, 46);
    gotoxy(35, 18);
    printTranslateLang(edit_records);
    ;
    gotoxy(25, 23);
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(enter_item_code4);
    scanf("%s", x);
    flag = check(x);
    if (flag == 0)
    {
        file = fopen("record.txt", "r+b");
        rewind(file);
        while (fread(&item, sizeof(item), 1, file))
        {
            if (strcmp(item.code, x) == 0)
            {
                //textcolor(0);
                gotoxy(25, 27);
                //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                printTranslateLang(name1);
                printf("%s", item.name);
                gotoxy(25, 28);
                //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                printTranslateLang(code1);
                printf("%s", item.code);
                gotoxy(25, 29);
                //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                printTranslateLang(rate1);
                printf("%g", item.rate);
                gotoxy(25, 30);
                //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                printTranslateLang(quantity1);
                printf("%d", item.quantity);
                gotoxy(25, 32);;
                //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                printTranslateLang(do_you_want_to_edit_this_record);
                fflush(file);
                if (toupper(_getche()) == 'Y')
                {
                    //textcolor(0);
                    gotoxy(25, 34);
                    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                    printTranslateLang(edit_name);
                    gotoxy(25, 35);
                    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                    printTranslateLang(edit_code);
                    gotoxy(25, 36);
                    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                    printTranslateLang(edit_rate);
                    gotoxy(25, 37);
                    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                    printTranslateLang(edit_quantity);
                    gotoxy(25, 39); ;
                    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                    printTranslateLang(enter_your_choice);
                    scanf("%d", &choice);
                    switch (choice)
                    {
                    case 1:
                        system("cls");
                        window(23, 48, 20, 40);
                        gotoxy(35, 18);
                        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                        printTranslateLang(edit_records);
                        gotoxy(25, 24);
                        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                        printTranslateLang(enter_new_name);
                        scanf("%s", item.name);
                        size = sizeof(item);
                        fseek(file, -size, SEEK_CUR);
                        fwrite(&item, sizeof(item), 1, file);
                        break;
                    case 2:
                        system("cls");
                        window(23, 65, 20, 40);
                        gotoxy(35, 18);
                        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                        printTranslateLang(edit_records);
                        gotoxy(25, 24);
                        c_code(y);
                        strcpy(item.code, y);
                        size = sizeof(item);
                        fseek(file, -size, SEEK_CUR);
                        fwrite(&item, sizeof(item), 1, file);
                        break;
                    case 3:
                        system("cls");
                        window(23, 65, 20, 40);
                        gotoxy(35, 18);
                        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                        printTranslateLang(edit_records);
                        gotoxy(25, 24);
                        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                        printTranslateLang(enter_new_rate);
                        scanf("%f", &item.rate);
                        size = sizeof(item);
                        fseek(file, -size, SEEK_CUR);
                        fwrite(&item, sizeof(item), 1, file);
                        break;
                    case 4:
                        system("cls");
                        window(23, 65, 20, 40);
                        gotoxy(35, 18);
                        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                        printTranslateLang(edit_records);
                        gotoxy(25, 24);
                        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                        printTranslateLang(enter_new_quantity);
                        scanf("%d", &item.quantity);
                        size = sizeof(item);
                        fseek(file, -size, 1);
                        fwrite(&item, sizeof(item), 1, file);
                        break;
                    }
                    gotoxy(27, 30);
                    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                    printTranslateLang(item_edited);
                    break;
                }
            }
        }
    }
    if (flag == 1)
    {
        gotoxy(32, 30);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(item_does_not_exist);
        gotoxy(36, 32);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(try_again);
    }
    _getch();
    fclose(file);
    d_mainmenu();
}

/*function to display all records*/
void d_all()
{
    int i, j = 1;
    FILE* file;
    dis_con();
    file = fopen("record.txt", "rb");
    rewind(file);
    i = 26;
    fflush(file);
    while (fread(&item, sizeof(item), 1, file))
    {
        display(&item, i, j);
        i++;
        j++;
        if ((j % 20) == 0)
        {
            gotoxy(27, 47);/*textcolor(0)*/;
            //if the selected language is Turkish, tr.dat works, otherwise en.dat works
            printTranslateLang(press_any_key_to_see_more);
            _getch();
            system("cls");
            dis_con();
            i = 26;
            continue;
        }
    }
    _getch();
    if (i == 26)
    {
        gotoxy(24, 30);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(no_articles_found);
    }
    _getch();
    fclose(file);
    d_mainmenu();
}

/*function to display by quantity*/
void d_quan()
{
    int i, j = 1;
    int a, b;
    FILE* file;
    dis_con();
    file = fopen("record.txt", "rb");
    rewind(file);
    i = 26;
    gotoxy(16, 20);;
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(enter_lower_range);
    scanf("%d", &a);
    gotoxy(16, 21);
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(enter_upper_range);
    scanf("%d", &b);
    fflush(file);
    while (fread(&item, sizeof(item), 1, file))
    {
        if ((item.quantity >= a) && (item.quantity <= b))
        {
            display(&item, i, j);
            i++;
            j++;
            if ((j % 20) == 0)
            {
                gotoxy(27, 47);
                //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                printTranslateLang(press_any_key_to_see_more);
                _getch();
                system("cls");
                dis_con();
                i = 26;
                continue;
            }
        }
    }
    _getch();
    if (i == 26)
    {
        gotoxy(28, 30);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(no_items_found);
    }
    _getch();
    d_search();
    fclose(file);
}

/*function to display by rate*/
void d_rate()
{
    int i, j = 1;
    float a, b;
    FILE* file;
    dis_con();
    file = fopen("record.txt", "rb");
    rewind(file);
    i = 26;
    gotoxy(16, 20);;
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(enter_lower_range);
    scanf("%f", &a);
    gotoxy(16, 21);
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(enter_upper_range);
    scanf("%f", &b);
    fflush(file);
    while (fread(&item, sizeof(item), 1, file))
    {
        if ((item.rate >= a) && (item.rate <= b))
        {
            display(&item, i, j);
            i++;
            j++;
            if ((j % 20) == 0)
            {
                gotoxy(27, 47);
                //if the selected language is Turkish, tr.dat works, otherwise en.dat works
                printTranslateLang(press_any_key_to_see_more);
                _getch();
                system("cls");
                dis_con();
                i = 26;
                continue;
            }
        }
    }
    _getch();
    if (i == 26)
    {
        gotoxy(28, 30);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(no_items_found);
    }
    _getch();
    fclose(file);
    d_search();
}

/*function to display by code*/
void d_code()
{
    int i, j = 1;
    char x[4] = { 0 };
    FILE* file;
    dis_con();
    file = fopen("record.txt", "rb");
    rewind(file);
    i = 26;
    gotoxy(16, 20);;
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(enter_item_code);
    scanf("%s", x);
    fflush(file);
    while (fread(&item, sizeof(item), 1, file))
    {
        if ((strcmp(item.code, x) == 0))
        {
            display(&item, i, j);
            i++;
            j++;
            break;
        }
    }
    if (i == 26)
    {
        gotoxy(28, 30);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(no_items_found);
    }
    _getch();
    fclose(file);
    d_search();
}

/*function to display window for item display*/
void dis_con()
{
    int i;
    system("cls");
    gotoxy(20, 10);
    ;
    for (i = 1; i <= 10; i++)
        printf("*");
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(fashion_wear);
    for (i = 1; i <= 10; i++)
        printf("*");
    printf("\n\n");
    gotoxy(30, 11);
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(department_store);
    //textcolor(1);
    gotoxy(32, 17);
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(records);
    //textcolor(8);
    gotoxy(18, 23);
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(sn_);
}

/*function to display in screen*/
void display(rec* item, int i, int j)
{
    gotoxy(16, i);//textcolor(13);
    printf("%4d", j);
    printf("%9s", item->name);
    printf("%12s", item->code);
    printf("%14.2f", item->rate);
    printf("%11d", item->quantity);
}

/*function to delete records*/
void del()
{
    int flag;
    char x[ANS];
    FILE* file = NULL, * file1 = NULL;
    system("cls");
    //textbackground(11);
    //textcolor(0);
    window(23, 51, 25, 34);
    gotoxy(29, 18);
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(delete_articles);
    gotoxy(27, 27);
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(enter_item_code);
    scanf("%s", x);
    flag = check(x);
    if (flag == 0)
    {
        file1 = fopen("record1.txt", "ab");
        file = fopen("record.txt", "rb");
        rewind(file);
        while (fread(&item, sizeof(item), 1, file))
        {
            if (strcmp(item.code, x) != 0)
                fwrite(&item, sizeof(item), 1, file1);
        }
        gotoxy(27, 29);
        printTranslateLang(item_deleted);
        remove("record.txt");
        rename("record1.txt", "record.txt");
    }
    if (flag == 1)
    {
        gotoxy(25, 29);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(item_does_not_exist);
        gotoxy(30, 31);
        //if the selected language is Turkish, tr.dat works, otherwise en.dat works
        printTranslateLang(try_again);
    }
    fclose(file1);
    fclose(file);
    _getch();
    d_mainmenu();
}

/*function to check validity of code while editing and deleting*/
int check(char x[ANS])
{
    FILE* file;
    int flag = 1;
    file = fopen("record.txt", "rb");
    rewind(file);
    while (fread(&item, sizeof(item), 1, file))
    {
        if (strcmp(item.code, x) == 0)
        {
            flag = 0;
            break;
        }
    }
    fclose(file);
    return flag;
}

/*function to display box*/
void window(int a, int b, int c, int d)
{
    int i;
    system("cls");
    gotoxy(20, 10);
    //textcolor(1);
    for (i = 1; i <= 10; i++)
        printf("*");
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(fashion_wear);
    for (i = 1; i <= 10; i++)
        printf("*");
    printf("\n\n");
    gotoxy(30, 11);
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(department_store);
    //textcolor(4);
    for (i = a; i <= b; i++)
    {
        gotoxy(i, 17);
        printf("\xcd");
        gotoxy(i, 19);
        printf("\xcd");
        gotoxy(i, c);
        printf("\xcd");
        gotoxy(i, d);
        printf("\xcd");
    }

    gotoxy(a, 17);
    printf("\xc9");
    gotoxy(a, 18);
    printf("\xba");
    gotoxy(a, 19);
    printf("\xc8");
    gotoxy(b, 17);
    printf("\xbb");
    gotoxy(b, 18);
    printf("\xba");
    gotoxy(b, 19);
    printf("\xbc");
    //textcolor(4);
    for (i = c; i <= d; i++)
    {
        gotoxy(a, i);
        printf("\xba");
        gotoxy(b, i);
        printf("\xba");
    }
    gotoxy(a, c);
    printf("\xc9");
    gotoxy(a, d);
    printf("\xc8");
    gotoxy(b, c);
    printf("\xbb");
    gotoxy(b, d);
    printf("\xbc");
    //textbackground(11);
    //textcolor(0);
}

void lang()
{
    window(25, 65, 20, 32);
    gotoxy(38, 18);
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(change_language1);

    //language selection from console 0=en 1=tr
    int  langSelection = 0;


    //ask for language
    gotoxy(27, 22);
    printf("----> for english press \"0\".\n");
    gotoxy(27, 24);
    printf("----> turkce icin \"1\"e basin.\n");
    gotoxy(27, 26);
    //if the selected language is Turkish, tr.dat works, otherwise en.dat works
    printTranslateLang(enter_your_choice1);
    gotoxy(27, 27);
    //get input
    scanf("%d", &langSelection);


    if (langSelection == APP_LANG_TR)
    {
        //if TR selected then set application language to Turkish 
        setTranslateLang(TURKISH_L, true);
    }
    else {
        //other cases set language to English 
        setTranslateLang(ENGLISH_L, true);
    }
    
    d_mainmenu();
}