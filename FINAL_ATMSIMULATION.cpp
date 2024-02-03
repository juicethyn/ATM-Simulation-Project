#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream> // using for the file management
#include <time.h> // using for rand();
#include <unistd.h> // Using for sleep();
#include <conio.h> // for getch();
#include <sstream> // for stringstream to convert strings to int
#define MAX 999

// Made by Juzzthyn Griey C. Perez
// BSCS-2A-M
// Project 1 - ATM SIMULATION 
// Started: October 7, 2023 to October 28, 2023

typedef struct AccountInformation{
    int acc_number;
    char name[50];
    std::string birthday;
    std::string contact_number;
    int initial_deposit; // balance should be 5000 minimum
    int pin;
}AccInfo;

typedef struct ATMCardInfo{
    int acc_number;
    int pin;
}CardInfo;

class Account{
    private:
        AccInfo accountData[MAX];
        CardInfo account;
        int count = 0;

    public:
        // Read and Write Module
        void save_account();
        void read_account();
        void save_account_exit();
        int encrypt(int pin);
        int decrypt(int pin);
        bool isFlashDriveInserted();
        
        // Registration Module
        void create_account();

        // Transaction Module
        void login_account();
        void transaction_menu();
        void preview_balance();
        void balance_inquiry();
        void withdraw_and_deposit(int amount, int option);
        void fund_transfer_menu();
        void transfer_fund(int amount, int pos);
        void check_pin();
        void change_pin();

        //Test Module
        void display();
};

int main(){
    int choice;
    int num;
    Account acc;
    acc.read_account();

    do{
        system("cls");
        std::cout << "\t\t\t\t==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==" << std::endl;
        std::cout << "\t\t\t\t||       WELCOME TO THE ATM SIMULATION       ||" << std::endl;
        std::cout << "\t\t\t\t==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==" << std::endl;
        std::cout << "\t\t\t\t||                 MAIN MENU                 ||" << std::endl;
        std::cout << "\t\t\t\t===============================================" << std::endl;
        std::cout << "\t\t\t\t|| [1]. REGISTRATION MODULE                  ||" << std::endl;
        std::cout << "\t\t\t\t||-------------------------------------------||" << std::endl;
        std::cout << "\t\t\t\t|| [2]. TRANSACTION MODULE                   ||" << std::endl;
        std::cout << "\t\t\t\t||-------------------------------------------||" << std::endl;
        std::cout << "\t\t\t\t|| [3]. EXIT PROGRAM                         ||" << std::endl;
        std::cout << "\t\t\t\t||-------------------------------------------||" << std::endl;
        std::cout << "\t\t\t\t==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==" << std::endl;
        std::cout << "\t\t\t\tEnter choice: ";
        std::cin >> choice;

        switch(choice){
            case 1:
                acc.create_account();
                break;
            case 2:
                acc.read_account(); // New Add
                acc.login_account();
                break;
            case 3:
                std::cout << "\t\t\t\t    \\\\==================================//" << std::endl;
                std::cout << "\t\t\t\t    || THANK YOU FOR USING OUR SERVICE! ||" << std::endl;
                std::cout << "\t\t\t\t    //==================================\\\\" << std::endl;
                exit(0);
                break;
            case 4:
                acc.display();
                break;
        }
    }while(choice !=3);

    return 0;
}

// READ AND WRITE MODULE 
bool Account::isFlashDriveInserted(){
    std::fstream flashdrivefp("D:\\\\temp.txt", std::ios::out);
    flashdrivefp.close();
    return flashdrivefp.good();
}

void Account::save_account(){
    std::fstream fp;
    std::fstream flashdrivefp;
    std::fstream savecount;

    fp.open("AccountsData.txt", std::ios::app);
    flashdrivefp.open("D:\\\\Account.txt", std::ios::out);
    savecount.open("AccountCount.txt", std::ios::out);
    
    if(!flashdrivefp){
        std::cout << "Failed to Save. Insert ATM Card Correctly" << std::endl;
        system("pause");
    }
    else{
        account.acc_number = accountData[count].acc_number;
        // Impelement this two in the code
        accountData[count].pin = encrypt(accountData[count].pin);
        account.pin = accountData[count].pin;

        flashdrivefp << account.acc_number << std::endl;
        flashdrivefp << account.pin << std::endl;

        if(!fp){
        std::cout << "File Can't be open" << std::endl;
        system("pause");
        }
        else{
            fp << accountData[count].acc_number << std::endl;
            fp << accountData[count].name << std::endl;
            fp << accountData[count].birthday << std::endl;
            fp << accountData[count].contact_number << std::endl;
            fp << accountData[count].initial_deposit << std::endl;
            fp << accountData[count].pin << std::endl;
        }

        count++;
        if(!savecount){
            std::cout << "File Can't be open" << std::endl;
            system("pause");
        }
        else{
            savecount << count;
        }
    }

    fp.close();
    savecount.close();
    flashdrivefp.close();
}

