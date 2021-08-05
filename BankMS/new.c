/*
 * ######################## CLASSICAL BANK ACCOUNT MANAGEMENT SYSTEM'S PROGRAM ########################
 *
 * MADE BY :- PRIYANSHU GUPTA ON 5 AUGUST 2021.
 * 
 * NOTE :- ACCOUNT NUMBER ACTS AS PASSWORD IN THIS PROGRAM. KEEP THE INFORMATION ABOUT ACCOUNT NUMBER SECRET.
 * 
 * LICENCE :-
 *          THIS IS TO INFORM ALL THE READERS WHO IS READING THIS CODE THAT
 *          (1) THIS CODE IS JUST FOR COURSE-WORK PURPOSE ONLY. IT IS NOT MADE FOR COMMERCIAL PURPOSES.
 *          (2) I, PRIYANSHU GUPTA, HEREBY DECLARE THAT NO-ONE IS ALLOWED TO MANIPULATE OR COPY THIS CODE.
 *          (3) I, PRIYANSHU GUPTA, DOESN'T CARRY ANY CERTAINITY FOR THE FACT THAT THIS CODE WILL WORK IN ALL SYSTEMS.
 *          (4) I, PRIYANSHU GUPTA, DOESN'T CARRY ANY CERTAINITY FOR TYPO ERROR IN THIS PROGRAM.
 *
 * FEATURES OF THE PROGRAM :-
 *                          (1) CLASSICAL, CONSOLE BASED PROGRAM.
 *                          (2) USER WILL HAVE TO ENTER NUMBERS EVERYTIME TO PROCEED AND IMPLEMENT TRANSACTIONS.
 *                          (3) PROGRAM HAS BULIT-IN DATA VALIDATION FEATURE AT ALL STAGE.
 *                          (4) EVERY POSSIBLE ATTEMPT HAS BEEN INCURRED TO MAKE THIS PROGRAM SECURE.
 * 
 * TASKS THAT CAN BE IMPLEMENTED BY THIS PROGRAM ARE AS FOLLOWS :-
 *                                         (1) CREATE ACCOUNT OF THE USER AND SAFELY SAVE THE DATA ABOUT IT.
 *                                         (2) UPDATE THE INFORMATION OF THE USER BY ENTERING ACCOUNT NUMBER,
 *                                              AND SAFELY SAVE THE UPDATED INFORMATION.
 *                                         (3) ABLE TO MAKE TRANSACTIONS LIKE DEPOSITING MONEY,
 *                                              WITHDRAWING MONEY, PAYING CHEQUEE, CHECK BANK ACCOUNT BALANCE,
 *                                              PRINTING PASSBOOK.
 *                                         (4) CHECK BANK ACCOUNT INFORMATION BY ENTERING ACCOUNT NUMBER.
 *                                         (5) REMOVE/DELETE THE ACCOUNT BY CONFIRMATION MADE BY THE USER.
 *                                         (6) EXIT FROM THE PROGRAM EASILY.
 * END OF THE LICENCE TEXT.
 * HAPPY CODING!
 *  ########################         ########################         ########################
 */
