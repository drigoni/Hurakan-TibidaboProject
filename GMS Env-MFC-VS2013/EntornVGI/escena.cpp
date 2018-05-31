//******** PRACTICAL WORK GRAPHICAL & MULTIMEDIA SYSTEMS (Engineering School - UAB)
//******** Basic Environment VS2013 MULTIWINDOW with MFC interface and Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Julià, Débora Gil, Enric Martí (February 2018)
// escena.cpp : Here we define the code of the functions to draw objects and scenes using 
//                 OpenGL drawing commands. 


#include "stdafx.h"
#include "material.h"
#include "escena.h"


// FOrmula  to find angle considering radius 
GLfloat legSizeX = 2.5, legSizeY = 1, legSizeZ = 12;
GLfloat armSizeX = 1, armSizeY = 1, armSizeZ = 20;
GLfloat seatSizeX = 3, seatSizeY = 16, seatSizeZ = 1.5;
GLfloat offset = 0.5;
GLfloat angleArm = 0.0f, angleSeat = 0.0f, hurakanSize = 10.0f;
GLfloat radiusSky = 1000.0f;

float accelTime = 10.0f;
float hurakanRadius = 12.0f;
float hurakanIUPower = 0.0f;
float hurakanLAccel = 0.0f;
float maxhurakanASpeed = 0.0f;
float radtodeg = 360.0f / (float)TWOPI;
float maxTurns = 0.0f;
float velIncrement = 0.0f;
float ang1Increment = 0.0f;
float ang1AccelIncrement = 0.0f;
float hurakanASpeed = 0.0f;
float oldASpeed = 0.0f;
float accelTurns = 0.0f;
int NTurns = 0;
int Turn = 0;
int i = 0;


// TEXTURES: Vector texture names
GLuint texturID[NUM_MAX_TEXTURES] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

// dibuixa_EscenaGL: To draw a scene with OpenGL commands
void dibuixa_EscenaGL(char objecte, CColor col_object, bool ref_mat, bool sw_mat[4], bool textur)
{
	float altfar = 0;

	switch (objecte)
	{
// Hurakan drawing
	case HURAKAN:
		hurakan(textur, texturID);
		break;

// Truck drawing
	case TRUCK:
		glDisable(GL_TEXTURE_2D);
		sea();
		truck(textur, texturID);
		break;

// To draw 3DS object
	case OBJ3DS:
		// Definition of reflexion properties (emission, ambient, diffuse, specular) of materials.
		SeleccionaColor(ref_mat, sw_mat, col_object);
		// To draw the 3DS object with textures (OBJECTE3DST) or without it (OBJECTE3DS)
		if (textur) glCallList(OBJECTE3DST);
			else glCallList(OBJECTE3DS);
		break;

// To draw OBJ object
	case OBJOBJ:
		// Definition of reflexion properties (emission, ambient, diffuse, specular) of materials.
		SeleccionaColor(ref_mat, sw_mat, col_object);
		// OBJ Object: To draw the OBJ object.
		glCallList(OBJECTEOBJ);
		break;

// To draw other objects
	default:
		// Definition of reflexion properties (emission, ambient, diffuse, specular) of materials.
		SeleccionaColor(ref_mat, sw_mat, col_object);
		dibuixa(objecte);
		break;
	}

// To send graphic commads to screen (OpenGL deprecated command)
	glFlush();

}


// dibuixa: This functions draws simple objects defined in GLUT library (glutSolid*()), accrding to obj parameter.
void dibuixa(char obj)
{
	switch(obj)
	{

// Cube
	case CUBE:
//		glColor3f(1.0,1.0,1.0);
		glPushMatrix();
		  glScalef(5.0f,5.0f,5.0f);
		  glutSolidCube(1.0);
		glPopMatrix();
		break;

// Sphere
	case SPHERE:
//		glColor3f(1.0,1.0,1.0);	
		glPushMatrix();
		  glScalef(5.0f,5.0f,5.0f);
		  //glutSolidSphere(1.0,40,40);
		  gluEsfera(1.0, 40, 40);
		glPopMatrix();
		break;

// Teapot
	case TEAPOT:
//		glColor3f(1.0,1.0,1.0);
		glPushMatrix();
		  glScalef(5.0f,5.0f,5.0f);
		  glutSolidTeapot(0.5);
		glPopMatrix();
		break;

	}

}


// OBJECTE Truck with texture images if tectxture is switched on
// Truck: Parameters:
//    - textu: Flag of textures switxhed on/off.
//    - VTextu: Image texture vector.
void truck(bool textu,GLuint VTextu[NUM_MAX_TEXTURES])
{

glPushMatrix();
  glTranslatef(0.0f,0.0f,20.0f);

 // ENGINE
 // Carrosseria texture
	if (textu)  
		{	GLfloat sPlane[4] = { 0.05f, 0.0f, 0.00f, 0.250f };
		  	GLfloat tPlane[4] = { 0.00f, 0.05f, 0.1f, 0.00f };
// Switch on planxa texture
			glBindTexture(GL_TEXTURE_2D,VTextu[5]) ;
			glEnable(GL_TEXTURE_2D);
			glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
			
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);

		}

