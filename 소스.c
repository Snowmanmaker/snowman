#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////
int snowNumber = 0;
float snowObejct[200][3];
int makeboard[80][80];
float xRotation = 0.0f, yRotation = 0.0f, zRotation = 0.0f;//로테이션
float Xmove = 0.0f, Ymove = 0.0f, Zmove = 0.0f;
int direct = 0;
float xPos = 0, zPos = -55;
float LeftArm = 0;
float RightArm = 0;
float Leg = 0;
int count = 0;
int count1 = 0;
int look = 0;
int m = 1;
int p = 1;
int r = 1;
int q = 0;
int t = 0;//space bar
int u = 0;
int kk = 0;
int g = 0;
float jump=0;
BOOL snowjump = FALSE;
BOOL move = FALSE;
BOOL makeSnow = FALSE;
BOOL camera = FALSE;
BOOL light = TRUE;
float ambientL = 0.6f;
float diffuseL = 0.2f;
float specularL = 0.6f;

typedef struct makeSnow
{
	float x;
	float y;
	float z;
	float size;
	int man;
	BOOL life;
};

struct makeSnow Snow[8];

typedef struct makeSnow1
{
	float x;
	float y;
	float z;
	float size;
	int man;
	int type;
	BOOL life;
};

struct makeSnow1 SnowMan[8];

void drawBitmapText(char *str, float x, float y, float z)
{
	glRasterPos3f(x, y, z); //문자열이 그려질 위치 지정

	while (*str)
	{
		//GLUT_BITMAP_TIMES_ROMAN_24 폰트를 사용하여 문자열을 그린다.
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str);

		str++;
	}
}

void TYPE()
{

	for (int i = 0; i < 8; i++)
	{
		if (i < 4)
		{
			SnowMan[i].type =i;
		}
		else if (i >= 4)
		{
			SnowMan[i].type = i-4;
		}
	}
}

void cloud(Cx,Cy,Cz)
{
	glPushMatrix();
	{
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(Cx,Cy,Cz );
		glutSolidSphere(55, 50, 50);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(Cx+35, Cy, Cz);
		glutSolidSphere(45, 50, 50);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(Cx - 35, Cy, Cz);
		glutSolidSphere(45, 50, 50);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(Cx - 65, Cy, Cz);
		glutSolidSphere(35, 50, 50);
	}
	glPopMatrix();

}
void Light()
{
	GLfloat AmbientLight[] = { ambientL, ambientL, ambientL, ambientL };//주변 조명
	GLfloat DiffuseLight[] = { diffuseL, diffuseL, diffuseL, diffuseL };//산란 반사 조명
	GLfloat SpecularLight[] = { specularL, specularL, specularL, specularL };//거울반사 조명
	GLfloat lightPos[] = { 230, 440, 300, 1 };
	GLfloat specref[] = { 1,1,1,1 };
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 64);

	if (light == TRUE)
	{
		glPushMatrix();
		{
			glColor3f(4, 4, 0);
			glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
			glutSolidSphere(10, 50, 50);
		}
		glPopMatrix();

		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);
	}
}

