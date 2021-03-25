#include <string.h>
#include <WiFi.h>
 
const char* ssid = "rx600m-90ebb6-1"; 
const char* password = "3250d8640b1b7"; 

WiFiServer server(80);

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h>
#endif

#define PIN        32

#define NUMPIXELS 91 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 1 // Time (in milliseconds) to pause between pixels

int cnt = 0;
int warmcnt = 0;
int k = 15;
int red = 255;
int green = 255;
int blue = 255;
int lightMode = 0;


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
//        Serial.write(c);
        Serial.print("currentLine:");
        Serial.println(currentLine);
        if(c == '\n'){
          Serial.println("runLED");
          char str[15];
          strcpy(str,currentLine.c_str());
          lightMode = atoi(strtok(str, ","));
          red = atoi(strtok(NULL, ","));
          green = atoi(strtok(NULL, ","));
          blue = atoi(strtok(NULL, ","));
          currentLine = "";
          if(lightMode == 0){
            runLED();
          }
        }
        else if (c != '\r'){
          currentLine += c;
        }
      }
      if(lightMode == 1){
        runLED();
      }
    }
//    Serial.println("while(client.connect) end");
  }
//  Serial.println("if(client) end");
}

void setupLED(){
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  
  pixels.begin();
}
int rainbow[100][3]={
  {255, 0, 0},  // red
  {255, 40, 0},   // orange
  {255, 155, 0}, //yellow
  {128, 225, 0},  // light green
  {0, 255, 0}, // green
  {0, 128, 255}, // skyblue
  {0, 0, 255}, // blue
  {255,0,70}, // purple
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
};

void runLED(){
  pixels.clear();
  for(int i=0; i<NUMPIXELS; i++) {
    int num = (i+cnt)%8;
    int num2 = (i+cnt)%100;
    switch(lightMode){
      case 0:
//        Serial.println("0");
        pixels.setPixelColor(i, pixels.Color(red,green,blue));
        break;
      case 1:
//        Serial.println("1");
        if(red == 1){
          pixels.setPixelColor(i, pixels.Color(rainbow[num][0],rainbow[num][1], rainbow[num][2]));
        }
        else if (green == 1){
          pixels.setPixelColor(i, pixels.Color(rainbow[num2][0],rainbow[num2][1], rainbow[num2][2]));
        }
        else if (blue == 1){
          pixels.setPixelColor(i, pixels.Color(warmcnt,warmcnt,warmcnt));
        }
        delay(1);
        break;
      }
  }
    pixels.show();   // Send the updated pixel colors to the hardware.

//    delay(DELAYVAL); // Pause before next pass through loop
    cnt++;
    if(lightMode == 1 && blue == 1){
      if(warmcnt == 255){
        k = -15;
        delay(400);
        }
      else if(warmcnt == 15){
        k = 15;
        delay(400);
        }
      warmcnt += k;
      Serial.println(warmcnt);
    }
    delayMicroseconds(100);
}
