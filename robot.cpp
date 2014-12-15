#include <Windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <time.h>
#include <iostream>
#define bending_knee_angle 85.0
#define lift_arms_duck_head_angle 160.0
#define split_angle 80.0
#define jumping_angle 170.0
#define pi 3.14159265359

using namespace std;

typedef struct treenode{
	GLfloat m[16];
	void (*draw)();
	struct treenode *sibling;
	struct treenode *child;
}treenode;

treenode torso_node, neck_node, head_node, rua_node, rla_node, lua_node, lla_node, rul_node, rll_node, lul_node, lll_node;

GLUquadricObj *t, *n, *h, *rua, *rla, *rh, *lua, *lla, *lh, *rul, *rll, *rf, *lul, *lll, *lf, *le, *re, *ns;

int win, lag = 1, state = 0, side = 0, jjtimes = 0;
GLfloat range = 10.0, angle = 0.0;
GLfloat max_angle[6] = {0.0, bending_knee_angle, lift_arms_duck_head_angle, split_angle, jumping_angle, jumping_angle};
int max_lag[6] = {0, 5, 5, 5, 2, 2}; 

GLfloat in_radians(GLfloat x){
	x = (pi*x)/180.0;
	return x;
}

void traverse(treenode* root){

	if(root==NULL)
		return;
	glPushMatrix();
	glMultMatrixf(root->m);
	root->draw();
	if(root->child!=NULL)
		traverse(root->child);
	glPopMatrix();
	if(root->sibling!=NULL)
		traverse(root->sibling);

}

void torso(){

	glPushMatrix();
	glColor3f(0.0,0.5,0.0);
	glRotatef(270.0,1.0,0.0,0.0);
	gluCylinder(t,1.3,1.8,4.5,100,100);
	glPopMatrix();

}

void neck(){

	glPushMatrix();
	glColor3f(1.0,0.835,0.659);
	glTranslatef(0.0,4.5,0.0);
	glRotatef(270.0,1.0,0.0,0.0);
	gluCylinder(n,0.5,0.3,0.7,10,10);
	glPopMatrix();

}

void the_head(){
	
	glPushMatrix();
	glColor3f(1.0,0.835,0.659);
	glTranslatef(0.0,6.1,0.0);
	gluSphere(h,1.2,100,100);
	// right eye
	glPushMatrix();
	glColor3f(51.0/255.0,25.0/255.0,0.0);
	glTranslatef(-0.4,0.2,-1.1);
	gluSphere(re,0.2,100,100);
	glPopMatrix();
	// left eye
	glPushMatrix();
	glColor3f(51.0/255.0,25.0/255.0,0.0);
	glTranslatef(0.4,0.2,-1.1);
	gluSphere(le,0.2,100,100);
	glPopMatrix();
	// nose
	glPushMatrix();
	glColor3f(153.0/255.0,76.0/255.0,0.0);
	glTranslatef(0.0,-0.3,-1.2);
	gluSphere(ns,0.15,100,100);
	glPopMatrix();
	glPopMatrix();

}

void right_upper_arm(){

	glPushMatrix();
	glColor3f(0.404,1.0,0.404);
	glTranslatef(-1.9,2.25,0.0);
	glRotatef(270.0,1.0,0.0,0.0);
	gluCylinder(lua,0.5,0.3,2.25,10,10);
	glPopMatrix();

}

void right_lower_arm(){

	glPushMatrix();
	glColor3f(0.404,1.0,0.404);
	glTranslatef(-1.9,0.0,0.0);
	glRotatef(270.0,1.0,0.0,0.0);
	gluCylinder(lla,0.3,0.5,2.25,10,10);
	// hand
	glPushMatrix();
	glColor3f(1.0,0.835,0.659);
	glTranslatef(0.0,0.0,-0.5);
	gluCylinder(lh,0.3,0.3,0.5,10,10);
	glPopMatrix();
	glPopMatrix();

}

void left_upper_arm(){

	glPushMatrix();
	glColor3f(0.404,1.0,0.404);
	glTranslatef(1.9,2.25,0.0);
	glRotatef(270.0,1.0,0.0,0.0);
	gluCylinder(rua,0.5,0.3,2.25,10,10);
	glPopMatrix();

}

