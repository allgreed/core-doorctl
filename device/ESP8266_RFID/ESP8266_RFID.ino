#include <SoftwareSerial.h>
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define DEBUG 

#ifdef DEBUG
#define D(msg) Serial.println(msg)
#else
#define D(msg) ((void)0)
#endif


#define URL "http://192.168.88.4:5000/?card="
//#define URL "http://192.168.122.1:80/?card="


SoftwareSerial RFIDSerial(12, 10); // RX, TX
ESP8266WiFiMulti WiFiMulti;

void id2str(int id[14], char strid[64]){
  int stridoffset = 0;
  memset(strid, 0,  64);
  for(int offset=0; offset < 14; offset++){
    itoa(id[offset], strid + stridoffset, 10);
    stridoffset += strlen(strid + stridoffset);
    strid[stridoffset]=',';
    stridoffset++;
  }
}


char queryUrl[128] = URL;
HTTPClient http;

int digit;
int id[14];
int offset=0;
int state=0;
char* strid = queryUrl + sizeof(URL) - 1;

void setup() {
  Serial.begin(115200);
  D("setup:rfid");
  RFIDSerial.begin(9600);
  D("setup:wifi");
  WiFiMulti.addAP("Hackerspace:AP", "dupaDupa42");
  D("setup:connecting to wifi");
  while(WiFiMulti.run() != WL_CONNECTED){delay(100);D(".");}
  D("setup:end");

}

bool sendQuery(){
  D("sendQuery");
  D(queryUrl);
  http.begin(queryUrl);
  int httpCode = http.GET();

  if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                return strcmp("yes", payload) ==0;
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
        return false;
}


void loop() {

  switch(state){

    case 0:
      if(RFIDSerial.available()){
        id[offset] = RFIDSerial.read();
        if(offset==0 && id[offset] !=2){
          //wait for start
          break;
        }
        offset++;
        if(offset == 14){
          state=1;
        }
      }
      break;
    case 1:
      id2str(id, stri
      break;d);
      D(strid);
      state=2;
      offset=0;
      break;
    case 2:
      if(sendQuery()){
        state=3;
      } else {
        state=0; 
      }
      break;
    case 3:
      //set servo to open
      //wait 1000
      //disable servo
      //wait 5000
      //set servo to close
      //wait 1000
      //disable servo
      
      break;
    default:
      D("ERR");
      
      
  }
  
}

