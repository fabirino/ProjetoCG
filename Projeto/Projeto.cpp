/* ==========================================================================
	Trabalho realizado por Fábio Santos 2020212310

   ==========================================================================
 */
#include "RgbImage.h"

#include <iostream>
#include <math.h>
#include <GL\glut.h>

#define BLUE     0.0, 0.0, 1.0, 1.0
#define ORANGE   1.0, 0.5, 0.1, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define PI 3.14159

 // Observador ==========================================================================
GLfloat  rVisao = 15, aVisao = PI / 4, incVisao = 1;
GLfloat  obsP[] = { rVisao * cos(aVisao), 5.0, rVisao * sin(aVisao) };
float     anguloZ = 35;

// Observador 3rd Person ================================================================
GLfloat  obs3Person[] = { -12, 5.0, 0 };
GLfloat  paraOnde[] = { 4, 4, 0 };
int thirdPerson = 0;

// Movimento carro ======================================================================
GLfloat theta = 0.;
GLfloat vel = 1.;
GLfloat pos[] = { 0., 0., 0. };

// Vidros ===============================================================================
int vidro = 0;
GLfloat hVidro1 = -0.05f;
GLfloat hVidro2 = -0.05f;

// Limpa Vidros =========================================================================
GLfloat angPB = 0.0f;
int PB = 0;
int ida; // para saber se o parabrisas esta na ida ou na volta

// Textura ==============================================================================
GLuint texture;
RgbImage imag;

// Luz Pontual ==========================================================================
GLfloat intensidadeLuz = 0.7;
GLfloat PosLuz[4] = { 5.0, 5.0, 5.0, 1.0 };
GLfloat localCorAmb[4] = { 0, 0, 0, 0.0 };
GLfloat localCorDif[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat localCorEsp[4] = { 1.0, 1.0, 1.0, 1.0 };

// Cor Materiais ========================================================================


// =#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#
// =#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#

void inicializa() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Textura =========================================================
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	imag.LoadBmpFile("Louis-Vuitton-Pattern.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	// Luz ==============================================================
	glLightfv(GL_LIGHT0, GL_POSITION, PosLuz);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);

	// Materiais + Cor

	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);*/


}

void drawEixos(){
	GLfloat whitePlasticAmb[] = { 0.8 ,0.8 ,0.8 };
	GLfloat whitePlasticDif[] = { 0.55 ,0.55 ,0.55 };
	GLfloat whitePlasticSpec[] = { 0.870 ,0.870 ,0.870 };
	GLint whitePlasticCoef = 0.25 * 128;

	//glColor4f(ORANGE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, whitePlasticAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, whitePlasticDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, whitePlasticSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, whitePlasticCoef);

	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0.5 * 20, 0, 0);
	glEnd();


	//glColor4f(GREEN);
	glMaterialfv(GL_FRONT, GL_AMBIENT, whitePlasticAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, whitePlasticDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, whitePlasticSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, whitePlasticCoef);

	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.5 * 20, 0);
	glEnd();


	//glColor4f(BLUE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, whitePlasticAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, whitePlasticDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, whitePlasticSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, whitePlasticCoef);

	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.5 * 20);
	glEnd();
}

void desenhaCubo() {

	//Face Lateral
	glNormal3f(0, 0, 1);
	glBegin(GL_POLYGON);
	glVertex3f(1, 1, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, -1, 1);
	glVertex3f(1, -1, 1);
	glEnd();
	//Face Lateral
	glNormal3f(0, 0, -1);
	glBegin(GL_POLYGON);
	glVertex3f(1, 1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);
	glEnd();
	//Face de tras
	glNormal3f(-1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 1);
	glEnd();
	//Face da Frente
	glNormal3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);
	glEnd();
	//Face de Cima
	glNormal3f(0, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, 1, 1);
	glEnd();
	//Face de baixo
	glNormal3f(0, -1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(1, -1, 1);
	glVertex3f(1, -1, -1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, -1, 1);
	glEnd();
}

void desenhaCuboTextura() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	//Face Lateral
	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.5f);
	glVertex3f(1, 1, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, -1, 1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1, -1, 1);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(-1, 1, 1);
	glEnd();

	//Face Lateral
	glNormal3f(0, 0, -1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(-1, 1, -1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, -1, -1);
	glTexCoord2f(1.0f, 0.5f);
	glVertex3f(1, 1, -1);
	glEnd();

	//Face de Tras
	glNormal3f(-1, 0, 0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(-1, 1, -1);
	glTexCoord2f(0.5f, 0.0f);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1, -1, 1);
	glEnd();

	//Face da Frente
	glNormal3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.5f);
	glVertex3f(1, 1, 1);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(1, 1, -1);
	glTexCoord2f(0.5f, 0.0f);
	glVertex3f(1, -1, -1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1, -1, 1);
	glEnd();

	//Face de Cima
	glNormal3f(0, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, 1, 1);
	glEnd();

	//Face de baixo
	glNormal3f(0, -1, 0);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, -1, 1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, -1, -1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1, -1, 1);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void desenhaVidro() {
	glDisable(GL_LIGHTING);
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

	glEnable(GL_LIGHTING);

}

