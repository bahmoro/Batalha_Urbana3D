//PROJETO DE COMPUTAÇÃO GRAFICA 2021
//ALUNOS: Barbara Lopes Moro e Matheus Viera Zarate
//Professor: ADAILTON JOSE ALVES DA CRUZ

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define ESC 27
int window;
float x = 5.0, y=1.0, z = -3.0;
float deltaMove = 0.0,deltaMove2 = 0.0;

float lx = 0.0, ly=1.0, y2=0,lz = 1.0;
float angle = 0.0;
float deltaAngle = 0.0;

int isDragging = 0;
int xDragStart = 0;

GLUquadricObj *IDquadric;
int flag =1, flag2=1, flag3=1, localizacaoCanhao1,localizacaoCanhao2;
float altura[36], aleatorio[36][3];
float anguloh=0, angulov=0,anguloh2=0, angulov2=0, v0=10,v0_2=10,moverbolax=0,moverbolay=0,moverbolaz=0, moverbolax2=0,moverbolay2=0,moverbolaz2=0;
float posicaox=0,posicaoy=0, posicaoz=0, posicaox2=0,posicaoy2=0,posicaoz2=0;
float t=0,t2=0,controleTempo=1,gravidade=10,tempo=0,radiano = 3.141592/180; ;
int jogador=0;
GLint lineAmount = 100; //triangulos usados para desenhar o circulo
GLfloat twicePi = 2.0 * 3.14; // duas vezes o PI
char convertidoVelocidade[16]={'1','0','.','0','0'}, convertidoVelocidade2[16]={'1','0','.','0','0'}, convertidoPonto1[16], convertidoPonto2[16];
GLfloat destruirCorpo = 0,destruirCorpo2 = 0; // controle de quando o objeto é acertado
GLint ponto1 = 0, ponto2 = 0; // pontuação dos canhoes

float abs( float valor )
    {
      if( valor < 0 )
        return -valor;
      else
        return valor;
}

int negativo( float valor )
    {
      if( valor < 0 )
        return -1;
      else
        return 1;
}
//escreve a pontuação na tela
void Pontuacao(){
    sprintf(convertidoPonto1, "%d ", ponto1);

    glColor3f(0, 0, 0);
    // posicionamos na tela
    glRasterPos2f(-0.8, -.7);
    char* jogador1 = (char*) "J1:";
    while (*jogador1 != '\0') {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *jogador1++);
    }
    glRasterPos2f(-.4, -.7);
    char* pont1 = (char*) convertidoPonto1;
    while (*pont1 != '\0') {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *pont1++);
    }

    glRasterPos2f(0, -.7);
    char* jogador2 = (char*) "J2:";
    while (*jogador2 != '\0') {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *jogador2++);
    }
    sprintf(convertidoPonto2, "%d ", ponto2);

     glColor3f(0, 0, 0);
    // posicionamos na tela
    glRasterPos2f(0.4, -0.7);

    char* p2 = (char*) convertidoPonto2;
    while (*p2 != '\0') {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p2++);
    }
}

//controla a desturição dos canhoes
void Destruir(){
    flag2 = 0; // controla pra enquanto ele estiver destruido ninguem atirar

    if(jogador == 1){ // caso seja o canhao azul q esteja atirando
        destruirCorpo = 0.2;
        ponto2++;
    }
    if(jogador == 0){  //caso seja o canhao vermelho q esteja atirando
        destruirCorpo2 = 0.2;
        ponto1++;
    }
}

//criar circulos 2D
void criarCirculo(GLfloat raio)
{
    GLint i;
    glBegin(GL_TRIANGLE_FAN);
		for(i = 0; i <= lineAmount; i++) {
			glVertex2f(
              0 + ((raio) * cos(i *  twicePi / lineAmount)),
              0 + ((raio) * sin(i * twicePi / lineAmount)));
		}
    glEnd();
}

//muda o tamanho da viewport
void changeSize(int w, int h)
{
	float ratio =  ((float) w) / ((float) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, ratio, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);

}

//gera alturas aleatorias para os predios
void gerarAltura()
{
    for(int i=0;i<36;i++){
        altura[i]=rand()%4+1;
    }

}

//gera localizações aleatorias para os canhoes
void locCanhao(){
    localizacaoCanhao1 = rand()%36;
    do{
        localizacaoCanhao2 = rand()%36;
    }while(localizacaoCanhao1 == localizacaoCanhao2);
}

