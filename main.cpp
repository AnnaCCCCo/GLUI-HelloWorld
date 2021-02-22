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

/****************************��Ⱦ����***********************************/
void SceneRendering(void)
{
	//�����ɫ��������������ɫ����ΪClearColor
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//�ı���ɫֵ
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

	//��Ⱦ�ı���
	glBegin(GL_POLYGON);
	//������ɫ/����λ��
	glColor3f(red, green, blue);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	//ǿ��ˢ�»��壬��֤��ͼ���ִ��
	//glFlush();

	//˫����
	glutSwapBuffers();
}
/****************************���ִ��ڱ�������***********************************/
void myGlutReshape(int w, int h)
{
	// ��ֹ�������߶�Ϊ0
	// (��������ô��ڿ��Ϊ0).
	if (h == 0)
		h = 1;

	float ratio = 1.0 * w / h;

	// ��λ��ͶӰ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//���뵥λ����

	// �����ӿڴ�СΪ�������ڴ�С
	glViewport(0, 0, w, h);

	// ������ȷ��ͶӰ����
	gluPerspective(45, ratio, 1, 1000);//��߱�����Ϊ��ǰֵ��������������Ļ��Сһ��
	//����ģ����ͼ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f); //�۲���λ��
}
/****************************GLUI�ص�����***********************************/
void myGlutIdle(void)
{
	//�ж��Ƿ�Ϊ��ǰ����
	if (glutGetWindow() != main_window)
		glutSetWindow(main_window);

	//glutPostRedisplay ��ǵ�ǰ������Ҫ���»���
	glutPostRedisplay();
}

//������
int main(int argc, char** argv)
{
	//��ʼ��glut
	glutInit(&argc, argv);

	//������ʾģʽ
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	//�趨����λ�����С
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1080, 720);

	//��������
	main_window = glutCreateWindow("Renderer");
	//�ص���Ⱦ����
	glutDisplayFunc(SceneRendering);
	//�ı䴰�ڴ�Сʱ���������ڱ���
	glutReshapeFunc(myGlutReshape);


	/***************************GLUI CODE*******************************/
	//GLUI�汾��
	float version = GLUI_Master.get_version();

	//�����µ�UI����
	GLUI* glui_window = GLUI_Master.create_glui("GLUI");
	//glui_window->add_statictext("Hello World!");   //����һ���ַ���

	//����Checkbox/Spinner
	new GLUI_Checkbox(glui_window, "ChangeRed", &changeRed);
	(new GLUI_Spinner(glui_window, "RedChannelValue:", &redChannelValue))
		->set_int_limits(0, 1);

	new GLUI_Checkbox(glui_window, "ChangeGreen", &changeGreeen);
	(new GLUI_Spinner(glui_window, "GreenChannelValue:", &greenChannelValue))
		->set_int_limits(0, 1);

	new GLUI_Checkbox(glui_window, "ChangeBlue", &changeBlue);
	(new GLUI_Spinner(glui_window, "BlueChannelValue:", &blueChannelValue))
		->set_int_limits(0, 1);

	//GLUI�ص�����
	GLUI_Master.set_glutIdleFunc(myGlutIdle);

	//ѭ��ִ��
	glutMainLoop();
}