void santa(int k, int j)
{
	glPushMatrix();
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x, 25 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2+ SnowMan[j + 1].size, SnowMan[k].z-10);
	glColor3f(1.0f, 0.0f, 0.0f);
	glRotated(-120, 1, 0, 0);
	glScalef(1.0, 1.0, 2.0);
	glutSolidCone(5+SnowMan[j + 1].size, 20, 20, 20);
	glPopMatrix();

	glPushMatrix();//모자 방울
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x, 1.3*(27 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2+ SnowMan[j + 1].size), SnowMan[k].z-28);
	glColor3f(1.0f, 0.9f, 0.9f);
	glutSolidSphere((SnowMan[j + 1].size/3), 20, 20);
	glPopMatrix();

	glPushMatrix();//목도리
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x, 15 + SnowMan[k].y + SnowMan[k].size - 2+ 10 + SnowMan[k].size, SnowMan[k].z);
	glRotated(90, 1, 0, 0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidTorus(SnowMan[j + 1].size-5, SnowMan[j + 1].size-3, 20, 20);
	glPopMatrix();

	glPushMatrix();//왼쪽 눈
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x-((10 + SnowMan[j + 1].size)/2), 28 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2, SnowMan[k].z+ 6 + SnowMan[j + 1].size);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere((10 + SnowMan[k].size)/10, 20, 20);
	glPopMatrix();

	glPushMatrix();//오른쪽 눈
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x + ((10 + SnowMan[j + 1].size) / 2), 28 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2, SnowMan[k].z+ 6 + SnowMan[j + 1].size);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere((10 + SnowMan[k].size) / 10, 20, 20);
	glPopMatrix();

	glPushMatrix();//코
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x, 25 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2, SnowMan[k].z + 8 + SnowMan[j + 1].size+3);
	glColor3f(7.0f, 0.5f, 0.0f);
	glScalef(1.0, 1.0, 3.0);
	glutSolidCone(((20 + SnowMan[k].size) / 2) / 6, 4, 10, 10);
	glPopMatrix();
	
}

void bear(int k, int j)
{
	glPushMatrix();
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x-((10 + SnowMan[j + 1].size)/2), 28 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2+ 10 + SnowMan[j + 1].size, SnowMan[k].z);
	glColor3f(0.95f, 0.95f, 1.0f);
	glutSolidSphere((10 + SnowMan[k].size) / 3, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x + ((10 + SnowMan[j + 1].size) / 2), 28 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2 + 10 + SnowMan[j + 1].size, SnowMan[k].z);
	glColor3f(0.95f, 0.95f, 1.0f);
	glutSolidSphere((10 + SnowMan[k].size) / 3, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x-(10 + SnowMan[k].size/2), 15 + SnowMan[k].y + SnowMan[k].size - 2+ (10 + SnowMan[k].size / 2), SnowMan[k].z);
	glColor3f(0.95f, 0.95f, 1.0f);
	glutSolidSphere((10 + SnowMan[k].size) / 3, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x + (10 + SnowMan[k].size / 2), 15 + SnowMan[k].y + SnowMan[k].size - 2 + (10 + SnowMan[k].size / 2), SnowMan[k].z);
	glColor3f(0.95f, 0.95f, 1.0f);
	glutSolidSphere((10 + SnowMan[k].size) / 3, 20, 20);
	glPopMatrix();

	glPushMatrix();//왼쪽 눈
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x - ((10 + SnowMan[j + 1].size) / 2), 28 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2, SnowMan[k].z + 6 + SnowMan[j + 1].size);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere((10 + SnowMan[k].size) / 10, 20, 20);
	glPopMatrix();

	glPushMatrix();//오른쪽 눈
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x + ((10 + SnowMan[j + 1].size) / 2), 28 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2, SnowMan[k].z + 6 + SnowMan[j + 1].size);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere((10 + SnowMan[k].size) / 10, 20, 20);
	glPopMatrix();

	glPushMatrix();//코
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x , 25 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2, SnowMan[k].z + 8 + SnowMan[j + 1].size);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere((10 + SnowMan[k].size) / 8, 20, 20);
	glPopMatrix();
}

void fourtop(int k, int j)
{
	glPushMatrix();//대가리
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x, 28 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2+ 8 + SnowMan[j + 1].size+ ((10 + SnowMan[j + 1].size) / 2), SnowMan[k].z);
	glColor3f(0.95f, 0.95f, 1.0f);
	glutSolidSphere(((10 + SnowMan[j + 1].size)/2), 20, 20);
	glPopMatrix();

	glPushMatrix();//왼쪽 눈
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x - (((10 + SnowMan[j + 1].size) / 2) / 2), 28 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2 + 8 + SnowMan[j + 1].size + ((10 + SnowMan[j + 1].size) / 2), SnowMan[k].z + ((10 + SnowMan[j + 1].size) / 2)-2);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(((10 + SnowMan[k].size)/2) / 8, 20, 20);
	glPopMatrix();

	glPushMatrix();//오른쪽 눈
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x + (((10 + SnowMan[j + 1].size) / 2) / 2), 28 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2 + 8 + SnowMan[j + 1].size + ((10 + SnowMan[j + 1].size) / 2), SnowMan[k].z + ((10 + SnowMan[j + 1].size) / 2)-2);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(((10 + SnowMan[k].size) / 2) / 8, 20, 20);
	glPopMatrix();

	glPushMatrix();//코
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x, 28 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2 + 6 + SnowMan[j + 1].size + ((10 + SnowMan[j + 1].size) / 2), SnowMan[k].z + ((10 + SnowMan[j + 1].size) / 2) - 2);
	glColor3f(7.0f, 0.5f, 0.0f);
	glScalef(1.0, 1.0, 3.0);
	glutSolidCone(((10 + SnowMan[k].size) / 2)/6, 4, 10,10);
	glPopMatrix();
}

