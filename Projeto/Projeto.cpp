/* ==========================================================================
	Trabalho realizado por Fábio Santos 2020212310

   ==========================================================================
 */
#include <iostream>
#include <GL\glut.h>

#define BLUE     0.0, 0.0, 1.0, 1.0
#define ORANGE   1.0, 0.5, 0.1, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define PI 3.14159

// Observador
GLfloat  rVisao = 15, aVisao =  PI/4, incVisao = 1;
GLfloat  obsP[] = { rVisao * cos(aVisao), 5.0, rVisao * sin(aVisao) };
float     anguloZ = 35;

// Vidros
GLfloat hVidro = 0;

void inicializa() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);*/

	/*glVertexPointer(3, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);*/

}

void drawEixos()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo
	glColor4f(ORANGE);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0.5 * 20, 0, 0);
	glEnd();
	glColor4f(GREEN);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.5 * 20, 0);
	glEnd();
	glColor4f(BLUE);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.5 * 20);
	glEnd();
}

void desenhaCubo() {

	//Face da frente
	glBegin(GL_POLYGON);
	glVertex3f(1, 1, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, -1, 1);
	glVertex3f(1, -1, 1);
	glEnd();
	//Face da trás
	glBegin(GL_POLYGON);
	glVertex3f(1, 1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);
	glEnd();
	//Face da Esquerda
	glBegin(GL_POLYGON);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 1);
	glEnd();
	//Face da Direita
	glBegin(GL_POLYGON);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);
	glEnd();
	//Face de Cima
	glBegin(GL_POLYGON);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, 1, 1);
	glEnd();
	//Face de baixo
	glBegin(GL_POLYGON);
	glVertex3f(1, -1, 1);
	glVertex3f(1, -1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 1);
	glEnd();
	

}

void desenhaVidro() {

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.6, 0.8, 0.9, 0.5);

	glPushMatrix();

	// Parte Frontal
	glBegin(GL_POLYGON);
	glVertex3f(2, 3, 2);
	glVertex3f(4, 1, 2);
	glVertex3f(4, 1, -2);
	glVertex3f(2, 3, -2);
	glEnd();

	// Vidro Condutor
	glBegin(GL_TRIANGLES);
	glVertex3f(2, 1, -2);
	glVertex3f(4, 1, -2);
	glVertex3f(2, 3, -2);
	glEnd();

	// Vidro Pendura
	glBegin(GL_TRIANGLES);
	glVertex3f(2, 3, 2);
	glVertex3f(2, 1, 2);
	glVertex3f(4, 1, 2);
	glEnd();

	glPopMatrix();
	glDisable(GL_BLEND);

}

void desenhaAmbulancia() {

	glPushMatrix();

	// Corpo da Ambulancia
	glColor3f(0.77, 0.6, 0);
	glPushMatrix();
	glScalef(4,1,2);
	desenhaCubo();
	glPopMatrix();

	// Parte traseira ao vidro (azul)
	glColor3f(0, 0, 1);
	glPushMatrix();
	glTranslatef(-1, 1.501, 0);
	glScalef(3, 0.5, 2);
	desenhaCubo();
	glPopMatrix();

	// Parte traseira ao vidro (amarela)
	glColor3f(0.77, 0.6, 0);
	glPushMatrix();
	glTranslatef(-1, 2.502, 0);
	glScalef(3, 0.5, 2);
	desenhaCubo();
	glPopMatrix();

	desenhaVidro();

	glPopMatrix();


}


void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, 600, 500);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(85, (float)600 / 500, 0.1, 9999);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);

	drawEixos();

	desenhaAmbulancia();

	glutSwapBuffers();
}

void teclasNotAscii(int key, int x, int y) {

	//=========================================================
	//  <><><><><><>  Movimento do observador  ???
	//=========================================================
	if (key == GLUT_KEY_UP) {
		obsP[1] += 0.2;
	}    // Movimento para cima
	if (key == GLUT_KEY_DOWN) {
		obsP[1] -= 0.2;
	}  // Movimento para baixo
	if (key == GLUT_KEY_LEFT) {
		aVisao += 0.1;
		obsP[0] = rVisao * cos(aVisao);
		obsP[2] = rVisao * sin(aVisao);
	}  // Movimento para a esquerda
	if (key == GLUT_KEY_RIGHT) {
		aVisao -= 0.1;
		obsP[0] = rVisao * cos(aVisao);
		obsP[2] = rVisao * sin(aVisao);
	} // Movimento para a direira

	glutPostRedisplay();
}

void Teclado(unsigned char key, int x, int y) {

	switch (key) {
		// Limpa-Vidros
	case 'l':

		break;
		// Sirene
	case 's':


		break;
	}

}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(0.5, Timer, 1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 500);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Setas Andar | 'L' Limpar o vidro | S - Ligar Sirene");

	inicializa();

	glutDisplayFunc(display);
	glutSpecialFunc(teclasNotAscii);
	glutKeyboardFunc(Teclado);
	glutTimerFunc(0.5, Timer, 1);


	glutMainLoop();

	return 0;
}
