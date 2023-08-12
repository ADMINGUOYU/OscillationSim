#include "OscillationSim.h"

constexpr auto PI = 3.141592653589793;
double GRAVITATIONAL_ACC = 9.8;


double osc_length;
double osc_maxAngle_DEG;
double osc_maxAngle_RAD;

double osc_startDisplace_y_circle;
double osc_startDisplace_x_circle;
double osc_maxVelocity;

double circum_Radius;
double circum_linear_velocity;
double circum_angular_velocity_RAD;
double circum_angular_velocity_DEG;
double circum_cycle;

double circum_degree;
double osc_currentVelocity;
double osc_current_x;
double osc_current_y;
double osc_currentAngle_RAD;
double osc_currentAngle_DEG;

double oscPaint_x;
double oscPaint_y;
double cirPaint_x;
double cirPaint_y;
double oscRealPaint_x;
double oscRealPaint_y;
double old_sec_coor_x;
double sec_coor_x;
double sec_coor_cir_y;
double sec_coor_rel_y;

double oscReal_angle_RAD;
double oscReal_angularVelocity_RAD;
//double oscReal_beta;
//double oscReal_w_d;
//double oscReal_f;
double oscReal_ACC;
double oscReal_AngularACC;
double oscReal_velocity;
double oscReal_x;
double oscReal_y;
double oscReal_cycle;
int oscReal_direction;
double oscReal_lastChangeDirection;
double mis;

double allTime;
double intervalTime;
double lastAllTime;
float scale_y;
float scale_x;
float zoom;

bool refresh;

void osc_init(double p_length, double g_input, double p_angle, double i_scale_x, double i_scale_y, double i_zoom) {
	GRAVITATIONAL_ACC = g_input;

	osc_length = p_length;
	osc_maxAngle_DEG = p_angle;
	osc_maxAngle_RAD = ANGLETORAD(osc_maxAngle_DEG);

	osc_startDisplace_y_circle = osc_length * (1 - cos(osc_maxAngle_RAD));
	osc_startDisplace_x_circle = osc_length * sin(osc_maxAngle_RAD);
	osc_maxVelocity = sqrt(2 * GRAVITATIONAL_ACC * osc_length * (1 - cos(osc_maxAngle_RAD)));

	circum_Radius = osc_startDisplace_x_circle;
	circum_linear_velocity = osc_maxVelocity;
	circum_angular_velocity_RAD = osc_maxVelocity / circum_Radius;
	circum_angular_velocity_DEG = ANGLETODEG(circum_angular_velocity_RAD);
	circum_cycle = (2 * PI) / circum_angular_velocity_RAD;

	circum_degree = 0.0;
	osc_currentVelocity = osc_maxVelocity * sin(ANGLETORAD(circum_degree));
	osc_current_x = osc_startDisplace_x_circle;
		// cos(ANGLETORAD(circum_degree))* circum_Radius;
	osc_current_y = osc_startDisplace_y_circle;
		//osc_length - (sqrt(pow(osc_length, 2) + pow(osc_current_x, 2)));
	osc_currentAngle_RAD = asin(osc_current_x / OSC_LENGTH);
	osc_currentAngle_DEG = ANGLETODEG(osc_currentAngle_RAD);

	oscPaint_x = 0.0;
	oscPaint_y = 0.0;
	cirPaint_x = 0.0;
	cirPaint_y = 0.0;
	oscRealPaint_x = 0.0;
	oscRealPaint_y = 0.0;
	old_sec_coor_x = 0.0;
	sec_coor_x = SECOND_COOR_CENTER_X + ((int)(allTime * scale_x) % SECOND_COOR_WIDTH);
	sec_coor_cir_y = 0.0;
	sec_coor_rel_y = 0.0;

	oscReal_angle_RAD = ANGLETORAD(osc_maxAngle_DEG);
	oscReal_angularVelocity_RAD = 0.0;
	oscReal_ACC = 0.0;
	oscReal_AngularACC = 0.0;
	oscReal_velocity = 0.0;
	/*oscReal_beta = 0.05;
	oscReal_w_d = sqrt(GRAVITATIONAL_ACC / osc_length);
	oscReal_f = 0;*/
	oscReal_x = osc_current_x;
	oscReal_y = osc_current_y;
	oscReal_direction = OSC_REAL_DIRECTION_LEFT;
	oscReal_lastChangeDirection = 0.0;
	oscReal_cycle = 0.0;

	mis = 0.0;

	allTime = 0.0;
	intervalTime = 0.0;
	lastAllTime = 0.0;
	scale_x = i_scale_x;
	scale_y = i_scale_y;
	zoom = i_zoom;

	refresh = true;
	return;
}