// Color carrosseria without texture
	glColor4f(0.5f,0.7f,1.0f,0.5f); 

	glPushMatrix();		
		glScalef(2.0f, 4.4f, 2.0f);
		glutSolidCube(10.0f);
	glPopMatrix();

// CABIN
// Lower cabin
	glPushMatrix();
		glTranslatef(0.0f,32.0f,0.0f);
		glScalef(4.0f, 2.0f, 2.0f);
		glutSolidCube(10.0f);
	glPopMatrix();

// Upper cabin
	glPushMatrix();
		glTranslatef(0.0f,32.0f,15.0f);
		glScalef(2.0f, 2.0f, 1.0f);
		glutSolidCube(10.0f);
	glPopMatrix();

// Rear cabin
	glPushMatrix();
		glTranslatef(0.0f,49.5f,12.5f);
		glScalef(4.0f, 1.5f, 4.5f);
		glutSolidCube(10.0f);
	glPopMatrix();

// CORNERS
// Left corner
	glPushMatrix() ;
	  glTranslatef(10.0f,22.0f,-10.0f);

  	  glBegin(GL_QUADS);  // Face with 4 sides
	 	glNormal3f(200.0f, 200.0f, 0.0f);
		glVertex3f(10.0f ,  0.0f , 0.0f ); //P1
		glVertex3f(10.0f , 0.0f , 20.0f ); //P2
		glVertex3f(0.0f , -10.0f ,20.0f ); //P3
		glVertex3f(0.0f ,  -10.0f ,0.0f ); //P4
	  glEnd();

	  glBegin(GL_POLYGON);  // Lower triangle
		glNormal3f(0.0f, 0.0f, -200.0f);
		glVertex3f(0.0f ,  0.0f , 0.0f );  // T1
		glVertex3f(10.0f ,  0.0f ,0.0f );  // P1
		glVertex3f(0.0f , -10.0f , 0.0f ); // P4
	  glEnd();

	  glBegin(GL_POLYGON);  // Triangle de dalt
		glNormal3f(0.0f, 0.0f, 200.0f);
		glVertex3f(0.0f ,  0.0f , 20.0f );	// T2
	    glVertex3f(0.0f , -10.0f , 20.0f ); // P3
		glVertex3f(10.0f ,  0.0f, 20.0f );  // P2
	  glEnd();
	glPopMatrix();

// Right corner
	glPushMatrix() ;
	  glTranslatef(-10.0f,22.0f,-10.0f);
	  glRotatef(-90.0f,0.0f,0.0f,1.0f);

  	  glBegin(GL_QUADS);  // Face with 4 sides
	 	glNormal3f(200.0f, 200.0f, 0.0f);
		glVertex3f(10.0f ,  0.0f , 0.0f ); //P1
		glVertex3f(10.0f , 0.0f , 20.0f ); //P2
		glVertex3f(0.0f , -10.0f ,20.0f ); //P3
		glVertex3f(0.0f ,  -10.0f ,0.0f ); //P4
	  glEnd();

	  glBegin(GL_POLYGON);  // Lower triangle
		glNormal3f(0.0f, 0.0f, -200.0f);
		glVertex3f(0.0f ,  0.0f , 0.0f );  // T1
		glVertex3f(10.0f ,  0.0f ,0.0f );  // P1
		glVertex3f(0.0f , -10.0f , 0.0f ); // P4
	  glEnd();

	  glBegin(GL_POLYGON);  // Upper triangle
		glNormal3f(0.0f, 0.0f, 200.0f);
		glVertex3f(0.0f ,  0.0f , 20.0f );	// T2
	    glVertex3f(0.0f , -10.0f , 20.0f ); // P3
		glVertex3f(10.0f ,  0.0f, 20.0f );  // P2
	  glEnd();
	glPopMatrix();


// WHEEL PROTECTIONS
// Wheel protections texture (metall)
//	if (textu)
//		{				
//			glBindTexture(GL_TEXTURE_2D,VTextu[5]) ;
//			glEnable(GL_TEXTURE_2D) ;
//			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
//			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
//			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
//			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
//			}

// Wheel protections color without texture
	glColor4f(0.5f,0.7f,1.0f,0.5f);

// Protection of left wheel
	glPushMatrix();		
		glTranslatef(10.0f, 0.0f, 3.0f);
		glBegin(GL_QUADS);
		//  glNormal3f(200.0f, 200.0f, 0.0f);
			glVertex3f(7.0f , -5.0f , 0.0f );
			glVertex3f(7.0f , 5.0f , 0.0f );
			glVertex3f(0.0f , 5.0f , 0.0f );
			glVertex3f(0.0f , -5.0f , 0.0f );

			glVertex3f(7.0f , -12.0f , -8.0f );
			glVertex3f(7.0f , -5.0f , 0.0f );
			glVertex3f(0.0f , -5.0f , 0.0f );
			glVertex3f(0.0f , -12.0f , -8.0f );

			glVertex3f(0.0f , 15.0f , -10.0f );
			glVertex3f(0.0f , 5.0f , 0.0f );
			glVertex3f(7.0f , 5.0f , 0.0f );
			glVertex3f(7.0f , 15.0f , -10.0f );

			glVertex3f(7.5f , -5.0f , -3.0f );
			glVertex3f(7.5f , 5.0f , -3.0f );
			glVertex3f(7.0f , 5.0f , 0.0f );
			glVertex3f(7.0f , -5.0f , 0.0f );
				
			glVertex3f(7.5f , -12.0f , -8.0f );
			glVertex3f(7.5f , -5.0f , -3.0f );
			glVertex3f(7.0f , -5.0f , 0.0f );
			glVertex3f(7.0f , -12.0f , -8.0f );
				
			glVertex3f(7.0f , 15.0f , -10.0f );
			glVertex3f(7.0f , 5.0f , 0.0f );
			glVertex3f(7.5f , 5.0f , -3.0f );
			glVertex3f(7.5f , 15.0f , -10.0f );

		glEnd();
	glPopMatrix();

