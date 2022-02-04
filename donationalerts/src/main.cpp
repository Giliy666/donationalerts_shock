//https://forum.arduino.cc/t/api-with-bearer-authentication/672242 - исходник
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Вводим имя и пароль точки доступа
const char* ssid = "Giliy666";
const char* password = "3216789q";

const String endpoint2 = "https://www.donationalerts.com/api/v1/alerts/donations";

const String Name ="Authorization";
const String Token ="Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiJ9.eyJhdWQiOiI4NzAzIiwianRpIjoiNjU1YjEyZDdlYjllYmQ3Yzg3NjQzM2JiMTU2MWFkZjFhODQ3YWQ3NmJiNDc0ZjZmMTU0Nzg3N2JjM2FhM2U0ZTQxM2VmNzI0NTE2MmU5NDEiLCJpYXQiOjE2NDM5NjU0NDUsIm5iZiI6MTY0Mzk2NTQ0NSwiZXhwIjoyMjc1MTE3NDQ1LCJzdWIiOiI2NjMwMzA3Iiwic2NvcGVzIjpbIm9hdXRoLXVzZXItc2hvdyIsIm9hdXRoLWRvbmF0aW9uLXN1YnNjcmliZSIsIm9hdXRoLWRvbmF0aW9uLWluZGV4Iiwib2F1dGgtY3VzdG9tX2FsZXJ0LXN0b3JlIiwib2F1dGgtZ29hbC1zdWJzY3JpYmUiLCJvYXV0aC1wb2xsLXN1YnNjcmliZSJdfQ.TELBniIUhzvnCDs5_YL8iaXMRI1G1k8GiivbnFXNhuurycmdEoTqPjp9bo28sNHY5psj3EsUvu-iqiVl4t7l0RwVzCJdqmVRBCJAqdbx6HIrVSgY8aR5mwoFWLA-vxEJ19CCfazrInmVGdQa5IV5LXoZ8FL-rBS3f6yNei_FW20FEUnvdZu79vHT-KhYJfBWP8b_RRRjz7CWuFQsHtRql2kXUJoCZqkMnEdOtZtRSERKzdFQqn_wP6ElsB1zn3LuICgXe59oEGz6JNAFi-RCSXjz8isrREgZqLrD3TNmotv3kpEhWOs155DgbETvw6cQFug1xM1GsJx6DNKKD8FXkl4A8RzhhAVo5NTgdJrtADdOGJxlZsQapGD81CIChw7W1RFBgbh-J-yIMtmAcYaFAJ1yJTmMxfJitSrgXLywoxr0SLsRyFSHVcB3EeCtbFth2ZQMO62GGmr9rfVj47kPzhl4JCkhxBo_mJzhyIYd1izj1MRIO2ro2h4Y1aVjb3lJIi3vW54zpwj91hXvFSIGEmIEuVS4eBH198iA6bveSf5gBvYTqWbRHJO1ZR_8J2AY-0RuUo__Cnw8pk8_Js3XtRZzKZpfNR9Uo5F1uqDFnVeNxeiikWCSd2B1aqKgiBQiy5WMQQASybH4IVI818HCSYtONZqYzfbfHEIJNGXq4G8";

const String find = "data-alert_type=\"1\"";


void handleReceivedMessage(String message) {
  DynamicJsonDocument doc(100000);    //Memory pool. Поставил наугад для демонстрации

  DeserializationError error = deserializeJson(doc, message);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

  Serial.println();
  Serial.println("----- donationalerts ----");

  int Donats = doc["meta"]["total"];
  Serial.print("Колличество донатов: ");
  Serial.println(Donats);

  String username = doc["data"][0]["username"];
  Serial.print("Имя пользователя: ");
  Serial.println(username);

  String amount = doc["data"][0]["amount"];
  Serial.print("Размер доната: ");
  Serial.println(amount);

  Serial.println("----- donationalerts ----");
}



void setup() {
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println(" ");
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Конектимся к WIFI c IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Задержка включения 5 секунд");
}


void loop()
{
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      http.begin(endpoint2);
      
      http.addHeader(Name,Token);
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        //Serial.println(payload);
        handleReceivedMessage(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    //Serial.println("All read--------------------------------------------");
    Serial.println(" ");
    delay(1000);
  
}