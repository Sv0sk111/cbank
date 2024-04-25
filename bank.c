//Copyright (c) 2024 Sv0sk111

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 256
bool write_credentials(char user_name[16], char user_pass[16], int *amount);
bool verify_sign_in(char user_name[16], char user_pass[16], int *amount);
int loan(char *user_name, int *amount, int *user_loan);
bool sign(char user_name[16], char user_pass[16]);
int withdraw(char *user_name, int *amount);
int deposit(char *user_name, int *amount);
bool verify_sign_up(char user_name[16]);
int bank(char *user_name, int *amount);
bool delete_account(char *user_name);
int scan_loan(char *user_name);
bool draw_ascii();
bool databases();

int main()
{
    char user_name[16];
    char user_pass[16];
    int amount = 0;
    int user_loan;
    bool exit_sign = false;
    bool exit_bank = false;
    int mode;
    int needed_loan;

    databases();

    printf("\033[1;36m"); 
    printf("Welcome to Cbank\n"); 
    draw_ascii();
    printf("\033[1;36m");
    printf("Made by Sv0sk111\n");
    printf("\033[0m");

    while (!exit_sign)
    {
        bool verify = false;
        printf("\033[1;33m"); 
        printf("Choose an option:\n");
        printf("1. Sign-in\n");
        printf("2. Sign-up\n");
        printf("3. Exit\n");
        printf("\033[0m"); 
        printf("Enter your choice: ");
        scanf("%d", &mode);

        switch (mode)
        {
        case 1:
            while (!verify)
            {
                verify = sign(user_name, user_pass);
            }
            if (verify_sign_in(user_name, user_pass, &amount))
            {
                printf("\033[1;32m");
                printf("Successfully signed in!\n");
                needed_loan = scan_loan(user_name);
                if (needed_loan != -1)
                {
                    printf("You haven't paid a loan of %d$\n", needed_loan);
                }
                printf("\033[0m"); 
                exit_sign = true;
                break;
            }
            else
            {
                printf("\033[1;31m"); 
                printf("Username or password is invalid!\n");
                printf("If you don't have an account try creating one!\n");
                printf("\033[0m"); 
            }
            break;
        case 2:
            while (!verify)
            {
                verify = sign(user_name, user_pass);
            }
            if (verify_sign_up(user_name))
            {
                printf("\033[1;31m"); 
                printf("Username already exists!\n");
                printf("\033[0m"); 
            }
            else
            {
                printf("\033[1;32m"); 
                printf("Username or password is valid!\n");
                printf("Saving credentials...\n");
                if (write_credentials(user_name, user_pass, &amount))
                {
                    printf("Credentials were saved successfully!\n");
                    printf("\033[0m"); 
                    exit_sign = true;
                    break;
                }
                else
                {
                    printf("\033[1;31m"); 
                    printf("An error occurred!\n");
                    printf("\033[0m"); 
                }
            }
            break;
        case 3:
            exit_sign = true;
            printf("\033[1;36m"); 
            printf("Exiting...\n");
            printf("\033[0m");
            return 0;
            break;
        default:
            printf("\033[1;31m");
            printf("Invalid choice!\n");
            printf("\033[0m"); 
            break;
        }
    }

    while (!exit_bank)
    {
        printf("\033[1;33m"); 
        printf("Account username: %s\n", user_name);
        printf("Amount: %d\n", amount);
        printf("Choices:(-1=exit) \n1. Withdraw \n2. Deposit \n3. Loan \n4. Delete your account\n");
        printf("\033[0m"); 
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case -1:
            exit_bank = true;
            printf("\033[1;36m"); 
            printf("Exiting...\n");
            printf("\033[0m"); 
            return 0;
            break;
        case 1:
            withdraw(user_name, &amount);
            break;
        case 2:
            deposit(user_name, &amount);
            break;
        case 3:
            loan(user_name, &amount, &user_loan);
            break;
        case 4:
            if(delete_account(user_name) == false)
            {
                printf("\033[1;36m"); 
                printf("Exiting...\n");
                printf("\033[0m");
                exit_bank = true;
            }
            break;
        default:
            printf("\033[1;31m"); 
            printf("Invalid choice!\n");
            printf("\033[0m");
            break;
        }
    }

    return 0;
}

