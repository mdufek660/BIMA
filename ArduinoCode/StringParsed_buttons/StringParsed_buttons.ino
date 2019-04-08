/*
Written on April 8th, 2019 by Michael Dufek
This code is designed to test parsing the text into cells through use of a dictionary and if statements
Note this code loops automatically with a short break between scrolls, future versions will impliment buttons
Special thanks to Pizzle on Discord for his help in troubleshooting a previous version of the project~
Note I tried to do the code with various libraries being made but could not fix it. Will try to update that in later
*/
int pin=0;
    char dictionary[50][9]= //Please note if you change the first value, you MUST change j to match minus 1
    {
      "A 100000", "B 101000", "C 110000", "D 110100", "E 100100", "F 111000", "G 111100", "H 101100", "I 011000", "J 011100", "K 100010",
      "L 101010", "M 110010", "N 110110", "O 100110", "P 111010", "Q 111110", "R 101110", "S 011010", "T 011110", "U 100011", "V 101011",
      "W 011101", "X 110011", "Y 110111", "Z 100111", "1 100000", "2 101000", "3 110000", "4 110100", "5 100100", "6 111000", "7 111100", 
      "8 101100", "9 011000", "0 011100", ". 001101", ", 001000", ", 001000", "? 001000", "; 001010", "! 001110", "\" 001011", "- 000011",
      "' 000010", "{ 001111", "* 010111", "+ 000001"
    };
  int j=49; //Note this MUST match the size of the dictionary entries minus 1! Larger means you will run out of the array bounds, smaller means you wont search each entry!
  int i=0;
  int k=2;
  int delayValue=500;
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}


//******************************************************************************************************************************************************************************


void loop() {
  // put your main code here, to run repeatedly:
 int  n=0;
  String hello = "Hello there!";
  while(n<hello.length())
  {
    if(isUpperCase(hello[n]))
    {
      Serial.println("Printing cap letter");
      makeBraille('+', hello[n]);
      n++;
     Serial.println(n);
    }
    if(isDigit(hello[n]))
    {
      Serial.println("Printing number");
      makeBraille('*', hello[n]);
      n++;
      Serial.println(n);
    }
    if(n<(hello.length()-1) && !(isUpperCase(hello[n])) && !(isDigit(hello[n])))
    {
      if(!(isUpperCase(hello[n+1])) && !(isDigit(hello[n+1])))
      {
      Serial.println("Printing 2 letters");
        makeBraille(hello[n], hello[n+1]);
        n++;
        n++;
        Serial.println(n);
      }
      else
      {
      Serial.println("Printing 1 letter and hyphon");
        makeBraille(hello[n], '-');
        n++;
        Serial.println(n);
      }
    }
    if(n==(hello.length()-1) && !(isUpperCase(hello[n])) && !(isDigit(hello[n])))
    {
      Serial.println("Printing one letter and space");
      makeBraille(hello[n], ' ');
      n++;
      Serial.println(n);
    }
    
    delay(2000);
    pinMode(3, OUTPUT);
    digitalWrite(3,1);
    delay(100);
    digitalWrite(3,0);
  }
}


//******************************************************************************************************************************************************************************