void Account::save_account_exit(){
    std::fstream fp;
    std::fstream flashdrivefp;
    std::fstream savecount;

    fp.open("AccountsData.txt", std::ios::out|std::ios::in);
    flashdrivefp.open("D:\\\\Account.txt", std::ios::out);
    savecount.open("AccountCount.txt", std::ios::out);
    
    if(!flashdrivefp){
        std::cout << "Failed to Save. Insert ATM Card Correctly" << std::endl;
        system("pause");
    }
    else{

        for(int i = 0; i < count; i++){

            if(account.acc_number == accountData[i].acc_number){
                account.acc_number = accountData[i].acc_number;
            }

            if(account.pin == accountData[i].pin){
                account.pin = accountData[i].pin;
                account.pin = encrypt(account.pin);
            }

            // Impelement this two in the code
            // account.pin = encrypt(account.pin);
            accountData[i].pin = encrypt(accountData[i].pin);

            if(!fp){
            std::cout << "File Can't be open" << std::endl;
            system("pause");
            }
            else{
                fp << accountData[i].acc_number << std::endl;
                fp << accountData[i].name << std::endl;
                fp << accountData[i].birthday << std::endl;
                fp << accountData[i].contact_number << std::endl;
                fp << accountData[i].initial_deposit << std::endl;
                fp << accountData[i].pin << std::endl;
            }
        }

        flashdrivefp << account.acc_number << std::endl;
        flashdrivefp << account.pin << std::endl;

        savecount << count;
    }

    fp.close();
    savecount.close();
    flashdrivefp.close();
}

void Account::read_account(){
    std::fstream fp;
    std::fstream flashdrivefp;
    std::fstream savecount;


    while(true){

        if(!isFlashDriveInserted()){
        system("cls");
        std::cout << "\t\t\t\t\t==+==+==+==+==+==+==+==+==+==" << std::endl;
        std::cout << "\t\t\t\t\t||  PLEASE INSERT CARD...  ||" << std::endl;
        std::cout << "\t\t\t\t\t==+==+==+==+==+==+==+==+==+==" << std::endl;
        sleep(2);
        continue;
        }
        else{

            fp.open("AccountsData.txt", std::ios::in|std::ios::out);
            flashdrivefp.open("D:\\\\Account.txt", std::ios::in);
            savecount.open("AccountCount.txt", std::ios::in);

            if(!fp || !savecount){
                std::cout << "File Cannot be found" << std::endl;
                system("pause");
                return;
            }
            else{

                savecount >> count;
                for(int i = 0; i < count; i++){
                    fp >> accountData[i].acc_number;
                    fp.ignore();
                    fp.getline(accountData[i].name, 50);
                    std::getline(fp, accountData[i].birthday);
                    std::getline(fp, accountData[i].contact_number);
                    fp >> accountData[i].initial_deposit;
                    fp.ignore();
                    fp >> accountData[i].pin;
                    fp.ignore();

                    // Implement this in the code
                    accountData[i].pin = decrypt(accountData[i].pin);

                    flashdrivefp >> account.acc_number;
                    flashdrivefp.ignore();
                    flashdrivefp >> account.pin;
                    flashdrivefp.ignore();

                    // Implement this in the code
                    account.pin = decrypt(account.pin);
                }
            }
        }
        fp.close();
        savecount.close();
        flashdrivefp.close();
        flashdrivefp.flush();
        break;
    }
}

int Account::encrypt(int pin) {
    int encryptedPin = 0;
    int multiplier = 1;

    while (pin > 0) {
        int digit = pin % 10;
        digit = (digit + 7) % 10;
        encryptedPin += digit * multiplier;
        multiplier *= 10;
        pin /= 10;
    }

    return encryptedPin;
}

int Account::decrypt(int pin) {
    int decryptedPin = 0;
    int multiplier = 1;

    while (pin > 0) {
        int digit = pin % 10;
        digit = (digit + 3) % 10;
        decryptedPin += digit * multiplier;
        multiplier *= 10;
        pin /= 10;
    }

    return decryptedPin;
}

