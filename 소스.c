#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////
int snowNumber = 0;
float snowObejct[200][3];
int makeboard[80][80];

void SetupRC()//초기화
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // clear 색상을 검정색으로 설정
	srand((unsigned)time(NULL));
	for (int i = 0; i < 200; ++i)
	{
		snowObejct[i][0] = rand() % (500 - (-500) + 1) + (-500);//x값
		snowObejct[i][1] = rand() % 300;//y값
		snowObejct[i][2] = rand() % (500 - (-500) + 1) + (-500);//x값
	}
}

void snow()
{
	for (int i = 0; i < 200; ++i)
	{
		glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);//색상
		glTranslatef(snowObejct[i][0], snowObejct[i][1], snowObejct[i][2]);//위치
		//반지름, 높이, z축 분활개수, z축 방향
		glutSolidSphere(3, 10, 10);
		glPopMatrix();
	}
}

void drop()
{
	for (int i = 0; i < 200; ++i)
	{
		snowObejct[i][1] -= 1;
	}
	for (int i = 0; i < 200; ++i)
	{
		if (snowObejct[i][1] < -50)
		{
			snowObejct[i][0] = rand() % (500 - (-500) + 1) + (-500);//x값
			snowObejct[i][1] = rand() % 300;//y값
			snowObejct[i][2] = rand() % (500 - (-500) + 1) + (-500);//x값
			if (snowNumber < 1000)
				snowNumber++;
		}
	}
}


int Loadfile()
{

	FILE *fp;

	fp = fopen("map.txt", "rt");

	int cha;

	while (feof(fp) == 0)
	{
		for (int i = 0; i < 80; i++)
		{
			for (int j = 0; j < 80; j++)
			{
				fscanf(fp, "%d", &cha);
				makeboard[i][j] = cha;
			}
		}
	}
	fclose(fp);
}

void board_maker()
{
	for (int i = 0; i < 80; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			if (makeboard[i][j] == 0)
			{
				glPushMatrix();
				{
					glColor3f(1.0f, 1.0f, 1.0f);
					glTranslatef(-400.0 + 10 * j, 0.0, -400.0 + 10 * i);
					glutSolidCube(10);
				}
				glPopMatrix();
			}

			else if (makeboard[i][j] == 1)
			{
				glPushMatrix();
				{
					glColor3f(0.7f, 0.5f, 0.3f);
					glTranslatef(-400.0 + 10 * j, 0.0, -400.0 + 10 * i);
					glutSolidCube(10);
				}
				glPopMatrix();
			}
			else if (makeboard[i][j] == 2)
			{
				glPushMatrix();
				{
					glColor3f(0.0f, 0.0f, 1.0f);
					glTranslatef(-400.0 + 10 * j, -20.0, -400.0 + 10 * i);
					glutSolidCube(10);
				}
				glPopMatrix();
			}
			else if (makeboard[i][j] == 3)
			{
				glPushMatrix();
				{
					glColor3f(0.4f, 0.2f, 0.1f);
					glTranslatef(-400.0 + 10 * j, 0.0, -400.0 + 10 * i);
					glutSolidCube(10);
				}
				glPopMatrix();
			}
		}
	}
}
void drawTree()
{

	// 잎


	glPushMatrix();
	glColor3f(0.1f, 0.5f, 0.3f);
	glTranslatef(-250.0, 100.0, 150.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(1.0, 4.0, 2.0);
	glutSolidCube(20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.1f, 0.4f, 0.3f);
	glTranslatef(-250.0, 100.0, 170.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(1.0, 4.0, 2.0);
	glutSolidCube(20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.1f, 0.4f, 0.3f);
	glTranslatef(-250.0, 100.0, 130.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(1.0, 4.0, 2.0);
	glutSolidCube(20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.1f, 0.5f, 0.3f);
	glTranslatef(-250.0, 100.0, 110.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(1.0,3.0, 1.0);
	glutSolidCube(20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.1f, 0.5f, 0.3f);
	glTranslatef(-250.0, 100.0, 190.0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glScalef(1.0, 3.0, 1.0);
	glutSolidCube(20);
	glPopMatrix();
	
	// 기둥
	glPushMatrix();
	glColor3f(0.5f, 0.3f, 0.3f);
	glTranslatef(-250.0, 10.0, 150.0);
	glScalef(1.0, 10.0, 1.0);
	glutSolidCube(20);
	glPopMatrix();

}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0f, w / h, 1.0, 1000.0); // 원근 거리
	glTranslatef(0.0, -50.0, -600.0);
	glRotatef(40, 1.0f, 0.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);

}

void TimerFunction(int value)
{
	drop();
	glutPostRedisplay();
	glutTimerFunc(30, TimerFunction, 1);
}


void drawScene()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Loadfile();
	board_maker();
	snow();//눈
	drawTree();
	glutSwapBuffers();
}



void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{

	}
	glutPostRedisplay();
}

void main(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(300, 100);
	glutInitWindowSize(1200, 700);
	glutCreateWindow("Hello Snowman");
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawScene);
	glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	SetupRC();//초기화
	glutMainLoop();

}