/*
Program Description: This is a security authentication program based on a provided access code "4523". 
The program allows a user to:
                -> Enter a code
                -> Encrypt the entered code and verify it with the access code
                -> Decrypt the code
                -> Keep a counter of the number of correct and incorrect matches the user code matched with the access code.

Author: Brandon-Lee De Bruyn 

Date: 18/02/2021

Compiler: GCC
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 4

// function signatures
int enter_code(int[], int *, int *);                                        // menu - option 1
int encrypt_verify(const int[], int[], int[], int *, int *, int *, int *);  // menu - option 2
int decrypt_code(int[], int[], int *);                                      // menu - option 3                             
void display_counter(int *, int *);                                         // menu - option 4
void exit_program(void);                                                    // menu - option 5

// main function - displays the menu for navigation through the program
int main(void)
{  
    int menu_decision = 0;
    const int access_code[SIZE] = {4, 5, 2, 3};       // access code -> "4, 5, 2, 3"
    static int user_code[SIZE];                       // user code set to default "1,2,3,4"
    static int encrypted_user_code[SIZE];
    static int decrypted_user_code[SIZE];
    static int valid_code_counter;
    static int invalid_code_counter;

    static int didEncrypt;                            // variable to check if encryption verification has been done with current user code
    static int codeExist = 0;                         // variable to check if a code exist within the program

    // display menu and get menu decision from user
    printf("\n--------------------------------------------------------------------\n");
    printf("\nSelect any option from the menu to get started:\n\n1. Enter any code\n2. Encrypt code entered and verify if correct\n3. Decrypt code");
    printf("\n4. Display the number of times the encrypted code entered matches the authorised code\n5. Exit Program\n\n");
    scanf("%d", &menu_decision);

    // if statement to handle menu navigation from user -> input (1 - 5) with validation for invalid input
    if (menu_decision == 1)
    {
        // menu_decision = 1 -> call the enter_code function passing the user_code as a parameter
        enter_code(user_code, &didEncrypt, &codeExist);
        
    }
    else if (menu_decision == 2)
    {
        // menu_decision = 2 -> call the encrypt_verify function
        encrypt_verify(access_code, user_code, encrypted_user_code, &valid_code_counter, &invalid_code_counter, &didEncrypt, &codeExist);
    }
    else if (menu_decision == 3)
    {
        decrypt_code(encrypted_user_code, user_code, &didEncrypt);
    }
    else if (menu_decision == 4)
    {
        display_counter(&valid_code_counter, &invalid_code_counter);

    }
    else if (menu_decision == 5)
    {   
        exit_program();
    }
    else
    {
        // input validation if user inputs a character or any non-integer type
        while(getchar() != '\n');

        // if incorrect input display error 
        printf("\nInvalid Input, Try again.\n");

        // return back to main()
        main();

    } // end if

} // end main()

// ------------------------------------ menu option 1 ------------------------------------
//
// enter_code() function is used to get a access code from the user and save it to an array
int enter_code(int *user_code, int *didEncrypt, int *codeExist)
{
    int i;
    (*didEncrypt) = 0;

    printf("\nEnter 4 single-digit non-negative integers between 0-9:\n");
    
    // for loop to input the user code into the array user_code 
    for(i = 0; i < SIZE; i++)
    {
        // if statement to check if the correct data type is entered into the array -> if the input is invalid, it enters the if statement, displays input error and calls the enter_code() function
        if( (scanf("%d", & *(user_code + i))) != 1)
        {
            // catch any invalid characters
            while(getchar() != '\n');

            // display error to user
            printf("\nInvalid Input, Try again.\n");

            // recall the enter_code() function for another attempt
            enter_code(user_code, didEncrypt, codeExist);

        } // end if

    } // end for

    // for loop to check if each integer in the array is a valid integer
    for(i = 0; i < SIZE; i++)
    {
        // check if integer is positive and smaller than 10 -> if the integer entered is invalid, enter if statement to display error and recalls the enter_code() function
        if(*(user_code + i) > 9 || *(user_code + i) < 0)
        {
            // display error 
            printf("\nInvalid Input, Try again.\n");

            // recall the enter_code() function for another attempt
            enter_code(user_code, didEncrypt, codeExist);

        } // end if

    } // end for

    // set the variable codeExist to 1 indicating that the user_code array contains a code and return back to main() 
    (*codeExist = 1);
    main();

} // end enter_code()


// ------------------------------------ menu option 2 ------------------------------------
//
// encrypt_verify() function is used to encrypt the code entered by the user from option 1 and encrypt it, 
// then it verifies if the encryption password matches with the access code
int encrypt_verify(const int *access_code, int *user_code, int *encrypted_user_code, int *valid_counter, int *invalid_counter, int *didEncrypt, int *codeExist)
{
    int i;
    int num_check = 0;

    if((*didEncrypt) == 0 && (*codeExist) == 1)
    {   
        // swap numbers (1 with 3) and (2 with 4) and assign to the encrypter_user_code
        encrypted_user_code[0] = user_code[2];
        encrypted_user_code[1] = user_code[3];
        encrypted_user_code[2] = user_code[0];
        encrypted_user_code[3] = user_code[1];

        // for loop to add 1 to each number and change values from 10 to 0
        //
        for(i = 0; i < SIZE; i++)
        {   
            // add 1 to each number
            *(encrypted_user_code + i) = *(encrypted_user_code + i) + 1;
            
            // if statememnt to check if the current index is the integer 10, if true -> change to 0
            if(*(encrypted_user_code + i) == 10)
            {
                *(encrypted_user_code + i) = 0;

            } // end if   

        } // end for

        // for loop to check if encrypted_user_code matches with the access code
        for(i = 0; i < SIZE; i++)
        {
            if (*(encrypted_user_code + i) == *(access_code + i))
            {
                num_check++; // counter if index of user code matches with the same index of access code

            } // end if

        } // end for
        
        // if statement to check if the correct code was entered and notify user of the result
        //
        if(num_check == SIZE) // if the encrypted user code matched (SIZE) times with the authorisation code, the code was entered correctly
        {
            printf("\n\nCorrect Code entered\n");
            (*valid_counter) ++;
        }
        else
        {
            printf("\n\nWrong Code entered\n");
            (*invalid_counter) ++;

        } // end if
        
        // reset the num_check counter and set didEncrypt to 1 -> since the code is now encrypted
        num_check = 0;
        (*didEncrypt) = 1;
    }
    else if((*didEncrypt) == 1) // if the code has been encrypted and verified already, theres no need to do it again
    {
        printf("\nYou have already Encrypted and Verified your current code\n");
    }
    else // if the code does not exist -> display error
    {
        printf("\nYou can't verify a PIN that does not exist.\n");
    }

    // return back to main()
    main();

} // end encrypt_verify()

// ------------------------------------ menu option 3 ------------------------------------
//
// decrypt_code() function to decrypt the encrypted user code
int decrypt_code(int *encrypted_user_code, int *user_code, int *didEncrypt)
{
    int i;

    if((*didEncrypt) == 1)
    {
        // ------ decryption algorithm ------- //
    
        // swap numbers (1 with 3) and (2 with 4) and assign to user_code
        user_code[0] = encrypted_user_code[2];
        user_code[1] = encrypted_user_code[3];
        user_code[2] = encrypted_user_code[0];
        user_code[3] = encrypted_user_code[1];

        // for loop to subtract 1 from each number and change values from -1 to 9
        //
        for(i = 0; i < SIZE; i++)
        {   
            // subtract 1 from each number
            *(user_code + i) = *(user_code + i) - 1;
            
            // if statememnt to check if the current index is the integer -1, if true -> change to 0
            if(*(user_code + i) == -1)
            {
                *(user_code + i) = 9;

            } // end if   

        } // end for

        // for loop to display the decrypted user_code to the user
        printf("\nSucess! Your code has been Decrypted.\nYour code is:\n\n");
        for(i = 0; i < SIZE; i++)
        {
            printf("%d", *(user_code + i));

        } // end for
            
        // set didEncrypt to 0
        (*didEncrypt) = 0;

    }
    else
    {
        // if didEncrypt is 0 -> user has not encrypted a code or has decrypted their code
        printf("\nYou have not encrypted a code yet.\n");

    } // end if

    // return back to main()
    main();

} // end decrypt_code()

// ------------------------------------ menu option 4 ------------------------------------
//
// display_counter() function is used to display the number of times the encrypted code entered by the user matches with the authorised code, it display successfull and unsuccessfull atempts
void display_counter(int *valid_counter, int *invalid_counter)
{  
    // display the succesfull and incorrect counters
    printf("\nNumber of times encrypted code entered matches authorised code succesfully: %d\n", ( *valid_counter));
    printf("\nNumber of times encrypted code entered matched authorised code incorrectly: %d\n", ( *invalid_counter));

    // return back to main()
    main();

} // end display_counter()

// ------------------------------------ menu option 5 ------------------------------------
//
// exit_program() function is used to confirm exiting program with some validation
void exit_program(void)
{
    char exit_confirm = ' ';

    // prompt user for confirmation to exit program -> get user decision for yes or no
    printf("\nAre you sure you want to exit the Program? Press 'y' for yes, press 'n' for no\n");
    scanf(" %c", &exit_confirm);

    // if statement to check if the user input is yes or no for program exit
    if(exit_confirm == 'y')
    {  
        printf("\nExiting Program.\n");
        exit(0);

    }
    else if(exit_confirm == 'n')
    {   
        // return back to main()
        main();

    }
    else  // input validation
    {
        // input validation to stop buffer overflow
        while(getchar() != '\n');

        // if incorrect input display error 
        printf("\nInvalid Input, Try again.\n");

        // prompt user again for yes/no exit
        exit_program();

    } // end if

} // end exit_program()