// Protection of right wheel
	glPushMatrix();		
		glTranslatef(-16.0f, 0.0f, 3.0f);
		glBegin(GL_QUADS);
		//  glNormal3f(200.0f, 200.0f, 0.0f);
			glVertex3f(7.0f , -5.0f , 0.0f );
			glVertex3f(7.0f , 5.0f , 0.0f );
			glVertex3f(0.0f , 5.0f , 0.0f );
			glVertex3f(0.0f , -5.0f , 0.0f );

			glVertex3f(7.0f , -12.0f , -8.0f );
			glVertex3f(7.0f , -5.0f , 0.0f );
			glVertex3f(0.0f , -5.0f , 0.0f );
			glVertex3f(0.0f , -12.0f , -8.0f );

			glVertex3f(0.0f , 15.0f , -10.0f );
			glVertex3f(0.0f , 5.0f , 0.0f );
			glVertex3f(7.0f , 5.0f , 0.0f );
			glVertex3f(7.0f , 15.0f , -10.0f );

			glVertex3f(7.5f , -5.0f , -3.0f );
			glVertex3f(7.5f , 5.0f , -3.0f );
			glVertex3f(7.0f , 5.0f , 0.0f );
			glVertex3f(7.0f , -5.0f , 0.0f );
				
			glVertex3f(7.5f , -12.0f , -8.0f );
			glVertex3f(7.5f , -5.0f , -3.0f );
			glVertex3f(7.0f , -5.0f , 0.0f );
			glVertex3f(7.0f , -12.0f , -8.0f );
				
			glVertex3f(7.0f , 15.0f , -10.0f );
			glVertex3f(7.0f , 5.0f , 0.0f );
			glVertex3f(7.5f , 5.0f , -3.0f );
			glVertex3f(7.5f , 15.0f , -10.0f );
		glEnd();
	glPopMatrix();

// Engine Rack Texture
	if (textu)  
		{	GLfloat sPlane[4] = { 0.05f, 0.25f, 0.00f, 0.00f };
		  	GLfloat tPlane[4] = { 0.00f, 0.25f, 0.05f, 0.00f };
// Switch on texture
			glBindTexture(GL_TEXTURE_2D,VTextu[3]) ;
	
			glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
			
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glEnable(GL_TEXTURE_2D);
		}

// Engine Rack Color without texture
	glColor4f(0.5f,0.7f,1.0f,0.5f);	

// Engine Rack
	glPushMatrix();
		glTranslatef(0.0f,-22.0f,0.0f);
		glBegin(GL_QUADS);
		    glNormal3f(0.0f,-1.0f,0.0f);	
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(-10.0f , -2.0f , -10.0f );
			glTexCoord2f(1.0f,0.00f);
			glVertex3f(10.0f , -2.0f , -10.0f );
			glTexCoord2f(1.0f,1.0);
			glVertex3f(10.0f , -2.0f , 10.0f );
			glTexCoord2f(0.0f,1.0f);	
			glVertex3f(-10.0f , -2.0f , 10.0f );
		glEnd();
	glPopMatrix();

// Switch off texture
	if (textu) glDisable(GL_TEXTURE_2D);

// Axe color without texture
	glColor4f(0.1f,0.4f,1.0f,0.5f);

// Front axle
	glPushMatrix();
	  glTranslatef(0.0f,0.0f,-10.0f);
	  glRotatef(90.0f,0.0f,1.0f,0.0f);
  	  glTranslatef(0.0f,0.0f,-13.0f);
	  gluCilindre(2,2,26.0f,6,1);
	glPopMatrix();
	
// Front right wheel 
	glPushMatrix();
		glTranslatef(-10.0f,0.0f,-10.0f);
		neumatic(textu,VTextu);
	glPopMatrix();

// Front left wheel
	glPushMatrix();
		glTranslatef(17.0f,0.0f,-10.0f);
		neumatic(textu,VTextu);
	glPopMatrix();

// Switch off texture
	if (textu) glDisable(GL_TEXTURE_2D);

// LIGHTHOUSES	
// Color lighthouses without texture
	glColor4f(1.0f,0.0f,0.0f,0.5f);

// Left Lighthouse	
	glPushMatrix();
		glTranslatef(-13.5f,-17.0f,-8.0f);
		glScalef(7.0f, 2.0f, 4.0f);
		glutSolidCube(1.0f);
	glPopMatrix();

