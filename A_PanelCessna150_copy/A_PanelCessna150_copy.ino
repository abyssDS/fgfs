/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital
  pin 13, when pressing a pushbutton attached to pin 2.


  The circuit:
   LED attached from pin 13 to ground
   pushbutton attached to pin 2 from +5V
   10K resistor attached to pin 2 from ground

   Note: on most Arduinos there is already an LED on the board
  attached to pin 13.


  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Button
*/

// constants won't change. They're used here to
// assign pin numbers:
//SWITCH PARKING BRAKE
byte bat = 3;    // MASTER BATTERY
byte alt = 6;     //MASTER ALTERNATOR
byte cle = 1;    //NEYMAN SELECTOR OFF/R/L/BOTH
bool stateCle = false;
byte dem = 7;    //Starter command
byte pitot = 8;//PITOT HT
byte dome = 9;//DOME LT
byte nav = 5; //NAV_LIGHT
byte strobe = 2; //STROBE_LIGHT
byte bcn = 10;//BCN_LIGHT
byte taxi = 11;//TAXI_LIGHT
byte land = 4; //LDG_LIGHT
byte throttle = 2; //ControlRPM
byte mixture = 0; //Control Mixture

// variables will change state/value:
byte batState = 0; byte altState = 0;
int cleValue = 0; byte demState = 0; byte pitotState = 0; byte domeState = 0;
byte navState = 0; byte strobeState = 0; byte bcnState = 0; byte taxiState = 0; byte landState = 0;
float throttleValue = 0.0;
float mixtureValue = 0.0;

void setup() {
  // initialize the LED pin as an output:
  //pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  Serial.begin(9600);
  pinMode(strobe, INPUT);
  pinMode(bat, INPUT);  pinMode(alt, INPUT);
  pinMode(cle, INPUT); pinMode(dem, INPUT); pinMode(pitot, INPUT); pinMode(dome, INPUT);
  pinMode(nav, INPUT); pinMode(strobe, INPUT); pinMode(bcn, INPUT); pinMode(taxi, INPUT); pinMode(land, INPUT);
  pinMode(throttle, INPUT); pinMode(mixture, INPUT);
}

void loop() {
  neymanFunction();//ON or OFF contact motor
  Serial.print(stateCle); Serial.print(",");
  if (stateCle == true) { //si il y a un contact LEFT/RIGHT/BOTH
    demState = digitalRead(dem);
    Serial.print("demState :");
    Serial.print(demState); //delay(5000);
    Serial.print(",");
  }

  batState = digitalRead(bat);//check battery contact ON/OFF
  Serial.print(batState); Serial.print(",");

  lighting();
  Serial.print(navState); Serial.print(",");
  Serial.print(strobeState); Serial.print(",");
  Serial.print(bcnState); Serial.print(",");
  Serial.print(taxiState); Serial.print(",");
  Serial.print(landState); Serial.print(",");

  throttleMix();
  Serial.print(throttleValue, 3); Serial.print(",");
  Serial.print(mixtureValue, 3); Serial.print(",");
  delay(2000);
  Serial.print("\n");
}

void neymanFunction() {
  cleValue = analogRead(cle);
  cleValue =map(cleValue, 0, 1023, 0, 500);
  if (cleValue > 139 && cleValue < 180) {
    stateCle = true;
    Serial.print("LEFT MAGNETO");
    Serial.print(",");
  }
  else if (cleValue > 329 && cleValue < 360) {
    stateCle = true;
    Serial.print("RIGHT MAGNETO");
    Serial.print(",");
  }
  else if (cleValue > 470) {
    stateCle = true;
    Serial.print("BOTH MAGNETO");
    Serial.print(",");
  }
  else
    stateCle = false;
  Serial.print("OFF");
  Serial.print(",");
}

void lighting() {
  navState = digitalRead(nav); strobeState = digitalRead(strobe); bcnState = digitalRead(bcn);
  taxiState = digitalRead(taxi);  landState = digitalRead(land);
}

void throttleMix(){
  throttleValue = (analogRead(throttle)/1007.0)-0.99;
  mixtureValue = (analogRead(mixture)/1023.0)-0.99;
  
}

