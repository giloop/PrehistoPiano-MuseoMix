/*  Code Arduino
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
*/

#pragma once

#include "ofMain.h"

#define NBVIDS	4
#define NBSONS  9

class testApp : public ofSimpleApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased (int key);

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		// Gestion des sons
		ofSoundPlayer	sounds[NBSONS];
		ofVideoPlayer	vids[NBVIDS];
		int				idxVidPlaying;
		float			fadeLevel;

		// Affichage de la touche appuyée
		ofTrueTypeFont	testFont;
		char			letter;

		// carte Arduino
		ofSerial	  serial;
		char		  bytesReadString[5];
		unsigned char bytesReturned[5];
		bool		  bSerialInited;
		int			  accXLu, accYLu;
		float	      accX, accY;

		// Couleurs
		ofColor bgColor;
		ofColor letterColor;

		// Image de fond
		ofImage  logoPP;
		ofImage  imgFond;
		bool bFullScreen;
};