bool draw_ascii() 
{
    printf("\033[1;32m");
    printf(" ▄████▄   ▄▄▄▄    ▄▄▄       ███▄    █  ██ ▄█▀\n");
    printf("▒██▀ ▀█  ▓█████▄ ▒████▄     ██ ▀█   █  ██▄█▒ \n");
    printf("▒▓█    ▄ ▒██▒ ▄██▒██  ▀█▄  ▓██  ▀█ ██▒▓███▄░ \n");
    printf("▒▓▓▄ ▄██▒▒██░█▀  ░██▄▄▄▄██ ▓██▒  ▐▌██▒▓██ █▄ \n");
    printf("▒ ▓███▀ ░░▓█  ▀█▓ ▓█   ▓██▒▒██░   ▓██░▒██▒ █▄\n");
    printf("░ ░▒ ▒  ░░▒▓███▀▒ ▒▒   ▓▒█░░ ▒░   ▒ ▒ ▒ ▒▒ ▓▒\n");
    printf("  ░  ▒   ▒░▒   ░   ▒   ▒▒ ░░ ░░   ░ ▒░░ ░▒ ▒░\n");
    printf("░         ░    ░   ░   ▒      ░   ░ ░ ░ ░░ ░ \n");
    printf("░ ░       ░            ░  ░         ░ ░  ░   \n");
    printf("░              ░                             \n");
    printf("\033[0m"); 
    return true;
}

bool write_credentials(char user_name[16], char user_pass[16], int *amount)
{
    FILE *file = fopen("database.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return false;
    }
    fprintf(file, "%s %d\n", user_name, *amount);
    fprintf(file, "%s\n", user_pass);

    fclose(file);
    return true;
}

bool sign(char user_name[16], char user_pass[16])
{
    printf("Sign here!\n");
    printf("Enter your username: ");
    scanf("%s", user_name);
    printf("Enter your password: ");
    scanf("%s", user_pass);

    if (user_name[0] == '\0' || user_pass[0] == '\0' || user_name[0] == ' ' || user_pass[0] == ' ')
    {
        printf("You cannot leave the username or password empty!\n");
        return false;
    }
    else
    {
        return true;
    }
}

bool verify_sign_up(char user_name[16])
{
    FILE *file = fopen("database.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return false;
    }

    char buffer[256];
    int line_count = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        char current_username[16];
        if (line_count % 2 == 0)
        {
            sscanf(buffer, "%15s", current_username);
            if (strcmp(current_username, user_name) == 0)
            {
                fclose(file);
                return true;
            }
        }
        line_count++;
    }

    fclose(file);
    return false;
}

