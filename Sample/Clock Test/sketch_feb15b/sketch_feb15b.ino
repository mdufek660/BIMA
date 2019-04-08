int ledPin = 8;
int continueLoop=1;
int i = 200;
int j = 1000;
int k = 300;

void setup() 
{
  pinMode(3, OUTPUT);//Reset
  pinMode(4, OUTPUT);//Counter A
  pinMode(5, OUTPUT);//Counter B
  pinMode(6, OUTPUT);//Counter C

  pinMode(9, OUTPUT);//Output 1
  pinMode(10, OUTPUT);//Output 2
}

void loop() 
{
  digitalWrite(4,0);//Sets A
  digitalWrite(5,0);//Sets B
  digitalWrite(6,0);//Sets C
  delay(k);//After setting the ABC to the correct address, pause just a few milliseconds (the time inside delay is in ms)
  digitalWrite(9,1);//Write a random value to memory 1-1
  digitalWrite(10,1);//Write a random value to memory 2-1
  delay(i);// wait a second
  digitalWrite(9,0);//Clear output 1
  digitalWrite(10,0);//Clear output 2
  
  digitalWrite(4,1);
  digitalWrite(5,0);
  digitalWrite(6,0);
  delay(k);
  digitalWrite(9,0);
  digitalWrite(10,0);
  delay(i);
  digitalWrite(9,0);
  digitalWrite(10,0);
  
  digitalWrite(4,0);
  digitalWrite(5,1);
  digitalWrite(6,0);
  delay(k);
  digitalWrite(9,0);
  digitalWrite(10,0);
  delay(i);
  digitalWrite(9,0);
  digitalWrite(10,0);
  
  digitalWrite(4,1);
  digitalWrite(5,1);
  digitalWrite(6,0);
  delay(k);
  digitalWrite(9,1);
  digitalWrite(10,1);
  delay(i);
  digitalWrite(9,0);
  digitalWrite(10,0);
  
  digitalWrite(4,0);
  digitalWrite(5,0);
  digitalWrite(6,1);
  delay(k);
  digitalWrite(9,1);
  digitalWrite(10,1);
  delay(i);
  digitalWrite(9,0);
  digitalWrite(10,0);
  
  digitalWrite(4,1);
  digitalWrite(5,0);
  digitalWrite(6,1);
  delay(k);
  digitalWrite(9,0);
  digitalWrite(10,0);
  delay(i);
  digitalWrite(9,0);
  digitalWrite(10,0);
  
  delay(j);
  digitalWrite(3,1);
  delay(j);
  digitalWrite(3,0);
  //the above chunk simply resets all the memory to start the next bits
  
  digitalWrite(4,0);
  digitalWrite(5,0);
  digitalWrite(6,0);
  delay(k);
  digitalWrite(9,0);
  digitalWrite(10,0);
  delay(i);
  digitalWrite(9,0);
  digitalWrite(10,0);
  
  digitalWrite(4,1);
  digitalWrite(5,0);
  digitalWrite(6,0);
  delay(k);
  digitalWrite(9,1);
  digitalWrite(10,1);
  delay(i);
  digitalWrite(9,0);
  digitalWrite(10,0);
  
  digitalWrite(4,0);
  digitalWrite(5,1);
  digitalWrite(6,0);
  delay(k);
  digitalWrite(9,1);
  digitalWrite(10,1);
  delay(i);
  digitalWrite(9,0);
  digitalWrite(10,0);
  
  digitalWrite(4,1);
  digitalWrite(5,1);
  digitalWrite(6,0);
  delay(k);
  digitalWrite(9,0);
  digitalWrite(10,0);
  delay(i);
  digitalWrite(9,0);
  digitalWrite(10,0);
  
  digitalWrite(4,0);
  digitalWrite(5,0);
  digitalWrite(6,1);
  delay(k);
  digitalWrite(9,0);
  digitalWrite(10,0);
  delay(i);
  digitalWrite(9,0);
  digitalWrite(10,0);
  
  digitalWrite(4,1);
  digitalWrite(5,0);
  digitalWrite(6,1);
  delay(k);
  digitalWrite(9,1);
  digitalWrite(10,1);
  delay(i);
  digitalWrite(9,0);
  digitalWrite(10,0);

  delay(j);
  digitalWrite(3,1);
  delay(j);
  digitalWrite(3,0);

  digitalWrite(4,0);
  digitalWrite(5,0);
  digitalWrite(6,0);
  delay(k);
  digitalWrite(9,0);
  digitalWrite(10,1);
  delay(i);
  digitalWrite(9,0);
  digitalWrite(10,0);
  
  digitalWrite(4,1);
  digitalWrite(5,0);
  digitalWrite(6,0);
  delay(k);
  digitalWrite(9,1);
  digitalWrite(10,0);
  delay(i);
  digitalWrite(9,0);
  digitalWrite(10,0);
  
  digitalWrite(4,0);
  digitalWrite(5,1);
  digitalWrite(6,0);
  delay(k);
  digitalWrite(9,1);
  digitalWrite(10,0);
  delay(i);
  digitalWrite(9,0);
  digitalWrite(10,0);
  
  digitalWrite(4,1);
  digitalWrite(5,1);
  digitalWrite(6,0);
  delay(k);
  digitalWrite(9,0);
  digitalWrite(10,1);
  delay(i);
  digitalWrite(9,0);
  digitalWrite(10,0);
  
  digitalWrite(4,0);
  digitalWrite(5,0);
  digitalWrite(6,1);
  delay(k);
  digitalWrite(9,1);
  digitalWrite(10,0);
  delay(i);
  digitalWrite(9,0);
  digitalWrite(10,0);
  
  digitalWrite(4,1);
  digitalWrite(5,0);
  digitalWrite(6,1);
  delay(k);
  digitalWrite(9,0);
  digitalWrite(10,1);
  delay(i);
  digitalWrite(9,0);
  digitalWrite(10,0);

  delay(j);
  digitalWrite(3,1);
  delay(j);
  digitalWrite(3,0);
}
