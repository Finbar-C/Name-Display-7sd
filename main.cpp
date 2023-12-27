#include "mbed.h"
#include <type_traits>
#include <string.h>

DigitalOut Outs[7] = {
    D1,
    D2,
    D3,
    D4,
    D5,
    D6,
    D7
};

DigitalIn FNB(D8, PullUp);
DigitalIn SB(D9, PullUp);


char FirstName[5];
char Surname[5];

//letters and numbers matrix

char CharCodes[36][8] = {
    {"A", "1", "1", "1", "1", "1", "0", "1"},
    {"B", "1", "1", "1", "0", "0", "1", "1"},

};

void FlashLetter(char array[8]) {
    char tVar;
    tVar = '1';
    for (int i = 1; i <= 8; i++) {
        char curr = array[i];
        if (curr == tVar) {
            Outs[i] = true;
        }
        else {
            Outs[i-1] = false;
        }
    }
    thread_sleep_for(1000);
    for (int i = 0; i <= 7; i++) {
        Outs[i] = false;
    }
    thread_sleep_for(250);
}

void DisplayName(char array[5]) {
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
    printf("This program is made to display the first 5 letters of your first name\n and the first 5 letters of your last name on a Seven Segment Display");
    printf("\nPlease enter the first 5 letters of your first name\n");
    scanf("%s", FirstName);
    printf("\nPlease enter the first 5 letters of your surname\n");
    scanf("%s", Surname);
    while (true) {
        if (not FNB) {
            DisplayName(FirstName);
        }
        if (not SB) {
            DisplayName(Surname);
        }
    }
}
