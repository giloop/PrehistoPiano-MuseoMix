#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);

	testFont.loadFont("arial.ttf", 400, true, true, true);
	/* Chargement des sons */
	fprintf(stdout, "Chargement des sons ...\n");
	sounds[0].loadSound("sounds/PrehistoPiano - Note_01.mp3");
	sounds[1].loadSound("sounds/PrehistoPiano - Note_02.mp3");
	sounds[2].loadSound("sounds/PrehistoPiano - Note_03.mp3");
	sounds[3].loadSound("sounds/PrehistoPiano - Note_04.mp3");
	sounds[4].loadSound("sounds/PrehistoPiano - Note_05.mp3");
	sounds[5].loadSound("sounds/PrehistoPiano - Note_06.mp3");
	sounds[6].loadSound("sounds/PrehistoPiano - Note_07.mp3");
	sounds[7].loadSound("sounds/PrehistoPiano - Note_08.mp3");
	sounds[8].loadSound("sounds/PrehistoPiano - Note_09.mp3");
	
	// Initialisation de la liaison série
	bSerialInited = serial.setup("COM4",57600);
	if (!bSerialInited) {
		printf("Warning : Could not initialize serial COM4\n");
	} else {
		printf("Serial initialized on COM4\n");
		serial.flush(true, true);
	}
	memset(bytesReadString, 0, 12);
	accXLu = 350; accYLu = 500; 
	accX = 350.0; accY = 500.0;
	// Chargement des vidéos
	vids[0].setPixelFormat(OF_PIXELS_RGBA);
	vids[0].loadMovie("vids/obj01_Racloir_640.mov");
	vids[1].setPixelFormat(OF_PIXELS_RGBA);
	vids[1].loadMovie("vids/obj02_TailleSilex_640.mov");
	vids[2].setPixelFormat(OF_PIXELS_RGBA);
	vids[2].loadMovie("vids/obj06_BoisDeCerf_640.mov");
	vids[3].setPixelFormat(OF_PIXELS_RGBA);
	vids[3].loadMovie("vids/obj07_TailleViande_640.mov");
	
	// Tout en pause au démarrage
	idxVidPlaying = -1;
	fadeLevel = 255; // opaque

	bFullScreen = false;
	ofSetFullscreen(bFullScreen);
	
	// Définition des couleurs
	bgColor.set(255,255,255);
	letterColor.set(41,81,117);
	
	// Chargement des images
	logoPP.loadImage("logoPP.png");
	logoPP.resize(145,149); // (,); 
	imgFond.loadImage("imageFond.png");
	
	ofFill();

}

//--------------------------------------------------------------
void testApp::update(){
	// Mise à jour des sons
	ofSoundUpdate();
	int nRead  = 0;
	// Mise à jour des vidéos
	for (int idx=0; idx<NBVIDS; idx++) { vids[idx].update(); }
	
	// Lecture Série !
	memset(bytesReadString, 0, 12);
	int byte1;
	if (bSerialInited) {
		if (serial.available()>0) {
			byte1 = serial.readByte();
			// printf("byte1 : %d\n", byte1);
			nRead = serial.readBytes(bytesReturned, 4);
			memcpy(bytesReadString, bytesReturned, nRead);
			// printf("suite : %s (int[0] = %d)\n", bytesReadString, bytesReadString[0]);
			if (byte1==88 && bytesReadString[0]!=0) { // accX
				accXLu = atoi(bytesReadString);
				accX *= 0.985;
				accX += 0.015 * float(accXLu);
			}
			if (byte1==89 && bytesReadString[0]!=0) { // accX
				accYLu = atoi(bytesReadString);
				accY *= 0.985;
				accY += 0.015 * float(accYLu);
			}
		}
	};

	// Mise à jour accéléromètre
	if (accX >= 400.0 && accX <= 510.0){
		if (!sounds[4].getIsPlaying()) { sounds[4].play(); }
		float speed = (accX - 400.0) / 110.0;
		float pan = (accX - 425.0) / 200.0;
		if (speed<-0.5) speed = -0.5;
		if (speed>0.5) speed = 0.5;
		if (pan<-1) pan = -1;
		if (pan>1) pan = 1;
		sounds[4].setSpeed( 0.5f + speed);
		sounds[4].setPan( 0.5f + pan);
		//printf("Play Cerf - speed : %.2f\n");
	} else {
		//printf("Stop Cerf !!!\n");
		if (sounds[4].getIsPlaying()) { sounds[4].stop(); }
	}
}

