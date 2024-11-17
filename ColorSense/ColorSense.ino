const int s0 = 26;  
const int s1 = 27;  
const int s2 = 32;  
const int s3 = 35;  
const int out = 33;   

// values
int red = 0;  
int green = 0;  
int blue = 0;  

void setup()   
{  
  Serial.begin(115200); 
 
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  
  digitalWrite(s0, LOW);  
  digitalWrite(s1, HIGH);  
} 
 
void loop() 
{  
  delay(100);
  color();
  Serial.print("RED ");  
  Serial.println(red, DEC);  
  Serial.print("GREEN ");  
  Serial.println(green, DEC);  
  Serial.print("BLUE ");  
  Serial.println(blue, DEC);  

  if (blue > 750 && blue < 900 && red > 700 && red < 900 && green > 200 && green < 300){  
    Serial.println("Blue Tape");
  } else if (blue > 700 && blue < 900 && red > 700 && red < 900 && green > 190 && green < 300){  
    Serial.println("Green Tape");
  } else if (blue > 390 && blue < 500 && red > 380 && red < 550 && green > 180 && green < 300){  
    Serial.println("Red Tape");
  } else if (blue > 300 && blue < 400 && red > 300 && red < 400 && green > 110 && green < 250){  
    Serial.println("Yellow Tape");
  } else if (blue > 750 && blue < 1100 && red > 750 && red < 1100 && green > 200 && green < 350){  
    Serial.println("Black Tape");
  } else {
    Serial.println("Table");
  }
}


void color()  
{
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
}
 