// Registration Module

void Account::create_account(){
    int posx = -1;
    std::fstream flashdrivefp;
    flashdrivefp.open("D:\\\\Account.txt", std::ios::in);
    if(flashdrivefp){
        sleep(1);
        std::cout << "\t\t\t\t\t=================================" << std::endl;
        std::cout << "\t\t\t\t\t|| CARD IS ALREADY REGISTERED! ||" << std::endl;
        std::cout << "\t\t\t\t\t=================================" << std::endl;
        system("pause");
    }
    else{   
        system("cls");
        std::cout << "\t\t\t\t||==============================================||" << std::endl;
        std::cout << "\t\t\t\t||         << REGISTER ACCOUNT MENU  >>         ||" << std::endl;
        std::cout << "\t\t\t\t==================================================" << std::endl;

        // If you want to automatic generate a account number;
        srand(time(0));
        accountData[count].acc_number = (rand() % 99999) + 10000;

        std::cout << "\t\t\t\t   ACCOUNT NUMBER (5DIGITS): " << accountData[count].acc_number;
        std::cout << std::endl;
        std::cout << "\t\t\t\t==______________________________________________==" << std::endl;

        // If you want to manually make ur own account number;
        // do{
        //     std::cout << "\t\t\t\t   ENTER ACCOUNT NUMBER (5DIGITS): ";
        //     std::cin >> accountData[count].acc_number;
        //     std::cout << "\t\t\t\t==______________________________________________==" << std::endl;

        //     for(int i = 0; i < count; i++){
        //         if(accountData[count].acc_number == accountData[i].acc_number){
        //             std::cout << "\t\t\t\t          ACCOUNT NUMBER ALREADY EXISTS " << std::endl;
        //             std::cout << "\t\t\t\t==______________________________________________==" << std::endl;
        //             posx = i;
        //         }
        //     }
        // }while(accountData[count].acc_number < 10000 or accountData[count].acc_number > 99999 or accountData[count].acc_number == accountData[posx].acc_number);
        std::cout << "\t\t\t\t   ENTER ACCOUNT NAME: ";
        std::cin.ignore();
        std::cin.getline(accountData[count].name, 50);
        std::cout << "\t\t\t\t==______________________________________________==" << std::endl;
        do{
            std::cout << "\t\t\t\t   ENTER BIRTHDAY (MONTH/DAY/YEAR): ";
            std::cin >> accountData[count].birthday;
            std::cout << "\t\t\t\t==______________________________________________==" << std::endl;

            if(accountData[count].birthday.length() != 10){
                std::cout << "\t\t\t\t            INVALID INPUT. TRY AGAIN" << std::endl;
                std::cout << "\t\t\t\t==______________________________________________==" << std::endl;
            }
        }while(accountData[count].birthday.length() != 10);
        do{
            std::cout << "\t\t\t\t   ENTER CONTACT NUMBER: ";
            std::cin >> accountData[count].contact_number;
            std::cout << "\t\t\t\t==______________________________________________==" << std::endl;

            if(accountData[count].contact_number.length() != 11){
                std::cout << "\t\t\t\t            NO. MUST BE 11 DIGITS ONLY" << std::endl;
                std::cout << "\t\t\t\t==______________________________________________==" << std::endl;
            }

        }while(accountData[count].contact_number.length() != 11);
        do{
            std::cout << "\t\t\t\t   ENTER INITIAL DEPOSIT (5000 MiN): ";
            std::cin >> accountData[count].initial_deposit;    
            std::cout << "\t\t\t\t==______________________________________________==" << std::endl;

            if(accountData[count].initial_deposit < 5000){
                std::cout << "\t\t\t\t       INITIAL DEPOSIT MUST BE MIN OF 5000 " << std::endl;
                std::cout << "\t\t\t\t==______________________________________________==" << std::endl;
            }

        }while(accountData[count].initial_deposit < 5000);
        do{
            std::cout << "\t\t\t\t   ENTER PIN CODE (6DIGITS): ";
            std::cin >> accountData[count].pin;
            std::cout << "\t\t\t\t==______________________________________________==" << std::endl;

            if(accountData[count].pin < 100000 or accountData[count].pin > 999999){
                std::cout << "\t\t\t\t          PIN CODE MUST BE 6 DIGITS ONLY " << std::endl;
                std::cout << "\t\t\t\t==______________________________________________==" << std::endl;
            }
        }while(accountData[count].pin < 100000 or accountData[count].pin > 999999);
        std::cout << "\t\t\t\t||+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=||" << std::endl;
        std::cout << std::endl;
        std::cout << "\t\t\t\t||==============================================||" << std::endl;
        std::cout << "\t\t\t\t||         <== CREATING ACCOUNT. ==>            ||" << std::endl;
        std::cout << "\t\t\t\t==================================================" << std::endl;
        sleep(1); 
        std::cout << "\t\t\t\t||==============================================||" << std::endl;
        std::cout << "\t\t\t\t||         <== CREATING ACCOUNT.. ==>           ||" << std::endl;
        std::cout << "\t\t\t\t==================================================" << std::endl;
        sleep(1);
        std::cout << "\t\t\t\t||==============================================||" << std::endl;
        std::cout << "\t\t\t\t||         <== CREATING ACCOUNT... ==>          ||" << std::endl;
        std::cout << "\t\t\t\t==================================================" << std::endl;
        sleep(1);
        std::cout << "\t\t\t\t||==============================================||" << std::endl;
        std::cout << "\t\t\t\t||    <== ACCOUNT SUCCESFULLY CREATED! ==>      ||" << std::endl;
        std::cout << "\t\t\t\t==================================================" << std::endl;
        save_account();
        system("pause");
    }
}

