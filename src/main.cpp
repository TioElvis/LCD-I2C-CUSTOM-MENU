#include "export.h"

// prototypes
unsigned long int read();

void up();
void down();
void enter();
void back();

void select_led();
void turn_on_led();
void turn_off_led();

// main
void setup() {
  Serial.begin(9600);
  IrReceiver.begin(2);

  lcd.init();
  lcd.backlight();

  menu.init();

  // Configure lines with callback functions (main menu)
  line_0_0.set_focusPosition(Position::LEFT);
  line_0_0.attach_function(1, select_led);
  line_0_1.set_focusPosition(Position::LEFT);
  line_0_1.attach_function(1, select_led);
  line_0_2.set_focusPosition(Position::LEFT);
  line_0_2.attach_function(1, select_led);
  line_0_3.set_focusPosition(Position::LEFT);
  line_0_3.attach_function(1, select_led);

  // Configure lines with callback functions (sub menu)
  line_1_0.set_focusPosition(Position::LEFT);
  line_1_0.attach_function(1, turn_on_led);
  line_1_1.set_focusPosition(Position::LEFT);
  line_1_1.attach_function(1, turn_off_led);
  line_1_2.set_focusPosition(Position::LEFT);
  line_1_2.attach_function(1, back);

  menu.add_screen(screen_0);
  menu.add_screen(screen_1);

  screen_0.set_displayLineCount(2);
  screen_1.set_displayLineCount(2);

  menu.set_focusedLine(0);
  menu.update();
}

void loop() {
  button = read();

  if (button == UP)
    up();

  if (button == DOWN)
    down();

  if (button == ENTER)
    enter();

  if (button == BACK)
    back();

  delay(250);
}

// functions
unsigned long int read() {
  unsigned long result = 0;

  if (IrReceiver.decode() == 1) {    
    unsigned long int code = IrReceiver.decodedIRData.decodedRawData;
    result = code;

    IrReceiver.resume();
  }
  
  return result;
}

void up() {
  if (current_line == 1) {
    if (current_menu == 1) {
      menu.set_focusedLine(LINES_MENU_1 - 1);
      current_line = LINES_MENU_1;
    } else if (current_menu == 2) {
      menu.set_focusedLine(LINES_MENU_2 - 1);
      current_line = LINES_MENU_2;
    }
  } else {
    menu.switch_focus(false);
    current_line--;
  }

  menu.update();
}

void down() {
  if (current_menu == 1 && current_line == LINES_MENU_1) {
    menu.set_focusedLine(0);
    current_line = 1;
  } else if (current_menu == 2 && current_line == LINES_MENU_2) {
    menu.set_focusedLine(0);
    current_line = 1;
  } else {
    menu.switch_focus(true);
    current_line++;
  }

  menu.update();
}

void enter() {
  menu.call_function(1);
  delay(100);
}

void back() {
  if (current_menu > 1) {
    if (current_menu == 2) {
      led_selected = 0;
      is_selected_all_leds = false;
    }

    current_menu--;
    current_line = 1;

    menu.previous_screen();
    menu.set_focusedLine(0);    
  }
}

void select_led() {
  current_menu = 2;

  if (current_line > 0 && current_line < LINES_MENU_1) {
    led_selected = current_line + 2;
    is_selected_all_leds = false;
  } else {
    led_selected = 0;
    is_selected_all_leds = true;
  }

  current_line = 1;

  menu.next_screen();
  menu.set_focusedLine(0);
}

void turn_on_led() {
  if (is_selected_all_leds == true) {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    return;
  }

  switch (led_selected) {
    case LED_1:
      digitalWrite(LED_1, HIGH);
      break;
    case LED_2:
      digitalWrite(LED_2, HIGH);
      break;
    case LED_3:
      digitalWrite(LED_3, HIGH);
      break;
  }
}

void turn_off_led() {
  if (is_selected_all_leds == true) {
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    return;
  }

  switch (led_selected) {
    case LED_1:
      digitalWrite(LED_1, LOW);
      break;
    case LED_2:
      digitalWrite(LED_2, LOW);
      break;
    case LED_3:
      digitalWrite(LED_3, LOW);
      break;
  }
}