//desenha o canhao vermelho
void canhao1()
{
    float tamx1=-0.6,tamx2=0.5,tamy1=0.2,tamy2=0.3,tamz1=0,tamz2=0.5;

    //corpo do canhao
    glPushMatrix();
        glTranslatef(-0.05, 0.25-destruirCorpo, 0.25);
        glColor3f(0.6, 0.0, 0.0);
        glScalef(1.1,0.1,0.5);
        glutSolidCube(1);
    glPopMatrix();
	glPushMatrix();

        glColor3f(0.0, 0.0, 0.0);
		glTranslatef(0, 0.4-destruirCorpo, 0.25);
		if(jogador==0){
		glRotatef(anguloh,0,1,0);
		glRotatef(angulov,0,0,1);
		}

        //cabeça do canhao
		glutSolidSphere(0.2, 20, 20);
        glTranslatef(0, 0.0, -0.05);
        glColor3f(1, 1, 1);
        gluCylinder(IDquadric,0.2,0.2,0.1,100,100);

        //cano do canhao
		glColor3f(0.6, 0.0, 0.0);
        glTranslatef(0, 0.1, 0.05);
        glRotated(90,0,1,0);
        gluCylinder(IDquadric,0.08,0.08,0.55,100,100);


        glColor3f(0.0, 0.0, 0.0);
        glTranslatef(0, 0, 0.54);
        gluCylinder(IDquadric,0.08,0.08,0.1,100,100);

    glPopMatrix();



	glPushMatrix();
        //apoio das rodas
        glColor3f(0.0, 0.0, 0.0);
		glTranslatef(0.3, 0.1, -0.1);
        gluCylinder(IDquadric,0.1,0.1,0.7,32,32);

        glTranslatef(-0.7, 0.0, 0);
        gluCylinder(IDquadric,0.1,0.1,0.7,100,100);
    glPopMatrix();

    glPushMatrix();
    //Rodas
        glColor3f(1, 1, 1);
        glTranslatef(0.3, 0.1, 0.50);
        gluCylinder(IDquadric,0.11,0.11,0.1,100,100);
        glColor3f(0, 0, 0);
        glTranslatef(0.0, 0.0, 0.0);
        glutSolidSphere(0.1, 20, 20);

        glColor3f(1, 1, 1);

        glTranslatef(0.0, 0.0, -0.60);
        gluCylinder(IDquadric,0.11,0.11,0.1,100,100);
        glTranslatef(0.0, 0.0, 0.1);
        glColor3f(0, 0, 0);
        glutSolidSphere(0.1, 20, 20);


        glTranslatef(-0.7, 0.0, 0);
        glutSolidSphere(0.1, 20, 20);
        glTranslatef(0.0, 0.0, -0.1);
        glColor3f(1, 1, 1);
        gluCylinder(IDquadric,0.11,0.11,0.1,100,100);

        glTranslatef(0.0, 0.0, 0.60);
        gluCylinder(IDquadric,0.11,0.11,0.1,100,100);
        glTranslatef(0.0, 0.0, 0);
        glColor3f(0, 0, 0);
        glutSolidSphere(0.1, 20, 20);

    glPopMatrix();
    //acertou o canhao azul
     if(abs(posicaox)>=  abs( 1-(abs(aleatorio[localizacaoCanhao2][1])+ abs(aleatorio[localizacaoCanhao1][1]))) && abs(posicaox)<= abs(-1-(abs(aleatorio[localizacaoCanhao2][1])+ abs(aleatorio[localizacaoCanhao1][1])) )&&
        (posicaoy + 3.5*aleatorio[localizacaoCanhao1][0])>=3.5*aleatorio[localizacaoCanhao2][0]-1 && (posicaoy + 3.5*aleatorio[localizacaoCanhao1][0])<=3.5*aleatorio[localizacaoCanhao2][0]+2 &&
        abs(posicaoz)>=(abs(aleatorio[localizacaoCanhao2][2])+ abs(aleatorio[localizacaoCanhao1][2]))-1 && abs(posicaoz) <= (abs(aleatorio[localizacaoCanhao2][2])+ abs(aleatorio[localizacaoCanhao1][2]))){
        controleTempo=0;
        Destruir();
        jogador=1;
    }

    //atingiu o chao
    if(posicaoy + 3.5*aleatorio[localizacaoCanhao1][0]< 0){ // caso a bola passe das extremidades da tela
        controleTempo = 0; // faz a bola parar de mover
        jogador=1;
    }

    //posição da bola
    posicaox = moverbolax;
    posicaoy = 0.4+moverbolay;
    posicaoz= -0.25+moverbolaz;
    glPushMatrix();
    glColor3f(0,0,0);
    //desenha a bola de canhao
        glTranslatef( posicaox,  posicaoy-destruirCorpo,-posicaoz);

    glutSolidSphere(0.07,100,100);
    glPopMatrix();

}

