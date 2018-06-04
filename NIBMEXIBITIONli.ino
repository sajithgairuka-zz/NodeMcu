#include<ESP8266WiFi.h>

const char* ssid="**your ssid**";
const char* password="**your password**";
const char* htmlLogin="
<!DOCTYPE html>
<html>
<head>
<script>
function Validate() {
    var uname = document.forms["login"]["uname"].value;
	var pass = document.forms["login"]["pass"].value;
    if (uname == "admin" && pass == "12345") {
        alert("Successful");
        return 1;
    }
	else {
		alert("Failed");
		return 0;
	}
}
</script>
</head>
<body>

<form name="login" action="#" onsubmit="return Validate()" method="post">
Username : <input type="text" name="uname">
Password : <input type="password" name="pass">
<input type="submit" value="Login">
</form>

</body>
</html>"

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
delay(200);
pinMode(D4,OUTPUT);
digitalWrite(D4,LOW);
pinMode(D3,OUTPUT);
digitalWrite(D3,LOW);
pinMode(D2,OUTPUT);
digitalWrite(D2,LOW);
pinMode(D1,OUTPUT);
digitalWrite(D1,LOW);
pinMode(D5,OUTPUT);
digitalWrite(D5,LOW);
pinMode(D6,OUTPUT);
digitalWrite(D6,LOW);
pinMode(D7,OUTPUT);
digitalWrite(D7,LOW);
pinMode(D8,OUTPUT);
digitalWrite(D8,LOW);

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

	client.println(htmlLogin);
  
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
  if (request.indexOf("/ROOM1bulbon")!=-1) {
      digitalWrite(D1,HIGH);   
  }
  if (request.indexOf("/ROOM1bulboff")!=-1) {
      digitalWrite(D1,LOW);   
  }
  if (request.indexOf("/ROOM2bulbon")!=-1) {
      digitalWrite(D2,HIGH);
    }
    if (request.indexOf("/ROOM2bulboff")!=-1) {
      digitalWrite(D2,LOW);
    }
    if (request.indexOf("/ROOM3bulbon")!=-1){
      digitalWrite(D3,HIGH);
    }
     if (request.indexOf("/ROOM3bulboff")!=-1){
      digitalWrite(D3,LOW);
    }
    if (request.indexOf("/ROOM4bulbon")!=-1) { 
      digitalWrite(D4,HIGH);
       }
       if (request.indexOf("/ROOM4bulboff")!=-1) { 
      digitalWrite(D4,LOW);
       }
    if (request.indexOf("/ROOM5bulbon")!=-1) {
      digitalWrite(D5,HIGH);    
      }
      if (request.indexOf("/ROOM5bulboff")!=-1) {
      digitalWrite(D5,LOW);    
      }
     client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<br><br>");
  client.println("<br>ROOM 1<br>");
  client.println("Click to turn on light<a href=\"/ROOM1bulbon\"> here</a><br>");
  client.println("Click to turn off light<a href=\"/ROOM1bulboff\"> here</a><br>");
  client.println("<br><br>");
  client.println("<br>ROOM 2<br>");
  client.println("Click to turn on light <a href=\"/ROOM2bulbon\"> here</a><br>");
  client.println("Click to turn off light<a href=\"/ROOM2bulboff\"> here</a><br>");
   client.println("<br><br>");
  client.println("<br>ROOM 3<br>");
  client.println("Click to turn on light <a href=\"/ROOM3bulbon\"> here</a><br>");
  client.println("Click to turn off light<a href=\"/ROOM3bulboff\"> here</a><br>");
   client.println("<br><br>");
  client.println("<br>ROOM 4<br>");
  client.println("Click to turn on light<a href=\"/ROOM4bulbon\"> here</a><br>");
  client.println("Click to turn off light<a href=\"/ROOM4bulboff\"> here</a><br>");
   client.println("<br><br>");
  client.println("<br>ROOM 5<br>");
  client.println("Click to turn on light<a href=\"/ROOM5bulbon\"> here</a><br>");
  client.println("Click to turn off light<a href=\"/ROOM5bulboff\"> here</a><br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
  
    }
  

 

