const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;
 
const int buzzerPin = 4;
int counter = 0;


#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define melodyPin 4


int melody1[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5, 
  NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, 
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5, 
  NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};

// The note duration, 8 = 8th note, 4 = quarter note, etc.
int durations[] = {
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8, 
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8
};
// determine the length of the arrays to use in the loop iteration
int songLength = sizeof(melody1)/sizeof(melody1[0]);



#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2);


#include <PCF8574.h>
PCF8574 expander(0x20);
PCF8574 expander1(0x21);
const int expanderPin[6] = {0, 1, 4, 5, 6, 7};

#include <Keypad.h>


 char kodRozbrojenia[4] = {'0','0','0','0'};
char czas[6]={'0','0','0','0','0','0'};
int sekundy=0;
int minuty=0;
int godziny=0;

int o =0;
int u =0;
int i = 0;
int w = 0;
int v =1000;
bool kable[6]= {1,0,1,0,1,1};


volatile bool stan = true;

const byte ROWS = 4; // ile wierszy
const byte COLS = 4; //ile kolumn
 
unsigned long aktualnyCzas = 0;
unsigned long zapamietanyCzas = 0;

unsigned long aktualnyCzas1 = 0;
unsigned long zapamietanyCzas1 = 0;

 
byte rowPins[ROWS] = {8, 7, 6, 5}; //piny wierszy
byte colPins[COLS] = {12, 11, 10, 9}; //piny kolum
 