void teapotman(int k, int j)
{
	glPushMatrix();//왼쪽 눈
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x - ((10 + SnowMan[j + 1].size) / 2), 28 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2, SnowMan[k].z + 6 + SnowMan[j + 1].size);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere((10 + SnowMan[k].size) / 10, 20, 20);
	glPopMatrix();

	glPushMatrix();//오른쪽 눈
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x + ((10 + SnowMan[j + 1].size) / 2), 28 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2, SnowMan[k].z + 6 + SnowMan[j + 1].size);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere((10 + SnowMan[k].size) / 10, 20, 20);
	glPopMatrix();

	glPushMatrix();//대가리
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x, 32 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2 + 6 + SnowMan[j + 1].size + ((10 + SnowMan[j + 1].size) / 2), SnowMan[k].z);
	glColor3f(0.7f, 0.3f, 0.3f);
	glutSolidTeapot(((15 + SnowMan[j + 1].size) / 2));
	glPopMatrix();

	glPushMatrix();//코
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x, 25 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2, SnowMan[k].z + 8 + SnowMan[j + 1].size);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere((10 + SnowMan[k].size) / 8, 20, 20);
	glPopMatrix();
}

void SnowManPerfect(int k, int j)
{
	TYPE();
	if (SnowMan[k].type == 0)
	{
		santa(k, j);
	}
	else if (SnowMan[k].type == 1)
	{
		bear(k, j);
	}
	else if (SnowMan[k].type == 2)
	{
		fourtop(k, j);
	}
	else if (SnowMan[k].type == 3)
	{
		teapotman(k, j);
	}
	
	glPushMatrix();//몸통
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x, 15 + SnowMan[k].y + SnowMan[k].size - 2, SnowMan[k].z);
	glColor3f(0.95f, 0.95f, 1.0f);
	glutSolidSphere(10 + SnowMan[k].size, 20, 20);
	glPopMatrix();

	glPushMatrix();//대가리
	glTranslated(0, jump, 0);
	glTranslated(SnowMan[k].x, 28 + SnowMan[k].y + SnowMan[k].size + SnowMan[k].size + SnowMan[j + 1].size - 2, SnowMan[k].z);
	glColor3f(0.95f, 0.95f, 1.0f);
	glutSolidSphere(10 + SnowMan[j + 1].size, 20, 20);
	glPopMatrix();
}