// Right Lighthouse
	glPushMatrix();
		glTranslatef(13.5f,-17.0f,-8.0f);
		glScalef(7.0f, 2.0f, 4.0f);
		glRotatef(90.0f,1.0f,0.0f,0.0f); // To the texture
		glutSolidCube(1.0f);
	glPopMatrix();

// Front Lighthouse texture
	  if (textu)  
		{	GLfloat sPlane[4] = { 0.15f, 0.0f, 0.0f, 0.5f };
	  		GLfloat tPlane[4] = { 0.0f, 0.35f, 0.25f, 0.15f };
// Switch on texture
			glBindTexture(GL_TEXTURE_2D,VTextu[4]) ;
	
			glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
				
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glEnable(GL_TEXTURE_2D);
			}

// Front lighthouse color without texture
	glColor4f(1.0f,1.0f,1.0f,0.5f);

// Right Front lighthouse
	glPushMatrix();
		glTranslatef(-13.5f,-16.5f,-8.0f);
		glBegin(GL_QUADS);
			glNormal3f(0.0f,-1.0f,0.0f);	
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(-3.5f , -2.0f , -2.0f );
			glTexCoord2f(1.0f,0.00f);
			glVertex3f(3.5f , -2.0f , -2.0f );
			glTexCoord2f(1.0f,1.0);
			glVertex3f(3.5f , -2.0f , 2.0f );
			glTexCoord2f(0.0f,1.0f);	
			glVertex3f(-3.5f , -2.0f , 2.0f );
		glEnd();	
	glPopMatrix();

// Left Front lighthouse
	glPushMatrix();
		glTranslatef(13.5f,-16.5f,-8.0f);
		glBegin(GL_QUADS);
			glNormal3f(0.0f,-1.0f,0.0f);	
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(-3.5f , -2.0f , -2.0f );
			glTexCoord2f(1.0f,0.00f);
			glVertex3f(3.5f , -2.0f , -2.0f );
		glTexCoord2f(1.0f,1.0);
			glVertex3f(3.5f , -2.0f , 2.0f );
			glTexCoord2f(0.0f,1.0f);	
			glVertex3f(-3.5f , -2.0f , 2.0f );
		glEnd();
	glPopMatrix();

// Switch off texture
	if (textu) glDisable(GL_TEXTURE_2D);

// VIDRE CABINA (SENSE TEXTURA)
// Activar transparència
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

// Cabin glass color without texture
	glColor4f(0.3f,0.8f,0.7f,0.5f);

// Glass
	glPushMatrix() ;
	  glTranslatef(0.0f,22.0f,10.0f);
	  glRotatef(-90.0f,1.0f,0.0f,0.0f);
	  glRotatef(90.0f,0.0f,1.0f,0.0f);
	  glTranslatef(0.0f,00.0f,-10.0f);

   	  glBegin(GL_QUADS);  // Face with 4 sides
	 	glNormal3f(200.0f, 200.0f, 0.0f);
		glVertex3f(10.0f ,  0.0f , 0.0f ); //P1
		glVertex3f(10.0f , 0.0f , 20.0f ); //P2
		glVertex3f(0.0f , -10.0f ,20.0f ); //P3
		glVertex3f(0.0f ,  -10.0f ,0.0f ); //P4
	  glEnd();

	  glBegin(GL_POLYGON);  // Lower triangle
		glNormal3f(0.0f, 0.0f, -200.0f);
		glVertex3f(0.0f ,  0.0f , 0.0f );  // T1
		glVertex3f(10.0f ,  0.0f ,0.0f );  // P1
		glVertex3f(0.0f , -10.0f , 0.0f ); // P4
	  glEnd();

	  glBegin(GL_POLYGON);  // Upper triangle
		glNormal3f(0.0f, 0.0f, 200.0f);
		glVertex3f(0.0f ,  0.0f , 20.0f );	// T2
	    glVertex3f(0.0f , -10.0f , 20.0f ); // P3
		glVertex3f(10.0f ,  0.0f, 20.0f );  // P2
	  glEnd();
	glPopMatrix();

// Switch off transparency
	glDisable(GL_BLEND);

// EXHAUST PIPE (WITHOUT TEXTURE)
// Exhaust Pipe color without texture
	glColor4f(1.0f,0.0f,0.0f,0.5f);

// Left Exhaust Pipe
	glPushMatrix();
		glTranslatef(18.0f,42.0f,10.0f);	
		gluCilindre(2,2,40.0f,12,1);	
	glPopMatrix();
	
// Right Exhaust Pipe
	glPushMatrix();
		glTranslatef(-18.0f,42.0f,10.0f);	
		gluCilindre(2, 2, 40.0f, 12, 1);
	glPopMatrix();

// BODYWORK
// Bodywork texture
	if (textu)
		{	GLfloat sPlane[4] = { 0.05f, 0.0f, 0.00f, 0.250f };
		  	GLfloat tPlane[4] = { 0.00f, 0.05f, 0.1f, 0.00f };

// Switch on texture
			glBindTexture(GL_TEXTURE_2D,VTextu[5]) ;
	
			glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
			
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glEnable(GL_TEXTURE_2D);
		}

