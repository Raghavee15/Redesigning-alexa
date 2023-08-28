/*
  WriteMultipleFields
  
  Description: Writes values to fields 1,2,3,4 and status in a single ThingSpeak update every 20 seconds.
  
  Hardware: ESP8266 based boards
  
  !!! IMPORTANT - Modify the secrets.h file for this project with your network connection and ThingSpeak channel details. !!!
  
  Note:
  - Requires ESP8266WiFi library and ESP8622 board add-on. See https://github.com/esp8266/Arduino for details.
  - Select the target hardware from the Tools->Board menu
  - This example is written for a network using WPA encryption. For WEP or WPA, change the WiFi.begin() call accordingly.
  
  ThingSpeak ( https://www.thingspeak.com ) is an analytic IoT platform service that allows you to aggregate, visualize, and 
  analyze live data streams in the cloud. Visit https://www.thingspeak.com to sign up for a free account and create a channel.  
  
  Documentation for the ThingSpeak Communication Library for Arduino is in the README.md folder where the library was installed.
  See https://www.mathworks.com/help/thingspeak/index.html for the full ThingSpeak documentation.
  
  For licensing information, see the accompanying license file.
  
  Copyright 2020, The MathWorks, Inc.
*/

#include <ESP8266WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

char ssid[] = "prakash";   // your network SSID (name) 
char pass[] = "9789901213";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = 2042003;
const char * myWriteAPIKey = "PV4JC123K3NTX6G8";

// Initialize our values
int number1 = 0;
int number2 = random(0,100);
int number3 = random(0,100);
int number4 = random(0,100);
int number5 = random(0,100);
int number6 = random(0,100);
int number7 = random(0,100);
int number8 = random(0,100);
String myStatus = "";
int incomingByte = 0;
char arr[12] ={0};
int i=0;
bool received_flag=0;
void setup() {
  Serial.begin(115200);  // Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}


void loop() {

  if (Serial.available() > 0) {

incomingByte = Serial.read(); // read the incoming byte:
arr[i] = incomingByte;
Serial.print(" I received:");
Serial.println(incomingByte);

i++;
}

if(i == 8 )
   {
       if(arr[7] == 'n')
       {
        
       if(arr[4] == '1')   
       {                   
        ThingSpeak.setField(1, 1);
        received_flag=1;             
       }
       else if(arr[4] == '2')
       { 
         ThingSpeak.setField(2, 1);
         received_flag=1;         
       } 
       else if(arr[4] == '3')
       { 
         ThingSpeak.setField(3, 1);
         received_flag=1;        
       }  
       else if(arr[4] == '4')
       { 
       ThingSpeak.setField(4, 1);
      received_flag=1;       
        }  
       else if(arr[4] == '5')
       { 
        ThingSpeak.setField(5, 1);
        received_flag=1;        
       }
       else if(arr[4] == '6')  
       {
         ThingSpeak.setField(6, 1);
         received_flag=1;         
         Serial.println("ThingSpeak.setField(6, 1);");         
       }
        else if(arr[4] == '7')  
       {
         ThingSpeak.setField(7, 1);
          received_flag=1;         
         Serial.println("ThingSpeak.setField(7, 1);");         
       }
        else if(arr[4] == '8')  
       {
         ThingSpeak.setField(8, 1);
         received_flag=1;         
       }
	   }
       else
       {
         if(arr[4] == '1')   
       {                   
          ThingSpeak.setField(1, 0);
          received_flag=1;             
       }
       else if(arr[4] == '2')
       { 
         ThingSpeak.setField(2, 0);
         received_flag=1;         
       } 
       else if(arr[4] == '3')
       { 
         ThingSpeak.setField(3, 0);
         received_flag=1;         
       }  
       else if(arr[4] == '4')
       { 
       ThingSpeak.setField(4, 0);
       received_flag=1;       
       }  
       else if(arr[4] == '5')
       { 
        ThingSpeak.setField(5, 0);
        received_flag=1;        
       }
       else if(arr[4] == '6')  
       {
         ThingSpeak.setField(6, 0);
         received_flag=1;         
       }
        else if(arr[4] == '7')  
       {
         ThingSpeak.setField(7, 0);
         received_flag=1;         
       }
        else if(arr[4] == '8')  
       {
         ThingSpeak.setField(8, 0);
         received_flag=1;         
       }




         
       }   
             
        i = 0 ;
     }
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  // set the fields with the values
  // ThingSpeak.setField(1, number1);
  // ThingSpeak.setField(2, number2);
  // ThingSpeak.setField(3, number3);
  // ThingSpeak.setField(4, number4);
  // ThingSpeak.setField(5, number5);
  // ThingSpeak.setField(6, number6);
  // ThingSpeak.setField(7, number7);
  // ThingSpeak.setField(8, number8);  

  // figure out the status message
  if(number1 > number2){
    myStatus = String("field1 is greater than field2"); 
  }
  else if(number1 < number2){
    myStatus = String("field1 is less than field2");
  }
  else{
    myStatus = String("field1 equals field2");
  }
  
  // set the status
  ThingSpeak.setStatus(myStatus);
  
  // write to the ThingSpeak channel
  if(received_flag)
  {
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  }  
  received_flag=0;
  // change the values
  //number1++;
  //if(number1 > 99){
    //number1 = 0;
  //}
  //number2 = random(0,100);
  //number3 = random(0,100);
  //number4 = random(0,100);
  
 // delay(20000); // Wait 20 seconds to update the channel again
}

