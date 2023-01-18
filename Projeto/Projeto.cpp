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

// Texturas ==============================================================================
GLuint texture;
GLuint texture2;
RgbImage imag;

int malha = 1;

// Luz Pontual ==========================================================================
int luz = 1;
GLfloat intensidadeLuz = 1.0;
GLfloat PosLuz[4] = { 5.0, 5.0, 5.0, 1.0 };
GLfloat localCorAmb[4] = { 0, 0, 0, 0.0 };
GLfloat localCorDif[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat localCorEsp[4] = { 1.0, 1.0, 1.0, 1.0 };

// Luz Focos
int sirene = 0;
GLfloat thetaFoco = 0.;
GLfloat velFoco = 1;

GLfloat foco1_pos[] = { 0.0, 5.5, 1 , 1.0 };
GLfloat foco1_direcao[] = { 0.0, -1.0, 1.0, 0.0 };
GLfloat foco1_cor[] = { 1.0, 0.0, 0.0, 1.0 };

GLfloat foco2_pos[] = { 0.0, 5.5, -1, 1.0 };
GLfloat foco2_direcao[] = { 0.0, -1.0, -1.0, 0.0 };
GLfloat foco2_cor[] = { 0.0, 0.0, 1.0, 1.0 };

GLfloat aberturaFoco = 80.0;

GLfloat foco_ak = 1.0f;
GLfloat foco_al = 0.25f;
GLfloat foco_aq = 1.0f;
GLfloat foco_Expon = 1.0;


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
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	// Texturas =========================================================
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


	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	imag.LoadBmpFile("Brick-Wall.bmp");
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

	// Materiais + Cor

	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);*/


}

void drawEixos() {
	GLfloat blackPlasticAmb[] = { 0.0 ,0.0 ,0.0 };
	GLfloat blackPlasticDif[] = { 0.00 ,0.00 ,0.00 };
	GLfloat blackPlasticSpec[] = { 0.0 ,0.00 ,0.0 };
	GLint blackPlasticCoef = 0.25 * 128;


	//glColor4f(ORANGE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, blackPlasticAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blackPlasticDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blackPlasticSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, blackPlasticCoef);

	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0.5 * 20, 0, 0);
	glEnd();


	//glColor4f(GREEN);
	glMaterialfv(GL_FRONT, GL_AMBIENT, blackPlasticAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blackPlasticDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blackPlasticSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, blackPlasticCoef);

	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.5 * 20, 0);
	glEnd();


	//glColor4f(BLUE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, blackPlasticAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blackPlasticDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blackPlasticSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, blackPlasticCoef);

	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.5 * 20);
	glEnd();
}

