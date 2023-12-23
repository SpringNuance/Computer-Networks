#include <MD5.h>

void setup() {

  // put your setup code here, to run once:

  Serial.begin(9600);   // initialize the serial port at 9600 baud

  while (!Serial) {

         ;  // wait for serial port to connect

         } // wait for serial port to connect

  establishContact();  // wait for incoming data

  } /* setup */


void loop() {

  // put your main code here, to run repeatedly:

  String input = "";             // serial input character
  if (Serial.available() > 0){        // if you have data input
         input = Serial.readString();        // read the whole input
         char charInput[input.length() + 1];
         input.toCharArray(charInput, input.length()); // adding the string input as char * type
         unsigned char* hash = MD5::make_hash(charInput);
         //generate the digest (hex encoding) of our hash
         char *md5str = MD5::make_digest(hash, 16);
          //print it on our serial monitor
        Serial.println(md5str);
        //Give the Memory back to the System if you run the md5 Hash generation in a loop
        free(md5str);
        //free dynamically allocated 16 byte hash from make_hash()
          free(hash);

   } // if Serial.available() > 0

}  /* loop */


void establishContact(){
   if (Serial.available() <= 0) {
       Serial.print("MD5 Hash Function. Please input your message");   
   } 
   Serial.println();
} // establishContact()
