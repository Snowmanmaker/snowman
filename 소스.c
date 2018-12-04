#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////
int snowNumber = 0;
float snowObejct[200][3];
int makeboard[80][80];
float xRotation = 0.0f, yRotation = 0.0f, zRotation = 0.0f;//로테이션
float Xmove = 0.0f, Ymove = 0.0f, Zmove = 0.0f;
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
			if (makeboard[i][j] == 0)//눈
			{
				glPushMatrix();
				{
					glColor3f(1.0f, 1.0f, 1.0f);
					glTranslatef(-400.0 + 10 * j, 0.0, -400.0 + 10 * i);
					glutSolidCube(10);
				}
				glPopMatrix();
			}

			else if (makeboard[i][j] == 1)//땅
			{
				glPushMatrix();
				{
					glColor3f(0.7f, 0.5f, 0.3f);
					glTranslatef(-400.0 + 10 * j, 0.0, -400.0 + 10 * i);
					glutSolidCube(10);
				}
				glPopMatrix();
			}
			else if (makeboard[i][j] == 2)//강
			{
				glPushMatrix();
				{
					glColor3f(0.0f, 0.0f, 1.0f);
					glTranslatef(-400.0 + 10 * j, -20.0, -400.0 + 10 * i);
					glutSolidCube(10);
				}
				glPopMatrix();
			}
			else if (makeboard[i][j] == 3)//다리
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

	// 잎

	for (int i = 0;i < 4;i++) {
		glPushMatrix();
		glColor3f(0.1f, 0.3f + i * 0.1, 0.3f);
		glTranslatef(Tx, Ty + i * 20, Tz);
		glScalef(2.5 - i * 0.5, 1, 2.5 - i * 0.5);
		glutSolidCube(20);
		glPopMatrix();
	}

	// 조명

	glPushMatrix();
	glColor3f(1.0f, 0.2f, 0.2f);
	glTranslatef(Tx, Ty+80, Tz);
	glutSolidSphere(8.0, 50, 24);
	glPopMatrix();


	// 기둥
	glPushMatrix();
	glColor3f(0.5f, 0.3f, 0.3f);
	glTranslatef(Tx, Ty-65, Tz);
	glScalef(1.0, 5.5, 1.0);	// y축으로 12배
	glutSolidCube(20);
	glPopMatrix();

}

void drawStone(float Sx, float Sy, float Sz, float Ssize)//돌
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