void makeSnowman()
{
	for (int k = 0; k < 8; k++)
	{
		for (int j = k; j < 7; j++)
		{
			if (sqrt(((Snow[k].x-Snow[j+1].x)*(Snow[k].x - Snow[j + 1].x))+ ((Snow[k].z - Snow[j + 1].z)*(Snow[k].z - Snow[j + 1].z)))<=
				(10+Snow[k].size+10+Snow[j+1].size) && Snow[k].man != 1 && Snow[j + 1].man != 1)
			{
				if (Snow[k].size >= 3 && Snow[j + 1].size >= 3 && Snow[j + 1].man != 1 && Snow[k].man != 1)
				{
					

					SnowMan[k].x = Snow[k].x;
					SnowMan[k].y = Snow[k].y;
					SnowMan[k].z = Snow[k].z;
					SnowMan[k].size = Snow[k].size;

					SnowMan[j + 1].x = Snow[j + 1].x;
					SnowMan[j + 1].y = Snow[j + 1].y;
					SnowMan[j + 1].z = Snow[j + 1].z;
					SnowMan[j + 1].size = Snow[j + 1].size;

					Snow[k].life = FALSE;
					Snow[j + 1].life = FALSE;
					
					snowjump = TRUE;
					if (SnowMan[k].size > SnowMan[j + 1].size) {
						SnowMan[k].size = SnowMan[k].size;
					}
					else {
						float tmp;
						tmp = SnowMan[k].size;
						SnowMan[k].size = SnowMan[j + 1].size;
						SnowMan[j + 1].size = tmp;
					}
					SnowManPerfect(k, j);

					

					Snow[k].man = 1;
					Snow[j + 1].man = 1;
					
				}
				
			}
			else
			{
				Snow[k].man = 0;
				Snow[j + 1].man = 0;
			
			}
			
		}
		
	}
}



void snowballrand()
{
	for (int i = 0; i < 8; i++) {
		Snow[i].life = TRUE;
	}
	srand((unsigned)time(NULL));
	int k = 0;
	int sx = 0;
	int sz = 0;
	while (k != 8)
	{
		sx = (((rand() % 80) - 40) * 10);
		sz = (((rand() % 80) - 40) * 10);
		for (int i = 0; i < 80; i++)
		{
			for (int j = 0; j < 80; j++)
			{
				if (sx == -400 + 10 * j && sz == -400 + 10 * i && makeboard[i][j] != 2)
				{
					Snow[k].x = (float)sx;
					Snow[k].z = (float)sz;
					k++;
				}
			}
		}
	}

}

void snowball()
{
	for (int k = 0; k < 8; k++)
	{
		if (Snow[k].life == TRUE) {
			glPushMatrix();
			glTranslated(Snow[k].x, 15 + Snow[k].y, Snow[k].z);
			glColor3f(0.95f, 0.95f, 1.0f);
			glutSolidSphere(10 + Snow[k].size, 20, 20);
			glPopMatrix();
		}
	}
}

void SetupRC()//초기화
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // clear 색상을 검정색으로 설정
	srand((unsigned)time(NULL));
	for (int i = 0; i < 200; ++i)
	{
		snowObejct[i][0] = rand() % (500 - (-500) + 1) + (-500);//x값
		snowObejct[i][1] = rand() % 500;//y값
		snowObejct[i][2] = rand() % (500 - (-500) + 1) + (-500);//x값
	}
}



void checkSnow(float i, float j, int k)
{
	int x = (int)(j + 400) / 10;
	int z = (int)(i + 400) / 10;
	if (makeboard[x][z] == 0) {
		if (Snow[k].size <= 40) {
			Snow[k].size += 0.1;
			Snow[k].y += 0.05;
		}
		
	}
	if (makeboard[x][z] == 1) {
		Snow[k].size -= 0.1;
		
	}
	if (makeboard[x][z] == 2) {
		Snow[k].life = FALSE;
		
	}

}

void checkRiver()
{
	int x = (int)(zPos + 400) / 10;
	int z = (int)(xPos + 400) / 10;
	if (makeboard[x][z] == 0) {
		u = 0;
	}
	if (makeboard[x][z] == 1) {
		u = 0;
	}
	if (makeboard[x][z] == 2) {
		
		u = 1;
	}
	if (makeboard[x][z] == 3) {

		u = 0;
	}

}

void selectSnow()
{
	if (direct == 1)
	{
		Snow[kk].x = xPos;
		Snow[kk].z = zPos - 24 - Snow[kk].size;
	}
	else if (direct == 2)
	{
		Snow[kk].x = xPos + 24 + Snow[kk].size;
		Snow[kk].z = zPos;
	}
	else if (direct == 3)
	{
		Snow[kk].x = xPos - 24 - Snow[kk].size;
		Snow[kk].z = zPos;
	}
	else if (direct == 0)
	{
		Snow[kk].x = xPos;
		Snow[kk].z = zPos + 24 + Snow[kk].size;
	}

}


