#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <cassert>
#include <Windows.h>
#include <comdef.h>
#import "msado15.dll" no_namespace rename("EOF", "EndOfFile") // For database access

using namespace std;

class Bank {
public:
    void acc_write();
    void modify_account();
    void deposit_withdraw();
    void search_rec();
    void display_all();
    void transfer();
    void menu_c();
    void menu_e();
    void close();
    void employee();
    void fordelay(int j);
    void main_menu();
    void PrintProviderError(_ConnectionPtr pConnection);
    void BeginTransX();
    void TESTHR(HRESULT x);
};

// Function to simulate delay
void Bank::fordelay(int j) {
    int i, k;
    for (i = 0; i < j; i++)
        k = i;
}

void Bank::close(void) {
    printf("\n\n\n\nThis Program is Closed... Thank You");
}

// Employee authentication
void Bank::employee() {
    char pass[10];
    char c;
    string s, name;
    int i = 0;
    cout << "\n\n\t\tFor Security Purpose:";
    cout << "\n\n\t\tEnter the Login Employee Id:";
    cin >> name;
    cout << "\n\n\t\tEnter the password to login:";
    while (1) {
        c = getch();
        printf("*");
        s += c;
        if (c == '\r') {
            break;
        }
    }
    s = s.substr(0, s.size() - 1);
    cout << endl;
    if (s == "1234" && (name == "Shivam" || name == "Garima")) {
        printf("\n\nAccess Granted!\nLOADING");
        for (i = 0; i <= 6; i++) {
            fordelay(100000000);
            printf(".");
        }
        system("cls");
        menu_e();
    } else {
        printf("\n\nWrong password or Employee Id!!");
        login_try:
        cout << "\nEnter 1 to try again , 2 for Main Menu and 0 to Exit:";
        scanf("%d", &main_exit);
        if (main_exit == 1) {
            system("cls");
            employee();
        } else if (main_exit == 0) {
            system("cls");
            close();
        } else if (main_exit == 2) {
            system("cls");
            main_menu();
        } else {
            printf("\nInvalid!");
            fordelay(1000000000);
            system("cls");
            goto login_try;
        }
    }
}

// Main menu for employee
void Bank::menu_e() {
    int choice;
    menu:
    system("cls");
    system("color 2");
    cout << "\n\n\t\t\tBANK RECORD SYSTEM";
    cout << "\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2";
    cout << "\n\n\t\t\tEmployee Menu";
    cout << "\n\t\t1.Check the details of existing account\n";
    cout << "\t\t2.Display All Account Holder Name\n";
    cout << "\t\t3.Exit\n\n\n\n\n\t\t Enter your choice:";
    cin >> choice;
    system("cls");
    switch (choice) {
        case 1: search_rec();
                break;
        case 2: display_all();
                break;
        case 3: close();
                break;
        default: cout << "Invalid Input!\n";
                cout << "   Try Again\n";
                goto menu;
    }
}

// Customer menu
void Bank::customer() {
    char pass[10];
    char c;
    string s, name, acc_no, password;
    int i = 0, x;
    system("cls");
    cout << "\n\n\t\t\tMENU";
    cout << "\n\t\t1. New Customer";
    cout << "\n\t\t2. Existing Customer";
    cout << "\n\t\tEnter Your Choice : ";
    cin >> x;
    if (x == 1)
        menu_c();
    else {
        cout << "\n\n\t\tFor Security Purpose:";
        cout << "\n\n\t\tEnter the Login Customer Id:";
        cin >> name;
        cout << "\n\n\t\tEnter the password to login:";
        while (1) {
            c = getch();
            printf("*");
            s += c;
            if (c == '\r') {
                break;
            }
        }
        s = s.substr(0, s.size() - 1);
        cout << endl;
        ifstream is("Account_info.csv");
        do {
            getline(is, acc_no, ',');
            getline(is, password, '\n');
            if (acc_no == name) {
                i = 1;
                if (password == s)
                    printf("\n\nAccess Granted!\nLOADING");
                for (i = 0; i <= 6; i++) {
                    fordelay(100000000);
                    printf(".");
                }
                system("cls");
                menu_c();
            }
        } while (is.good());
        if (i == 0) {
            printf("\n\nWrong password or Customer Id!!");
            login_try:
            cout << "\nEnter 1 to try again , 2 for Main Menu and 0 to Exit:";
            scanf("%d", &main_exit);
            if (main_exit == 1) {
                system("cls");
                customer();
            } else if (main_exit == 0) {
                system("cls");
                close();
            } else if (main_exit == 2) {
                system("cls");
                main_menu();
            } else {
                printf("\nInvalid!");
                fordelay(1000000000);
                system("cls");
                goto login_try;
            }
        }
    }
}

// Customer menu
void Bank::menu_c(void) {
    int choice;
    Bank B;
    menu:
    system("cls");
    system("color 2");
    cout << "\n\n\t\t\tBANK RECORD SYSTEM";
    cout << "\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2";
    cout << "\n\n\t\t1.Create new account\n";
    cout << "\t\t2.Update information of existing account\n";
    cout << "\t\t3.For transactions\n";
    cout << "\t\t4.Check the details of existing account\n";
    cout << "\t\t5.For Transfer\n";
    cout << "\t\t6.Exit\n\n\n\n\n\t\t Enter your choice:";
    cin >> choice;

    system("cls");
    switch (choice) {
        case 1: acc_write();
                break;
        case 2: modify_account();
                break;
        case 3: deposit_withdraw();
                break;
        case 4: search_rec();
                break;
        case 5: transfer();
                break;
        case 6: close();
                break;
    }
    login_try:
    cout << "\nEnter 1 for Main Menu , 2 for Previous Menu and"
            << " 0 to Exit:";
    scanf("%d", &main_exit);
    if (main_exit == 1) {
        system("cls");
        main_menu();
    } else if (main_exit == 0) {
        system("cls");
        close();
    } else if (main_exit == 2) {
        system("cls");
        employee();
    } else {
        printf("\nInvalid!");
        fordelay(1000000000);
        system("cls");
        goto login_try;
    }
}

// Transaction Functions, Modify and other operations go here

int main() {
    Bank B;
    int ch, i;
    cout << "\n\n\n\n\n\t\t\t\tWelcome to our bank System";
    for (i = 0; i < 6; i++) {
        fordelay(100000000);
        printf(".");
    }
    menu:
    system("cls");
    system("color 4");
    cout << "\t\t\t ---------------------" << endl;
    cout << "\t\t\t| SAI'S MINI PROJECT |" << endl;
    cout << "\t\t\t ---------------------" << endl;
    system("color 3");
    cout << "\n\n\t\t\t\t MENU\n";
    cout << "\n\t\t1. Employee ";
    cout << "\n\t\t2. Customer ";
    cout << "\n\t\t3. Exit ";
    cout << "\n\t\tEnter Your Choice: ";
    cin >> ch;
    switch (ch) {
        case 1: employee();
                break;
        case 2: customer();
                break;
        case 3: close();
                break;
        default : cout << "Invalid Input! Try Again...\n";
                  fordelay(1000000000);
                  goto menu;
    }
}
