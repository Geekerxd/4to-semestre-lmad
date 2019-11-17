#include "GL/glut.h"
#include "Triangle.h"

void Triangle::Draw(int a)
{
	glPushMatrix();// Push-> inicia
	    glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT | GL_COLOR_MATERIAL);
	            glBegin(GL_TRIANGLES);
	            glColor3f(1, 0, 0);//rojo
	            glVertex3f(a, -a, 0);

	            glVertex3f(a, a , 0);

	            glVertex3f(2*a, 0, 0);
	        glEnd();
			//...
			glBegin(GL_TRIANGLES);
			glColor3f(0, 0, 1);//azul
			glVertex3f(a, 0, a);

			glVertex3f(-a, 0, a);

			glVertex3f(0, 0, 2*a);
			glEnd();
			//...
			glBegin(GL_TRIANGLES);
			glColor3f(0, 1, 0);//verde
			glVertex3f(a, a, 0);

			glVertex3f(-a, a, 0);

			glVertex3f(0, 2 * a,0);
			glEnd();
			//...
	    glPopAttrib();
	glPopMatrix();// Pop-> finaliza
}