void followSnow()
{
	
		for (int k = 0; k < 8; k++)
		{
			if (Snow[k].x - 30.0 - Snow[k].size <= xPos && Snow[k].x + 30.0 + Snow[k].size >= xPos &&   //캐릭터가 눈덩이 범위안에 들어오면
				Snow[k].z - 30.0 - Snow[k].size <= zPos && Snow[k].z + 30.0 + Snow[k].size >= zPos)
			{
				if (makeSnow == TRUE && Snow[k].man != 1)
		        {
					kk = k;
					g = 1;
				}
			}
		}
	
	if (makeSnow == FALSE)
	{
		g = 0;
	}

}

void crash()
{
	for (int k = 0; k < 8; k++) {
		if ((-290 < xPos&&-270 > xPos&&-230 < zPos&&-210 > zPos) ||
			(150 < xPos && 170 > xPos&&-130 < zPos&&-110 > zPos) ||
			(240 < xPos && 260 > xPos && 290 < zPos && 310 > zPos) ||
			(-160 < xPos&&-140 > xPos && 210 < zPos && 230 > zPos) ||
			(-210 < xPos&&-190 > xPos&&-310 < zPos&&-290 > zPos) ||
			(-310 < xPos&&-290 > xPos && 290 < zPos && 310 > zPos) ||
			(290 < xPos && 310 > xPos && 90 < zPos && 110 > zPos) ||
			(140 < xPos && 160 > xPos && 340 < zPos && 360 > zPos)|| u==1) {			// 돌4

			if (direct == 0) {				
				zPos -= 1.5;
			}
			if (direct == 1) {
				zPos += 1.5;
			}
			if (direct == 2) {
				xPos -= 1.5;
			}
			if (direct == 3) {
				xPos += 1.5;
			}
		}
	}
}

void crashSnow()
{
	for (int k = 0; k < 8; k++)
	{
		if ((sqrt(((Snow[k].x + 280)*(Snow[k].x + 280)) + ((Snow[k].z + 220)*(Snow[k].z + 220))) <= (20 + Snow[k].size))||
			(sqrt(((Snow[k].x - 160)*(Snow[k].x - 160)) + ((Snow[k].z + 120)*(Snow[k].z + 120))) <= (20 + Snow[k].size))||
			(sqrt(((Snow[k].x - 250)*(Snow[k].x - 250)) + ((Snow[k].z - 300)*(Snow[k].z - 300))) <= (20 + Snow[k].size))||
			(sqrt(((Snow[k].x + 150)*(Snow[k].x + 150)) + ((Snow[k].z - 220)*(Snow[k].z - 220))) <= (20 + Snow[k].size))||
			(sqrt(((Snow[k].x + 200)*(Snow[k].x + 200)) + ((Snow[k].z + 300)*(Snow[k].z + 300))) <= (21 + Snow[k].size))||
			(sqrt(((Snow[k].x + 300)*(Snow[k].x + 300)) + ((Snow[k].z - 300)*(Snow[k].z - 300))) <= (17 + Snow[k].size))||
			(sqrt(((Snow[k].x - 300)*(Snow[k].x - 300)) + ((Snow[k].z - 100)*(Snow[k].z - 100))) <= (21 + Snow[k].size))||
			(sqrt(((Snow[k].x - 150)*(Snow[k].x - 150)) + ((Snow[k].z - 350)*(Snow[k].z - 350))) <= (17 + Snow[k].size)))
		{
			Snow[k].size = (Snow[k].size/2);
		}
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
		glutSolidSphere(2.5, 10, 10);
		glPopMatrix();
	}
}

