//http://developer.alexanderklimov.ru/arduino/esp32/webclient.php
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Вводим имя и пароль точки доступа
const char* ssid = "Giliy666";
const char* password = "3216789q";



const String endpoint = "https://www.donationalerts.com/widget/lastdonations?alert_type=1,7,10,12&limit=10000&token=6pc1ZoinN5Y1hIwcz4a7";
const String key1 = "1,4,6,8,7,10,9,3,2,5,11,12,13,14,15,16,17,18,19,20";  //фильтр
const String key2 = "10000000000"; //кол-во выводов
const String key3 = "6pc1ZoinN5Y1hIwcz4a7"; //токен аккаунта

const String find = "data-alert_type=\"1\"";

String find2="";

void setup() 
{
   // создаем объект для работы с HTTP
  Serial.begin(115200);
  
  // делаем небольшую задержку на открытие монитора порта
  delay(5000);
  
  // подключаемся к Wi-Fi сети
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(3000);
    Serial.println("Соединяемся с Wi-Fi..");
  }

  Serial.println("Соединение с Wi-Fi установлено");
}

void loop() 
{
    HTTPClient http;
    http.begin(endpoint);    
    
    int httpCode = http.GET();  // Делаем запрос
    Serial.println(httpCode);

    // проверяем успешность запроса
    if (httpCode > 0)
    { 
      String payload = http.getString();  
      
      //Serial.println(payload);
      int a=payload.indexOf(find);
      int b=payload.lastIndexOf(find)+find.length();

      if (a>0 && b>0)
      {
        Serial.println(payload.substring(a,b));  
      }            
      Serial.println(a);
      Serial.println(b);
      payload.clear();

    }
    else 
    {
      Serial.println("Ошибка HTTP-запроса");
    }
 
    http.end(); // освобождаем ресурсы микроконтроллера
    
    delay(5000);

}