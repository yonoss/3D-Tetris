/*
3DTetris: it is a 3D version of the well known 2D game Tetris
Made by: Alin Aron Oana

*/
//--------------------------------------------------------------------------------------------------


#include "3dTetris.h"


#include "objxload.cpp"



//--------------------------------------------------------------------------------------------------
//-------------------------- Variable---------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
#define NUM_BUFFERS 11

// Maximum emissions we will need.
#define NUM_SOURCES 11

// These index the buffers and sources.
#define MSOUND      0
#define GSOUND      1
#define BUTTON      2
#define CHANGE      3
#define LEVEL       4
#define BLOCKM      5
#define BLOCKR      6
#define BLOCKD      7
#define FREE        8
#define ESC         9
#define GAMEOVER    10
#define M_PI    3.141592653589793238462643383279502884197

ALint play;

char sfilen[][35]={											//sounds path 
	"data/sounds/game.wav",
	"data/sounds/test.wav",
	"data/sounds/blip2.wav",
	"data/sounds/blip3.wav",
	"data/sounds/hockey_organ.wav",
	"data/sounds/Rot.wav",
	"data/sounds/Flip2.wav",
	"data/sounds/Vb.wav",
	"data/sounds/test.wav",
	"data/sounds/drip.wav",
	"data/sounds/gong.wav",
	
	};
ALuint Buffer;
// Buffers hold sound data.
ALuint Buffers[NUM_BUFFERS];

// Sources are points of emitting sound.
ALuint Sources[NUM_SOURCES];
/*
// Position of the source sounds.
ALfloat SourcesPos[NUM_SOURCES][3];

// Velocity of the source sounds.
ALfloat SourcesVel[NUM_SOURCES][3];
*/
// Position of the source sounds.
ALfloat SourcesPos[]={ 0.0, 0.0, 0.0 };

// Velocity of the source sounds.
ALfloat SourcesVel[]={ 0.0, 0.0, 0.0 };

// Position of the listener.
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

// Velocity of the listener.
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

// Orientation of the listener. (first 3 elements are "at", second 3 are "up")
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

//---------------------------------------------------------------------------------------------------
//             Finish OpenAL vars
//---------------------------------------------------------------------------------------------------
// light parameters
GLfloat light_ambient[] = { 0.7, 0.7, 0.7, 0.0 };
GLfloat light_diffuse[] = { 0.3, 0.3, 0.3, 0.0 };
GLfloat light_specular[] = { 0.8, 0.8, 0.8, 0.0 };
GLfloat light_position[] = { 5.0, 20.0, 5.0, 1.0 };
GLfloat light_position2[] = { 5.0, -20.0, 5.0, 1.0 };
GLfloat light_position3[] = { -3.0, 3.0, 4.0, 1.0 };
GLfloat light_position4[] = { 4.0, 3.0, 4.0, 1.0 };


#define Yi      38											//initial camera position
#define Zi      60
#define M_PI    3.141592654
#define TWOPI 6.283185308
#define MHeight 12           //maximum height of the blocks
int eyey=38;
int eyez=60;
int psound=0;                    // sound flags
int bsound=0;

GLUquadricObj *quadratic;	// Storage For Our Quadratic Objects

struct gl_texture_t			//texture structure
{
  GLsizei width;
  GLsizei height;

  GLenum format;
  GLint internalFormat;
  GLuint id;

  GLubyte *texels;
};

GLuint texId;	


char setText[][35]={                         //settings text
	"Easy 8 X 8",
	"Hard 16 X 16",
	};	
#define Nlev      19						//number of levelss 
int lspeedT[19]={40,35,33,31,30,30,30,29,27,26,25,24,23,20,20,15,15,10,8};	//level speed				

#define Ntex      41                                        //number of textures
GLuint	texture[Ntex];										//holds the textures

int buttonPoz[][4]={{307,717,154,230},						//stores buttons position
					{307,717,269,343},
					{307,717,384,459},
					{307,717,499,576},
					{307,717,613,690}};

char filen[][35]={											//the path for the textures
	"",    
	"",
	"",
	"data/texture/blocks/ist.jpg",
	"data/texture/fire/Particle.jpg",
	"data/texture/blocks/nit.JPG",
	"data/texture/menu/me.JPG",
	"data/texture/menu/sd.JPG",
	"data/texture/menu/su.JPG",
	"data/texture/menu/od.JPG",
	"data/texture/menu/ou.JPG",
	"data/texture/menu/ad.JPG",
	"data/texture/menu/au.JPG",
	"data/texture/menu/ed.JPG",
	"data/texture/menu/eu.JPG",
	"data/texture/menu/setdown.JPG",
	"data/texture/menu/setup.JPG",
	"data/texture/menu/au.JPG",
	"data/texture/menu/au.JPG",
	"data/texture/floor/floor.JPG",
	"data/texture/blocks/rocks.JPG",
	"data/texture/blocks/metal.JPG",
	"data/texture/world/W1.JPG",    
	"data/texture/world/W2.JPG",
	"data/texture/world/W3.JPG",
	"data/texture/world/W4.JPG",
	"data/texture/world/W5.JPG",
	"data/texture/world/W6.JPG",
	"data/texture/world/W7.JPG",    
	"data/texture/world/W8.JPG",
	"data/texture/world/W9.JPG",
	"data/texture/world/W10.JPG",
	"data/texture/world/W11.JPG",
	"data/texture/world/W12.JPG",
	"data/texture/world/W13.JPG",    
	"data/texture/world/W14.JPG",
	"data/texture/world/W15.JPG",
	"data/texture/world/W16.JPG",
	"data/texture/world/W17.JPG",
	"data/texture/world/W18.JPG",
	"data/texture/world/W19.JPG"
	}; 
					
char keysD[][45]={											//Controls menu text
	"[up key]",   
	"[down key]",
	"[left key]",
	"[right key]",
	"[4]",
	"[1]",
	"[5]",
	"[2]",
	"[6]",
	"[3]",
	"[mouse right ckick] or [0]",
	"[r]",
	"[p]",
	"[i]",
	"[mouse left ckick + move]",
	"[mouse wheel]",
	"[Esc]"
	};
char keysT[][45]={											//Controls menu text
	" - move block forward",   
	" - move block backward",
	" - move block left",
	" - move block right",
	" - rotate block counterclockwise on X",
	" - rotate block clockwise on X",
	" - rotate block counterclockwise on Y",
	" - rotate block clockwise on Y",
	" - rotate block counterclockwise on Z",
	" - rotate block clockwise on Z",
	" - put the block down",
	" - reset camera position",
	" - game pause",
	" - show the empty spaces",
	" - camera move",
	" - zoom in / out",
	" - return to main menu"
	};

											
int xDimension=8,yDimension=16;zDimension=8;				//The dimensions of the world

int Mnu[5]={0,1,1,1,1};										//store the main menu state
int Snu[2]={1,0};										    //store the settings menu state
int level=1;
int score=0;												//Score value
int Lsatus[Nlev+1];                                //store the levels flags
int timer=0;                                                //display timer "Level No"
int sound=0;												//sound flag
int butt=0;                                               //right button click flag
int endGameCount=0;										    // end game counter (for how long the end game message will apear on the screen)
int lfinish=400;											//level maximum score
int q;														// global variable(general use)
int angl=0;


BOOL firstTime=TRUE;                                        // bool variable to acces bock initialisation;
BOOL done=TRUE;												// bool variable to exit loop
BOOL Omenu=FALSE;											// bool variable to exit Option menu		
BOOL Amenu=FALSE;											// bool variable to exit About menu
BOOL Mmenu=TRUE;
BOOL pause=FALSE;											// bool variable to enter Pause mode
BOOL Smenu=FALSE;											// bool variable to exit Settings menu
BOOL GameEnd=FALSE;										    // end game bool variable 
BOOL ffTime=TRUE;											// first time plaeing the game over sound
BOOL fistS=TRUE;
BOOL invrt=FALSE;											    // invert flag if 1 draw the static blocks if 2 draw the empty spaces

static BOOL keystate[256];                                   //keyboard map

int dimchange=0;     										// has the floor dimension been changed

int cnt=0;													//counters used to generate a delay
int cnttimer=0;												

int maxHeight=0;											//stores the masimum height of the static world
int reset;													//reset flag
int lSpeed=50;												//stores the curent level blocks speed

int moving, startx, starty;                                 //used for camera movement
int last=0;													//store the last random number
int xPosition=0,yPosition=0,zPosition=0;                    //dropping block's position on x,y,z


float mX=0;													//mouse coords	
float mY=0;

GLfloat NextBlockAngle = 0;									//the angle of rotation for the next bock fig. top left corner 											
GLfloat angle = 0;										    // camera angle on x in degrees 
GLfloat angle2 = 0;										    // camera angle on y in degrees


static GLfloat ambientLight[] = { 0.4, 0.4, 0.4, 1.0 };				//not used anymore
static GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
static GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat positiona[] = { 1, 1, 1, 0.0};
static GLfloat positionb[] = { 1, 1, 1, 1.0};
static GLfloat positionc[] = { 1, 1, 1,1.0};
static GLfloat positiond[] = { 1, 1, 1, 1.0};

GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };


int moveBloc[4][4][4];                                      //stores in the structure of the moving block: moveBloc[y][x][z]
int tempBloc[4][4][4];										//a temporary block structure

int dist;													



//+++++++++++++++++++++++++++++
int world[30][30][30];										//Game playground  declaration [y][x][z]

int worldHeight[30][30];									//stores the highest position on y in the static world; will be use to see what is under the falling block

//+++++++++++++++++++++++++++++
int futurebloc[4][4][4];
int bloc[4][4][4];

int blockLPoints[4][4];                    //stores the blocks lovest points

int Bno;									//number of blocks
int data[64][64];						    //used to store blocks data

char str[43];								//general strings (especialy used to print the level and score messages on the screen)
char str1[43];
char points[33];							

int i=567;									

GLMmodel* cone;
GLMmodel* frame;
GLMmodel* tub;
GLMmodel* prop;
GLMmodel* banner;
GLMmodel* circle;
GLMmodel* banner1;
GLMmodel* circle1;
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
#define	MAX_PARTICLES	5000	// Number Of Particles To Create

typedef struct						// Create A Structure For Particle
{
	BOOL	active;					// Active (Yes/No)
	float	life;					// Particle Life
	float	fade;					// Fade Speed
	float	r;						// Red Value
	float	g;						// Green Value
	float	b;						// Blue Value
	float	x;						// X Position
	float	y;						// Y Position
	float	z;						// Z Position
	float	xi;						// X Direction
	float	yi;						// Y Direction
	float	zi;						// Z Direction
	float	xg;						// X Gravity
	float	yg;						// Y Gravity
	float	zg;						// Z Gravity
}
particles;							// Particles Structure

particles particle[MAX_PARTICLES];	// Particle Array (Room For Particle Info)



GLuint	loop;						// Misc Loop Variable
GLuint	col;						// Current Color Selection
GLuint	delay;						// Rainbow Effect Delay

BOOL	active=TRUE;				// Window Active Flag Set To TRUE By Default
BOOL	fullscreen=TRUE;			// Fullscreen Flag Set To Fullscreen Mode By Default
BOOL	rainbow=TRUE;				// Rainbow Mode?
BOOL	sp;							// Spacebar Pressed?
BOOL	rp;							// Enter Key Pressed?

float	slowdown=0.2f;				// Slow Down Particles
float	xspeed;						// Base X Speed (To Allow Keyboard Direction Of Tail)
float	yspeed;						// Base Y Speed (To Allow Keyboard Direction Of Tail)
float	zoom=-40.0f;				// Used To Zoom Out


//--------------------------------------------------------------------------------------------------
//--------------------Functions declaration---------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cubr(float x, float y, float z);									//draw the cub unit wich start at x, y, z used to draw only the empty spaces when "i" is pressed

BOOL checkway(int sx,int sy,int sz);                    // checks to see if the shadow can be casted or not
int calcangl();												// calculate the proppaler rotateing angle
GLMmodel* loadOBJ(char* filename);                              //loads a object;  returns, GLMmodel* - pointer to model
void updateMenuTable(int i);									//updates the menu table acording with the new coords
int checkMvBP();											    // checks if mouse cursor is over a button and returns button's position
int calcCos(float angle);										// checks the cos sign
int calcCos(float angle);                                       // checks the sin sign
int checkCadran(float angle);                                   // chechs trigonometric circle position
void CSphere(float cx,float cy,float cz,double r,int n);		//Create a sphere centered at c, with radius r, and precision 
void recheckHeight();										    // generates the worlds height bitmap
int trans();												    //return the Y diference (for the camera view)
void playSound(int so);											// plays the sound wich has the so index   
void DisplayOpenALError(char* _string, int error);				//handels the sound errors
int LoadAndAssignWAV(char* _fileName, ALuint _buffer);			//load a sound file
ALboolean LoadALData();											//initialize the soun vars
void SetListenerValues();                                       // sets the values of the observer
void drawStringBig(char *s);									// draw string 
void checkLevel();                                              //checks the curent level
void wCub(int j, int i, int k);								    // draw static unit cube accordingly to the bitmap
void genShadow(float x,float y,float z);                        // draw the shadow unit
void drawShadow();                                              // draw the fallsing block shadow;
void drawButton(float x, float y, float z, int but, int state);	//draw buttons; but=button name; state= up/1 or down/0 		
void doInit();												    //reinitialize the game vars
void getDataFromFile(char* file);							    //gets the blocks structure from file 
void futureToCurent();											//generate the new curent block;
void dataToBlock(int bl);										// transfer data to the block structure
GLuint LoadTextureRAW( const char * filename, int wrap );		// load a 512x512 RGB .RAW file as a texture		
void removePlaneFromWorld(int plane,int X,int Y,int Z);			// removes the i-th plane from the world 
void checkPlanes();												//checks for complet planes in the world space				
void checkFinish();												// check if the pile has reached the top of the play ground
void resetParams();												//Resets the parameters to the original value
int checkCollisionsMove(int X,int Y, int Z);					// check if there are any collisions betwen the new structure and the world elements			
int getFreeBottom();											// returns the free space available in the bottom side of the moveing block
int getFreeFront();												// returns the free space available in the front side of the moveing block
int getFreeBack();												// returns the free space available in the back side of the moveing block
int getFreeLeft();												// returns the free space available in the left side  of the moveing block
int getFreeRight();												// returns the free space available in the right side of the moveing block
int checkCollisions(tempBloc);									// check if there are any collisions betwen the new structure and the world elements			
int checkRotate(int text);										//Checks if a rotation is valid or not
void convertBlockToStaticWorld();								//Converts bock's coords. into static ones
int distantsToClosestCub(); 									//returns the smallest distance to the cubs below
void blocksLowestPoints();										//creates a map of moveing block lowest points
void tempToTemp(int tblock[4][4][4]);							// replace the temp block structure with the new structure
void tempToMoveBlock(int tblock[4][4][4]);						// replace the moving block structure with the new structure
void generateNewBlock();										//generates a new block
void initBLP();													//initialization of the blockLPoints matrix
void initVars();												//initialization of the variables
void initWorld();												// initialozation of the world
void initMBlock(int tblock[4][4][4]);							//initialize the moving block structure
void initTBlock();												//initialize the temporary block structure	
void rotateBlocYCCW(int modBlock[4][4][4], int m);				//rotates the falling blocks; 1 for movingblock; 2 for a temporary block
void rotateBlocYCW(int modBlock[4][4][4], int m);				//rotates the falling blocks
void rotateBlocXCCW(int modBlock[4][4][4], int m);				//rotates the falling blocks
void rotateBlocXCW(int modBlock[4][4][4], int m);				//rotates the falling blocks
void rotateBlocZCCW(int modBlock[4][4][4], int m);				//rotates the falling blocks
void rotateBlocZCW(int modBlock[4][4][4], int m);				//rotates the falling blocks
static void drawFloor();										//draw the game floor                          
void display();													//draw the scene
void cub(float x, float y, float z);							//draw the cube unit 
static void drawBlock(float x, float y, float z, int a);		//draw the blocks a=1=> moving block;a=0=> futureblock
static void drawWorld(BOOL a);										//draw the static cubs
void drawGrid();												// draw a help gridd, takes as parameters the dimensions of the wold
void NormalKeys(unsigned char key, int x, int y);				//manage the normal keys events
void SpecialKeys(int key, int x, int y);						//manage the special keys events
static void mouse(int button, int state, int x, int y);			//controls mouse movement
static void motion(int x, int y);								//rotates the scene according with the mouse movements
void init();													//initialize the environment
void createWindowa();											//creates OpenGL window
static void idle(void);											//game's loop


