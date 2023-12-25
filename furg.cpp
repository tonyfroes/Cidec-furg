#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>

GLfloat angle, fAspect;

// usado para criar cilindros
GLUquadric* qobj;

GLfloat rotateX = 0.0f;
GLfloat rotateY = 0.0f;


GLfloat curvedSurface[4][4][3] = {

	// curva 1
	{{-40, 0, -15}, {-40, 20, -40},
	 {-40, 70, -15}, {-40, 45, 20}}, 

	// curva 2
	{{-40, 0, -15}, {-40, 20, -40},
	 {-40, 70, -15}, {-40, 45, 20}},

	// curva 3
	{{40, 0, -15}, {40, 20, -40},
	 {40, 70, -15}, {40, 45, 20}},

	// curva 4
	{{40, 0, -15}, {40, 20, -40},
	 {40, 70, -15}, {40, 45, 20}}
};

// void floor(float compxz, float alty){
//   glColor3f(0.1f, 0.4f, 0.1f);
	
//     // Desenha varios retangulos formando uma 'parede'
// 	glBegin(GL_QUADS);			// Face frontal
// 		glNormal3f(0.0, 0.0, 1.0);	// Normal da face
// 		glVertex3f(compxz/2, 0, compxz/2);
// 		glVertex3f(-compxz/2, 0, compxz/2);
// 		glVertex3f(-compxz/2, -alty, compxz/2);
// 		glVertex3f(compxz/2, -alty, compxz/2);
// 	glEnd();
// 	glBegin(GL_QUADS);			// Face traseira
// 		glNormal3f(0.0, 0.0, -1.0); 	// Normal da face
// 		glVertex3f(compxz/2, 0, -compxz/2);
// 		glVertex3f(compxz/2, -alty, -compxz/2);
// 		glVertex3f(-compxz/2, -alty, -compxz/2);
// 		glVertex3f(-compxz/2, 0, -compxz/2);
// 	glEnd();
// 	glBegin(GL_QUADS);			// Face lateral esquerda
// 		glNormal3f(-1.0, 0.0, 0.0); 	// Normal da face
// 		glVertex3f(-compxz/2, 0, compxz/2);
// 		glVertex3f(-compxz/2, 0, -compxz/2);
// 		glVertex3f(-compxz/2, -alty, -compxz/2);
// 		glVertex3f(-compxz/2, -alty, compxz/2);
// 	glEnd();
// 	glBegin(GL_QUADS);			// Face lateral direita
// 		glNormal3f(1.0, 0.0, 0.0);	// Normal da face
// 		glVertex3f(compxz/2, 0, compxz/2);
// 		glVertex3f(compxz/2, -alty, compxz/2);
// 		glVertex3f(compxz/2, -alty, -compxz/2);
// 		glVertex3f(compxz/2, 0, -compxz/2);
// 	glEnd();
// 	glBegin(GL_QUADS);			// Face superior
// 		glNormal3f(0.0, 1.0, 0.0);  	// Normal da face
// 		glVertex3f(-compxz/2, 0, -compxz/2);
// 		glVertex3f(-compxz/2, 0, compxz/2);
// 		glVertex3f(compxz/2, 0, compxz/2);
// 		glVertex3f(compxz/2, 0, -compxz/2);
// 	glEnd();
// 	glBegin(GL_QUADS);			// Face inferior
// 		glNormal3f(0.0, -1.0, 0.0); 	// Normal da face
// 		glVertex3f(-compxz/2, -alty, -compxz/2);
// 		glVertex3f(compxz/2, -alty, -compxz/2);
// 		glVertex3f(compxz/2, -alty, compxz/2);
// 		glVertex3f(-compxz/2, -alty, compxz/2);
// 	glEnd();
// }

void Transposta(float matriz[4][4]){

   float aux;
   for (int i = 0; i < 4; i++) {
      for (int j = i; j >= 0;j--) {
          aux = matriz[i][j];
          matriz[i][j] = matriz[j][i];
          matriz[j][i] = aux;
      }
   }
}