// Color porta-eix motriu sense textura
	glColor4f(0.5f,0.7f,1.0f,0.5f);

// Porta-eix motriu mig
	glPushMatrix();
	  glTranslatef(0.0f,82.0f,-5.0f);
	  glScalef(1.0f, 5.0f, 1.0f);
	  glutSolidCube(10.0f);
	glPopMatrix();

	if (textu) glDisable(GL_TEXTURE_2D);

// Conjunt eixos i rodes eix mig
	glPushMatrix();
// Desplaçament Eix Mig
	  glTranslatef(0.0f,72.0f,0.0f);

// Axe color withou texture
	  glColor4f(0.1f,0.4f,1.0f,0.5f);

// Front Middle Axe
	  glPushMatrix();
	    glTranslatef(0.0f,0.0f,-10.0f);
	    glRotatef(90.0f,0.0f,1.0f,0.0f);
	    glTranslatef(0.0f,0.0f,-13.0f);
		gluCilindre(2, 2, 26.0f, 6, 1);
	  glPopMatrix();
	
// Roda Dreta Davantera Eix Mig Davanter
	  glPushMatrix();
	    glTranslatef(-10.0f,0.0f,-10.0f);
	    neumatic(textu,VTextu);
	  glPopMatrix();

// Roda Esquerra Davantera Eix Mig Davanter
	  glPushMatrix();
	    glTranslatef(17.0f,0.0f,-10.0f);
	    neumatic(textu,VTextu);
	  glPopMatrix();

// Switch off texture
	if (textu) glDisable(GL_TEXTURE_2D);

// Distance btween the two axes
	  glTranslatef(0.0f,25.0f,0.0f);

// Axe color without texture
	  glColor4f(0.1f,0.4f,1.0f,0.5f);

// Rear Middle Axe
	  glPushMatrix();
	    glTranslatef(0.0f,0.0f,-10.0f);
	    glRotatef(90.0f,0.0f,1.0f,0.0f);
	    glTranslatef(0.0f,0.0f,-13.0f);
		gluCilindre(2, 2, 26.0f, 6, 1);
	  glPopMatrix();
	
// Roda Dreta Davantera Eix Mig Darrera
	  glPushMatrix();
	    glTranslatef(-10.0f,0.0f,-10.0f);
	    neumatic(textu,VTextu);
	  glPopMatrix();

// Roda Esquerra Davantera Eix Mig Darrera
	  glPushMatrix();
	    glTranslatef(17.0f,0.0f,-10.0f);
	    neumatic(textu,VTextu);
	  glPopMatrix();

// End axes set and middle axe wheels
    glPopMatrix();

// Switch off texture
	if (textu) glDisable(GL_TEXTURE_2D);
		
// TOW	
// Bodywork texture
	if (textu)
		{	GLfloat sPlane[4] = { 0.05f, 0.0f, 0.00f, 0.250f };
		  	GLfloat tPlane[4] = { 0.00f, 0.05f, 0.1f, 0.00f };

// Switch on texture
			glBindTexture(GL_TEXTURE_2D,VTextu[5]);
	
			glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
			
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glEnable(GL_TEXTURE_2D);
		}


// Color plataforma sense textura
	glColor4f(0.5f,0.7f,1.0f,0.5f);

// Plataform
	glPushMatrix();
		glTranslatef(0.0f,127.0f,4.0f);
		glScalef(3.0f, 14.0f, 0.8f);
		glutSolidCube(10.0f);
	glPopMatrix();

// Tank texture
	if (textu)
		{	glBindTexture(GL_TEXTURE_2D,VTextu[6]);
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glEnable(GL_TEXTURE_2D);			
		}

// Tank color without texture
	glColor4f(0.9f,0.9f,1.0f,0.5f);

// Tank
	glPushMatrix();
	  glTranslatef(0.0f,60.0f,20.0f);
	  glScalef(0.75f,1.0f,0.5f);
	  glRotatef(270.0f,1.0f,0.0f,0.0f);
// Front Part
	  gluCilindre(20, 25, 5.0f, 25, 1);
	  glPushMatrix();
	  	glRotatef(180.0f,1.0f,0.0f,0.0f);
		gluDisc(0.0f, 20.0f, 25, 1);	
	  glPopMatrix();
// Central Part
	  glTranslatef(0.0f,0.0f,5.0f);
	  gluCilindre(25, 25, 125.0f, 25, 1);
// Rear Part
	  glPushMatrix();
		glTranslatef(0.0f,0.0f,125.0f);
		gluCilindre(25, 20, 5.0f, 25, 1);
		glTranslatef(0.0f,0.0f,5.0f);
		gluDisc(0.0f, 20.0f, 25, 1);	
	  glPopMatrix();
	glPopMatrix();

// Switch off texture
//	if (textu) glDisable(GL_TEXTURE_2D);

// Textura planxa
	if (textu)  
		{	
			GLfloat sPlane[4] = { 0.05f, 0.0f, 0.00f, 0.250f };
		  	GLfloat tPlane[4] = { 0.00f, 0.05f, 0.1f, 0.00f };
// Switch on texture
			glBindTexture(GL_TEXTURE_2D,VTextu[5]) ;
	
			glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
			
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glEnable(GL_TEXTURE_2D);
		}

