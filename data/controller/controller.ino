
char button0=3, button1=4, button2=5, button3=6;
char sel=2;
bool s,u,d,l,r,a,b,c,p; //Checks pressed State
                        //Send Serial.print("S"); if true then set to false. 
                        //Represents Key Released

void setup(void)
{
  pinMode(sel, INPUT);      //Set the Joystick 'Select'button as an input
  digitalWrite(sel, HIGH);  //Enable the pull-up resistor on the select button
  
  pinMode(button0, INPUT);      //Set the Joystick button 0 as an input
  digitalWrite(button0, HIGH);  //Enable the pull-up resistor on button 0

  pinMode(button1, INPUT);      //Set the Joystick button 1 as an input
  digitalWrite(button1, HIGH);  //Enable the pull-up resistor on button 1
  
  pinMode(button2, INPUT);      //Set the Joystick button 2 as an input
  digitalWrite(button2, HIGH);  //Enable the pull-up resistor on button 2

  pinMode(button3, INPUT);      //Set the Joystick button 3 as an input
  digitalWrite(button3, HIGH);  //Enable the pull-up resistor on button 3
  
  Serial.begin(9600);           //Turn on the Serial Port at 9600 bps
}

void loop(void)
{

  if(analogRead(0) > 600){ //Right analog
    if(r == false){
      Serial.print("r");
      //Check if l is true
    }
    r = true;
    
  }else if(analogRead(0) < 400){ //Left analog
    if(l == false){
      Serial.print("l");
      //Check if r is true
    }
    l = true;
    
  }else{ //Horizontal Neutral
    if(r == true){//Key Released Logic
      Serial.print("R");
    }
    if(l == true){//Key Released Logic
      Serial.print("L");
    }
     r = false;
     l = false;
  }
  if(analogRead(1) > 600){  //Up analog
    if(u == false){
      Serial.print("u");
      //check if d is true
    }
    u = true;
    
  }else if(analogRead(1) < 500){//Down analog
    if(d == false){
      Serial.print("d");
      //check if u is true
    }
    d = true;
   
  }else{//Vertical Neutral
    if(u == true){//Key Released Logic
      Serial.print("U");
    }
    if(d == true){//Key Released Logic
      Serial.print("D");
    }
    u = false;
    d = false;
  }
  if(digitalRead(sel) == 0){ //Button D_3
    if(s == false){
      Serial.print("s");
    }
    s = true;
    
  }else{
    if(s == true){//Key Released Logic
      Serial.print("S");
    }
    s = false;
  }
  if(digitalRead(button0) == 0){ //Button D_3
    if(a == false){
      Serial.print("a");
    }
    a = true;
    
  }else{
    if(a == true){//Key Released Logic
      Serial.print("A");
    }
    a = false;
  }
  if(digitalRead(button1) == 0){ //Button D_4
    if(b == false){
        Serial.print("b");
    }
    b = true;
    
  }else{
    if(b == true){//Key Released Logic
      Serial.print("B");
    }
    b = false;
  }
  if(digitalRead(button2) == 0){//Button D_5
     if(c == false){
        Serial.print("c");
    }
    c = true;
    
  }else{
     if(c == true){//Key Released Logic
      Serial.print("C");
    }
   c = false;
  }
  if(digitalRead(button3) == 0){ //Button D_6
    if(p == false){
      Serial.print("p");
    }
    p = true;
  }else{
     if(p == true){//Key Released Logic
      Serial.print("P");
    }
    p = false;
  }
  
  //Wait for 100 ms, then go back to the beginning of 'loop' and repeat.
  //delay(100);
}
