#include <ESP8266WiFi.h>
 /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~For Static IP ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
const char* ssid = "**your SSID **";
const char* password = "**Your routr password**";
IPAddress ip(192, 168, 1, 10); //set static ip
IPAddress gateway(192, 168, 1, 1); //set getteway
IPAddress subnet(255, 255, 255, 0);//set subnet
 
int ledPin = D3;
/*int ledPin2 = D2;
int ledPin3 = D3;
int ledPin4 = D4;
int ledPin5 = D5;
int ledPin6 = D6;*/

WiFiServer server(80);
 
void setup() {
  Serial.begin(9600);
  delay(10);
 
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connect to WiFi network
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
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED=OFF") != -1){
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
 
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html><font size=72>");
 
  client.print("Led pin is now: ");
 
  if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/LED=ON\">here</a> Turn relay ON<br>");
  client.println("Click <a href=\"/LED=OFF\">here</a> Turn relay OFF<br>");
  
  client.println("</font></html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
