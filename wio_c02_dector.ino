#include"TFT_eSPI.h"
TFT_eSPI tft;
#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD
////////////////////////////////////////////////////////////////////////////
#include <SoftwareSerial.h>
#include <MHZ.h>

// pin for pwm reading
#define CO2_IN BCM26

// pin for uart reading
#define MH_Z19_RX BCM12  // D7
#define MH_Z19_TX BCM16 // D6

MHZ co2(MH_Z19_RX, MH_Z19_TX, CO2_IN, MHZ19B);
////////////////////////////////////////////////////////////////////////////
 
void setup() {
  // put your setup code here, to run once:

    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
 
    tft.setTextColor(TFT_BLUE);
    tft.setTextSize(3);
    tft.drawString("Starting...",25,120);
    
  Serial.begin(9600);
  pinMode(CO2_IN, INPUT);
  delay(100);
  Serial.println("MHZ 19B");
////////////////////////////////////////////////////////////////////////////
  // enable debug to get addition information
  //co2.setDebug(true);
  delay(5000);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("PreHeating...",25,120);
  
  if (co2.isPreHeating()) {
    Serial.print("Preheating");    
    while (co2.isPreHeating()) {     
      Serial.print(".");
      delay(5000);
    }
    Serial.println();
  }    
////////////////////////////////////////////////////////////////////////////  
}
 
void loop() {
  // put your main code here, to run repeatedly:
////////////////////////////////////////////////////////////////////////////  
  Serial.print("\n----- Time from start: ");
  Serial.print(millis() / 1000);
  Serial.println(" s");

  long ppm_uart = co2.readCO2UART();
  Serial.print("PPMuart: ");

  if (ppm_uart > 0) {
    Serial.print(ppm_uart);
  } else {
    Serial.print("n/a");
  }


  int ppm_pwm = co2.readCO2PWM();
  Serial.print(", PPMpwm: ");
  Serial.print(ppm_pwm);

  int temperature = co2.getLastTemperature();
  Serial.print(", Temperature: ");

  if (temperature > 0) {
    Serial.println(temperature);
  } else {
    Serial.println("n/a");
  }
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE); 
  tft.drawString("CO2 ppm: "+String(ppm_pwm),25,120);
  Serial.println("\n------------------------------");
  delay(130000);
////////////////////////////////////////////////////////////////////////////  
}
