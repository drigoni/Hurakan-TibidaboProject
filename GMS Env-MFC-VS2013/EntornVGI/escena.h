//******** PRACTICAL WORK GRAPHICAL & MULTIMEDIA SYSTEMS (Engineering School - UAB)
//******** Basic Environment VS2013 MULTIWINDOW with MFC interface and Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� (Febrer 2018)
// escena.h : escena interface
//

#ifndef GLSOURCE_H
#define GLSOURCE_H


extern GLfloat legSizeX;
extern GLfloat legSizeY;
extern GLfloat legSizeZ;
extern GLfloat armSizeX;
extern GLfloat armSizeY;
extern GLfloat armSizeZ;
extern GLfloat seatSizeX;
extern GLfloat seatSizeY;
extern GLfloat seatSizeZ;
extern GLfloat offset;
extern GLfloat angleArm, angleSeat, hurakanSize;
extern GLfloat radiusSky;

/* ------------------------------------------------------------------------- */
/*                            Scenes Functions                               */
/* ------------------------------------------------------------------------- */
// GMS Environment: dibuixa_EscenaGL -> Draws the GL scene
void dibuixa_EscenaGL(char objecte, CColor col_object, bool ref_mat, bool sw_mat[4], bool textur);

// GMS Environment: dibuixa -> Function that draws simple GLUT or GLU objects according the value of obj variable
void dibuixa(char obj);

// GMS Environment: Truck
void hurakan(bool textu, GLuint VTextu[NUM_MAX_TEXTURES]);
void truck(bool textu,GLuint VTextu[NUM_MAX_TEXTURES]);
void neumatic(bool textur, GLuint VTextur[NUM_MAX_TEXTURES]);
void llanta(bool textur, GLuint VTextur[NUM_MAX_TEXTURES]);
void sea(void);
#endif