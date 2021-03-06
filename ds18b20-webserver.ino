/*
===========================================
programma di log in caldaia
legge tre sensori di temperatura ds18b20
===========================================
*/
//#include <SPI.h>
#include <UIPEthernet.h>
#include <DS18B20MED.h>

#define SENSOR_A  9 
#define SENSOR_B  8 
#define SENSOR_C  7 

// settaggio ethernet
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //????
//char server[] = "192.168.1.45"; 
IPAddress ip(192, 168, 1, 211); // controllare che non sia doppio
IPAddress gateAway(192, 168, 1, 254);
IPAddress DNS(8, 8, 8, 8);
//settaggio sensore
char temp_string_a[7];
char temp_string_b[7];
char temp_string_c[7];
long shortLoop = 100;
//long shortDelay = 100;
int lettTodo = 10;

EthernetServer server(80);
DS18B20MED mytest (shortLoop, lettTodo);

void setup() {
  // Set up the data pins for communication with DS18B20 sensors
  digitalWrite(SENSOR_A, LOW);
  pinMode(SENSOR_A, INPUT);
  digitalWrite(SENSOR_B, LOW);
  pinMode(SENSOR_B, INPUT);
  digitalWrite(SENSOR_C, LOW);
  pinMode(SENSOR_C, INPUT);
  
  // give the Ethernet shield a second to initialize:
  delay(1000);
  //Serial.begin(9600);
  // start the Ethernet connection:
  Ethernet.begin(mac, ip, DNS, gateAway);
  server.begin();
  }
void loop() {
  EthernetClient client = server.available();
  if (client) {
    //Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        //Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          mytest.DataConv (mytest.lettCycle(SENSOR_A), temp_string_a);
          client.print("temp A ");
          client.print(temp_string_a);
          mytest.DataConv (mytest.lettCycle(SENSOR_B), temp_string_b);
          client.print(" temp B ");
          client.print(temp_string_b);
          mytest.DataConv (mytest.lettCycle(SENSOR_C), temp_string_c);
          client.print(" temp C ");
          client.print(temp_string_c);
          client.println("<br />");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    //Serial.println("client disconnected");
  } 
}