void updateGraph(double startTime, double runTime, double lastRunTime) {
	allTime = (runTime - startTime) / 1000;
	intervalTime = (runTime - lastRunTime) / 1000;
	lastAllTime = (lastRunTime - startTime) / 1000;
	circum_degree = (allTime) * circum_angular_velocity_DEG;
	
	cirPaint_x = X_Coordinate(circum_degree, circum_Radius);
	cirPaint_y = Y_Coordinate(circum_degree, circum_Radius);

	osc_currentVelocity = osc_maxVelocity * sin(ANGLETORAD(circum_degree));
	osc_current_x = cos(ANGLETORAD(circum_degree)) * circum_Radius;
	osc_currentAngle_RAD = asin(osc_current_x / osc_length);
	osc_current_y = osc_length - osc_length * cos(osc_currentAngle_RAD);
	osc_currentAngle_DEG = ANGLETODEG(osc_currentAngle_RAD);

	/*oscReal_angularVelocity_RAD += (-GRAVITATIONAL_ACC / osc_length * sin(oscReal_angle_RAD) - 2 * oscReal_beta * oscReal_angularVelocity_RAD + oscReal_f * cos(oscReal_w_d * time)) * intervalTime;
	oscReal_angle_RAD += oscReal_angularVelocity_RAD * intervalTime;
	oscReal_x = sin(oscReal_angle_RAD) * circum_Radius;
	oscReal_y = osc_length - osc_length * cos(oscReal_angle_RAD);*/

	oscReal_ACC = - GRAVITATIONAL_ACC * sin(oscReal_angle_RAD);
	oscReal_AngularACC = oscReal_ACC / osc_length;
	//double  old_oscReal_velocity = oscReal_velocity;
	oscReal_velocity += oscReal_AngularACC * intervalTime;
	//double oscRealDisplace = (pow(oscReal_velocity, 2) - pow(old_oscReal_velocity, 2)) / (2 * oscReal_ACC);
	oscReal_angle_RAD += oscReal_velocity  * intervalTime;
		//asin(oscRealDisplace / osc_length);

	double old_oscReal_x = oscReal_x;
	oscReal_x = sin(oscReal_angle_RAD) * osc_length;
	oscReal_y = osc_length - osc_length * cos(oscReal_angle_RAD);

	int old_oscReal_direction = oscReal_direction;

	if (old_oscReal_x < oscReal_x && oscReal_cycle == 0) {
		oscReal_cycle = 2 * allTime;
		mis = ((oscReal_cycle - circum_cycle) / oscReal_cycle) * 100;
		oscReal_direction = OSC_REAL_DIRECTION_RIGHT;
		oscReal_lastChangeDirection = (runTime- startTime) /1000;
	}
	else if (old_oscReal_x - oscReal_x > 0 && oscReal_direction == OSC_REAL_DIRECTION_RIGHT && oscReal_cycle != 0) {
		oscReal_cycle =( oscReal_cycle + 2 * (allTime - oscReal_lastChangeDirection)) / 2;
		mis = ((oscReal_cycle - circum_cycle) / oscReal_cycle) * 100;
		oscReal_direction = OSC_REAL_DIRECTION_LEFT;
		oscReal_lastChangeDirection = (runTime - startTime) / 1000; 
	}
	else if (old_oscReal_x - oscReal_x < 0 && oscReal_direction == OSC_REAL_DIRECTION_LEFT && oscReal_cycle != 0) {
		oscReal_cycle = (oscReal_cycle + 2 * (allTime - oscReal_lastChangeDirection)) / 2;
		mis = ((oscReal_cycle - circum_cycle) / oscReal_cycle) * 100;
		oscReal_direction = OSC_REAL_DIRECTION_RIGHT;
		oscReal_lastChangeDirection = (runTime - startTime) / 1000; 
	}

	old_sec_coor_x = sec_coor_x;
	sec_coor_x = SECOND_COOR_CENTER_X + ((int)(allTime * scale_x) % SECOND_COOR_WIDTH);

	sec_coor_cir_y = SECOND_COOR_CENTER_Y - (osc_current_x * scale_y);
	sec_coor_rel_y = SECOND_COOR_CENTER_Y - (oscReal_x * scale_y);

}