void Translate(float dx, float dy, float dz) {
   float matriz[4][4] = {{1,0,0,0},
                      {0,1,0,0},
                      {0,0,1,0},
                      {0,0,0,1}};
   matriz[0][3] = dx;
   matriz[1][3] = dy;
   matriz[2][3] = dz;
   Transposta(matriz);
   glMultMatrixf((float *) matriz);
}

//Criar um retangulo com altura e largura definidas e com o centro no ponto (x,y,z) 
void retangulo(float x, float y, float z, float largura, float altura) {
    Translate(x, y, z);
	glColor3f(1.0f, 1.0f, 1.0f); // Define a cor para verde
    
    glBegin(GL_QUADS);
        glVertex3f(-largura / 2, -altura / 2, 0);
        glVertex3f(largura / 2, -altura / 2, 0);
        glVertex3f(largura / 2, altura / 2, 0);
        glVertex3f(-largura / 2, altura / 2, 0);
    glEnd();
	glPopAttrib(); // Restaura o estado anterior da cor
}


void desenharSemiCirculo(float x, float y, float z, float raio, float anguloInicial, float anguloFinal) {
    int numSegmentos = 100; // Número de segmentos para suavizar o semicírculo

    glPushMatrix();
    glTranslatef(x, y, z);

    glPushAttrib(GL_CURRENT_BIT); // Salva o estado atual da cor
	glColor3f(1.0f, 0.5f, 0.0f); // Define a cor para laranja


    glBegin(GL_TRIANGLE_FAN);

    // Centro do semicírculo
    glVertex3f(x, y, z);

    // Desenhar o semicírculo usando os vértices de um círculo
    for (int i = 0; i <= numSegmentos; ++i) {
        float angulo = anguloInicial + (i * (anguloFinal - anguloInicial) / numSegmentos);
        float xBorda = x + (raio / 2) * cos(angulo);
        float yBorda = y + (raio / 2) * sin(angulo);
        glVertex3f(xBorda, yBorda, z);
    }

    glEnd();
    glPopAttrib(); // Restaura o estado anterior da cor
    glPopMatrix();
}

void desenharSemiCirculoDireita(float x, float y, float z, float raio, float anguloInicial, float anguloFinal) {
    int numSegmentos = 100; // Número de segmentos para suavizar o semicírculo

    glPushMatrix();
    glTranslatef(x, y, z);

    glPushAttrib(GL_CURRENT_BIT); // Salva o estado atual da cor
    glColor3f(1.0f, 0.5f, 0.0f); // Cor laranja para o semicírculo superior

    glBegin(GL_TRIANGLE_FAN);

    // Centro do semicírculo na parte inferior
    glVertex3f(x, y - raio, z);

    // Desenhar o semicírculo usando os vértices de um círculo
    for (int i = 0; i <= numSegmentos; ++i) {
        float angulo = anguloInicial + (i * (anguloFinal - anguloInicial) / numSegmentos);
        float xBorda = x + (raio / 2) * cos(angulo);
        float yBorda = (y - raio) + (raio / 2) * sin(angulo);
        glVertex3f(xBorda, yBorda, z);
    }

    glEnd();
    glPopAttrib(); // Restaura o estado anterior da cor
    glPopMatrix();
}

