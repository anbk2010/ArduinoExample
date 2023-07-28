#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Rotary Encoder Inputs
#define re1_clk_pin 12
#define re1_dt_pin 13
#define re1_sw_pin 9

#define m1_step_pin 2
#define m1_direction_pin 5
#define m1_enable_pin 8

int level_1 = 0;
int current_clk_1;
int previous_clk_1;
int re1_sw_value;

int step_state_1 = 0;
int m1_direction = 0;

void setup() {
  Serial.begin(9600);
  // Set encoder pins as inputs
  pinMode(re1_clk_pin, INPUT);
  pinMode(re1_dt_pin, INPUT);

  pinMode(m1_enable_pin, OUTPUT);     //enable pin
  pinMode(m1_step_pin, OUTPUT);       //step pin
  pinMode(m1_direction_pin, OUTPUT);  //direction pin

  // Setup LCD Monitor
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Lvl: ");

  lcd.setCursor(0, 1);
  lcd.print("Step: ");

  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previous_clk_1 = digitalRead(re1_clk_pin);
}

void loop() {
  //print_level(level_1);
  // lcd.setCursor(0, 0);
  // lcd.print("Lvl: ");

  if (level_1 < 0) {
    level_1 = 0;
    for (int i = 0; i < 3; i++) {
      lcd.setCursor(6, 0);
      lcd.print(" ");
      delay(200);
      lcd.setCursor(6, 0);
      lcd.print(level_1);
      delay(200);
    }
  } else {
    lcd.setCursor(6, 0);
    lcd.print(level_1);
  }

  // Read the current state of inputCLK
  current_clk_1 = digitalRead(re1_clk_pin);
  if (current_clk_1 != previous_clk_1) {
    if (digitalRead(re1_dt_pin) != current_clk_1) {
      level_1--;
      //sets x axis direction
      m1_direction = 1;
    } else {
      //sets x axis direction
      m1_direction = 0;
      level_1++;
    }
    step_state_1++;
  }

  // lcd.setCursor(0, 1);
  // lcd.print("Step: ");
  // lcd.setCursor(6, 1);
  // lcd.print(step_state_1);
  // //print_step_state(step_state_1);

  // if (step_state_1 > 0 && level_1 > 0) {
  //   //enable stepper 1
  //   digitalWrite(m1_enable_pin, 0);

  //   //set stepper direction
  //   digitalWrite(m1_direction_pin, m1_direction);

  //   //move_step(m1_enable_pin, m1_direction_pin, m1_direction, m1_step_pin, 1024, 500);
  //   for (int i = 0; i < 128; i++) {
  //     digitalWrite(m1_step_pin, HIGH);
  //     delay(2);

  //     digitalWrite(m1_step_pin, LOW);
  //     delay(2);
  //   }

  //   //disable stepper 1
  //   digitalWrite(m1_enable_pin, 1);
  //   step_state_1--;
  // } else {
  //   step_state_1 = 0;
  // }

  // lcd.setCursor(6, 1);
  // lcd.print(step_state_1);

  // Update previousStateCLK with the current state
  previous_clk_1 = current_clk_1;
}

// void move_step(int state_pin, int direction_pin, int direction_value, int step_pin, int step_number, int delay_time) {

//   enable_stepper(state_pin);
//   set_stepper_direction(direction_pin, direction_value);

//   for (int i = 0; i < step_number; i++) {
//     digitalWrite(step_pin, HIGH);
//     delay(delay_time);
//     digitalWrite(step_pin, HIGH);
//     delay(delay_time);
//   }

//   disable_stepper(state_pin);
// }

// void print_level(int level) {
//   int row_index = 0;
//   int col_index = 6;
//   lcd.setCursor(0, row_index);
//   lcd.print("Lvl: ");

//   lcd.setCursor(col_index, row_index);

//   if (level < 0) {
//     for (int i = 0; i < 3; i++) {
//       lcd.print(" ");
//       delay(200);
//       lcd.print(level);
//     }
//     level = 0;
//   }
//   lcd.print(level);
// }


// void print_step_state(int step_state) {
//   int row_index = 0;
//   int col_index = 6;
//   lcd.setCursor(0, row_index);
//   lcd.print("Lvl: ");
//   lcd.setCursor(col_index, row_index);
//   lcd.print(step_state);
// }

// void enable_stepper(int state_pin) {
//   //enables a4988 stepper drivers, pin 8, 0=enable, 1=disable
//   set_stepper_state(state_pin, 0);
// }


// void set_stepper_direction(int direction_pin, int direction_value) {
//   digitalWrite(direction_pin, direction_value);
// }

// void disable_stepper(int state_pin) {
//   //enables a4988 stepper drivers, pin 8, 0=enable, 1=disable
//   set_stepper_state(state_pin, 1);
// }

// /*
//  * enables a4988 stepper drivers, pin 8, 0=enable, 1=disable
//  */
// void set_stepper_state(int state_pin, int state_value) {
//   //enables a4988 stepper drivers, pin 8, 0=enable, 1=disable
//   digitalWrite(state_pin, state_value);
// }
