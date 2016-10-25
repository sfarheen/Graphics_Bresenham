/*
*** FILE NAME   : Bresenham_Algo.c
*** DESCRIPTION : This program draws a Christmas Tree
*** DATE        : February. 2016
*** WRITTEN By  : Farheen Sultana
*/

/*
The program draws a Christmas Tree using Bresenham Line Scan Conversion Algorithm.

The algorithm chooses the best pixels in order to draw a line. 
Data structures Used:
	 Lines [][] - A 2-Dimensional array is used to store the coordinates of line segments. 
	 count - An integer variable controlling the number of lines to be displayed with each right mouse click.

Methods Used:
	draw_jumbo_pixel(int , int) - Takes the midpoint coordinates and draws a 5*5 jumbo pixel 
	bresenham(int, int,int,int) - Takes the x and y coordinates of the two end points of a line, 
									Calculates slope of the line
									Depending on the slope, the appropriate condition is executed, calculating the correct update conditions and the line is drawn.

Program Execution:

Program execution starts from main()
It calls display() method. 
When the right mouse button is clicked, mouse_func() is called.
A count variable is incremented to display each line segment at a time and the display_func() is called again.
The display() method inturn calls bresenham() method with the x and y coordinates of two end points.

In the bresenham function, slope of the line is calculated and depending on the slope, appropriate if else block is executed.
*/

#include <stdio.h>              // standard C libraries
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <GL/glut.h>            // GLUT library
#include "cs_graphics_setup.h"  // Header for CS4250/5250/6250 courses

//@@***********************************************************************************@@
// Constants
#define WINDOW_XS 600 // Window size
#define WINDOW_YS 600

#define WINDOW_NAME "Christmas tree" // Window name

//@@***********************************************************************************@@
// Function prototypes
void display_func(void);
void mouse_func(int button, int state, int x, int y);
void draw_jumbo_pixel(GLint midpt_x, GLint midpt_y);
void bresenham(int x1, int y1, int x2, int y2);

//@@***********************************************************************************@@
//Global Variables

int count = -1;
//A 2-dimensional array with coordinates of the line segments
int lines[22][4] = {
	{ 237, 12, 362, 12 },
	{ 302, 12, 302, 587 },
	{ 302, 92, 12, 62 },
	{ 12, 82, 107, 72 },
	{ 302, 92, 587, 62 },
	{ 587, 82, 492, 72 },
	{ 302, 177, 72, 127 },
	{ 142, 142, 72, 157 },
	{ 302, 177, 527, 127 },
	{ 457, 142, 527, 157 },
	{ 302, 337, 152, 187 },
	{ 202, 237, 152, 287 },
	{ 302, 337, 452, 187 },
	{ 402, 237, 452, 287 },
	{ 302, 487, 207, 307 },
	{ 237, 362, 207, 417 },
	{ 302, 487, 387, 307 },
	{ 362, 362, 387, 417 },
	{ 302, 587, 237, 487 },
	{ 257, 517, 237, 547 },
	{ 302, 587, 367, 487 },
	{ 347, 517, 367, 547 }
};
//@@***********************************************************************************@@
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	init_setup(WINDOW_XS, WINDOW_YS, WINDOW_NAME);

	glutDisplayFunc(display_func); // call back for display event
	glutMouseFunc(mouse_func); // call back for mouse event
	glutMainLoop();

	return 1;
} // end of main()

//@@***********************************************************************************@@
//This function draws a 5*5 jumbo pixel
// Input: Midpoint of the jumbo pixel.
//Draws pixels in green color
void draw_jumbo_pixel(GLint midpt_x, GLint midpt_y)
{
	glColor3f(0, 1, 0); //set pixel color to green
	glBegin(GL_POINTS);
	for (int i = -2; i <= 2; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			glVertex2i(midpt_x + i, midpt_y + j);
		}
	}
	glEnd();
	glFlush();
}

//@@***********************************************************************************@@
//This function displays the output.
// The background color is set to black.
//The line segments are drawn w.r.t count variable.

void display_func(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);   // background color (black)
	glClear(GL_COLOR_BUFFER_BIT);       // clearing the buffer not to keep the color
	int i = 0;

	//Count controls the number of times for loop is executed. This count is incremented with each Right Mouse Click.
	for (i = 0; i <= count; i++)
	{
		bresenham(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
	}
} // end of display_func()