// Transaction Module

void Account::login_account(){
    int password;
    std::string pass;
    int pos;
    std::fstream flashdrive;
    flashdrive.open("D:\\\\Account.txt", std::ios::in);

    if(!flashdrive){
        sleep(1);
        std::cout << "\t\t\t    =======================================================" << std::endl;
        std::cout << "\t\t\t    || THERE IS NO ACCOUNT IN THIS CARD! PLEASE REGISTER ||" << std::endl;
        std::cout << "\t\t\t    =======================================================" << std::endl;
        system("pause");
        return;
    }
    else{
        
    for(int i = 0; i < count; i++){
        if(account.acc_number == accountData[i].acc_number){
            pos = i;
            break;
        }
    }
        do{
            system("cls");
            std::cout << "\t\t\t\t==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==" << std::endl;
            std::cout << "\t\t\t\t||                LOGIN MENU                 ||" << std::endl;
            std::cout << "\t\t\t\t==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==" << std::endl;
            std::cout << "\t\t\t\t|| ACCOUNT NUMBER: " << std::left << std::setw(15) << account.acc_number << "           ||" << std::endl;
            std::cout << "\t\t\t\t===============================================" << std::endl;
            std::cout << "\t\t\t\tENTER PIN CODE (6 DIGITS): ";

            // IMPLEMENTING THE ****** password
            pass.clear(); // Clear muna natin mga existing para iwas chuchu
            do{
                char ch = getch();
                if(ch == 13){
                    break;
                }
                if(ch == 8){
                    if(!pass.empty()){
                        pass.pop_back();
                        std::cout << "\b \b";
                    }
                }
                else if(isdigit(ch)){
                    std::cout << '*';
                    pass += ch;
                }
            }while(pass.length() != 15);

            std::stringstream(pass) >> password;
            std::cout << std::endl;

            std::cout << "\t\t\t\t===============================================" << std::endl;
            std::cout << "\t\t\t\t|| LOGGING IN...                             ||" << std::endl;
            std::cout << "\t\t\t\t===============================================" << std::endl;
            sleep(2);
            if(password == accountData[pos].pin){
                std::cout << "\t\t\t\t|| LOGGED IN SUCCESSFUL!                     ||" << std::endl;
                std::cout << "\t\t\t\t===============================================" << std::endl;
                sleep(2);
                transaction_menu();
            }
            else{
                std::cout << "\t\t\t\t|| INVALID PIN. TRY AGAIN                    ||" << std::endl;
                std::cout << "\t\t\t\t===============================================" << std::endl;
                sleep(2);
            }
            flashdrive.close();
        }while(password != account.pin and password != accountData[pos].pin);        
    }
}