// Color porta-eix motriu
	glColor4f(0.5f,0.7f,1.0f,0.5f);

// Porta-eix motriu darrera
	glPushMatrix();
	  glTranslatef(0.0f,172.0f,-5.0f);
	  glScalef(1.0f, 5.0f, 1.0f);
	  glutSolidCube(10.0f);
	glPopMatrix();

// Desactivar textura
	if (textu) glDisable(GL_TEXTURE_2D);

// Conjunt eixos i rodes eix darrera
	glPushMatrix();

// Desplaçament Eix Darrera
	  glTranslatef(0.0f,162.0f,0.0f);

// Color eix sense textura
	  glColor4f(0.1f,0.4f,1.0f,0.5f);

// Eix Darrera Davanter
	  glPushMatrix();
	    glTranslatef(0.0f,0.0f,-10.0f);
	    glRotatef(90.0f,0.0f,1.0f,0.0f);
	    glTranslatef(0.0f,0.0f,-13.0f);
		gluCilindre(2, 2, 26.0f, 6, 1);
	  glPopMatrix();
	
// Roda Dreta Davantera Eix Darrera Davanter
	  glPushMatrix();
	    glTranslatef(-10.0f,0.0f,-10.0f);
	    neumatic(textu,VTextu);
	  glPopMatrix();

// Roda Esquerra Davantera Eix Darrera Davanter
	  glPushMatrix();
	    glTranslatef(17.0f,0.0f,-10.0f);
	    neumatic(textu,VTextu);
	  glPopMatrix();

// Desactivar textura
	if (textu) glDisable(GL_TEXTURE_2D);

// Desplaçament entre dos eixos
	  glTranslatef(0.0f,25.0f,0.0f);

// Color eix sense textura
	  glColor4f(0.1f,0.4f,1.0f,0.5f);

// Eix Darrera Darrera
	  glPushMatrix();
		glTranslatef(0.0f,0.0f,-10.0f);
	 	glRotatef(90.0f,0.0f,1.0f,0.0f);
		glTranslatef(0.0f,0.0f,-13.0f);
		gluCilindre(2, 2, 26.0f, 6, 1);
	  glPopMatrix();
	
// Roda Dreta Davantera Eix Darrera Darrera
	  glPushMatrix();
	    glTranslatef(-10.0f,0.0f,-10.0f);
	    neumatic(textu,VTextu);
	  glPopMatrix();

// Roda Esquerra Davantera Eix Darrera Darrera
	  glPushMatrix();
	    glTranslatef(17.0f,0.0f,-10.0f);
	    neumatic(textu,VTextu);
	  glPopMatrix();
// Fi conjunt eixos i rodes eix darrera
	glPopMatrix();

// Fi dibuix Truck
glPopMatrix();

// Restaurar textura[0]
if (textu)
	{	glBindTexture(GL_TEXTURE_2D,VTextu[0]);
//		glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
//		glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_2D);			
	}
}


// Wheel drawing
// neumatic: Paràmetres:
//    - textur: Flag if textures switched on or off.
//    - VTextur: Image vector texture.
void neumatic(bool textur, GLuint VTextur[NUM_MAX_TEXTURES])
{
// Textura tire
	if (textur)  
		{	
// Switch on tire texture
			glBindTexture(GL_TEXTURE_2D,VTextur[1]) ;
			
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glEnable(GL_TEXTURE_2D);
		}

// Tire Color without texture
	glColor4f(0.2f,0.2f,0.2f,0.5f);	

	glPushMatrix();
// Upper Tire Top
	  glRotatef(90.0f,0.0f,1.0f,0.0f);
	  gluDisc(5.0f, 10.0f, RESOLUCIO_RODA, 1);

// Dibuix de la llanta
	  llanta(textur,VTextur);

// Textura neumàtic
	  if (textur)  
		{	
// Switch on tire texture
			glBindTexture(GL_TEXTURE_2D,VTextur[1]) ;	
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glEnable(GL_TEXTURE_2D);
		}

// Tire Color without texture
	glColor4f(0.2f,0.2f,0.2f,0.5f);	

// Tire Thick
	  glTranslatef(0.0f,0.0f,-6.0f);
	  gluCilindre(10, 10, 6.0f, RESOLUCIO_RODA, 1);
// Tire Upper Top
	  glRotatef(180.0f,0.0f,1.0f,0.0f);
	  gluDisc(5.0f, 10.0f, RESOLUCIO_RODA, 1);
// Tire drawing
	  llanta(textur,VTextur);
	glPopMatrix();

// Switch off textures
//	if (textur) glDisable(GL_TEXTURE_2D);

}

// Wheel tire drawing
// llanta: Paràmeters:
//    - textur: Flag of textures if switched on or not.
//    - VTextur: Image texture Vector.
void llanta(bool textur, GLuint VTextur[NUM_MAX_TEXTURES])
{

// Tire Texture
	if (textur)  
		{	GLfloat sPlane[4] = { 0.0f, -0.1f, 0.5f, 0.5f };
		  	GLfloat tPlane[4] = { 0.1f, 0.0f, 0.5f, 0.5f };
// Texture Switch on
			glBindTexture(GL_TEXTURE_2D,VTextur[2]) ;
			glEnable(GL_TEXTURE_2D) ;
		
			glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
			glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);
			
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR) ;
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR) ;
			glEnable(GL_TEXTURE_GEN_S) ;
			glEnable(GL_TEXTURE_GEN_T) ;
		}

