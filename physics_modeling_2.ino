// include these three libraries for all M3T3 projects
#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

float k = 9.3; // spring stiffness
float m = 5.0; // mass
float d = 0.01; // damping coefficient

float x; // virtual position
float v; // velocity
float f; // force

long tick = 0;
int last_pos = 0;

int c = 0;

void setup() {

  MotorA.init();
  tick = millis();
  last_pos = analogRead(A1);

}

void loop() {

  long tick_now = millis();
  float dt = (float)(tick_now - tick) / 100;

  int current_pos = analogRead(A1);

  int dx = last_pos - current_pos;

  f = k * (dx - x) - (d * v);
  v += (f / m) * dt;
  x += v * dt;

  MotorA.torque(f);
  
  tick = millis();
  last_pos = current_pos;
  
  Serial.println(f);
}