void desenhaCenario() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture2);

	GLfloat whitePlasticAmb[] = { 0.8 ,0.8 ,0.8 };
	GLfloat whitePlasticDif[] = { 0.55 ,0.55 ,0.55 };
	GLfloat whitePlasticSpec[] = { 0.870 ,0.870 ,0.870 };
	GLint whitePlasticCoef = 0.25 * 128;

	glMaterialfv(GL_FRONT, GL_AMBIENT, whitePlasticAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, whitePlasticDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, whitePlasticSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, whitePlasticCoef);

	int i, j;
	GLint dim = 8;
	float med_dim = (float)dim / 2;

	if (malha) {

		// Lateral
		glPushMatrix();
		glTranslatef(-15, -15, -15);
		glScalef(15, 15, 1);


		glNormal3f(0, 0, 1);
		glBegin(GL_QUADS);
		for (i = 0; i < dim; i++)
			for (j = 0; j < dim; j++) {
				glTexCoord2f((float)j / dim, (float)i / dim);
				glVertex3d((float)j / med_dim, (float)i / med_dim, 0);
				glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
				glVertex3d((float)(j + 1) / med_dim, (float)i / med_dim, 0);
				glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
				glVertex3d((float)(j + 1) / med_dim, (float)(i + 1) / med_dim, 0);
				glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
				glVertex3d((float)j / med_dim, (float)(i + 1) / med_dim, 0);
			}
		glEnd();

		glPopMatrix();

		// Lateral
		glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glTranslatef(-15, -15, -15);
		glScalef(15, 15, 1);


		glNormal3f(0, 0, 1); // nao necessito de mudar a normal pq as transformacoes tambem se aplicam
		glBegin(GL_QUADS);
		for (i = 0; i < dim; i++)
			for (j = 0; j < dim; j++) {
				glTexCoord2f((float)j / dim, (float)i / dim);
				glVertex3d((float)j / med_dim, (float)i / med_dim, 0);
				glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
				glVertex3d((float)(j + 1) / med_dim, (float)i / med_dim, 0);
				glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
				glVertex3d((float)(j + 1) / med_dim, (float)(i + 1) / med_dim, 0);
				glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
				glVertex3d((float)j / med_dim, (float)(i + 1) / med_dim, 0);
			}
		glEnd();

		glPopMatrix();

		// Tras
		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(-15, -15, -15);
		glScalef(15, 15, 1);


		glNormal3f(0, 0, 1); // nao necessito de mudar a normal pq as transformacoes tambem se aplicam
		glBegin(GL_QUADS);
		for (i = 0; i < dim; i++)
			for (j = 0; j < dim; j++) {
				glTexCoord2f((float)j / dim, (float)i / dim);
				glVertex3d((float)j / med_dim, (float)i / med_dim, 0);
				glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
				glVertex3d((float)(j + 1) / med_dim, (float)i / med_dim, 0);
				glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
				glVertex3d((float)(j + 1) / med_dim, (float)(i + 1) / med_dim, 0);
				glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
				glVertex3d((float)j / med_dim, (float)(i + 1) / med_dim, 0);
			}
		glEnd();

		glPopMatrix();

		// Frente
		glPushMatrix();
		glRotatef(-90, 0, 1, 0);
		glTranslatef(-15, -15, -15);
		glScalef(15, 15, 1);


		glNormal3f(0, 0, 1); // nao necessito de mudar a normal pq as transformacoes tambem se aplicam
		glBegin(GL_QUADS);
		for (i = 0; i < dim; i++)
			for (j = 0; j < dim; j++) {
				glTexCoord2f((float)j / dim, (float)i / dim);
				glVertex3d((float)j / med_dim, (float)i / med_dim, 0);
				glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
				glVertex3d((float)(j + 1) / med_dim, (float)i / med_dim, 0);
				glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
				glVertex3d((float)(j + 1) / med_dim, (float)(i + 1) / med_dim, 0);
				glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
				glVertex3d((float)j / med_dim, (float)(i + 1) / med_dim, 0);
			}
		glEnd();

		glPopMatrix();

	}
	else {
		// Lateral 
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(15, 15, -15);
		glTexCoord2f(1, 0);
		glVertex3f(15, -15, -15);
		glTexCoord2f(0, 0);
		glVertex3f(-15, -15, -15);
		glTexCoord2f(0, 1);
		glVertex3f(-15, 15, -15);
		glEnd();

		// Lateral 
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(15, 15, 15);
		glTexCoord2f(1, 0);
		glVertex3f(15, -15, 15);
		glTexCoord2f(0, 0);
		glVertex3f(-15, -15, 15);
		glTexCoord2f(0, 1);
		glVertex3f(-15, 15, 15);
		glEnd();

		// Tras
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex3f(-15, 15, 15);
		glTexCoord2f(0, 0);
		glVertex3f(-15, -15, 15);
		glTexCoord2f(1, 0);
		glVertex3f(-15, -15, -15);
		glTexCoord2f(1, 1);
		glVertex3f(-15, 15, -15);
		glEnd();

		// Frente
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(15, 15, 15);
		glTexCoord2f(0, 1);
		glVertex3f(15, 15, -15);
		glTexCoord2f(0, 0);
		glVertex3f(15, -15, -15);
		glTexCoord2f(1, 0);
		glVertex3f(15, -15, 15);
		glEnd();
	}

	// Baixo
	glBegin(GL_QUADS);
	glVertex3f(-15, -15, 15);
	glVertex3f(15, -15, 15);
	glVertex3f(15, -15, -15);
	glVertex3f(-15, -15, -15);
	glEnd();

	// Cima
	/*glBegin(GL_QUADS);
	glVertex3f(-15, 15, 15);
	glVertex3f(-15, 15, -15);
	glVertex3f(15, 15, -15);
	glVertex3f(15, 15, 15);
	glEnd();*/


	glDisable(GL_TEXTURE_2D);

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
	//glVertex3f(-0.5, 1, 0.5);
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
	//glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glColor4f(0.6, 0.8, 0.9, 0.5);

	GLfloat corVidro[] = { 0.6, 0.8, 0.9, 0.3 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, corVidro);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, corVidro);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corVidro);

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

	//glEnable(GL_LIGHTING);

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
	glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, goldSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, goldCoef);

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

	// Sirene
	if (sirene) {
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		thetaFoco += 10.0;
		foco1_direcao[0] = cos(thetaFoco * PI / 180.);
		foco1_direcao[2] = sin(thetaFoco * PI / 180.);

		foco2_direcao[0] = cos(thetaFoco * PI / 180. + PI);
		foco2_direcao[2] = sin(thetaFoco * PI / 180. + PI);
	}
	else {
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
	}
	glPushMatrix();

	glTranslatef(-1.0, 3.502, 0);
	glScalef(0.5, 0.5, 0.5);
	glRotated(-thetaFoco, 0, 1, 0);
	desenhaCubo();

	glPopMatrix();


	desenhaVidro();

	desenhaParaBrisas();

	glPopMatrix();

}