//--------------------------------------------------------------------------------------------------
//-------------------Functions implementation-------------------------------------------------------
void DrawGLFire()										// Here's Where We Do All The Drawing
{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glShadeModel(GL_SMOOTH);
	glEnable( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, texture[4]);
//	glLoadIdentity();										// Reset The ModelView Matrix
	glPointSize(8);
	for (loop=0;loop<MAX_PARTICLES;loop++)					// Loop Through All The Particles
	{
		if (particle[loop].active)							// If The Particle Is Active
		{
			
			float x=particle[loop].x;						// Grab Our Particle X Position
			float y=particle[loop].y;						// Grab Our Particle Y Position
			float z=particle[loop].z+zoom;					// Particle Z Pos + Zoom

			//glEnable( GL_TEXTURE_2D );
			//glBindTexture(GL_TEXTURE_2D, texture[19]);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glColor4f(1,1,1,0.04);			
				glBegin(GL_POINTS);
					glVertex3f(x,y,z);
				glEnd();
			glDisable(GL_BLEND);
			//glDisable( GL_TEXTURE_2D );
			if(!pause)
			{
			particle[loop].x+=particle[loop].xi/(slowdown*6000);// Move On The X Axis By X Speed
			particle[loop].y+=particle[loop].yi/(slowdown*1000);// Move On The Y Axis By Y Speed
			particle[loop].z+=particle[loop].zi/(slowdown*6000);// Move On The Z Axis By Z Speed

			particle[loop].xi+=particle[loop].xg;			// Take Pull On X Axis Into Account
			particle[loop].yi+=particle[loop].yg;			// Take Pull On Y Axis Into Account
			particle[loop].zi+=particle[loop].zg;			// Take Pull On Z Axis Into Account
			particle[loop].life-=particle[loop].fade;		// Reduce Particles Life By 'Fade'

			if (particle[loop].life<0.0f)					// If Particle Is Burned Out
			{
				particle[loop].life=1.0f;					// Give It New Life
				particle[loop].fade=(rand()%100)/1000.0f+0.003f;	// Random Fade Value
				particle[loop].x=0.0f;						// Center On X Axis
				particle[loop].y=0.0f;						// Center On Y Axis
				particle[loop].z=0.0f;						// Center On Z Axis
				particle[loop].xi=xspeed+((rand()%60)-32.0f);	// X Axis Speed And Direction
				particle[loop].yi=yspeed+((rand()%60)-30.0f);	// Y Axis Speed And Direction
				particle[loop].zi=((rand()%60)-30.0f);	// Z Axis Speed And Direction
			}
			}

			
		}
    }
	
	glDisable( GL_TEXTURE_2D );	
									
}
//---------------------------------
//---------------------------------

BOOL checkway(int sx,int sy,int sz)                    // checks to see if the shadow can be casted or not
{
	BOOL flg=TRUE;
	int i=sy+1;
	while ((i<=worldHeight[sx][sz])&&(flg==TRUE))
	{
		if(world[i][sx][sz]==1)
		{
			flg=FALSE;
			i=13;
		}
		i++;
	}
	

	return flg;
}

//---------------------------------
//---------------------------------

int calcangl()                                // calculate the proppaler rotateing angle
{
	int rez;
	if(!pause)
	{
		angl+=10;
		if(angl>360)
		{
			angl=angl%360;
		}
	}
	rez=angl;
	return rez;
}												

//---------------------------------
//---------------------------------

void drawFlr(GLMmodel * object) // draw the game floor
{
	// draw the board

	glmDraw(object, GLM_SMOOTH);

}

//---------------------------------
//---------------------------------

GLMmodel* loadOBJ(char* filename)  //loads a object;  returns, GLMmodel* - pointer to model
{
	GLMmodel* aModel = NULL; 
	
	if (!aModel) {
		aModel = glmReadOBJ(filename);
		if (!aModel)
			exit(0);
		
		glmFacetNormals(aModel);
		glmVertexNormals(aModel, 90.0);
	}
	
	return aModel;
}

//---------------------------------
//---------------------------------

int checkMvBP()   // checks if mouse cursor is over a button and returns button's position
{
	
	if((mX>=buttonPoz[0][0])&&(mX<=buttonPoz[0][1])&&(mY>=buttonPoz[0][2])&&(mY<=buttonPoz[0][3]))
		return 1;
	if((mX>=buttonPoz[1][0])&&(mX<=buttonPoz[1][1])&&(mY>=buttonPoz[1][2])&&(mY<=buttonPoz[1][3]))
		return 2;
	if((mX>=buttonPoz[2][0])&&(mX<=buttonPoz[2][1])&&(mY>=buttonPoz[2][2])&&(mY<=buttonPoz[2][3]))
		return 3;
	if((mX>=buttonPoz[3][0])&&(mX<=buttonPoz[3][1])&&(mY>=buttonPoz[3][2])&&(mY<=buttonPoz[3][3]))
		return 4;
	if((mX>=buttonPoz[4][0])&&(mX<=buttonPoz[4][1])&&(mY>=buttonPoz[4][2])&&(mY<=buttonPoz[4][3]))
		return 5;
	else return 0;
} 

//---------------------------------
//---------------------------------

void updateMenuTable(int cell)   //updates the menu table acording with the new coords
{
	int i;
	for(i=0;i<5;i++)
	{
		Mnu[i]=1;
	}
	
		Mnu[cell-1]=0;

}


//---------------------------------
//---------------------------------

static struct gl_texture_t * ReadJPEGFromFile (const char *filename)  // decripts jpg format
{
  struct gl_texture_t *texinfo = NULL;
  FILE *fp = NULL;
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  JSAMPROW j;
  int i;

  /* Open image file */
  fp = fopen (filename, "rb");
  if (!fp)
    {
      fprintf (stderr, "error: couldn't open \"%s\"!\n", filename);
      return NULL;
    }

  /* Create and configure decompressor */
  jpeg_create_decompress (&cinfo);
  cinfo.err = jpeg_std_error (&jerr);
  jpeg_stdio_src (&cinfo, fp);

  /*
   * NOTE: this is the simplest "readJpegFile" function. There
   * is no advanced error handling.  It would be a good idea to
   * setup an error manager with a setjmp/longjmp mechanism.
   * In this function, if an error occurs during reading the JPEG
   * file, the libjpeg abords the program.
   * See jpeg_mem.c (or RTFM) for an advanced error handling which
   * prevent this kind of behavior (http://tfc.duke.free.fr)
   */

  /* Read header and prepare for decompression */
  jpeg_read_header (&cinfo, TRUE);
  jpeg_start_decompress (&cinfo);

  /* Initialize image's member variables */
  texinfo = (struct gl_texture_t *)
    malloc (sizeof (struct gl_texture_t));
  texinfo->width = cinfo.image_width;
  texinfo->height = cinfo.image_height;
  texinfo->internalFormat = cinfo.num_components;

  if (cinfo.num_components == 1)
    texinfo->format = GL_LUMINANCE;
  else
    texinfo->format = GL_RGB;

  texinfo->texels = (GLubyte *)malloc (sizeof (GLubyte) * texinfo->width
			       * texinfo->height * texinfo->internalFormat);

  /* Extract each scanline of the image */
  for (i = 0; i < texinfo->height; ++i)
    {
      j = (texinfo->texels +
	((texinfo->height - (i + 1)) * texinfo->width * texinfo->internalFormat));
      jpeg_read_scanlines (&cinfo, &j, 1);
    }

  /* Finish decompression and release memory */
  jpeg_finish_decompress (&cinfo);
  jpeg_destroy_decompress (&cinfo);

  fclose (fp);
  return texinfo;
}

//---------------------------------
//---------------------------------

GLuint loadJPEGTexture (const char *filename)	// load a jpg texture
{
  struct gl_texture_t *jpeg_tex = NULL;
  GLuint tex_id = 0;

  jpeg_tex = ReadJPEGFromFile (filename);

  if (jpeg_tex && jpeg_tex->texels)
    {
      /* Generate texture */
      glGenTextures (1, &jpeg_tex->id);
      glBindTexture (GL_TEXTURE_2D, jpeg_tex->id);

      /* Setup some parameters for texture filters and mipmapping */
      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

#if 0
      glTexImage2D (GL_TEXTURE_2D, 0, jpeg_tex->internalFormat,
		    jpeg_tex->width, jpeg_tex->height, 0, jpeg_tex->format,
		    GL_UNSIGNED_BYTE, jpeg_tex->texels);
#else
      gluBuild2DMipmaps (GL_TEXTURE_2D, jpeg_tex->internalFormat,
			 jpeg_tex->width, jpeg_tex->height,
			 jpeg_tex->format, GL_UNSIGNED_BYTE, jpeg_tex->texels);
#endif

      tex_id = jpeg_tex->id;

      /* OpenGL has its own copy of texture data */
      free (jpeg_tex->texels);
      free (jpeg_tex);
    }

  return tex_id;
}


//---------------------------------
//---------------------------------
void LJpegT()		// loads Ntex jpg textures
{
	for( i=3;i<Ntex;i++)
	{
		texture[i] = loadJPEGTexture (filen[i]);
	 
	}
}


//---------------------------------
//---------------------------------

static void cleanup ()
{
  glDeleteTextures (1, &texId);
}


//---------------------------------
//---------------------------------

void CSphere(float cx,float cy,float cz,double r,int n)   //Create a sphere centered at c, with radius r, and precision n
{
   int i,j;
   double theta1,theta2,theta3;
   float ex,ey,ez,px,py,pz;

   if (r < 0)
      r = -r;
   if (n < 0)
      n = -n;
   if (n < 4 || r <= 0) {
      glBegin(GL_POINTS);
      glVertex3f(cx,cy,cz);
      glEnd();
      return;
   }

   for (j=0;j<n/2;j++) {
      theta1 = j * TWOPI / n - M_PI/2;
      theta2 = (j + 1) * TWOPI / n - M_PI/2;

      glBegin(GL_QUAD_STRIP);
      for (i=0;i<=n;i++) {
         theta3 = i * TWOPI / n;

         ex = cos(theta2) * cos(theta3);
         ey = sin(theta2);
         ez = cos(theta2) * sin(theta3);
         px = cx + r * ex;
         py = cy + r * ey;
         pz = cz + r * ez;

         glNormal3f(ex,ey,ez);
         glTexCoord2f(i/(double)n,2*(j+1)/(double)n);
         glVertex3f(px,py,pz);

         ex = cos(theta1) * cos(theta3);
         ey = sin(theta1);
         ez = cos(theta1) * sin(theta3);
         px = cx + r * ex;
         py = cy + r * ey;
         pz = cz + r * ez;

         glNormal3f(ex,ey,ez);
         glTexCoord2f(i/(double)n,2*j/(double)n);
         glVertex3f(px,py,pz);
      }
      glEnd();
   }
}

//---------------------------------
//---------------------------------

int calcCos(float an)               // checks the cos sign
{

	if(cos(an*M_PI/180)>=0)
	{
		return 1;
	}
	else 
		return 0;
}

//---------------------------------
//---------------------------------

int calcSin(float an)          // checks the sin sign
{

	if(sin(an*M_PI/180)>=0)
		return 1;
	else 
		return 0;
}

//---------------------------------
//---------------------------------

int checkCadran(float ang)       // chechs trigonometric circle position
{
	int cs;
	int sn;
	cs=calcCos(ang);
	sn=calcSin(ang);
	if(cs==1)
	{
		if(sn==1)
		{
			return 1;
		}
		else
			return 4;
	}
	else
	{
		if(sn==1)
		{
			return 2;
		}
		else
			return 3;
	}

}

//---------------------------------
//---------------------------------


void printString(GLfloat x, GLfloat y,char *f)											// print the string at the given location
{
	glColor3f(0.7,0.7,0.7);
	glRasterPos2f(x, y);
	drawStringBig(f);
	glColor3f(0.7,0.7,0.7);
	glRasterPos2f(x-0.003, y);
	drawStringBig(f);
	glColor3f(0,0,0);
	glRasterPos2f(x-0.0015, y);
	drawStringBig(f);
}

//---------------------------------
//---------------------------------

void recheckHeight()										// generates the worlds height pitmap
{
	int i;
	int j;
	int k;
		for(j=0;j<xDimension;j++)
		{
			for(k=0;k<zDimension;k++)
			{				
				worldHeight[j][k]=0;
				for(i=0;i<yDimension;i++)								
				{
					if(world[i][j][k]==1)
					{
						if(worldHeight[j][k]<=i)
						{
							worldHeight[j][k]=i+1;
						}
					}
				}
			}
			
		}
}

//---------------------------------
//---------------------------------

int trans()    //return the Y diference (for the camera view)
{
	int rez;
	rez=Yi-eyey;
	return rez;
}

//---------------------------------
//---------------------------------

void playSound(int so)    // plays the sound    
{
		alGetSourcei(Sources[so], AL_SOURCE_STATE, &play);
	   if (play != AL_PLAYING)
                {
					alSourcePlay(Sources[so]);
				}
}

//---------------------------------
//---------------------------------

void DisplayOpenALError(char* _string, int error)   //handels the sound errors
{
	switch (error)
	{
	case AL_INVALID_NAME:
		printf("%s Invalid Name", _string);
		break;
	case AL_INVALID_ENUM:
		printf("%s Invalid Enum", _string);
		break;
	case AL_INVALID_VALUE:
		printf("%s Invalid Value: %d", _string,error);
		break;
	case AL_INVALID_OPERATION:
		printf("%s Invalid Operation", _string);
		break;
	case AL_OUT_OF_MEMORY:
		printf("%s Out Of Memory", _string);
		break;
	default:
		printf("*** ERROR *** Unknown error case in DisplayOpenALError\n");
		break;
	};
}