void left_lower_arm(){

	glPushMatrix();
	glColor3f(0.404,1.0,0.404);
	glTranslatef(1.9,0.0,0.0);
	glRotatef(270.0,1.0,0.0,0.0);
	gluCylinder(rla,0.3,0.5,2.25,10,10);
	// hand
	glPushMatrix();
	glColor3f(1.0,0.835,0.659);
	glTranslatef(0.0,0.0,-0.5);
	gluCylinder(rh,0.3,0.3,0.5,10,10);
	glPopMatrix();
	glPopMatrix();

}

void right_upper_leg(){

	glPushMatrix();
	glColor3f(0.73,0.0,0.0);
	glTranslatef(-0.7,-3.0,0.0);
	glRotatef(270.0,1.0,0.0,0.0);
	gluCylinder(lul,0.5,0.6,3.0,10,10);
	glPopMatrix();

}

void right_lower_leg(){

	glPushMatrix();
	glColor3f(1.0,0.835,0.659);
	glTranslatef(-0.7,-5.0,0.0);
	glRotatef(270.0,1.0,0.0,0.0);
	gluCylinder(lll,0.3,0.5,2.0,10,10);
	// foot
	glPushMatrix();
	glColor3f(0.0,0.0,0.0);
	glTranslatef(0.0,0.0,-0.5);
	gluCylinder(lf,0.4,0.4,0.5,10,10);
	glPopMatrix();
	glPopMatrix();

}

void left_upper_leg(){

	glPushMatrix();
	glColor3f(0.73,0.0,0.0);
	glTranslatef(0.7,-3.0,0.0);
	glRotatef(270.0,1.0,0.0,0.0);
	gluCylinder(rul,0.5,0.6,3.0,10,10);
	glPopMatrix();

}

void left_lower_leg(){

	glPushMatrix();
	glColor3f(1.0,0.835,0.659);
	glTranslatef(0.7,-5.0,0.0);
	glRotatef(270.0,1.0,0.0,0.0);
	gluCylinder(rll,0.3,0.5,2.0,10,10);
	// foot
	glPushMatrix();
	glColor3f(0.0,0.0,0.0);
	glTranslatef(0.0,0.0,-0.5);
	gluCylinder(rf,0.4,0.4,0.5,10,10);
	glPopMatrix();
	glPopMatrix();

}

void myinit(){

	glClearColor(0.423,0.435,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-range,range,-range,range,-range,range);
	glMatrixMode(GL_MODELVIEW);
	
	t = gluNewQuadric();
	gluQuadricDrawStyle(t, GLU_FILL);
	n = gluNewQuadric();
	gluQuadricDrawStyle(n, GLU_FILL);
	h = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_FILL);
	rua = gluNewQuadric();
	gluQuadricDrawStyle(rua, GLU_FILL);
	rla = gluNewQuadric();
	gluQuadricDrawStyle(rla, GLU_FILL);
	rh = gluNewQuadric();
	gluQuadricDrawStyle(rh, GLU_FILL);
	lua = gluNewQuadric();
	gluQuadricDrawStyle(lua, GLU_FILL);
	lla = gluNewQuadric();
	gluQuadricDrawStyle(lla, GLU_FILL);
	lh = gluNewQuadric();
	gluQuadricDrawStyle(lh, GLU_FILL);
	rul = gluNewQuadric();
	gluQuadricDrawStyle(rul, GLU_FILL);
	rll = gluNewQuadric();
	gluQuadricDrawStyle(rll, GLU_FILL);
	rf = gluNewQuadric();
	gluQuadricDrawStyle(rf, GLU_FILL);
	lul = gluNewQuadric();
	gluQuadricDrawStyle(lul, GLU_FILL);
	lll = gluNewQuadric();
	gluQuadricDrawStyle(lll, GLU_FILL);
	lf = gluNewQuadric();
	gluQuadricDrawStyle(lf, GLU_FILL);
	re = gluNewQuadric();
	gluQuadricDrawStyle(re, GLU_FILL);
	le = gluNewQuadric();
	gluQuadricDrawStyle(le, GLU_FILL);
	ns = gluNewQuadric();
	gluQuadricDrawStyle(ns, GLU_FILL);

	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, torso_node.m);
	torso_node.draw = torso;
	torso_node.sibling = NULL;
	torso_node.child = &neck_node;

	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, neck_node.m);
	neck_node.draw = neck;
	neck_node.sibling = &rua_node;
	neck_node.child = &head_node;

	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, head_node.m);
	head_node.draw = the_head;
	head_node.sibling = NULL;
	head_node.child = NULL;
	
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, rua_node.m);
	rua_node.draw = right_upper_arm;
	rua_node.sibling = &lua_node;
	rua_node.child = &rla_node;

	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, rla_node.m);
	rla_node.draw = right_lower_arm;
	rla_node.sibling = NULL;
	rla_node.child = NULL;

	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, lua_node.m);
	lua_node.draw = left_upper_arm;
	lua_node.sibling = &rul_node;
	lua_node.child = &lla_node;

	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, lla_node.m);
	lla_node.draw = left_lower_arm;
	lla_node.sibling = NULL;
	lla_node.child = NULL;

	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, rul_node.m);
	rul_node.draw = right_upper_leg;
	rul_node.sibling = &lul_node;
	rul_node.child = &rll_node;

	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, rll_node.m);
	rll_node.draw = right_lower_leg;
	rll_node.sibling = NULL;
	rll_node.child = NULL;

	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, lul_node.m);
	lul_node.draw = left_upper_leg;
	lul_node.sibling = NULL;
	lul_node.child = &lll_node;

	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, lll_node.m);
	lll_node.draw = left_lower_leg;
	lll_node.sibling = NULL;
	lll_node.child = NULL;

	glLoadIdentity();

}

