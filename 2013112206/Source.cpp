#include <stdlib.h>
#include <gl/glut.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <time.h>
using std::vector;
using std::cin;
using std::cout;
using std::string;


	vector<int> fx;
	vector<int> fy;
	vector<int> fx1;
	vector<int> fy1;
	vector<int> R;
	vector<int> G;
	vector<int> B;

	int q = 0; //�̰͵� ���� 

int Width = 800, Height = 600; //ũ�� ����

int count = 0; //ù��° Ŭ���ΰ� �ƴѰ�(�׸��� �������� ����)


int lastc = 0; //������ ��Ŭ��ī���ÿ�

int ix; //Ŭ������ ���� ���콺�� ��ġ
int iy; //Ŭ������ ���� ���콺�� ��ġ

int k = 0;
struct Point2D
{
	int x;
	int y;
};

struct Polygon
{
	vector<Point2D> Pts;
	double color[3];
	vector<int> point; // �������� ��ġ�� ���� ��� Ŭ���߳�?

	
};

vector<Polygon> PolyList;
Polygon tmpPolygon;

void MouseFunc(int button, int state, int x, int y)
{


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && count == 1) //������ �� ����
	{
		Point2D xy;
		xy.x = x;
		xy.y = y;
		tmpPolygon.Pts.push_back(xy);
		//ī��Ʈ�� �������ϰ��� 0���� �������.
		count = 2;
		
		tmpPolygon.point.push_back(1); // �������� ��ġ�� ���� ��� Ŭ���߳�? 1�̶�� ���� ���� �ǹ̾���
		PolyList.push_back(tmpPolygon);
		glutPostRedisplay();
	}
	
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) //ó�� �� ����
	
	
	{
		if (x <= 50 && y <= 50 && y >= 0) //������ �׸� ����Ŭ��
		{
			tmpPolygon.color[0] = 255;
			tmpPolygon.color[1] = 0;
			tmpPolygon.color[2] = 0;
			
			


		}
		else if (x >= 50 && x <= 100 && y <= 50 && y >= 0) //�ʷϻ� �׸� ����Ŭ��
		{
			tmpPolygon.color[0] = 0;
			tmpPolygon.color[1] = 255;
			tmpPolygon.color[2] = 0;
			

		}
		else if (x >= 100 && x <= 150 && y <= 50 && y >= 0) //�Ķ��� �׸� ����Ŭ��
		{
			tmpPolygon.color[0] = 0;
			tmpPolygon.color[1] = 0;
			tmpPolygon.color[2] = 255;
			

		}
		else
		{
			Point2D xy;
			xy.x=x;
			xy.y=y;
			tmpPolygon.Pts.push_back(xy);
			count = 1;
		
			tmpPolygon.point.push_back(1);
			glutPostRedisplay();
		}
	}
}

void MouseMove(int x, int y)
{
	ix = x; //Ŭ������ ���� x��
	iy = y; //Ŭ������ ���� y��
	
	glutPostRedisplay();
}

void SetUpViewTransform()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, 0.0);
}

void SetupViewVolume()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -100.0, 100.0);
}

void Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetUpViewTransform();

	SetupViewVolume();

	glMatrixMode(GL_MODELVIEW);

	// darw
	glBegin(GL_POLYGON); //������ �׸�
	glColor3ub(255, 0, 0);
	glVertex3f(0, Height, 0.0);
	glVertex3f(0, Height - 50, 0.0);
	glVertex3f(50, Height - 50, 0.0);
	glVertex3f(50, Height, 0.0);
	glEnd();
	glBegin(GL_POLYGON); //�ʷϻ� �׸�
	glColor3ub(0, 255, 0);
	glVertex3f(50, Height, 0.0);
	glVertex3f(50, Height - 50, 0.0);
	glVertex3f(100, Height - 50, 0.0);
	glVertex3f(100, Height, 0.0);
	glEnd();
	glBegin(GL_POLYGON); //�Ķ��� �׸�
	glColor3ub(0, 0, 255);
	glVertex3f(100, Height, 0.0);
	glVertex3f(100, Height - 50, 0.0);
	glVertex3f(150, Height - 50, 0.0);
	glVertex3f(150, Height, 0.0);
	glEnd();

	if (k > 0)    // �׸� �����    ������ ���� ���� �־�� ���� �׷����� ���� �� ���� ����Ƿ� ���� ���� ��ġ
	{
		for (int i = 0; i < k; i++)
		{

			glColor3ub(PolyList[i].color[0], PolyList[i].color[1], PolyList[i].color[2]);
			glBegin(GL_POLYGON);
			for (int q = 0; q < PolyList[i].point.size(); q++)
			{
				glVertex3f(PolyList[i].Pts[q].x, Height - PolyList[i].Pts[q].y, 0);
			}
			glEnd();

		}
	}


	if (count == 2) //������ �� ���������� Ŭ��
	{
		glColor3ub(tmpPolygon.color[0], tmpPolygon.color[1], tmpPolygon.color[2]);

		glBegin(GL_POLYGON);
		for (int i = 0; i < tmpPolygon.point.size(); i++)
		{
			glVertex3f(tmpPolygon.Pts[i].x, Height - tmpPolygon.Pts[i].y, 0);
		}
		glEnd();
		tmpPolygon.Pts.clear(); //������ �� ��������� �ʱ�ȭ ������� (�׷��ִ� for������ �ʱ�ȭ���ָ� ����ʱ�ȭ�Ǽ� �ȳ�Ÿ��)
		tmpPolygon.point.clear();
		tmpPolygon.color[0] = (0, 0, 0);
		tmpPolygon.color[1] = (0, 0, 0);
		tmpPolygon.color[2] = (0, 0, 0);
		count = 0;
		k++; // �ϼ� Ƚ�� ++
		

	}

	else if (count == 1) //�������� Ŭ�� �� Ŭ������ ���� �ٰ����׸���
	{
		glColor3ub(tmpPolygon.color[0], tmpPolygon.color[1], tmpPolygon.color[2]);
		glBegin(GL_POLYGON);
		for (int i = 0; i < tmpPolygon.point.size(); i++)
		{
			glVertex3f(tmpPolygon.Pts[i].x, Height - tmpPolygon.Pts[i].y, 0); //�������� �� ����
		}
		glVertex3f(ix, Height - iy, 0);

		glEnd();
	}

	
	glutSwapBuffers();

}


int main(int argc, char **argv)
{
	
	
	glutInit(&argc, argv);
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutCreateWindow("����");

	glutDisplayFunc(Render);

	glutPassiveMotionFunc(MouseMove);

	glutMouseFunc(MouseFunc);

	glutMainLoop();

	return 0;
}