bool verify_sign_in(char user_name[16], char user_pass[16], int *amount)
{
    FILE *file = fopen("database.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return false;
    }

    char current_username[16];
    int current_amount;
    char current_pass[16];
    while (fscanf(file, "%15s %d %15s", current_username, &current_amount, current_pass) == 3)
    {
        if (strcmp(current_username, user_name) == 0 && strcmp(current_pass, user_pass) == 0)
        {
            *amount = current_amount;
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

bool databases()
{
    FILE *file1 = fopen("database.txt", "r");
    FILE *file2 = fopen("loan_database.txt", "r");
    if (!file1)
    {
        printf("Credential database doesn't exist!\n");
        printf("Creating new!\n");
        file1 = fopen("database.txt", "w");
        if (file1 == NULL)
        {
            printf("Error opening database!\n");
            return false;
        }
    }
    else
    {
        fclose(file1);
    }
    if (!file2)
    {
        printf("Loan database doesn't exist!\n");
        printf("Creating new!\n");
        file2 = fopen("loan_database.txt", "w");
        if (file2 == NULL)
        {
            printf("Error opening database!\n");
            return false;
        }
    }
    else
    {
        fclose(file2);
    }
    return true;
}

int withdraw(char *user_name, int *amount)
{
    int amount_choice;
    printf("Account: %s\n", user_name);
    printf("Amount: %d\n", *amount);
    printf("Enter the amount you want to withdraw(-1=exit): ");
    scanf("%d", &amount_choice);
    if (amount_choice == -1)
    {
        return 0;
    }
    else if (amount_choice > *amount)
    {
        printf("This amount is invalid!\n");
        return *amount;
    }
    else if (amount_choice <= 0)
    {
        printf("This amount is invalid!\n");
        return *amount;
    }
    printf("Great! You withdrew %d from your account\n", amount_choice);
    *amount -= amount_choice;
    FILE *file = fopen("database.txt", "r+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return -1;
    }
    char temp_name[16];
    int temp_amount;
    bool user_found = false;
    while (fscanf(file, "%15s %d", temp_name, &temp_amount) == 2)
    {
        if (strcmp(temp_name, user_name) == 0)
        {
            temp_amount -= amount_choice;
            fseek(file, -((int)strlen(temp_name) + sizeof(int)), SEEK_CUR);
            fprintf(file, "%s %d", temp_name, temp_amount);
            user_found = true;
            break;
        }
    }
    fclose(file);
    if (!user_found)
    {
        printf("User not found in the database.\n");
        return -1;
    }
    return *amount;
}

int deposit(char *user_name, int *amount)
{
    int amount_choice;
    printf("Account: %s\n", user_name);
    printf("Amount: %d\n", *amount);
    printf("Enter the amount you want to deposit(-1=exit): ");
    scanf("%d", &amount_choice);
    if (amount_choice == -1)
    {
        return 0;
    }
    printf("Great! You deposited %d to your account\n", amount_choice);
    *amount += amount_choice;
    FILE *file = fopen("database.txt", "r+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return -1;
    }
    char temp_name[16];
    int temp_amount;
    bool user_found = false;
    while (fscanf(file, "%15s %d", temp_name, &temp_amount) == 2)
    {
        if (strcmp(temp_name, user_name) == 0)
        {
            temp_amount += amount_choice;
            fseek(file, -((int)strlen(temp_name) + sizeof(int)), SEEK_CUR);
            fprintf(file, "%s %d", temp_name, temp_amount);
            user_found = true;
            break;
        }
    }
    fclose(file);
    if (!user_found)
    {
        printf("User not found in the database.\n");
        return -1;
    }
    return *amount;
}

int loan(char *user_name, int *amount, int *user_loan)
{
    int loan_amount;
    char temp_name[16];
    int temp_loan;
    bool user_found = false;
    printf("Enter the amount of loan you want to request(-1=exit)(1.6 interest): ");
    scanf("%d", &loan_amount);
    if (loan_amount == -1)
    {
        return 0;
    }
    int loan_with_interest = loan_amount * 1.6;
    printf("The loan with interest is %d$\n", loan_with_interest);
    FILE *file = fopen("loan_database.txt", "r+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }

    while (fscanf(file, "%15s %d", temp_name, &temp_loan) == 2)
    {
        if (strcmp(temp_name, user_name) == 0)
        {
            temp_loan += loan_with_interest;
            fseek(file, -((int)strlen(temp_name) + sizeof(int)), SEEK_CUR);
            fprintf(file, "%s %d", temp_name, temp_loan);
            user_found = true;
            break;
        }
    }

    if (!user_found)
    {
        fseek(file, 0, SEEK_END);
        fprintf(file, "%s %d\n", user_name, loan_with_interest);
    }

    fclose(file);

    *user_loan = loan_with_interest;
    *amount += loan_amount;
    FILE *file2 = fopen("database.txt", "r+");
    if (file2 == NULL)
    {
        printf("Error opening file.\n");
        return -1;
    }
    int temp_amount;
    while (fscanf(file, "%15s %d", temp_name, &temp_amount) == 2)
    {
        if (strcmp(temp_name, user_name) == 0)
        {
            temp_amount += loan_amount;
            fseek(file, -((int)strlen(temp_name) + sizeof(int)), SEEK_CUR);
            fprintf(file, "%s %d", temp_name, temp_amount);
            user_found = true;
            break;
        }
    }
    fclose(file);
    if (!user_found)
    {
        printf("User not found in the database.\n");
        return -1;
    }

    return *amount;
}

int scan_loan(char *user_name)
{
    FILE *file = fopen("loan_database.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return -1;
    }

    char temp_name[16];
    int temp_loan;
    int user_loan = -1;

    while (fscanf(file, "%15s %d", temp_name, &temp_loan) == 2)
    {
        if (strcmp(temp_name, user_name) == 0)
        {
            user_loan = temp_loan;
            break;
        }
    }

    fclose(file);
    return user_loan;
}

bool delete_account(char *user_name) 
{
    FILE* file = fopen("database.txt", "r");
    if (file == NULL) 
    {
        printf("Error opening file.\n");
        return false;
    }

    FILE* temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) 
    {
        printf("Error creating temporary file.\n");
        fclose(file);
        return false;
    }

    char buffer[256];
    int line_count = 0;
    bool account_found = false;

    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        char current_username[16];
        if (line_count % 2 == 0) 
        {
            sscanf(buffer, "%15s", current_username);
            if (strcmp(current_username, user_name) == 0) 
            {
                fgets(buffer, sizeof(buffer), file); 
                account_found = true;
                continue;
            }
        }
        fprintf(temp_file, "%s", buffer);
        line_count++;
    }

    fclose(file);
    fclose(temp_file);

    if (remove("database.txt") != 0) 
    {
        printf("Error deleting original file.\n");
        return false;
    }
    
    if (rename("temp.txt", "database.txt") != 0)
    {
        printf("Error renaming temporary file.\n");
        return false;
    }

    if (account_found)
    {
        printf("Account '%s' deleted successfully.\n", user_name);
        printf("Account closed!\n");
        return false;
    }
    else 
    {
        printf("Account '%s' not found.\n", user_name);
        return false;
    }
}


