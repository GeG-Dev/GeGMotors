#include <stdint.h>
#include "Arduino.h"

#ifndef GEGMOTOR_H
#define GEGMOTOR_H

class L298N {  //----------------------------------------драйвер L298N-----------------------------------
public:
  explicit L298N(uint8_t PWM, uint8_t IN1, uint8_t IN2);  //инициализация

  void setSpeed(uint8_t newSpeed);  //устанавливаем скорость вращения

  void Forward(uint8_t newSpeed);   //движение вперед с установкой скорости
  void Backward(uint8_t newSpeed);  //движение назад с установкой скорости

  void RSTPWM();  //переустанавливаем скорость
  int getSpeed(); // вернет скорость

  void autoRun(int16_t newSpeed);  // вращение с авто выбором направления(вперед\назад\стоп) (значения от - 255 до 255)


  void Forward();   // вперед без установки скорости(НЕ плавно!!!!!!!!)
  void Backward();  //назад  без установки скорости(НЕ плавно!!!!!!!!)
  void Stop();      // остановка(НЕ плавно!!!!!!)

  void smoothMove(uint8_t interval, int speed);  // планое движение вперед\назад
  void smoothStop(uint8_t interval);             // плавная остановка

  void smoothSettings(uint8_t MSinterval = 10, uint8_t acceleration = 5, uint8_t stopAcceleration = 15); /* настройки плавного движения:

  MSinterval - установка интервала смены скорости --- например MSinterval = 10 acceleration = 5, для смены скорости с 0 до 40 пройдет 80 мс ---- delay не стоит использовать -------- 
  acceleration - установка ускорения т.е. на сколько будет увеличиваться при движении вперед и уменьшаться при движении назад скорость каждый цикл
  stopAcceleration то же самое что и acceleration но для торможения ------- используется в smoothMove , autoRun , smoothStop


*/
private:
  void digitalWritePinState();  //----------устанавливаем пины------
  uint8_t PWMpin = 0;           // --------хранит пин пвм(без него плавного движения не будет)------
  uint8_t digitPins[2];         // цифровые пины(можно использовать аналоговые) - хранят до 2х пинов к которым подключен драйвер пример: IN1 - IN2\IN3 - IN4\IN2 - IN3 и тд
  uint8_t digitPinsState[2];    // хранит состояние пинов
  uint32_t smoothTmr = 0;       //таймер для плавного движения
  uint8_t interval = 10;        //интервал обновления скорости
  uint8_t acceler = 5;          // хранит значение которое влияет на сколько будет увеличиваться скорость каждое interval миллисекунд
  uint8_t stopAcceler = 15;     //тот же  acceler но для тормаза / остановки

  int spd = 90;  // скорость
};

class ZK5AD {  //--------------------------драйвер zk - 5AD
public:
  explicit ZK5AD(uint8_t SpdPin1, uint8_t SpdPin2);  // инициализация драйвера


  void setSpeed(uint8_t newSpeed);  //устанавливаем скорость вращения

  void Forward(uint8_t newSpeed);   //движение вперед с установкой скорости
  void Backward(uint8_t newSpeed);  //движение назад с установкой скорости

  void Forward();   // вперед без установки скорости(не плавно но драйвер сам по себе плавнее L298N)
  void Backward();  //назад  без установки скорости(не плавно но драйвер сам по себе плавнее L298N)
  void Stop();      // остановка(не плавно но драйвер сам по себе плавнее L298N и торможение занимает чуть больше времени так же как и вижение вперед\назад)
  void Breaking();  // торможение - аналог остановки но в случае со Stop питание с мотора убераем а в этом случае подаем питание на оба контакта мотора ------ очень резкое торможение но может нагревать драйвер при частом использовании(увеличится энергопотребление по сравнению со Stop)


  void autoRun(int16_t newSpeed);  // вращение с авто выбором направления(вперед\назад\стоп) (значения от - 255 до 255)
  int getSpeed(); // вернет скорость

  //-------------------------------------то же самое что и в L298N-------------------------
  void smoothMove(uint8_t interval, int speed);
  void smoothStop(uint8_t interval);

  void smoothSettings(uint8_t MSinterval = 10, uint8_t acceleration = 5, uint8_t stopAcceleration = 15);
  //---------------------------------------------------------------------------------------
private:
  uint8_t SpeedPins[2];          // хранит пины - только ПВМ (иначе плавности не будет)
  uint32_t smoothTmr = 0;  //таймер плавного движения
  //---------тоже самое что и в L298N---------
  uint8_t interval = 10;
  uint8_t acceler = 5;
  uint8_t stopAcceler = 15;
  //----------------------------
  int speed = 90;  // скорость
};



#endif
