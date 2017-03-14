#include <Adafruit_BMP280.h>
#include <BMI160Gen.h>
#include <CurieIMU.h>

#define Arduino_UNO
#define I2C

BMI160GenClass BMI160;
const int select_pin = 10;
Adafruit_BMP280 BMP280;

void setup() {
  Serial.begin(9600); // initialize Serial communication
  Serial.println("Programme de Test Capteur BMI+BMM");
  while (!Serial);    // wait for the serial port to open

  // initialize device
  BMI160.begin(select_pin);
  uint8_t dev_id = BMI160.getDeviceID();
  Serial.print("DEVICE ID: ");
  Serial.println(dev_id, HEX);

  BMI160.setGyroRange(250);
  BMI160.setAccelerometerRange(4);
}

void loop() {
  uint8_t IF_CONF = 107;
  uint8_t MAG_IF_1 = 75;
  uint8_t MAG_IF_2 = 76;
  uint8_t MAG_IF_3 = 77;
  uint8_t MAG_IF_4 = 78;
  uint8_t MAG_IF_5 = 79;
  uint8_t Res_IF_CONF, Res_MAG_IF_1, Res_MAG_IF_2, Res_MAG_IF_3, Res_MAG_IF_4, Res_MAG_IF_5 ;
  uint8_t I2C_MAG = 16;
  uint8_t MAG_MAN_DIS = 3;
  uint8_t MAG_MAN_8BitsVal = 131;
  int x, y, z;
  float MagRate;

  BMI160.setMagRate(100);
  MagRate = BMI160.getMagRate();
  BMI160.setRegister(MAG_IF_2, MAG_MAN_8BitsVal);

  Res_IF_CONF = BMI160.getRegister(IF_CONF);
  
  Res_MAG_IF_1 = BMI160.getRegister(MAG_IF_1);
  Res_MAG_IF_2 = BMI160.getRegister(MAG_IF_2);
  Res_MAG_IF_3 = BMI160.getRegister(MAG_IF_3);
  Res_MAG_IF_4 = BMI160.getRegister(MAG_IF_4);
  Res_MAG_IF_5 = BMI160.getRegister(MAG_IF_5);

  BMI160.readMag(x, y, z);

  Serial.print("Valeur du registre IF_CONF :\t");
  Serial.print(int(Res_IF_CONF));
  Serial.println();
  Serial.print("Adresse I2C pour le magnetometre :\t");
  Serial.print((Res_MAG_IF_1)/2);
  
  Serial.println();
  Serial.print("Freq echantillonage Magnetometre :\t");
  Serial.print(MagRate);
  Serial.println();
  Serial.print("Valeur du registre DATA pour le mag :\t");
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.print(z);
  Serial.println();
  Serial.println();

  delay(500);
}