// Including Some Standard Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//const values
#define MICR_CODE 12345098756 //a default number as usually mentioned in our passbook
#define IFSC_CODE 90875634212 //again a default number mentioned in our passbook
#define ADD_SIZE 21           //length of locality string
#define ENTRIES_LENGTH 172    //length of each entry in accounts file
#define BALANCE_LENGTH 78     //length of each entry in balance file
//some const string to make code minimal
const char IDMENTION[] = "\n\nYour generated Account No. is : %d\n Please remember It!\n\n";
const char OPTIONS[] = "Tasks that can be operated by this program are :\n 1. Create New Account.\n 2. Update Information of Existing Account.\n 3. For transactions.\n 4. Removing Existing Account.\n 5. Check details for existing Account.\n 6. Exit.\n\n   Enter your Choice : ";
const char OPTIONS2[] = "\nTasks that can be operated by this program for transaction are :\n 1. Deposited Money to the account.\n 2. WithDrawing Money from the Account.\n 3. Paying chequee.\n 4. Checking Bank Account Balance.\n 5. Print Passbook.\n 6. Return to the Main Menu\n\n Enter Your Choice : ";
const char DETAILS[] = "Your details :\n Name : %s %s \n DOB : %d/%d/%d \n Locality : %s \n Aadhar No. : %lld \n Mob. No. : %lld";
const char ACDETAILS[] = "MICR : %lld\tIFSC : %lld\tACC_NO : %d\tName : %s %s\tLocality : %s\tDOB : %d/%d/%d\tAadhar No. : %lld\tMob. No. : %lld\n";
//  SOME STRUCTs/OBJECTs
typedef struct Time
{
    int dd, //day month year
        mm,
        yyyy;
} TIME;
struct Person
{
    int id;   //symbol of uniqueness
    TIME dob; //dob means date of birth
    char fname[11], lname[11], locality[ADD_SIZE];
    long long AadhaarNo, mobno; //identity proof
};
int lengthOfNumber(long long int num)
{
    int l = 1;
    while (num > 10)
    {
        num /= 10;
        l++;
    }
    return l;
}
int NameValidation(char str[11])
{
    int correct = 0, i;
    char c;
    for (i = 0; str[i] != '\0'; i++)
    {
        c = str[i];
        if (!isalpha(c))
            correct = 1;
    }
    return correct;
}
int ValidatePerson(struct Person per)
{
    //1 means incorrect 0 means correct
    if ((lengthOfNumber(per.AadhaarNo) == 12) && (lengthOfNumber(per.mobno) == 10) && (per.dob.dd < 32) && (per.dob.mm < 13) && (per.dob.yyyy > 1950) && (per.dob.yyyy < 2022) && (NameValidation(per.fname) == 0) && (NameValidation(per.lname) == 0))
        return 0;
    else
        return 1;
}
struct Person getData()
{
    struct Person repr; //repr means representative
    printf(" Enter Full name : ");
    scanf("%s %s", &repr.fname, &repr.lname);
    printf("  Enter Date of Birth DD MM YYYY : ");
    scanf("%d %d %d", &repr.dob.dd, &repr.dob.mm, &repr.dob.yyyy);
    printf("  Enter Your locality name : ");
    scanf("%s", &repr.locality);
    printf("  Enter AadharNo : ");
    scanf("%lld", &repr.AadhaarNo);
    printf("  Enter Mob no. : ");
    scanf("%lld", &repr.mobno);
    int l = 0;
    long long t = repr.mobno;
    while (t > 10)
    {
        t /= 10;
        l++;
    }
    repr.id = (repr.dob.dd * 300) + (repr.dob.mm * 30) + (repr.dob.yyyy) + l;
    printf(IDMENTION, repr.id);
    return repr;
}
//Declarations
void CreateNewAc(), UpdateInfo(), DisplayAcDetails(), displayEntryScreen(), PrintPassbook(int ans), UpdateAc(int rec, int pay, long long int amt), Submission(struct Person ptr), deleteAc(int ans), Transaction(), depositMoney(int ans), WithDrawMoney(int ans), PayChequee(int ans), RemoveAc(), ProceedForUpdate(struct Person argv, int ans);
long long int checkAcBalance(int ans);
void DisplayDetails(char str[ENTRIES_LENGTH + 1])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\t')
            printf("\n   ");
        else
            printf("%c", str[i]);
    }
}

//  FUNCTION DEFINITIONS
//main function
void main()
{
    printf("-------------------\tWelcome To Customer Bank Account Management System\t-------------------\n Note:FirstName and LastName should contain atmax 10 characters.\n  AadharNumber and Mobno. should contain 12 and 10 digits respectively.\n  DOb should be separated by spaces only.\n\nPlease Adhere to all instructuons.\n");
    displayEntryScreen();
}
void displayEntryScreen()
{
    int choice;
    printf(OPTIONS);
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        CreateNewAc();
        break;
    case 2:
        UpdateInfo();
        break;
    case 3:
        Transaction();
        break;
    case 4:
        RemoveAc();
        break;
    case 5:
        DisplayAcDetails();
        break;
    case 6:
        exit(1); //no function related to choice 6
    default:
        break;
    }
}

