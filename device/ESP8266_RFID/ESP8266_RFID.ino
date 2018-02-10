//#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

SoftwareSerial RFIDSerial(2, 10); // RX, TX

int flag=0,RX_Flag=0;//serial port sign
char Code[14]; 
long Num=0;//decode data
int serpin=0;//pin of servo
int Door=0;

const char* ssid     = "hackerspace_publiczny";
const char* password = "przyjmujemy_datki_x86";

const char* host = "192.168.88.246";
const int httpPort = 5000;
char rx_byte = 0;
String rx_str = "";

void setup() {
  Serial.begin(115200);
  RFIDSerial.begin(9600);
}

void loop() {
  int i;
  long temp = 0, time = 0;
  RX_Flag = 0;
  while (1){
    Read_ID();
    if (RX_Flag == 1)
    {
      for (i = 5; i < 11; i++) //
      {
        Num <<= 4;
        if (Code[i] > 64)  Num += ((Code[i]) - 55);
        else Num += ((Code[i]) - 48);
        RFIDSerial.println(Num);
      }
      RFIDSerial.println(Num);
//      if ((Num == Password1) || (Num == Password2)) //识别成功
//      {
//        for (int i = 0; i <= 50; i++) //
//        {
//          pulse(serpin, 180); //
//        }
//        delay(2000);
//        for (int i = 0; i <= 50; i++) //
//        {
//          pulse(serpin, 20); //
//        }
//      }
      while (RFIDSerial.read() > 0); //
      RX_Flag = 0; //
      Num = 0; //
    }
  }
}

//
//String Read_database() {
//  rx_str = "";
//  //  WiFi.forceSleepWake();
//  delay(10);
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
//  WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//
//  Serial.println("");
//  Serial.println("WiFi connected");
//  Serial.print("connecting to ");
//  Serial.println(host);
//
//  // Use WiFiClient class to create TCP connections
//  WiFiClient client;
//  if (!client.connect(host, httpPort)) {
//    Serial.println("connection failed");
//  }
//
//  //   We now create a URI for the request
//  String url = "/cards";
//  Serial.print("Requesting URL: ");
//  Serial.println(url);
//
//  // This will send the request to the server
//  client.print(String("GET ") +
//               url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Accept: text/html" + "\r\n" + "Connection: close\r\n\r\n");
//  delay(10);
//
//  // Read all the lines of the reply from server and print them to Serial
//  Serial.println("Respond:");
//  while (client.available()) {
//    String readInfo = client.readStringUntil('\r');
//    Serial.print(readInfo);
//
//  }
//
//  Serial.println();
//  Serial.println("closing connection");
//  //  stopWiFiAndSleep();
//}

void Read_ID(void)
{
    int i=0;
    char temp;
    for(i=0;(RFIDSerial.available()>0);i++)//
    //while(Serial.available()>0)
    {
      temp=RFIDSerial.read();
      RFIDSerial.print(temp);
      delay(2);
      RFIDSerial.println(i);
      if(temp==0X02)  //recieve the ssrt bit
        {
         flag=1;i=0;RX_Flag=0;//
        }
      if(flag==1)//detect the start bit and recieve data
      {
        if(temp==0X03)//detect the end code,
        {
         flag=0;  //zero clearing
         if(i==13) RX_Flag=1;//
         else RX_Flag=0;
       break;
        }
         Code[i]=temp;
      } 
    }       
     flag=0;//
}

//void stopWiFiAndSleep() {
//  WiFi.disconnect();
//  WiFi.mode(WIFI_OFF);
//  WiFi.forceSleepBegin();
//  delay(1);
//}

void pulse( int serpin,int angle)
{
  int width;//
  width=(angle*11)+500;//
  digitalWrite(serpin,HIGH);//
  delayMicroseconds(width);//
  digitalWrite(serpin,LOW);//
  delay(20-width/1000);
}
