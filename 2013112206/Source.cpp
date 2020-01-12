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

	int q = 0; //이것도 뭐지 

int Width = 800, Height = 600; //크기 만듬

int count = 0; //첫번째 클릭인가 아닌가(그리기 시작함을 뜻함)


int lastc = 0; //마지막 점클릭카운팅용

int ix; //클릭하지 않은 마우스의 위치
int iy; //클릭하지 않은 마우스의 위치

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
	vector<int> point; // 정상적인 위치의 점을 몇번 클릭했나?

	
};

vector<Polygon> PolyList;
Polygon tmpPolygon;

void MouseFunc(int button, int state, int x, int y)
{


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && count == 1) //마지막 점 연결
	{
		Point2D xy;
		xy.x = x;
		xy.y = y;
		tmpPolygon.Pts.push_back(xy);
		//카운트는 렌더링하고나서 0으로 만들어줌.
		count = 2;
		
		tmpPolygon.point.push_back(1); // 정상적인 위치의 점을 몇번 클릭했나? 1이라는 값은 별로 의미없음
		PolyList.push_back(tmpPolygon);
		glutPostRedisplay();
	}
	
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) //처음 점 선택
	
	
	{
		if (x <= 50 && y <= 50 && y >= 0) //빨강색 네모 왼쪽클릭
		{
			tmpPolygon.color[0] = 255;
			tmpPolygon.color[1] = 0;
			tmpPolygon.color[2] = 0;
			
			


		}
		else if (x >= 50 && x <= 100 && y <= 50 && y >= 0) //초록색 네모 왼쪽클릭
		{
			tmpPolygon.color[0] = 0;
			tmpPolygon.color[1] = 255;
			tmpPolygon.color[2] = 0;
			

		}
		else if (x >= 100 && x <= 150 && y <= 50 && y >= 0) //파랑색 네모 왼쪽클릭
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
	ix = x; //클릭하지 않은 x값
	iy = y; //클릭하지 않은 y값
	
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
	glBegin(GL_POLYGON); //빨간색 네모
	glColor3ub(255, 0, 0);
	glVertex3f(0, Height, 0.0);
	glVertex3f(0, Height - 50, 0.0);
	glVertex3f(50, Height - 50, 0.0);
	glVertex3f(50, Height, 0.0);
	glEnd();
	glBegin(GL_POLYGON); //초록색 네모
	glColor3ub(0, 255, 0);
	glVertex3f(50, Height, 0.0);
	glVertex3f(50, Height - 50, 0.0);
	glVertex3f(100, Height - 50, 0.0);
	glVertex3f(100, Height, 0.0);
	glEnd();
	glBegin(GL_POLYGON); //파랑색 네모
	glColor3ub(0, 0, 255);
	glVertex3f(100, Height, 0.0);
	glVertex3f(100, Height - 50, 0.0);
	glVertex3f(150, Height - 50, 0.0);
	glVertex3f(150, Height, 0.0);
	glEnd();

	if (k > 0)    // 그림 남기기    렌더링 가장 위에 있어야 현재 그려지는 선이 그 위에 생기므로 가장 위에 위치
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


	if (count == 2) //마지막 점 오른쪽으로 클릭
	{
		glColor3ub(tmpPolygon.color[0], tmpPolygon.color[1], tmpPolygon.color[2]);

		glBegin(GL_POLYGON);
		for (int i = 0; i < tmpPolygon.point.size(); i++)
		{
			glVertex3f(tmpPolygon.Pts[i].x, Height - tmpPolygon.Pts[i].y, 0);
		}
		glEnd();
		tmpPolygon.Pts.clear(); //마지막 점 을찍었을때 초기화 해줘야함 (그려주는 for문에서 초기화해주면 계속초기화되서 안나타남)
		tmpPolygon.point.clear();
		tmpPolygon.color[0] = (0, 0, 0);
		tmpPolygon.color[1] = (0, 0, 0);
		tmpPolygon.color[2] = (0, 0, 0);
		count = 0;
		k++; // 완성 횟수 ++
		

	}

	else if (count == 1) //왼쪽으로 클릭 중 클릭하지 않은 다각형그리기
	{
		glColor3ub(tmpPolygon.color[0], tmpPolygon.color[1], tmpPolygon.color[2]);
		glBegin(GL_POLYGON);
		for (int i = 0; i < tmpPolygon.point.size(); i++)
		{
			glVertex3f(tmpPolygon.Pts[i].x, Height - tmpPolygon.Pts[i].y, 0); //순간적인 점 생성
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

	glutCreateWindow("문제");

	glutDisplayFunc(Render);

	glutPassiveMotionFunc(MouseMove);

	glutMouseFunc(MouseFunc);

	glutMainLoop();

	return 0;
}
