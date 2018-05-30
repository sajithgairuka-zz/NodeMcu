#include<ESP8266WiFi.h>

const char* ssid="**Router SSID**";
const char* password="**Your wifi PassWord**";

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
delay(200);

pinMode(4,OUTPUT);// issarahata dakunupaththa moter eka
digitalWrite(4,LOW);
pinMode(2,OUTPUT);// pitipassata dakunupaththa moter eka
digitalWrite(2,LOW);
pinMode(5,OUTPUT);//wampaththe pitipassata
digitalWrite(5,LOW);
pinMode(0,OUTPUT);//wampaththa issarahata
digitalWrite(0,LOW);


Serial.println();
Serial.println();
Serial.print("Your are connecting to:");
Serial.println(ssid);
WiFi.begin(ssid, password);
      
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("");
  Serial.println("WiFi connected");
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
  if (request.indexOf("/forward")!=-1) {
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(2,HIGH);
      digitalWrite(0,HIGH);
  }

  if (request.indexOf("/reverse")!=-1) {
      digitalWrite(2,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(0,LOW);
    }
    if (request.indexOf("/right")!=-1){
      digitalWrite(2,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(4,LOW);
      digitalWrite(0,HIGH);
    }
    if (request.indexOf("/left")!=-1) { 
      digitalWrite(2,HIGH);
      digitalWrite(5,LOW);
      digitalWrite(4,HIGH);
      digitalWrite(0,LOW);

    }
    if (request.indexOf("/stop")!=-1) {
      digitalWrite(2,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4,LOW);
      digitalWrite(0,LOW);
    }
     client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<br><br>");
  client.println("Click <a href=\"/forward\">here</a> FORWORD<br>");
  client.println("Click <a href=\"/reverse\">here</a> REVERSE <br>");
  client.println("Click <a href=\"/right\">here</a> Turn right<br>");
  client.println("Click <a href=\"/left\">here</a> Turn left<br>");
  client.println("Click <a href=\"/stop\">here</a> STOP <br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
  
    }
  

 