void canhao2(){
    float tamx1=-0.6,tamx2=0.5,tamy1=0.2,tamy2=0.3,tamz1=0,tamz2=0.5;
    //corpo do canhao
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.6);
        glTranslatef(-0.05, 0.25-destruirCorpo2, 0.25);
        glScalef(1.1,0.1,0.5);
        glutSolidCube(1);
    glPopMatrix();


	glPushMatrix();
	//cabeça do canhao
        glColor3f(0.0, 0.0, 0.0);
		glTranslatef(0, 0.4-destruirCorpo2, 0.25);
        if(jogador==1){
		glRotatef(anguloh2,0,1,0);
		glRotatef(angulov2,0,0,1);
		}
		glutSolidSphere(0.2, 20, 20);
        glTranslatef(0, 0.0, -0.05);
        glColor3f(1, 1, 1);
        gluCylinder(IDquadric,0.2,0.2,0.1,100,100);

        //cano do canhao
		glColor3f(0.0, 0.0, 0.6);
        glTranslatef(0, 0.1, 0.05);
        glRotatef(90,0,1,0);
        gluCylinder(IDquadric,0.08,0.08,0.55,100,100);


        glColor3f(0.0, 0.0, 0.0);
        glTranslatef(0, 0, 0.54);
        gluCylinder(IDquadric,0.08,0.08,0.1,100,100);

    glPopMatrix();

	glPushMatrix();
	//apoio das rodas
        glColor3f(0.0, 0.0, 0.0);
		glTranslatef(0.3, 0.1, -0.1);
        gluCylinder(IDquadric,0.1,0.1,0.7,32,32);

        glTranslatef(-0.7, 0.0, 0);
        gluCylinder(IDquadric,0.1,0.1,0.7,100,100);
    glPopMatrix();

    glPushMatrix();
    //rodas
        glColor3f(1, 1, 1);
        glTranslatef(0.3, 0.1, 0.50);
        gluCylinder(IDquadric,0.11,0.11,0.1,100,100);
        glColor3f(0, 0, 0);
        glTranslatef(0.0, 0.0, 0.0);
        glutSolidSphere(0.1, 20, 20);

        glColor3f(1, 1, 1);

        glTranslatef(0.0, 0.0, -0.60);
        gluCylinder(IDquadric,0.11,0.11,0.1,100,100);
        glTranslatef(0.0, 0.0, 0.1);
        glColor3f(0, 0, 0);
        glutSolidSphere(0.1, 20, 20);


        glTranslatef(-0.7, 0.0, 0);
        glutSolidSphere(0.1, 20, 20);
        glTranslatef(0.0, 0.0, -0.1);
        glColor3f(1, 1, 1);
        gluCylinder(IDquadric,0.11,0.11,0.1,100,100);

        glTranslatef(0.0, 0.0, 0.60);
        gluCylinder(IDquadric,0.11,0.11,0.1,100,100);
        glTranslatef(0.0, 0.0, 0);
        glColor3f(0, 0, 0);
        glutSolidSphere(0.1, 20, 20);

    glPopMatrix();
    //atingiu o canhao vermelho
    if(abs(posicaox2)>=  abs( 1-(abs(aleatorio[localizacaoCanhao2][1])+ abs(aleatorio[localizacaoCanhao1][1]))) && abs(posicaox2)<= abs(-1-(abs(aleatorio[localizacaoCanhao2][1])+ abs(aleatorio[localizacaoCanhao1][1])) )&&
        (posicaoy2 + 3.5*aleatorio[localizacaoCanhao2][0])>=3.5*aleatorio[localizacaoCanhao1][0]-1 && (posicaoy2 + 3.5*aleatorio[localizacaoCanhao2][0])<=3.5*aleatorio[localizacaoCanhao1][0]+2 &&
        abs(posicaoz2)>=(abs(aleatorio[localizacaoCanhao2][2])+ abs(aleatorio[localizacaoCanhao1][2]))-1 && abs(posicaoz2) <= (abs(aleatorio[localizacaoCanhao2][2])+ abs(aleatorio[localizacaoCanhao1][2]))){
        controleTempo=0;
        Destruir();
        jogador=0;
    }


    if(moverbolay2 + 3.5*aleatorio[localizacaoCanhao2][0]< 0){ // caso a bola passe das extremidades da tela
        controleTempo = 0; // faz a bola parar de mover
        jogador=0;

    }

    posicaox2 = moverbolax2;
    posicaoy2 = 0.5+moverbolay2;
    posicaoz2= -0.25+moverbolaz2;

    //posição da bola
    glPushMatrix();
    glColor3f(0,0,0);
    //desenha a bola de canhao

    glTranslatef( posicaox2,posicaoy2-destruirCorpo2 ,-posicaoz2);

    glutSolidSphere(0.07,100,100);
    glPopMatrix();

}

