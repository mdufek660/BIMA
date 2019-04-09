int dataAvailable=0;

void setup() {
  pinMode(3, OUTPUT);
  Serial.begin(38400); // Default comm rate of the Bluetooth HC05 module
}
void loop() {
  
  if(Serial.available() > 0) // Checks whether data is comming from the serial port
  { 
    dataAvailable = Serial.read(); // Reads the data from the serial port
  }
  
 if (dataAvailable == '0') 
  {
    digitalWrite(3, LOW);
    Serial.println("0"); // Communicate back to the phone
    dataAvailable = 0;
  }
  
 else if (dataAvailable == '1') 
  {
    digitalWrite(3, HIGH);
    Serial.println("1");;
    dataAvailable = 0;
  } 
}
