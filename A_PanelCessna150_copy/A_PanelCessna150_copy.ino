// constants won't change. They're used here to
// assign pin numbers:
//SWITCH PARKING BRAKE

byte cle = 0;    //A1 NEYMAN SELECTOR OFF/R/L/BOTH PIN
bool stateCle = false;
int ignition = 0;
byte throttle = 2; //A2 Control RPM PIN
byte mixture = 1; //A0 Control Mixture PIN

/*
byte flapspin[2] = {12, 13}; //Flaps assigned PIN
 byte flapsStt0 = 0; //variable position switch 1
 byte flapsStt1 = 0; //variable position switch 2
 byte flapsPos = 0; //variable flaps Position
 */
byte prk = 2; //Pilote Automatique
byte dem = 3;    //Starter command PIN
byte pitot = 4;//PITOT HT
//byte dome = 5;//DOME LT PIN
byte nav = 6; //NAV_LIGHT PIN
byte strobe = 7; //STROBE_LIGHT PIN
byte alt = 8;     //MASTER ALTERNATOR PIN
byte bat = 9;    // MASTER BATTERY PIN
byte bcn = 12;//BCN_LIGHT PIN
byte taxi = 11;//TAXI_LIGHT PIN
byte land = 10; //LDG_LIGHT PIN

// variables will change state/value:
byte prkState = 0;
byte batState = 0; 
byte altState = 0;
int cleValue = 0; 
byte demState = 0; 
byte pitotState = 0; 
//byte domeState = 0;
byte navState = 0; 
byte strobeState = 0; 
byte bcnState = 0; 
byte taxiState = 0; 
byte landState = 0;
float throttleValue = 0.0;
float mixtureValue = 0.0;

void setup() {
  // initialize the LED pin as an output:
  //pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  Serial.begin(9600);
  pinMode(prk, INPUT);
  pinMode(alt, INPUT); 
  pinMode(bat, INPUT);  
  pinMode(cle, INPUT); 
  pinMode(dem, INPUT);
  pinMode(pitot, INPUT); 
  //pinMode(dome, INPUT); 
  pinMode(nav, INPUT); 
  pinMode(strobe, INPUT); 
  pinMode(bcn, INPUT); 
  pinMode(taxi, INPUT); 
  pinMode(land, INPUT);
  pinMode(mixture, INPUT); 
  pinMode(throttle, INPUT);
  /*for (byte i = 0; i < 2; i++) {
   pinMode(flapspin[i], INPUT);
   }*/
}

void loop() {
  prkState = digitalRead(prk);
  Serial.print(prkState); 
  Serial.print(",");
  //Serial.print("af"); 


  altState = digitalRead(alt);//check Master-ALT contact ON/OFF
  Serial.print(altState); 
  Serial.print(",");
  //Serial.print("al"); 

  batState = digitalRead(bat);//check MASTER-BAT contact ON/OFF
  Serial.print(batState); 
  Serial.print(",");
  //Serial.print("ba"); 

  pitotState = digitalRead(pitot);
  Serial.print(pitotState); 
  Serial.print(",");
  //Serial.print("pit"); 
  /*
  domeState = digitalRead(dome);
   Serial.print(domeState); Serial.print(",");
   //Serial.print("dom"); */

  lighting();
  Serial.print(navState); 
  Serial.print(",");
  //Serial.print("nav"); 

  Serial.print(strobeState); 
  Serial.print(",");
  //Serial.print("stb"); 

  Serial.print(bcnState); 
  Serial.print(",");
  //Serial.print("bcn"); 

  Serial.print(taxiState); 
  Serial.print(",");
  //Serial.print("tax"); 

  Serial.print(landState); 
  Serial.print(",");
  //Serial.print("lan"); 
  
  throttleMix();
  Serial.print(throttleValue, 3); 
  Serial.print(","); 

  Serial.print(mixtureValue, 3); 
  Serial.print(",");
  
  neymanFunction();//ON or OFF contact motor
  Serial.print(ignition); 
  Serial.print(",");
  //Serial.print("ig"); 
  if (stateCle == true) { //si il y a un contact LEFT/RIGHT/BOTH
    demState = digitalRead(dem);
    Serial.print(demState); 
   //ial.print(",");
    //Serial.print("dem"); //delay(5000);
  }
  //flapsFunc();
  //Serial.println(flapsPos);

  //delay(2000);
  Serial.print("\n");
}

void neymanFunction() {//IGNITION SWITCH INT 0-1-2-3
  cleValue = analogRead(cle);
  cleValue = map(cleValue, 0, 1023, 0, 500);
  if (cleValue > 139 && cleValue < 180) {
    stateCle = true;
    ignition = 1 ;
    //Serial.print(ignition);
    //Serial.print(",");
  }
  else if (cleValue > 329 && cleValue < 360) {
    stateCle = true;
    ignition = 2 ;
    //Serial.print(ignition);
    //Serial.print(",");
  }
  else if (cleValue > 470) {
    stateCle = true;
    ignition = 3 ;
    //Serial.print(ignition);
    //Serial.print(",");
  }
  else{
    stateCle = false;
    ignition = 0;
    //Serial.print(ignition);
    //Serial.print(",");
  }
}

void lighting() {
  navState = digitalRead(nav); 
  strobeState = digitalRead(strobe); 
  bcnState = digitalRead(bcn);
  taxiState = digitalRead(taxi);  
  landState = digitalRead(land);
}

void throttleMix() {
  throttleValue = (analogRead(throttle) / 512.0) - 0.99;
  mixtureValue = (analogRead(mixture) / 512.0) - 0.99;
}
/*
void flapsFunc() {
 flapsStt0 = digitalRead(flapspin[0]);
 flapsStt1 = digitalRead(flapspin[1]);
 
 
 if (flapsStt0 == 1 && flapsPos < 3) {
 //Serial.println("trimPlus");
 flapsPos = flapsPos + 1;
 }
 else if (flapsStt1 == 1 && flapsPos > 0) {
 //Serial.println("trimMoin");
 flapsPos = flapsPos - 1;
 }
 }
 */


