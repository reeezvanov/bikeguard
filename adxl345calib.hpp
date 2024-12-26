#include<Wire.h>
#include<ADXL345_WE.h>
#define ADXL345_I2CADDR 0x53

/* There are several ways to create your ADXL345 object:
 * ADXL345_WE myAcc = ADXL345_WE()                -> uses Wire / I2C Address = 0x53
 * ADXL345_WE myAcc = ADXL345_WE(ADXL345_I2CADDR) -> uses Wire / ADXL345_I2CADDR
 * ADXL345_WE myAcc = ADXL345_WE(&wire2)          -> uses the TwoWire object wire2 / ADXL345_I2CADDR
 * ADXL345_WE myAcc = ADXL345_WE(&wire2, ADXL345_I2CADDR) -> all together
 */
ADXL345_WE myAcc = ADXL345_WE(ADXL345_I2CADDR);

void setup(){
  Wire.begin();
  Serial.begin(9600);
  Serial.println("ADXL345_Sketch - Calibration");
  Serial.println();
  if(!myAcc.init()){
    Serial.println("ADXL345 not connected!");
  }
  Serial.println("Calibration procedure:");
  Serial.println(" - stay in full resolution");
  Serial.println(" - supply voltage has influence (at least for the modules)");
  Serial.println("        -> choose the same voltage you will use in your project!"); 
  Serial.println(" - turn your ADXL slowly (!) to find the min and max raw x,y and z values");
  Serial.println(" - deviations of one or two units don't matter much");
  Serial.println(" - the calibration changes the slope of g vs raw and assumes zero is (min+max)/2 ");
  Serial.println(" - write down the six values ");
  Serial.println(" - you can try the calibration values in ADXL345_angles_tilt_orientation.ino example sketch");
  Serial.println(" - ready to go? Then type in any key and send. ");
  while(!Serial.available());
  Serial.read();
  Serial.println(); Serial.println(); Serial.println();  
}

void loop() {
  xyzFloat raw = myAcc.getRawValues();
  Serial.print("Raw-x = ");
  Serial.print(raw.x);
  Serial.print("  |  Raw-y = ");
  Serial.print(raw.y);
  Serial.print("  |  Raw-z = ");
  Serial.println(raw.z);
  
  delay(1000);
  
}