class Braille_alpha
{
  public:
    int getValue(char letter);
    Braille_alpha();
    
    
  private:
    int firstLetter;
    char lookUp[7][100];
    char temp;
  
};
