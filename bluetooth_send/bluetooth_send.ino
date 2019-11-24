//#include <SoftwareSerial.h>

#include "SoftwareSerial.h"
#include "NewPing.h"

#define TRIGGER_PIN_L  12
#define ECHO_PIN_L     11
#define TRIGGER_PIN_R  9
#define ECHO_PIN_R     19
#define MAX_DISTANCE 10000
 
NewPing sonar_L(TRIGGER_PIN_L, ECHO_PIN_L, MAX_DISTANCE);
NewPing sonar_R(TRIGGER_PIN_R, ECHO_PIN_R, MAX_DISTANCE);

float left_read, right_read, object_dist;
SoftwareSerial serial_connection(2, 3);//Create a serial connection with TX and RX on these pins
#define BUFFER_SIZE 64//This will prevent buffer overruns.
char inData[BUFFER_SIZE];//This is a character buffer where the data sent by the python script will go.
char inChar=-1;//Initialie the first character as nothing
int count=0;//This is the number of lines sent in from the python script
int i=0;//Arduinos are not the most capable chips in the world so I just create the looping variable once
void setup()
{
  Serial.begin(9600);//Initialize communications to the serial monitor in the Arduino IDE
  serial_connection.begin(9600);//Initialize communications with the bluetooth module
  //serial_connection.println("Ready!!!");//Send something to just start comms. This will never be seen.
  Serial.println("Started");//Tell the serial monitor that the sketch has started.
}
void loop()
{

  left_read = sonar_L.ping_cm();
  delay(75);
  right_read = sonar_R.ping_cm();

  float myArr[] = {left_read, right_read};

  if ((left_read - right_read) < 5 & left_read < 200 & left_read > 0){ 
    object_dist = (left_read + right_read) / 2;
    Serial.print("Object in front! Distance: ");
    Serial.print(object_dist);
    Serial.print("cm . "); 
    Serial.print("L: ");
    Serial.print(left_read);
    Serial.print(" .  R:");
    Serial.println(right_read);
 
    serial_connection.println(String(left_read) + " " + String(right_read) + " " + String(object_dist));
    //serial_connection.println(String(right_read) + "right");
  }else if (left_read != 0 & left_read < 200){
    Serial.print("Object to left! Distance: ");
    Serial.print(left_read);  
    Serial.print("cm . "); 
    Serial.print("R: ");
    Serial.println(right_read);
    serial_connection.println(String(left_read) + " " + String(right_read));
    //serial_connection.println(String(right_read) + "right");
  }else if (right_read != 0 & right_read < 200){
    Serial.print("Object to right! Distance: ");
    Serial.print(right_read);
    Serial.print("cm . "); 
    Serial.print("L: ");
    Serial.println(left_read);
    serial_connection.println(String(left_read) + " " + String(right_read));
    //serial_connection.println(String(right_read) + "right");
    }

  //serial_connection.println(String(count));//Then send an incrmented string back to the python script
  //count++;//Increment the line counter
  
//  serial_connection.println("Hello from Blue "+String(count));//Then send an incrmented string back to the python script
//  count++;//Increment the line counter

  
  //This will prevent bufferoverrun errors
//  byte byte_count=serial_connection.available();//This gets the number of bytes that were sent by the python script
//  if(byte_count)//If there are any bytes then deal with them
//  {
//    Serial.println("Incoming Data");//Signal to the monitor that something is happening
//    int first_bytes=byte_count;//initialize the number of bytes that we might handle. 
//    int remaining_bytes=0;//Initialize the bytes that we may have to burn off to prevent a buffer overrun
//    if(first_bytes>=BUFFER_SIZE-1)//If the incoming byte count is more than our buffer...
//    {
//      remaining_bytes=byte_count-(BUFFER_SIZE-1);//Reduce the bytes that we plan on handleing to below the buffer size
//    }
//    for(i=0;i<first_bytes;i++)//Handle the number of incoming bytes
//    {
//      inChar=serial_connection.read();//Read one byte
//      inData[i]=inChar;//Put it into a character string(array)
//    }
//    //inData[i]='\0';//This ends the character array with a null character. This signals the end of a string
////    if(String(inData)=="BOOP 2")//This could be any motor start string we choose from the python script
////    {
////      Serial.println("********* Start Motor *********");
////    }
////    else if(String(inData)=="BOOP 4")//Again this is an arbitrary choice. It would probably be something like: MOTOR_STOP
////    {
////      Serial.println("********* STOP Motor *********");
////    }
//    for(i=0;i<remaining_bytes;i++)//This burns off any remaining bytes that the buffer can't handle.
//    {
//      inChar=serial_connection.read();
//    }
//    //Serial.println(inData);//Print to the monitor what was detected
//    serial_connection.println(String(count));//Then send an incrmented string back to the python script
//    count++;//Increment the line counter
//  }
  //delay(100);//Pause for a moment 
}
