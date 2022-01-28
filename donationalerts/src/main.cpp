//http://developer.alexanderklimov.ru/arduino/esp32/webclient.php
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Вводим имя и пароль точки доступа
const char* ssid = "Giliy666";
const char* password = "3216789q";

const String endpoint = "https://www.donationalerts.com/widget/lastdonations?alert_type=1,4,6,8,7,10,9,3,2,5,11,12,13,14,15,16,17,18,19,20&limit=10000000000&token=6pc1ZoinN5Y1hIwcz4a7";
const String key = "yourAPIkey";

void setup() {

  Serial.begin(115200);
  
  // делаем небольшую задержку на открытие монитора порта
  delay(5000);
  
  // подключаемся к Wi-Fi сети
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Соединяемся с Wi-Fi..");
  }

  Serial.println("Соединение с Wi-Fi установлено");
}

void loop() {
  // выполняем проверку подключения к беспроводной сети
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    // создаем объект для работы с HTTP
    HTTPClient http;
    // подключаемся к веб-странице OpenWeatherMap с указанными параметрами
    http.begin(endpoint + key);
    int httpCode = http.GET();  // Делаем запрос
	
    // проверяем успешность запроса
    if (httpCode > 0) { //Check for the returning code
      // выводим ответ сервера
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
    }
    else {
      Serial.println("Ошибка HTTP-запроса");
    }
 
    http.end(); // освобождаем ресурсы микроконтроллера
  }
  delay(30000);
}