//functions related to choice 1
void CreateNewAc()
{
    printf("Enter Details:\n ");
    char warn[1];
    struct Person temp;
    temp = getData(); //name dob locality aadharno mobno
    printf(DETAILS, temp.fname, temp.lname, temp.dob.dd, temp.dob.mm, temp.dob.yyyy, temp.locality, temp.AadhaarNo, temp.mobno);
    printf("\n  Enter Y to confirm : ");
    scanf("%s", &warn);
    if (warn[0] == 'Y')
        Submission(temp);
    else
    {
        printf("Re-Enter your details :\n ");
        temp = getData(); //name dob locality aadharno mobno
        printf(DETAILS, temp.fname, temp.lname, temp.dob.dd, temp.dob.mm, temp.dob.yyyy, temp.locality, temp.AadhaarNo, temp.mobno);
        printf("\n  Enter Y to confirm : ");
        scanf("%s", &warn);
        if (warn[0] == 'Y')
            Submission(temp);
        else
        {
            printf("Exiting.....\n");
            displayEntryScreen();
        }
    }
}
void Submission(struct Person ptr)
{
    FILE *fptr = fopen("acdetails.txt", "a+"), *balance = fopen("balance.txt", "a+");
    if (fptr == NULL | balance == NULL)
    {
        printf("\nError While getting file...!\n");
        exit(1);
    }
    if (ValidatePerson(ptr) == 0)
    {
        fprintf(fptr, "MICR : %lld\tIFSC : %lld\tACC_NO : %d\tName : %s %s\tLocality : %s\tDOB : %d/%d/%d\tAadhar No. : %lld\tMob. No. : %lld\n", MICR_CODE, IFSC_CODE, ptr.id, ptr.fname, ptr.lname, ptr.locality, ptr.dob.dd, ptr.dob.mm, ptr.dob.yyyy, ptr.AadhaarNo, ptr.mobno);
        printf("\n\nData stored Successfully...!\n\n");
        fprintf(balance, "ACC_NO : %d\tTimeStamp : %s,%s\tBALANCE : 0\n", ptr.id, __DATE__, __TIME__);
    }
    else
        printf("\nInvalid data...\n");
    fclose(fptr);
    fclose(balance);
    displayEntryScreen();
}

