evre /*
  Arduino DC Voltage Demo 1
  dc-voltage-demo.ino
  Use Arduino A/D converter to measure voltage
  Use external voltage divider with 30k & 7.5k resistors
  Results displayed on Serial Monitor

  DroneBot Workshop 2021
  https://dronebotworkshop.com
*/

// Define analog input
#define ANALOG_VIN_PIN A0

// Floats for ADC voltage & Input voltage
float adc_voltage = 0.0;
float in_voltage = 0.0;

// Floats for resistor values in divider (in ohms)
float R1 = 30000.0;
float R2 = 7500.0; 

// Float for Reference Voltage
double ref_voltage = 5.0;

// Integer for ADC value
int adc_value = 0;

// Variables for Measured Voltage and Calculated Current
double Vout = 0;
double Current = 0;
 
// Constants for Scale Factor
// Use one that matches your version of ACS712
 
//const double scale_factor = 0.185; // 5A
const double scale_factor = 0.200000; // 20A
//const double scale_factor = 0.066; // 30A
 
// Constants for A/D converter resolution
// Arduino has 10-bit ADC, so 1024 possible values
// Reference voltage is 5V if not using AREF external reference
// Zero point is half of Reference Voltage
 
const double vRef = 5.00;
const double resConvert = 1024;
double resADC = vRef/resConvert;
double zeroPoint = 2.50;
 

void setup(){
   // Setup Serial Monitor
   Serial.begin(9600);
   Serial.println("DC Voltage Test");
}

void loop(){
   // Read the Analog Input
   adc_value = analogRead(ANALOG_VIN_PIN);
   
   // Determine voltage at ADC input
   adc_voltage  = (adc_value * ref_voltage) / 1024.0; 
    // Vout is read 1000 Times for precision
  for(int i = 0; i < 1000; i++) {
    Vout = (Vout + (resADC * analogRead(A1)));   
    delay(1);
  }
  
  // Get Vout in mv
  Vout = Vout /1000;
  
  // Convert Vout into Current using Scale Factor
  Current = -(Vout - zeroPoint)/scale_factor;                   

  // Print Vout and Current to two Current = ");                  
 
  Serial.print("Vout = ");           
  Serial.print(Vout); 
  Serial.print(" V");                            
  Serial.print("\t Current = ");                  
  Serial.print(Current);
  Serial.println(" A");                             
 
   // Calculate voltage at divider input
//   in_voltage = adc_voltage / (R2/(R1+R2)); 
   
   // Print results to Serial Monitor to 2 decimal places
  Serial.print("Input Voltage = ");
  Serial.print(adc_voltage, 2);
  Serial.println(" V");
  Serial.println("\n");
  // Short delay
  delay(500);
}



 
