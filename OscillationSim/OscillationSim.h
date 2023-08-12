#pragma once
#include "framework.h"
#include "CWindowsDesktopAPP.h"
#include <stdio.h>
#include <math.h>
#include <time.h>


#define ZOOM 200.0
#define G_ACC 9.8
#define SCALE_X 100.0
#define SCALE_Y 100.0

#define ANGLETORAD(degree) (degree / 180) * PI
#define ANGLETODEG(rad) (rad / PI) * 180


#define OSC_LENGTH 1.0
#define OSC_MAXANGLE_DEG 5.0
//#define OSC_MAXANGLE_RAD(osc_maxAngle_DEG) ANGLETORAD(osc_maxAngle_DEG)
//#define OSC_STARTDISPLACE_y_CIRCLE(osc_maxAngle_DEG) (OSC_LENGTH * (1 - cos(OSC_MAXANGLE_RAD(osc_maxAngle_DEG))))
//#define OSC_STARTDISPLACE_x_CIRCLE(osc_maxAngle_DEG) (OSC_LENGTH * sin(OSC_MAXANGLE_RAD(osc_maxAngle_DEG)))
//#define OSC_MAXVELOCITY(osc_maxAngle_DEG) (sqrt(2 * GRAVITATIONAL_ACC * OSC_LENGTH * (1 - cos(OSC_MAXANGLE_RAD))))

//#define CIRCLE_RADIUS OSC_STARTDISPLACE_x_CIRCLE
//#define CIRCLE_LINEAR_VELOCITY OSC_MAXVELOCITY
//#define ANGULARVELOCITY_RAD (CIRCLE_LINEAR_VELOCITY / CIRCLE_RADIUS)
//#define ANGULARVELOCITY_DEG ANGLETODEG(ANGULARVELOCITY_RAD)
#define X_Coordinate(degree,circle_radius) (cos(ANGLETORAD(degree)) * circle_radius)
#define Y_Coordinate(degree,circle_radius) (sin(ANGLETORAD(degree)) * circle_radius)
//#define CYCLE_CIRCLE ((2 * PI) / ANGULARVELOCITY_RAD)

//#define OSC_CURRENTVELOCITY_USING_CIRCLE(degree) (OSC_MAXVELOCITY * sin(ANGLETORAD(degree)))
////#define OSC_CURRENT_x_CIRCLE(degree) OSC_LENGTH * sin(ANGLETORAD(degree)
//#define OSC_CURRENT_x_CIRCLE(degree) (cos(ANGLETORAD(degree)) * CIRCLE_RADIUS)
////#define OSC_CURRENT_y_CIRCLE(degree) OSC_STARTDISPLACE_y_CIRCLE - (pow(OSC_CURRENTVELOCITY_USING_CIRCLE(degree,OSC_MAXVELOCITY) , 2)) / 2 * GRAVITATIONAL_ACC
//#define OSC_CURRENT_DEGREE_CIRCLE_RAD (asin(OSC_CURRENT_x_CIRCLE(degree) / OSC_LENGTH))
//#define OSC_CURRENT_DEGREE_CIRCLE_DEG (ANGLETODEG(OSC_CURRENT_DEGREE_CIRCLE_RAD))
//#define OSC_CURRENT_y_CIRCLE(degree) (OSC_LENGTH - (sqrt(pow(OSC_LENGTH,2) + pow(OSC_CURRENT_x_CIRCLE(degree),2)) ))

#define OSC_REAL_DIRECTION_LEFT -1
#define OSC_REAL_DIRECTION_RIGHT 1



#define COOR_WIDTH 500
#define COOR_HEIGHT 500
#define COOR_CENTER_X COOR_WIDTH / 2
#define COOR_CENTER_Y COOR_HEIGHT / 2

#define SECOND_COOR_CENTER_X COOR_WIDTH + 20
#define SECOND_COOR_HEIGHT 200
#define SECOND_COOR_WIDTH 500
#define SECOND_COOR_CENTER_Y SECOND_COOR_HEIGHT / 2

#define INFO_X SECOND_COOR_CENTER_X 
#define INFO_Y SECOND_COOR_HEIGHT + 20
#define INFO_WIDTH COOR_WIDTH
#define INFO_HEIGHT 300
#define INFO_SPACE 30


void osc_init(double p_length,double g_input,double p_angle,double i_scale_x,double i_scale_y,double i_zoom);
void updateGraph(double startTime,double runTime , double lastRunTime);
void paintGraph(HWND hWnd ,HDC hdc);
