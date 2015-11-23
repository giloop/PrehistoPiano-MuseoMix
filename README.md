# PrehistoPiano-MuseoMix
Projet #TeamBrigitte pour Muséomix Rennes 

Ce dépot contient : 
- le code Source C++ sous forme de projet openFrameworks : http://openframeworks.cc )
- l'exécutable de l'application, fichier PrehistoPiano-exe.zip (avec les sons et vidéos réduites pour la miseen ligne).

Mode d'emploi PréhistoPiano
----------------------------

- Lancez l'exécutable. 
- Appuyez sur la touche 'm' pour basculer en mode plein écran. 
- Les touches qui lancent les sons / vidéos sont : 
  PrehistoPiano - Note_01.wav : 'q' 		 | obj01_Racloir_640.mov
  PrehistoPiano - Note_02.wav : ' ' (espace) | obj02_TailleSilex_640.mov
  PrehistoPiano - Note_03.wav : Flêche Bas
  PrehistoPiano - Note_04.wav : 'z'
  PrehistoPiano - Note_05.wav : Branché à l'accéléromètre
  PrehistoPiano - Note_06.wav : 'g'  		 | obj06_BoisDeCerf_640.mov
  PrehistoPiano - Note_07.wav : Flêche Haut  | obj07_TailleViande_640.mov
  PrehistoPiano - Note_08.wav : 'f'
  PrehistoPiano - Note_09.wav : Flêche Gauche
  
- Si vous avez une Makey Makey vous pouvez l'utiliser et relier ce que vous voulez

- Un des samples se lance à partir des données d'un accéléromètre 2 axes de TinkerKit 
  branché sur une Arduino. Le code est donné ci-dessous. 


// ----------------------
// Code Arduino
//  Lecture de l'accéléromètre 2 axes de TinkerKit depuis Openframeworks
//  Created by Gilles Gonon
//  pour Muséomix 2015
// 
//  This example code is in the public domain. 

int accX = A0;    // select the input pin for the accX
int accY = A1;    // select the input pin for the accY
int accXval = 0;  // value coming from accX
int accYval = 0;  // value coming from accY
boolean bX;
void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(57600);
  bX = true;
}

void loop() {
  // read the value from the sensor:
  accXval = analogRead(accX);    
  accYval = analogRead(accY);    
  
  if (bX) {
    Serial.print("X");
    Serial.println(accXval);
    bX = false;
  } else {
    Serial.print("Y");
    Serial.println(accYval); 
    bX = true;
  }
  delay(15);
}
// FIN DU CODE ARDUINO
// ----------------------