//desenha os predios
void predio()
{
    float tamx1=1,tamx2=6,tamy1=0,tamy2=7,tamz1=0,tamz2=4;
    glPushMatrix();
		glTranslatef(1, 0.0, 0);

       //- FRENTE
         glBegin(GL_POLYGON);
            glVertex3f(tamx1, tamy1,tamz1 );
            glVertex3f(tamx2, tamy1, tamz1 );
            glVertex3f(tamx2, tamy2,  tamz1 );
            glVertex3f( tamx1, tamy2, tamz1 );
          glEnd();

          // - TRASEIRA
         glBegin(GL_POLYGON);
          glVertex3f(  tamx1,  tamy1, tamz2 );
          glVertex3f( tamx2,  tamy1, tamz2 );
          glVertex3f( tamx2,  tamy2, tamz2 );
          glVertex3f( tamx1,  tamy2, tamz2 );
          glEnd();

          // - Direito
         glBegin(GL_POLYGON);
          glVertex3f( tamx1,  tamy1, tamz1 );
          glVertex3f( tamx1,  tamy1, tamz2 );
          glVertex3f( tamx1,  tamy2, tamz2 );
          glVertex3f( tamx1,  tamy2, tamz1 );
          glEnd();

          // - ESQUERDA
         glBegin(GL_POLYGON);
          glVertex3f(tamx2,  tamy1, tamz2 );
          glVertex3f(tamx2,  tamy1, tamz1 );
          glVertex3f(tamx2,  tamy2, tamz1 );
          glVertex3f(tamx2,  tamy2,  tamz2 );
          glEnd();

          // - TOPO
         glBegin(GL_POLYGON);
          glVertex3f( tamx1,  tamy2,  tamz1 );
          glVertex3f( tamx2,  tamy2,  tamz1 );
          glVertex3f( tamx2,  tamy2,  tamz2 );
          glVertex3f( tamx1,  tamy2,  tamz2 );
          glEnd();

          //- BASE
         glBegin(GL_POLYGON);
          glVertex3f(  tamx1, tamy1,  tamz1 );
          glVertex3f( tamx2,  tamy1,  tamz1 );
          glVertex3f( tamx2,  tamy1,  tamz2 );
          glVertex3f(  tamx1,  tamy1, tamz2 );
          glEnd();
        //porta
        glTranslatef(3,0,0);
        glColor3f(0.6, 0.3, 0.0);
           glBegin(GL_POLYGON);
            glVertex3f(0, 0, -0.01);
            glVertex3f(1, 0,-0.01);
            glVertex3f(1, 1, -0.01);
            glVertex3f(0, 1, -0.01);
          glEnd();




        glPopMatrix();
        glColor3f(0.9, 0.9, 1);

        //janela frente
        for(int i = 1; i < 3; i++){
            for(int j = 0; j < 4; j++) {
                glPushMatrix();
                    glTranslatef(i*3, j*1.9, 0);
                    glBegin(GL_POLYGON);
                        glVertex3f(-0.5, 0, -0.01);
                        glVertex3f(0.5, 0, -0.01);
                        glVertex3f(0.5, 1.3, -0.01);
                        glVertex3f(-0.5, 1.3, -0.01);
                    glEnd();
                glPopMatrix();
            }
        }

         //janela tras
        for(int i = 1; i < 3; i++){
            for(int j = 0; j < 4; j++) {
                glPushMatrix();
                    glTranslatef(i*3, j*1.9, 0);
                    glBegin(GL_POLYGON);
                        glVertex3f(-0.5, 0, 4.01);
                        glVertex3f(0.5, 0, 4.01);
                        glVertex3f(0.5, 1.3, 4.01);
                        glVertex3f(-0.5, 1.3, 4.01);
                    glEnd();
                glPopMatrix();
            }
        }

        //janela direita
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 4; j++) {
                glPushMatrix();
                    glTranslatef(0, j*1.9, i*2);
                    glBegin(GL_POLYGON);
                        glVertex3f(1.99, 0, 0.5);
                        glVertex3f(1.99, 0, 1.5);
                        glVertex3f(1.99, 1.3, 1.5);
                        glVertex3f(1.99, 1.3, 0.5);
                    glEnd();
                glPopMatrix();
            }
        }

        //janela esquerda
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 4; j++) {
                glPushMatrix();
                    glTranslatef(0, j*1.9, i*2);
                    glBegin(GL_POLYGON);
                        glVertex3f(7.01, 0, 0.5);
                        glVertex3f(7.01, 0, 1.5);
                        glVertex3f(7.01, 1.3, 1.5);
                        glVertex3f(7.01, 1.3, 0.5);
                    glEnd();
                glPopMatrix();
            }
        }



}

