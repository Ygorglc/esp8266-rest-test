
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "YGORR";
const char* password = "12345ygor";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://93.188.161.151:8085/defeito-motor-eletrico/v1/dados/dados-brutos";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

float aceleracao_eixo_x = 0; 
float aceleracao_eixo_y = 0;
float aceleracao_eixo_z = 0;
float giro_eixo_x = 0;
float giro_eixo_y = 0;
float giro_eixo_z = 0;
float tempo = 0;
int posicao = 1;
int idTeste = 1;
void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);

      // Specify content-type header
//      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
//      // Data to send with HTTP POST
//      String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&value1=24.25&value2=49.54&value3=1005.14";           
//      // Send HTTP POST request
//      int httpResponseCode = http.POST(httpRequestData);
      
       //If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      String httpRequestDataObjectJson = "{\"aceleracao_eixo_x\": \""+String(aceleracao_eixo_x)+"\",";
             httpRequestDataObjectJson +="\"aceleracao_eixo_y\": \""+String(aceleracao_eixo_y)+"\",";
             httpRequestDataObjectJson += "\"aceleracao_eixo_z\": \""+String(aceleracao_eixo_z)+"\",";
             httpRequestDataObjectJson += "\"giro_eixo_x\": \""+String(giro_eixo_x)+"\",";
             httpRequestDataObjectJson += "\"giro_eixo_y\": \""+String(giro_eixo_y)+"\",";
             httpRequestDataObjectJson += "\"giro_eixo_z\": \""+String(giro_eixo_z)+"\",";
             httpRequestDataObjectJson += "\"tempo\": \""+String(tempo)+"\",";
             httpRequestDataObjectJson += "\"posicao\": \""+String(posicao)+"\",";
             httpRequestDataObjectJson += "\"idTeste\": \""+String(idTeste)+"\"}";
      Serial.println(httpRequestDataObjectJson);                                  
      //String httpRequestDataObjectJson = "{\"descricao\":\"teste-esp8266-rest-post\"}";
      int httpResponseCode = http.POST(httpRequestDataObjectJson);

      // If you need an HTTP request with a content type: text/plain
      //http.addHeader("Content-Type", "text/plain");
      //int httpResponseCode = http.POST("Hello, World!");
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