// Tire drawing (disk of 5 radius of light color)
	glColor4f(0.7f,0.7f,0.7f,0.5f);	
	gluDisc(0.0f, 5.0f, RESOLUCIO_RODA, 1);

}


// Ondulated sea
void sea(void)
{
	int i, j, step, it1, it2;
	//     GLfloat pi=3.14159;
	float angle, delay;

	//aigua plana
	/*	glColor3f(0.5,0.4,0.9);
	glNormal3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-250,-250,0);
	glVertex3f(250,-250,0);
	glVertex3f(250,250,0);
	glVertex3f(-250,250,0);
	glEnd();*/

// Ondulated water simulated from sinusoidal normal vectors
	step = 5;
	delay = 0;
	it1 = 0;

//   SeleccionaMaterial(MAT_DEFAULT);	
	float h = 2 * pi*step / 500;
	for (j = -250; j<250 - step; j = j + step)
	{

		delay = 1.0*h*it1;

		it2 = 0;
		glColor3f(0.5f, 0.4f, 0.9f);
		for (i = -250; i<250 - step; i = i + step)
		{
			glBegin(GL_POLYGON);
			angle = 1.0*it2*h * 15;
			glNormal3f(-cos(angle), 0, 1);
			glVertex3f(i, j, 0);

			angle = 1.0*(it2 + 1)*h * 15;
			glNormal3f(-cos(angle), 0, 1);
			glVertex3f(i + step, j, 0);

			angle = 1.0*(it2 + 1)*h * 15;
			glNormal3f(-cos(angle), 0, 1);
			glVertex3f(i + step, j + step, 0);
			glEnd();

			glBegin(GL_POLYGON);
			angle = 1.0*it2*h * 15;
			glNormal3f(-cos(angle), 0, 1);
			glVertex3f(i, j, 0);

			angle = 1.0*(it2 + 1)*h * 15;
			glNormal3f(-cos(angle), 0, 1);
			glVertex3f(i + step, j + step, 0);

			angle = 1.0*it2*h * 15;
			glNormal3f(-cos(angle), 0, 1);
			glVertex3f(i, j + step, 0);
			glEnd();
			it2++;
		}
		it1++;
	}

}



// OBJECTE Hurakan project
void hurakan(bool textu, GLuint VTextu[NUM_MAX_TEXTURES])
{
	/*double aArm = (2 * pi * fmod(angleArm - 90, 360) / 360.0f);
	double xArm = (armSizeZ / 2 - seatSizeZ/2 - 0.5) * hurakanSize * -cos(aArm);
	double zArm = (armSizeZ / 2 - seatSizeZ/2 - 0.5) * hurakanSize * sin(aArm);
	zArm += (legSizeZ - offset) * hurakanSize;

	double aSeat = (2 * pi * fmod(angleSeat + angleArm + 90, 360) / 360.0f);
	double xSeat = (seatSizeZ/2)* hurakanSize * - cos(aSeat);
	double zSeat = (seatSizeZ/2)* hurakanSize * sin(aSeat);
	double x = xArm + xSeat;
	double z = zArm + zSeat;

	double xEye = radiusSky * cos(aSeat);
	double zEye = radiusSky * sin(aSeat);


	glPushMatrix();
	glTranslatef(x, 0.0f, z);
	glutSolidSphere(2, 10, 10);
	glPopMatrix();*/







	glPushMatrix();
		glRotatef(270.0, 0.0, 1.0, 0.0);
		glTranslatef(-25.0f, 0.0f, 0.0f);
		//Hemisphere
		glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glPushMatrix();
				//glRotatef(90.0, 0.0, 0.0, 0.0);
				glBindTexture(GL_TEXTURE_2D, texturID[1]);
				hemisphere(radiusSky, 500, 500);
			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, texturID[1]);
			glPushMatrix();
				glTranslatef(25.0f, 0.0f, 0.0f);
				glScalef(0.001f, 5000.0f, 3000.0f);
				glutSolidCube(1.0);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	

	
	//Hurakan structure
	glPushMatrix();
		// Color
		glColor3f(1.0f, 1.0f, 1.0f);

		glTranslatef(0.0f, 1.0f, 0.0f);
		glScalef(hurakanSize, hurakanSize, hurakanSize);
		glPushMatrix();
		
			// Rotate the arms and the seat
			glTranslatef(0.0f, 0.0f, legSizeZ - offset);
			glRotatef(angleArm, 0.0f, 1.0f, 0.0f);
			glTranslatef(0.0f, 0.0f, -(legSizeZ - offset) );

			glPushMatrix();

				// Rotate the seat
				glTranslatef(0.0f, 0.0f, legSizeZ - armSizeZ/2 + offset);
				glRotatef(angleSeat, 0.0f, 1.0f, 0.0f);
				glTranslatef(0.0f, 0.0f, -(legSizeZ - armSizeZ/2 + offset) );

				// Draw the seat
				glPushMatrix();
					glTranslatef(0.0f, 0.0f, legSizeZ - armSizeZ/2 + offset);
					glScalef(seatSizeX, seatSizeY, seatSizeZ);
					glutSolidCube(1);
				glPopMatrix();

			glPopMatrix();

			// Draw two arms
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, legSizeZ - armSizeZ/2 + armSizeZ/2);
				glPushMatrix();
					glTranslatef(0.0f, -(armSizeY/2 + seatSizeY/2), 0.0f);
					glPushMatrix();
						glTranslatef(0.0f, -(armSizeY/2 + 0.5f), -0.5f);
						glutSolidCube(1);
					glPopMatrix();
					glPushMatrix();
						glScalef(armSizeX, armSizeY, armSizeZ);
						glutSolidCube(1);
					glPopMatrix();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0.0f, armSizeY/2 + seatSizeY/2, 0.0f);
					glPushMatrix();
						glTranslatef(0.0f, armSizeY/2 + 0.5f, -0.5f);
						glutSolidCube(1);
					glPopMatrix();
					glPushMatrix();
						glScalef(armSizeX, armSizeY, armSizeZ);
						glutSolidCube(1);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();

		glPopMatrix();

		//Draw two legs
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, legSizeZ / 2);
			glPushMatrix();
				glTranslatef(0.0f, seatSizeY / 2 + armSizeY + 1.0f + legSizeY / 2, 0.0f);
				glScalef(legSizeX, legSizeY, legSizeZ);
				glutSolidCube(1);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, -(seatSizeY / 2 + armSizeY + 1.0f + legSizeY / 2), 0.0f);
				glScalef(legSizeX, legSizeY, legSizeZ);
				glutSolidCube(1);
			glPopMatrix();
		glPopMatrix();

		//Draw cube
		glPushMatrix();
			glTranslatef(0.0, 0.0, 0.5f);
			glScalef(legSizeX + 20, 2 * (legSizeY + armSizeZ) + seatSizeY + 5, 1);
			glutSolidCube(1);
		glPopMatrix();
	glPopMatrix();
}

