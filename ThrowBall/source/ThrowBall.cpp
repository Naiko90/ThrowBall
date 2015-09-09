#include "ThrowBall.h"
#include <sstream>

void init() {
    GLfloat mat1_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat1_shininess[] = {60.0};
    GLfloat light1_diffuse[] = {0.6, 0.6, 0.6, 1.0};
    GLfloat ambient_lightModel[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_lightModel);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat1_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat1_shininess);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light1_diffuse);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT3); glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT1); glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_CULL_FACE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	// Load meshes
	loader = new AssimpSimpleModelLoader(resourceDir,modelDir,textureDir,modelName);
	loader->LoadGLTextures(loader->getScene());

	// Initialize room
	room = new Room(_level);

	// Initialize player
    player = new Player(_level);

	// Initialize bin
	bin = new Bin(0.4, _level, 100);
}

void drawStrokeCharacter(float x, float y, float z, char *string) {
    char *c;
    glPushMatrix();
    glScalef(0.005, 0.005, 1);
    glLineWidth(3.0);
    glTranslatef(x, y, z / 1000);
    for (c = string; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
}

void printInstruction() {
	cout << "Throw Ball!" << endl;
	cout << "You can change view using W,A,D,X, and rotate it to the right and to the left using Q and E" << endl;
	cout << "To reposition the ball in the last launch position, simply press F" << endl;
	cout << "To reposition the ball in the initial position, simply press press R" << endl;
	// cout << "Difficulty can be changed by pressing the right button of the mouse." << endl;
	cout << "To throw the ball just press S, you will need to select the strength and the right angle..." << endl;
	cout << "GOOD LUCK! :)" << endl;
	cout << endl;
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {
        case 27:
            exit(0); break;
        case 'e':	// Ruota visuale verso dx
            player->lookX(1); break;
        case 'q':	// Ruota visuale verso sx
            player->lookX(-1); break;
        case 's':	
        {//stato 0 partenza stato 1 carica angolo stato 2 carica forza stato 3 palla in volo
			if (!player->ballInTheAir())  {
                if (player->getPhase() == 0) {
                    player->setPhase(1);
                } else if (player->getPhase() == 1) {
                    player->setPhase(2);
                } else {
                    player->throwBall();
                }
            }
			break;
        }
        case 'w':	// Muovi giocatore avanti
            player->moveForwardBack(FORWARD); break;
        case 'x':	// Muovi giocare indietro
            player->moveForwardBack(BACK); break;
        case 'd':	// Muovi giocatore verso dx
            player->moveRightLeft(RIGHT); break;
        case 'a':	// Muovi giocare verso sx
            player->moveRightLeft(LEFT); break;
        case 'f':	// Riposiziona palla nell'ultima posizione di tiro
            player->resetBall(loader); break;
		case 'r':	// Riposiziona palla nella posizione di partenza
			player->restart(_level); break;
		// Used just for debugging purpose
		/*case 't':
			player->showTrack();
			break;*/
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    windowWidth = w; windowHeight = h;
}

void setLookAt() {
    Vector3D* lookAtEye=NULL;
    Vector3D* lookAtCenter=NULL;
	Vector3D upVector(0.0,1.0,0.0);
    lookAtEye = player->getLookAtEye();
    lookAtCenter = player->getLookAtCenter();
    gluLookAt(lookAtEye->getValueAt(X), lookAtEye->getValueAt(Y), lookAtEye->getValueAt(Z),
            lookAtCenter->getValueAt(X), lookAtCenter->getValueAt(Y), lookAtCenter->getValueAt(Z),
            upVector.getValueAt(X), upVector.getValueAt(Y), upVector.getValueAt(Z));
}

void showScore() {
	glDisable(GL_LIGHTING);
	char* tempString = new char[40];
    Vector3D* lookAtEye = player->getBallPos();
	sprintf_s(tempString, 40, "Scored %d on %d",player->getScore(), player->getThrows());
    glColor3d(0.0,0.0,0.0);
    drawStrokeCharacter(250, 800, 1600, tempString);
    delete tempString;
	glEnable(GL_LIGHTING);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double asp = (double) windowWidth / (double) windowHeight;
    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport (0, 0, windowWidth, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glColor3d(1.0,1.0,1.0);
    glLoadIdentity();
    glFrustum(-1 * asp, 1 * asp, -1, 1, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    setLookAt();

	// Draw room
	glDisable(GL_CULL_FACE);
    room->drawRoom();
    glEnable(GL_CULL_FACE);

	// Draw player
	player->drawPlayerState(loader);

	// Draw bin
	bin->drawBin(loader);
	glDisable(GL_COLOR_MATERIAL);
    
	// Show score
	showScore();
	
    glutSwapBuffers();
}

void processMenuEvents(int option) { // Callback function
    switch (option) {
		delete room;
		delete player;
        case 1:
			room = new Room(EASY);
			player = new Player(EASY);
            break;
        case 2:
			room = new Room(MEDIUM);
			player = new Player(MEDIUM);
            break;
		case 3:
			room = new Room(HARD);
			player = new Player(HARD);
			break;
    }
}

void createMenus() {
    int submenu = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("Easy", 1);
    glutAddMenuEntry("Medium", 2);
	glutAddMenuEntry("Hard", 3);

    int menu = glutCreateMenu(processMenuEvents);
    glutAddSubMenu("Level", submenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void update(int value) {
	glutPostRedisplay();
	glutTimerFunc(TIMER_MS, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - windowWidth)/2,
							(glutGet(GLUT_SCREEN_HEIGHT) - windowHeight)/2);
    glutCreateWindow(argv[0]);
    init();
	printInstruction();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
	glutTimerFunc(TIMER_MS, update, 0);
	glutIdleFunc(display);
    // createMenus();
    glutMainLoop();
    return 0;
}
