int ledPin = 8;
int continueLoop=1;
int i = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  

  while(continueLoop == 1)
  {
    while(i<8)
    {
     i++; 
     digitalWrite(8, HIGH);   // sets the LED on
     delay(300);                  // waits for a second
     digitalWrite(8, LOW);    // sets the LED off
     delay(300);                  // waits for a second
    }
   i=0;
   delay(2000);
  }

}
