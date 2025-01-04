#include <Arduino.h>
// IRemote
#include <Wire.h>
#include <IRremote.h>
// LiquidCrystal
#include <LiquidMenu.h>
#include <LiquidCrystal_I2C.h>

// define keys
#define UP 2673870599
#define DOWN 2657158919
#define ENTER 2540177159
#define BACK 2807564039

// define LEDs pin
#define LED_1 3
#define LED_2 4
#define LED_3 5

// define lines
#define LINES_MENU_1 4
#define LINES_MENU_2 3

#ifndef EXPORT_H
#define EXPORT_H

unsigned int current_menu = 1;
unsigned int current_line = 1;

unsigned long int button;

unsigned int led_selected = 0;
bool is_selected_all_leds = false;

// display initialization
LiquidCrystal_I2C lcd(0x27, 16, 2);

// declare lines (main menu)
LiquidLine line_0_0(1, 0, "LED 1");
LiquidLine line_0_1(1, 1, "LED 2");
LiquidLine line_0_2(1, 0, "LED 3");
LiquidLine line_0_3(1, 1, "ALL");

// declare lines (sub menu)
LiquidLine line_1_0(1, 0, "ON");
LiquidLine line_1_1(1, 1, "OFF");
LiquidLine line_1_2(1, 0, "BACK");

// declare menus
LiquidScreen screen_0(line_0_0, line_0_1, line_0_2, line_0_3);
LiquidScreen screen_1(line_1_0, line_1_1, line_1_2);

LiquidMenu menu(lcd, screen_0, screen_1);

#endif