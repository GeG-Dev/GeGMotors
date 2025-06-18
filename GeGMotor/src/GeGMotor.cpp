#include "Arduino.h"
#include "GeGMotor.h"

ZK5AD::ZK5AD(uint8_t SpdPin1, uint8_t SpdPin2) {
  SpeedPins[0] = SpdPin1;
  SpeedPins[1] = SpdPin2;

  for (uint8_t i = 0; i < 2; i++) {
    pinMode(SpeedPins[i], OUTPUT);
  }
}
void ZK5AD::setSpeed(uint8_t newSpeed) {
  speed = newSpeed;
}

void ZK5AD::Forward(uint8_t newSpeed) {
  speed = newSpeed;
  Forward();
}
void ZK5AD::Backward(uint8_t newSpeed) {
  speed = newSpeed;
  Backward();
}

void ZK5AD::Forward() {
  analogWrite(SpeedPins[0], speed);
  analogWrite(SpeedPins[1], 0);
}
void ZK5AD::Backward() {
  analogWrite(SpeedPins[0], 0);
  analogWrite(SpeedPins[1], speed);
}

void ZK5AD::Stop() {
  analogWrite(SpeedPins[0], 0);
  analogWrite(SpeedPins[1], 0);
}
void ZK5AD::Breaking() {
  analogWrite(SpeedPins[0], 255);
  analogWrite(SpeedPins[1], 255);
}
void ZK5AD::autoRun(int16_t newSpeed) {
  newSpeed = constrain(newSpeed, -255, 255);
  smoothMove(interval, newSpeed);
}

void ZK5AD::smoothMove(uint8_t interval, int speedMax) {
  if (millis() - smoothTmr >= interval) {
    smoothTmr = millis();

    if (speedMax > speed) {
      speed += acceler;
      if (speed > speedMax) speed = speedMax;
    } else if (speedMax < speed && speed > 0) {
      speed -= stopAcceler;
      if (speed < speedMax) speed = speedMax;
    } else if (speedMax < speed && speed <= 0) {
      speed -= acceler;
      if (speed < speedMax) speed = speedMax;
    }
  }

  if (speed > 0) {
    analogWrite(SpeedPins[0], speed);
    analogWrite(SpeedPins[1], 0);
  } else if (speed < 0) {
    analogWrite(SpeedPins[0], 0);
    analogWrite(SpeedPins[1], -speed);
  } else {
    analogWrite(SpeedPins[0], 0);
    analogWrite(SpeedPins[1], 0);
  }
}
void ZK5AD::smoothStop(uint8_t interval) {
  if (millis() - smoothTmr >= interval) {
    smoothTmr = millis();

    if (speed > 0) {
      speed -= stopAcceler;
      if (speed < 0) speed = 0;
    }
    if (speed < 0) {
      speed += stopAcceler;
      if (speed > 0) speed = 0;
    }
  }
}

void ZK5AD::smoothSettings(uint8_t MSinterval, uint8_t acceleration, uint8_t stopAcceleration) {
  interval = MSinterval;
  acceler = acceleration;
  stopAcceler = stopAcceleration;
}
int ZK5AD::getSpeed(){
  return speed;
}



L298N::L298N(uint8_t PWM, uint8_t IN1, uint8_t IN2) {
  PWMpin = PWM;
  pinMode(PWMpin, OUTPUT);

  digitPins[0] = IN1;
  digitPins[1] = IN2;

  for (uint8_t i = 0; i < 2; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitPinsState[i] = 0;
  }
}
void L298N::setSpeed(uint8_t newSpeed) {
  spd = newSpeed;
  analogWrite(PWMpin , spd);
}


void L298N::Forward(uint8_t newSpeed) {
  spd = newSpeed;
  Forward();
}
void L298N::Backward(uint8_t newSpeed) {
  spd = newSpeed;
  Backward();
}

void L298N::digitalWritePinState() {
  digitalWrite(digitPins[0], digitPinsState[0]);
  digitalWrite(digitPins[1], digitPinsState[1]);
}


void L298N::Forward() {
  analogWrite(PWMpin, spd);
  digitPinsState[0] = 1;
  digitPinsState[1] = 0;


  digitalWritePinState();
}
void L298N::Backward() {
  analogWrite(PWMpin, spd);
  digitPinsState[0] = 0;
  digitPinsState[1] = 1;

  digitalWritePinState();
}

void L298N::Stop() {
  digitPinsState[0] = 0;
  digitPinsState[1] = 0;

  digitalWritePinState();
}
void L298N::RSTPWM() {
  analogWrite(PWMpin, spd);
}
int L298N::getSpeed(){
  return spd;
}

void L298N::autoRun(int16_t newSpeed) {
  newSpeed = constrain(newSpeed, -255, 255);
  smoothMove(interval, newSpeed);
}

void L298N::smoothMove(uint8_t interval, int speed) {
  if (millis() - smoothTmr >= interval) {
    smoothTmr = millis();

    if (speed > spd) {
      spd += acceler;
      if (spd > speed) spd = speed;
    } else if (speed < spd && spd > 0) {
      spd -= stopAcceler;
      if (spd < speed) spd = speed;
    } else if (speed < spd && spd <= 0) {
      spd -= acceler;
      if (spd < speed) spd = speed;
    }
  }

  if (spd > 0) {
    digitPinsState[0] = 1;
    digitPinsState[1] = 0;
  } else if (spd < 0) {
    digitPinsState[0] = 0;
    digitPinsState[1] = 1;
  } else {
    digitPinsState[0] = 0;
    digitPinsState[1] = 0;
  }

  analogWrite(PWMpin, abs(spd));
  digitalWritePinState();
}
void L298N::smoothStop(uint8_t interval) {
  if (millis() - smoothTmr >= interval) {
    smoothTmr = millis();

    if (spd > 0) {
      spd -= stopAcceler;
      if (spd < 0) spd = 0;
    }
    if (spd < 0) {
      spd += stopAcceler;
      if (spd > 0) spd = 0;
    }
  }
}

void L298N::smoothSettings(uint8_t MSinterval, uint8_t acceleration, uint8_t stopAcceleration) {
  interval = MSinterval;
  acceler = acceleration;
  stopAcceler = stopAcceleration;
}
