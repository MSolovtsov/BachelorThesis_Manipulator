#include <Wire.h>
#include "AS5600.h"

#define IN1 9
#define IN2 8
#define BUTTON 3

AS5600 as5600;  // Создаем объект датчикаx  

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(5, INPUT);
  pinMode(4, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(BUTTON, INPUT);

  Serial.begin(9600);
  Wire.begin();  // Инициализация I2C

  as5600.begin();
  as5600.setDirection(AS5600_CLOCK_WISE); 


  if (!as5600.begin()) {  // Проверка подключения
    Serial.println("AS5600 не найден!");
    while (1);
  }
  Serial.println("AS5600 готов!");

  // Стоп двигателя
  stop_motor();

}

void loop() {

  Serial.println(digitalRead(BUTTON));

  // Чтение угла (0-4096, 12 бит)
    uint16_t angle = as5600.readAngle();  // Чтение угла (0-4095)
    float degrees = angle * 360.0 / 4096; // Перевод в градусы
    Serial.print("Угол: ");
    Serial.println(degrees);

  if (digitalRead(BUTTON) == 0){
      // Открыть схват
      open_fingers();
      //close_fingers();
  
  } else {
      // Закрыть схват
      close_fingers();
      //open_fingers();
  }

  // Отобразить работу драйвера
  print_motor_driver();
  Serial.println("End loop");
}


// Свои фунции
void open_fingers(){

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void close_fingers(){

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void stop_motor(){

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void print_motor_driver(){

  Serial.print("IN1: ");
  Serial.print(digitalRead(5));
  Serial.print("  IN2: ");
  Serial.println(digitalRead(4));
}