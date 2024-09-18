#include <Arduino.h>

// Учитывая, что земля общая, следует использовать диоды, иначе во всех входящих пинах будет максимальное значение одного из питающих пинов 

#define KNOWN_RESISTOR 10000  // Значение известного резистора в Омах

// Массив пинов для измерения напряжения
const int measurePins[] = {25, 26, 27, 32, 33, 34, 35, 36};

// Под вопросом - подключение по WiFi, возможно, имеются ограничения, рекомендуют использовать только 32, 33, 34, 35, 36, 39.
// Проверить работоспособность 25, 26, 27, 32, 33, 34, 35, 36.
// Однако, в любом случае, следует использовать bluetooth подключение, WiFi коннект - вариант не лучший(WiFi подключение может быть только одно, мобильный интернет пропадает, если появляется WiFi подключение).
// ОДНАКО, для Bluetooth нужно приложения для телефона, а для WiFi достаточно захостить сайт на самой esp32(либо телефон подключается к точке доступа esp32, либо наоборот - esp32 к точке доступа телефона)

// 2 пункта выше "Однако" неакутальные - можно сделать точку доступа с телефона и тогда, и интернет, и сайт esp32 будет работает, только нужно сделать статический ip для esp32, и желательно знать его

// Определяем количество пинов в массиве
const int numPins = sizeof(measurePins) / sizeof(measurePins[0]); // 8

void setup() 
{
  Serial.begin(115200);
  
  // Настройка пинов для измерения напряжения
  for (int i = 0; i < numPins; i++)
    pinMode(measurePins[i], INPUT);
}

void loop() 
{
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