void desenhaParaBrisas() {
	GLfloat  obsidianAmb[] = { 0.05375 ,0.05 ,0.06625 };
	GLfloat  obsidianDif[] = { 0.18275 ,0.17 ,0.22525 };
	GLfloat  obsidianSpec[] = { 0.332741 ,0.328634 ,0.346435 };
	GLint  obsidianCoef = 0.3 * 128;

	// condutor
	//glColor3f(0.2, 0.2, 0.2);
	glMaterialfv(GL_FRONT, GL_AMBIENT, obsidianAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, obsidianDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, obsidianSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, obsidianCoef);
	glPushMatrix();
	glTranslatef(4, 1.1, -2);
	glRotatef(45, 0, 0, 1);
	glRotatef(-angPB, 1, 0, 0);
	glTranslatef(0, 0.05, 1);
	glScalef(0.05, 0.05, 1);
	desenhaCubo();
	glPopMatrix();

	// Pendura
	//glColor3f(0.2, 0.2, 0.2);
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

	GLfloat  TextAmb[] = { 0.75 ,0.75 ,0.75 };
	GLfloat  TextDif[] = { 0.75 ,0.75 ,0.75 };
	GLfloat  TextSpec[] = { 0.75 ,0.75 ,0.75 };
	GLint  TextCoef = 0.4 * 128;

	GLfloat  goldAmb[] = { 0.24725 ,0.1995 ,0.0745 };
	GLfloat  goldDif[] = { 0.75164 ,0.60648 ,0.22648 };
	GLfloat  goldSpec[] = { 0.628281 ,0.555802 ,0.366065 };
	GLint  goldCoef = 0.4 * 128;
	GLfloat  chromeAmb[] = { 0.25 ,0.25 ,0.25 };
	GLfloat  chromeDif[] = { 0.4 ,0.4 ,0.4 };
	GLfloat  chromeSpec[] = { 0.774597 ,0.774597 ,0.774597 };
	GLint  chromeCoef = 0.6 * 128;
	GLfloat  obsidianAmb[] = { 0.05375 ,0.05 ,0.06625 };
	GLfloat  obsidianDif[] = { 0.18275 ,0.17 ,0.22525 };
	GLfloat  obsidianSpec[] = { 0.332741 ,0.328634 ,0.346435 };
	GLint  obsidianCoef = 0.3 * 128;
	GLfloat  bluePlasticAmb[] = { 0.0 ,0.1 ,0.06 };
	GLfloat  bluePlasticDif[] = { 0.0 ,0.20980392 ,0.85980392 };
	GLfloat  bluePlasticSpec[] = { 0.0 ,0.20196078 ,0.85196078 };
	GLint  bluePlasticCoef = 0.25 * 128;

	glPushMatrix();

	// Corpo da Ambulancia ================================
	//glColor3f(0.77, 0.6, 0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, TextAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, TextDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, TextSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, TextCoef);

	glPushMatrix();
	glScalef(4, 1, 2);
	desenhaCuboTextura();
	glPopMatrix();

	// Parte traseira ao vidro (azul) =====================
	glMaterialfv(GL_FRONT, GL_AMBIENT, bluePlasticAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, bluePlasticDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, bluePlasticSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, bluePlasticCoef);

	glColor3f(0, 0, 1);
	glPushMatrix();
	glTranslatef(-1, 1.501, 0);
	glScalef(3, 0.5, 2);
	desenhaCubo();
	glPopMatrix();

	// Parte traseira ao vidro (amarela) ==================

	//glColor3f(0.77, 0.6, 0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, goldSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, goldCoef);

	glPushMatrix();
	glTranslatef(-1, 2.502, 0);
	glScalef(3, 0.5, 2);
	desenhaCubo();
	glPopMatrix();

	// Rodas 
	//glColor3f(0.2, 0.2, 0.2);
	glMaterialfv(GL_FRONT, GL_AMBIENT, obsidianAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, obsidianDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, obsidianSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, obsidianCoef);

	glPushMatrix();
	glTranslatef(2, -1, 2);
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

void iluminacao() {
	glLightfv(GL_LIGHT0, GL_POSITION, PosLuz);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
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

		iluminacao();
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

		iluminacao();
		drawEixos();
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2]);
		glRotatef(theta, 0, 1, 0);
		desenhaAmbulancia();
		glPopMatrix();

	}

	// Minimapa
	glViewport(0, 0, 600 / 4, 500 / 4);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, -10, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(pos[0], pos[1] + 5, pos[2], pos[0], 0, pos[2], 0, 0, -1);

	iluminacao();
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