//desenha o chao
void grama(){
    // Draw ground - 200x200 square colored green
	glColor3f(0.0, 0.7, 0.0);
    glBegin(GL_QUADS);
		glVertex3f(-200.0,0, -200.0);
		glVertex3f(-200.0,0,  200.0);
		glVertex3f( 200.0,0,  200.0);
		glVertex3f( 200.0,0, -200.0);
	glEnd();


}

//desenha as ruas
void rua(){
    glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
		glVertex3f(-2.0,0.01, -5.0);
		glVertex3f(11.0,0.01, -5.0);
		glVertex3f(11.0,0.01, -1.0);
		glVertex3f(-2.0,0.01, -1.0);
	glEnd();

    glColor3f(1.0, 1.0, 0.0);
    glLineWidth(3);
	glBegin(GL_LINES);
        glVertex3f(1.0,0.02, -3.0);
		glVertex3f(6.0,0.02, -3.0);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
		glVertex3f(1.0,0.01, 5.0);
		glVertex3f(-2.0,0.01, 5.0);
		glVertex3f(-2.0,0.01, -5.0);
		glVertex3f(1.0,0.01, -5.0);
	glEnd();

    glColor3f(1.0, 1.0, 0.0);
    glLineWidth(3);
	glBegin(GL_LINES);
        glVertex3f(-0.5,0.02, 1.0);
		glVertex3f(-0.5,0.02, 5.0);
	glEnd();
}

//desenha as nuvnes
void nuvem(){
    glPushMatrix();
    	glColor3f(1.0, 1.0, 1.0);
    	glTranslatef(0,60,0);
 		glutSolidSphere(2, 20, 20);
        glTranslatef(1.4,0,0);
        glutSolidSphere(1.6, 20, 20);
        glTranslatef(-3.2,0,0);
        glutSolidSphere(1.4, 20, 20);
    glPopMatrix();

}

//desenha as arvores
void arvore(){
    float tamx1=1,tamx2=2,tamy1=0,tamy2=2,tamz1=0,tamz2=1;
    glPushMatrix();
		glTranslatef(32, 0.0, 0);
    	glColor3f(0.6, 0.3, 0);
       //- FRENTE
         glBegin(GL_POLYGON);
            glVertex3f(tamx1, tamy1,tamz1 );
            glVertex3f(tamx2, tamy1, tamz1 );
            glVertex3f(tamx2, tamy2,  tamz1 );
            glVertex3f( tamx1, tamy2, tamz1 );
          glEnd();

          // - TRASEIRA
         glBegin(GL_POLYGON);
          glVertex3f(  tamx1,  tamy1, tamz2 );
          glVertex3f( tamx2,  tamy1, tamz2 );
          glVertex3f( tamx2,  tamy2, tamz2 );
          glVertex3f( tamx1,  tamy2, tamz2 );
          glEnd();

          // - Direito
         glBegin(GL_POLYGON);
          glVertex3f( tamx1,  tamy1, tamz1 );
          glVertex3f( tamx1,  tamy1, tamz2 );
          glVertex3f( tamx1,  tamy2, tamz2 );
          glVertex3f( tamx1,  tamy2, tamz1 );
          glEnd();

          // - ESQUERDA
         glBegin(GL_POLYGON);
          glVertex3f(tamx2,  tamy1, tamz2 );
          glVertex3f(tamx2,  tamy1, tamz1 );
          glVertex3f(tamx2,  tamy2, tamz1 );
          glVertex3f(tamx2,  tamy2,  tamz2 );
          glEnd();

          // - TOPO
         glBegin(GL_POLYGON);
          glVertex3f( tamx1,  tamy2,  tamz1 );
          glVertex3f( tamx2,  tamy2,  tamz1 );
          glVertex3f( tamx2,  tamy2,  tamz2 );
          glVertex3f( tamx1,  tamy2,  tamz2 );
          glEnd();

          //- BASE
         glBegin(GL_POLYGON);
          glVertex3f(  tamx1, tamy1,  tamz1 );
          glVertex3f( tamx2,  tamy1,  tamz1 );
          glVertex3f( tamx2,  tamy1,  tamz2 );
          glVertex3f(  tamx1,  tamy1, tamz2 );
          glEnd();

        glTranslatef(1.5, 2, 0.5);
        glRotatef(-90,1,0,0);

    	glColor3f(0.6, 0.8, 0);
        glutSolidCone(2,5,100,100);
        glPopMatrix();

}

