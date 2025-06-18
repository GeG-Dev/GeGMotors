#include <GeGMotor.h>

//------------------------мотор 1    PWM пины --------------
#define inOne 3
#define inTwo 11
//------------------------мотор 2     PWM пины --------------
#define inThree 10
#define inFour 9

#define smoothInterv 20   //интервал ускорения (в МС)
#define acceleration 5  //ускорение (работает при движении вперед и назад)(число на которое будет увеличиваться скорость каждые smoothInterv миллисекунд)
#define accelerationStop 15 // то же самое что и acceleration  но для тормозов 

ZK5AD motor1( inOne , inTwo);
ZK5AD motor2( inThree , inFour);

int speed = 200;

void setup(){
  motor1.smoothMove(smoothInterv , speed);// плавно едем вперед >1мотор< (smoothInterv - насколько быстро будем ускорятся до заданной скорости чем больше smoothInterv тем медленее разгон)
  delay(1000);
  motor2.smoothMove(smoothInterv , -speed);// плавно едем назад >2мотор<
  delay(1000);


  motor1.smoothStop(smoothInterv); //плавное торможение (аналог smoothMove)  мотор 1 
  motor2.smoothStop(smoothInterv); //плавное торможение (аналог smoothMove)  мотор 2
  delay(1000);


  motor1.smoothSettings(smoothInterv , acceleration , accelerationStop);

  
  motor1.autoRun(speed);//движемся вперед плавно мотор 1
  delay(1000);
  motor2.autoRun(-speed);//движемся назад плавно мотор 2
  delay(1000);

  motor1.smoothStop(accelerationStop); //плавная остановка мотор 1
  motor2.smoothStop(accelerationStop); //плавная остановка мотор 2
}

void loop(){
    //тут может быть ваш код
}