//functions related to choice 2
void UpdateInfo()
{
    char str[ENTRIES_LENGTH + 1], cropped[7], warn[1];
    int i, j, que;
    printf("\n Enter Account No. : ");
    scanf("%d", &que);
    FILE *dataptr = fopen("acdetails.txt", "r");
    if (dataptr == NULL)
    {
        printf("Error While getting file....");
        exit(1);
    }
    while (1)
    {
        if (feof(dataptr))
        {
            printf("\nOopss...\nAccount Not Found....\nExiting....\n");
            break;
        }
        else
        {
            fgets(str, ENTRIES_LENGTH, dataptr);
            for (i = 0; str[i] != 'A'; i++)
                ;
            for (i += 8, j = 0; str[i] != '\t'; i++, j++)
                cropped[j] = str[i];
            int ans = atoi(cropped);
            if (ans == que)
            { //after matching,  printing results
                printf("\nAccount Details...\n   ");
                DisplayDetails(str);
                printf("\n Do you want to want to change the details ?\nEnter Y to confirm : ");
                scanf("%s", &warn);
                if (warn[0] == 'Y')
                {
                    struct Person temp = getData();
                    printf(DETAILS, temp.fname, temp.lname, temp.dob.dd, temp.dob.mm, temp.dob.yyyy, temp.locality, temp.AadhaarNo, temp.mobno);
                    printf("\n  Enter Y to confirm : ");
                    scanf("%s", &warn);
                    if (warn[0] == 'Y')
                    {
                        if (ValidatePerson(temp) == 0)
                            ProceedForUpdate(temp, ans);
                        else
                            printf("\nInValid Data...\n");
                    }
                    else
                    {
                        printf("Re-Enter details : ");
                        temp = getData();
                        printf("Your details :\n Name : %s %s \n DOB : %d/%d/%d \n Locality : %s \n Aadhar No. : %lld \n Mob. No. : %lld",
                               temp.fname, temp.lname, temp.dob.dd, temp.dob.mm, temp.dob.yyyy, temp.locality, temp.AadhaarNo, temp.mobno);
                        printf("\n  Enter Y to confirm : ");
                        scanf("%s", &warn);
                        if (warn[0] == 'Y')
                        {
                            if (ValidatePerson(temp) == 0)
                                ProceedForUpdate(temp, ans);
                            else
                                printf("\nInvalid Data...\n");
                        }
                        else
                            printf("\nExiting....\n");
                    }
                }
                else
                    printf("\n Exiting...\n");
                break;
            }
        }
    }
    fclose(dataptr);
    displayEntryScreen();
}
void ProceedForUpdate(struct Person argv, int ans)
{
    FILE *fptr = fopen("acdetails.txt", "r"), *tempf = fopen("temp.txt", "w");
    if (fptr == NULL)
    {
        printf("\nError While getting file...\n");
        exit(1);
    }
    char str[ENTRIES_LENGTH + 1], cropped[7];
    int j, i, temp, copy = 0;
    while (1)
    { //printing entries temporarily
        if (feof(fptr))
            break;
        else
        {
            fgets(str, ENTRIES_LENGTH, fptr);
            for (i = 0; str[i] != 'A'; i++)
                ;
            for (i += 8, j = 0; str[i] != '\t'; i++, j++)
                cropped[j] = str[i];
            temp = atoi(cropped);
            if (copy != temp)
            {
                //update the records if account no is matched with user's account no.
                if (temp == ans)
                    fprintf(tempf, ACDETAILS, MICR_CODE, IFSC_CODE, argv.id, argv.fname, argv.lname, argv.locality, argv.dob.dd, argv.dob.mm, argv.dob.yyyy, argv.AadhaarNo, argv.mobno);
                else
                    fprintf(tempf, str);
                copy = temp;
            }
        }
    }
    fclose(fptr);
    fclose(tempf);
    //undoing this process above but with updated content
    FILE *again = fopen("acdetails.txt", "w"), *ftemp = fopen("temp.txt", "r");
    copy = 0;
    while (1)
    {
        if (feof(ftemp))
            break;
        fgets(str, ENTRIES_LENGTH, ftemp);
        for (i = 0; str[i] != 'A'; i++)
            ;
        for (i += 8, j = 0; str[i] != '\t'; i++, j++)
            cropped[j] = str[i];
        temp = atoi(cropped);
        if (copy != temp)
        {
            fprintf(again, str);
            copy = temp;
        }
    }
    fclose(ftemp);
    if (remove("temp.txt") != 0)
        printf("\nError while deleting temporary file\n");
    fclose(again);
    printf("\nData Updated Successfully...\n\n");
}

//function related to choice 3
void Transaction()
{
    int que, ans, i, j, choice;
    char str[ENTRIES_LENGTH + 1], cropped[7];
    printf("Enter Account No. : ");
    scanf("%d", &que);
    FILE *acdetails = fopen("acdetails.txt", "r");
    while (1)
    {
        if (feof(acdetails))
        {
            printf("\n\nOops...\nAccount Not Found...\nExiting...\n\n");
            break;
        }
        fgets(str, ENTRIES_LENGTH, acdetails);
        for (i = 0; str[i] != 'A'; i++)
            ;
        for (i += 8, j = 0; str[i] != '\t'; i++, j++)
            cropped[j] = str[i];
        ans = atoi(cropped);
        if (ans == que)
        {
            printf(OPTIONS2);
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                depositMoney(ans);
                break;
            case 2:
                WithDrawMoney(ans);
                break;
            case 3:
                PayChequee(ans);
                break;
            case 4:
                printf("\n\nYour Account contains INR %lld\n\n", checkAcBalance(ans));
                break;
            case 5:
                PrintPassbook(ans);
                break;
            default:
                break;
            }
            break;
        }
    }
    fclose(acdetails);
    displayEntryScreen();
}

