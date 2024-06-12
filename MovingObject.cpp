/**********************************
-----------------------------------
NAME SURNAME : Sara Zebardast
-----------------------------------
PROBLEMS : None
-----------------------------------
ADDITIONAL FEATURES : Different fogs with various messages appear and disappear in the different parts of the glass if you click on it, and the duck disappears if you click ''d'' button on key board.
**********************************/
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800
#define TIMER_PERIOD  10
#define TIMER_ON         1 // 0:Disable timer, 1:Enable timer
#define D2R 0.017453292
#define PI 3.141592654

// Global Variables
bool show1 = false, show2 = false, show3 = false, show4 = false, duckB = true;
bool activeTimer = true;
int  winWidth, winHeight;
int x = -300, y = 100;
int startx = -300, starty = 100;

// To draw a filled circle
void circle(int x, int y, int r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 3)
        glVertex2f(x + r * cos(i*D2R), y + r * sin(i*D2R));
    glEnd();
}

// Display text with variables
void vprint(int x, int y, void *font, const char *string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
        glutBitmapCharacter(font, str[i]);
}

// draw the wall paper
void wallpaper(){
    glClearColor(1.0, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glLineWidth(3.0);
    glBegin(GL_LINES);
            glColor3ub(255, 182, 193); //pink
            
            // Vertical lines
            for (int x = -600; x <= 600; x += 20) {
                glVertex2f(x, -600);
                glVertex2f(x, 600);
            }
    glEnd();
    
}

// draw the outline of the window
void window1() {
    
    glBegin(GL_POLYGON); // dark brown
        glColor3ub(173, 109, 54);
        glVertex2f(-266, -266);
        glColor3ub(173, 109, 54);
        glVertex2f(266, -266);
        glColor3ub(173, 109, 54);
        glVertex2f(266, 266);
        glColor3ub(173, 109, 54);
        glVertex2f(-266, 266);
    glEnd();
    
 
    glBegin(GL_POLYGON); // light brown
        glColor3ub(205, 133, 63);
        glVertex2f(-250, -250);
        glColor3ub(205, 133, 63);
        glVertex2f(250, -250);
        glColor3ub(205, 133, 63);
        glVertex2f(250, 250);
        glColor3ub(205, 133, 63);
        glVertex2f(-250, 250);
    glEnd();
 
    glBegin(GL_POLYGON); // blue
        glColor3ub(0, 0, 139);
        glVertex2f(-230, -230);
        glVertex2f(230, -230);
        glVertex2f(230, 230);
        glVertex2f(-230, 230);
    glEnd();
    
}

// draw the inside of the window
void window2(){
    
    glBegin(GL_POLYGON); // dark brown edge
        glColor3ub(173, 109, 54);
        glVertex2f(250, -266);
        glVertex2f(266, -266);
        glVertex2f(266, 266);
        glVertex2f(250, 266);
    glEnd();
    
    glBegin(GL_POLYGON); // light brown edge
        glColor3ub(205, 133, 63);
        glVertex2f(230, -250);
        glVertex2f(250, -250);
        glVertex2f(250, 250);
        glVertex2f(230, 250);
    glEnd();
    
    glBegin(GL_POLYGON); // dark brown edge
        glColor3ub(173, 109, 54);
        glVertex2f(-250, 266);
        glVertex2f(-266, 266);
        glVertex2f(-266, -266);
        glVertex2f(-250, -266);
    glEnd();
    
    glBegin(GL_POLYGON); // light brown edge
        glColor3ub(205, 133, 63);
        glVertex2f(-230, 250);
        glVertex2f(-250, 250);
        glVertex2f(-250, -250);
        glVertex2f(-230, -250);
    glEnd();
    
    glBegin(GL_LINES);
        glColor3ub(173, 109, 54);
        glVertex2f(-230, -230);
        glVertex2f(230, -230);
        glVertex2f(230, 230);
        glVertex2f(-230, 230);
    glEnd();
    
    glBegin(GL_LINES);
        glColor3ub(173, 109, 54);
        glVertex2f(-230, -230);
        glVertex2f(-230, 230);
        glVertex2f(230, 230);
        glVertex2f(230, -230);
    glEnd();
    glLineWidth(45);
    
    glBegin(GL_LINES);
        glColor3ub(173, 109, 54);
        glVertex2f(0, 230);
        glVertex2f(0, -230);
        glVertex2f(230, 0);
        glVertex2f(-230, 0);
    glEnd();
    
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3ub(173, 109, 54);
        glVertex2f(0, 230);
        glVertex2f(0, -230);
        glVertex2f(230, 0);
        glVertex2f(-230, 0);
    glEnd();
}

// draw the handles of the window
void handle () {

    glColor3ub(0,0,0);
    circle(-9, 20, 4);
    circle(-9, -20, 4);
    glBegin(GL_LINES);
        glColor3ub(0,0,0);
        glVertex2f(-9, 20);
        glVertex2f(-9, -20);
    glEnd();
    
    glColor3ub(0,0,0);
    circle(9, 20, 4);
    circle(9, -20, 4);
    glBegin(GL_LINES);
        glColor3ub(0,0,0);
        glVertex2f(9, 20);
        glVertex2f(9, -20);
    glEnd();
}

// draw the banner on top of the winodw
void banner (){
    glBegin(GL_POLYGON);
        glColor3ub(255, 248, 231);
        glVertex2f(-250, 300);
        glVertex2f(250, 300);
        glVertex2f(250, 350);
        glVertex2f(-250, 350);
    glEnd();
    
    glBegin(GL_LINES);
        glColor3ub(240, 230, 207);
        glVertex2f(-250, 300);
        glVertex2f(250, 300);
        glVertex2f(-250, 350);
        glVertex2f(250, 350);
        glVertex2f(-250, 300);
        glVertex2f(-250, 350);
        glVertex2f(250, 300);
        glVertex2f(250, 350);
    glEnd();
    
    glColor3ub(0,0,0);
       vprint(-130, 315, GLUT_BITMAP_TIMES_ROMAN_24, "Sara Zebardast's Window");
}

// Draw a half circle
void drawHalfCircle(float cx, float cy,float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 180; i++) {
        float angle = i * 3.14159 / 180;
        float x = cx + radius * cos(angle);
        float y = cy + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// Draw an oval
void drawEllipse(float cx, float cy,float rx, float ry) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159 / 180;
        float x = cx + rx * cos(angle);
        float y = cy + ry * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// draw a UFO (complex object)
void UFO() {
    
    // Body
    glColor3f(0.87, 0.63, 0.87);
    drawEllipse(x, y, 50, 25);
    glColor3f(1.0, 1.0, 1.0);
    drawHalfCircle(x, y+5, 30);
    glColor3f(0.87, 0.63, 0.87);
    drawEllipse(x, y-30, 3, 20);
    drawEllipse(x-20, y-25, 3, 20);
    drawEllipse(x+20, y-25, 3, 20);
    glColor3f(1.0, 1.0, 1.0);
    circle(x, y-5, 4);
    circle(x-15, y-5, 4);
    circle(x+15, y-5, 4);
    circle(x-30, y-5, 4);
    circle(x+30, y-5, 4);
    glColor3f(0.42, 0.77, 0.09);
    drawHalfCircle(x, y+5, 20);
    glColor3f(0, 0, 0);
    circle(x+6, y+16, 3);
    circle(x-6, y+16, 3);
    glColor3f(0.42, 0.77, 0.09);
    drawEllipse(x, y+20, 3, 10);
    
    // light
    glColor3f(0.95, 0.95, 0.5);
    glBegin(GL_TRIANGLES);
        glVertex2f(x, y-30);
        glVertex2f(x-10, y-330);
        glVertex2f(x+10, y-330);
    glEnd();
    
    glBegin(GL_TRIANGLES);
        glVertex2f(x-20, y-30);
        glVertex2f(x-40, y-330);
        glVertex2f(x, y-330);
    glEnd();
    
    glBegin(GL_TRIANGLES);
        glVertex2f(x+20, y-30);
        glVertex2f(x+40, y-330);
        glVertex2f(x, y-330);
    glEnd();
}

//draw a mask layer on each side to cover the UFO while traveling to have a smoother transition
void mask (){
    
    // mask edge Right
    glBegin(GL_POLYGON);
        glColor3ub(255, 204, 204);
        glVertex2f(266, -800);
        glVertex2f(800, -800);
        glVertex2f(800, 800);
        glVertex2f(266, 800);
    glEnd();
    
    glLineWidth(3.0);
    glBegin(GL_LINES);
            glColor3ub(255, 182, 193); //pink
            
            // Vertical lines
            for (int x = 260; x <= 600; x += 20) {
                glVertex2f(x, -600);
                glVertex2f(x, 600);
            }
    glEnd();
    
    // mask edge left
    glBegin(GL_POLYGON);
        glColor3ub(255, 204, 204);
        glVertex2f(-266,800);
        glVertex2f(-800, 800);
        glVertex2f(-800, -800);
        glVertex2f(-266, -800);
    glEnd();
    
    glBegin(GL_LINES);
            glColor3ub(255, 182, 193); //pink
            
            // Vertical lines
            for (int x = -600; x <= -266; x += 20) {
                glVertex2f(x, -600);
                glVertex2f(x, 600);
            }
    glEnd();
}

// top left panel transparent fog
void fog1() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_POLYGON);
        glColor4ub(255, 255, 255, 128);
        glVertex2f(-8, 8);
        glVertex2f(-228, 8);
        glVertex2f(-228, 228);
        glVertex2f(-8, 228);
    glEnd();

    glDisable(GL_BLEND);
    
    //Text
    glColor4ub(0, 0, 0, 128);
    glRasterPos2f(-200, 100);

    const char* text = "Catch me at area 51";
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

// top right panel transparent fog
void fog2() {
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_POLYGON);
        glColor4ub(255, 255, 255, 128);
        glVertex2f(8, 8);
        glVertex2f(228, 8);
        glVertex2f(228, 228);
        glVertex2f(8, 228);
    glEnd();

    glDisable(GL_BLEND);
    
    //Text
    glColor4ub(0, 0, 0, 128);
    glRasterPos2f(30, 100);

    const char* text = "Alien's ARE Real!!!!!";
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

// buttom left panel transparent fog
void fog3() {
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_POLYGON);
        glColor4ub(255, 255, 255, 128);
        glVertex2f(-8, -7);
        glVertex2f(-229, -7);
        glVertex2f(-229, -228);
        glVertex2f(-8, -228);
    glEnd();

    glDisable(GL_BLEND);
    
    //Text
    glColor4ub(0, 0, 0, 128);
    glRasterPos2f(-200, -120);

    const char* text = "What u looking at ^-^ ";
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

// buttom right panel transparent fog
void fog4() {
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_POLYGON);
        glColor4ub(255, 255, 255, 128);
        glVertex2f(8, -8);
        glVertex2f(228, -8);
        glVertex2f(228, -228);
        glVertex2f(8, -228);
    glEnd();

    glDisable(GL_BLEND);
    
    //Text
    glColor4ub(0, 0, 0, 128);
    glRasterPos2f(40, -120);

    const char* text = "I <3 technical math";
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

// cloud
void cloud1() {
    glColor3f(1.0f, 1.0f, 1.0f);
    circle(48, 180, 20);
    circle(75, 180, 20);
    circle(102, 180, 20);
    circle(65, 190, 20);
    circle(92, 190, 20);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    circle(-112, 130, 20);
    circle(-85, 130, 20);
    circle(-58, 130, 20);
    circle(-75, 140, 20);
    circle(-48, 140, 20);
}

// cloud
void cloud2(){
    glColor3f(1.0f, 1.0f, 1.0f);
    circle(48 + 50, 80, 20);
    circle(75 + 50, 80, 20);
    circle(102 + 50, 80, 20);
    circle(65 + 50, 90, 20);
    circle(102 + 50, 90, 20);
}

// draw a duck
void duck(){
    glColor3f(1.0, 1.0, 0.5);
    drawEllipse(-150, -150, 25, 15);
    circle(-125, -130, 13);
    drawEllipse(-145, -170, 3, 8);
    drawEllipse(-155, -170, 3, 8);
    
    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.5, 0.0);
        glVertex2f(-100, -130);
        glVertex2f(-112, -130);
        glVertex2f(-112, -143);
    glEnd();
    
    glColor3f(1.0, 0.8, 0.6);
    circle(-122, -131, 2);
    drawEllipse(-150, -150, 10, 5);
}

