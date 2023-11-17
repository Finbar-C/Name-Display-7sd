#include "mbed.h"
#include <type_traits>

DigitalOut t1(D1);
DigitalOut t2(D2);
DigitalOut t3(D3);
DigitalOut t4(D4);
DigitalOut t5(D5);
DigitalOut t6(D6);
DigitalOut t7(D7);
DigitalOut t8(D8);
// main() runs in its own thread in the OS
int main() {
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

}