void Account::transaction_menu(){
    int choice;
    int amount;
    do{
        system("cls");
        read_account();
        std::cout << "\t\t\t\t++============================================++" << std::endl;
        std::cout << "\t\t\t\t||        <<<< TRANSACTION MENU >>>>          ||" << std::endl;
        std::cout << "\t\t\t\t++============================================++" << std::endl;
        for(int i = 0; i < count; i++){
            if(account.acc_number == accountData[i].acc_number){
                std::cout << "\t\t\t\t||   Hello, "<< std::left << std::setw(30) << accountData[i].name << "    ||" << std::endl;
            }
        }
        std::cout << "\t\t\t\t||____________________________________________||" << std::endl;
        std::cout << "\t\t\t\t||   [1] BALANCE INQUIRY                      ||" << std::endl;
        std::cout << "\t\t\t\t||____________________________________________||" << std::endl;
        std::cout << "\t\t\t\t||   [2] WITHDRAW                             ||" << std::endl;
        std::cout << "\t\t\t\t||____________________________________________||" << std::endl;
        std::cout << "\t\t\t\t||   [3] DEPOSIT                              ||" << std::endl;
        std::cout << "\t\t\t\t||____________________________________________||" << std::endl;
        std::cout << "\t\t\t\t||   [4] FUND TRANSFER                        ||" << std::endl;
        std::cout << "\t\t\t\t||____________________________________________||" << std::endl;
        std::cout << "\t\t\t\t||   [5] CHANGE PIN CODE                      ||" << std::endl;
        std::cout << "\t\t\t\t||____________________________________________||" << std::endl;
        std::cout << "\t\t\t\t||   [6] LOG OUT                              ||" << std::endl;
        std::cout << "\t\t\t\t||____________________________________________||" << std::endl;
        std::cout << "\t\t\t\tEnter choice: ";
        std::cin >> choice;

        switch(choice){
            case 1:
                balance_inquiry();
                break;
            case 2:
                system("cls");
                std::cout << "\t\t\t\t++============================================++" << std::endl;
                std::cout << "\t\t\t\t||         <<<< WITHDRAW MENU >>>>            ||" << std::endl;
                std::cout << "\t\t\t\t++============================================++" << std::endl;
                preview_balance();
                std::cout << "\t\t\t\t  ENTER AMOUNT TO DEPOSIT: ";
                std::cin >> amount;
                withdraw_and_deposit(amount, 1);
                break;
            case 3:
                system("cls");
                std::cout << "\t\t\t\t++============================================++" << std::endl;
                std::cout << "\t\t\t\t||          <<<< DEPOSIT MENU >>>>            ||" << std::endl;
                std::cout << "\t\t\t\t++============================================++" << std::endl;
                preview_balance();
                std::cout << "\t\t\t\t  ENTER AMOUNT TO DEPOSIT: ";
                std::cin >> amount;
                withdraw_and_deposit(amount, 2);
                break;
            case 4:
                fund_transfer_menu();
                break;
            case 5:
                check_pin();
                break;
            case 6:
                main();
                break;
            default:
                std::cout << "Invalid Choice. Try Again" << std::endl;
        }
    }while(choice!=7);

}

void Account::preview_balance(){
        for(int i = 0; i < count; i++){
        if(account.acc_number == accountData[i].acc_number){
            std::cout << "\t\t\t\t|=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+|" << std::endl;
            std::cout << "\t\t\t\t||            << PREVIEW BALANCE  >>           ||" << std::endl;
            std::cout << "\t\t\t\t+=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+=" << std::endl;
            std::cout << "\t\t\t\t|| ACCOUNT NUMBER: "<< std::left  << std::setw(25)<< accountData[i].acc_number << "   ||" << std::endl;
            std::cout << "\t\t\t\t||_____________________________________________||" << std::endl;
            std::cout << "\t\t\t\t|| ACCOUNT BALANCE: $"<< std::left  << std::setw(25)<< accountData[i].initial_deposit << " ||" << std::endl;
            std::cout << "\t\t\t\t+=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+=" << std::endl;
            break;
        }
    }
}