void drop()
{
	for (int i = 0; i < 200; ++i)
	{
		snowObejct[i][1] -= 3.0;
	}
	for (int i = 0; i < 200; ++i)
	{
		if (snowObejct[i][1] < -50)
		{
			snowObejct[i][0] = rand() % (500 - (-500) + 1) + (-500);//x값
			snowObejct[i][1] = rand() % 500;//y값
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
					glTranslatef(-400.0 + 10 * j, -10.0, -400.0 + 10 * i);
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
	glTranslatef(Tx, Ty + 80, Tz);
	glutSolidSphere(8.0, 50, 24);
	glPopMatrix();


	// 기둥
	glPushMatrix();
	glColor3f(0.5f, 0.3f, 0.3f);
	glTranslatef(Tx, Ty - 65, Tz);
	glScalef(1.0, 5.5, 1.0);   // y축으로 12배
	glutSolidCube(20);
	glPopMatrix();

}

void drawStone(float Sx, float Sy, float Sz, float Ssize)//돌
{
	glPushMatrix();

	glTranslatef(Sx, Sy, Sz);
	glColor3f(0.5f, 0.5f, 0.5f);
	glutSolidCube(15 + Ssize);

	glTranslatef(0.0, 0.0 + 10.0 + Ssize, 0.0);
	glColor3f(0.4f, 0.4f, 0.4f);
	glutSolidCube(10 + Ssize);

	glTranslatef(0.0, 0.0 - 10.0, 0.0 + 10.0 + Ssize);
	glColor3f(0.55f, 0.55f, 0.55f);
	glutSolidCube(8 + Ssize);

	glPopMatrix();
}

void character()//캐릭터
{
	glPushMatrix();
	{
		glTranslatef(xPos, 0, zPos);
		if (direct == 2) {
			glRotatef(90, 0, 1, 0);
		}
		if (direct == 3) {
			glRotatef(-90, 0, 1, 0);
		}
		if (direct == 1) {
			glRotatef(-180, 0, 1, 0);
		}

		glPushMatrix();//오른쪽 발,다리
		{

			glPushMatrix();//발
			glTranslatef(-5.0, 37.0, -1.0);
			glRotated(Leg*(-1)*0.5, 1, 0, 0);
			glTranslatef(0.0f, -30.0f, 3.0f);
			glScalef(1.0, 1.3, 2.0);
			glColor3f(0.9f, 0.3f, 0.3f);
			glutSolidCube(5);
			glPopMatrix();

			glPushMatrix();//양말
			glTranslatef(-5.0, 35.0, -3.0);
			glRotated(Leg*(-1)*0.5, 1, 0, 0);
			glTranslatef(0.0f, -20.0f, 3.0f);
			glScalef(1.0, 2.0, 1.0);
			glColor3f(1.0f, 0.9f, 0.9f);
			glutSolidCube(4.5);
			glPopMatrix();

			glPushMatrix();//다리
			glTranslatef(-5.0, 33.0, -3.0);
			glRotated(Leg*(-1)*0.5, 1, 0, 0);
			glTranslatef(0.0f, -8.0f, 3.0f);
			glScalef(1.0, 4.0, 1.0);
			glColor3f(0.9f, 0.8f, 0.7f);
			glutSolidCube(4);
			glPopMatrix();


		}
		glPopMatrix();

		glPushMatrix();//왼쪽 발,다리
		{
			glPushMatrix();//발
			glTranslatef(5.0, 37.0, -1.0);
			glRotated(Leg*0.5, 1, 0, 0);
			glTranslatef(0.0f, -30.0f, 3.0f);
			glScalef(1.0, 1.3, 2.0);
			glColor3f(0.9f, 0.3f, 0.3f);
			glutSolidCube(5);
			glPopMatrix();

			glPushMatrix();//양말
			glTranslatef(5.0, 35.0, -3.0);
			glRotated(Leg*0.5, 1, 0, 0);
			glTranslatef(0.0f, -20.0f, 3.0f);
			glScalef(1.0, 2.0, 1.0);
			glColor3f(1.0f, 0.9f, 0.9f);
			glutSolidCube(4.5);
			glPopMatrix();

			glPushMatrix();//다리
			glTranslatef(5.0, 33.0, -3.0);
			glRotated(Leg*0.5, 1, 0, 0);
			glTranslatef(0.0f, -8.0f, 3.0f);
			glScalef(1.0, 4.0, 1.0);
			glColor3f(0.9f, 0.8f, 0.7f);
			glutSolidCube(4);
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();//몸통
		glTranslatef(0.0, 28.0, 0);
		glScalef(1.0, 3.0, 1.0);
		glRotated(-90, 1, 0, 0);
		glColor3f(0.9f, 0.3f, 0.3f);
		glutSolidCone(15, 20, 20, 20);
		glPopMatrix();

		glPushMatrix();//얼굴
		glTranslatef(0.0, 75.0, 0);
		glColor3f(0.9f, 0.8f, 0.7f);
		glutSolidSphere(14, 20, 20);
		glPopMatrix();

		glPushMatrix();//오른쪽 팔
		{

			glPushMatrix();//어깨
			glTranslatef(-9.0, 58.0, 0);
			glRotated(RightArm, 1, 0, 0);
			glTranslatef(0.0, 0.0, 0);
			glColor3f(0.9f, 0.3f, 0.3f);
			glutSolidSphere(6.5, 15, 15);
			glPopMatrix();

			glPushMatrix();//팔
			glTranslatef(-13.0, 53.0, 0);
			glRotated(RightArm, 1, 0, 0);
			glTranslatef(0.0, -10.0, 0);
			glRotated(-15, 0, 0, 1);
			glScalef(1.0, 4.5, 1.0);
			glColor3f(0.9f, 0.8f, 0.7f);
			glutSolidCube(4);
			glPopMatrix();

			glPushMatrix();//손
			glTranslatef(-14.0, 50.0, 0);
			glRotated(RightArm, 1, 0, 0);
			glTranslatef(0.0, -20, 0);
			glColor3f(0.9f, 0.8f, 0.7f);
			glutSolidSphere(5, 15, 15);
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();//왼쪽 팔
		{
			glPushMatrix();//어깨
			glTranslatef(9.0, 58.0, 0);
			glRotated(LeftArm, 1, 0, 0);
			glTranslatef(0.0, 0.0, 0);
			glColor3f(0.9f, 0.3f, 0.3f);
			glutSolidSphere(6.5, 15, 15);
			glPopMatrix();

			glPushMatrix();//팔
			glTranslatef(13.0, 53.0, 0);
			glRotated(LeftArm, 1, 0, 0);
			glTranslatef(0.0, -10.0, 0);
			glRotated(15, 0, 0, 1);
			glScalef(1.0, 4.5, 1.0);
			glColor3f(0.9f, 0.8f, 0.7f);
			glutSolidCube(4);
			glPopMatrix();

			glPushMatrix();//손
			glTranslatef(14.0, 50.0, 0);
			glRotated(LeftArm, 1, 0, 0);
			glTranslatef(0.0, -20.0, 0);
			glColor3f(0.9f, 0.8f, 0.7f);
			glutSolidSphere(5, 15, 15);
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();//모자
		glTranslatef(0.0, 81.0, -3);
		glRotated(-120, 1, 0, 0);
		glScalef(1.0, 1.0, 2.0);
		glColor3f(0.9f, 0.3f, 0.3f);
		glutSolidCone(14, 20, 20, 20);
		glPopMatrix();

		glPushMatrix();//모자 방울
		glTranslatef(0.0, 113.0, -20);
		glColor3f(1.0f, 0.9f, 0.9f);
		glutSolidSphere(5, 20, 20);
		glPopMatrix();
	}
	glPopMatrix();
}


void shake()
{
	//왼쪽팔
	if (LeftArm <= 50 && p == 1) {
		LeftArm += 12.5;
		if (LeftArm == 50) {
			p = 0;
		}
	}
	if (LeftArm <= 50 && p == 0) {
		LeftArm -= 12.5;
		if (LeftArm == -50) {
			p = 1;
		}
	}

	//오른쪽팔
	if (RightArm <= 50 && r == 1) {
		RightArm -= 12.5;
		if (RightArm == -50) {
			r = 0;
		}
	}
	if (RightArm <= 50 && r == 0) {
		RightArm += 12.5;
		if (RightArm == 50) {
			r = 1;
		}
	}

	if (Leg <= 50 && q == 1) {
		Leg += 12.5;
		if (Leg == 50) {
			q = 0;
		}
	}
	if (Leg <= 50 && q == 0) {
		Leg -= 12.5;
		if (Leg == -50) {
			q = 1;
		}
	}

}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0f, w / h, 1.0, 1000.0); // 원근 거리
	if (camera == FALSE) {
		glTranslatef(0.0, -30.0, -600.0);
	}
	if (camera == TRUE) {
		glTranslatef(0.0, -80.0, -350.0);
	}

	glRotatef(40, 1.0f, 0.0f, 0.0f);

	glMatrixMode(GL_MODELVIEW);

}

void TimerFunction(int value)
{
	drop();
	if (move == TRUE) {
		shake();

		move = FALSE;
	}

	else if (move == FALSE) {
		LeftArm = 0;
		RightArm = 0;
		Leg = 0;
	}

	if (makeSnow == TRUE) {
		LeftArm = -60;
		RightArm = -60;

	}

	if (snowjump == TRUE) {
		if (jump <= 20 && m == 1) {
			jump += 4;			
			if (jump == 20)
				m = 0;
		}
		if (jump <= 20 && m == 0) {
			jump -= 4;
			if (jump == -4)
				m = 1;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void drawScene()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.6f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	if (camera == TRUE) {
		gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0); // 카메라위치
		glTranslatef(-xPos, 0, -zPos);
		drawBitmapText("HI", 0.0, 0.0, 150.0);// 지정한 좌표에 문자열 출력
	}

	glPushMatrix();
	glTranslatef(Xmove, Ymove, Zmove);
	glRotated(xRotation, 1.0f, 0.0f, 0.0f);
	glRotated(yRotation, 0.0f, 1.0f, 0.0f);
	glRotated(zRotation, 0.0f, 0.0f, 1.0f);
	Loadfile();
	board_maker();
	snow();//눈
	// 나무
	drawTree(-280.0, 120.0, -220.0);
	drawTree(160.0, 120.0, -120.0);
	drawTree(250.0, 120.0, 300.0);
	drawTree(-150.0, 120.0, 220.0);

	//돌
	drawStone(-200.0, 10.0, -300.0, 7);
	drawStone(-300.0, 10.0, 300.0, 0);
	drawStone(300.0, 10.0, 100.0, 7);
	drawStone(150.0, 10.0, 350.0, 0);

	cloud(100, 500, -500);

	cloud(-300, 400, -500);

	//캐릭터
	character();
	snowball();
	followSnow();
	checkRiver();
	Light();
	crash();
	crashSnow();
	if (g == 1)
   {
      selectSnow();
      checkSnow(Snow[kk].x, Snow[kk].z, kk);  //땅 체크 후 크기 키우자
   }
	makeSnowman();
	glPopMatrix();

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
	case 'c':
		if (look % 2 == 0) {
			camera = TRUE;
		}
		if (look % 2 == 1) {
			camera = FALSE;
		}
		break;

	case VK_SPACE:
		if (count % 2 == 0) {
			makeSnow = TRUE;
		}
		if (count % 2 == 1) {
			makeSnow = FALSE;
		}
		break;
	}
	count++;
	if (count == 10) {
		count = 0;
	}
	look++;
	if (look == 10) {
		look = 0;
	}
	Reshape(1200, 700);
	glutPostRedisplay();
}

void KeyboardSpe(int key, int x, int y)//스페셜 키보드
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		move = TRUE;
		direct = 3;
		xPos -= 2.0;
		
		break;

	case GLUT_KEY_UP:
		move = TRUE;
		direct = 1;

		zPos -= 2.0;
	
		break;
	case GLUT_KEY_RIGHT:
		move = TRUE;
		direct = 2;
	
		xPos += 2.0;
		
		break;
	case GLUT_KEY_DOWN:
		move = TRUE;
		direct = 0;
		zPos += 2.0;
		
		break;

	}
	glutPostRedisplay();
}

void main(int argc, char *argv[])
{
	Loadfile();
	snowballrand();
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