#include <GL/glut.h>
#include <cmath>
#include <string>

using namespace std;

float jogadorEsquerdaX = 5.0;
float jogadorEsquerdaY = 110.0;
bool jogadorEsquerdaSubindo = false;
bool jogadorEsquerdaDescendo = false;

float jogadorDireitaX = 240.0;
float jogadorDireitaY = 110.0;
bool jogadorDireitoSubindo = false;
bool jogadorDireitoDescendo = false;

float bolaX = 125.0;
float bolaY = 125.0;
float velocidadeBolaX = 3.0;
float velocidadeBolaY = 0.0;
float raioBola = 2.5;

int pontuacaoEsquerda = 0;
int pontuacaoDireita = 0;

void inicializar() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    gluOrtho2D(0.0f, 250.0f, 0.0f, 250.0f);
}

void exibirPontuacao() {
    glRasterPos2f(10.0, 240.0);
    glColor3f(1.0f, 1.0f, 1.0f);

    string pontuacaoEsquerdaStr = to_string(pontuacaoEsquerda);
    string pontuacaoDireitaStr = to_string(pontuacaoDireita);

    for (char c : pontuacaoEsquerdaStr) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '-');

    for (char c : pontuacaoDireitaStr) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}

void jogo() {
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT);

    if(jogadorEsquerdaSubindo) {
        jogadorEsquerdaY += 3.0;
    }
    if(jogadorEsquerdaDescendo) {
        jogadorEsquerdaY -= 3.0;
    }

    if(jogadorDireitoSubindo) {
        jogadorDireitaY += 3.0;
    }
    if(jogadorDireitoDescendo) {
        jogadorDireitaY -= 3.0;
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS); //playerLeft
    glVertex2i(jogadorEsquerdaX, jogadorEsquerdaY);
    glVertex2i(jogadorEsquerdaX, jogadorEsquerdaY + 45.0);
    glVertex2i(jogadorEsquerdaX + 5.0, jogadorEsquerdaY + 45.0);
    glVertex2i(jogadorEsquerdaX + 5.0, jogadorEsquerdaY);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS); // playerRight
    glVertex2i(jogadorDireitaX, jogadorDireitaY);
    glVertex2i(jogadorDireitaX, jogadorDireitaY + 45.0);
    glVertex2i(jogadorDireitaX + 5.0, jogadorDireitaY + 45.0);
    glVertex2i(jogadorDireitaX + 5.0, jogadorDireitaY);
    glEnd();

    bolaX += velocidadeBolaX; // bola
    bolaY += velocidadeBolaY;
    int numeroTriangulos = 100;
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(bolaX, bolaY);
    for (int i = 0; i <= numeroTriangulos; i++) {
        float angulo = 5.0f * 3.14f * float(i) / float(numeroTriangulos);
        float x = raioBola * cos(angulo) + bolaX;
        float y = raioBola * sin(angulo) + bolaY;
        glVertex2f(x, y);
    }
    glEnd();

    if(bolaX - raioBola <= 0 || bolaX + raioBola >= 250) { // colisao com parede
        velocidadeBolaX = -velocidadeBolaX;
    }
    if(bolaY - raioBola <= 0 || bolaY + raioBola >= 250) {
        velocidadeBolaY = -velocidadeBolaY;
    }

    if(bolaX + raioBola >= 250.0) { // pontuacao
        pontuacaoEsquerda++;
        bolaX = 125.0;
        bolaY = 125.0;
        velocidadeBolaX = -3.0;
        velocidadeBolaY = 0.0;
    }
    if(bolaX - raioBola <= 0.0) {
        pontuacaoDireita++;
        bolaX = 125.0;
        bolaY = 125.0;
        velocidadeBolaX = 3.0;
        velocidadeBolaY = 0.0;
    }

    if (bolaX - raioBola <= jogadorEsquerdaX + 5.0) { //colisao com jogador
        if (bolaY >= jogadorEsquerdaY && bolaY <= jogadorEsquerdaY + 45.0) {
            velocidadeBolaX = -velocidadeBolaX;
            velocidadeBolaY = (bolaY - (jogadorEsquerdaY + 22.5)) * 0.1;
        }
    }

    if (bolaX + raioBola >= jogadorDireitaX) {
        if (bolaY >= jogadorDireitaY && bolaY <= jogadorDireitaY + 45.0) {
            velocidadeBolaX = -velocidadeBolaX;
            velocidadeBolaY = (bolaY - (jogadorDireitaY + 22.5)) * 0.1;
        }
    }

    if(jogadorEsquerdaY + 45.0 >= 250.0) { //jogador nn sumir
        jogadorEsquerdaY = 250.0 - 45.0;
    } else if(jogadorEsquerdaY <= 0.0) {
        jogadorEsquerdaY = 0.0;
    }
    if(jogadorDireitaY + 45.0 >= 250.0) {
        jogadorDireitaY = 250.0 - 45.0;
    } else if(jogadorDireitaY <= 0.0) {
        jogadorDireitaY = 0.0;
    }

    exibirPontuacao();

    glPopMatrix();
    glutSwapBuffers();
}

void atualizarJogo(int valor) {
    glutPostRedisplay();
    glutTimerFunc(16, atualizarJogo, 0);
}

void eventoTeclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case 'w': jogadorEsquerdaSubindo = true;
            break;

        case 's': jogadorEsquerdaDescendo = true;
            break;

        case '8': jogadorDireitoSubindo = true;
            break;

        case '2': jogadorDireitoDescendo = true;
            break;
    }
    glutPostRedisplay();
}

void eventoTecladoPara(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case 'w': jogadorEsquerdaSubindo = false;
            break;

        case 's': jogadorEsquerdaDescendo = false;
            break;

        case '8': jogadorDireitoSubindo = false;
            break;

        case '2': jogadorDireitoDescendo = false;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Ping Pong");
    glutDisplayFunc(jogo);
    glutKeyboardFunc(eventoTeclado);
    glutKeyboardUpFunc(eventoTecladoPara);
    inicializar();
    glutTimerFunc(0, atualizarJogo, 0);
    glutMainLoop();

    return 0;
}