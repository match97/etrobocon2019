#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ev3api.h"

#include "Clock.h"
#include "ColorSensor.h"
#include "Motor.h"
#include "TouchSensor.h"

/*
 * touch_sensor = EV3_PORT_1;
 * sonar_sensor = EV3_PORT_2;
 * color_sensor = EV3_PORT_3;
 * gyro_sensor  = EV3_PORT_4;
 *
 * left_motor   = EV3_PORT_C;
 * right_motor  = EV3_PORT_B;
 * lift_motor   = EV3_PORT_A;
 * tail_motor   = EV3_PORT_D;
 */

unsigned struct HsvStatus {
  //色相 範囲(0~360)
  double hue;
  //彩度 範囲(0~100)
  double saturation;
  //明度 範囲(0~100)
  double value;
};

using namespace ev3api;

class Controller {
 public:
  Controller();
  TouchSensor touchSensor;
  ColorSensor colorSensor;
  Clock clock;
  // モータ入力電圧の最大値
  static constexpr int MOTOR_PWM_MAX = 100;
  // モータ入力電圧の最小値
  static constexpr int MOTOR_PWM_MIN = -100;

  void speakerSetVolume(int volume);
  void ledSetColorOrange();
  void ledSetColorGreen();
  int getBrightness();
  static void speakerPlayToneFS6(int duration);
  bool buttonIsPressedBack();
  bool buttonIsPressedUp();
  bool buttonIsPressedDown();
  bool buttonIsPressedRight();
  bool buttonIsPressedLeft();
  bool buttonIsPressedEnter();
  static float getBatteryVoltage();
  static void tslpTsk(int time);  // 4msec周期起動
  void getRawColor(int& r, int& g, int& b);
  void convertHsv(int &r, int &g, int &b); // RGBをHSV変換する
  HsvStatus getHsv();
  static void lcdFillRect(int x, int y, int h);
  static void lcdDrawString(const char* str, int x, int y);
  static void lcdSetFont();
  int getLeftMotorCount();
  int getRightMotorCount();
  void setLeftMotorPwm(const int pwm);
  void setRightMotorPwm(const int pwm);

 private:
  rgb_raw_t rgb;
  HsvStatus hsv;
  Motor liftMotor;
  Motor rightWheel;
  Motor leftWheel;
  Motor tailMotor;

  static int suppressPwmValue(const int value);
};
#endif