//---------------------------------
//---------------------------------

int LoadAndAssignWAV(char* _fileName, ALuint _buffer)  //load a sound file
{
	int			error;
	ALenum		format; 
	ALsizei		size;
	ALsizei		freq; 
	ALboolean	loop;
	ALvoid*		data;

	// Load in the WAV file from disk
	alutLoadWAVFile(_fileName, &format, &data, &size, &freq, &loop); 
	if ((error = alGetError()) != AL_NO_ERROR) 
	{ 
		DisplayOpenALError("alutLoadWAVFile : ", error);	
		return 0; 
	}

	// Copy the new WAV data into the buffer
	alBufferData(_buffer,format,data,size,freq); 
	if ((error = alGetError()) != AL_NO_ERROR) 
	{ 
		DisplayOpenALError("alBufferData :", error); 
		return 0; 
	}

	// Unload the WAV file
	alutUnloadWAV(format,data,size,freq); 
	if ((error = alGetError()) != AL_NO_ERROR) 
	{ 
		DisplayOpenALError("alutUnloadWAV :", error);
		return 0;
	}

	return 1;
}

//---------------------------------
//---------------------------------

ALboolean LoadALData()   //initialize the soun vars
{
    // Variables to load into.
	int i;
	int error;
    
	ALenum format;
    ALsizei size;
    ALvoid* data;
    ALsizei freq;
    ALboolean loop;

    // Load wav data into buffers.

    alGenBuffers(NUM_BUFFERS, Buffers);
	
    if ((error = alGetError()) != AL_NO_ERROR) 
	{ 
		DisplayOpenALError("alGenBuffers :", error);
		return 0;
	}

    for(i=0;i<NUM_BUFFERS;i++)
	{
		if (!LoadAndAssignWAV(sfilen[i], Buffers[i]))
		{
			// Error loading in the WAV so quit
			alDeleteBuffers(NUM_BUFFERS, Buffers); 
			return 0;
		}
	}
	
    


    // Bind buffers into audio sources.

    alGenSources(NUM_SOURCES, Sources);
	if ((error = alGetError()) != AL_NO_ERROR) 
	{ 
		DisplayOpenALError("alGenSource :", error); 
		return 0; 
	}
    

   for(i=0;i<2;i++)
		{
			alSourcei(Sources[i], AL_BUFFER,   Buffers[i]  );
			alSourcef(Sources[i], AL_PITCH,    1.0              );
			alSourcef(Sources[i], AL_GAIN,     0.4              );
			alSourcefv(Sources[i], AL_POSITION, SourcesPos);
			alSourcefv(Sources[i], AL_VELOCITY, SourcesVel);
			alSourcei(Sources[i], AL_LOOPING,  AL_TRUE          );
		}
	for(i=2;i<NUM_BUFFERS;i++)
		{
			alSourcei(Sources[i], AL_BUFFER,   Buffers[i]  );
			alSourcef(Sources[i], AL_PITCH,    1.0            );
			alSourcef(Sources[i], AL_GAIN,     1.0            );
			alSourcefv(Sources[i], AL_POSITION, SourcesPos);
			alSourcefv(Sources[i], AL_VELOCITY, SourcesVel);
			alSourcei(Sources[i], AL_LOOPING,  AL_FALSE       );
		}
     return AL_TRUE;
}

//---------------------------------
//---------------------------------

void SetListenerValues()               // sets the values of the observer
{
    alListenerfv(AL_POSITION,    ListenerPos);
    alListenerfv(AL_VELOCITY,    ListenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOri);
}

//---------------------------------
//---------------------------------

void KillALData()                     // destroy all the sound buffers and sources 
{
    alDeleteBuffers(NUM_BUFFERS, &Buffers[0]);
    alDeleteSources(NUM_SOURCES, &Sources[0]);
    alutExit();
}

//---------------------------------
//---------------------------------

void checkLevel()                                              //checks the curent level
{
	int rez;
	rez=score/lfinish;
	if(rez<=18)
	{
		level=rez+1;
		lSpeed=lspeedT[rez];
	}
	else
	{
		level=Nlev;
		lSpeed=lspeedT[Nlev-1];
	}	
}

//---------------------------------
//---------------------------------

void wCub(int x, int y, int z)  // draw static unit cube accordingly to the bitmap (draw only the visible faces)
{	
	glEnable( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, texture[21]);
	glBegin(GL_QUADS);
		if(world[y][x][z-1]!=1)
		{
			glColor3f(0.7,0.7,0.7);	                                 //draw back face
			glTexCoord2f(0.0f, 0);glVertex3f(x,y,z);
			glTexCoord2f(1.0f, 0.0f);glVertex3f(x,y+1.,z);
			glTexCoord2f(1, 1);glVertex3f(x+1.,y+1.,z);
			glTexCoord2f(0, 1.0f);glVertex3f(x+1.,y,z);
			
			
		}
		if((world[y-1][x][z]!=1)&&(i=!0))
		{
			glColor3f(0.5,0.5,0.5);								//draw bottom face
			glTexCoord2f(0.0f, 0);glVertex3f(x,y,z);
			glTexCoord2f(1.0f, 0.0f);glVertex3f(x+1.,y,z);
			glTexCoord2f(1, 1);glVertex3f(x+1.,y,z+1.);
			glTexCoord2f(0, 1.0f);glVertex3f(x,y,z+1.);
		
		}
		if(world[y][x][z+1]!=1)
		{
			glColor3f(0.7,0.7,0.7);									//draw front face
			glTexCoord2f(0.0f, 0);glVertex3f(x,y,z+1.);
			glTexCoord2f(1.0f, 0.0f);glVertex3f(x+1.,y,z+1);
			glTexCoord2f(1, 1);glVertex3f(x+1.,y+1,z+1.);
			glTexCoord2f(0, 1.0f);glVertex3f(x,y+1.,z+1.);
		
		}
		if(world[y+1][x][z]!=1)
		{
			glColor3f(1.0,1.0,1.0);							//draw top face
			glTexCoord2f(0.0f, 0);glVertex3f(x,y+1.,z);
			glTexCoord2f(1.0f, 0.0f);glVertex3f(x,y+1,z+1);
			glTexCoord2f(1, 1);glVertex3f(x+1.,y+1,z+1.);
			glTexCoord2f(0, 1.0f);glVertex3f(x+1.,y+1.,z);
		
		}
		if((world[y][x-1][z]!=1)||(x==0))
		{
						
			glColor3f(0.7,0.7,0.7);								//draw left face
			glTexCoord2f(0.0f, 0);glVertex3f(x,y,z);
			glTexCoord2f(1.0f, 0.0f);glVertex3f(x,y,z+1.);
			glTexCoord2f(1, 1);glVertex3f(x,y+1.,z+1.);
			glTexCoord2f(0, 1.0f);glVertex3f(x,y+1.,z);
		
		}
		if(world[y][x+1][z]!=1)
		{
			glColor3f(0.7,0.7,0.7);								//draw right face
			glTexCoord2f(0.0f, 0);glVertex3f(x+1.,y,z);
			glTexCoord2f(1.0f, 0.0f);glVertex3f(x+1.,y+1.,z);
			glTexCoord2f(1, 1);glVertex3f(x+1.,y+1.,z+1.);
			glTexCoord2f(0, 1.0f);glVertex3f(x+1.,y,z+1.);
			
		}
	glEnd();
	glShadeModel(GL_SMOOTH);
	glDisable( GL_TEXTURE_2D );	
	if((x>=xPosition)&&(x<=(xPosition+3))&&(z>=zPosition)&&(z<=(zPosition+3)))      //cast shadow for the back face of the unit cube
			{
				if((blockLPoints[x-xPosition][z-zPosition]!=30)&&(blockLPoints[x-xPosition][z-zPosition-1]!=30)&&((z-zPosition-1)>=0))
				{
					if(y<yPosition+blockLPoints[x-xPosition][z-zPosition])
					{
					if(checkway(x,y,z-1))
					{
						glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
						glEnable(GL_BLEND);
						glBegin(GL_QUADS);
							glColor4f(0.4,0.4,0.4,0.5);                                 
							glVertex3f(x,y,z-0.01);
							glVertex3f(x,y+1,z-0.01);
							glVertex3f(x+1,y+1,z-0.01);
							glVertex3f(x+1,y,z-0.01);

						glEnd();	
						glDisable(GL_BLEND);
					}
					}
				}
			}
	if((x>=xPosition)&&(x<=(xPosition+3))&&(z>=zPosition)&&(z<=(zPosition+3)))           //cast shadow for the front face 
			{
				if((blockLPoints[x-xPosition][z-zPosition]!=30)&&(blockLPoints[x-xPosition][z-zPosition+1]!=30)&&((z-zPosition+1)<=3))
				{
					if(y<yPosition+blockLPoints[x-xPosition][z-zPosition])
					{
					if(checkway(x,y,z+1))
					{
						glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
						glEnable(GL_BLEND);
						glBegin(GL_QUADS);
							glColor4f(0.4,0.4,0.4,0.5);                                 
							glVertex3f(x,y,z+1.01);
							glVertex3f(x,y+1,z+1.01);
							glVertex3f(x+1,y+1,z+1.01);
							glVertex3f(x+1,y,z+1.01);

						glEnd();	
						glDisable(GL_BLEND);
					}
					}
				}
			}
	if((x>=xPosition)&&(x<=(xPosition+3))&&(z>=zPosition)&&(z<=(zPosition+3)))           //cast shadow for the left face 
			{
				if((blockLPoints[x-xPosition][z-zPosition]!=30)&&(blockLPoints[x-xPosition-1][z-zPosition]!=30)&&((x-xPosition-1)>=0))
				{
					if(y<yPosition+blockLPoints[x-xPosition][z-zPosition])
					{
					if(checkway(x-1,y,z))
					{
						glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
						glEnable(GL_BLEND);
						glBegin(GL_QUADS);
							glColor4f(0.4,0.4,0.4,0.5);                                 
							glVertex3f(x-0.01,y,z);
							glVertex3f(x-0.01,y,z+1);
							glVertex3f(x-0.01,y+1,z+1);
							glVertex3f(x-0.01,y+1,z);

						glEnd();	
						glDisable(GL_BLEND);
					}
					}
				}
			}
	if((x>=xPosition)&&(x<=(xPosition+3))&&(z>=zPosition)&&(z<=(zPosition+3)))           //cast shadow for the left face 
			{
				if((blockLPoints[x-xPosition][z-zPosition]!=30)&&(blockLPoints[x-xPosition+1][z-zPosition]!=30)&&((x-xPosition+1)<=3))
				{
					if(y<yPosition+blockLPoints[x-xPosition][z-zPosition])
					{
					if(checkway(x+1,y,z))
					{
						glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
						glEnable(GL_BLEND);
						glBegin(GL_QUADS);
							glColor4f(0.4,0.4,0.4,0.5);                                 
							glVertex3f(x+1.01,y,z);
							glVertex3f(x+1.01,y+1,z);
							glVertex3f(x+1.01,y+1,z+1);
							glVertex3f(x+1.01,y,z+1);

						glEnd();	
						glDisable(GL_BLEND);
					}
					}
				}
			}
}

//---------------------------------
//---------------------------------
int NextBlosk(int x,int y, int z)
{
	int i;
	for(i=y;i>0;i--)
	{
		if(world[i][x][z]==1)
		{
			return i;
		}
	}
	return 0;
}
//---------------------------------
//---------------------------------


void drawShadow()                                                   // draw the fallsing block shadow;
{
	int i;
	int j;
	if(invrt==FALSE)
	{
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{	
			if(blockLPoints[i][j]!=30)
			{
				if(worldHeight[xPosition+i][zPosition+j]<yPosition+blockLPoints[i][j])
				{
					genShadow(xPosition+i,worldHeight[xPosition+i][zPosition+j],zPosition+j); 
				}
				else
				{
					genShadow(xPosition+i,NextBlosk(xPosition+i,yPosition+blockLPoints[i][j], zPosition+j),zPosition+j);
				}
			}
		}

	}
	}
	else
	{
	}


}

//---------------------------------
//---------------------------------

void genShadow(float x,float y,float z)                                           // draw the shadow unit
{
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
		glColor4f(0.4,0.4,0.4,0.5);                                 
		glVertex3f(x,y+0.01,z);
		glVertex3f(x,y+0.01,z+1);
		glVertex3f(x+1,y+0.01,z+1);
		glVertex3f(x+1,y+0.01,z);

	glEnd();
	glDisable(GL_BLEND);
}

//---------------------------------
//---------------------------------