//function related to choice 3->1
void depositMoney(int ans)
{
    char str[BALANCE_LENGTH + 1], cropped[7];
    int i, j, copy = 0, temp;
    long long int amt;
    FILE *depositfile = fopen("depositfile.txt", "a+"), *balance = fopen("balance.txt", "r"), *tempf = fopen("temp.txt", "w");
    if ((depositfile == NULL) | (balance == NULL))
        printf("Error while getting file...\n");
    printf("Enter Amt of the money : ");
    scanf("%lld", &amt);
    fprintf(depositfile, "ACC_NO : %d\tTimeStamp : %s,%s\tBALANCE : %lld\n", ans, __DATE__, __TIME__, amt); //time
    fclose(depositfile);
    //depositing done , now updating account balance
    while (1)
    {
        if (feof(balance))
            break;
        else
        {
            fgets(str, BALANCE_LENGTH, balance);
            for (i = 0; str[i] != ':'; i++)
                ;
            for (i += 2, j = 0; str[i] != '\t'; i++, j++)
                cropped[j] = str[i];
            temp = atoi(cropped);
            if (copy != temp)
            {
                if (temp == ans)
                    fprintf(tempf, "ACC_NO : %d\tTimeStamp : %s,%s\tBALANCE : %lld\n", ans, __DATE__, __TIME__, checkAcBalance(ans) + amt);
                else
                    fprintf(tempf, str);
                copy = temp;
            }
        }
    }
    fclose(tempf);
    fclose(balance);
    //undoing the process with updated content
    FILE *ftemp = fopen("temp.txt", "r"),
         *fbalance = fopen("balance.txt", "w");
    if (ftemp == NULL)
        printf("\nError While getting File...\n");
    copy = 0;
    while (1)
    {
        if (feof(ftemp))
            break;
        else
        {
            fgets(str, BALANCE_LENGTH, ftemp);
            for (i = 0; str[i] != ':'; i++)
                ;
            for (i += 2, j = 0; str[i] != '\t'; i++, j++)
                cropped[j] = str[i];
            temp = atoi(cropped);
            if (copy != temp)
            {
                fprintf(fbalance, str);
                copy = temp;
            }
        }
    }
    fclose(fbalance);
    fclose(ftemp);
    if (remove("temp.txt") != 0)
        printf("\nError while Deleting temp file\n");
    printf("\n\nMoney Deposited Successfully...\n\n");
}

//function related to choice 3->2
void WithDrawMoney(int ans)
{
    char str[BALANCE_LENGTH + 1], cropped[7];
    int i, j, copy = 0, temp;
    long long int amt;
    FILE *depositfile = fopen("depositfile.txt", "a+");
    if (depositfile == NULL)
        printf("Error while getting file...\n");
    printf("Enter Amt of the money you want to withdraw : ");
    scanf("%lld", &amt);
    if (checkAcBalance(ans) > amt)
    {
        fprintf(depositfile, "ACC_NO : %d\tTimeStamp : %s,%s\tBALANCE : -%lld\n", ans, __DATE__, __TIME__, amt); //time
        //withdraw done, updating ...
        FILE *balance = fopen("balance.txt", "r"),
             *tempf = fopen("temp.txt", "w");
        while (1)
        {
            if (feof(balance))
                break;
            else
            {
                fgets(str, BALANCE_LENGTH, balance);
                for (i = 0; str[i] != ':'; i++)
                    ;
                for (i += 2, j = 0; str[i] != '\t'; i++, j++)
                    cropped[j] = str[i];
                temp = atoi(cropped);
                if (copy != temp)
                {
                    if (temp == ans)
                        fprintf(tempf, "ACC_NO : %d\tTimeStamp : %s,%s\tBALANCE : %lld\n", ans, __DATE__, __TIME__, checkAcBalance(ans) - amt);
                    else
                        fprintf(tempf, str);
                    copy = temp;
                }
            }
        }
        fclose(tempf);
        fclose(balance);
        //undoing the process with updated content
        FILE *ftemp = fopen("temp.txt", "r"),
             *fbalance = fopen("balance.txt", "w");
        if (ftemp == NULL)
            printf("\nError While getting File...\n");
        copy = 0;
        while (1)
        {
            if (feof(ftemp))
                break;
            else
            {
                fgets(str, BALANCE_LENGTH, ftemp);
                for (i = 0; str[i] != ':'; i++)
                    ;
                for (i += 2, j = 0; str[i] != '\t'; i++, j++)
                    cropped[j] = str[i];
                temp = atoi(cropped);
                if (copy != temp)
                {
                    fprintf(fbalance, str);
                    copy = temp;
                }
            }
        }
        printf("\n\nCollect Your Money...\n\n");
        fclose(fbalance);
        fclose(ftemp);
        if (remove("temp.txt") != 0)
            printf("\nError while Deleting temp file\n");
    }
    else
        printf("\nYour Account Doesn't contain Enough Money...\n");
    fclose(depositfile);
}