void makeBraille(char c, char d){
  int i=0;
  int k=2;  
  digitalWrite(3,1);
  delay(100);
  digitalWrite(3,0);
  digitalWrite(7,0);
  digitalWrite(8,0);
  
  bool found = false;
  String value1 = "";
  String value2 = "";
  
  /*
  Serial.print("About to search. Found: ");
  Serial.print(found);
  Serial.print(" i: ");
  Serial.println(i);
  */

  c = charUpper(c);
  d = charUpper(d);
  
  Serial.print("Inside the makeBraille function, value is: ");
  Serial.print(c);
  Serial.print(" and ");
  Serial.println(d);
  
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Get first value
  if( c != ' ') //set up the first value
  {
  while(i<j && found==false)
  {
    
    if(dictionary[i][0]==c)
    {
      //Serial.println("Found letter: " + c);
       while(k<8)
       {
        value1 += dictionary[i][k];
        k++;
        found = true;
       }
     Serial.println(value1);
    }
    i++;
  }
  if(found == false)
  {
    Serial.println("This was not the char we were looking for");
    value1 = "111111";//this is the default for a character not found in the dictionary, all bumps
  }
  }
  else
  {
    Serial.println("It is a space");
    value1 = "000000";
  }

  i=0;
  k=2;
  found=false;
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Get second value
  if( d != ' ') //set up the first value
  {
  while(i<j && found==false)
  {
    
    if(dictionary[i][0]==d)
    {
      //Serial.println("Found letter: " + c);
       while(k<8)
       {
        value2 += dictionary[i][k];
        k++;
        found = true;
       }
     Serial.println(value2);
    }
    i++;
  }
  if(found == false)
  {
    Serial.println("This was not the char we were looking for");
    value2 = "111111";//this is the default for a character not found in the dictionary, all bumps
  }
  }
  else
  {
    Serial.println("It is a space");
    value2 = "000000";
  }
  int l = 0;
  
  digitalWrite(4,0);//Sets A
  digitalWrite(5,0);//Sets B
  digitalWrite(6,0);//Sets C
  delay(delayValue);
  if(value1[l]=='0'){digitalWrite(7,0);}
  else{digitalWrite(7,1);}
  if(value2[l]=='0'){digitalWrite(8,0);}
  else{digitalWrite(8,1);}
  l++;
  delay(delayValue);
  digitalWrite(7,0);//Clear output 1
  digitalWrite(8,0);//Clear output 2
  
  digitalWrite(4,1);
  digitalWrite(5,0);
  digitalWrite(6,0);
  delay(delayValue);
  if(value1[l]=='0'){digitalWrite(7,0);}
  else{digitalWrite(7,1);}
  if(value2[l]=='0'){digitalWrite(8,0);}
  else{digitalWrite(8,1);}
  l++;
  delay(delayValue);
  digitalWrite(7,0);
  digitalWrite(8,0);
  
  digitalWrite(4,0);
  digitalWrite(5,1);
  digitalWrite(6,0);
  delay(delayValue);
  if(value1[l]=='0'){digitalWrite(7,0);}
  else{digitalWrite(7,1);}
  if(value2[l]=='0'){digitalWrite(8,0);}
  else{digitalWrite(8,1);}
  l++;
  delay(delayValue);
  digitalWrite(7,0);
  digitalWrite(8,0);
  
  digitalWrite(4,1);
  digitalWrite(5,1);
  digitalWrite(6,0);
  delay(delayValue);
  if(value1[l]=='0'){digitalWrite(7,0);}
  else{digitalWrite(7,1);}
  if(value2[l]=='0'){digitalWrite(8,0);}
  else{digitalWrite(8,1);}
  l++;
  delay(delayValue);
  digitalWrite(7,0);
  digitalWrite(8,0);
  
  digitalWrite(4,0);
  digitalWrite(5,0);
  digitalWrite(6,1);
  delay(delayValue);
  if(value1[l]=='0'){digitalWrite(7,0);}
  else{digitalWrite(7,1);}
  if(value2[l]=='0'){digitalWrite(8,0);}
  else{digitalWrite(8,1);}
  l++;
  delay(delayValue);
  digitalWrite(7,0);
  digitalWrite(8,0);
  
  digitalWrite(4,1);
  digitalWrite(5,0);
  digitalWrite(6,1);
  delay(delayValue);
  if(value1[l]=='0'){digitalWrite(7,0);}
  else{digitalWrite(7,1);}
  if(value2[l]=='0'){digitalWrite(8,0);}
  else{digitalWrite(8,1);}
  l++;
  delay(delayValue);
  digitalWrite(7,0);
  digitalWrite(8,0);
}


//******************************************************************************************************************************************************************************


char charUpper(char c)
{
  if(c=='a'){c='A';}
  if(c=='b'){c='B';}
  if(c=='c'){c='C';}
  if(c=='d'){c='D';}
  if(c=='e'){c='E';}
  if(c=='f'){c='F';}
  if(c=='g'){c='G';}
  if(c=='h'){c='H';}
  if(c=='i'){c='I';}
  if(c=='j'){c='J';}
  if(c=='k'){c='K';}
  if(c=='l'){c='L';}
  if(c=='m'){c='M';}
  if(c=='n'){c='N';}
  if(c=='o'){c='O';}
  if(c=='p'){c='P';}
  if(c=='q'){c='Q';}
  if(c=='r'){c='R';}
  if(c=='s'){c='S';}
  if(c=='t'){c='T';}
  if(c=='u'){c='U';}
  if(c=='v'){c='V';}
  if(c=='w'){c='W';}
  if(c=='x'){c='X';}
  if(c=='y'){c='Y';}
  if(c=='z'){c='Z';}
  return(c);
}
