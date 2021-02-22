#include <gl/glut.h>
#include<gl/gl.h>
#include<gl/GLU.h>

#include <string.h>
#include <GL/glui.h>

/**************************ID*******************************/
float red = 1.0;
float green = 1.0;
float blue = 1.0;

int   changeRed;
int   changeGreeen;
int   changeBlue;

float redChannelValue;
float greenChannelValue;
float blueChannelValue;

int main_window;

/****************************渲染函数***********************************/
void SceneRendering(void)
{
	//清除颜色缓冲区，并将颜色设置为ClearColor
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//改变颜色值
	if (changeRed)
	{
		red = redChannelValue;
	}

	if (changeGreeen)
	{
		green = greenChannelValue;
	}

	if (changeBlue)
	{
		blue = blueChannelValue;
	}

	//渲染四边形
	glBegin(GL_POLYGON);
	//顶点颜色/顶点位置
	glColor3f(red, green, blue);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	//强制刷新缓冲，保证绘图命令被执行
	//glFlush();

	//双缓冲
	glutSwapBuffers();
}
/****************************保持窗口比例函数***********************************/
void myGlutReshape(int w, int h)
{
	// 防止除数即高度为0
	// (你可以设置窗口宽度为0).
	if (h == 0)
		h = 1;

	float ratio = 1.0 * w / h;

	// 单位化投影矩阵。
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//导入单位矩阵

	// 设置视口大小为增个窗口大小
	glViewport(0, 0, w, h);

	// 设置正确的投影矩阵
	gluPerspective(45, ratio, 1, 1000);//宽高比例改为当前值，视线区域与屏幕大小一致
	//设置模型视图矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f); //观察者位置
}
/****************************GLUI回调函数***********************************/
void myGlutIdle(void)
{
	//判断是否为当前窗口
	if (glutGetWindow() != main_window)
		glutSetWindow(main_window);

	//glutPostRedisplay 标记当前窗口需要重新绘制
	glutPostRedisplay();
}

//主函数
int main(int argc, char** argv)
{
	//初始化glut
	glutInit(&argc, argv);

	//设置显示模式
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	//设定窗口位置与大小
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1080, 720);

	//创建窗口
	main_window = glutCreateWindow("Renderer");
	//回调渲染函数
	glutDisplayFunc(SceneRendering);
	//改变窗口大小时，保留窗口比例
	glutReshapeFunc(myGlutReshape);


	/***************************GLUI CODE*******************************/
	//GLUI版本号
	float version = GLUI_Master.get_version();

	//创建新的UI窗口
	GLUI* glui_window = GLUI_Master.create_glui("GLUI");
	//glui_window->add_statictext("Hello World!");   //输入一行字符串

	//创建Checkbox/Spinner
	new GLUI_Checkbox(glui_window, "ChangeRed", &changeRed);
	(new GLUI_Spinner(glui_window, "RedChannelValue:", &redChannelValue))
		->set_int_limits(0, 1);

	new GLUI_Checkbox(glui_window, "ChangeGreen", &changeGreeen);
	(new GLUI_Spinner(glui_window, "GreenChannelValue:", &greenChannelValue))
		->set_int_limits(0, 1);

	new GLUI_Checkbox(glui_window, "ChangeBlue", &changeBlue);
	(new GLUI_Spinner(glui_window, "BlueChannelValue:", &blueChannelValue))
		->set_int_limits(0, 1);

	//GLUI回调函数
	GLUI_Master.set_glutIdleFunc(myGlutIdle);

	//循环执行
	glutMainLoop();
}
