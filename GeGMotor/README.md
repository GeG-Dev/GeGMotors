#GeGMotor

##English

GeGMotor is a simple Arduino library to control motors with L298N or ZK-5AD motor drivers.

---------------------------------------------------------Features---------------------------------------------
Easy control of L298N or ZK-5AD motor drivers.

Supports forward, backward, stop, and smooth acceleration/deceleration.

Compatible with Arduino boards.

Simple API for speed and direction control.

Supported hardware
-----L298N H-Bridge motor driver

-----ZK-5AD PWM motor driver

---------------------------------------------------Example usage-------------------------------------

#include <GeGMotor.h>

// Create motor instances
L298N motorA(3, 4, 5);  // PWM pin, IN1, IN2
ZK5AD motorB(6, 7);     // PWM1, PWM2

void setup() {
  motorA.setSpeed(150);
  motorA.Forward();

  motorB.setSpeed(200);
  motorB.Backward();
}

void loop() {
  // your logic here
}
---------------------------------------------------Installation-------------------------------------------
--------->>>Download the library as ZIP.

In Arduino IDE: Sketch > Include Library > Add .ZIP Library...

Select the downloaded file.

-------------or unzip in documents > Arduino > libraries
-----------------------------------------------------------------------API Reference-----------------------------
------------------------L298N-------------------
L298N(uint8_t pwmPin, uint8_t in1Pin, uint8_t in2Pin);

void setSpeed(uint8_t speed);

void Forward();

void Backward();

void Stop();

void autoRun(int16_t speed);

void smoothMove(uint8_t interval, int speed);

void smoothStop(uint8_t interval);

int getSpeed();
--------------------------------------------------
------------------------ZK5AD--------------------
ZK5AD(uint8_t pwm1Pin, uint8_t pwm2Pin);

void setSpeed(uint8_t speed);

void Forward();

void Backward();

void Stop();


void autoRun(int16_t speed);

void smoothMove(uint8_t interval, int speed);

void smoothStop(uint8_t interval);

int getSpeed();

-------------------------------------------------------------------------License----------------------------------
This library is released under the MIT License.
----------------------------------------------------------------------version----------------------
GeGMotor v0.1.1





-----------------------------------------------------------------------------------------------------------------------

##Русский


GeGMotor — это простая библиотека Arduino для управления двигателями с помощью драйверов двигателей L298N или ZK-5AD.

---------------------------------------------------------Функции---------------------------------------------
Простое управление драйверами двигателей L298N или ZK-5AD.

Поддерживает движение вперед, назад, остановку и плавное ускорение/замедление.

Совместим с платами Arduino.

Простой API для контроля скорости и направления.

Поддерживаемое оборудование
-----L298N Драйвер двигателя H-Bridge

-----ZK-5AD ШИМ-драйвер двигателя

------------------------------------Пример использования-------------------------------------

#include <GeGMotor.h>

// Create motor instances
L298N motorA(3, 4, 5);  // PWM pin, IN1, IN2
ZK5AD motorB(6, 7);     // PWM1, PWM2

void setup() {
  motorA.setSpeed(150);
  motorA.Forward();

  motorB.setSpeed(200);
  motorB.Backward();
}

void loop() {
  // your logic here
}


 ------------------------------------Установка-------------------------------------------
--------->>>Скачайте библиотеку в формате ZIP.

В Arduino IDE: «Скетч» > «Подключить библиотеку» > «Добавить библиотеку .ZIP»...

Выберите загруженный файл.

-------------или разархивируйте в документы > Arduino > библиотеки.
----------------------------------------------------------------------- Функции -----------------------------

------------------------L298N-------------------
L298N(uint8_t pwmPin, uint8_t in1Pin, uint8_t in2Pin);

void setSpeed(uint8_t speed);

void Forward();

void Backward();

void Stop();

void autoRun(int16_t speed);

void smoothMove(uint8_t interval, int speed);

void smoothStop(uint8_t interval);

int getSpeed();
--------------------------------------------------
------------------------ZK5AD--------------------
ZK5AD(uint8_t pwm1Pin, uint8_t pwm2Pin);

void setSpeed(uint8_t speed);

void Forward();

void Backward();

void Stop();


void autoRun(int16_t speed);

void smoothMove(uint8_t interval, int speed);

void smoothStop(uint8_t interval);

int getSpeed();


-------------------------------------------------------------------------Лицензия----------------------------------
Эта библиотека выпущена под лицензией MIT.
----------------------------------------------------------------------версия----------------------
GeGMotor v0.1.1