void changeangle() {

	if (Turn == 0) {

		oldASpeed = hurakanASpeed;
		hurakanASpeed += velIncrement;
		velIncrement = (hurakanASpeed * 0.004);
		ang1AccelIncrement = hurakanASpeed * 0.016;
		angleArm += 0.5f * ang1AccelIncrement;
	}
	else if (Turn > 0 && Turn < NTurns) {
		hurakanASpeed = maxhurakanASpeed;
		angleArm += ang1Increment;
	}
	else if (Turn == NTurns) {
		hurakanASpeed = maxhurakanASpeed;
		oldASpeed = hurakanASpeed;
		hurakanASpeed -= velIncrement;
		velIncrement = (hurakanASpeed * 0.004);
		ang1AccelIncrement = hurakanASpeed * 0.016;
		angleArm += 0.5f * ang1AccelIncrement;
	}
	else if (Turn > NTurns) {
		angleArm = 0;
	}

	if (angleArm > 360) {
		angleArm = angleArm - 360;
		Turn++;
	}
}

void changeangle2() {
	if (Turn > 0 && Turn < NTurns) {
		
		if (angleArm > 45 && angleArm < 260) {
			angleSeat = angleSeat + i * 0.03f;
			i++;
		}
		else {
			angleSeat = 0;
			i = 0;
		}
		if (angleSeat > 360) {
			angleSeat = angleSeat - 360;
		}
	
	}
}

float speedupdate() {
	return hurakanASpeed;
}

void calculateacceleration(GLfloat hurakanEPower, GLfloat hurakanMass,  GLfloat hurakanGravity) {

	Turn = 0;

	oldASpeed = 0.0f;

	angleArm = 0.0f;

	angleSeat = 0.0f;

	// Acceleration.

	// Convert Power to IU.

	hurakanIUPower = hurakanEPower * 765;


	// Calculate the acceleration.

	hurakanLAccel = (hurakanIUPower * accelTime) / (hurakanMass * hurakanRadius * (float)TWOPI);

	// Angular velocity.

	// Calculate the maximum angular speed.

	maxhurakanASpeed = (sqrt(hurakanGravity / hurakanRadius) + sqrt(hurakanLAccel / hurakanRadius)) * radtodeg;

	// Turns made during the animation, excluding the acceleration and deceleration.

	// Calculate number of turns.

	maxTurns = ceilf((maxhurakanASpeed * 90 / 360) * 1) / 1;

	NTurns = (int)maxTurns;

	// Increment in angle and velocity for position calculation.

	// Calculate the number of frames to do the animation.

	velIncrement = (maxhurakanASpeed / accelTime) * 0.016f;

	ang1Increment = ((maxTurns * 360.0f) / 90.0f) * 0.016f;
}

	//OBJECTE Engine for the Hurakan, demonstration of how it moves.
/*void engine(bool textu, GLuint VTextu[NUM_MAX_TEXTURES]) {

	//Draw the engine inmobile part.
	//Draw the base of the engine.
	glPushMatrix();
	glScalef((float)sqrt(), 8.0f, 4.0f);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
}*/