void  drawStringBig (char *s)
{
  unsigned int i;

  for (i = 0; i < strlen (s); i++) {
    //glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, s[i]);
    glutBitmapCharacter (GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
  }
};

//---------------------------------
//---------------------------------

void drawButton(float x, float y, float z, int but, int state)	//draw buttons 
{

	float dimx=0.8;
	float dimy=0.2;

    int i=6;
	
	i=i+(2*but)+state-1;
	
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(1.0,1.0,1.0,0.8); 
	glEnable( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, texture[i]);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_QUADS);
		                                //draw front face
		glTexCoord2f(0.0f, 0);glVertex3f(x,y,z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(x+dimx,y,z);
		glTexCoord2f(1, 1);glVertex3f(x+dimx,y+dimy,z);
		glTexCoord2f(0, 1.0f);glVertex3f(x,y+dimy,z);
		
	
	glEnd();	
	glDisable(GL_BLEND);
}

//---------------------------------
//---------------------------------

void doInit()                                                  //reinitialize the game vars
{
		int a;
		int i;
		for(i=0;i<Nlev+1;i++)
			{
				Lsatus[i]=0;
			}
		eyey=38;
		eyez=60;
		level=1;
		lSpeed=lspeedT[0];
		timer=0;
		butt=0;
		sound=0;
		initWorld();
		a=genBlNo();
		dataToBlock(a);
		generateNewBlock();										// generates the moving block
		dist=0;
		GameEnd=FALSE;
		maxHeight=0;
		endGameCount=0;
		ffTime=TRUE;
}


//---------------------------------
//---------------------------------

void getDataFromFile(char* file)     //gets the blocks structure from file 
{

	int j=0;
	int i=0;
	int k=0;
	char a[64];
	char c;
	FILE *File=NULL;								// File Handle

	if (!file)										// Make Sure A Filename Was Given
	{
		return NULL;								// If Not Return NULL
	}

	File=fopen(file,"r");							// Check To See If The File Exists
	do
	{
		i=0;
		do
		{
			c=fgetc(File);
			if((c=='1')||(c=='0'))
			{
				a[i]=c;
				i++;
			}
		}while((c!='\n')&&(c!=eof()));
		
		if(c!=eof())
		{
			for( k=0;k<64;k++)
			{
				data[j][k]	=(int)a[k]-48;
			
			}
		j++;
		}

	}while(c!=eof());
	Bno=j;
	
	
	fclose (File);
}

//---------------------------------
//---------------------------------
int genBlNo()   // generate random numbers, diferent from the precedent one
{
	int rez;
	srand ( time(NULL) );
	cnttimer++;
	rez=(rand()+cnttimer)%Bno;
	if(last==rez)
		{
			rez=(rand()+cnttimer+1)%Bno;
			last=rez;
		}
	else last=rez;
	 
	return rez;
     
}


//---------------------------------
//---------------------------------

void futureToCurent()  //generate the new curent block;
{
	
	int i=0;
	int j=0;
	int k=0;
	for(i=0;i<4;i++)    //y
	{ 
		for(j=0;j<4;j++)  //x
		{
			for(k=0;k<4;k++)   //z
			{
				moveBloc[i][j][k]=futurebloc[i][j][k];
			}
		}
	}
	dataToBlock(genBlNo());

}

//---------------------------------
//---------------------------------

void dataToBlock(int bl)  //read the bloc data from the initial sore place 
{
	int t=0;
	int i=0;
	int j=0;
	int k=0;
	for(i=0;i<4;i++)    //y
	{ 
		for(j=0;j<4;j++)  //x
		{
			for(k=0;k<4;k++)   //z
			{
				futurebloc[i][j][k]=data[bl][t];
				t++;
			}
		}
	}

}

//---------------------------------
//---------------------------------

AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
{
	FILE *File=NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File=fopen(Filename,"r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);// Load The Bitmap And Return A Pointer
		
	}

	return NULL;										// If Load Failed Return NULL
}

//---------------------------------
//---------------------------------

void LoadGLTextures()									// Load Bitmaps And Convert To Textures
{
	int Status=FALSE;									// Status Indicator
	int i;
	AUX_RGBImageRec *TextureImage[Ntex];					// Create Storage Space For The Texture

	memset(TextureImage,0,sizeof(void *)*1);           	// Set The Pointer To NULL

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	for( i=0;i<Ntex;i++)
	{
		if (TextureImage[i]=LoadBMP(filen[i]))
		{
			Status=TRUE;									// Set The Status To TRUE

			glGenTextures(1, &texture[i]);					// Create The Texture

			// Typical Texture Generation Using Data From The Bitmap
			glBindTexture(GL_TEXTURE_2D, texture[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[i]->sizeX, TextureImage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data);
		/*	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);*/
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		}

		if (TextureImage[i])									// If Texture Exists
		{
			if (TextureImage[i]->data)							// If Texture Image Exists
			{
				free(TextureImage[i]->data);					// Free The Texture Image Memory
			}

			free(TextureImage[i]);								// Free The Image Structure
		}
	}
											// Return The Status
}

//---------------------------------
//---------------------------------


void FreeTexture( GLuint texture )
{

  glDeleteTextures( 1, &texture );

}

					
//---------------------------------
//---------------------------------

void resetParams()											//Resets the parameters to the original value
{
	angle = 0;										    // camera angle on x in degrees 
	angle2 = 0;										    // camera angle on y in degrees
    

}
					
//---------------------------------
//---------------------------------

void removePlaneFromWorld(int plane, int X,int Y, int Z)						// removes the i-th plane from the world 
{
	int i;
	int j;
	int k;
	for(i=plane;i<Y;i++)
	{
		for(j=0;j<X;j++)
		{
			for(k=0;k<Z;k++)
			{
				if(i<(Y-1))											// if y < world height- 1, copy the old y+1 map locations, else put 0  
				{
					world[i][j][k]=world[i+1][j][k];

				}
				else
				{
					world[i][j][k]=0;

				}
			}
		}
	}
	recheckHeight();

	score+=100;
}
					
//---------------------------------
//---------------------------------

void checkPlanes(int X,int Y,int Z)										//checks for complet planes in the world space
{	
	int rez=1;
	int i;
	int j;
	int k;
	for(i=yPosition;i<4+yPosition;i++)
	{
		for(j=0;j<X;j++)
		{
			for(k=0;k<Z;k++)
			{
				if(world[i][j][k]!=1)
				{
					rez=0;
				}
			}
		}
		if(rez==1)removePlaneFromWorld(i,X,Y,Z);
		
		rez=1;
	}
	
	display();
}
//---------------------------------
//---------------------------------


void drawGrid()										// draw a help gridd, takes as parameters the dimensions of the wold
{

	int	j;
	int k;
	
		for(j=0;j<4;j++)
		{
			for(k=0;k<4;k++)
			{
				if(blockLPoints[xPosition+j][zPosition+k]<4)
				{
				glLineWidth(0.1);
				glColor3f(1,0,0);
				glBegin(GL_LINES);
					
					glVertex3f(xPosition+j,yPosition+blockLPoints[xPosition+j][zPosition+k],zPosition+k);glVertex3f(xPosition+j,worldHeight[xPosition+j][zPosition+k],zPosition+k);
					
				glEnd();
				}
			}
		}
}
					
//---------------------------------
//---------------------------------

int checkCollisionsMove(int X,int Y, int Z)						// check if there are any collisions betwen the new structure and the world elements			
{
	int rez=1;
	int i=0;
	int j=0;
	int k=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			for(k=0;k<4;k++)
			{	
				
				
				if((moveBloc[i][j][k]==1)&&(moveBloc[i][j][k]==world[Y+i][X+j][Z+k]))
				{
					rez=0;
				}
		
			}	
		}	
	}
	return rez;
}
					

//---------------------------------
//---------------------------------

int getFreeBottom()										// returns the free space available in the bottom side of the moveing block
{
	int rez=0;
	int flag=1;
	int i=0;
	int j;
	int k;
	while(flag)
	{
			for(j=0;j<4;j++)
			{
				for(k=0;k<4;k++)
				{
					if(moveBloc[i][k][j]==1)
					{
						rez=i;
						flag=0;	
					}
				}
			}
		i++;
	}
	return rez;
}

//---------------------------------
//---------------------------------

int getFreeFront()									// returns the free space available in the front side of the moveing block
{
	int rez=0;
	int flag=1;
	int i=3;
	int j;
	int k;
	while(flag)
	{
			for(j=0;j<4;j++)
			{
				for(k=0;k<4;k++)
				{
					if(moveBloc[j][k][i]==1)
					{
						rez=3-i;
						flag=0;
					}

				}
			}
		i--;

	}
	return rez;
}
										
//---------------------------------
//---------------------------------

int getFreeBack()								// returns the free space available in the back side of the moveing block
{
	int rez=0;
	int flag=1;
	int i=0;
	int j;
	int k;
	while(flag)
	{
		
			for(j=0;j<4;j++)
			{
				for(k=0;k<4;k++)
				{
					if(moveBloc[j][k][i]==1)
					{
						rez=i;
						flag=0;
					}

				}
			}
		i++;

	}
	return rez;

}										
//---------------------------------
//---------------------------------

int getFreeLeft()										// returns the free space available in the left side  of the moveing block
{
	int rez=0;
	int flag=1;
	int i=0;
	int j;
	int k;
	while(flag)
	{
		
			for(j=0;j<4;j++)
			{
				for(k=0;k<4;k++)
				{
					if(moveBloc[k][i][j]==1)
					{
						rez=i;
						flag=0;
					}

				}
			}
		i++;

	}
	return rez;
}

//---------------------------------
//---------------------------------

int getFreeRight()										// returns the free space available in the right side of the moveing block
{
	int rez=0;
	int flag=1;
	int i=3;
	int j;
	int k;
	while(flag)
	{
		
			for(j=0;j<4;j++)
			{
				for(k=0;k<4;k++)
				{
					if(moveBloc[k][i][j]==1)
					{
						rez=3-i;
						flag=0;
						
					}

				}
			}
		i--;

	}
	return rez;
}

//---------------------------------
//---------------------------------

void checkFinish()											    // check if the pile has reached the top of the play ground
{ 
	if(maxHeight>MHeight)
	{
	//	done=TRUE;
		GameEnd=TRUE;
	}

}

//---------------------------------
//---------------------------------

int checkCollisions(int tblock[4][4][4])						// check if there are any collisions betwen the new structure and the world elements			
{
	int rez=1;
	int i=0;
	int j=0;
	int k=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			for(k=0;k<4;k++)
			{	
				
				
				if(tblock[i][j][k]==1)
				{
					if(tblock[i][j][k]==world[yPosition+i][xPosition+j][zPosition+k])
					{
						rez=0;   //colision found
					}
					if((yPosition+i)<0)
					{
						rez=0;            // the block is out of the gampe play volume
					}
					if(((xPosition+j)<0)||((xPosition+j)>=xDimension))
					{
						rez=0;  // the block is out of the gampe play volume
					}
						if(((zPosition+k)<0)||((zPosition+k)>=zDimension))
					{
						rez=0;  // the block is out of the gampe play volume
					}
				}
		
			}	
		}	
	}

	return rez;
}

//---------------------------------
//---------------------------------


int checkRotate(int text)											//Checks if a rotation is valid or not
{
	int rez=2;
	switch (text)
	{
		case 4:
				rotateBlocXCCW(moveBloc,0);							//rotate the block in a temporary structure
				rez=checkCollisions(tempBloc);						// check if there are any collisions betwen the new structure and the world elements
				return rez;
				break;
		case 1:	
				rotateBlocXCW(moveBloc,0);							//rotate the block in a temporary structure
				rez=checkCollisions(tempBloc);						// check if there are any collisions betwen the new structure and the world elements
				return rez;
				break;
		case 5:	
				rotateBlocYCCW(moveBloc,0);							//rotate the block in a temporary structure
				rez=checkCollisions(tempBloc);						// check if there are any collisions betwen the new structure and the world elements
				return rez;
				break;
		case 2:	
				rotateBlocYCW(moveBloc,0);							//rotate the block in a temporary structure
				rez=checkCollisions(tempBloc);						// check if there are any collisions betwen the new structure and the world elements
				return rez;
				break;
		case 6:	
				rotateBlocZCCW(moveBloc,0);							//rotate the block in a temporary structure
				rez=checkCollisions(tempBloc);						// check if there are any collisions betwen the new structure and the world elements
				return rez;
				break;
		case 3:	
				rotateBlocZCW(moveBloc,0);							//rotate the block in a temporary structure
				rez=checkCollisions(tempBloc);						// check if there are any collisions betwen the new structure and the world elements
				return rez;
				break;
		default:return rez;
				break;

	}
}

//---------------------------------
//---------------------------------

void blocksLowestPoints()										//creates a map of moveing block lowest points
{
	int i=0;
	int j=0;
	int k=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			for(k=0;k<4;k++)
			{	
				
				
				if(moveBloc[i][j][k]==1)
				{
					if(blockLPoints[j][k]>i)
					{
						blockLPoints[j][k]=i;
					}
				}
		
			}	
		}	
	}

}

//---------------------------------
//---------------------------------

static void drawWorld(BOOL a)                                       //draw the static cubes
{
	int i=0;
	int j=0;
	int k=0;
	
	for(i=0;i<yDimension;i++)
	{
		for(j=0;j<xDimension;j++)
		{
			for(k=0;k<zDimension;k++)
			{
				if(world[i][j][k]==1)
				{
				  if(a==FALSE)
				  {
					if((j!=0)&&(world[i][j-1][k]==1)&&(world[i][j+1][k]==1)&&(world[i][j][k+1]==1)&&(world[i][j][k-1]==1)&&((world[i-1][j][k]==1)||(i==0))&&(world[i+1][j][k]==1))
					{
					}
					else
					{
						wCub(j,i,k);
					}
				  }										// draw the unit cube accordingly with the bitmap									
				}
				else
				{
					if(a==TRUE)
					{
						if(i<maxHeight)
						{
							cubr(j,i,k);
						}
					}
				}
			}
		}
	}
	
}

//---------------------------------
//---------------------------------

void generateNewBlock()									//generates a new block
{
	futureToCurent();
	blocksLowestPoints();
}

//---------------------------------
//---------------------------------

void initVars()											//initialization of the variables
{

	xPosition=xDimension/2-2;
	yPosition=15;
	zPosition=zDimension/2-2;


	initBLP();
	
}

//---------------------------------
//---------------------------------

void initBLP()											//initialization of the blockLPoints matrix
{
	int i;
	int j;

	for(i=0;i<4;i++)
	{	
		for(j=0;j<4;j++)
		{
			blockLPoints[i][j]=30;
		}

	}
}


//---------------------------------
//---------------------------------

void initWorld()															// initialozation of the world; world element = 0 ; & other params. 
{
	
	
	int i;
	int j;
	int k;

	for(i=0;i<yDimension;i++)								
	{
		for(j=0;j<xDimension;j++)
		{
			for(k=0;k<zDimension;k++)
			{
				world[i][j][k]=0;
				
				worldHeight[j][k]=0;
			}
			
		}
	}
	initVars();
	score=0;					//score=0;
	
}

//---------------------------------
//---------------------------------

void convertBlockToStaticWorld(int tblock[4][4][4])                         //Converts bock's coords. into static ones
{
	int i;
	int j;
	int k;
	for(i=0;i<4;i++)								
	{
		for(j=0;j<4;j++)
		{
			for(k=0;k<4;k++)
			{
				if(tblock[i][j][k]==1)
				{
				  
					world[yPosition+i][xPosition+j][k+zPosition]=tblock[i][j][k];     //mark the moveing blocks as static
					if(worldHeight[xPosition+j][zPosition+k]<yPosition+i+1)			  //check the hightbitmap, and change it if necessarily
					{
						worldHeight[xPosition+j][zPosition+k]=yPosition+i+1;
						if(maxHeight<yPosition+i+1)
						{
							maxHeight=yPosition+i+1;
						}
					}
				}			
			}
		}
	}
	score+=10;
}

//---------------------------------
//---------------------------------

int distantsToClosestCub()								 //returns the smallest distance to the cubes below
{
	int minDist=30;
	int i;
	int j;
	dist=0;

	for(i=0;i<4;i++)								
	{
		for(j=0;j<4;j++)
		{
			
			if(((xPosition+i)>=0)&&((xPosition+i)<xDimension)&&((zPosition+j)>=0)&&((zPosition+j)<yDimension))
			{
				if(minDist>yPosition+blockLPoints[i][j]-worldHeight[xPosition+i][zPosition+j])	// if the block is fall-ing
				{
					minDist=abs(yPosition+blockLPoints[i][j]-worldHeight[xPosition+i][zPosition+j]);
				
				}
			}
		}
	
	}
    dist=minDist;
	return minDist;
}

//---------------------------------
//---------------------------------

void tempToMoveBlock(int tblock[4][4][4])			// replace the moving block structure with the new structure

{
	int x;
	int y;
	int z;

	for(y=0;y<4;y++)								// replace the moving block structure with the new structure
	{
		for(x=0;x<4;x++)
		{
			for(z=0;z<4;z++)
			{
				moveBloc[x][y][z]=tblock[x][y][z];
			}
		}
	}
	initBLP();
	blocksLowestPoints();
}

//---------------------------------
//---------------------------------

void tempToTemp(int tblock[4][4][4])			// replace the moving block structure with the new structure

