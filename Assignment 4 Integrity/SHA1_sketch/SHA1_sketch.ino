#include <ArduinoBearSSL.h>

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

  // This is the RSA encrypt-decrypt algorithm

  if (Serial.available() > 0){        // if you have data input
         String input = Serial.readString();        // read the whole input
         char charInput[input.length() + 1];
         input.toCharArray(charInput, input.length()); // adding the string input as char * type
          printSHA1(charInput);
         //std::string result = sha1(inputString);
         // Serial.print(result.toString());   
   } // if Serial.available() > 0

}  /* loop */

void printSHA1(char* str) {
  Serial.print("SHA1 of '");
  Serial.print(str);
  Serial.print("' is ");

  SHA1.beginHash();
  SHA1.print(str);
  SHA1.endHash();

  printResult();
}

void printResult()
{
  while (SHA1.available()) {
    byte b = SHA1.read();

    if (b < 16) {
      Serial.print("0");
    }

    Serial.print(b, HEX);
  }
  Serial.println();
}


void establishContact(){
   if (Serial.available() <= 0) {
       Serial.print("SHA1 Hash Function. Please input your message");   
   } 
   Serial.println();
} // establishContact()