//desenha o lago
void lago(){
    GLint i;
    glPushMatrix();
    glTranslatef(50,0.01,0);
    glRotatef(90,1,0,0);

    glColor3f(0.0, 0.0, 0.8);


    glBegin(GL_TRIANGLE_FAN);
		for(i = 0; i <= 100; i++) {
			glVertex2f(
              0 + ((11) * cos(i *  6.28 / 100)),
              0 + ((11) * sin(i * 6.28 / 100)));
		}
    glEnd();
     glBegin(GL_TRIANGLE_FAN);
		for(i = 0; i <= 100; i++) {
			glVertex2f(
              10 + ((9) * cos(i *  6.28 / 100)),
              10 + ((9) * sin(i * 6.28 / 100)));
		}
    glEnd();
    glPopMatrix();
}

//movimenta a bola do canhao vermelho
void MovimentaBola1(int passo)
{
    GLfloat V0y = v0 * sin (angulov*radiano), V0x = v0 *cos(angulov*radiano)*cos(anguloh*radiano),V0z= v0 * sin(anguloh*radiano)* cos(angulov*radiano); //velocidades nos eixos X e Y


    moverbolax = V0x * t; // a bola anda de acordo com sua velociade para a direita em x

    moverbolay = (V0y * t) - (0.5 * gravidade * pow(t,2)) ; // a bola anda de acordo com sua velociade em y

    moverbolaz = V0z * t;
    t += 0.5; // tempo decorrido

    glutPostRedisplay(); //redesenha a bola

    if(controleTempo == 1 ) { // função para o redesenho da bola automaticamente com o passar do tempo
        glutTimerFunc(500 - tempo,MovimentaBola1, 1);
    }
}

//movimenta a bola do canhao azul
void MovimentaBola2(int passo)
{
    GLfloat V0y = v0_2 * sin (angulov2*radiano), V0x = v0_2 *cos(angulov2*radiano)*cos(anguloh2*radiano),V0z= v0_2 * sin(anguloh2*radiano)* cos(angulov2*radiano); //velocidades nos eixos X e Y

    moverbolax2 = V0x * t2; // a bola anda de acordo com sua velociade para a direita em x

    moverbolay2 = (V0y * t2) - (0.5 * gravidade * pow(t2,2)) ; // a bola anda de acordo com sua velociade em y

    moverbolaz2= V0z * t2;
    t2 += 0.5; // tempo decorrido

    glutPostRedisplay(); //redesenha a bola

    if(controleTempo == 1 ) { // função para o redesenho da bola automaticamente com o passar do tempo
        glutTimerFunc(500 - tempo,MovimentaBola2, 1);
    }
}

//atualiza a posição da camera
void update(void)
{
	if (deltaMove) { // atualiza a posição da camera
		x += deltaMove * lx * 0.1;
		z += deltaMove * lz * 0.1;
	}
	if(deltaMove2){
		y += deltaMove2 * ly ;
	}
	glutPostRedisplay(); // redesenha tudo
}

//atualiza o valor da velociade
void AtualizaVelocidade(GLint x){
    GLfloat valor = ((x )/10) ;
    if(jogador==0){
        v0 = valor+10;
        sprintf(convertidoVelocidade, "%.2f ", v0);
    }
    else{
        v0_2=valor+10;
        sprintf(convertidoVelocidade2, "%.2f ", v0_2);
    }
}

//escreve a palavra velocidade
void Velocidade()
{
    glColor3f(0, 0, 0);
    // posicionamos na tela
    glRasterPos2f(0.3, 0.6);
    glutPostRedisplay();
    char* p;
    if(jogador==0)p = (char*) convertidoVelocidade;
    else p = (char*) convertidoVelocidade2;
    while (*p != '\0') {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p++);
    }

}

//a barra da velocidade
void BarraVelocidade(){
    glColor3f(0, 0, 0);


     glPushMatrix();

    glColor3f(0,0,0);
    if(jogador==0)glTranslatef(-0.9 +((v0-10)/10),0.0,0);
    else glTranslatef(-0.9 +((v0_2-10)/10),0.0,0);
    criarCirculo(0.05);

    glColor3f(0.8,0.8,0.8);
    criarCirculo(0.11);

    glPopMatrix();

    glColor3f(0,0,0);
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2f (-0.9, 0);
        glVertex2f (0.9, 0);
    glEnd();
   // posicionamos na tela
    glRasterPos2f(-0.9, 0.6);

    // String a ser escrita na tela
    char* p = (char*) "Velocidade= ";
    while (*p != '\0') {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p++);
    }
}