void desenharSemiCirculoEmbaixo(float x, float y, float z, float raio, float anguloInicial, float anguloFinal) {
    int numSegmentos = 100; // Número de segmentos para suavizar o semicírculo

    glPushMatrix();
    glTranslatef(x, y, z);

    glPushAttrib(GL_CURRENT_BIT); // Salva o estado atual da cor
    glColor3f(1.0f, 0.5f, 0.0f); // Cor laranja para o semicírculo superior

    glBegin(GL_TRIANGLE_FAN);

    // Centro do semicírculo na parte inferior
    glVertex3f(x, y - raio, z);

    // Desenhar o semicírculo usando os vértices de um círculo
    for (int i = 0; i <= numSegmentos; ++i) {
        float angulo = anguloInicial + (i * (anguloFinal - anguloInicial) / numSegmentos);
        float xBorda = x + (raio / 2) * cos(angulo);
        float yBorda = (y - raio) + (raio / 2) * sin(angulo);
        glVertex3f(xBorda, yBorda, z);
    }

    glEnd();
    glPopAttrib(); // Restaura o estado anterior da cor
    glPopMatrix();
}

void desenharRetangulo(float x, float y, float z, float largura, float altura) {
    glPushMatrix();
    glTranslatef(x, y, z);

    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);                // Canto inferior esquerdo
    glVertex3f(largura, 0, 0);          // Canto inferior direito
    glVertex3f(largura, altura, 0);     // Canto superior direito
    glVertex3f(0, altura, 0);           // Canto superior esquerdo
    glEnd();

    glPopMatrix();
}




void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST); // Habilita o Z-buffer

    glLoadIdentity();
    gluLookAt(0, 80, 250, 0, 0, 0, 0, 1, 0); // Defina sua visão

    glRotatef(rotateX, 1.0f, 0.0f, 0.0f); // Rotação em x
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f); // Rotação em y

    glColor3f(0.0f, 1.0f, 0.0f); // Cor verde para o retângulo
    retangulo(0, 0, 0, 150, 150);

    glColor3f(1.0f, 0.5f, 0.0f); // Cor laranja para o semicírculo superior
    glPushMatrix();
    glRotatef(90, 0.0f, 0.0f, 1.0f); // Rotação para posicionar na lateral esquerda
    desenharSemiCirculo(0, 20, 0.1, 70, 3.13, 0); // Desenha o semicírculo superior
    glPopMatrix();

    glColor3f(1.0f, 0.5f, 0.0f); // Cor laranja para o semicírculo superior
    glPushMatrix();
    // glTranslatef(0, -20, 0); // Translada para a posição inferior
	glTranslatef(110, 0, 0); // Translada para a posição à direita
    glRotatef(90, 0.0f, 0.0f, -1.0f); // Rotação no semicírculo inferior
    desenharSemiCirculoDireita(0, 0, 0.1, 70, 3.13, 0); // Desenha o semicírculo na parte inferior
    glPopMatrix();

	glColor3f(0.0f, 0.0f, 1.0f); // Cor azul para o semicírculo na parte inferior
    glPushMatrix();
    glTranslatef(0, 0, 0); // Translada para a posição inferior
    glRotatef(-179, 0.0f, 0.0f, 1.0f); // Rotação no semicírculo inferior
    desenharSemiCirculoEmbaixo(0, 55, 0.1, 70, 3.13, 0); // Desenha o semicírculo na parte inferior
    glPopMatrix();
	
	//EMBAIXO
	glPushMatrix();
    glTranslatef(-30, -30, 0); // Translada para a posição inferior
	desenharRetangulo(0, 0, 0.1, 60, 10);
	glPopMatrix();

	//DIREITA
	glPushMatrix();
	glTranslatef(30,-30, 0); // Translada para a posição inferior
	glRotatef(90, 0.0f, 0.0f, 1.0f); // Rotação no semicírculo inferior
	desenharRetangulo(0, 0, 0.1, 60, 10);
	glPopMatrix();

	//ESQUERDA
	glPushMatrix();
	glTranslatef(-20,-30, 0); // Translada para a posição inferior
	glRotatef(90, 0.0f, 0.0f, 1.0f); // Rotação no semicírculo inferior
	desenharRetangulo(0, 0, 0.1, 60, 10);
	glPopMatrix();

	//CENTRO
	glPushMatrix();
	glTranslatef(15, -15, 0); // Translada para a posição inferior
	glRotatef(90, 0.0f, 0.0f, 1.0f); // Rotação no semicírculo inferior
	desenharRetangulo(0, 0, 0.1, 70, 30);
	glPopMatrix();


    glutSwapBuffers();
}

