#include "materiais.h"

void initMaterials(int material) {

	//……………………………………………………………………………………………esmerald
	if (material == 0) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, esmeraldAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, esmeraldDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, esmeraldSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, esmeraldCoef);
	}
	//……………………………………………………………………………………………jade
	else if (material == 1) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, jadeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, jadeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, jadeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, jadeCoef);
	}
	//……………………………………………………………………………………………obsidian
	else if (material == 2) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, obsidianAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, obsidianDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, obsidianSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, obsidianCoef);
	}
	//……………………………………………………………………………………………pearl
	else if (material == 3) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, pearlAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, pearlDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, pearlSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, pearlCoef);
	}
	//……………………………………………………………………………………………ruby
	else if (material == 4) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, rubyAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, rubyDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, rubySpec);
		glMaterialf(GL_FRONT, GL_SHININESS, rubyCoef);
	}
	//……………………………………………………………………………………………turquoise
	else if (material == 5) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, turquoiseAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, turquoiseDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, turquoiseSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, turquoiseCoef);
	}
	//……………………………………………………………………………………………brass
	else if (material == 6) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, brassAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, brassDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, brassSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, brassCoef);
	}
	//……………………………………………………………………………………………bronze
	else if (material == 7) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, bronzeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bronzeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, bronzeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, bronzeCoef);
	}
	//……………………………………………………………………………………………chrome
	else if (material == 8) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, chromeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, chromeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, chromeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, chromeCoef);
	}
	//……………………………………………………………………………………………copper
	else if (material == 9) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, copperAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, copperDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, copperSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, copperCoef);
	}
	//……………………………………………………………………………………………gold
	else if (material == 10) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, goldSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, goldCoef);
	}
	//……………………………………………………………………………………………silver
	else if (material == 11) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, silverAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, silverDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, silverSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, silverCoef);
	}
	//……………………………………………………………………………………………blackPlastic
	else if (material == 12) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, blackPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blackPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, blackPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, blackPlasticCoef);
	}
	//……………………………………………………………………………………………cyankPlastic
	else if (material == 13) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, cyanPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, cyanPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, cyanPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, cyanPlasticCoef);
	}
	//……………………………………………………………………………………………greenPlastic
	else if (material == 14) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, greenPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, greenPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, greenPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, greenPlasticCoef);
	}
	//……………………………………………………………………………………………redPlastic
	else if (material == 15) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, redPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, redPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, redPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, redPlasticCoef);
	}
	//……………………………………………………………………………………………yellowPlastic
	else if (material == 16) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, whitePlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, whitePlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, whitePlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, whitePlasticCoef);
	}
	//……………………………………………………………………………………………yellowPlastic
	else if (material == 17) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, yellowPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellowPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, yellowPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, yellowPlasticCoef);
	}

}
