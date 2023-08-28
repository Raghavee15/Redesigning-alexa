/*
 * This is a basic example on how to use Espalexa and its device declaration methods.
 */ 
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>

// prototypes
boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);

// Change this!!
const char* ssid = "onepluspro";
const char* password = "12345678";

boolean wifiConnected = false;

Espalexa espalexa;

EspalexaDevice* device3; //this is optional

void setup()
{
  Serial.begin(115200);
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    
    // Define your devices here. 
    espalexa.addDevice("32301", firstLightChanged); //simplest definition, default state off
    
    device3 = new EspalexaDevice("32303", thirdLightChanged); //you can also create the Device objects yourself like here
    espalexa.addDevice(device3); //and then add them
    device3->setValue(128); //this allows you to e.g. update their state value at any time!
    espalexa.addDevice("32202", secondLightChanged, 255); //third parameter is beginning state (here fully on)
    espalexa.addDevice("32304", fourthLightChanged);
    espalexa.addDevice("32305", fifthLightChanged);
    espalexa.addDevice("32306", sixthLightChanged);
    espalexa.addDevice("32307", sevethLightChanged);
    espalexa.addDevice("32308", eigthLightChanged);
    
    espalexa.begin();
    
  } else
  {
    while (1) {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}
 
void loop()
{
   espalexa.loop();
   delay(1);
}

//our callback functions
void firstLightChanged(uint8_t brightness) {
   // Serial.print("Device 1 changed to ");
    
    //do what you need to do here

    //EXAMPLE
    if (brightness) {
      Serial.print("32301 on");
      //Serial.println(brightness);
    }
    else  {
      Serial.println("32301 off");
    }
}

void secondLightChanged(uint8_t brightness) {
    //Serial.print("Device 1 changed to ");
    
    //do what you need to do here

    //EXAMPLE
    if (brightness) {
      Serial.print("32302 on");
      //Serial.println(brightness);
    }
    else  {
      Serial.println("32302 off");
    }
}

void thirdLightChanged(uint8_t brightness) {
    //Serial.print("Device 1 changed to ");
    
    //do what you need to do here

    //EXAMPLE
    if (brightness) {
      Serial.print("32303 on");
      //Serial.println(brightness);
    }
    else  {
      Serial.println("32303 off");
    }
}

void fourthLightChanged(uint8_t brightness) {
    //Serial.print("Device 1 changed to ");
    
    //do what you need to do here

    //EXAMPLE
    if (brightness) {
      Serial.print("32304 on");
      //Serial.println(brightness);
    }
    else  {
      Serial.println("32304 off");
    }
}
void fifthLightChanged(uint8_t brightness) {
    //Serial.print("Device 1 changed to ");
    
    //do what you need to do here

    //EXAMPLE
    if (brightness) {
      Serial.print("32305 on");
      //Serial.println(brightness);
    }
    else  {
      Serial.println("32305 off");
    }
}
void sixthLightChanged(uint8_t brightness) {
   // Serial.print("Device 1 changed to ");
    
    //do what you need to do here

    //EXAMPLE
    if (brightness) {
      Serial.print("32306 on");
      //Serial.println(brightness);
    }
    else  {
      Serial.println("32306 off");
    }
}
void sevethLightChanged(uint8_t brightness) {
    //Serial.print("Device 1 changed to ");
    
    //do what you need to do here

    //EXAMPLE
    if (brightness) {
      Serial.print("32307 on");
      //Serial.println(brightness);
    }
    else  {
      Serial.println("32307 off");
    }
}
void eigthLightChanged(uint8_t brightness) {
    //Serial.print("Device 1 changed to ");
    
    //do what you need to do here

    //EXAMPLE
    if (brightness) {
      Serial.print("32308 on");
      //Serial.println(brightness);
    }
    else  {
      Serial.println("32308 off");
    }
}
// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state){
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