// ESTICAR
// void display(void) {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//     glEnable(GL_DEPTH_TEST); // Habilita o Z-buffer

//     glLoadIdentity();
//     gluLookAt(0, 80, 250, 0, 0, 0, 0, 1, 0); // Defina sua visão

//     glRotatef(rotateX, 1.0f, 0.0f, 0.0f); // Rotação em x
//     glRotatef(rotateY, 0.0f, 1.0f, 0.0f); // Rotação em y

//     glColor3f(0.0f, 1.0f, 0.0f); // Cor verde para o retângulo
//     retangulo(0, 0, 0, 132, 100);

//     glColor3f(1.0f, 0.5f, 0.0f); // Cor laranja para o semicírculo superior
//     glPushMatrix();
//     glRotatef(90, 0.0f, 0.0f, 1.0f); // Rotação para posicionar na lateral esquerda
//     desenharSemiCirculo(0, 20, 0.1, 70, 3.13, 0); // Desenha o semicírculo superior
//     glPopMatrix();

//     glColor3f(1.0f, 0.5f, 0.0f); // Cor laranja para o semicírculo superior
//     glPushMatrix();
//     // glTranslatef(0, -20, 0); // Translada para a posição inferior
//     glTranslatef(100, 0, 0); // Translada para a posição à direita
//     glRotatef(90, 0.0f, 0.0f, -1.0f); // Rotação no semicírculo inferior
//     desenharSemiCirculoDireita(0, 0, 0.1, 70, 3.13, 0); // Desenha o semicírculo na parte inferior
//     glPopMatrix();

//     glColor3f(1.0f, 0.5f, 0.0f); // Cor laranja para o semicírculo inferior
//     glPushMatrix();
//     // glTranslatef(0, -20, 0); // Translada para a posição inferior
//     glTranslatef(0, -20, 0); // Translada para a posição inferior
//     glRotatef(90, 0.0f, 0.0f, -1.0f); // Rotação no semicírculo inferior
//     desenharSemiCirculoEmbaixo(0, 0, 0.1, 90, 50, 3.13, 0); // Desenha o semicírculo na parte inferior
//     glPopMatrix();

//     glutSwapBuffers();
// }



// void display(void) {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//     glEnable(GL_DEPTH_TEST); // Habilita o Z-buffer

//     glLoadIdentity();
//     gluLookAt(0, 80, 250, 0, 0, 0, 0, 1, 0); // Defina sua visão

//     glRotatef(rotateX, 1.0f, 0.0f, 0.0f); // Rotação em x
//     glRotatef(rotateY, 0.0f, 1.0f, 0.0f); // Rotação em y

//     glColor3f(0.0f, 1.0f, 0.0f); // Cor verde para o retângulo
//     retangulo(0, 0, 0, 132, 100);

//     glColor3f(1.0f, 0.5f, 0.0f); // Cor laranja para o semicírculo
//     glPushMatrix();
//     glRotatef(90, 0.0f, 0.0f, 1.0f); // Rotação para posicionar na lateral esquerda
//     desenharSemiCirculo(20, 0, 0.1, 70, 3.13, 0); // Desenha o semicírculo na lateral esquerda
//     glPopMatrix(); // Restaura a matriz de rotação

//     glColor3f(0.0f, 0.0f, 1.0f); // Cor azul para o semicírculo na parte inferior
//     glPushMatrix();
//     //glTranslatef(0, -20, 0); // Move o desenho do semicírculo na parte inferior
//     desenharSemiCirculoEmbaixo(0, 0, 0.1, 70, 3.13, 0); // Desenha o semicírculo na parte inferior
//     glPopMatrix();

//     glutSwapBuffers();
// }








// void rotate(int opcao){

