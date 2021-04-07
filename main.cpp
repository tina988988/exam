#include "mbed.h"
#include "uLCD_4DGL.h"
using namespace std::chrono;


Timer debounce;
uLCD_4DGL uLCD(D1, D0, D2);


// Initialize a pins to perform analog and digital output functions

// Adjust analog output pin name to your board spec.


AnalogOut aout(PA_4);
AnalogIn Ain(A0);

//DigitalOut dout(LED1);
InterruptIn sw2(PB_1);
InterruptIn sw1(PB_4);
InterruptIn sw0(PA_3);
EventQueue queue(64 * EVENTS_EVENT_SIZE);
Thread t;
//Timer T;

int flag = 0;
int c = 0;
int sample = 1000;
int j, d = 0;
int g = 0;

float ADCdata[4004];

void Confirm_print() {
 uLCD.printf("\nConfirm !\n");
}

void Confirm_Freq() {
 if (duration_cast<milliseconds>(debounce.elapsed_time()).count() > 500) {
 c = 1;
 g = 0;
 queue.call(Confirm_print);
 debounce.reset();
 }
}

void uLCD_print() {
 if (flag == -1) {
 uLCD.cls();
 uLCD.printf("\n1/8\n");
 }
 if (flag == 0) {
 uLCD.cls();
 uLCD.printf("\n1/4\n");
 }
 if (flag == 1) {
 uLCD.cls();
 uLCD.printf("\n1/2\n");
 }
 if (flag == 2) {
 uLCD.cls();
 uLCD.printf("\n1\n");
 }
}

void Trig_up() {
 if (duration_cast<milliseconds>(debounce.elapsed_time()).count() > 500) {
 if (flag < 2) flag = flag + 1;
 else flag = 2;

 c = 0;
 queue.call(uLCD_print);
 debounce.reset();
 }
}

void Trig_down() {
 if (duration_cast<milliseconds>(debounce.elapsed_time()).count() > 500) {
 if (flag > -1) flag = flag - 1;
 else flag = -1;
 c = 0;
 queue.call(uLCD_print);
 debounce.reset();
 }
}

int main(void)

{
 debounce.start();

 t.start(callback(&queue, &EventQueue::dispatch_forever));

 sw2.rise(Trig_up);
 sw1.rise(Trig_down);
 sw0.rise(Confirm_Freq);
 //int k = 0;

 while (1) {

 // change the voltage on the digital output pin by 0.1 * VCC

 // and print what the measured voltage should be (assuming VCC = 3.3v)

 if ((flag == 0) && c) {
 j = 0;
 for (float i = 0.0f; i < 0.9; i += 0.0009f) {

 aout = i;
 if ((g >=20) && (g <= 21)) ADCdata[j] = Ain;
 wait_us(5);
 j++;
 }
//f ((g >=200) && (g <= 201)) {
//for(k = 0 ; k < 10000;) {
    //ADCdata[j] = Ain;
   // j++;
//}
//}
ThisThread::sleep_for(200ms);

 
 for (float a = 0.9; a > 0.0f; a -= 0.0009f) {

 aout = a;
 if ((g >=20) && (g <= 21)) ADCdata[j] = Ain;
 wait_us(5);
 j++;

 }
 }

 if ((flag == -1) && c) {
 j = 0;
 for (float b = 0.0f; b < 0.9; b+= 0.0009f) {
 aout = b;
 if ((g >=20) && (g <= 21)) ADCdata[j] = Ain;
 wait_ns(10);
 j++;
 }
 //if ((g >=200) && (g <= 201)){
 //for(k = 0 ; k < 10000;k) {
    //ADCdata[j] = Ain;
    //j++;
 //}
//}
 ThisThread::sleep_for(220ms);
 for (float a = 0.9; a > 0.0f; a -= 0.0009f) {
 aout = a;
 if ((g >=20) && (g <= 21)) ADCdata[j] = Ain;
 wait_ns(10);
 j++;
 }
 }


 if((flag == 1) && c) {
 j = 0;
 for (float b = 0.0f; b < 0.9; b+= 0.0009f) {
 aout = b;
 if ((g >=20) && (g <= 21)) ADCdata[j] = Ain;
 wait_us(25);
 j++;
 }
 //if ((g >=200) && (g <= 201)){
 //for(k = 0 ; k < 10000;k++) {
   // ADCdata[j] = Ain;
    //j++;
// }
//}
 ThisThread::sleep_for(160ms);
 for (float a = 0.9; a > 0.0f; a -= 0.0009f) {
 aout = a;
 if ((g >=20) && (g <= 21)) ADCdata[j] = Ain;
 wait_us(25);
 j++;
 }
 }
 if((flag == 2) && c) {
 j = 0;
 for (float b = 0.0f; b < 0.9; b+= 0.0009f) {
 aout = b;
 if ((g >=20) && (g <= 21)) ADCdata[j] = Ain;
 wait_us(65);
 j++;
 }
 //if ((g >=200) && (g <= 201)){
 //for(k = 0 ; k < 1000;) {
 //  ADCdata[j] = Ain;
  //  j++;
//}
//}
 ThisThread::sleep_for(80ms);
 for (float a = 0.9; a > 0.0f; a -= 0.0009f) {
 aout = a;
 if ((g >=20) && (g <= 21)) ADCdata[j] = Ain;
 wait_us(65);
 j++;
 }
 }

 if (c && (g >= 20) && (g <= 21)) {
 for (int e = 0;e < j; e++) {
 printf("%f\r\n", ADCdata[e]);
 }
 }
 g++;
 }
}