//desenha a cena
void renderScene(void)
{
	int i, j;

	glClearColor(0.0, 0.7, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    gluLookAt(
			x,      y, z,
			x + lx, y+y2, z + lz,
			0.0,    1.0,    0.0);
    grama();
    lago();
    arvore();
        for(i = -6; i < 6; i++){
            for(j = -6; j < 6; j++) {
                glPushMatrix();
                glTranslatef(i*20, 0, j*20);
                if(i<-3 || i>2 || j<-2 || j>2 ) arvore();
                glScaled(3,1,2);
                nuvem();
                glPopMatrix();
            }
        }

    int    corpredio=1, cont = 0;
    for(i = -3; i < 3; i++){
        if(corpredio == 1){
            glColor3f(0.7, 0.7, 0.7);
            glNormal3f(0, 1, 0);      // Green

            corpredio=0;
        }
        else
        {
            glColor3f(0.8, 0.8, 0.8);
            glNormal3f(0, 1, 0);      // Green

            corpredio=1;
        }
        for(j = -3; j < 3; j++) {
			glPushMatrix();
				glTranslatef(i*10, 0, j*10);
                rua();

                aleatorio[cont][0]=altura[cont];
                aleatorio[cont][1]=i*10;
                aleatorio[cont][2]=j*10;

                glScalef(1,0.5*altura[cont],1);
                if(corpredio == 1){
                    glColor3f(0.7, 0.7, 0.7);
                    corpredio=0;
                }
                else
                {
                    glColor3f(0.8, 0.8, 0.8);
                    corpredio=1;
                }
                predio();
			glPopMatrix();
			cont++;
		}
    }


    glPushMatrix();
    glTranslatef(5+aleatorio[localizacaoCanhao1][1],3.5*aleatorio[localizacaoCanhao1][0],1.5+aleatorio[localizacaoCanhao1][2]);
    canhao1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5+aleatorio[localizacaoCanhao2][1],3.5*aleatorio[localizacaoCanhao2][0],1.5+aleatorio[localizacaoCanhao2][2]);
    canhao2();
    glPopMatrix();
    glColor3f(0.0, 0.0, 0.0);

     /*float tamx1=aleatorio[1][1]+2,tamx2=aleatorio[1][1]+7,tamy1=0,tamy2=20,tamz1=(aleatorio[1][2]),tamz2=(aleatorio[1][2]+4);*/

	glutSwapBuffers();
}

//desenha a subjanela
void rendeSubScene(){
    glutPostRedisplay();
    if(jogador==1)glClearColor(0.0, 0.0, 0.8, 0.7);
    if(jogador==0)glClearColor(0.7, 0.0, 0.0, 0.7);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
    BarraVelocidade();
    Velocidade();
    Pontuacao();
    glutSwapBuffers();

}

//zera as variaveis
void zerar(){
        destruirCorpo = 0;
        destruirCorpo2 = 0;

        t = 0;
        t2 = 0;

        moverbolax = 0;
        moverbolay = 0;
        moverbolaz = 0;
        moverbolax2 = 0;
        moverbolay2 = 0;
        moverbolaz2 = 0;

        posicaox = moverbolax;
        posicaoy = 0.5+moverbolay;
        posicaoz = 0.25-moverbolaz;
        posicaox2 = moverbolax2;
        posicaoy2 = 0.5+moverbolay2;
        posicaoz2 = 0.25-moverbolaz2;
}

//uso do teclado
void processNormalKeys(unsigned char key, int xx, int yy)
{
	if (key == ESC || key == 'q' || key == 'Q') exit(0);

    //mover o cano para a esquerda
    if(key == 'A' || key == 'a') {
             if(jogador==0){
                    anguloh+=5;
                    if(anguloh==360) anguloh=0;
            }
            else{
                anguloh2+=5;
                if(anguloh2==360) anguloh2=0;
            }

    }
    //mover o cano para a direita
    if(key == 'd' || key == 'D') {
            if(jogador==0){
                    anguloh-=5;
                    if(anguloh==-360) anguloh=0;
            }
            else{
                anguloh2-=5;
                if(anguloh2==-360) anguloh2=0;
            }

    }
    //mover o cano para cima
    if(key == 'w' || key == 'W') {
        if(jogador==0){
            if(angulov<90){
                angulov+=5;
            }
        }
        if(jogador==1){
            if(angulov2<90){
                angulov2+=5;
            }
        }

    }
    //mover o cano para baixo
    if(key == 's' || key == 'S') {
        if(jogador==0){
            if(angulov>0){
                angulov-=5;
            }
        }
        if(jogador==1){
            if(angulov2>0){
                angulov2-=5;
            }
        }
    }

    //localizar canhao vermelho
    if(key == 'z' || key == 'Z') {
            x=5+aleatorio[localizacaoCanhao1][1];
            y=3.5*aleatorio[localizacaoCanhao1][0]+1;
            z=-1.5+aleatorio[localizacaoCanhao1][2];
            lx = 0.0;
            ly=1.0;
            lz = 1.0;
            deltaAngle=0;
            angle=0;

        }

    //localizar canhao azul
    if(key == 'x' || key == 'X ') {
        x=5+aleatorio[localizacaoCanhao2][1];
        y=3.5*aleatorio[localizacaoCanhao2][0]+1;
        z=-1.5+aleatorio[localizacaoCanhao2][2];
        lx = 0.0;
        ly=1.0;
        lz = 1.0;
        deltaAngle=0;
        angle=0;
        }

   //atirar
    if(key=='c' || key=='C' ){
        if(flag2 == 1){
            controleTempo=1;
            zerar();
            if(jogador==0)MovimentaBola1(1);
            if(jogador==1) MovimentaBola2(1);
        }
    }

    //novo jogo
    if(key=='n' || key=='N' ){
        zerar();
        locCanhao();
        gerarAltura();
        anguloh=0;
        anguloh2=0;
        angulov2=0;
        angulov=0;
        ponto1 = 0;
        ponto2 = 0;
        AtualizaVelocidade(0);
    }

    //olha o mapa de cima
    if(key=='m' || key=='M'){
        x=0;
        y=30;
        y2=-y;
        z=0;
    }

    //olhar o mapa de frente
    if(key=='b' || key=='B'){
        x=5;
        y=3.5*altura[21]+1;
        y2=0;
        z=-3;
    }

   //reconstuir
    if(key=='r' || key=='R'){
        controleTempo = 0;
        flag2 = 1;
        zerar();
        gerarAltura();
        locCanhao();
        anguloh2 = 0;
        anguloh = 0;
        angulov2 = 0;
        angulov = 0;
        AtualizaVelocidade(0);
    }

}

