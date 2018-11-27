#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////
int snowNumber = 0;
float snowObejct[200][3];
int makeboard[80][80];
float xRotation = 0.0f, yRotation = 0.0f, zRotation = 0.0f;//�����̼�
void SetupRC()//�ʱ�ȭ
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // clear ������ ���������� ����
	srand((unsigned)time(NULL));
	for (int i = 0; i < 200; ++i)
	{
		snowObejct[i][0] = rand() % (500 - (-500) + 1) + (-500);//x��
		snowObejct[i][1] = rand() % 300;//y��
		snowObejct[i][2] = rand() % (500 - (-500) + 1) + (-500);//x��
	}
}

void snow()
{
	for (int i = 0; i < 200; ++i)
	{
		glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);//����
		glTranslatef(snowObejct[i][0], snowObejct[i][1], snowObejct[i][2]);//��ġ
		//������, ����, z�� ��Ȱ����, z�� ����
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
			snowObejct[i][0] = rand() % (500 - (-500) + 1) + (-500);//x��
			snowObejct[i][1] = rand() % 300;//y��
			snowObejct[i][2] = rand() % (500 - (-500) + 1) + (-500);//x��
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
			if (makeboard[i][j] == 0)//��
			{
				glPushMatrix();
				{
					glColor3f(1.0f, 1.0f, 1.0f);
					glTranslatef(-400.0 + 10 * j, 0.0, -400.0 + 10 * i);
					glutSolidCube(10);
				}
				glPopMatrix();
			}

			else if (makeboard[i][j] == 1)//��
			{
				glPushMatrix();
				{
					glColor3f(0.7f, 0.5f, 0.3f);
					glTranslatef(-400.0 + 10 * j, 0.0, -400.0 + 10 * i);
					glutSolidCube(10);
				}
				glPopMatrix();
			}
			else if (makeboard[i][j] == 2)//��
			{
				glPushMatrix();
				{
					glColor3f(0.0f, 0.0f, 1.0f);
					glTranslatef(-400.0 + 10 * j, -20.0, -400.0 + 10 * i);
					glutSolidCube(10);
				}
				glPopMatrix();
			}
			else if (makeboard[i][j] == 3)//�ٸ�
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
void drawTree(float Tx, float Ty, float Tz)
{

	// ��

	for (int i = 0;i < 4;i++) {
		glPushMatrix();
		glColor3f(0.1f, 0.3f + i * 0.1, 0.3f);
		glTranslatef(Tx, Ty + i * 20, Tz);
		glScalef(2.5 - i * 0.5, 1, 2.5 - i * 0.5);
		glutSolidCube(20);
		glPopMatrix();
	}

	// ����

	glPushMatrix();
	glColor3f(1.0f, 0.2f, 0.2f);
	glTranslatef(Tx, Ty+80, Tz);
	glutSolidSphere(8.0, 50, 24);
	glPopMatrix();


	// ���
	glPushMatrix();
	glColor3f(0.5f, 0.3f, 0.3f);
	glTranslatef(Tx, Ty-65, Tz);
	glScalef(1.0, 5.5, 1.0);	// y������ 12��
	glutSolidCube(20);
	glPopMatrix();

}

void drawStone(float Sx, float Sy, float Sz, float Ssize)//��
{
	glPushMatrix();
	
	glTranslatef(Sx, Sy, Sz);
	glColor3f(0.5f, 0.5f, 0.5f);
	glutSolidCube(15+Ssize);

	glTranslatef(0.0, 0.0+10.0+Ssize, 0.0);	
	glColor3f(0.4f, 0.4f, 0.4f);
	glutSolidCube(10+Ssize);

	glTranslatef(0.0, 0.0-10.0, 0.0+10.0+Ssize);
	glColor3f(0.55f, 0.55f, 0.55f);
	glutSolidCube(8+Ssize);

	glPopMatrix();
}

void character()//ĳ����
{
	glPushMatrix();
	{
		glPushMatrix();//������ ��,�ٸ�
		{
			glPushMatrix();//��
			glTranslatef(150.0, 10.0, 300.0);
			glScalef(1.0, 1.3, 2.0);
			glColor3f(0.9f, 0.3f, 0.3f);
			glutSolidCube(5);
			glPopMatrix();

			glPushMatrix();//�縻
			glTranslatef(150.0, 13.0, 297.0);
			glScalef(1.0, 5.0, 1.0);
			glColor3f(1.0f, 0.9f, 0.9f);
			glutSolidCube(4.5);
			glPopMatrix();

			glPushMatrix();//�ٸ�
			glTranslatef(150.0, 10.0, 297.0);
			glScalef(1.0, 20.0, 1.0);
			glColor3f(0.9f, 0.8f, 0.7f);
			glutSolidCube(4);
			glPopMatrix();


		}
		glPopMatrix();

		glPushMatrix();//���� ��,�ٸ�
		{
			glPushMatrix();//��
			glTranslatef(160.0, 10.0, 300.0);
			glScalef(1.0, 1.3, 2.0);
			glColor3f(0.9f, 0.3f, 0.3f);
			glutSolidCube(5);
			glPopMatrix();

			glPushMatrix();//�縻
			glTranslatef(160.0, 13.0, 297.0);
			glScalef(1.0, 5.0, 1.0);
			glColor3f(1.0f, 0.9f, 0.9f);
			glutSolidCube(4.5);
			glPopMatrix();

			glPushMatrix();//�ٸ�
			glTranslatef(160.0, 10.0, 297.0);
			glScalef(1.0, 20.0, 1.0);
			glColor3f(0.9f, 0.8f, 0.7f);
			glutSolidCube(4);
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();//����
		glTranslatef(155.0, 40.0, 300);
		glScalef(1.0, 3.0, 1.0);
		glRotated(-90, 1, 0, 0);
		glColor3f(0.9f, 0.3f, 0.3f);
		glutSolidCone(15, 20, 20, 20);
		glPopMatrix();

		glPushMatrix();//��
		glTranslatef(155.0, 87.0, 300);
		glColor3f(0.9f, 0.8f, 0.7f);
		glutSolidSphere(12, 20, 20);
		glPopMatrix();

		glPushMatrix();//������ ��
		{
			glPushMatrix();//���
			glTranslatef(145.0, 70.0, 300);
			glColor3f(0.9f, 0.9f, 0.3f);
			glutSolidSphere(4, 15, 15);
			glPopMatrix();

			glPushMatrix();//��
			glTranslatef(145.0, 45.0, 300);
			glScalef(1.0, 10.0, 1.0);
			glRotated(45, 0, 0, 1);
			glColor3f(0.9f, 0.8f, 0.7f);
			glutSolidCube(4);
			glPopMatrix();

			glPushMatrix();//��
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();//���� ��
		{
			glPushMatrix();//���
			glTranslatef(165.0, 70.0, 300);
			glColor3f(0.9f, 0.9f, 0.3f);
			glutSolidSphere(4, 15, 15);
			glPopMatrix();

			glPushMatrix();//��
			glTranslatef(165.0, 45.0, 300);
			glScalef(1.0, 10.0, 1.0);
			glRotated(-45, 0, 0, 1);
			glColor3f(0.9f, 0.8f, 0.7f);
			glutSolidCube(4);
			glPopMatrix();

			glPushMatrix();//��
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0f, w / h, 1.0, 1000.0); // ���� �Ÿ�
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
	glClearColor(0.0f, 0.6f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	glRotated(xRotation, 1.0f, 0.0f, 0.0f);
	glRotated(yRotation, 0.0f, 1.0f, 0.0f);
	glRotated(zRotation, 0.0f, 0.0f, 1.0f);
	Loadfile();
	board_maker();
	snow();//��

	// ����
	drawTree(-280.0,120.0,-220.0);
	drawTree(160.0, 120.0, -120.0);
	drawTree(250.0, 120.0, 300.0);
	drawTree(-150.0, 120.0, 220.0);

	//��
	drawStone(-200.0, 10.0, -300.0, 7);
	drawStone(-300.0, 10.0, 300.0, 0);
	drawStone(300.0, 10.0, 100.0, 7);
	drawStone(150.0, 10.0, 350.0, 0);

	//ĳ����
	character();

	glPopMatrix();
	glutSwapBuffers();
}





void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
		xRotation += 3.0f;
		break;
	case 'y':
		yRotation += 3.0f;
		break;
	case 'z':
		zRotation += 3.0f;
		break;
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
	SetupRC();//�ʱ�ȭ
	glutMainLoop();

}