// draw the grass
void grass(){
    //grass
    glBegin(GL_POLYGON);
        glColor3ub(144, 238, 144);
        glVertex2f(-228, -228);
        glVertex2f(228, -228);
        glVertex2f(228, -170);
        glVertex2f(-228, -170);
    glEnd();
}

// To display onto window
void display() {
    
    // WALL PAPER
    wallpaper();
    
    // WINDOW
    window1();
    
    // BANNER
    banner();
    
    // Cloud 1
    cloud1();
    
    //grass
    grass();
    
    //duck
    if (duckB) {
        duck();
    }
    
    // UFO
    UFO();
    
    // MASK
    mask();
    
    // WINDOW
    window2();
    
    // Handles
    handle();
    
    // Cloud 2
    cloud2();
    
    // Fog
    if (show1) {
        fog1();
    }
    if (show2) {
        fog2();
    }
    if (show3) {
        fog3();
    }
    if (show4) {
        fog4();
    }
    
    // Handles
    handle();
    
    glutSwapBuffers();
}

// Pause the animaiton using space key
// disapear the duck using d key
void onKeyDown(unsigned char key, int x, int y) {
   
   if (key == ' ')
       activeTimer = !activeTimer;
    
    if (key == 'd')
        duckB = !duckB;
    
    glutPostRedisplay();
}

