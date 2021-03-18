#include <iostream>
#include <WiFi.h>
 


// ウェブサーバーをポート80で開始
WiFiServer server(80);

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>
#endif

#define PIN        32

#define NUMPIXELS 91 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 100 // Time (in milliseconds) to pause between pixels

int cnt = 0;
int red = 255;
int green = 255;
int blue = 255;


void setup() {
  // put your setup code here, to run once:
  setupWIFI();
  setupLED();
  runLED();
}

void loop() {
  // put your main code here, to run repeatedly:
  runWIFI();
}

void setupWIFI(){
  delay(1000);
  Serial.begin(115200);

  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.begin();
}

void runWIFI(){
  WiFiClient client = server.available();

  if (client) {
    Serial.println("new client");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if(c != '\n'){
          currentLine += c;
        }
        Serial.print("currentLine:");
        Serial.println(currentLine);
       
          if(currentLine == "RED"){
            Serial.println("REDBUTTON");
            red = 128;
            green = 0;
            blue = 0;
            currentLine = "";
            runLED();
            delay(100);
//            break;
            }
          else if(currentLine == "GRN"){
            Serial.println("GRNBUTTON");
            red = 0;
            green = 128;
            blue = 0;
            currentLine = "";
            runLED();
            delay(100);
//            break;
            }
           else if(currentLine == "BLU"){
            Serial.println("BLUBUTTON");
            red = 0;
            green = 0;
            blue = 128;
            currentLine = "";
            runLED();
            delay(100);
//            break;
            }
          else if(c == '\n'){
            }
//          else if(tmp1 == "R"){
//            red = 25*atoi(tmp2.c_str());
//            Serial.println(red);
//            String tmp1 = "";
//            String tmp2 = "";
//            delay(100);
////            break;
//            }
//          else if(tmp1 == "G"){
//            green = 25*atoi(tmp2.c_str());
//            Serial.println(green);
//            String tmp1 = "";
//            String tmp2 = "";
//            delay(100);
//            break;
//            }
//          else if(tmp1 == "B"){
//            blue = 25*atoi(tmp2.c_str());
//            Serial.println(blue);
//            String tmp1 = "";
//            String tmp2 = "";
//            delay(100);
//            break;
//            }
//          if(currentLine.length() > 3){
//            String tmp1 = "";
//            String tmp2 = "";
//            delay(100);
//            break;
//            }
//          }
      }
    }
    Serial.println("while(client.connect) end");
//    client.stop();
//    Serial.println("Dis Connect");
  }
  Serial.println("if(client) end");
}

void setupLED(){
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  
  pixels.begin();
}

void runLED(){
  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    int num = (i+cnt)%8;
//    pixels.setPixelColor(i, pixels.Color(rainbow[num][0],rainbow[num][1], rainbow[num][2]));
      pixels.setPixelColor(i, pixels.Color(red,green,blue));
    
  }
    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    cnt++;
}
