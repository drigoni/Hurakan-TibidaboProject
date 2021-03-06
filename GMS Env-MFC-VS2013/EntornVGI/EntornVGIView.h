//******** PRACTICAL WORK GRAPHICAL & MULTIMEDIA SYSTEMS (Engineering School - UAB)
//******** Basic Environment VS2013 MULTIWINDOW with MFC interface and Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� (February 2018)
// EntornVGIView.h : interface of the CEntornVGI class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "MainFrm.h"

// GMS: Constant definition of the Visual Studio application entorn VGI
#include "constants.h"

// GMS: Includes shaders GLSL
#include <gl/glew.h>
#include <gl/wglew.h>

// GMS: OpenGL Libraries
//#include <gl/gl.h>
//#include <gl/glu.h>
//#include <gl/glut.h>

// VGI Environment: 3DS OBJECT. Include to definition of Obj_3DS class
#include "Obj3DS.h"	

// VGI Environment: OBJ OBJECT. Include per la definition of Obj_OBJ class
#include "objLoader.h"	

class CEntornVGIView : public CView
{
protected: // Crear s�lo a partir de serializaci�n
	CEntornVGIView();
	DECLARE_DYNCREATE(CEntornVGIView)

// Atributos
public:
	CEntornVGIDoc* GetDocument() const;

//-------------- GMS Environment: Global variables of CEntornVGIView class
	HGLRC	 m_hrc;		// OpenGL Rendering Context 

// VGI environment: Control variables to menu option View->FullScreen 
	bool fullscreen;	// Opci� booleana per Pantalla Completal [0:NO,1:SI]

// VGI Environment: Variables de control per Men� Vista: canvi PV interactiu, Zoom i dibuixar eixos 
	bool mobil;	 // Opci� canvi de Punt de Vista interactiu (mobil) [0:NO,1:SI]
	bool zzoom;	 // Opci� Zoom interactiu (zoom) [0:NO,1:SI]
	bool satelit; // Opci� de navegaci� animada al volt de l'objecte centrat definint increment per mouse (SAT�LIT)
	bool pan;    // Opcio Pan. Despla�ament del centre de l'esfera de Vista [0:NO,1:SI]
	bool navega; // Opci� Navega [F:NO,T:SI].
	bool eixos;	 // Opci� per dibuixar els eixos X,Y,Z (Eixos?) [0:NO,1:SI]

// VGI Environment: Variables de l'opci� Vista->Pan
	float fact_pan;	  // Factor de despla�ament de la c�mara (opci� pan).
	CPunt3D tr_cpv;   // Vector de Traslaci� del Centre del Punt de Vista actiu dins opci� pan.
	CPunt3D tr_cpvF;  // Vector de Traslaci� del Centre del Punt de Vista (fixat amb INSERT dins opci� pan) 
					  //       i actiu fora l'opci� pan.

// VGI Environment: Variables de control de l'opci� Vista->Navega?
	GLfloat n[3];   // Punt cap on mira.
	CPunt3D opvN;   // Definici� Or�gen Punt de Vista (en coordenades m�n)
	float angleZ;   // angle de rotaci� de la traject�ria.

// VGI Environment: Variables de control per les opcions de men� Projecci�, Objecte
	char projeccio;	// Men� Projecci�: Tipus de projeccio 
	char objecte;	// Men� Objecte: Tipus d'Objecte

// VGI Environment: Variables de control del men� Transforma
	bool transf;	// Booleana per activar Transformacions (true) o no (false).
	bool trasl;		// Booleana d'activaci� de la Traslaci� (true) o no (false).
	bool rota;		// Booleana d'activaci� de la Rotaci� (true) o no (false).
	bool escal;		// Booleana d'activaci� de l'Escalatge (true) o no (false).
	float fact_Tras, fact_Rota;	// Increments de Traslaci� i Rotaci�.
	INSTANCIA TG;	// Estructura que cont� TG del men� Transforma actiu dins qualsevol opci� de Transforma 
					//      (Traslaci� Rotaci� i Escalatge).
	INSTANCIA TGF;	// Estructura que cont� TG del men� Transforma fixat amb INSERT dins les opcions de Transforma
					//     i actiu fora l'opci� Transforma.
	bool transX;	// Opci� Mobil Eix X?: TG interactives per l'eix X via mouse [F:NO,T:SI].
	bool transY;	// Opci� Mobil Eix Y?: TG interactives per l'eix Y via mouse [F:NO,T:SI].
	bool transZ;	// Opci� Mobil Eix Z?: TG interactives per l'eix Z via mouse [F:NO,T:SI].

// VGI Environment: Variables de control per les opcions de men� Ocultacions
	bool test_vis;  // Men� ocultacions: Activa [true] o desactiva [false] Test Visibilitat.
	bool oculta;    // Men� ocultacions: Activa [true] o desactiva [false] Ocultacions (Z-buffer).
	bool back_line; // Men� ocultacions: Activa [true] o desactiva [false] dibuix cares back com a l�nies.

// VGI Environment: Variables de control del men� Iluminaci�	
	bool ifixe;         // Iluminaci� fixe independent del PV (ifixe=1) 
						// o depenent (mobil) respecte el PV (casc miner) (ifixe=0)
	char ilumina;		// Tipus d'il.luminaci� [FILFERROS 'f',PLANA 'c',SUAU 'c']
	bool sw_material[4];// Variable que controla els coeficients de reflectivitat del material [TRUE] o no [FALSE]:
	// [0]: emission, [1]: ambient, [2]: difusa, [3] especular.
	bool sw_material_old[4]; // Variable que guarda els valors de sw_material mentre no hi ha reflectivitat de material (refl_material=false).
	bool textura;       // Control de textures desactivades [0:NO] o activades [1:SI]
	char t_textura;		// Tipus de textures (predefinides o per fitxer)
	bool textura_map;	// Mapping de textura modulat amb la llum [TRUE] o calcat [FALSE]

// VGI Environment: Variables de control del men� Llums
	bool llum_ambient;	// Booleana que controla la llum ambient (SI/NO).
	LLUM llumGL;		// Llum 0
	bool sw_llambient;	// Booleana que controla modus de configurar el color de la llum ambient [TRUE] o no [FALSE]
	CColor col_llambient;// Color llum ambient.

// VGI Environment: Variables de control del men� Shaders
	bool sw_shader;			// Variable que controla si els shaders s�n actius [TRUE] o no [FALSE]
	char shader_menu;		// Variable que defineix el shader actiu
	GLuint shader_program;	// Shader Program que cont� el Vertex i Fragment program.

// VGI Environment: Variables butons de mouse 
	CPoint m_PosEAvall, m_PosDAvall; // Coordenades del cursor quan el boto esquerre(E) o dret(D) del 
									 //    mouse ha estat clicat.
	bool m_ButoEAvall, m_ButoDAvall; //TRUE si el boto esquerre(E) o dret(D) del mouse esta clicat.
	CEsfe3D m_EsfeEAvall;			 // Coordenades Esf�riques del PV (OPV) quan el boto esquerre(E) o dret(D) del 
	//										mouse ha estat clicat.
	CEsfe3D m_EsfeIncEAvall;		 // Increment de despla�ament en coordenades Esf�riques del PV (OPV).

// VGI Environment: Variables que controlen par�metres visualitzaci�: Mides finestra Windows i PV
	int w, h;				// Mides de la finestra Windows (w-amplada,h-al�ada)
	CEsfe3D OPV;			// Par�metres camera en coord. esf�riques (R,alfa,beta)
	char Vis_Polar;			// Variable que controla orientaci� dels eixos en Visualitzaci� Interactiva (POLARZ,POLARY,POLARX)

// VGI Environment: Color de fons i de l'objecte
	bool fonsR, fonsG, fonsB;	// Booleanes per controlar variaci� de color per teclat.
	CColor c_fons;			// Intensitat de color de fons.
	bool sw_color;			// Booleana que controla el modus de configurar color de l'objecte per teclat [TRUE] o no [FALSE]
	CColor col_obj;			// Color de l'objecte simple.

// VGI Environment: Objecte 3DS:
	Obj_3DS* Ob3DS;			// Variable d'objecte 3D Studio (*.3DS)

// VGI Environment: Objecte OBJ:
	COBJModel* ObOBJ;		// Variable d'objecte format OBJ (*.OBJ)

// VGI Environment: Variables del Timer
	float t;		// Par�metre t pel Timer.
	bool anima;		// Booleana que controla si l'animaci� �s activa (TRUE) o no (FALSE)
					//    dins la funci� de control del rellotge OnTimer.

// VGI Environment: Variables de l'objecte FRACTAL
	char t_fractal;		// Tipus de fractal.
	char soroll;		// Men� Fractals: Tipus de soroll
	int pas, pas_ini;	// Resoluci� del fractal inicial (pas_ini) i de visualitzaci� (pas).
	bool sw_il;			// Booleana que controla si cal compilar el fractal (sw_il=1) o no (sw_il=0)
	bool palcolFractal;	// Booleana que activa coloraci� del fractal segons paleta de colors [TRUE] o no [FALSE].

// VGI Environment: Altres variables
	GLfloat mida;	// Factor d'escala per calcular Volum de Visualitzaci� de l'objecte que encaixi.
	CString nom;	// Nom de fitxer.
	CString buffer; // Buffer que magatzema string caracters corresponent a variables float a printar en Status Bar (funci� Barra_Estat).

// Variables about Hurakan
	GLfloat hurakanASpeed;   /*Hurakan average speed calcu-
							 lated by the function of the
							 hurakan engine*/
	GLfloat maxhurakanASpeed;
	GLfloat oldASpeed;
	GLfloat hurakanEPower;   // Hurakan engine power.
	GLfloat hurakanIUPower;  // Hurakan power in IU.
	GLfloat hurakanGravity;  // Hurakan gravity value
	GLfloat hurakanMass;	 // Hurakan mass value with 40
							 // people inside.
	GLfloat hurakanAAccel;	 //Angular acceleration.
	GLfloat hurakanLAccel;	 //Linear acceleration.
	GLfloat counter;
	GLfloat counter2;
	GLfloat angle1;
	GLfloat angle2;
	GLfloat oldangleArm;
	GLfloat velIncrement;
	float angle1increment;
	int hurakanGravityValue; /* Hurakan Gravity value used 
							 to change the gravity. 
							 0 = Earth Gravity, 
							 1 = Moon Gravity, 
							 2 = Mars Gravity, 
							 3 = Venus Gravity */
	int hurakanKeyValue;     /* Hurakan key value used for 
							 change the selected variable.
							 0 = hurakanEPower,
							 1 = hurakanGravity,
							 2 = hurakanMaterial*/
	int hurakanViewMode;	 /* View mode. 0 = both, 
							 1 = Inside Hurakan, 
							 2 = Perspective */
	bool hurakanStatus;		 /* Represent the status of the
							 hurikan. 
							 FALSE = Stopped, 
							 TRUE = Activate */
	int hurakanMaterial;     /*Represent the current material
							 0 = Original Hurakan,
							 1 = Full Steel Hurakan,
							 2 = Full Aluminium Hurakan,
							 3 = Full Wood Hurakan */
	int hurakanAccelFrame;	 // Number of frames to accelerate.
	int hurakanSpeedFrame;
	int hurakanmaxSpeedFrame;
	int i;


// Gravity values
	float Earth = 9.8f;		// Gravity on Earth in m/s.
	float Moon = 1.6f;		// Gravity on The Moon in m/s.
	float Mars = 3.7f;		// Gravity on Mars in m / s.
	float Venus = 8.9f;		// Gravity on Venus in m/s.

// Hurakan Radius
	float hurakanRadius = 10.0f;
	float radtodeg = 360.0f / (float)TWOPI;

// Mass values
	float Original = 17400.0f;
	float Steel = 21060.0f;
	float Aluminium = 8859.0f;
	float Wood = 3309.0f;

// Acceleration time.
	float accelTime = 10.0f;

// Turn numbers
	int Turn;				 // Number of turns done by the
							 // Hurakan.
	GLfloat maxTurns;		 // Maximum number of turns.
	GLfloat accelTurns;
	int NaccelTurns;
	int NTurns;

//--------------VGI Environment: Fi De Variables globals de CEntornVGIView

// Operaciones
public:

// Reemplazos
public:
	virtual void OnDraw(CDC* pDC);  // Reemplazado para dibujar esta vista
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Funcions de c�rrega i activaci� de shaders
	void InitAPI();
	void GetGLVersion(int* major, int* minor);
	void OnInitialUpdate();

// Implementaci�n
public:
	virtual ~CEntornVGIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void CEntornVGIView::configura_Escena();
	void CEntornVGIView::dibuixa_Escena();
	void CEntornVGIView::Barra_Estat();
	void CEntornVGIView::float2CString(float varf);
	int CEntornVGIView::Log2(int num);							// Log2: C�lcul del log base 2 de num
	char * CEntornVGIView::CString2Char(CString entrada);		// Conversi� string CString --> char *
	void CEntornVGIView::Refl_MaterialOff();					// Desactivar Reflexi� de Material
	void CEntornVGIView::Refl_MaterialOn();						// Activar Reflexi� de Material

// VGI Environment: Funcions de c�rrega i activaci� de shaders
	GLuint CEntornVGIView::initializeShaders(CString filename);
	char *CEntornVGIView::textFileRead(char *fn);
	void CEntornVGIView::releaseAllShaders();

// // VGI Environment: Funcions de tractament de teclat en diferents modus
	void CEntornVGIView::Teclat_ColorObjecte(UINT nChar, UINT nRepCnt);
	void CEntornVGIView::Teclat_ColorFons(UINT nChar, UINT nRepCnt);
	void CEntornVGIView::Teclat_Navega(UINT nChar, UINT nRepCnt);
	void CEntornVGIView::Teclat_Pan(UINT nChar, UINT nRepCnt);
	void CEntornVGIView::Teclat_TransEscala(UINT nChar, UINT nRepCnt);
	void CEntornVGIView::Teclat_TransRota(UINT nChar, UINT nRepCnt);
	void CEntornVGIView::Teclat_TransTraslada(UINT nChar, UINT nRepCnt);
	void CEntornVGIView::Teclat_Hurakan(UINT nChar, UINT nRepCnt);