// Exit when ESC is pressed
void onKeyUp(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);

    glutPostRedisplay();
}

// Click on the window glass to appear fog
void onClick(int button, int state, int x, int y) {
    
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if ( x > 174 && x < 390 && y > 160 && y < 380 ) {
            show1 = !show1;
        }
        glutPostRedisplay();
    }
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if ( x > 410 && x < 630 && y > 160 && y < 380 ) {
            show2 = !show2;
        }
        glutPostRedisplay();
    }
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if ( x > 172 && x < 390 && y > 397 && y < 614 ) {
            show3 = !show3;
        }
        glutPostRedisplay();
    }
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if ( x > 410 && x < 628 && y > 397 && y < 614 ) {
            show4 = !show4;
        }
        glutPostRedisplay();
    }
    printf ("Event: CLK x=%d y=%d\n", x, y ) ;
}

// Resize
void onResize(int w, int h) {
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // Refresh window.
}

// Move the animation accross the plane
#if TIMER_ON == 1
void onTimer(int v) {
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);

    if (activeTimer) {
        // animate the current shape until it touches the edge of the window.
        x = x + 2;
        if (x == 280) {
            x = startx;
        }
    }
    glutPostRedisplay(); //display()
}
#endif

void Init() {
    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Main function
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Sara Zebardast HW1");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    // Keyboard Events
    glutKeyboardFunc(onKeyDown);
    glutKeyboardUpFunc(onKeyUp);

    // Mouse Events
    glutMouseFunc(onClick);

#if  TIMER_ON == 1
    // Timer Event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();
    glutMainLoop();
    return 0;
}