{
	int x;
	int y;
	int z;
	initTBlock();

	for(y=0;y<4;y++)								// replace the moving block structure with the new structure
	{
		for(x=0;x<4;x++)
		{
			for(z=0;z<4;z++)
			{
				tempBloc[x][y][z]=tblock[x][y][z];
			}
		}
	}

}

//---------------------------------
//---------------------------------

void initMBlock(int tblock[4][4][4])					//initialize the moving block structure
{
	int i;
	int j;
	int k;

	for(i=0;i<4;i++)								
	{
		for(j=0;j<4;j++)
		{
			for(k=0;k<4;k++)
			{
				moveBloc[i][j][k]=tblock[i][j][k];
			}
		}
	}
}

//---------------------------------
//---------------------------------

void initTBlock()					//initialize the temporary block structure
{
	int i;
	int j;
	int k;
	for(i=0;i<4;i++)								
	{
		for(j=0;j<4;j++)
		{
			for(k=0;k<4;k++)
			{
				tempBloc[i][j][k]=0;
			}
		}
	}


}

//---------------------------------
//---------------------------------



void rotateBlocYCCW(int modBlock[4][4][4], int m)              //rotate the moveing bloc 90deg counterclockwise on Y
{
	int tempBlock[4][4][4];									//create a temporary block structure
    int x=0;
	int y=0;
	int z=0;
	for(y=0;y<4;y++)									//calculate the new position
	{
		for(x=0;x<4;x++)
		{
			for(z=0;z<4;z++)
			{
				tempBlock[x][y][3-z]=modBlock[x][z][y];
			}
		}
	}
	
	if(m==1)
	{
		tempToMoveBlock(tempBlock);								// replace the moving block structure with the new structure
	
	}
	else tempToTemp(tempBlock);								// replace the temp block structure with the new structure
	
}

//---------------------------------
//---------------------------------

void rotateBlocYCW(int modBlock[4][4][4], int m)              //rotate the moveing bloc 90deg clockwise on Y
{
	int tempBlock[4][4][4];									//create a temporary block structure
    int x=0;
	int y=0;
	int z=0;
	for(y=0;y<4;y++)									//calculate the new position
	{
		for(x=0;x<4;x++)
		{
			for(z=0;z<4;z++)
			{
				tempBlock[x][3-y][z]=modBlock[x][z][y];
			}
		}
	}
	
	if(m==1)
	{
		tempToMoveBlock(tempBlock);								// replace the moving block structure with the new structure
	
	}
	else tempToTemp(tempBlock);								// replace the temp block structure with the new structure
	
}

//---------------------------------
//---------------------------------

void rotateBlocXCW(int modBlock[4][4][4], int m)              //rotate the moveing bloc 90deg clockwise on X
{
	int tempBlock[4][4][4];									//create a temporary block structure
    int x=0;
	int y=0;
	int z=0;
	for(y=0;y<4;y++)									//calculate the new position
	{
		for(x=0;x<4;x++)
		{
			for(z=0;z<4;z++)
			{
				tempBlock[x][y][3-z]=modBlock[z][y][x];
			}
		}
	}
	
	if(m==1)
	{
		tempToMoveBlock(tempBlock);								// replace the moving block structure with the new structure
	
	}
	else tempToTemp(tempBlock);								// replace the temp block structure with the new structure
	
}

//---------------------------------
//---------------------------------

void rotateBlocXCCW(int modBlock[4][4][4], int m)              //rotate the moveing bloc 90deg counterclockwise on X
{
	int tempBlock[4][4][4];									//create a temporary block structure
    int x=0;
	int y=0;
	int z=0;
	for(y=0;y<4;y++)									//calculate the new position
	{
		for(x=0;x<4;x++)
		{
			for(z=0;z<4;z++)
			{
				tempBlock[3-x][y][z]=modBlock[z][y][x];
			}
		}
	}
	
	if(m==1)
	{
		tempToMoveBlock(tempBlock);								// replace the moving block structure with the new structure
	
	}
	else tempToTemp(tempBlock);								// replace the temp block structure with the new structure
	
}

//---------------------------------
//---------------------------------

void rotateBlocZCCW(int modBlock[4][4][4], int m)              //rotate the moveing bloc 90deg counterclockwise on Z
{
	int tempBlock[4][4][4];									//create a temporary block structure
    int x=0;
	int y=0;
	int z=0;
	for(y=0;y<4;y++)									//calculate the new position
	{
		for(x=0;x<4;x++)
		{
			for(z=0;z<4;z++)
			{
				tempBlock[x][3-y][z]=modBlock[y][x][z];
			}
		}
	}
	
	if(m==1)
	{
		tempToMoveBlock(tempBlock);								// replace the moving block structure with the new structure
	
	}
	else tempToTemp(tempBlock);								// replace the temp block structure with the new structure
	
}

//---------------------------------
//---------------------------------

void rotateBlocZCW(int modBlock[4][4][4], int m)              //rotate the moveing bloc 90deg clockwise on Z
{
	int tempBlock[4][4][4];									//create a temporary block structure
    int x=0;
	int y=0;
	int z=0;
	for(y=0;y<4;y++)									//calculate the new position
	{
		for(x=0;x<4;x++)
		{
			for(z=0;z<4;z++)
			{
				tempBlock[3-x][y][z]=modBlock[y][x][z];
			}
		}
	}
	
	if(m==1)
	{
		tempToMoveBlock(tempBlock);								// replace the moving block structure with the new structure
	
	}
	else tempToTemp(tempBlock);								// replace the temp block structure with the new structure
	
}

//---------------------------------
//---------------------------------

static void drawBlock(float x, float y, float z, int a)                 //draw the blocks if a=1 draw the moveing block if a=0 draw the future block 
{
	int i=0;
	int j=0;
	int k=0;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			for(k=0;k<4;k++)
			{
				if(a==1)
				{
					if(moveBloc[i][j][k]==1)
					{
						cub(x+j,y+i,z+k);
					}
				}
				else
				{
					if(futurebloc[i][j][k]==1)
					{
						cub(x+j,y+i,z+k);
					}

				}
			}
		}
	}
}

//---------------------------------
//---------------------------------

static void drawFloor()											//Uset to draw the playground floor
{
 
	// Top face
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseLight);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	 glMaterialfv(GL_FRONT, GL_AMBIENT, ambientLight);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glEnable( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, texture[19]);
	glBegin(GL_QUADS);											//The playground floor is nothing else but a square 20x20 units
    glColor3f(1.0, 1.0,1.0);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0,1.0);
    glTexCoord2f(0.0f, 0);glVertex3f(0.0, 0.0, zDimension);
    glColor3f(1.0, 1.0,1.0);
    glTexCoord2f(0, 1);glVertex3f(xDimension, 0.0, zDimension);
    glColor3f(1.0,1.0,1.0);
    glTexCoord2f(1, 1.0f);glVertex3f(xDimension, 0.0, 0.0);
  glEnd();

  
//  bottom face 
  
	    glEnable( GL_TEXTURE_2D );
	    glBindTexture(GL_TEXTURE_2D, texture[19]);
		glBegin(GL_QUADS);											//The playground floor is nothing else but a square 20x20 units
		glColor3f(1.0, 1.0,1.0);
		glTexCoord2f(1, 1);glVertex3f(0.0, -0.01, 0.0);
		glColor3f(1.0,1.0,1.0);
		glTexCoord2f(1,0);glVertex3f(xDimension, -0.01, 0.0);
		glColor3f(1.0, 1.0,1.0);
		glTexCoord2f(0, 0);glVertex3f(xDimension, -0.01, zDimension);
	    glColor3f(1.0, 1.0,1.0);
		glTexCoord2f(0, 1);glVertex3f(0.0, -0.01, zDimension);

    
  glEnd();
}

//---------------------------------
//---------------------------------

void glutKeyboardUpCallback( unsigned char key, int x, int y ) //handels key up events
    {
        
        keystate[key]=FALSE;
    }
//---------------------------------
//---------------------------------

void glutKeyboardSUpCallback( unsigned char key, int x, int y ) //handels special key up events
    {
        
        keystate[key]=FALSE;
    }

//---------------------------------
//---------------------------------

void NormalKeys(unsigned char key, int x, int y)				//Manage the Normal Keys events
{


	if (key == 27)												//If 'Escape' key was pressed the aplication will finish 
	{
		if(done==FALSE)
		{
			
			
			done=TRUE;
			pause=FALSE;
			playSound(9);
		}
		if(Omenu==TRUE)
		{
			Omenu=FALSE;
			Mmenu=TRUE;
			playSound(9);
		}
		if(Amenu==TRUE)
		{
			Amenu=FALSE;
			Mmenu=TRUE;
			playSound(9);
		}
		if(Smenu==TRUE)
		{
			Smenu=FALSE;
			Mmenu=TRUE;
			playSound(9);
		}
	
		
	}
	if(!pause)
	{
	if((key=='r')||(key=='R'))
	{
		resetParams();											//Resets the parameters to the original value
		display();
	}
	
	if((key=='i')||(key=='I'))									// invert key event
	{
		if(done==FALSE)
		{
			invrt=!invrt;
			display();
		}
	}
	if((key=='4')&&(keystate[key]==FALSE)) 
			{
				
				if(checkRotate(4))
				{		
					rotateBlocXCCW(moveBloc,1);						//Rotate CW the block 90deg on X 		
					keystate[key]=TRUE;											//set flag to 1
					cnt++;
					playSound(6);
				}
				else
				{
					playSound(7);
				}
				
				display();     											//Repaint useing the new angle of rotation 
			}
		if((key=='1')&&(keystate[key]==FALSE))
		{
				if(checkRotate(1))
				{
					rotateBlocXCW(moveBloc,1);										//-90 on X
					keystate[key]=TRUE;											//set flag to 1 										
					cnt++;
					playSound(6);

				}
				else
				{
					playSound(7);
				}
				display();
		}
		if((key=='5')&&(keystate[key]==FALSE))			
			{	
				if(checkRotate(5))
				{
					rotateBlocYCCW(moveBloc,1);										//+90 on Y
					keystate[key]=TRUE;
					cnt++;
					playSound(6);
				}
				else
				{
					playSound(7);
				}
				display();
			}
		if((key=='2')&&(keystate[key]==FALSE))
		{
				if(checkRotate(2))
				{
					rotateBlocYCW(moveBloc,1);								  //-90 on Y
					keystate[key]=TRUE;
					cnt++;
					playSound(6);
				}
				else
				{
					playSound(7);
				}
					display();
		}
		if((key=='6')&&(keystate[key]==FALSE)) 
			{	
				if(checkRotate(6))
				{
					rotateBlocZCCW(moveBloc,1);								 //+90 on Z
					keystate[key]=TRUE;
					cnt++;
					playSound(6);
				}
				else
				{
					playSound(7);
				}
				display();
			}
		if((key=='3')&&(keystate[key]==FALSE))
		{
			if(checkRotate(3))
				{	
					rotateBlocZCW(moveBloc,1);									//-90 on Z
					keystate[key]=TRUE;
					cnt++;
					playSound(6);
				}
				else
				{
					playSound(7);
				}
				display();
		}
		if((key=='0')&&(keystate[key]==FALSE))
		{
			if(distantsToClosestCub()>0)
				{
					yPosition-=dist;									//Y=Y-distantsToClosestCub; put the block on the bottom
					cnt=lSpeed;
					keystate[key]=TRUE;
					playSound(6);
					display();
				}	
				display();
		}
	}
		if(key==13)                                      //enter pressed
		{
			   if(done==TRUE)							//if we are in the main menu area
			   {
				   if(Mnu[0]==0)						//output the menu selection
				   {
						done=FALSE;
						resetParams();
						playSound(3);
						doInit();
				   }
					if(Mnu[1]==0)
					{
						Omenu=TRUE;
						Mmenu=FALSE;
						playSound(3);
					}
					if(Mnu[2]==0)
					{
						Smenu=TRUE;
						Mmenu=FALSE;
						playSound(3);
						
					}
				   if(Mnu[3]==0)
					{
					
					   Amenu=TRUE;
					   Mmenu=FALSE;
					   playSound(3);
					}
				   if(Mnu[4]==0)
					{
					   playSound(3);
					   KillALData();
					   exit(0);
					}
			   }
			   
			   
				display();
		}
				
	if((key=='p')||(key=='P'))
	{
		if(done==FALSE)
		{
			pause=!pause;										//Resets the parameters to the original value
			display();
		}
	}
}

//---------------------------------
//---------------------------------