char keys[ROWS][COLS] = { //mapowanie klawiatury
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

 Keypad klawiatura = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
 int pozycja = 1;
 
void setup() {

  Serial.begin(9600);
 pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(1, onStep, FALLING);
    pinMode(buzzerPin, OUTPUT);
    
 lcd.init();
lcd.begin(16,2);   
  lcd.backlight();
  
Wire.begin();
expander.begin(INPUT);
expander1.begin(OUTPUT);

for(int i = 0; i <= 6; i++)
{
  expander1.write(i+2, LOW);
   expander.write(expanderPin[i], HIGH);
 }
 
}

 
void loop() {


char klawisz = 0; 
int x=0;
int y=0;
int b=0;



  switch(pozycja) { 
    case 1:


while(x != 4)
{
   klawisz = klawiatura.getKey();
   lcd.setCursor(0,0); 
  lcd.print("Kod Rozbrojenia: ");
  lcd.setCursor(x,1);
   lcd.noCursor();
  delay(50); 
  lcd.cursor(); 
  delay(50); 
 
  if(klawisz)
   {
    tone(4, 2000, 100); 
lcd.setCursor(x,1); 
  lcd.print("*");
  
   kodRozbrojenia[x]=klawisz;
    x++;
   }
   
}
delay(200);
  lcd.clear();

while(y != 6)
{ 
 
   klawisz = klawiatura.getKey();
    
   if(klawisz)
   {
tone(4, 2000, 100); 
if( klawisz >= '0' && klawisz <= '9')
   {
if(y == 1 || y == 3)
{
   b++;
 lcd.setCursor(b,1);
   lcd.noCursor();
  delay(110); 
  lcd.cursor(); 
  delay(110);
}
 czas[y]=klawisz; 
 y++;
 b++;
if(czas[0] >= '2'){czas[0] = '2';}
if(czas[1] >= '4' && czas[0] == '2'){czas[1]='4'; czas[2]='0'; czas[3]='0'; czas[4]='0'; czas[5]='0';}

if(czas[2] >= '5'){czas[2] = '5';}
if(czas[4] >= '5'){czas[4] = '5';}

}  
   }
   
lcd.setCursor(0,0); 
lcd.print("Czas Detonacji:");

lcd.setCursor(0,1);
 
lcd.print(czas[0]);
lcd.print(czas[1]);
lcd.print(":");
lcd.print(czas[2]);
lcd.print(czas[3]);
lcd.print(":");
lcd.print(czas[4]);
lcd.print(czas[5]);

 lcd.setCursor(b,1);
 lcd.noCursor();
 delay(50); 
 lcd.cursor(); 
 delay(50); 

}
pozycja=2;
    lcd.clear();


    break; 
    
    case 2:
    
 klawisz = klawiatura.getKey();

 lcd.noCursor();
 lcd.setCursor(0,0);
lcd.print("    Kliknij     ");
lcd.setCursor(0,1);
lcd.print("A-SAVE   B-BACK");

 if(klawisz)
 {
  tone(4, 2000, 100); 
if(klawisz == 'A'){  delay(1000); pozycja = 3; lcd.clear();}
if(klawisz == 'B'){   delay(1000); pozycja = 1; czas[0] = '0'; czas[1]='0'; czas[2]='0'; czas[3]='0'; czas[4]='0'; czas[5]='0'; lcd.clear();}
 }

    break;
    
    case 3:
    lcd.setCursor(0,0);
lcd.print(" Odliczanie Za:");
for(int i =9; i>= 0; i--)
{
  tone(4, 4000, 100); 
 
lcd.setCursor(0,1);
lcd.print("       ");
lcd.print(i);
delay(1000);
}
pozycja=4;
 lcd.clear();
  zapisanieCzasu();
    break;
    
    case 4:
  klawisz = klawiatura.getKey();
odliczanieCzasu();
buzzer();

 
for(int i = 0; i < 6; i++)
{
  if(expander.read(expanderPin[i]) == HIGH){expander1.write(i+2, HIGH);}
  else{expander1.write(i+2, LOW);}
}

 if(stan == true){lcd.backlight();}
  if(stan == false){lcd.noBacklight();}


   lcd.setCursor(0,1);
  lcd.print("Wpisz kod: ");
    lcd.setCursor(i+11,1);
   lcd.noCursor();
  delay(50); 
  lcd.cursor(); 
  delay(50); 
  

  
    if(i==4 && w!=4){ i=0; w=0; lcd.clear(); if(o == 12){pozycja=6; o =0; lcd.clear();}}
  if(w==4){pozycja=5; i=0; w=0; lcd.clear();}
if(godziny ==0 && minuty==0 && sekundy==0){pozycja=6;lcd.clear();}

if(klawisz)
   {
    tone(4, 2000, 100); 
lcd.setCursor(i+11,1); 
  lcd.print(klawisz);
if(kodRozbrojenia[i] == klawisz){w++;}
i++;
o++;
   }
   
   if(digitalRead(2) == LOW)
{
  ble();
  lcd.clear();
 }
 
    break;

    case 5:
 
 lcd.noCursor();
 lcd.setCursor(5,0); 
  lcd.print("bomb");
   lcd.setCursor(4,1); 
  lcd.print("Defuse");
  
  firstSection();
 
  secondSection();
 
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 350);  
  beep(a, 125);
  beep(cH, 500);
  beep(a, 375);  
  beep(cH, 125);
  beep(eH, 650);
  delay(500);
  secondSection();
  beep(f, 250);  
  beep(gS, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 500);  
  beep(f, 375);  
  beep(cH, 125);
  beep(a, 650);  
 
  delay(650);
    
    pozycja=1;
       lcd.clear();
  czas[0] = '0'; czas[1]='0'; czas[2]='0'; czas[3]='0'; czas[4]='0'; czas[5]='0';
    break;
    
    case 6:

 lcd.noCursor();
     lcd.setCursor(6,0); 
  lcd.print("bomb");
   lcd.setCursor(4,1); 
  lcd.print("Exploded");
for(int i =0; i<4; i++)
{
  for (int thisNote = 0; thisNote < songLength; thisNote++)
  {
    int duration = 1000/ durations[thisNote];
    tone(4, melody1[thisNote], duration);
    int pause = duration * 1.3;
    delay(pause);
    noTone(4);
  }
}

  
   pozycja=1;
    lcd.clear();
      czas[0] = '0'; czas[1]='0'; czas[2]='0'; czas[3]='0'; czas[4]='0'; czas[5]='0';
    break;
}
   }
    void zapisanieCzasu()
 {
   godziny = (czas[0]-'0')*10+(czas[1]-'0');
   minuty = (czas[2]-'0')*10+(czas[3]-'0');
   sekundy=(czas[4]-'0')*10+(czas[5]-'0');
 }
 
 void odliczanieCzasu()
 {
    aktualnyCzas = millis();

if(sekundy >= 0)
    {
      if(aktualnyCzas - zapamietanyCzas >= 1000UL)
      {
      zapamietanyCzas=aktualnyCzas;
     sekundy--;
      }
    }
    else{
    sekundy=59;
    if(minuty >= 0)
    {
      minuty--;
    }
    if(godziny>0 && minuty < 0)
    {
      minuty=59;
      godziny--;
    }
    }
     lcd.noCursor();
lcd.setCursor(4,0);
if(godziny ==0 && minuty ==0 && sekundy ==0){pozycja =5;}
if(godziny <= 9&&  godziny >= 0){ lcd.print("0");lcd.print(godziny);}
else{lcd.print(godziny);}
lcd.print(":");
if(minuty <= 9&&  minuty >= 0){ lcd.print("0");lcd.print(minuty);}
else{lcd.print(minuty);}
lcd.print(":");
if(sekundy <= 9&&  sekundy >= 0){ lcd.print("0");lcd.print(sekundy);}
else{lcd.print(sekundy);}
 }

 void buzzer()
 {
    aktualnyCzas1 = millis();
if(sekundy >=20 && sekundy <=30 && minuty == 0 && godziny ==0)
{
  if(aktualnyCzas1 - zapamietanyCzas1 >= 1000UL)
      {
      zapamietanyCzas1=aktualnyCzas1;
     tone(4, 4000, 100); 
      } 
}

if(sekundy >=15 && sekundy <=20 && minuty == 0 && godziny ==0)
{
  if(aktualnyCzas1 - zapamietanyCzas1 >= 700UL)
      {
      zapamietanyCzas1=aktualnyCzas1;
     tone(4, 4000, 100); 
      } 
}

if(sekundy >=10 && sekundy <=15 && minuty == 0 && godziny ==0)
{
  if(aktualnyCzas1 - zapamietanyCzas1 >= 300UL)
      {
      zapamietanyCzas1=aktualnyCzas1;
     tone(4, 4000, 100); 
      } 
}
if(sekundy >=5 && sekundy <=10 && minuty == 0 && godziny ==0)
{
  if(aktualnyCzas1 - zapamietanyCzas1 >= 150UL)
      {
      zapamietanyCzas1=aktualnyCzas1;
     tone(4, 4000, 100); 
      } 
}
if(sekundy >=0 && sekundy <=5 && minuty == 0 && godziny ==0)
{
  if(aktualnyCzas1 - zapamietanyCzas1 >= 100UL)
      {
      zapamietanyCzas1=aktualnyCzas1;
     tone(4, 4000, 100); 
      } 
}
}
void onStep()
{
 stan=!stan;
 
}