void display(void){

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	traverse(&torso_node);
	glFlush();

}

void chooseFromMenu(int option){

	/* Only one move can be performed every time.
	If a move is already performed you need to return
	back to "original standing position" in order to
	perform another move. */
	/* When the state is greater than zero then
	the robot performs a move, if it is lower than zero
	then the state is reversed and the robot returns back
	to its original standing position. */

	if(option==1&&state==0){
		state = 1;
		angle = 0.0;
	}
	
	else if(option==2&&state==0){
		state = 2;
		angle = 0.0;
	}

	else if(option==3&&state==0){
		state = 3;
		angle = 0.0;
	}

	else if(option==4&&state==0){
		state = 4;
		angle = 0.0;
	}

	else if(option==5&&state==0){
		state = 5;
		angle = 0.0;
	}

	else if(option==0&&state>0){
		state = -state;
		angle = max_angle[abs(state)];
	}

	else if(option==6){
	
		if(side==0){ // go to side view
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-range,range,-range,range,-range,range);
			glRotatef(-90.0,0.0,1.0,0.0);
			glMatrixMode(GL_MODELVIEW);
			side = 1;
		}
		
		else{ // return back to front view
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-range,range,-range,range,-range,range);
			glRotatef(0.0,0.0,1.0,0.0);
			glMatrixMode(GL_MODELVIEW);
			side = 0;
		}
		
		glutPostRedisplay();
	}
	
	else if(option==7){
		glutDestroyWindow(win);
		exit(0);
	}

}

void findAngle(){

	if(lag<max_lag[abs(state)])
		lag++;
	else{
		if(state>0&&angle<=max_angle[abs(state)]){
			angle++;
			lag = 1;
		}
		// negative (reverse) state 
		else if(state<0&&angle>=0.0){
			angle--;
			lag = 1;
		}
	}

}