void SpecialKeys(int key, int x, int y)							//Manage the Special Keys events
{
	if(!pause)
	{
		if(key==GLUT_KEY_UP) 
			{
				if(done==FALSE)
				{
					if(keystate[key]==FALSE)
					{
						if(checkCadran(angle+45)==1)
						{
							if(zPosition>(0-getFreeBack())&&(checkCollisionsMove(xPosition,yPosition,zPosition-1)))
							{
								zPosition-=1;										//Calculate the new position on Z ( decrement the Z position whith 1; Z.new=Z.old-1)
								keystate[key]=TRUE;
								cnt++;
								playSound(5);
								display();
							}
						}
						if(checkCadran(angle+45)==2)
						{
							if(xPosition<((xDimension-4)+getFreeRight())&&(checkCollisionsMove(xPosition+1,yPosition,zPosition)))
							{
								xPosition+=1;									//X=X+1
								keystate[key]=TRUE;
								cnt++;
								playSound(5);
								display();
							}
							
						}
						if(checkCadran(angle+45)==3)
						{
							if(zPosition<((zDimension-4)+getFreeFront())&&(checkCollisionsMove(xPosition,yPosition,zPosition+1)))
							{
								zPosition+=1;									// Z=Z+1
								keystate[key]=TRUE;
								cnt++;
								playSound(5);
								display();
							}
						}
						if(checkCadran(angle+45)==4)
						{
							
							if(xPosition>(0-getFreeLeft())&&(checkCollisionsMove(xPosition-1,yPosition,zPosition)))
							{
								xPosition-=1;									//X=X-1
								keystate[key]=TRUE;
								cnt++;
								playSound(5);
								display();
							}
						}
					}
				}
				else
				{
				if(Mmenu==TRUE)					//Main menu control
				{
					int tmp[5];
					tmp[0]=Mnu[1];
					tmp[1]=Mnu[2];
					tmp[2]=Mnu[3];
					tmp[3]=Mnu[4];
					tmp[4]=Mnu[0];
					Mnu[0]=tmp[0];
					Mnu[1]=tmp[1];
					Mnu[2]=tmp[2];
					Mnu[3]=tmp[3];
					Mnu[4]=tmp[4];
					playSound(2);
					display();
				}}
			}
		if(key==GLUT_KEY_DOWN)
		{
			if(done==FALSE)
			{	
				if(keystate[key]==FALSE)
				{
					if(checkCadran(angle+45)==1)
						{
							if(zPosition<((zDimension-4)+getFreeFront())&&(checkCollisionsMove(xPosition,yPosition,zPosition+1)))
							{
								zPosition+=1;									// Z=Z+1
								keystate[key]=TRUE;
								cnt++;
								playSound(5);
								display();
							}
						}
					if(checkCadran(angle+45)==2)
					{
						if(xPosition>(0-getFreeLeft())&&(checkCollisionsMove(xPosition-1,yPosition,zPosition)))
							{
								xPosition-=1;									//X=X-1
								keystate[key]=TRUE;
								cnt++;
								playSound(5);
								display();
							}
					}
					if(checkCadran(angle+45)==3)
					{
						if(zPosition>(0-getFreeBack())&&(checkCollisionsMove(xPosition,yPosition,zPosition-1)))
							{
								zPosition-=1;										//Calculate the new position on Z ( decrement the Z position whith 1; Z.new=Z.old-1)
								keystate[key]=TRUE;
								cnt++;
								playSound(5);
								display();
							}

					}
					if(checkCadran(angle+45)==4)
					{
						if(xPosition<((xDimension-4)+getFreeRight())&&(checkCollisionsMove(xPosition+1,yPosition,zPosition)))
							{
								xPosition+=1;									//X=X+1
								keystate[key]=TRUE;
								cnt++;
								playSound(5);
								display();
							}
					}
				}
			}
			else{
			if(Mmenu==TRUE)										//Main menu control
			{
				int tmp[5];
					tmp[0]=Mnu[4];
					tmp[1]=Mnu[0];
					tmp[2]=Mnu[1];
					tmp[3]=Mnu[2];
					tmp[4]=Mnu[3];
					Mnu[0]=tmp[0];
					Mnu[1]=tmp[1];
					Mnu[2]=tmp[2];
					Mnu[3]=tmp[3];
					Mnu[4]=tmp[4];
					playSound(2);
					display();
			}
			}

		}
		if(key==GLUT_KEY_RIGHT) 
			{
				if(done==FALSE)
				{	
					if(keystate[key]==FALSE)
					{
						if(checkCadran(angle+45)==1)
						{
							if(xPosition<((xDimension-4)+getFreeRight())&&(checkCollisionsMove(xPosition+1,yPosition,zPosition)))
							{
								xPosition+=1;									//X=X+1
								keystate[key]=TRUE;
								cnt++;
								playSound(5);
								display();
							}
						}
						if(checkCadran(angle+45)==2)
						{
							if(zPosition<((zDimension-4)+getFreeFront())&&(checkCollisionsMove(xPosition,yPosition,zPosition+1)))
							{
								zPosition+=1;									// Z=Z+1
								keystate[key]=TRUE;
								cnt++;
								playSound(5);
								display();
							}

						}
						if(checkCadran(angle+45)==3)
						{
							if(xPosition>(0-getFreeLeft())&&(checkCollisionsMove(xPosition-1,yPosition,zPosition)))
							{
								xPosition-=1;									//X=X-1
								keystate[key]=TRUE;
								cnt++;
								playSound(5);
								display();
							}
						}
						if(checkCadran(angle+45)==4)
						{
							
							if(zPosition>(0-getFreeBack())&&(checkCollisionsMove(xPosition,yPosition,zPosition-1)))
							{
								zPosition-=1;										//Calculate the new position on Z ( decrement the Z position whith 1; Z.new=Z.old-1)
								keystate[key]=TRUE;
								cnt++;
								playSound(5);
								display();
							}
						}
					}
				}
				if(Smenu==TRUE)                 //Settings menu control
				{
					int tmp[5];
					tmp[0]=Snu[1];
					tmp[1]=Snu[0];
					Snu[0]=tmp[0];
					Snu[1]=tmp[1];
					playSound(6);
					if(Snu[1]==1)
					{
						xDimension=16,yDimension=16;zDimension=16;
					}
					if(Snu[0]==1)
					{
						xDimension=8,yDimension=16;zDimension=8;
					}
					display();
				}
			}
		if(key==GLUT_KEY_LEFT)
		{
			if(done==FALSE)
			{	
				if(keystate[key]==FALSE)
				{
					if(checkCadran(angle+45)==1)
						{
							if(xPosition>(0-getFreeLeft())&&(checkCollisionsMove(xPosition-1,yPosition,zPosition)))
							{
								xPosition-=1;									//X=X-1
								keystate[key]=TRUE;
								cnt++;
								playSound(5);
								display();
							}
						}
					if(checkCadran(angle+45)==2)
						{
							if(zPosition>(0-getFreeBack())&&(checkCollisionsMove(xPosition,yPosition,zPosition-1)))
							{
								zPosition-=1;										//Calculate the new position on Z ( decrement the Z position whith 1; Z.new=Z.old-1)
								keystate[key]=TRUE;
								cnt++;
								playSound(5);
								display();
							}
						}
					if(checkCadran(angle+45)==3)
						{
							if(xPosition<((xDimension-4)+getFreeRight())&&(checkCollisionsMove(xPosition+1,yPosition,zPosition)))
							{
								xPosition+=1;									//X=X+1
								keystate[key]=TRUE;
								cnt++;
								playSound(5);
								display();
							}
						}
					if(checkCadran(angle+45)==4)
						{
							if(zPosition<((zDimension-4)+getFreeFront())&&(checkCollisionsMove(xPosition,yPosition,zPosition+1)))
							{
								zPosition+=1;									// Z=Z+1
								keystate[key]=TRUE;
								cnt++;
								playSound(5);
								display();
							}
						}
				}
			}
			if(Smenu==TRUE)                       //Settings menu control
			{
				int tmp[5];
					tmp[0]=Snu[1];
					tmp[1]=Snu[0];
					Snu[0]=tmp[0];
					Snu[1]=tmp[1];
					playSound(6);
					if(Snu[1]==1)
					{
						xDimension=16,yDimension=16;zDimension=16;
					}
					if(Snu[0]==1)
					{
						xDimension=8,yDimension=16;zDimension=8;
					}
					display();
			}
		}
		
		/*	if(key==GLUT_KEY_PAGE_UP)
		{
				yPosition+=1;									//Y=Y+1
				PlaySound("data/sounds/Rot.wav", NULL, SND_ASYNC);
				display();
		}
		*/
	}
}

//---------------------------------
//---------------------------------

static void mouse(int button, int state, int x, int y)				//Used to get the mouse coordinates 
{
  
  if (button == GLUT_LEFT_BUTTON)
  {
	
    if(done==TRUE)
	{
		if(moving==1)
		{
			if (state == GLUT_UP)
			{
				moving = 0;
			}

		}
		else
		{
		
		if((checkMvBP()!=0)&&(moving==0))
		{
		
				   if(Mnu[0]==0)
				   {
						done=FALSE;
						resetParams();
						if(psound==0)
						{
							psound=1;
							playSound(3);
						}
						doInit();
				   }
					if(Mnu[1]==0)
					{
						Omenu=TRUE;
						Mmenu=FALSE;
						if(psound==0)
						{
							psound=1;
							playSound(3);
						}
					}
					if(Mnu[2]==0)
					{
						Smenu=TRUE;
						Mmenu=FALSE;
						if(psound==0)
						{
							psound=1;
							playSound(3);
						}
						
					}
				   if(Mnu[3]==0)
					{
					
					   Amenu=TRUE;
					   Mmenu=FALSE;
					   if(psound==0)
						{
							psound=1;
							playSound(3);
						}
					}
				   if(Mnu[4]==0)
					{
					   if(psound==0)
						{
							psound=1;
							playSound(3);
						}
					   KillALData();
					   exit(0);
					}
		}
		}		   
		
	}
	else
	{
		if (state == GLUT_DOWN)
		{
			moving = 1;
			startx = x;
			starty = y;
		}
		if (state == GLUT_UP)
		{
			moving = 0;
		}
	}
  }
  // Used for wheel , has to be up
	if (state == GLUT_UP )
	{
		if ( button == GLUT_WHEEL_UP )
		{
			if(xDimension==8)
			{
				if(eyey>22)
				{
					eyey--;
					eyez--;
					//	printf("Wheel Up\n");
				
				}
			}
			else
			{
				if(eyey>27)
				{
					eyey--;
					eyez--;
					//	printf("Wheel Up\n");
				
				}
			}
		}
		else if( button == GLUT_WHEEL_DOWN )
		{
			if(eyey<38)
			{
				eyey++;
				eyez++;
			//	printf("Wheel Dn\n");
				
			}
		}
	}
  
  if ((button == GLUT_RIGHT_BUTTON)&&(!pause))
  {
	 if(done==TRUE)
	{
		if (state == GLUT_DOWN)  
		{

			if(Omenu==TRUE)
			{
				Omenu=FALSE;
				Mmenu=TRUE;
				if(psound==1)
						{
							psound=0;
							playSound(9);
						}
			}
			if(Amenu==TRUE)
			{
				Amenu=FALSE;
				Mmenu=TRUE;
				if(psound==1)
						{
							psound=0;
							playSound(9);
						}
			}
			if(Smenu==TRUE)
			{
				Smenu=FALSE;
				Mmenu=TRUE;
				if(psound==1)
						{
							psound=0;
							playSound(9);
						}
			}
		}
	}
	 else
	 {
	  
	  if (state == GLUT_DOWN)        
		{
		if(butt==0)                          //do this only one time
		{
			butt=1;
			if(distantsToClosestCub()>0)
				{
					yPosition-=dist;									//Y=Y-distantsToClosestCub; put the block on the bottom
					cnt=lSpeed;
					playSound(6);
					display();
				}	
		}
		}
	if (state == GLUT_UP)
	{
      butt = 0;
    }
	}
  }
}

//---------------------------------
//---------------------------------

static void motion(int x, int y)								//Calculates the new angle, based on mouse movements
{
  
  if (moving)
  {
    angle = angle + (x - startx);
    angle2 = angle2 + (y - starty);
    startx = x;
    starty = y;
    glutPostRedisplay();
		
  }
 
}
//---------------------------------
//---------------------------------

static void passive(int x, int y)						// returns cursor position
{
	mX=x;
    mY=y;
	
	if((done==TRUE)&&(Mmenu==TRUE))
	{
	switch(checkMvBP())
	{
	case 1:updateMenuTable(1);
			if(bsound==0)
			{	
				bsound=1;
				playSound(2);
			}
			break;
	case 2:updateMenuTable(2);
			if(bsound==0)
			{	
				bsound=1;
				playSound(2);
			}
			break;
	case 3:updateMenuTable(3);
			if(bsound==0)
			{	
				bsound=1;
				playSound(2);
			}
			break;
	case 4:updateMenuTable(4);
			if(bsound==0)
			{	
				bsound=1;
				playSound(2);
			}
			break;
	case 5:updateMenuTable(5);
			if(bsound==0)
			{	
				bsound=1;
				playSound(2);
			}
			break;
	default:
			if(bsound==1)
			{	
				bsound=0;
				
			}
			break;
	}
	}
}

//---------------------------------
//---------------------------------

void drawAxes()														//help function :draw the coordonates axes
{
	glBegin(GL_LINES);
		glColor3f(0.5,0.5,0.5);                                 
		glVertex3f(0,0,0);glVertex3f(0,15,0);
		glVertex3f(0,0,0);glVertex3f(5,0,0);
		glVertex3f(0,0,0);glVertex3f(0,0,5);
		glVertex3f(0,MHeight,0);glVertex3f(0,MHeight,1);
		glVertex3f(0,MHeight,0);glVertex3f(1,MHeight,0);
	
	glEnd();
	glBegin(GL_LINES);
		glColor3f(0.5,0.5,0.5);                                 
		glVertex3f(0,0,zDimension);glVertex3f(0,15,zDimension);
		glVertex3f(0,0,zDimension);glVertex3f(5,0,zDimension);
		glVertex3f(0,0,zDimension);glVertex3f(0,0,zDimension-5);
		glVertex3f(0,MHeight,zDimension);glVertex3f(0,MHeight,zDimension-1);
		glVertex3f(0,MHeight,zDimension);glVertex3f(1,MHeight,zDimension);
	glEnd();
	glBegin(GL_LINES);
		glColor3f(0.5,0.5,0.5);                                 
		glVertex3f(xDimension,0,zDimension);glVertex3f(xDimension,15,zDimension);
		glVertex3f(xDimension,0,zDimension);glVertex3f(xDimension-5,0,zDimension);
		glVertex3f(xDimension,0,zDimension);glVertex3f(xDimension,0,zDimension-5);
		glVertex3f(xDimension,MHeight,zDimension);glVertex3f(xDimension,MHeight,zDimension-1);
		glVertex3f(xDimension,MHeight,zDimension);glVertex3f(xDimension-1,MHeight,zDimension);
	
	glEnd();
	glBegin(GL_LINES);
		glColor3f(0.5,0.5,0.5);                                 
		glVertex3f(xDimension,0,0);glVertex3f(xDimension,15,0);
		glVertex3f(xDimension,0,0);glVertex3f(xDimension-5,0,0);
		glVertex3f(xDimension,0,0);glVertex3f(xDimension,0,5);
		glVertex3f(xDimension,MHeight,0);glVertex3f(xDimension,MHeight,1);
		glVertex3f(xDimension,MHeight,0);glVertex3f(xDimension-1,MHeight,0);
	glEnd();
}

//---------------------------------
//---------------------------------

void drawAxes1()														//help function :draw the coordonates axes
{
	glBegin(GL_LINES);
		glColor3f(1.0,0.0,0.0);                                 
		glVertex3f((xDimension/2),0,(zDimension/2));glVertex3f((xDimension/2),5,(zDimension/2));
		glVertex3f((xDimension/2),0,(zDimension/2));glVertex3f((xDimension/2+10),0,(zDimension/2));
		glVertex3f((xDimension/2),0,(zDimension/2));glVertex3f((xDimension/2),0,(zDimension/2+10));
	glEnd();
}

//---------------------------------
//---------------------------------

