#include <Firebase.h>


#include <LiquidCrystal.h>

LiquidCrystal lcd(16,5,4,0,2,14);


#define pinDigital 12


void setup()  {
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(pinDigital, INPUT);

}

void loop() {
  if(digitalRead(pinDigital)) {
    
    Serial.print("Sem Umidade");
    lcd.setCursor(3,0);
    lcd.print("Carga:");
    lcd.setCursor(3,1);
    lcd.print("Aprovada");

    delay(5000);

    lcd.clear();
  } else {
    
    Serial.print("Com Umidade");
    lcd.setCursor(3,0);
    lcd.print("Carga");
    lcd.setCursor(3,1);
    lcd.print("Reprovada");

     delay(5000);

    lcd.clear();
  }

}
