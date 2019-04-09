
  int potA4, potA5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
}

void loop() 
{
  potA4 = analogRead(A4);
  potA5 = analogRead(A5);
  Serial.print("Potentiometer at A4: ");
  Serial.println(potA4);
  Serial.print("Potentiometer at A5: ");
  Serial.println(potA5);
  delay(1000);  
}
