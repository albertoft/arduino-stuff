#include "SimpleDmp.h"
 
/// Instancia a clase SimpleDmp
///
SimpleDmp mpu;
///
/// Fin de instancia a SimpleDmp
 
bool okDmp = false;
 
void setup()
{
    Serial.begin(9600);
    Serial.println("Inicio de sistema");
 
    // Inicializa MPU
      okDmp = mpu.initDmp();
}
 
void loop()
{
    if(okDmp) {
      float yaw, pitch, roll;
      mpu.readMPU();
      mpu.getAngles(yaw, pitch, roll);

      Serial.print(yaw);
      Serial.print(" ");
      Serial.print(pitch);
      Serial.print(" ");
      Serial.println(roll);
      delay(50);
    }
}