void paintCoordinate(HDC hdc) {
	RECT rect1 = { 0 };
	SetRect(&rect1, 0, 0, COOR_WIDTH, COOR_HEIGHT);
	FillRect(hdc, &rect1, (HBRUSH)COLOR_WINDOW);

	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(80, 80, 80));
	HGDIOBJ nOldPen = SelectObject(hdc, hPen);
	MoveToEx(hdc, 0, COOR_CENTER_Y, NULL);
	LineTo(hdc, COOR_WIDTH, COOR_CENTER_Y);
	MoveToEx(hdc, COOR_CENTER_X, 0, NULL);
	LineTo(hdc, COOR_CENTER_X, COOR_HEIGHT);


	SelectObject(hdc, nOldPen);
	DeleteObject(hPen);
}

void paintOSC_std(HDC hdc) {
	oscPaint_x = COOR_CENTER_X + (osc_current_x * zoom);
	oscPaint_y = COOR_CENTER_Y - (osc_current_y * zoom);


	HPEN hPen = CreatePen(PS_SOLID, 8, RGB(0, 0, 0));
	HGDIOBJ nOldPen = SelectObject(hdc, hPen);
	MoveToEx(hdc, COOR_CENTER_X, COOR_CENTER_Y - (osc_length * zoom), NULL);
	LineTo(hdc, COOR_CENTER_X, COOR_CENTER_Y - (osc_length * zoom));
	
	MoveToEx(hdc, oscPaint_x, oscPaint_y, NULL);
	LineTo(hdc, oscPaint_x, oscPaint_y);

	SelectObject(hdc, nOldPen);
	DeleteObject(hPen);

	hPen = CreatePen(PS_SOLID, 2, RGB(0, 10, 30));
	nOldPen = SelectObject(hdc, hPen);
	MoveToEx(hdc, COOR_CENTER_X, COOR_CENTER_Y - (osc_length * zoom), NULL);
	LineTo(hdc, oscPaint_x, oscPaint_y);

	SelectObject(hdc, nOldPen);
	DeleteObject(hPen);
}

void paintOSC_real(HDC hdc) {
	oscRealPaint_x = COOR_CENTER_X + (oscReal_x * zoom);
	oscRealPaint_y = COOR_CENTER_Y - (oscReal_y * zoom);

	HPEN hPen = CreatePen(PS_SOLID, 8, RGB(0, 255, 127));
	HGDIOBJ nOldPen = SelectObject(hdc, hPen);

	MoveToEx(hdc, oscRealPaint_x, oscRealPaint_y, NULL);
	LineTo(hdc, oscRealPaint_x, oscRealPaint_y);

	SelectObject(hdc, nOldPen);
	DeleteObject(hPen);

	hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 127));
	nOldPen = SelectObject(hdc, hPen);
	MoveToEx(hdc, COOR_CENTER_X, COOR_CENTER_Y - (osc_length * zoom), NULL);
	LineTo(hdc, oscRealPaint_x, oscRealPaint_y);

	SelectObject(hdc, nOldPen);
	DeleteObject(hPen);
}

