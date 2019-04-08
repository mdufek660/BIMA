/*
Written on April 8th, 2019 by Michael Dufek
This code is designed to test parsing the text into cells through use of a dictionary and if statements
Note this code loops automatically with a short break between scrolls, future versions will impliment buttons
Special thanks to Pizzle on Discord for his help in troubleshooting a previous version of the project~
Note I tried to do the code with various libraries being made but could not fix it. Will try to update that in later
*/
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
  int delayValue=5;
  String hello = "Hello there! General Kenobi, you are a bold one.";
  int curState9=0, curState10=0, prevState9=0, prevState10=0;
  int timer=0;
  int pressed=0;
  int counter=0;
  bool check, written;
  
//******************************************************************************************************************************************************************************

  
void setup() {
  Serial.begin(9600);//makes the arduino able to output to the console in the topright of the screen.
  
  pinMode(3, OUTPUT);//Reset for the cells
  pinMode(4, OUTPUT);//A on the 1-to-8 demultiplexor
  pinMode(5, OUTPUT);//B on the 1-to-8 demultiplexor
  pinMode(6, OUTPUT);//C on the 1-to-8 demultiplexor
  pinMode(7, OUTPUT);//Outputs to cell 1
  pinMode(8, OUTPUT);//Outputs to cell 2
  pinMode(9, INPUT);//input to move backwards
  pinMode(10, INPUT);//input to move forwards
}
//Note the Serial.print's are used for diagnostic and display purposes.

//******************************************************************************************************************************************************************************


void loop() {
  
  int  n=0;
  while(n<hello.length()) //ensure we don't run out of bounds on the string
  {
    pressed=0;
    timer=0;
    while(pressed==0 && timer<1000) //wait for a timer of two seconds or a button press to change the current cell display
    {
      if(digitalRead(9)==1){pressed=1;}
      if(digitalRead(10)==1){pressed=2;}
      delay(6);
      timer++;
    }
    if(pressed==1)
    {
      if(check==false){counter=4;}
      else{counter=3;}
      
      while(n>=0 && counter!=0)
      {
        if(n!=0){n--;}
        counter--;
      }
      check=false;
      
    }
    pinMode(3, OUTPUT); //clear the cells with the next four lines
    digitalWrite(3,1);
    delay(10);
    digitalWrite(3,0);
    
    pressed=0;
    timer=0;
    written=false;
    
    if(isUpperCase(hello[n]) && written==false) //check if I need the uppercase cell
    {
      Serial.println("Printing cap letter");
      makeBraille('+', hello[n]); //Send the braille cells for capital and the char
      n++;
     Serial.println(n);
     check=true;
     written=true;
    }
    if(isDigit(hello[n]) && written==false)//check if i need the digit cell
    {
      Serial.println("Printing number");
      makeBraille('*', hello[n]); //Send the braille cells for number and the char
      n++;
      Serial.println(n);
      check=true;
      written=true;
    }
    if(n<(hello.length()-1) && !(isUpperCase(hello[n])) && !(isDigit(hello[n])) && written==false) //Checks if the character is in bounds and isn't a number or caps. probably redundant but not near the program byte cap
    {
      if(!(isUpperCase(hello[n+1])) && !(isDigit(hello[n+1]))) //Checks if the char after the current wouldn't require two cells (ie caps or number)
      {
      Serial.println("Printing 2 letters");
        makeBraille(hello[n], hello[n+1]); //Print the current char and the next
        n++;
        n++;
        Serial.println(n);
      }
      else
      {
      Serial.println("Printing 1 letter and hyphon");
        makeBraille(hello[n], '-'); //Prints the current letter and the hyphon so you know the word is continued next but couldn't fit
        n++;
        Serial.println(n);
      }
    written=true;
    }
    if(n==(hello.length()-1) && !(isUpperCase(hello[n])) && !(isDigit(hello[n])) && written==false) //checks to see if it is the end of the string and if so prints the last char and a space
    {
      Serial.println("Printing one letter and space");
      makeBraille(hello[n], ' ');
      n++;
      Serial.println(n);
      written=true;
    }
    
  }
}


//******************************************************************************************************************************************************************************


void makeBraille(char c, char d){
  int i=0;
  int k=2;  
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

  c = charUpper(c); //using char upper to search the array
  d = charUpper(d);

  //The following four lines are for diagnostic purposes
  Serial.print("Inside the makeBraille function, value is: ");
  Serial.print(c);
  Serial.print(" and ");
  Serial.println(d);
  
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Get first value
  if( c != ' ') //set up the first value
  {
  while(i<j && found==false) //checks to see if it has found the char while also ensuring it doesn't run out of bounds if it hasn't.
  {
    
      if(dictionary[i][0]==c) //check if the current location in the dictionary matches the current char
      {
        //Serial.println("Found letter: " + c);
         while(k<8) //this while loop assembles a string from the char array to parse out later
         {
          value1 += dictionary[i][k]; 
          k++;
          found = true;
         }
       Serial.println(value1);
      }
      i++;
    }//end the while.
    
    if(found == false) //Couldn't find it
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
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Get second value, look at instructions for c
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
  if(value1[l]=='0'){digitalWrite(7,0);} //this if-else controls whether the current cell location is a 1 or a 0 based on the string location
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
