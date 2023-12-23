// Title: 
int p = 997; // First prime number
int q = 991; // Second prime number
int n = p * q; // Product of the two large number = 988027
// n is the modulus for the public key and the private keys.
int phi = (p - 1)*(q - 1); // The totient: phi(n) = (p-1)(q-1) = 986040
// e is released as the public key exponent
// Choose an integer e such that 1 < e < phi(n), and e is co-prime to phi(n)
int e = 877;

// Compute d to satisfy the congruence relation: d * e congruent to 1 (mod phi(n))
// d * e = 1 + x * phi(n). d and x are integers 
// In this case, 877 * 3373 = 1 + 3 * 986040
// d is kept as the private key exponent.
int d = 3373; 

// Public key is tuple (n, e) and private key is tuple (n, d)
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

  String input = "";             // serial input character
  if (Serial.available() > 0){        // if you have data input
         input = Serial.readString();        // read the whole input
         if (input.startsWith("/en ")){
          int messageToEncrypt = input.substring(4).toInt();
          int encryptedMessage = modularExponentiation(messageToEncrypt, e, n);
          Serial.println(encryptedMessage);
         } else if (input.startsWith("/de ")){
          int messageToDecrypt = input.substring(4).toInt();
          int decryptedMessage = modularExponentiation(messageToDecrypt, d, n);
          Serial.println(decryptedMessage);
         } else {
            Serial.print("Unknown command. Please start the message with either /en or /de ");
          }
         Serial.println();

   } // if Serial.available() > 0

}  /* loop */


/* Efificent iterative modular exponentiation function to calculate (m^e)%n in O(log e) */
int modularExponentiation(long long m, int e, int n)
{
    long res = 1;     // Initialize result
 
    m = m % n; // Update m if it is more than or equal to n
  
    if (m == 0) return 0; // In case m is divisible by n;
 
    while (e > 0) {
        // If e is odd, multiply m with result
        if (e & 1)
            res = (res*m) % n;
 
        // e must be even now
        e = e>>1; // e = e/2
        m = (m*m) % n;
    }
    return res;
}


void establishContact(){
   if (Serial.available() <= 0) {
       Serial.print("RSA encryption/decryption. Can only works with numbers.\nPlease start with either /en or /de and your message");   
   } 
   Serial.println();
} // establishContact()
