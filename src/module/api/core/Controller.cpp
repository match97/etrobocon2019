
#include "Controller.h"

Controller::Controller()
    : touchSensor(PORT_1),
      colorSensor(PORT_3),
      liftMotor(PORT_A),
      rightWheel(PORT_B),
      leftWheel(PORT_C),
      tailMotor(PORT_D) {
  colorSensor.getRawColor(rgb);
}

void Controller::speakerSetVolume(int volume) {
  ev3_speaker_set_volume(volume);
}

void Controller::speakerPlayToneFS6(int duration) {
  ev3_speaker_play_tone(NOTE_FS6, duration);
}

void Controller::ledSetColorOrange() { ev3_led_set_color(LED_ORANGE); }

void Controller::ledSetColorGreen() { ev3_led_set_color(LED_GREEN); }

bool Controller::buttonIsPressedBack() {
  return ev3_button_is_pressed(BACK_BUTTON);
}

bool Controller::buttonIsPressedEnter() {
  return ev3_button_is_pressed(ENTER_BUTTON);
}

bool Controller::buttonIsPressedUp() {
  return ev3_button_is_pressed(UP_BUTTON);
}

bool Controller::buttonIsPressedDown() {
  return ev3_button_is_pressed(DOWN_BUTTON);
}

bool Controller::buttonIsPressedRight() {
  return ev3_button_is_pressed(RIGHT_BUTTON);
}

bool Controller::buttonIsPressedLeft() {
  return ev3_button_is_pressed(LEFT_BUTTON);
}

float Controller::getBatteryVoltage() { return ev3_battery_voltage_mV(); }

int Controller::getBrightness() {
  colorSensor.getRawColor(rgb);
  int luminance = 0.298912 * rgb.r + 0.586611 * rgb.g + 0.114478 * rgb.b;
  return luminance;
}

void Controller::getRawColor(int& r, int& g, int& b) {
  colorSensor.getRawColor(rgb);
  r = rgb.r;
  g = rgb.g;
  b = rgb.b;
}

void Controller::tslpTsk(int time) { tslp_tsk(time); }

void Controller::lcdFillRect(int x, int y, int h) {
  ev3_lcd_fill_rect(x, y, EV3_LCD_WIDTH, h, EV3_LCD_WHITE);
}

void Controller::lcdDrawString(const char* str, int x, int y) {
  ev3_lcd_draw_string(str, x, y);
}

void Controller::lcdSetFont() { ev3_lcd_set_font(EV3_FONT_SMALL); }

int Controller::getLeftMotorCount(){
  return leftWheel.getCount();
}

int Controller::getRightMotorCount(){
  return rightWheel.getCount();
}

int Controller::suppressPwmValue(const int value){
  if(value > MOTOR_PWM_MAX){
    return MOTOR_PWM_MAX;
  }else if(value < MOTOR_PWM_MIN){
    return MOTOR_PWM_MIN;
  }
  return value;
}

void Controller::setLeftMotorPwm(const int pwm){
  leftWheel.setPWM(suppressPwmValue(pwm));
}

void Controller::setRightMotorPwm(const int pwm){
  rightWheel.setPWM(suppressPwmValue(pwm));
}

void Controller::convertHsv(int& r, int& g, int& b)
{
  // r,g,bの最大値を求める
  double max = r;
  if(max < g) max = g;
  if(max < b) max = b;

  // r,g,bの最小値を求める
  double min = r;
  if(min > g) min = g;
  if(min > b) min = b;

  // 色相(hue)を求める

  // 3つが同値の時は色相(hue)は０
  if(r == g && r == b) {
    hsv.hue = 0;
  }

  // rが最大値の場合
  else if(max == r) {
    hsv.hue = 60 * ((g - b) / (max - min));
  }

  // gが最大値の場合
  else if(max == g) {
    hsv.hue = 60 * ((b - r) / (max - min)) + 120;
  }

  // bが最大値の場合
  else if(max == b) {
    hsv.hue = 60 * ((r - g) / (max - min)) + 240;
  }

  //求められた色彩(hue)がマイナス値だった場合は360を加算して0～360の範囲に収める
  if(hsv.hue < 0) {
    hsv.hue += 360;
  }

  // 彩度(saturation)を求める
  hsv.saturation = (max - min) / max * 100;

  // 明度(value)を求める
  hsv.value = max / 255 * 100;
}

HsvStatus Controller::getHsv()
{
  return hsv;
}  // hsv値を返す