void cub(float x, float y, float z)									//draw the cub unit wich start at x, y, z
{
	
	

	glEnable( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, texture[21]);
	glBegin(GL_QUADS);
		glColor3f(0.7,0.7,0.7);	                                 //draw back face
		glTexCoord2f(0.0f, 0);glVertex3f(x,y,z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(x,y+1.,z);
		glTexCoord2f(1, 1);glVertex3f(x+1.,y+1.,z);
		glTexCoord2f(0, 1.0f);glVertex3f(x+1.,y,z);
		
		glColor3f(0.5,0.5,0.5);								//draw bottom face
		glTexCoord2f(0.0f, 0);glVertex3f(x,y,z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(x+1.,y,z);
		glTexCoord2f(1, 1);glVertex3f(x+1.,y,z+1.);
		glTexCoord2f(0, 1.0f);glVertex3f(x,y,z+1.);
		
		glColor3f(0.7,0.7,0.7);									//draw front face
		glTexCoord2f(0.0f, 0);glVertex3f(x,y,z+1.);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(x+1.,y,z+1);
		glTexCoord2f(1, 1);glVertex3f(x+1.,y+1,z+1.);
		glTexCoord2f(0, 1.0f);glVertex3f(x,y+1.,z+1.);

		glColor3f(1.0,1.0,1.0);							//draw top face
		glTexCoord2f(0.0f, 0);glVertex3f(x,y+1.,z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(x,y+1,z+1);
		glTexCoord2f(1, 1);glVertex3f(x+1.,y+1,z+1.);
		glTexCoord2f(0, 1.0f);glVertex3f(x+1.,y+1.,z);

		glColor3f(0.7,0.7,0.7);								//draw left face
		glTexCoord2f(0.0f, 0);glVertex3f(x,y,z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(x,y,z+1.);
		glTexCoord2f(1, 1);glVertex3f(x,y+1.,z+1.);
		glTexCoord2f(0, 1.0f);glVertex3f(x,y+1.,z);

		glColor3f(0.7,0.7,0.7);								//draw left face
		glTexCoord2f(0.0f, 0);glVertex3f(x+1.,y,z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(x+1.,y+1.,z);
		glTexCoord2f(1, 1);glVertex3f(x+1.,y+1.,z+1.);
		glTexCoord2f(0, 1.0f);glVertex3f(x+1.,y,z+1.);

	glEnd();
	glShadeModel(GL_SMOOTH);
}

//---------------------------------
//---------------------------------

void cubr(float x, float y, float z)									//draw the cub unit wich start at x, y, z used to draw only the empty spaces when "i" is pressed
{
	
	

	glEnable( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, texture[21]);
	glBegin(GL_QUADS);
		glColor3f(0.7,0.0,0.0);	                                 //draw back face
		glTexCoord2f(0.0f, 0);glVertex3f(x,y,z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(x,y+1.,z);
		glTexCoord2f(1, 1);glVertex3f(x+1.,y+1.,z);
		glTexCoord2f(0, 1.0f);glVertex3f(x+1.,y,z);
		
		glColor3f(0.7,0.0,0.0);								//draw bottom face
		glTexCoord2f(0.0f, 0);glVertex3f(x,y,z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(x+1.,y,z);
		glTexCoord2f(1, 1);glVertex3f(x+1.,y,z+1.);
		glTexCoord2f(0, 1.0f);glVertex3f(x,y,z+1.);
		
		glColor3f(0.7,0.0,0.0);									//draw front face
		glTexCoord2f(0.0f, 0);glVertex3f(x,y,z+1.);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(x+1.,y,z+1);
		glTexCoord2f(1, 1);glVertex3f(x+1.,y+1,z+1.);
		glTexCoord2f(0, 1.0f);glVertex3f(x,y+1.,z+1.);

		glColor3f(0.7,0.0,0.0);							//draw top face
		glTexCoord2f(0.0f, 0);glVertex3f(x,y+1.,z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(x,y+1,z+1);
		glTexCoord2f(1, 1);glVertex3f(x+1.,y+1,z+1.);
		glTexCoord2f(0, 1.0f);glVertex3f(x+1.,y+1.,z);

		glColor3f(0.7,0.0,0.0);								//draw left face
		glTexCoord2f(0.0f, 0);glVertex3f(x,y,z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(x,y,z+1.);
		glTexCoord2f(1, 1);glVertex3f(x,y+1.,z+1.);
		glTexCoord2f(0, 1.0f);glVertex3f(x,y+1.,z);

		glColor3f(0.7,0.0,0.0);								//draw left face
		glTexCoord2f(0.0f, 0);glVertex3f(x+1.,y,z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(x+1.,y+1.,z);
		glTexCoord2f(1, 1);glVertex3f(x+1.,y+1.,z+1.);
		glTexCoord2f(0, 1.0f);glVertex3f(x+1.,y,z+1.);

	glEnd();
	glShadeModel(GL_SMOOTH);
}


//---------------------------------
//---------------------------------

/*void bigCub(float x, float y, float z,int dim)									//draw the room
{



	glEnable( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
		glColor3f(1.0,1.0,1.0);                                 //draw front face
		glTexCoord2f(1.0f, 0.0f);glVertex3f(x-0.08,y-0.08,z+0.08);
		glTexCoord2f(0.0f, 0);glVertex3f(x+dim+0.08,y-0.08,z+0.08);
		glTexCoord2f(0, 1);glVertex3f(x+dim+0.08,y+dim+0.08,z+0.08);
		glTexCoord2f(1, 1.0f);glVertex3f(x-0.08,y+dim+0.08,z+0.08);
	glEnd();	

	 
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
		glColor3f(1.0,1.0,1.0);									//draw bottom face
		glTexCoord2f(0.0f, 0.0f);glVertex3f(x-0.08,y,z);
		glTexCoord2f(0.0f, 1);glVertex3f(x-0.08,y,z+dim);
		glTexCoord2f(1, 1);glVertex3f(x+dim+0.08,y,z+dim);
		glTexCoord2f(1, 0.0f);glVertex3f(x+dim+0.08,y,z);
	glEnd();	

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);	
		glColor3f(1.0,1.0,1.0);									//draw back face
		glTexCoord2f(0.0f, 0.0f);glVertex3f(x-0.08,y-0.08,z+dim-0.08);
		glTexCoord2f(0.0f, 1);glVertex3f(x-0.08,y+dim+0.08,z+dim-0.08);
		glTexCoord2f(1, 1);glVertex3f(x+dim+0.08,y+dim+0.08,z+dim-0.08);
		glTexCoord2f(1, 0.0f);glVertex3f(x+dim+0.08,y-0.08,z+dim-0.08);
	glEnd();	

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
		glColor3f(1.0,1.0,1.0);									//draw top face
		glTexCoord2f(0.0f, 1.0f);glVertex3f(x-0.08,y+dim,z);
		glTexCoord2f(1.0f, 1);glVertex3f(x+dim+0.08,y+dim,z);
		glTexCoord2f(1, 0);glVertex3f(x+dim+0.08,y+dim,z+dim);
		glTexCoord2f(0, 0.0f);glVertex3f(x-0.08,y+dim,z+dim);
	glEnd();	
	
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
		glColor3f(1.0,1.0,1.0);									//draw left face
		glTexCoord2f(0.0f, 0.0f);glVertex3f(x,y-0.08,z);
		glTexCoord2f(0.0f, 1);glVertex3f(x,y+dim+0.08,z);
		glTexCoord2f(1, 1);glVertex3f(x,y+dim+0.08,z+dim);
		glTexCoord2f(1, 0.0f);glVertex3f(x,y-0.08,z+dim);
	glEnd();	
	
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
		glColor3f(1.0,1.0,1.0);									//draw right face
		glTexCoord2f(1.0f, 0.0f);glVertex3f(x+dim,y-0.08,z);
		glTexCoord2f(0.0f, 0);glVertex3f(x+dim,y-0.08,z+dim);
		glTexCoord2f(0, 1);glVertex3f(x+dim,y+dim+0.08,z+dim);
		glTexCoord2f(1, 1.0f);glVertex3f(x+dim,y+dim+0.08,z);
	glEnd();
	
	
	glMatrixMode(GL_MODELVIEW);	


}*/
void bigCub(float x, float y, float z,int dim)									//draw the room
{
//	glRotatef(90,1,0,0);
	glTranslatef(xDimension/2,zDimension/2,0);

	glBindTexture(GL_TEXTURE_2D, texture[21+level]);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glEnable( GL_TEXTURE_2D );
	glEnable(GL_TEXTURE_GEN_R);	

	glColor3f(1,1,1);
	CSphere(0,0,0,60,100);

	glDisable(GL_TEXTURE_GEN_R);
	glDisable( GL_TEXTURE_2D );
}

//---------------------------------
//---------------------------------

void drawMenu(float x, float y, float z,int dim,int texturen)				//draw the main menu
{

	glMatrixMode(GL_MODELVIEW);

	glEnable( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, texture[texturen]);
	glBegin(GL_QUADS);
		glColor3f(1.0,1.0,1.0);                                 //draw front face
		glTexCoord2f(0.0f, 0);glVertex3f(x,y,z);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(x+dim,y,z);
		glTexCoord2f(1, 1);glVertex3f(x+dim,y+dim,z);
		glTexCoord2f(0, 1.0f);glVertex3f(x,y+dim,z);
	glEnd();	
}

//---------------------------------
//---------------------------------


static void idle(void)										// Game loop
{
 
	

	
   if(!done)                                                       //while not done
   {
	   	
	  if((!pause)&&(!GameEnd))
	  {	  
		if(cnt>=lSpeed)                                                
		{
			
			if((checkCollisionsMove(xPosition,yPosition-1,zPosition))&&(yPosition>(0-getFreeBottom())))
			{
				yPosition -= 1;
				cnt=0;
				checkFinish();
				
			}
			else
			{
				convertBlockToStaticWorld(moveBloc);				//converts the moveing blocs to static ones
				checkPlanes(xDimension,yDimension,zDimension);										//checks for complet planes in the world space
				initVars();											//initialization of the variables
				generateNewBlock();									//generates a new block
				checkFinish();										// checks the finish conditons
				cnt=0;
				checkLevel();		
			}
			
		}
		
		cnt++;
	  }
	  else
	  {
		  if(GameEnd)
		  {
			  
			  if(ffTime)
			  {
				  playSound(10);
				  ffTime=FALSE;
			  }
			  if(endGameCount<200)
			  {
				endGameCount++;
			  }
			  else
			  {
				done=TRUE;
				endGameCount=0;
			  }
		  }
		  
	  };
   }
   else                                                              //when done do this
   {
	   playSound(0);
		
   }
	glutPostRedisplay();
}

//---------------------------------
//---------------------------------

void display()														//display function: generates the final image
{
	if(!done)
	{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glPushMatrix();
	glEnable(GL_DEPTH_TEST);	
	if(fistS==TRUE)
	{
		if(xDimension!=8)
		{
			dimchange=1;

		}
		fistS=FALSE;
	}
	if(xDimension==8)                                               // generates the mouse wheel zoom efect and floor centering
	{	
			
			if(dimchange==1)
			{
				glTranslatef(4,trans(),trans()*2);
			}
			else
				glTranslatef(0,trans(),trans()*2);
			
			
	}
	else
	{
			
			if(dimchange==1)
			{
				glTranslatef(-0.25,trans(),trans()*2);
			}
			else
			{
				glTranslatef(-4,trans(),trans()*2);
			}
	}
	glPushMatrix();
			
			glTranslatef((xDimension/2),0,(zDimension/2));
			glRotatef(angle2, 1.0, 0.0, 0.0);								// Perform scene rotations based on user mouse input. 
			glRotatef(angle, 0.0, 1.0, 0.0);								// Perform scene rotations based on user mouse input.
			glTranslatef(-(xDimension/2),0,-(zDimension/2));
				glPushMatrix();
						bigCub(-45,-50,-45,100);
				glPopMatrix();
			drawWorld(invrt);													//draw the static cubs
			drawFloor();													// draw the floor
			glDisable( GL_TEXTURE_2D );
			
			glPushMatrix();													// draw the four engines
				glTranslatef(-0.50,-2,-0.50);	
				glScalef(0.3,0.3,0.3);
				
					glEnable( GL_TEXTURE_2D );
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);	
					glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);			
					glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);			
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glBindTexture(GL_TEXTURE_2D, texture[5]);
				glColor3f(1,0,0);	
				drawFlr(cone);
				glColor3f(1,1,1);
				drawFlr(tub);
					glDisable(GL_TEXTURE_GEN_S);
					glDisable(GL_TEXTURE_GEN_T);
					glDisable( GL_TEXTURE_2D );
				glPushMatrix();
							glEnable (GL_TEXTURE_GEN_S);
							glEnable (GL_TEXTURE_GEN_T);
							glEnable (GL_TEXTURE_GEN_R);
							glEnable (GL_TEXTURE_2D);
							glBindTexture (GL_TEXTURE_2D, texture[3]);
							glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_MODULATE);
							glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_MODULATE);
							glTexGeni (GL_R, GL_TEXTURE_GEN_MODE, GL_MODULATE);			
					glColor3f(1,1,1);
					drawFlr(frame);
							glDisable (GL_TEXTURE_2D);
							glDisable (GL_TEXTURE_GEN_S);
							glDisable (GL_TEXTURE_GEN_T);
							glDisable (GL_TEXTURE_GEN_R);
				glPopMatrix();
				glColor3f(1,1,0);
					glPushMatrix();	
						glRotatef(calcangl(), 0.0, 1.0, 0.0);
						drawFlr(prop);
					glPopMatrix();
					

			glPopMatrix();
			

			glPushMatrix();
				glTranslatef(xDimension+0.45,-2,-0.50);	
				glScalef(0.3,0.3,0.3);
					glEnable( GL_TEXTURE_2D );
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);	
					glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);			
					glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);			
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glBindTexture(GL_TEXTURE_2D, texture[5]);
				glColor3f(1,0,0);	
				drawFlr(cone);
				glColor3f(1,1,1);
				drawFlr(tub);
					glDisable(GL_TEXTURE_GEN_S);
					glDisable(GL_TEXTURE_GEN_T);
					glDisable( GL_TEXTURE_2D );
				glPushMatrix();
							glEnable (GL_TEXTURE_GEN_S);
							glEnable (GL_TEXTURE_GEN_T);
							glEnable (GL_TEXTURE_GEN_R);
							glEnable (GL_TEXTURE_2D);
							glBindTexture (GL_TEXTURE_2D, texture[3]);
							glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_MODULATE);
							glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_MODULATE);
							glTexGeni (GL_R, GL_TEXTURE_GEN_MODE, GL_MODULATE);			
					glColor3f(1,1,1);
					drawFlr(frame);
							glDisable (GL_TEXTURE_2D);
							glDisable (GL_TEXTURE_GEN_S);
							glDisable (GL_TEXTURE_GEN_T);
							glDisable (GL_TEXTURE_GEN_R);
				glPopMatrix();
				glColor3f(1,1,0);
					glPushMatrix();	
						glRotatef(calcangl(), 0.0, 1.0, 0.0);
						drawFlr(prop);
					glPopMatrix();
					
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(-0.50,-2,zDimension+0.55);	
				glScalef(0.3,0.3,0.3);
					glEnable( GL_TEXTURE_2D );
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);	
					glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);			
					glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);			
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glBindTexture(GL_TEXTURE_2D, texture[5]);
				glColor3f(1,0,0);	
				drawFlr(cone);
				glColor3f(1,1,1);
				drawFlr(tub);
					glDisable(GL_TEXTURE_GEN_S);
					glDisable(GL_TEXTURE_GEN_T);
					glDisable( GL_TEXTURE_2D );
				glPushMatrix();
							glEnable (GL_TEXTURE_GEN_S);
							glEnable (GL_TEXTURE_GEN_T);
							glEnable (GL_TEXTURE_GEN_R);
							glEnable (GL_TEXTURE_2D);
							glBindTexture (GL_TEXTURE_2D, texture[3]);
							glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_MODULATE);
							glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_MODULATE);
							glTexGeni (GL_R, GL_TEXTURE_GEN_MODE, GL_MODULATE);			
					glColor3f(1,1,1);
					drawFlr(frame);
							glDisable (GL_TEXTURE_2D);
							glDisable (GL_TEXTURE_GEN_S);
							glDisable (GL_TEXTURE_GEN_T);
							glDisable (GL_TEXTURE_GEN_R);
				glPopMatrix();
				glColor3f(1,1,0);
					glPushMatrix();	
						glRotatef(calcangl(), 0.0, 1.0, 0.0);
						drawFlr(prop);
					glPopMatrix();
					
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(xDimension+0.50,-2,zDimension+0.55);	
				glScalef(0.3,0.3,0.3);
					glEnable( GL_TEXTURE_2D );
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);	
					glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);			
					glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);			
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glBindTexture(GL_TEXTURE_2D, texture[5]);
				glColor3f(1,0,0);	
				drawFlr(cone);
				glColor3f(1,1,1);
				drawFlr(tub);
					glDisable(GL_TEXTURE_GEN_S);
					glDisable(GL_TEXTURE_GEN_T);
					glDisable( GL_TEXTURE_2D );
				glPushMatrix();
							glEnable (GL_TEXTURE_GEN_S);
							glEnable (GL_TEXTURE_GEN_T);
							glEnable (GL_TEXTURE_GEN_R);
							glEnable (GL_TEXTURE_2D);
							glBindTexture (GL_TEXTURE_2D, texture[3]);
							glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_MODULATE);
							glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_MODULATE);
							glTexGeni (GL_R, GL_TEXTURE_GEN_MODE, GL_MODULATE);			
					glColor3f(1,1,1);
					drawFlr(frame);
							glDisable (GL_TEXTURE_2D);
							glDisable (GL_TEXTURE_GEN_S);
							glDisable (GL_TEXTURE_GEN_T);
							glDisable (GL_TEXTURE_GEN_R);
				glPopMatrix();
				glColor3f(1,1,0);
				glPushMatrix();	
						glRotatef(calcangl(), 0.0, 1.0, 0.0);
						drawFlr(prop);
				glPopMatrix();
				

			glPopMatrix();
			
			drawAxes();
			drawBlock(xPosition,yPosition,zPosition,1);                     // the falling block           
			drawShadow();                                                   // draw the fallsing block shadow;
			
			//draw the 4 particle sistems
		glPushMatrix();
			glPushMatrix();	
					glTranslatef(-0.50,-2,-0.50);	
					glScalef(0.3,0.3,0.3);
					glPushMatrix();	
						glScalef(1,2,1);
						glTranslatef(0,2,40);	
						DrawGLFire();  
					glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(xDimension+0.45,-2,-0.50);	
				glScalef(0.3,0.3,0.3);
					glPushMatrix();
						glScalef(1,2,1);
						glTranslatef(0,2,40);	
						DrawGLFire();
					glPopMatrix();
			glPopMatrix();
			
			glPushMatrix();	
				glTranslatef(-0.50,-2,zDimension+0.55);	
				glScalef(0.3,0.3,0.3);
					glPushMatrix();	
						glScalef(1,2,1);
						glTranslatef(0,2,40);	
						DrawGLFire();   
					glPopMatrix();
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(xDimension+0.50,-2,zDimension+0.55);	
				glScalef(0.3,0.3,0.3);
					glPushMatrix();
						glScalef(1,2,1);
						glTranslatef(0,2,40);	
						DrawGLFire();
					glPopMatrix();		
			glPopMatrix();
		glPopMatrix();


	glPopMatrix();
	glDisable(GL_DEPTH_TEST);
	
	glPopMatrix();

	
	glPushMatrix();
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
			glPushMatrix();
				glTranslatef(-0.95,0.7,0);
				glPushMatrix();
					glRotatef(-45, 0, 1, 0);
					glRotatef(-45, 1, 0, 0);
					glScalef(0.05,0.05,0.05);
					drawBlock(0.5,0.5,0.5,0);										//draw the next block
				glPopMatrix();
				glPushMatrix();
						glTranslatef(0.05,0.29,0.5);
						glRotatef(-90, 1, 0, 0);
						glRotatef(95, 0, 1, 0);
						glScalef(0.08,0.08,0.08);
						glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
						glEnable(GL_BLEND);
						glColor4f(0,0,0,0.5);
						drawFlr(banner);
							glEnable (GL_TEXTURE_GEN_S);
							glEnable (GL_TEXTURE_GEN_T);
							glEnable (GL_TEXTURE_GEN_R);
							glEnable (GL_TEXTURE_2D);
							glBindTexture (GL_TEXTURE_2D, texture[19]);
							glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
							glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
							glTexGeni (GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
							glDisable (GL_DEPTH_TEST);
						glColor4f(1.0,1.0,1.0,0.9);
						//glShadeModel(GL_SMOOTH);
						drawFlr(circle);
							glEnable (GL_DEPTH_TEST);
							glDisable (GL_TEXTURE_2D);
							glDisable (GL_TEXTURE_GEN_S);
							glDisable (GL_TEXTURE_GEN_T);
							glDisable (GL_TEXTURE_GEN_R);	
						glDisable(GL_BLEND);

				glPopMatrix();		
			glPopMatrix();
			glPushMatrix();
				glLoadIdentity();
				glTranslatef(0.0,0.0,-0.5);
				glColor3f(1,1,1);                                            //draw top right messages
				glRasterPos2f(0.6f, 0.9f);
				itoa(score, points, 10);
				strcpy (str,"Score: ");
				strcat (str,points);
				drawStringBig(str);
				glRasterPos2f(0.6f, 0.8f);
				itoa(level, points, 10);
				strcpy (str1,"Level: ");
				strcat (str1,points);
				drawStringBig(str1);
				glPushMatrix();
						glTranslatef(0.75,0.87,0.5);
						glRotatef(-90, 1, 0, 0);
						glScalef(0.14,0.19,0.14);
						glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
						glEnable(GL_BLEND);
						glColor4f(0.0,0.0,0.0,0.5);
						drawFlr(banner1);
							glEnable (GL_TEXTURE_GEN_S);
							glEnable (GL_TEXTURE_GEN_T);
							glEnable (GL_TEXTURE_GEN_R);
							glEnable (GL_TEXTURE_2D);
							glBindTexture (GL_TEXTURE_2D, texture[19]);
							glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
							glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
							glTexGeni (GL_R, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
							glDisable (GL_DEPTH_TEST);
						glColor4f(1.0,1.0,1.0,0.9);
						drawFlr(circle1);
							glEnable (GL_DEPTH_TEST);
							glDisable (GL_TEXTURE_2D);
							glDisable (GL_TEXTURE_GEN_S);
							glDisable (GL_TEXTURE_GEN_T);
							glDisable (GL_TEXTURE_GEN_R);
						glDisable(GL_BLEND);
				glPopMatrix();	
			
				if(pause)               // show "pause" message
				{
					glColor3f(1,1,1);
					glRasterPos2f(-0.1f, 0.0f);
					drawStringBig("PAUSE");
					glColor3f(0.5,0.5,0.5);
					glRasterPos2f(-0.103f, 0.0f);
					drawStringBig("PAUSE");
				}
				if(GameEnd)
				{
					glColor3f(1,1,1);
					glRasterPos2f(0.0f, 0.0f);
					drawStringBig("Game Over");
					glColor3f(0.5,0.5,0.5);
					glRasterPos2f(0.003f, 0.0f);
					drawStringBig("Game Over");

				}
				if(Lsatus[level]==0)
				{
					if(sound==0)     // play level sound
					{
					
						playSound(4);
						sound=1;
					}
					if(timer<100)    //show the "Level # " message for few seconds
					{
					timer++;
					glColor3f(1,1,1);
					glRasterPos2f(0.0f, 0.0f);
					drawStringBig(str1);
					glColor3f(0.5,0.5,0.5);
					glRasterPos2f(0.003f, 0.0f);
					drawStringBig(str1);
					glColor3f(0.0,0.0,0.0);
					glRasterPos2f(0.006f, 0.0f);
					drawStringBig(str1);
					}
					else
					{
						Lsatus[level]=1;
						timer=0;
						sound=0;
					}
				}
			
			glPopMatrix();
		glDisable(GL_DEPTH_TEST);
		glPopMatrix();
	glutSwapBuffers();
	}
	else
	{
		if(Mmenu==TRUE)   //main menu
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			glPushMatrix();
			glEnable(GL_DEPTH_TEST);
			glLoadIdentity();
		
		
			

			drawMenu(-1, -1, 0,2,6);    //draw the main menu ng		
			drawButton(-0.4, 0.4, 0, 1, Mnu[0]);             //draw start button
			drawButton(-0.4, 0.1, 0, 2, Mnu[1]);			//draw controls button
			drawButton(-0.4, -0.2, 0, 5, Mnu[2]);			//draw settingd button
			drawButton(-0.4, -0.5, 0, 3, Mnu[3]);			//draw about button
			drawButton(-0.4, -0.8, 0, 4, Mnu[4]);			//draw exit button
			

			glDisable(GL_DEPTH_TEST);
			glPopMatrix();
			glutSwapBuffers();
		}
		else
		{
			if(Omenu==TRUE)  //controls menu
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
				glPushMatrix();
				glEnable(GL_DEPTH_TEST);
				glLoadIdentity();
				drawMenu(-1, -1, 0,2,6);    //draw the main menu 		
				
				for(q=0;q<17;q++)
				{
					printString(-0.7, 0.65-q/11.0,keysD[q]);
					printString(0.2,  0.65-q/11.0,keysT[q]);
				}
				glPopMatrix();
			   glutSwapBuffers();
			}
			if(Amenu==TRUE)		//about menu	
				{
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
					glPushMatrix();
					glEnable(GL_DEPTH_TEST);
					glLoadIdentity();
					drawMenu(-1, -1, 0,2,6);    //draw the main menu bg		
					printString(-0.25,0.4,"Created by Alin Aron Oana");
					printString(-0.25,0.3,"alin_aron_oana@yahoo.ca");
					printString(-0.07,-0.35,"Enjoy!");
					glPopMatrix();
					glutSwapBuffers();
				}
			if(Smenu==TRUE)    //settings menu
				{
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
					glPushMatrix();
					glEnable(GL_DEPTH_TEST);
					glLoadIdentity();
					drawMenu(-1, -1, 0,2,6);    //draw the main menu bg		
					
					
					glColor3f(0,0,0);
					glRasterPos2f(-0.2f, 0.0f);
					drawStringBig("Difficulty : ");
					glRasterPos2f(-0.205f, 0.0f);
					drawStringBig("Difficulty : ");
					glRasterPos2f(0.0f, 0.0f);
				    if(Snu[0]==1)
					{
						drawStringBig(setText[0]);
						glRasterPos2f(0.005f, 0.0f);
						drawStringBig(setText[0]);
					}
					if(Snu[1]==1)
					{
						drawStringBig(setText[1]);
						glRasterPos2f(0.005f, 0.0f);
						drawStringBig(setText[1]);
					}
					glRasterPos2f(-0.27f, -0.7f);
					drawStringBig("Left & Right arrows to select");
					glRasterPos2f(-0.274f, -0.7f);
					drawStringBig("Left & Right arrows to select");
					
					glRasterPos2f(-0.27f, -0.8f);
					drawStringBig("[Esc] - return to main menu");
					glRasterPos2f(-0.274f, -0.8f);
					drawStringBig("[Esc] - return to main menu");
					glPopMatrix();
					glutSwapBuffers();
				}
			
		}

	}