// 	switch (opcao) {
// 		case 1: // em x
// 			glRotatef(2.0, 1.0, 0.0, 0.0);
// 			break;
// 		case (-1): // em -x
// 			glRotatef(-2.0, 1.0, 0.0, 0.0);
// 			break;
// 		case 2: // em y
// 			glRotatef(2.0, 0.0, 1.0, 0.0);
// 			break;
// 		case (-2): // em -y
// 			glRotatef(-2.0, 0.0, 1.0, 0.0);						
// 			break;
// 	}

//     glutPostRedisplay();
// }
void rotate(int opcao){
    switch (opcao) {
        case 1: // em x
            rotateX += 2.0f;
            break;
        case (-1): // em -x
            rotateX -= 2.0f;
            break;
        case 2: // em y
            rotateY += 2.0f;
            break;
        case (-2): // em -y
            rotateY -= 2.0f;                        
            break;
    }
    glutPostRedisplay();
}


void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
	gluPerspective(angle,fAspect,0.4,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	gluLookAt(0,80,250, 0,0,0, 0,1,0); // 1º,2º,3º -> coordenadas do observador | 4º,5º,6º -> coordenadas do alvo | 7º,8º,9º -> vetor UP, estabelece o 'lado de cima'
}




void keyboard(unsigned char key, int x, int y)
{
    int hor, ver;
    hor = 0; ver = 0; // horizontal e vertical

    switch (key) {
        case 27:
            exit(0);
            break;
        case 'l':
            glDisable(GL_LIGHTING); // desabilita iluminação
            break;
        case 'f':
            glEnable(GL_LIGHTING); // habilita iluminação
            break;
        case 'r':
        EspecificaParametrosVisualizacao();
            break;
    }

    glutPostRedisplay();
}

void SpecialKeyboard(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
		rotate(1); // Seta para cima rotaciona em x
    }
    else if(key == GLUT_KEY_DOWN) {
		rotate(-1); // Seta para baixo rotaciona em -x
    }
	else if(key == GLUT_KEY_RIGHT) {
		rotate(2); // Seta para direita rotaciona em y
    }
	else if(key == GLUT_KEY_LEFT) {
		rotate(-2); // seta para esquerda rotaciona em -y
    }
	
    glutPostRedisplay(); // redesenha a cena
}




void initLights(){
	GLfloat ambientLight[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,-.2}; // "cor"
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat posicaoLuz[4]={0.0, -100.0, 250.0, 1.0}; // "posição"  

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;    
	// Define a refletância do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial); 
	GLfloat mat_transparent[] = { 0.0, 0.8, 0.8, 0.6 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent); 

	// Define os parâmetros da luz de número 0
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); // melhor SEM
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );    

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);  
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);	
    // Habilita o MultiSampling Anti-Aliasing
    glEnable(GL_MULTISAMPLE_ARB);	
}


void init(void)
{
	//lColor3f(0.663, 0.663, 0.663); // Cinza (concreto)
	
	angle=45; // angulo de visao
	
	//glMap2f( type of value generated, 0, 1, number of floats inside [0][0], dimension of array in 'u' axis,
	// 0, 1, number of floats in [0], dimension of array in 'v' axis, pointer to array )
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4, &curvedSurface[0][0][0]);		
	// cria vertex do curvedSurface
	glEnable(GL_MAP2_VERTEX_3);

	// preenchimento da superficie curva
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glShadeModel(GL_SMOOTH);

	// cria quadradric usado para criar cilindros
	// qobj = gluNewQuadric();
  	// gluQuadricNormals(qobj, GLU_SMOOTH);

	// inicia configurações de iluminação
	initLights();

	// configura buffer de profundidade
	glEnable(GL_DEPTH_TEST);
}


void reshape(int w, int h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
 
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
   glutInitWindowSize (1200, 1000);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("FURG LOGO");
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(SpecialKeyboard); 
   init ();
   glutMainLoop();
}