void paintSubCoordinate(HDC hdc) {
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(80, 80, 80));
	HGDIOBJ nOldPen = SelectObject(hdc, hPen);
	MoveToEx(hdc, SECOND_COOR_CENTER_X, SECOND_COOR_CENTER_Y, NULL);
	LineTo(hdc, SECOND_COOR_CENTER_X + SECOND_COOR_WIDTH, SECOND_COOR_CENTER_Y);
	//MoveToEx(hdc, COOR_CENTER_X, 0, NULL);
	//LineTo(hdc, COOR_CENTER_X, COOR_HEIGHT);
	SelectObject(hdc, nOldPen);
	DeleteObject(hPen);
}

void paintSubCoor_osc_cir(HDC hdc) {
	

	HPEN hPen = CreatePen(PS_SOLID, 5, RGB(28, 28, 28));
	HGDIOBJ nOldPen = SelectObject(hdc, hPen);
	MoveToEx(hdc, sec_coor_x, sec_coor_cir_y, NULL);
	LineTo(hdc, sec_coor_x, sec_coor_cir_y);

	SelectObject(hdc, nOldPen);
	DeleteObject(hPen);
}

void paintSubCoor_osc_rel(HDC hdc) {
	
	

	HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 127));
	HGDIOBJ nOldPen = SelectObject(hdc, hPen);
	MoveToEx(hdc, sec_coor_x, sec_coor_rel_y, NULL);
	LineTo(hdc, sec_coor_x, sec_coor_rel_y);

	SelectObject(hdc, nOldPen);
	DeleteObject(hPen);
}


void printInfo(HDC hdc) {
	RECT rect1 = { 0 };
	SetRect(&rect1, INFO_X, INFO_Y, INFO_X + INFO_WIDTH, INFO_Y + INFO_HEIGHT);
	FillRect(hdc, &rect1, (HBRUSH)COLOR_WINDOW);

	HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 127));
	HGDIOBJ nOldPen = SelectObject(hdc, hPen);

	TCHAR szText[256];
	_stprintf_s(szText, _TEXT("OSC_cycle (by calc): %f"), circum_cycle);
	TextOut(hdc, INFO_X, INFO_Y, szText, wcslen(szText));

	_stprintf_s(szText, _TEXT("OSC_REAL_cycle: %f"), oscReal_cycle);
	TextOut(hdc, INFO_X, INFO_Y + INFO_SPACE, szText, wcslen(szText));

	_stprintf_s(szText, _TEXT("delta: %f%%"), mis);
	TextOut(hdc, INFO_X, INFO_Y + 2 * INFO_SPACE, szText, wcslen(szText));

	SelectObject(hdc, nOldPen);
	DeleteObject(hPen);
}

void paintGraph(HWND hWnd, HDC hdc) {
	
	paintCoordinate(hdc);
	paintOSC_std(hdc);
	paintOSC_real(hdc);
	
	paintSubCoordinate(hdc);
	paintSubCoor_osc_cir(hdc);
	paintSubCoor_osc_rel(hdc);

	printInfo(hdc);

	
	//RECT rect2 = { 0 };
	//SetRect(&rect2, SECOND_COOR_CENTER_X, 0, SECOND_COOR_CENTER_X + SECOND_COOR_WIDTH, SECOND_COOR_HEIGHT);
	if (old_sec_coor_x > sec_coor_x) {
		InvalidateRect(hWnd, NULL, TRUE);
	}
	else {
		InvalidateRect(hWnd, NULL, FALSE);
	}
	

	return;
}












//double x = 0.0;
//double y = 0.0;
//
//for (circum_degree = 0.0; circum_degree <= 360; circum_degree += circum_angular_velocity_DEG / 1000) {
//	x = X_Coordinate(circum_degree, circum_Radius);
//	y = Y_Coordinate(circum_degree, circum_Radius);
//
//	osc_currentVelocity = osc_maxVelocity * sin(ANGLETORAD(circum_degree));
//	osc_current_x = cos(ANGLETORAD(circum_degree)) * circum_Radius;
//	osc_current_y = osc_length * (1 - (sqrt(1 - pow(osc_current_x / osc_length, 2))) / osc_length);
//	osc_currentAngle_RAD = asin(osc_current_x / OSC_LENGTH);
//	osc_currentAngle_DEG = ANGLETODEG(osc_currentAngle_RAD);
//
//	printf("%.12f\n", osc_current_y);
