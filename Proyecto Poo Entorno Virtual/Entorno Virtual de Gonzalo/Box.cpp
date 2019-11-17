#include "Box.h"

Box::Box(double boxSize):boxSize(boxSize)
{
}

void Box::Draw()
{
	glPushMatrix();
	    glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT | GL_COLOR_MATERIAL);
	        glTranslated(20, 0 , 0);
	        glScaled(this->boxSize, this->boxSize, this->boxSize);
	        glBegin(GL_QUADS);
	            glColor3f(0.5, 0.5, 0.5);
	            glVertex3f(-1.0f, -1.0f, 1.0f);
	            glVertex3f(1.0f, -1.0f, 1.0f);
	            glVertex3f(1.0f, 1.0f, 1.0f);
	            glVertex3f(-1.0f, 1.0f, 1.0f);
	            
	            glVertex3f(-1.0f, -1.0f, -1.0f);
	            glVertex3f(-1.0f, 1.0f, -1.0f);
	            glVertex3f(1.0f, 1.0f, -1.0f);
	            glVertex3f(1.0f, -1.0f, -1.0f);
	            
	            glVertex3f(-1.0f, 1.0f, -1.0f);
	            glVertex3f(-1.0f, 1.0f, 1.0f);
	            glVertex3f(1.0f, 1.0f, 1.0f);
	            glVertex3f(1.0f, 1.0f, -1.0f);
	            
	            glVertex3f(-1.0f, -1.0f, -1.0f);
	            glVertex3f(1.0f, -1.0f, -1.0f);
	            glVertex3f(1.0f, -1.0f, 1.0f);
	            glVertex3f(-1.0f, -1.0f, 1.0f);
	            
	            glVertex3f(1.0f, -1.0f, -1.0f);
	            glVertex3f(1.0f, 1.0f, -1.0f);
	            glVertex3f(1.0f, 1.0f, 1.0f);
	            glVertex3f(1.0f, -1.0f, 1.0f);
	            
	            glVertex3f(-1.0f, -1.0f, -1.0f);
	            glVertex3f(-1.0f, -1.0f, 1.0f);
	            glVertex3f(-1.0f, 1.0f, 1.0f);
	            glVertex3f(-1.0f, 1.0f, -1.0f);
	        glEnd();
	    glPopAttrib();
	glPopMatrix();
}
