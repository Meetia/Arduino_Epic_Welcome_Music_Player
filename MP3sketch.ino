int LED = 5; //initializing the LED
int trackNumber;
int randNumber;
#include <SPI.h> //including all the libraries
#include <SdFat.h>
#include <SdFatUtil.h> 
#include <SFEMP3Shield.h>

//#define SCI_VOL 0x0B //VS10xx SCI Registers

//Sd2Card card;
//SdVolume volume;  //volume variable to be used by SdFat Library


SFEMP3Shield MP3player;
void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);  //for the LED on the breadboard to make sure it's working
  MP3player.begin(); //starts the MP3 player
  randomSeed(analogRead(5)); //to play a random track
  MP3player.SetVolume(10, 10);
  //if (!volume.init(&card)) Serial.println("Error: Volume ini"); //Initialize a volume on the SD card.
  //Mp3SetVolume(20, 20); //Set initial volume (20 = -10dB) LOUD
  //Mp3SetVolume(40, 40); //Set initial volume (20 = -10dB) Manageable
  //Mp3SetVolume(80, 80); //Set initial volume (20 = -10dB) More quiet

}

void loop() {
  // read the input on analog pin 0 & 2:
  int buttonValue = analogRead(A4);
  int sensorValue = analogRead(A0);
  int switchValue = analogRead(A2);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  float voltage1 = switchValue * (5.0 / 1023.0);
  float voltage2 = buttonValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.print("Sensor: ");
  Serial.println(voltage);
  Serial.print("Switch: ");
  Serial.println(voltage1);
  Serial.print("Button: ");
  Serial.println(voltage2);
  Serial.println(" ");
  if(voltage1 > 3)
  {
    sensorValue = analogRead(A0); 
    switchValue = analogRead(A2);
    randNumber = random(1,94);
    voltage = sensorValue * (5.0 / 1023.0);
    voltage1 = switchValue * (5.0 / 1023.0);
    Serial.print("Sensor: ");
    Serial.println(voltage);
    Serial.print("Switch: ");
    Serial.println(voltage1);
    Serial.print("Button: ");
    Serial.println(voltage2);
    Serial.println(" ");
    if(voltage < 3)
    {
      if(voltage2 < 3)
      {
        trackNumber = randNumber;
        MP3player.playTrack(randNumber);
        digitalWrite(LED, HIGH);
      }
      else
      {
        MP3player.stopTrack();
        if(trackNumber == 93)
        {
          trackNumber = 1;
        }
        else
        {
          trackNumber ++;
        }
        MP3player.playTrack(trackNumber);
        delay(50);
      }

    }
    else
    {
      digitalWrite(LED, LOW);
    }
  }
  else
  {
    digitalWrite(LED, LOW);
    MP3player.stopTrack();
  }
}

//Set VS10xx Volume Register
//void Mp3SetVolume(unsigned char leftchannel, unsigned char rightchannel){
//Mp3WriteRegister(SCI_VOL, leftchannel, rightchannel);
//}