void Account::balance_inquiry(){
    system("cls");
    std::cout << "\t\t\t\t|=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+|" << std::endl;
    std::cout << "\t\t\t\t||         << BANK ACCOUNT DETAILS  >>         ||" << std::endl;
    std::cout << "\t\t\t\t||_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_||" << std::endl;
    for(int i = 0; i < count; i++){
        if(account.acc_number == accountData[i].acc_number){
            std::cout << "\t\t\t\t|| ACCOUNT NUMBER: "<< std::left  << std::setw(25)<< accountData[i].acc_number << "   ||" << std::endl;
            std::cout << "\t\t\t\t||_____________________________________________||" << std::endl;
            std::cout << "\t\t\t\t|| NAME: "<< std::left  << std::setw(30)<< accountData[i].name << "        ||" << std::endl;
            std::cout << "\t\t\t\t||_____________________________________________||" << std::endl;
            std::cout << "\t\t\t\t|| BIRTHDAY: "<< std::left  << std::setw(30)<< accountData[i].birthday << "    ||" << std::endl;
            std::cout << "\t\t\t\t||_____________________________________________||" << std::endl;
            std::cout << "\t\t\t\t|| CONTACT NUMBER: "<< std::left  << std::setw(25)<< accountData[i].contact_number << "   ||" << std::endl;
            std::cout << "\t\t\t\t||_____________________________________________||" << std::endl;
            std::cout << "\t\t\t\t|| ACCOUNT BALANCE: $"<< std::left  << std::setw(25)<< accountData[i].initial_deposit << " ||" << std::endl;
            std::cout << "\t\t\t\t||_____________________________________________||" << std::endl;
            std::cout << "\t\t\t\t|| PIN CODE: "<< std::left  << std::setw(30)<< accountData[i].pin << "    ||" << std::endl;
            std::cout << "\t\t\t\t+=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+=" << std::endl;
            break;
        }
    }
    system("pause");
}

void Account::withdraw_and_deposit(int amount, int option) {
    std::fstream fp;
    fp.open("AccountsData.txt", std::ios::in | std::ios::out);

    if (!fp) {
        std::cout << "File can't be open" << std::endl;
        system("pause");
    } else {

        std::ofstream tempFile("tempAccountsData.txt");

        if (option == 1) {
            for (int i = 0; i < count; i++) {
                if (account.acc_number == accountData[i].acc_number) {
                    int balance = accountData[i].initial_deposit - amount;
                    if (amount < 0) {
                        sleep(1);
                        std::cout << "\t\t\t\t||==============================================||" << std::endl;
                        std::cout << "\t\t\t\t||            <== INVALID AMOUNT ==>            ||" << std::endl;
                        std::cout << "\t\t\t\t==================================================" << std::endl;
                        system("pause");
                    } else if (amount > accountData[i].initial_deposit) {
                        sleep(1);
                        std::cout << "\t\t\t\t||==============================================||" << std::endl;
                        std::cout << "\t\t\t\t||         <== INSUFFICIENT BALANCE ==>         ||" << std::endl;
                        std::cout << "\t\t\t\t==================================================" << std::endl;
                        system("pause");
                    } else {
                        accountData[i].initial_deposit = balance;
                        sleep(1);
                        std::cout << "\t\t\t\t||==============================================||" << std::endl;
                        std::cout << "\t\t\t\t||         <== WITHDRAW SUCCESSFUL ==>          ||" << std::endl;
                        std::cout << "\t\t\t\t==================================================" << std::endl;
                        system("pause");
                    }
                }

                accountData[i].pin = encrypt(accountData[i].pin);

                tempFile << accountData[i].acc_number << std::endl; 
                tempFile << accountData[i].name << std::endl;
                tempFile << accountData[i].birthday << std::endl;
                tempFile << accountData[i].contact_number << std::endl;
                tempFile << accountData[i].initial_deposit << std::endl; 
                tempFile<< accountData[i].pin << std::endl;
            }
        } else if (option == 2) {
            for (int i = 0; i < count; i++) {
                if (account.acc_number == accountData[i].acc_number) {
                    int balance = accountData[i].initial_deposit + amount;
                    if (amount < 0) {
                        sleep(1);
                        std::cout << "\t\t\t\t||==============================================||" << std::endl;
                        std::cout << "\t\t\t\t||            <== INVALID AMOUNT ==>            ||" << std::endl;
                        std::cout << "\t\t\t\t==================================================" << std::endl;
                        system("pause");
                    } else {
                        accountData[i].initial_deposit = balance;
                        sleep(1);
                        std::cout << "\t\t\t\t||==============================================||" << std::endl;
                        std::cout << "\t\t\t\t||          <== DEPOSIT SUCCESSFUL ==>          ||" << std::endl;
                        std::cout << "\t\t\t\t==================================================" << std::endl;
                        system("pause");
                    }
                }

                accountData[i].pin = encrypt(accountData[i].pin);

                tempFile << accountData[i].acc_number << std::endl; 
                tempFile << accountData[i].name << std::endl;
                tempFile << accountData[i].birthday << std::endl;
                tempFile << accountData[i].contact_number << std::endl;
                tempFile << accountData[i].initial_deposit << std::endl; 
                tempFile<< accountData[i].pin << std::endl;
            }
        }

        tempFile.close();
        fp.close();

        std::remove("AccountsData.txt");
        std::rename("tempAccountsData.txt", "AccountsData.txt");
        
    }
}