void character()//캐릭터
{
	glPushMatrix();
	{
		glPushMatrix();//오른쪽 발,다리
		{
			glPushMatrix();//발
			glTranslatef(150.0, 10.0, 300.0);
			glScalef(1.0, 1.3, 2.0);
			glColor3f(0.9f, 0.3f, 0.3f);
			glutSolidCube(5);
			glPopMatrix();

			glPushMatrix();//양말
			glTranslatef(150.0, 10.0, 297.0);
			glScalef(1.0, 5.0, 1.0);
			glColor3f(1.0f, 0.9f, 0.9f);
			glutSolidCube(4.5);
			glPopMatrix();

			glPushMatrix();//다리
			glTranslatef(150.0, 35.0, 297.0);
			glScalef(1.0, 20.0, 1.0);
			glColor3f(0.9f, 0.8f, 0.7f);
			glutSolidCube(4);
			glPopMatrix();


		}
		glPopMatrix();

		glPushMatrix();//왼쪽 발,다리
		{
			glPushMatrix();//발
			glTranslatef(160.0, 10.0, 300.0);
			glScalef(1.0, 1.3, 2.0);
			glColor3f(0.9f, 0.3f, 0.3f);
			glutSolidCube(5);
			glPopMatrix();

			glPushMatrix();//양말
			glTranslatef(160.0, 10.0, 297.0);
			glScalef(1.0, 5.0, 1.0);
			glColor3f(1.0f, 0.9f, 0.9f);
			glutSolidCube(4.5);
			glPopMatrix();

			glPushMatrix();//다리
			glTranslatef(160.0, 35.0, 297.0);
			glScalef(1.0, 20.0, 1.0);
			glColor3f(0.9f, 0.8f, 0.7f);
			glutSolidCube(4);
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();//몸통
		glTranslatef(155.0, 30.0, 300);
		glScalef(1.0, 3.0, 1.0);
		glRotated(-90, 1, 0, 0);
		glColor3f(0.9f, 0.3f, 0.3f);
		glutSolidCone(15, 20, 20, 20);
		glPopMatrix();

		glPushMatrix();//얼굴
		glTranslatef(155.0, 77.0, 300);
		glColor3f(0.9f, 0.8f, 0.7f);
		glutSolidSphere(14, 20, 20);
		glPopMatrix();

		glPushMatrix();//오른쪽 팔
		{
			glPushMatrix();//어깨
			glTranslatef(146.0, 60.0, 300);
			glColor3f(0.9f, 0.3f, 0.3f);
			glutSolidSphere(6, 15, 15);
			glPopMatrix();

			glPushMatrix();//팔
			glTranslatef(142.0, 45.0, 300);			
			glRotated(-15, 0, 0, 1);
			glScalef(1.0, 6.0, 1.0);
			glColor3f(0.9f, 0.8f, 0.7f);
			glutSolidCube(4);
			glPopMatrix();

			glPushMatrix();//손
			glTranslatef(141.0, 35.0, 300);
			glColor3f(0.9f, 0.8f, 0.7f);
			glutSolidSphere(5, 15, 15);
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();//왼쪽 팔
		{
			glPushMatrix();//어깨
			glTranslatef(164.0, 60.0, 300);
			glColor3f(0.9f, 0.3f, 0.3f);
			glutSolidSphere(6, 15, 15);
			glPopMatrix();

			glPushMatrix();//팔
			glTranslatef(168.0, 45.0, 300);			
			glRotated(15, 0, 0, 1);
			glScalef(1.0, 6.0, 1.0);
			glColor3f(0.9f, 0.8f, 0.7f);
			glutSolidCube(4);
			glPopMatrix();

			glPushMatrix();//손
			glTranslatef(169.0, 35.0, 300);
			glColor3f(0.9f, 0.8f, 0.7f);
			glutSolidSphere(5, 15, 15);
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();//모자
		glTranslatef(155.0, 83.0, 297);
		glRotated(-120, 1, 0, 0);
		glScalef(1.0, 1.0, 2.0);	
		glColor3f(0.9f, 0.3f, 0.3f);
		glutSolidCone(14, 20, 20, 20);
		glPopMatrix();

		glPushMatrix();//모자 방울
		glTranslatef(155.0, 115.0, 278);
		glColor3f(1.0f, 0.9f, 0.9f);
		glutSolidSphere(5, 20, 20);
		glPopMatrix();
	}
	glPopMatrix();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0f, w / h, 1.0, 1000.0); // 원근 거리
	glTranslatef(0.0, -30.0, -600.0);
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
	glTranslatef(Xmove, Ymove, Zmove);
	glRotated(xRotation, 1.0f, 0.0f, 0.0f);
	glRotated(yRotation, 0.0f, 1.0f, 0.0f);
	glRotated(zRotation, 0.0f, 0.0f, 1.0f);
	Loadfile();
	board_maker();
	snow();//눈

	// 나무
	drawTree(-280.0,120.0,-220.0);
	drawTree(160.0, 120.0, -120.0);
	drawTree(250.0, 120.0, 300.0);
	drawTree(-150.0, 120.0, 220.0);

	//돌
	drawStone(-200.0, 10.0, -300.0, 7);
	drawStone(-300.0, 10.0, 300.0, 0);
	drawStone(300.0, 10.0, 100.0, 7);
	drawStone(150.0, 10.0, 350.0, 0);

	//캐릭터
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
	case'X':
		xRotation -= 3.0f;
		break;
	case 'y':
		yRotation += 3.0f;
		break;
	case'Y':
		yRotation -= 3.0f;
		break;
	case 'z':
		zRotation += 3.0f;
		break;
	case 'Z':
		zRotation -= 3.0f;
		break;
	}
	glutPostRedisplay();
}

void KeyboardSpe(int key, int x, int y)//스페셜 키보드
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		Xmove -= 5;
		break;
	case GLUT_KEY_UP:
		Ymove -= 5;
		break;
	case GLUT_KEY_RIGHT:
		Xmove += 5;
		break;
	case GLUT_KEY_DOWN:
		Ymove += 5;
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
	glutSpecialFunc(KeyboardSpe);//키보드 스페셜
	glutDisplayFunc(drawScene);
	glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	SetupRC();//초기화
	glutMainLoop();

}