//uso das setas
void pressSpecialKey(int key, int xx, int yy)
{
	switch (key) {
		case GLUT_KEY_UP : deltaMove = 3; break;
		case GLUT_KEY_DOWN : deltaMove = -3; break;
		case GLUT_KEY_LEFT : deltaMove2 = 1; break;
		case GLUT_KEY_RIGHT :deltaMove2 = -1; break;
	}
}

//soltar o uso das setas
void releaseSpecialKey(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_UP : deltaMove = 0.0; break;
		case GLUT_KEY_DOWN : deltaMove = 0.0; break;
		case GLUT_KEY_LEFT : deltaMove2 = 0.0; break;
		case GLUT_KEY_RIGHT : deltaMove2 = 0.0; break;
	}
}

//uso do mouse
void mouseMove(int x, int y)
{
	if (isDragging) {
        deltaAngle = (x - xDragStart) * 0.005;

        lx = -sin(angle + deltaAngle);
        lz = cos(angle + deltaAngle);

	}
}

//uso do clique do mouse
void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			isDragging = 1;
			xDragStart = x;
		}
		else  {
			angle += deltaAngle;
			isDragging = 0;
		}
	}
	if (state == GLUT_UP && x>=10 && x<=188 && y>=46 && y<=53 )
    {
        AtualizaVelocidade(x);
    }
}

//inicializa as variaveis da glut
void Inicializa (void)
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);
    glutIgnoreKeyRepeat(1);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressSpecialKey);
	glutSpecialUpFunc(releaseSpecialKey);

    glEnable(GL_DEPTH_TEST);
	gerarAltura();
	locCanhao();
	y=3.5*altura[21]+1;
    //AtualizaVelocidade(0);
    IDquadric=gluNewQuadric();
}

//função principal
int main(int argc, char **argv)
{
	printf("\n\
-----------------------------------------------------------------------\n\
  Batalha urbana:\n\
  - Arraste o mouse para a esqueda-direita para rotacionar a camera\n\
  - Aperte a seta para cima ou para baixo para mover a camera para frente ou para tras\n\
  - Aperte a seta para esquerda ou para direita para mover a camera para cima ou para baixo\n\
  - q ou ESC para sair\n\
  - w para mover o cano do canhao para cima\n\
  - s para mover o cano do canhao para baixo\n\
  - a para mover o cano do canhao para esquerda\n\
  - d para mover o cano do canhao para direita\n\
  - n para criar um novo jogo\n\
  - z para localizar o canhao vermelho\n\
  - x para localizar o canhao azul\n\
  - m para ver o mapa de cima\n\
  - b para ver o mapa de frente\n\
  - r para reconstruir o canhao\n\
  - c para atirar\n\
-----------------------------------------------------------------------\n");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 400);
	window=glutCreateWindow("OpenGL/GLUT Sampe Program");
	glutReshapeFunc(changeSize);
	glutDisplayFunc(renderScene);
	glutIdleFunc(update);
    Inicializa();


	glutCreateSubWindow(window,0,0,200,100);
    glutDisplayFunc(rendeSubScene);
    Inicializa();
	glutMainLoop();

	return 0;
}