//@@***********************************************************************************@@
//bresenham is the algorithm to draw lines.
//Input:X and Y coordinates of two end points.
// Output: Draws a line on screen.

void bresenham(int x1, int y1, int x2, int y2)
{
	// Use absolute values of dy and dx. 
	int dy = abs(y2 - y1);
	int dx = abs(x2 - x1);
	
	//dfa is actually dfa` , dfb is dfb`  , f is f`;
	//dfa and dfb are the variables used to update decision condition f`
	int dfa, dfb, f;

	int x, y; // Coordinates of pixel chosen to be drawn
	int m = 0; //m =Slope
	int k=0; // Looping variable

	//Calculate slope of the line
	//Avoiding Divide by Zero error
	if (dx != 0)
	{
		m = dy / dx;
	}

	// << ------------------ Vertical Line ----------------------->>
	//Draw vertical Line

	if (dx == 0 && dy != 0)
	{
		if (y1 < y2)
		{
			x = x1;
			y = y1;
		}
		//Light first pixel
		draw_jumbo_pixel(x, y); 

		for (k = 0; k < (dy - 1)/5; ++k)
		{
			y = y + 5;
			draw_jumbo_pixel(x, y);
		}
	}

	//   <<----------------In the case of slope <= 1 ---------------------------->>
	// Calculate initial decision condition f = 2*dy - dx
	// Calculate and store decision value increments; one for choosing point on right/top right/bottom right
	
	if (m <= 1)
	{
		//Calculate update conditions
		dfa = (2 * dy) - (2 * dx);
		dfb = 2 * dy;
		f = 2 * dy - dx;

		//Set the coordinates of first pixel.
		if (x1 < x2)
		{
			x = x1;
			y = y1;
		}
		else
		{
			x = x2;
			y = y2;
			x2 = x1;
			y2 = y1;
		}

		//Light first pixel
		draw_jumbo_pixel(x, y);


		for (k = 0; k < (dx - 1)/5; ++k)
		{
			
			if (f > 0)
			{
				if (y < y2)
				{
					//if f is positive and y < y2, it means that pixel to right and UP must be chosen 
					//next pixel: x+5,y+5
					y = y + 5;                        
					f = f + dfa;
				}
				else
				{
					//if f is positive and y > y2, it means that pixel to right and DOWN must be chosen
					//next pixel: x+5,y-5
					y = y - 5;
					f = f + dfa;
				}
			}
			else
			{
				//if f is negative, then pixel on right must be chosen
				//next pixel: x+5,y
				f = f + dfb;
			}
			x = x + 5;
			// Light pixel
			draw_jumbo_pixel(x, y);
		}
	}

	//   <<----------------In the case of slope > 1 ---------------------------->>
	// Calculate initial decision condition f = 2*dx - dy
	// Calculate and store decision value increments; one for choosing point on top/Top right/top left

	else if (m > 1)
	{
		//Calculate update conditions
		dfa = (2 * dx) - (2 * dy);
		dfb = 2 * dx;
		f = 2 * dx - dy;

		//Set the coordinates of first pixel.
		if (y1 < y2)
		{
			x = x1;
			y = y1;
		}
		else
		{
			x = x2;
			y = y2;
			x2 = x1;
			y2 = y1;
		}

		//Light first pixel
		draw_jumbo_pixel(x, y);


		for (k = 0; k < (dy - 1)/5; ++k)
		{
			if (f > 0)
			{
				if (x > x2)
				{
					//if f is positive and x > x2, it means that pixel to TOP and left must be chosen
					// next pixel: x-5,y+5
					x = x - 5;
					f = f + dfa;
				}
				else
				{
					//if f is positive and x < x2, it means that pixel to TOP and right must be chosen
					//next pixel: x+5, y+5
					x = x + 5;
					f = f + dfa;
				}
			}
			else
			{
				//if f is negative, then pixel on TOP must be chosen
				//next pixel: x,y+5
				f = f + dfb;
			}
			y = y + 5;
			draw_jumbo_pixel(x, y);
		}
	}
	//glFlush();
}

//@@***********************************************************************************@@
void mouse_func(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		count++;
		glutPostRedisplay();
	}
} // end of mouse_func()