	CMFCStatusBar& GetStatusBar() const
	{
		return ((CMainFrame*)AfxGetMainWnd())->GetStatusBar();
	}

private:

//Rendering Context and Device Context Pointers
	HGLRC     m_hRC;
	CDC*      m_pDC;

// Funciones de asignaci�n de mensajes generadas
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnPaint();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnArxiuObrirFractal();
	afx_msg void OnArxiuObrirFitxerObj();
	afx_msg void OnArxiuObrirFitxer3ds();
	afx_msg void OnVistaMobil();
	afx_msg void OnUpdateVistaMobil(CCmdUI *pCmdUI);
	afx_msg void OnVistaZoom();
	afx_msg void OnUpdateVistaZoom(CCmdUI *pCmdUI);
	afx_msg void OnVistaPolarsX();
	afx_msg void OnUpdateVistaPolarsX(CCmdUI *pCmdUI);
	afx_msg void OnVistaPolarsY();
	afx_msg void OnUpdateVistaPolarsY(CCmdUI *pCmdUI);
	afx_msg void OnVistaPolarsZ();
	afx_msg void OnUpdateVistaPolarsZ(CCmdUI *pCmdUI);
	afx_msg void OnVistaPan();
	afx_msg void OnUpdateVistaPan(CCmdUI *pCmdUI);
	afx_msg void OnVistaOrigenpan();
	afx_msg void OnVistaNavega();
	afx_msg void OnUpdateVistaNavega(CCmdUI *pCmdUI);
	afx_msg void OnVistaOrigennavega();
	afx_msg void OnVistaEixos();
	afx_msg void OnUpdateVistaEixos(CCmdUI *pCmdUI);
	afx_msg void OnProjeccioPerspectiva();
	afx_msg void OnUpdateProjeccioPerspectiva(CCmdUI *pCmdUI);
	afx_msg void OnObjecteCub();
	afx_msg void OnUpdateObjecteCub(CCmdUI *pCmdUI);
	afx_msg void OnObjecteEsfera();
	afx_msg void OnUpdateObjecteEsfera(CCmdUI *pCmdUI);
	afx_msg void OnObjecteTetera();
	afx_msg void OnUpdateObjecteTetera(CCmdUI *pCmdUI);
	afx_msg void OnObjecteTruck();
	afx_msg void OnUpdateObjecteTruck(CCmdUI *pCmdUI);
	afx_msg void OnTransformaTraslacio();
	afx_msg void OnUpdateTransformaTraslacio(CCmdUI *pCmdUI);
	afx_msg void OnTransformaOrigentraslacio();
	afx_msg void OnTransformaRotacio();
	afx_msg void OnUpdateTransformaRotacio(CCmdUI *pCmdUI);
	afx_msg void OnTransformaOrigenrotacio();
	afx_msg void OnTransformaEscalat();
	afx_msg void OnUpdateTransformaEscalat(CCmdUI *pCmdUI);
	afx_msg void OnTransformaOrigenescalat();
	afx_msg void OnTransformaMobilx();
	afx_msg void OnUpdateTransformaMobilx(CCmdUI *pCmdUI);
	afx_msg void OnTransformaMobily();
	afx_msg void OnUpdateTransformaMobily(CCmdUI *pCmdUI);
	afx_msg void OnTransformaMobilz();
	afx_msg void OnUpdateTransformaMobilz(CCmdUI *pCmdUI);
	afx_msg void OnOcultacionsTestvis();
	afx_msg void OnUpdateOcultacionsTestvis(CCmdUI *pCmdUI);
	afx_msg void OnOcultacionsZbuffer();
	afx_msg void OnUpdateOcultacionsZbuffer(CCmdUI *pCmdUI);
	afx_msg void OnOcultacionsBackline();
	afx_msg void OnUpdateOcultacionsBackline(CCmdUI *pCmdUI);
	afx_msg void OnIluminacioLlumfixe();
	afx_msg void OnUpdateIluminacioLlumfixe(CCmdUI *pCmdUI);
	afx_msg void OnIluminacioFilferros();
	afx_msg void OnUpdateIluminacioFilferros(CCmdUI *pCmdUI);
	afx_msg void OnIluminacioPlana();
	afx_msg void OnUpdateIluminacioPlana(CCmdUI *pCmdUI);
	afx_msg void OnIluminacioGouraud();
	afx_msg void OnUpdateIluminacioGouraud(CCmdUI *pCmdUI);
	afx_msg void OnMaterialEmissio();
	afx_msg void OnUpdateMaterialEmissio(CCmdUI *pCmdUI);
	afx_msg void OnMaterialAmbient();
	afx_msg void OnUpdateMaterialAmbient(CCmdUI *pCmdUI);
	afx_msg void OnMaterialDifusa();
	afx_msg void OnUpdateMaterialDifusa(CCmdUI *pCmdUI);
	afx_msg void OnMaterialEspecular();
	afx_msg void OnUpdateMaterialEspecular(CCmdUI *pCmdUI);
	afx_msg void OnIluminacioTextures();
	afx_msg void OnUpdateIluminacioTextures(CCmdUI *pCmdUI);
	afx_msg void OnIluminacioTexturaFitxerimatge();
	afx_msg void OnUpdateIluminacioTexturaFitxerimatge(CCmdUI *pCmdUI);
	afx_msg void OnLlumsLlumambient();
	afx_msg void OnUpdateLlumsLlumambient(CCmdUI *pCmdUI);
	afx_msg void OnLlumsLlum0();
	afx_msg void OnUpdateLlumsLlum0(CCmdUI *pCmdUI);
	afx_msg void OnShadersSense();
	afx_msg void OnUpdateShadersSense(CCmdUI *pCmdUI);
	afx_msg void OnShadersGouraud();
	afx_msg void OnUpdateShadersGouraud(CCmdUI *pCmdUI);
	afx_msg void OnShadersPhong();
	afx_msg void OnUpdateShadersPhong(CCmdUI *pCmdUI);
	afx_msg void OnVistaSatelit();
	afx_msg void OnUpdateVistaSatelit(CCmdUI *pCmdUI);
	afx_msg void OnProjectionHurakan();
	afx_msg void OnUpdateProjectionHurakan(CCmdUI *pCmdUI);
	afx_msg void OnObjectHurakan();
	afx_msg void OnUpdateObjectHurakan(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // Versi�n de depuraci�n en EntornVGIView.cpp
inline CEntornVGIDoc* CEntornVGIView::GetDocument() const
   { return reinterpret_cast<CEntornVGIDoc*>(m_pDocument); }
#endif

