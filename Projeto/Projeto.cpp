/* ==========================================================================
	Trabalho realizado por Fábio Santos 2020212310

   ==========================================================================
 */
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL\glut.h>

#define BLUE     0.0, 0.0, 1.0, 1.0
#define ORANGE   1.0, 0.5, 0.1, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define PI 3.14159

 // Observador
GLfloat  rVisao = 15, aVisao = PI / 4, incVisao = 1;
GLfloat  obsP[] = { rVisao * cos(aVisao), 5.0, rVisao * sin(aVisao) };
float     anguloZ = 35;

// Observador 3rd Person
GLfloat  obs3Person[] = { -12, 5.0, 0 };
GLfloat  paraOnde[] = { 4, 4, 0};
int thirdPerson = 0;

// Movimento carro
GLfloat theta = 0.;
GLfloat vel = 1.;
GLfloat pos[] = { 0., 0., 0. };

// Vidros
int vidro = 0;
GLfloat hVidro1 = -0.05f;
GLfloat hVidro2 = -0.05f;

// Limpa Vidros
GLfloat angPB = 0.0f;
int PB = 0;
int ida; // para saber se o parabrisas esta na ida ou na volta

void inicializa() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);*/

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
	glPushMatrix();
	glTranslatef(0, hVidro1, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(2, 1, -1.999);
	glVertex3f(4, 1, -1.999);
	glVertex3f(2, 3, -1.999);
	glEnd();
	glPopMatrix();

	// Vidro Pendura
	glPushMatrix();
	glTranslatef(0, hVidro2, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(2, 3, 1.999);
	glVertex3f(2, 1, 1.999);
	glVertex3f(4, 1, 1.999);
	glEnd();
	glPopMatrix();

	glPopMatrix();
	glDisable(GL_BLEND);

}

void desenhaParaBrisas() {

	// condutor
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(4, 1.1, -2);
	glRotatef(45, 0, 0, 1);
	glRotatef(-angPB, 1, 0, 0);
	glTranslatef(0, 0.05, 1);
	glScalef(0.05, 0.05, 1);
	desenhaCubo();
	glPopMatrix();

	// Pendura
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(4, 1.1, 0);
	glRotatef(45, 0, 0, 1);
	glRotatef(-angPB, 1, 0, 0);
	glTranslatef(0, 0.05, 1);
	glScalef(0.05, 0.05, 1);
	desenhaCubo();
	glPopMatrix();
}

void desenhaAmbulancia() {

	glPushMatrix();

	// Corpo da Ambulancia
	glColor3f(0.77, 0.6, 0);
	glPushMatrix();
	glScalef(4, 1, 2);
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

	// Rodas 
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glTranslatef(2,-1,2);
	glutSolidTorus(0.6, 0.6, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2, -1, -2);
	glutSolidTorus(0.6, 0.6, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2, -1, 2);
	glutSolidTorus(0.6, 0.6, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2, -1, -2);
	glutSolidTorus(0.6, 0.6, 15, 15);
	glPopMatrix();



	desenhaVidro();

	desenhaParaBrisas();

	glPopMatrix();

}


void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (vidro) {
		if (hVidro1 > -2) {
			hVidro1 -= 0.05;
		}
		if (hVidro2 > -2) {
			hVidro2 -= 0.05;
		}
	}
	else {
		if (hVidro1 < 0) {
			hVidro1 += 0.05;
		}
		if (hVidro1 == 0) {
			hVidro1 += 0.099;
		}
		if (hVidro2 < 0) {
			hVidro2 += 0.05;
		}
		if (hVidro2 == 0) {
			hVidro2 += 0.099;
		}
	}

	if (PB) { // 0 < x < -90
		if (angPB == 0) ida = 0;
		if (angPB == 90)  ida = 1;
		if (ida) angPB -= 5;
		else     angPB += 5;
	}

	// Observador 
	if (!thirdPerson) {
		glViewport(0, 0, 600, 500);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(85, (float)600 / 500, 0.1, 9999);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);

		drawEixos();


		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2]);
		glRotatef(theta, 0, 1, 0);
		desenhaAmbulancia();
		glPopMatrix();
	
	}
	// 3 Pessoa
	else {
		glViewport(0, 0, 600, 500);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(85, (float)600 / 500, 0.1, 9999);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluLookAt(obs3Person[0], obs3Person[1], obs3Person[2], paraOnde[0], paraOnde[1], paraOnde[2], 0, 1, 0);
		drawEixos();


		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2]);
		glRotatef(theta, 0, 1, 0);
		desenhaAmbulancia();
		glPopMatrix();

	}

	// Minimapa
	glViewport(0, 0, 600/4, 500/4);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, -10, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(pos[0], pos[1] + 5, pos[2], pos[0], 0, pos[2], 0, 0, -1);
	drawEixos();


	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(theta, 0, 1, 0);
	desenhaAmbulancia();
	glPopMatrix();

	glutSwapBuffers();
}

void teclasNotAscii(int key, int x, int y) {
	// Observador
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
		// Movimento carro
	case 'W': case 'w':
		pos[0] = pos[0] + vel * cos(theta * PI / 180.);
		pos[2] = pos[2] - vel * sin(theta * PI / 180.);

		obs3Person[0] = obs3Person[0] + vel * cos(theta * PI / 180.);
		obs3Person[2] = obs3Person[2] - vel * sin(theta * PI / 180.);

		paraOnde[0] = obs3Person[0] + vel * cos(theta * PI / 180.);
		paraOnde[2] = obs3Person[2] - vel * cos(theta * PI / 180.);

		glutPostRedisplay();
		break;
	case 'S': case 's':
		pos[0] = pos[0] - vel * cos(theta * PI / 180.);
		pos[2] = pos[2] + vel * sin(theta * PI / 180.);

		obs3Person[0] = obs3Person[0] - vel * cos(theta * PI / 180.);
		obs3Person[2] = obs3Person[2] + vel * sin(theta * PI / 180.);

		paraOnde[0] = obs3Person[0] + vel * cos(theta * PI / 180.);
		paraOnde[2] = obs3Person[2] - vel * cos(theta * PI / 180.);

		glutPostRedisplay();
		break;
	case 'A': case 'a':
		theta += 3.;
		glutPostRedisplay();
		break;
	case 'D': case 'd':
		theta -= 3.;
		glutPostRedisplay();
		break;

		// Limpa-Vidros
	case 'L': case 'l':
		if (!PB) PB = 1;
		else PB = 0;
		glutPostRedisplay();
		break;

		// Vidros
	case 'V': case 'v':
		if (!vidro) vidro = 1;
		else vidro = 0;
		glutPostRedisplay();
		break;

		// Troca Observador
	case 'P': case 'p':
		if (!thirdPerson) thirdPerson = 1;
		else thirdPerson = 0;
		glutPostRedisplay();
		break;

	}


}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(50, Timer, 1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 500);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Setas Andar | 'L' Limpar o vidro | V - Baixa os vidros");

	inicializa();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(Teclado);
	glutTimerFunc(50, Timer, 1);


	glutMainLoop();

	return 0;
}
