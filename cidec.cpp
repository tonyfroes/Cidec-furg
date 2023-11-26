#include <stdlib.h>
#include <GL/glut.h>

GLfloat angle, fAspect;

// usado para criar cilindros
GLUquadric* qobj;

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

void floor(float compxz, float alty){
  glColor3f(0.1f, 0.4f, 0.1f);
	
    // Desenha varios retangulos formando uma 'parede'
	glBegin(GL_QUADS);			// Face frontal
		glNormal3f(0.0, 0.0, 1.0);	// Normal da face
		glVertex3f(compxz/2, 0, compxz/2);
		glVertex3f(-compxz/2, 0, compxz/2);
		glVertex3f(-compxz/2, -alty, compxz/2);
		glVertex3f(compxz/2, -alty, compxz/2);
	glEnd();
	glBegin(GL_QUADS);			// Face traseira
		glNormal3f(0.0, 0.0, -1.0); 	// Normal da face
		glVertex3f(compxz/2, 0, -compxz/2);
		glVertex3f(compxz/2, -alty, -compxz/2);
		glVertex3f(-compxz/2, -alty, -compxz/2);
		glVertex3f(-compxz/2, 0, -compxz/2);
	glEnd();
	glBegin(GL_QUADS);			// Face lateral esquerda
		glNormal3f(-1.0, 0.0, 0.0); 	// Normal da face
		glVertex3f(-compxz/2, 0, compxz/2);
		glVertex3f(-compxz/2, 0, -compxz/2);
		glVertex3f(-compxz/2, -alty, -compxz/2);
		glVertex3f(-compxz/2, -alty, compxz/2);
	glEnd();
	glBegin(GL_QUADS);			// Face lateral direita
		glNormal3f(1.0, 0.0, 0.0);	// Normal da face
		glVertex3f(compxz/2, 0, compxz/2);
		glVertex3f(compxz/2, -alty, compxz/2);
		glVertex3f(compxz/2, -alty, -compxz/2);
		glVertex3f(compxz/2, 0, -compxz/2);
	glEnd();
	glBegin(GL_QUADS);			// Face superior
		glNormal3f(0.0, 1.0, 0.0);  	// Normal da face
		glVertex3f(-compxz/2, 0, -compxz/2);
		glVertex3f(-compxz/2, 0, compxz/2);
		glVertex3f(compxz/2, 0, compxz/2);
		glVertex3f(compxz/2, 0, -compxz/2);
	glEnd();
	glBegin(GL_QUADS);			// Face inferior
		glNormal3f(0.0, -1.0, 0.0); 	// Normal da face
		glVertex3f(-compxz/2, -alty, -compxz/2);
		glVertex3f(compxz/2, -alty, -compxz/2);
		glVertex3f(compxz/2, -alty, compxz/2);
		glVertex3f(-compxz/2, -alty, compxz/2);
	glEnd();
}


void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// desenha floor verde
    floor(132, 1); // x: 160, z: 160, y: 4  || ORIGEM NO CENTRO

    glutSwapBuffers();
	  			
}


void rotate(int opcao){

	switch (opcao) {
		case 1: // em x
			glRotatef(2.0, 1.0, 0.0, 0.0);
			break;
		case (-1): // em -x
			glRotatef(-2.0, 1.0, 0.0, 0.0);
			break;
		case 2: // em y
			glRotatef(2.0, 0.0, 1.0, 0.0);
			break;
		case (-2): // em -y
			glRotatef(-2.0, 0.0, 1.0, 0.0);						
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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
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
   glutCreateWindow ("Cidec");
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(SpecialKeyboard); 
   init ();
   glutMainLoop();
}