void idle(){

	if(state==1||state==-1){
		
		// move upper leg
		glPushMatrix();
		glLoadIdentity();
		glRotatef(angle,1.0,0.0,0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, lul_node.m);
		glPopMatrix();
		
		// move lower leg
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0.0,-3.0,0.0);
		glRotatef(-angle,1.0,0.0,0.0);
		glTranslatef(0.0,3.0,0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, lll_node.m);
		glPopMatrix();
		
		findAngle();
		
		if(state==-1&&angle<0.0)
			state = 0;
		
		glutPostRedisplay();
	
	}
	
	else if(state==2||state==-2){
	
		// move right arm
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0.0,4.5,0.0);
		glRotatef(angle,1.0,0.0,0.0);
		glTranslatef(0.0,-4.5,0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, rua_node.m);
		glPopMatrix();
		
		// move left arm
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0.0,4.5,0.0);
		glRotatef(angle,1.0,0.0,0.0);
		glTranslatef(0.0,-4.5,0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, lua_node.m);
		glPopMatrix();
		
		// duck neck by a smaller angle
		if(angle<=45.0){
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0,4.5,0.0);
			glRotatef(-angle,1.0,0.0,0.0);
			glTranslatef(0.0,-4.5,0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, neck_node.m);
			glPopMatrix();
		}
		
		// duck head by smaller angle after neck is fully ducked
		if(angle>45.0&&angle<=75.0){
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0,4.9,0.0);
			glRotatef(46.0-angle,1.0,0.0,0.0);
			glTranslatef(0.0,-4.9,0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, head_node.m);
			glPopMatrix();
		}
		
		findAngle();
		
		if(state==-2&&angle<0.0)
			state = 0;
		
		glutPostRedisplay();
	
	}

	else if(state==3||state==-3){
	
		glPushMatrix();
		glLoadIdentity();
		glRotatef(angle,0.0,0.0,1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, lul_node.m);
		glPopMatrix();
		
		glPushMatrix();
		glLoadIdentity();
		glRotatef(-angle,0.0,0.0,1.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, rul_node.m);
		glPopMatrix();
		
		// lower body as legs split
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0.0,-(5.5-cos(in_radians(angle))*5.5),0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, torso_node.m);
		glPopMatrix();
		
		findAngle();
		
		if(state==-3&&angle<0.0)
			state = 0;
		
		glutPostRedisplay();
	
	}
	
	else if(state==4||state==-4||state==5||state==-5){
	
		// right upper arm
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(-1.9,4.5,0.0);
		glRotatef(-angle,0.0,0.0,1.0);
		glTranslatef(1.9,-4.5,0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, rua_node.m);
		glPopMatrix();
		
		// right lower arm - bend elbow a few moments after arm has started moving
		if(angle>=60.0&&angle<=60.0+(180.0-max_angle[abs(state)]+45.0)){
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(-1.9,2.25,0.0);
			glRotatef(-angle+60.0,0.0,0.0,1.0);
			glTranslatef(1.9,-2.25,0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, rla_node.m);
			glPopMatrix();
		}
		
		// left upper arm
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(1.9,4.5,0.0);
		glRotatef(angle,0.0,0.0,1.0);
		glTranslatef(-1.9,-4.5,0.0);
		glGetFloatv(GL_MODELVIEW_MATRIX, lua_node.m);
		glPopMatrix();
		
		// left lower arm - bend elbow a few moments after arm has started moving
		if(angle>=60.0&&angle<=60.0+(180.0-max_angle[abs(state)]+45.0)){
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(1.9,2.25,0.0);
			glRotatef(angle-60.0,0.0,0.0,1.0);
			glTranslatef(-1.9,-2.25,0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, lla_node.m);
			glPopMatrix();
		}
		
		// move legs - slower than arms
		if(angle<=90&&int(angle)%2==0){
			// left leg
			glPushMatrix();
			glLoadIdentity();
			glRotatef(angle/2.0,0.0,0.0,1.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, lul_node.m);
			glPopMatrix();
		
			// right leg
			glPushMatrix();
			glLoadIdentity();
			glRotatef(-angle/2.0,0.0,0.0,1.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, rul_node.m);
			glPopMatrix();
			
			// lower body as legs split
			glPushMatrix();
			glLoadIdentity();
			glTranslatef(0.0,-(5.5-cos(in_radians(angle/2.0))*5.5),0.0);
			glGetFloatv(GL_MODELVIEW_MATRIX, torso_node.m);
			glPopMatrix();
		}
		
		findAngle();
		
		if(state==-4&&angle<0.0)
			state = 0;
		// in state 5 - needs to 5 continuous jumping jacks
		else if(state==5&&angle>max_angle[abs(state)]&&jjtimes<5){
			angle = max_angle[abs(state)];
			state = -5;
			jjtimes++;
		}
		else if(state==-5&&angle<0.0){
			if(jjtimes<5){ // 5 continuous jumping jacks have not been performed yet
				angle = 0.0;
				state = 5;
			}
			else{
				jjtimes = 0;
				state = 0;
			}
		}
		
		glutPostRedisplay();
	
	}
	
}

void buildMenu(){

	int menu;
	menu = glutCreateMenu(chooseFromMenu);
	glutAddMenuEntry("Original standing position",0);
	glutAddMenuEntry("Bending knee",1);
	glutAddMenuEntry("Lift arms/duck head",2);
	glutAddMenuEntry("Split",3);
	glutAddMenuEntry("Jumping jack",4);
	glutAddMenuEntry("Quintuple jumping jack", 5);
	glutAddMenuEntry("Side",6);
	glutAddMenuEntry("Quit",7);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50,50);
	win = glutCreateWindow("Robot");
	buildMenu();
	myinit();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	
}