//function related to choice 3->3
void PayChequee(int ans)
{
    int choice, someonea_c, check = 0, temp, i, j, copy = 0;
    long long int amt = 0;
    printf("What you want to do?\n 1. Depositing Money from Someone via Chequee\n 2. Paying Money to Someone via Chequee\n Enter Your Choice : ");
    scanf("%d", &choice);
    char str[ENTRIES_LENGTH + 1], cropped[7];
    FILE *ptr = fopen("chequee.txt", "a+"),
         *account = fopen("acdetails.txt", "r");
    printf("\nEnter another's account number : ");
    scanf("%d", &someonea_c);
    while (1)
    {
        if (feof(account))
            break;
        else
        {
            fgets(str, ENTRIES_LENGTH, account);
            for (i = 0; str[i] != 'A'; i++)
                ;
            for (i += 8, j = 0; str[i] != '\t'; i++, j++)
                cropped[j] = str[i];
            temp = atoi(cropped);
            if (temp != copy)
            {
                if (temp == ans)
                    check++;
                if (temp == someonea_c)
                    check++;
                copy = temp;
            }
        }
    }
    if (check == 2 && someonea_c != ans)
    {
        if (choice == 1)
        {
            printf("Enter amt of money you want to have via Chequee : ");
            scanf("%lld", &amt);
            if (checkAcBalance(someonea_c) > amt)
            {
                fprintf(ptr, "TYPE:HAVE\tREC_A_C : %d\tPAY_A_C : %d\tAMOUNT : %lld", ans, someonea_c, amt);
                UpdateAc(ans, someonea_c, amt);
            }
            else
                printf("\nPayer doesn't have enough money...\n");
        }
        else if (choice == 2)
        {
            printf("Enter amt of money you want to pay via Chequee : ");
            scanf("%lld", &amt);
            if (checkAcBalance(ans) > amt)
            {
                fprintf(ptr, "TYPE:PAY\tREC_A_C : %d\tPAY_A_C : %d\tAMOUNT : %lld", someonea_c, ans, amt);
                UpdateAc(someonea_c, ans, amt);
            }
            else
                printf("\nYou don't have enough money...\n");
        }
        else
            printf("Enter Number Correctly....\n");
    }
    else
        printf("\nEither Account Doesn't Exist Or Account Number of payer and receiver is same. \n");
    fclose(ptr);
    fclose(account);
}
void UpdateAc(int rec, int pay, long long int amt)
{
    FILE *balance = fopen("balance.txt", "r"), *tempf = fopen("temp.txt", "w");
    if (balance == NULL)
        printf("\nError While getting file...\n");
    char str[BALANCE_LENGTH + 1], copys[BALANCE_LENGTH] = "", cropped[7];
    int i, j, copy = 0, temp;
    while (1)
    {
        if (feof(balance))
            break;
        else
        {
            fgets(str, BALANCE_LENGTH, balance);
            for (i = 0; str[i] != ':'; i++)
                ;
            for (i += 2, j = 0; str[i] != '\t'; i++, j++)
                cropped[j] = str[i];
            temp = atoi(cropped);
            if (copy != temp)
            {
                if (temp == rec)
                    fprintf(tempf, "ACC_NO : %d\tTimeStamp : %s,%s\tBALANCE : %lld\n", rec, __DATE__, __TIME__, checkAcBalance(rec) + amt);
                if (temp == pay)
                    fprintf(tempf, "ACC_NO : %d\tTimeStamp : %s,%s\tBALANCE : %lld\n", pay, __DATE__, __TIME__, checkAcBalance(pay) - amt);
                copy = temp;
            }
        }
    }
    fclose(balance);
    fclose(tempf);
    //undoing the process with updated content
    FILE *fbalance = fopen("balance.txt", "w"), *ftemp = fopen("temp.txt", "r");
    copy = 0;
    if (ftemp == NULL)
        printf("\nError While getting file...\n");
    while (1)
    {
        if (feof(ftemp))
            break;
        else
        {
            fgets(str, BALANCE_LENGTH, ftemp);
            if (strcmp(copys, str) != 0)
            {
                fprintf(fbalance, str);
                strcpy(copys, str);
            }
        }
    }
    fclose(fbalance);
    fclose(ftemp);
    if (remove("temp.txt") != 0)
        printf("\nError while deleting file...\n");
    printf("\nPayment Succeeded...\n");
}