//--------------------------------------------------------------
void testApp::draw() {
	if (idxVidPlaying==-1) { ofBackground(255,255,255); }
	char tempStr[128];
	if (bSerialInited) {
		sprintf(tempStr, "accX : %.1f\naccY : %.1f\n", accX, accY);
	} else {
		sprintf(tempStr, "arduino non connectée");
	}
	
	ofSetColor(letterColor);
	ofDrawBitmapString(tempStr, 512, ofGetHeight()-20);
	
	ofSetColor(bgColor);
	//imgFond.draw(ofGetWidth()-imgFond.width,  ofGetHeight()-imgFond.height);
	//logoPP.draw(20, 20);
	imgFond.draw(0.5*(ofGetWidth()-imgFond.width), 0);
	logoPP.draw(10, ofGetHeight()-logoPP.height-10);

	
	// Une seule vidéo à la fois 
	if (idxVidPlaying>=0) {
		ofBackground(0,0,0);
		// printf("Lecture video %d", idxVidPlaying);
		vids[idxVidPlaying].draw(0.5*(ofGetWidth()-vids[idxVidPlaying].width),0.5*(ofGetHeight()-vids[idxVidPlaying].height));
	}
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	int idxNewSnd, idxNewVid;
	// Special keys : return (13), tab key (9), backspace(8) ...
	fprintf(stdout, "keyPressed %c, code %d\n", key, (int) key);
	
	idxNewVid = -1;
	idxNewSnd = -1;
	switch (key) {
	case 113:
		printf("Obj 1\n");
		idxNewSnd = 0;
		idxNewVid = 0;
		break;
	case 32:
		printf("Obj 2\n");
		idxNewSnd = 1;
		idxNewVid = 1;
		break;
	case 359:
		printf("Obj 3\n");
		idxNewSnd = 2;
		break;
	case 122:
		printf("Obj 4\n");
		idxNewSnd = 3;
		//idxNewVid = 3;
		break;
	//case 102:
	//	printf("Obj 5\n");
	//	idxNewSnd = 4;
	//	break;
	case 103:
		printf("Obj 6\n");
		idxNewSnd = 5;
		idxNewVid = 2;
		break;
	case 357:
		printf("Obj 7\n");
		idxNewSnd = 6;
		idxNewVid = 3;
		break;
	case 102:
		printf("Obj 8\n");
		idxNewSnd = 7;
		break;
	case 356:
		printf("Obj 9\n");
		idxNewSnd = 8;
		break;
	}

	// Lecture Sons ?
	if (idxNewSnd>=0) {
		printf("Playsound %d\n", idxNewSnd);
		if (!sounds[idxNewSnd].getIsPlaying()) {
			sounds[idxNewSnd].play();
		}
	}

	// Lecture Vidéo ?
	if (idxNewVid>=0 && idxNewVid != idxVidPlaying) {
		// Arrêt vidéo en cours
		if (idxVidPlaying>=0) { 
			printf("Arret video %d\n", idxNewSnd);
			vids[idxVidPlaying].stop(); 
		}
		// Mise à jour indice vidéo à jouer
		idxVidPlaying = idxNewVid;
		printf("Lecture video %d\n", idxNewVid);
		vids[idxVidPlaying].play();
	}

}

//--------------------------------------------------------------
void testApp::keyReleased  (int key) {
	int idxSndStop, idxVidStop;
	
	idxSndStop = -1;
	idxVidStop = -1;

	fprintf(stdout, "keyReleased %c, code %d\n", key, (int) key);
	switch (key) {
	case 113:
		printf("Obj 1\n");
		idxSndStop = 0;
		idxVidStop = 0;
		break;
	case 32:
		printf("Obj 2\n");
		idxSndStop = 1;
		idxVidStop = 1;
		break;
	case 359:
		printf("Obj 3\n");
		idxSndStop = 2;
		break;
	case 122:
		printf("Obj 4\n");
		idxSndStop = 3;
		//idxVidStop = 3;
		break;
	//case 102:
		//printf("Obj 5\n");
		//idxSndStop = 4;
		//break;
	case 103:
		printf("Obj 6\n");
		idxSndStop = 5;
		idxVidStop = 2;
		break;
	case 357:
		printf("Obj 7\n");
		idxSndStop = 6;
		idxVidStop = 3;
		break;
	case 102:
		printf("Obj 8\n");
		idxSndStop = 7;
		break;
	case 356:
		printf("Obj 9\n");
		idxSndStop = 8;
		break;
	}

	// Arrêt Sons ?
	printf("Arret sons\n");
	if (idxSndStop>=0) {
		if (sounds[idxSndStop].getIsPlaying()) {
			sounds[idxSndStop].stop();
		}
	}

	// Lecture Vidéo ?
	printf("Arret video\n");
	if (idxVidStop>=0) {
		// Arrêt vidéo en cours
		if (idxVidPlaying==idxVidStop) { 
			vids[idxVidStop].stop(); 
			vids[idxVidStop].setPosition(0.0);
			idxVidPlaying = -1; // Reset le statut des vidéos
			fadeLevel = 0;
		}
	}

	// M pour fullscreen
	if (key=='m') {
		bFullScreen = !bFullScreen;
		ofSetFullscreen(bFullScreen);
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	/*if ((y>ofGetHeight()-30) && !bURLlaunched) {
		ofLaunchBrowser("http://museomix.org");
		bURLlaunched = true;
	}*/
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