void Account::fund_transfer_menu(){
    int account_number;
    int amount;
    int pos = -1;
    system("cls");
    std::cout << "\t\t\t\t++==================================================++" << std::endl;
    std::cout << "\t\t\t\t||          <<<< FUND TRANSFER MENU >>>>            ||" << std::endl;
    std::cout << "\t\t\t\t++==================================================++" << std::endl;
    std::cout << "\t\t\t\t||       NOTE: ENTER ONLY THE AMOUNT YOU HAVE       ||" << std::endl;
    std::cout << "\t\t\t\t++==================================================++" << std::endl;
    std::cout << "\t\t\t\t  ENTER THE ACCOUNT NUMBER TO TRANSFER: ";
    std::cin >> account_number;
    std::cout << "\t\t\t\t||==================================================||" << std::endl;
    
    for(int i = 0; i < count; i++){
        if(account_number == accountData[i].acc_number){
            pos = i;
            break;
        }
    }

    if(account.acc_number == accountData[pos].acc_number){
        sleep(1);
        std::cout << "\t\t\t\t      YOU CAN'T TRANSFER TO YOUR OWN ACCOUNT" << std::endl;
        std::cout << "\t\t\t\t||==================================================||" << std::endl;
        system("pause");
    }
    else if(pos != -1 and account_number == accountData[pos].acc_number){
        std::cout << "\t\t\t\t  ENTER THE AMOUNT TO TRANSFER: ";
        std::cin >> amount;
        std::cout << "\t\t\t\t||==================================================||" << std::endl;
        transfer_fund(amount, pos);
    }
    else{
        sleep(1);
        std::cout << "\t\t\t\t              ACCOUNT DOES NOT EXIST" << std::endl;
        std::cout << "\t\t\t\t||==================================================||" << std::endl;
        system("pause");
    }
}

void Account::transfer_fund(int amount, int pos){
    int tempPosx;
    std::fstream fp;
    fp.open("AccountsData.txt", std::ios::in | std::ios::out);

    if(!fp){
        std::cout << "File Can't be open" << std::endl;
        system("pause");
        return;
    }
    for(int i = 0; i < count; i++){
        if(account.acc_number == accountData[i].acc_number){
            tempPosx = i;
        }
    }
    if(amount < 0 || amount > accountData[tempPosx].initial_deposit){
        std::cout << std::endl;
        sleep(1);
        std::cout << "\t\t\t\t||==================================================||" << std::endl;
        std::cout << "\t\t\t\t||    INSUFFICIENT OR INVALID BALANCE. TRY AGAIN    ||" << std::endl;
        std::cout << "\t\t\t\t||==================================================||" << std::endl;
        system("pause");
        return;  // Return early if insufficient balance
    }
    else{

        std::ofstream tempFile("tempAccountsData.txt");

        accountData[tempPosx].initial_deposit -= amount;
        accountData[pos].initial_deposit += amount;

        for (int i = 0; i < count; i++) {

                accountData[i].pin = encrypt(accountData[i].pin);

                tempFile << accountData[i].acc_number << std::endl; 
                tempFile << accountData[i].name << std::endl;
                tempFile << accountData[i].birthday << std::endl;
                tempFile << accountData[i].contact_number << std::endl;
                tempFile << accountData[i].initial_deposit << std::endl; 
                tempFile << accountData[i].pin << std::endl;
        }

        tempFile.close();
        fp.close();
        std::cout << std::endl;
        sleep(1);
        std::cout << "\t\t\t\t||==================================================||" << std::endl;
        std::cout << "\t\t\t\t||      MONEY TRANSER COMPLETED SUCCESSFULLY!       ||" << std::endl;
        std::cout << "\t\t\t\t||==================================================||" << std::endl;
        system("pause");
    }

    std::remove("AccountsData.txt");
    std::rename("tempAccountsData.txt", "AccountsData.txt");
}