//function related to choice 3->4
long long int checkAcBalance(int ans)
{
    FILE *balance = fopen("balance.txt", "r");
    long long int amt = 0;
    char str[BALANCE_LENGTH + 1], cropped[7], amttxt[20];
    int i, j, temp;
    while (1)
    {
        if (feof(balance))
        {
            printf("\n\nOops...\nAccount Not Found..\nExiting...\n\n");
            break;
        }
        else
        {
            fgets(str, BALANCE_LENGTH, balance);
            for (i = 0; str[i] != ':'; i++)
                ;
            for (i += 2, j = 0; str[i] != '\t'; i++, j++)
                cropped[j] = str[i];
            temp = atoi(cropped);
            if (temp == ans)
            {
                for (i = 0; str[i] != 'B'; i++)
                    ;
                for (i += 10, j = 0; str[i] != '\n'; i++, j++)
                    amttxt[j] = str[i];
                amt = atoi(amttxt);
                break;
            }
        }
    }
    fclose(balance);
    return amt;
}

//function related to choice 3->5
void PrintPassbook(int ans)
{
    printf("-------------------------- Account Number : %d --------------------------\nNote: -ve Entries Reflect Withdrawal of Money\n", ans);
    FILE *ptr = fopen("depositfile.txt", "r");
    if (ptr == NULL)
        printf("\nError While getting the file...\n");
    char str[BALANCE_LENGTH + 1], copy[BALANCE_LENGTH + 1] = "", cropped[7], amttxt[20];
    int i, j, temp;
    while (1)
    {
        if (feof(ptr))
            break;
        else
        {
            fgets(str, BALANCE_LENGTH, ptr);
            for (i = 0; str[i] != ':'; i++)
                ;
            for (i += 2, j = 0; str[i] != '\t'; i++, j++)
                cropped[j] = str[i];
            temp = atoi(cropped);
            if (strcmp(copy, str) != 0)
            {
                if (temp == ans)
                    printf(str);
                strcpy(copy, str);
            }
        }
    }
    fclose(ptr);
    printf("\nMoney have in the Account : INR %lld\n\n", checkAcBalance(ans));
}