//	glutSwapBuffers();
	
}



//---------------------------------
//---------------------------------

void init()															//initialize the OpenGl environment
{  
  glMatrixMode(GL_MODELVIEW); 
  glEnable(GL_TEXTURE_2D); 								
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);                      // The Type Of Depth Testing To Do
  
  gluPerspective( /* field of view in degree */ 40.0,
  /* aspect ratio */ 1,
  /* Z near */ 20.0, /* Z far */ 200.0);
  //glOrtho(-45,55,-45,55,20,100);
  gluLookAt((xDimension/2), eyey, eyez,										// eye is at (0,38,60) 
			(xDimension/2), 0.0, 0.0,											// center is at (0,0,0) 
			0.0, 1.0, 0.);											// up is in postivie Y direction 
 
	 // set up the lights
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);

	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position3);

	glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT3, GL_POSITION, light_position4);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
   // glEnable(GL_LIGHT1);
	/*glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);*/

  for (loop=0;loop<MAX_PARTICLES;loop++)				// Initials All The Textures
	{
		particle[loop].active=TRUE;								// Make All The Particles Active
		particle[loop].life=0.5f;								// Give All The Particles Full Life
		particle[loop].fade=(rand()%100)/1000.0f+0.003f;	// Random Fade Speed
		particle[loop].xi=((rand()%50)-26.0f)*10.0f;		// Random Speed On X Axis
		particle[loop].yi=((rand()%50)-25.0f)*10.0f;		// Random Speed On Y Axis
		particle[loop].zi=((rand()%50)-25.0f)*10.0f;		// Random Speed On Z Axis
		particle[loop].xg=0.0f;									// Set Horizontal Pull To Zero
		particle[loop].yg=-0.8f;								// Set Vertical Pull Downward
		particle[loop].zg=0.0f;									// Set Pull On Z Axis To Zero
	}

  
  
  // LoadGLTextures();
	LJpegT();
	
	cone=loadOBJ("data/model/cone.obj");
	frame=loadOBJ("data/model/frame.obj");
	tub=loadOBJ("data/model/tub.obj");
	prop=loadOBJ("data/model/prop.obj");
	banner=loadOBJ("data/model/circbk.obj");
	circle=loadOBJ("data/model/circfr.obj");
	banner1=loadOBJ("data/model/panbk.obj");
	circle1=loadOBJ("data/model/panfr.obj");

}

//---------------------------------
//---------------------------------

void createWindowa()												//creates OpenGL window
{

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
//	glutInitWindowSize(800,600);									//Windows dimension are 800x600
	glutCreateWindow("3DTetris");									//Windows title is "3DTetris" 
	
	
	glutFullScreen();
	//glutSetCursor(GLUT_CURSOR_DESTROY);
	
	glutDisplayFunc(display);										//The containt of the windows 

	atexit (cleanup);
	
	glutMouseFunc(mouse);											//Proces mous events
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passive);
	glutIdleFunc(idle);
    

	glutKeyboardFunc(NormalKeys);									//Proces normal keys events
	glutSpecialFunc(SpecialKeys);									//Proces special function keys events	
	glutKeyboardUpFunc(glutKeyboardUpCallback);                   // handels key up events
	glutSpecialUpFunc(glutKeyboardSUpCallback);					  // handels  special key up events
	init();
	glutMainLoop();

}

//---------------------------------
//---------------------------------

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)
{

    alutInit(NULL, 0);												//openAL initialisation
    alGetError();

    
    if (LoadALData() == AL_FALSE)									// Load the wav data.
        return 0;

    SetListenerValues();
	atexit(KillALData);
	 
	if(firstTime)													// if this function has been accesed for the first time
	{
										         	
		
			getDataFromFile("data/structures/blocks.txt");                                      // get block structures from the file 
			firstTime=FALSE;
		
	}
	
	createWindowa();


}