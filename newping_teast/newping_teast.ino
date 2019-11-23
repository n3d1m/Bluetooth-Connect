#include "NewPing.h"

#define TRIGGER_PIN_L  12
#define ECHO_PIN_L     11
#define TRIGGER_PIN_R  9
#define ECHO_PIN_R     10
#define MAX_DISTANCE 10000
 
NewPing sonar_L(TRIGGER_PIN_L, ECHO_PIN_L, MAX_DISTANCE);
NewPing sonar_R(TRIGGER_PIN_R, ECHO_PIN_R, MAX_DISTANCE);

float left_read, right_read, object_dist;
 
void setup() {
  Serial.begin(115200);
}
 
void loop() {
  left_read = sonar_L.ping_cm();
  delay(75);
  right_read = sonar_R.ping_cm();
/*Serial.print("L: ");
  Serial.print(left_read);
  Serial.print(" .  R:");
  Serial.println(right_read);
*/
  
  if ((left_read - right_read) < 5 & left_read < 200 & left_read > 0){ 
    object_dist = (left_read + right_read) / 2;
    Serial.print("Object in front! Distance: ");
    Serial.print(object_dist);
    Serial.print("cm . "); 
    Serial.print("L: ");
    Serial.print(left_read);
    Serial.print(" .  R:");
    Serial.println(right_read);
  }else if (left_read != 0 & left_read < 200){
    Serial.print("Object to left! Distance: ");
    Serial.print(left_read);  
    Serial.print("cm . "); 
    Serial.print("R: ");
    Serial.println(right_read);
  }else if (right_read != 0 & right_read < 200){
    Serial.print("Object to right! Distance: ");
    Serial.print(right_read);
    Serial.print("cm . "); 
    Serial.print("L: ");
    Serial.println(left_read);
    }
  
  delay(500);
}