//function related to choice 4
void RemoveAc()
{
    char str[ENTRIES_LENGTH + 1], cropped[7], warn[1];
    int i, j, que, ans;
    printf("\n Enter Account No. : ");
    scanf("%d", &que);
    FILE *dataptr = fopen("acdetails.txt", "r");
    if (dataptr == NULL)
    {
        printf("Error While getting file....");
        exit(1);
    }
    while (1)
    {
        if (feof(dataptr))
        {
            printf("\nOopss...\nAccount Not Found....\nExiting....\n");
            break;
        }
        else
        {
            fgets(str, ENTRIES_LENGTH, dataptr);
            for (i = 0; str[i] != 'A'; i++)
                ;
            for (i += 8, j = 0; str[i] != '\t'; i++, j++)
                cropped[j] = str[i];
            ans = atoi(cropped);
            if (ans == que)
            { //after matching ask again for deletion
                printf("Are You Sure to Delete the Account ? (Y/n) : ");
                scanf("%s", &warn);
                if (warn[0] == 'Y')
                    deleteAc(ans);
                else
                    printf("\n\nYour Account is not deleted...\n\n");
                break;
            }
        }
    }
    fclose(dataptr);
    displayEntryScreen();
}
void deleteAc(int ans)
{
    FILE *fptr = fopen("acdetails.txt", "a+"),
         *tempf = fopen("temp.txt", "w");
    if (fptr == NULL)
    {
        printf("\nError While getting file...\n");
        exit(1);
    }
    char str[ENTRIES_LENGTH + 1], cropped[7];
    int j, i, temp, copy = 0;
    while (1)
    { //printing entries temporarily
        if (feof(fptr))
            break;
        else
        {
            fgets(str, ENTRIES_LENGTH, fptr);
            for (i = 0; str[i] != 'A'; i++)
                ;
            for (i += 8, j = 0; str[i] != '\t'; i++, j++)
                cropped[j] = str[i];
            temp = atoi(cropped);
            if (copy != temp)
            {
                if (temp == ans)
                    continue;
                /* 
                 *  don't write if the account no. of the loop
                 *  and the provided account no. is same. i.e., deleted the account
                 */
                else
                    fprintf(tempf, str);
                copy = temp;
            }
        }
    }
    fclose(fptr);
    fclose(tempf);
    //undoing this process above but with deleted content
    FILE *again = fopen("acdetails.txt", "w"),
         *ftemp = fopen("temp.txt", "r");
    copy = 0;
    while (1)
    {
        if (feof(ftemp))
            break;
        fgets(str, ENTRIES_LENGTH, ftemp);
        for (i = 0; str[i] != 'A'; i++)
            ;
        for (i += 8, j = 0; str[i] != '\t'; i++, j++)
            cropped[j] = str[i];
        temp = atoi(cropped);
        if (copy != temp)
        {
            fprintf(again, str);
            copy = temp;
        }
    }
    fclose(ftemp);
    if (remove("temp.txt") != 0)
        printf("\nError while deleting temporary file\n");
    fclose(again);
    printf("\nAccount Deleted Successfully...\n\n");
}

//function related to choice 5
void DisplayAcDetails()
{
    int que, i, j, ans;
    printf("Enter Account No. : ");
    scanf("%d", &que);
    FILE *ptr = fopen("acdetails.txt", "r");
    char str[ENTRIES_LENGTH + 1], cropped[7], warn[1];
    if (ptr == NULL)
    {
        printf("Error While getting file....");
        exit(1);
    }
    while (1)
    {
        if (feof(ptr))
        {
            printf("\nOopss...\nAccount Not Found....\nExiting....\n");
            break;
        }
        else
        {
            fgets(str, ENTRIES_LENGTH, ptr);
            for (i = 0; str[i] != 'A'; i++)
                ;
            for (i += 8, j = 0; str[i] != '\t'; i++, j++)
                cropped[j] = str[i];
            ans = atoi(cropped);
            if (ans == que)
            { //after matching,  printing results
                printf("\nAccount Details...\n   ");
                DisplayDetails(str);
                break;
            }
        }
    }
    fclose(ptr);
    displayEntryScreen();
}
/*
 * Thanks For Reading Till here.
 * Hope, You haven't just scrolled till down.
 */