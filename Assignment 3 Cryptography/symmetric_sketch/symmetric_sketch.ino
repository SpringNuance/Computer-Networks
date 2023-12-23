// This is a XOR encryption sketch
// This sketch tests communication between your terminal program and the Arduino board.
// If you send a plain text message to the Arduino board, you get back an encrypted message.
// If you send the encrypted message back to the Arduino, you get the original plain text message back.
// Hence it is called the symmetric encryption

// Testing procedure:
// Connect your USB to serial cable to the Arduino.
// Compile and upload this sketch to the Arduino board.
// Go to tools -> serial monitor.
// Type in a plain text message and send it.
// The Arduino will reply with an encrypted message.

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
  // This is the XOR encrypt-decrypt symmetric algorithm
  // If you run the algorithm twice, you get back the original message

  String input = "";             // serial input character
  char key[30] = "abcdefghijklmnopqrstuvwxyz";      // The key for xor function
  if (Serial.available() > 0) {        // if you have data input
         input = Serial.readString();        // read the whole input
         char charInput[input.length() + 1];
         input.toCharArray(charInput, input.length()); // adding the string input as char * type
         char * result = XORENC(charInput, key); // xor symmetric encryption
         Serial.print(result);   
         Serial.println();
   } 
}  /* loop */

// XOR symmetric encryption
char* XORENC(char* in, char* key){
  int insize = strlen(in);
  int keysize = strlen(key);
  for(int x=0; x < insize; x++){
    for(int i=0; i < keysize; i++){
      in[x]=(in[x]^key[i]);
    }
  }
  return in;
}

void establishContact() {
   if (Serial.available() <= 0) {
       Serial.print("XOR encryption/decryption. Please input a message");   
   } 
   Serial.println();
} // establishContact()
