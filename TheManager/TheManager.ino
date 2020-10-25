
/* THE TASK MANAGER
 *  
 * 
 * The Task Manager can be used to distribute tasks during a live game version of AmongUs/Werewolf/Mafioso
 * The Task Manager gives out random tasks and regions (you need to edit these to fit your needs) and also has the capability to show 
 * remaining time for game rounds and play a sound after a round ends. Each round begins with the first button press and ends 
 * when the timer reaches zero. If confused, read the game rules :)
 * 
 * Tutorial I used to figure out millis: https://www.baldengineer.com/use-millis-with-buttons-to-delay-events.html
 * Mighty lot of help received by reading several topics at: https://forum.arduino.cc/
 * 
 * 
 */

#include <LiquidCrystal.h>
#include <TM1637Display.h>


// define the pins that are in use

#define CLK 6               
#define DIO 7              

#define Button 13          
#define Piezo 8            


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// set here the time you want one round of game to last (good round time could be 4 minutes, one game lasting several rounds)

int RoundMinutes = 4;       
int RoundSeconds = 0;       

TM1637Display display(CLK, DIO);
uint8_t data[] = {0, 0, 0, 0};

int task;                   // used to randomly select a task for the player
int region;                 // used to randomly select a region for the player
int ButtonState = 0;        // current state of the button
int oldButtonState = 0;     // previous state of the button
boolean countdown = false;  // boolean to check if we should be counting down, or waiting for next round
int Minutes = RoundMinutes; // Temporary value 
int Seconds = RoundSeconds; // Temporary value 

unsigned long previousMillis = 0;    // Avoiding delay() by using Millis to run multiple things at the same time (countdown not affected by button presses)
unsigned long interval = 1000;       // Setting countdown interval to 1000ms (1s)


void setup() {
pinMode(Button, INPUT);     // button can now give us INPUT
lcd.begin(16, 2);           // LCD size is width: 16, height: 2
randomSeed(analogRead(0));  // this will make our random more ramdom
lcd.print("!LOOP ERROR!");  // if you see this, you messed up something within the loop, yikes!
}


void loop() {

ButtonState = digitalRead(Button);                 
unsigned long currentMillis = millis();             
display.showNumberDecEx(Seconds, 0x00, true, 2, 2); 
display.showNumberDecEx(Minutes, 0x40, true, 2, 0); 

  if (ButtonState != oldButtonState) 
  {  
     
    if (ButtonState == LOW) 
    { 
     countdown = true;         // this starts the clock (round), if it's not already started
     task = random(6);
     region = random(6);
     lcd.clear();
     lcd.setCursor(0,0);
 

     // Tasks and regions. Please edit. Confused? See Game Rules for explanation on what to put here.
     switch(task){
     case 0:
     lcd.print("1 Tarkista halot");
     break;
     case 1:
     lcd.print("1 Tarkista vesi");
     break;
     case 2:
     lcd.print("1 Tarkista WC");
     break;
     case 3:
     lcd.print("1 Tarkista tie");
     break;
     case 4:
     lcd.print("1 Tarkista ovet");
     break;
     case 5:
     lcd.print("1 Tarkista valot");
     break;
    }

    lcd.setCursor(0,1);
    
     switch(region){
     case 0:
     lcd.print("2 Tutki puuvaja");
     break;
     case 1:
     lcd.print("2 Tutki sauna");
     break;
     case 2:
     lcd.print("2 Tutki huussi");
     break;
     case 3:
     lcd.print("2 Tutki nuotio");
     break;
     case 4:
     lcd.print("2 Tutki terassi");
     break;
     case 5:
     lcd.print("2 Tutki metsa");
     break;
     }

 }

    if (ButtonState == HIGH) 
    { 
     lcd.clear();
     lcd.setCursor(0,0);        
     lcd.print("Pida nappia");  
     lcd.setCursor(0,1);     
     lcd.print("pohjassa");   
    }
          
 } 
    
  oldButtonState = ButtonState; 

// COUNTDOWN TIMER, with sound <3
  display.setBrightness(0x0f);

  data[4] = display.encodeDigit(Seconds % 10);
  data[3] = display.encodeDigit(Seconds / 10);
  data[2] = display.encodeDigit(Minutes % 10);
  data[1] = display.encodeDigit(Minutes % 10);
  data[0] = display.encodeDigit(Minutes / 10);
 
  if (currentMillis - previousMillis > interval && countdown == true) 
  {
   previousMillis = currentMillis;
   
    if (Seconds > 0) 
    {
     Seconds -= 1;
    } 
    else 
    {
      if (Minutes > 0) 
        {
        Seconds = 59;
        Minutes -= 1;
        }
    }
  }
  
  if(Minutes == 0 && Seconds == 0) 
  {   // after counting down to zero, we setup a new round, play a sound and wait for a button press to start the countdown again
    Minutes = RoundMinutes;
    Seconds = RoundSeconds;
    tone(Piezo,10000,1000);
    countdown = false;
  }
  
}