void Account::check_pin(){
    int password;
    int pos;

    system("cls");
    std::cout << "\t\t\t\t|=+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+|" << std::endl;
    std::cout << "\t\t\t\t||         << CHANGE PIN CODE MENU  >>         ||" << std::endl;
    std::cout << "\t\t\t\t||_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_||" << std::endl;
    std::cout << "\t\t\t\t||       NOTE: PIN CODE MUST BE 6 DIGITS       ||" << std::endl;
    std::cout << "\t\t\t\t||---------------------------------------------||" << std::endl;
    do{
        std::cout << "\t\t\t\t    ENTER ACCOUNT PIN CODE: ";
        std::cin >> password;


        for(int i = 0; i < count; i++){
            if(account.acc_number == accountData[i].acc_number){
                pos = i;
                break;
            }
        }

        if(password == accountData[pos].pin){
            std::cout << "\t\t\t\t==______________________________________________==" << std::endl;
            change_pin();
            break;
        }
        else{
            std::cout << "\t\t\t\t==______________________________________________==" << std::endl;
            std::cout << "\t\t\t\t          PIN CODE INVALID. TRY AGAIN " << std::endl;
            std::cout << "\t\t\t\t==______________________________________________==" << std::endl;
        }
    }while(password != accountData[pos].pin);

}

void Account::change_pin(){
    int new_password;
    int confirm_new_password;

    // do{
        std::cout << "\t\t\t\t    ENTER NEW PIN CODE: ";
        std::cin >> new_password;
        std::cout << "\t\t\t\t==______________________________________________==" << std::endl;
        std::cout << "\t\t\t\t    CONFIRM NEW PIN CODE: ";
        std::cin >> confirm_new_password;
        std::cout << "\t\t\t\t==______________________________________________==" << std::endl;

        if(new_password == confirm_new_password){
            std::fstream fp("AccountsData.txt", std::ios::in|std::ios::out|std::ios::app);
            std::fstream flashdrivefp("D:\\\\Account.txt", std::ios::in | std::ios::out);

            if(!fp || !flashdrivefp){
                std::cout << "File can't be open" << std::endl;
                system("pause");
            }
            else{
                std::ofstream tempFile("tempAccountsData.txt");
                std::ofstream tempFile2("D:\\\\tempAccount.txt");
                for(int i = 0; i < count; i++){
                    if(account.acc_number == accountData[i].acc_number){
                        accountData[i].pin = new_password;
                    }
                        tempFile << accountData[i].acc_number << std::endl;
                        tempFile << accountData[i].name << std::endl;
                        tempFile << accountData[i].birthday << std::endl;
                        tempFile << accountData[i].contact_number << std::endl;
                        tempFile << accountData[i].initial_deposit << std::endl; 
                        tempFile << accountData[i].pin << std::endl;
                        
                }

                account.pin = confirm_new_password;
                tempFile2 << account.acc_number << std::endl; 
                tempFile2 << account.pin << std::endl;

                tempFile.close();
                tempFile2.close();
                fp.close();
                flashdrivefp.close();

                std::remove("AccountsData.txt");
                std::rename("tempAccountsData.txt", "AccountsData.txt");

                std::remove("D:\\\\Account.txt");
                std::rename("D:\\\\tempAccount.txt", "D:\\\\Account.txt");
                std::remove("D:\\\\tempAccount.txt");

                save_account_exit();
            }
            
            std::cout << std::endl;
            sleep(1);
            std::cout << "\t\t\t\t||==============================================||" << std::endl;
            std::cout << "\t\t\t\t||  <== NEW PIN CODE SUCCESFULLY CHANGED! ==>   ||" << std::endl;
            std::cout << "\t\t\t\t==================================================" << std::endl;
            system("pause");
        }
        else{
            sleep(1);
            std::cout << "\t\t\t\t       PIN CODE DOES NOT MATCH. TRY AGAIN " << std::endl;
            std::cout << "\t\t\t\t==______________________________________________==" << std::endl;
            system("pause");
        }
    // }while(new_password != confirm_new_password);
}

// TEST FUNCTIONS
void Account::display(){
    
    for(int i = 0; i < count; i++){
        std::cout << "Bank Account Number: " << accountData[i].acc_number << std::endl;
        std::cout << "Account Holder Name: " << accountData[i].name << std::endl;
        std::cout << "Account Birthday: " << accountData[i].birthday << std::endl;
        std::cout << "Account Contact Number: " << accountData[i].contact_number << std::endl;
        std::cout << "Account Balance: " << accountData[i].initial_deposit << "$" << std::endl;
        std::cout << "Pin Code: " << accountData[i].pin << std::endl;
        std::cout << std::endl;
    }
    system("pause");
}
