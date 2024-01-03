#include "mbed.h"
#include <type_traits>
#include <string.h>

DigitalOut Outs[7] = {           //initialising outputs in an array
    D1,
    D2,
    D3,
    D4,
    D5,
    D6,
    D7
};

DigitalIn FNB(D8, PullUp);       //initialising input buttons
DigitalIn SB(D9, PullUp);


char FirstName[5];               //initialising First Name and Last Name variables
char Surname[5];

//letters and numbers matrix

char CharCodes[36][8] = {
    {'A', '1', '1', '1', '1', '1', '0', '1'},
    {'B', '1', '1', '1', '0', '0', '1', '1'},
    {'C', '0', '0', '0', '1', '1', '0', '1'},
    {'D', '0', '0', '1', '1', '1', '1', '1'},
    {'E','1','1','0','1','1','0','1'},
    {'F','1','1','0','1','0','0','1'},
    {'G','1','1','0','1','1','1','0'},
    {'H','1','0','0','1','0','1','1'},
    {'I','0','1','0','1','0','0','0'},
    {'J','0','1','0','0','1','1','0'},
    {'K','1','1','0','1','0','1','1'},
    {'L','1','0','0','1','1','0','0'},
    {'M','0','1','0','1','0','1','1'},
    {'N','0','0','0','1','0','1','1'},
    {'O','0','0','0','1','1','1','1'},
    {'P','1','1','1','1','0','0','1'},
    {'Q','1','1','1','0','0','1','1'},
    {'R','0','0','0','1','0','0','1'},
    {'S','1','1','0','0','1','1','0'},
    {'T','1','0','0','1','1','0','1'},
    {'U','0','0','0','1','1','1','0'},
    {'V','1','0','1','0','1','0','0'},
    {'W','1','0','1','0','1','0','1'},
    {'X','0','0','0','1','0','1','0'},
    {'Y','1','0','1','0','1','1','1'},
    {'Z','0','1','1','1','1','0','0'},
    {'0','1','1','1','1','1','1','0'},
    {'1','0','0','1','0','0','1','0'},
    {'2','0','1','1','1','1','0','1'},
    {'3','0','1','1','0','1','1','1'},
    {'4','1','0','1','0','0','1','1'},
    {'5','1','1','0','0','1','1','1'},
    {'6','1','1','0','1','1','1','1'},
    {'7','0','1','1','0','0','1','0'},
    {'8','1','1','1','1','1','1','1'},
    {'9','1','1','1','0','1','1','1'}
};

void FlashLetter(char array[8]) {            //letter flash function
    char tVar;
    tVar = '1';
    for (int i = 1; i <= 8; i++) {           //sets lights on 7SD to true if they correspond to the character display, by testing their relevant data in the matrix to the test character '1'
        char curr = array[i];
        if (curr == tVar) {
            Outs[i] = true;
        }
        else {
            Outs[i-1] = false;
        }
    }
    thread_sleep_for(1000);                //sleeps for 1s to display letter for 1s
    for (int i = 0; i <= 7; i++) {
        Outs[i] = false;
    }
    thread_sleep_for(250);                 //sleeps for .25s to leave break between letters
}

void DisplayName(char array[5]) {          //DisplayName function to iteratively sort through the characters in the name variable, and then find and display the corresponding letters on the 7SD using the flash letter function
    for (int i = 0; i < 5; i++) {
        char CurrLetter = array[i];
        for (int j = 0; j < 36; j++) {
            char TestLetter = CharCodes[j][0];
            if (CurrLetter == TestLetter) {
                FlashLetter(CharCodes[j]);
                j = 37;
            }
        }
    }
}

// main() runs in its own thread in the OS
/* testing
t1 = true;
    thread_sleep_for(500);
    t2 = true;
    thread_sleep_for(500);
    t3 = true;
    thread_sleep_for(500);
    t4 = true;
    thread_sleep_for(500);
    t5 = true;
    thread_sleep_for(500);
    t6 = true;
    thread_sleep_for(500);
    t7 = true;
    thread_sleep_for(500);
    t8 = true;
    thread_sleep_for(500);
*/
int main() {
    printf("This program is made to display the first 5 letters of your first name\n and the first 5 letters of your last name on a Seven Segment Display");         //interaction via CoolTerm
    printf("\nPlease enter the first 5 letters of your first name\n");
    scanf("%s", FirstName);                                            //input first name and surname
    printf("\nPlease enter the first 5 letters of your surname\n");
    scanf('%s', Surname);
    while (true) {                                                     //allow names to be displayed on button press
        if (not FNB) {
            DisplayName(FirstName);
        }
        if (not SB) {
            DisplayName(Surname);
        }
    }
}