void ble()
{
   lcd.clear();
if(expander.read(expanderPin[0]) == LOW && expander.read(expanderPin[1]) == HIGH
&& expander.read(expanderPin[2]) == HIGH &&expander.read(expanderPin[3]) == LOW 
&& expander.read(expanderPin[4]) == HIGH &&expander.read(expanderPin[5]) == LOW)
{
  tone(4, 4000, 100); 
   lcd.noCursor();
lcd.setCursor(0,0);
  lcd.print("     UKLAD");
  lcd.setCursor(0,1);
  lcd.print("    POPRAWNY");
  delay(2000);
  pozycja = 5;
}
else{
  tone(4, 4000, 100); 
   lcd.noCursor();
lcd.setCursor(0,0);
  lcd.print("     UKLAD");
  lcd.setCursor(0,1);
  lcd.print("  NIEPOPRAWNY");
  delay(2000);
  pozycja=6;
 }
}
void beep(int note, int duration)
{
  //Play tone on buzzerPin
  tone(melodyPin, note, duration);
 
  //Play different LED depending on value of 'counter'
  if(counter % 2 == 0)
  {
    delay(duration);
  }else
  {
    delay(duration);
  }
 
  noTone(buzzerPin);
  delay(50);
  counter++;
}
 
void firstSection()
{
  beep(a, 500);
  beep(a, 500);    
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);  
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  delay(500);
 
  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);  
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  delay(500);
}
 
void secondSection()
{
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);    
  beep(fSH, 250);
 
  delay(325);
 
  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);  
  beep(cSH, 175);  
  beep(cH, 125);  
  beep(b, 125);  
  beep(cH, 250);  
 
  delay(350);
}
