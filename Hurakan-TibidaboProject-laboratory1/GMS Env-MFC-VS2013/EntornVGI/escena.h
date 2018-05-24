//******** PRACTICAL WORK GRAPHICAL & MULTIMEDIA SYSTEMS (Engineering School - UAB)
//******** Basic Environment VS2013 MULTIWINDOW with MFC interface and Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Julià, Débora Gil, Enric Martí (Febrer 2018)
// escena.h : escena interface
//

#ifndef GLSOURCE_H
#define GLSOURCE_H

/* ------------------------------------------------------------------------- */
/*                            Scenes Functions                               */
/* ------------------------------------------------------------------------- */
// GMS Environment: dibuixa_EscenaGL -> Draws the GL scene
void dibuixa_EscenaGL(char objecte, CColor col_object, bool ref_mat, bool sw_mat[4], bool textur);

// GMS Environment: dibuixa -> Function that draws simple GLUT or GLU objects according the value of obj variable
void dibuixa(char obj);

// GMS Environment: Truck
extern float elbowz;
extern float elbowx;
extern float wristz;
extern float wristx;
extern float wristy;
extern float clamp;
extern float aexi;
extern float aezi;
extern float bwxi;
extern float bwyi;
extern float bwzi;
extern float aci;
extern float aexf;
extern float aezf;
extern float bwxf;
extern float bwyf;
extern float bwzf;
extern float acf;
void InElZP();
void InElZN();
void InElXP();
void InElXN();
void InWrZP();
void InWrZN();
void InWrXP();
void InWrXN();
void InWrYP();
void InWrYN();
void InCl();
void DeCl();
void hurikan(bool textu, GLuint VTextu[NUM_MAX_TEXTURES]);
void robot(bool textu, GLuint VTextu[NUM_MAX_TEXTURES]);
/*void robot_leg(bool textu, GLuint VTextu[NUM_MAX_TEXTURES]);
void robot_elbow(bool textu, GLuint VTextu[NUM_MAX_TEXTURES]);
void robot_arm(bool textu, GLuint VTextu[NUM_MAX_TEXTURES]);
void robot_wrist(bool textu, GLuint VTextu[NUM_MAX_TEXTURES]);
void robot_clamp(bool textu, GLuint VTextu[NUM_MAX_TEXTURES]);*/
void truck(bool textu,GLuint VTextu[NUM_MAX_TEXTURES]);
void neumatic(bool textur, GLuint VTextur[NUM_MAX_TEXTURES]);
void llanta(bool textur, GLuint VTextur[NUM_MAX_TEXTURES]);
void sea(void);
#endif