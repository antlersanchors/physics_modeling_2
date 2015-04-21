// include these three libraries for all M3T3 projects
#include <spi4teensy3.h>
#include <EEPROM.h>
#include <M3T3.h>

float k = 0.3; // spring stiffness
float m = 1.0; // mass
float d = 0.02; // damping coefficient

float x; // virtual position
float v; // velocity
float f; // force

long tick = 0;
int last_pos = 0;

int c = 0;

void setup() {
  Music.init();
  MotorB.init();
  tick = millis();
  last_pos = analogRead(A9);

}

void loop() {

  long tick_now = millis();
  float dt = (float)(tick_now - tick) / 100;

  int current_pos = analogRead(A9);

  int dx = last_pos - current_pos;

  f = k * (current_pos - x) - (d * v);
  v += (f / m) * dt;
  x += v * dt;

  if (f < 200 && f > -200) {
    Serial.print("INSUFFICIENT TORQUE! ");
    Serial.println("f");
  }

    MotorB.torque(f);

    int abs_f = abs(f);

    int freq_val = map(abs_f, 0, 800, 500, 1200);
    Music.setFrequency(freq_val);

    tick = millis();
    last_pos = current_pos;

    Serial.println(abs_f);
  }
