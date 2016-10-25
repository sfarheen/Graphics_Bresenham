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
	 Lines [][] :
 A 2-Dimensional array is used to store the coordinates of line segments. 
	 Count:
An integer variable controlling the number of lines to be displayed with each right mouse click.

Functions Used:
	draw_jumbo_pixel(int , int) :
 Takes the midpoint coordinates and draws a 5*5 jumbo pixel 
	bresenham(int, int,int,int) :
Takes the x and y coordinates of the two end points of a line				Calculates slope of the line
Depending on the slope, the appropriate condition is executed, calculating the correct update conditions and the line is drawn.

Program Execution:

Program execution starts from main()
It calls display() function. 
When the right mouse button is clicked, mouse_func() is called.
A count variable is incremented to display each line segment at a time and the display_func() is called again.
The display() function inturn calls bresenham() function with the x and y coordinates of two end points.

In the bresenham function, slope of the line is calculated and depending on the slope, appropriate if else block is executed.

*/
