#include <Arduino.h>

#define VOLTAGE_PIN 25  // Пин для подачи напряжения
#define GROUND_PIN 26   // Пин для подключения к земле через известный резистор

#define KNOWN_RESISTOR 10000  // Значение известного резистора в Омах

// Массив пинов для измерения напряжения
const int measurePins[] = {25, 26, 27, 32, 33, 34, 35, 36};

// Под вопросом - подключение по WiFi, возможно, имеются ограничения, рекомендуют использовать только 32, 33, 34, 35, 36, 39.
// Проверить работоспособность 25, 26, 27, 32, 33, 34, 35, 36.
// Однако, в любом случае, следует использовать bluetooth подключение, WiFi коннект - вариант не лучший(WiFi подключение может быть только одно, мобильный интернет также пропадает, если появляется WiFi подключение).
// ОДНАКО, для Bluetooth нужно приложения для телефона, а для WiFi достаточно захостить сайт на самой esp32

// Определяем количество пинов в массиве
const int numPins = sizeof(measurePins) / sizeof(measurePins[0]);

void setup() {
  Serial.begin(115200);
  pinMode(VOLTAGE_PIN, OUTPUT);
  pinMode(GROUND_PIN, OUTPUT);
  digitalWrite(GROUND_PIN, LOW);

  // Настройка пинов для измерения напряжения
  for (int i = 0; i < numPins; i++)
    pinMode(measurePins[i], INPUT);
}

void loop() {
  // Подаем напряжение на измеряемые резисторы
  digitalWrite(VOLTAGE_PIN, HIGH);

  // Ждем немного, чтобы напряжение стабилизировалось
  delay(10);

  // Измеряем напряжение на каждом пине
  for (int i = 0; i < numPins; i++) 
{
    int adcValue = analogRead(measurePins[i]);

    // Преобразуем значение АЦП в напряжение
    float voltage = (adcValue * 3.3) / 4095.0;

    // Вычисляем сопротивление
    float resistance = (KNOWN_RESISTOR * voltage) / (3.3 - voltage);

    // Выводим результат
    Serial.print("Pin ");
    Serial.print(measurePins[i]);
    Serial.print(": ADC Value: ");
    Serial.print(adcValue);
    Serial.print("  Voltage: ");
    Serial.print(voltage);
    Serial.print(" V  Resistance: ");
    Serial.print(resistance);
    Serial.println(" Ohm");
  }

  // Выключаем напряжение
  digitalWrite(VOLTAGE_PIN, LOW);

  // Частота опроса
  delay(1000);
}
