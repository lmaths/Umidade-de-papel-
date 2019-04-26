#include <Firebase.h>


#include <LiquidCrystal.h>

LiquidCrystal lcd(16,5,4,0,2,14);


#define pinDigital 12
#define pinA 0


void setup()  {
  Serial.begin(1200);
  lcd.begin(16,2);
  pinMode(pinDigital, INPUT);

}

void loop() {
  Serial.print("Valor ");
  Serial.print ("");
  Serial.print(analogRead(pinA));


  if(analogRead(pinA) >= 800) {
   Serial.print(" Aprovada ");

   lcd.setCursor(3,0);
    lcd.print("Aprovada:");
    lcd.setCursor(3,1);
    lcd.print(analogRead(pinA));

    delay(5000);
   
  }else if (analogRead(pinA) <= 650) {
    Serial.print(" Reprovada ");
     lcd.setCursor(3,0);
    lcd.print("Reprovada:");
    lcd.setCursor(3,1);
    lcd.print(analogRead(pinA));

    delay(5000);
  }else {
    Serial.print(" Aprovada com desconto ");
     lcd.setCursor(3,0);
    lcd.print("Desconto:");
    lcd.setCursor(3,1);
    lcd.print(analogRead(pinA));

    delay(5000);
  }


  

}