void iluminacao() {

	// Luz pontual
	glLightfv(GL_LIGHT0, GL_POSITION, PosLuz);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);

	// Foco 1 RED
	glLightfv(GL_LIGHT1, GL_DIFFUSE, foco1_cor);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, foco1_cor);
	//glLightfv(GL_LIGHT1, GL_AMBIENT, foco1_cor);
	//glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, foco_ak);
	//glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, foco_al);
	//glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, foco_aq);

	glLightfv(GL_LIGHT1, GL_POSITION, foco1_pos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, foco1_direcao);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, aberturaFoco);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, foco_Expon);

	// Foco 2 BLUE
	glLightfv(GL_LIGHT2, GL_DIFFUSE, foco2_cor);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, foco2_cor);
	//glLightfv(GL_LIGHT1, GL_AMBIENT, foco2_cor);
	//glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, foco_ak);
	//glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, foco_al);
	//glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, foco_aq);

	glLightfv(GL_LIGHT2, GL_POSITION, foco2_pos);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, foco2_direcao);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, aberturaFoco);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, foco_Expon);
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

	// (Des)Ligar luz
	if (luz) {
		glEnable(GL_LIGHT0);
	}
	else {
		glDisable(GL_LIGHT0);
	}

	// Observador 
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
	desenhaCenario();

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
	desenhaCenario();

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

		foco1_pos[0] = foco1_pos[0] + vel * cos(theta * PI / 180.);
		foco1_pos[2] = foco1_pos[2] - vel * sin(theta * PI / 180.);

		foco2_pos[0] = foco2_pos[0] + vel * cos(theta * PI / 180.);
		foco2_pos[2] = foco2_pos[2] - vel * sin(theta * PI / 180.);

		glutPostRedisplay();
		break;
	case 'S': case 's':
		pos[0] = pos[0] - vel * cos(theta * PI / 180.);
		pos[2] = pos[2] + vel * sin(theta * PI / 180.);

		foco1_pos[0] = foco1_pos[0] - vel * cos(theta * PI / 180.);
		foco1_pos[2] = foco1_pos[2] + vel * sin(theta * PI / 180.);

		foco2_pos[0] = foco2_pos[0] - vel * cos(theta * PI / 180.);
		foco2_pos[2] = foco2_pos[2] + vel * sin(theta * PI / 180.);

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
		if (!luz) luz = 1;
		else luz = 0;
		glutPostRedisplay();
		break;

	case 'E': case 'e':
		if (!sirene) sirene = 1;
		else sirene = 0;
		glutPostRedisplay();
		break;

	case 'M': case 'm':
		if (!malha) malha = 1;
		else malha = 0;
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
	glutCreateWindow("Setas Andar | 'WASD' Mover Observador| 'L' Limpar o vidro | V - Baixa os vidros | 'V' Baixar os vidros | 'E' Sirene | 'M' Desativar Malha | 'P' Desativas Luz Pontual");

	inicializa();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(Teclado);
	glutTimerFunc(50, Timer, 1);


	glutMainLoop();

	return 0;
}
