#include <GeGMotor.h>

//---------------------------обязательно ПВМ пины!!!!!!!!!!!!-------------------------
#define inOne 3
#define inTwo 11

#define smoothInterv 20   //интервал ускорения (в МС)
#define acceleration 5  //ускорение (работает при движении вперед и назад)(число на которое будет увеличиваться скорость каждые smoothInterv миллисекунд)
#define accelerationStop 15 // то же самое что и acceleration  но для тормозов 

ZK5AD motor1( inOne , inTwo);

int speed = 200;

void setup(){
  Serial.begin(9600);

  motor1.setSpeed(speed);//устанавливаем скорость
  
  motor1.Forward();//вперед едем 1 сек (движение НЕ плавное!!!)
  delay(1000);
  motor1.Backward();//назад едем 1 сек (движение НЕ плавное!!!)
  delay(1000);


  motor1.smoothMove(smoothInterv , speed);// плавно едем вперед (smoothInterv - насколько быстро будем ускорятся до заданной скорости чем больше smoothInterv тем медленее разгон)
  delay(1000);
  motor1.smoothMove(smoothInterv , -speed);// плавно едем назад ()
  delay(1000);


  motor1.smoothStop(smoothInterv); //плавное торможение (аналог smoothMove) 
  delay(1000);

  motor1.smoothSettings(smoothInterv , acceleration , accelerationStop);
  motor1.autoRun(speed);//движемся вперед плавно
  delay(1000);
  motor1.autoRun(-speed);//движемся назад плавно
  delay(1000);

  motor1.autoRun(0);//плавная остановка

  int i = motor1.getSpeed(); //читаем скорость
  Serial.println(i);  //выводим ее

  speed += 10;//увеичиваем скорость
  motor1.setSpeed(speed); //устанавливаем скорость
  
  int j = motor1.getSpeed(); //читаем скорость
  Serial.println(j);  //выводим ее
}

void loop(){
    //тут может быть ваш код
}