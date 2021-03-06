#pragma config(Motor,  port1,           intake,        tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           conveyer,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           leftShoot1,    tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           leftShoot2,    tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           rightShoot1,   tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           rightShoot2,   tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           frontLeft,     tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port8,           backLeft,      tmotorVex393_MC29, openLoop, reversed, driveLeft)
#pragma config(Motor,  port9,           frontRight,    tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port10,          backRight,     tmotorVex393_HBridge, openLoop, driveRight)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////


	// .....................................................................................
	// Insert user code here.
	// .....................................................................................

	void shoot ( float x)
{
	motor [leftShoot1] = x;
	motor [leftShoot2] = x;
	motor [rightShoot1] = x;
	motor [rightShoot2] = x;
}

void intaked (float x)

{
	motor [intake] = x;
	motor [conveyer] = x;
}
void stopper ()
{
	intaked(0);
}

int ballWait = 650;
void repat ()
{
	shoot (70);
	wait1Msec(2000);
	intaked(65);
	wait1Msec(ballWait);
}
task autonomous()
{

	repat();
	stopper();
	repat();
	stopper();
	repat();
	stopper();
	repat();
	wait1Msec(4000);
	shoot(0);
	intaked(0);

}
/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////
//void driveArcade (int y, int x)
//{
//	motor [frontLeft] = motor [backLeft] = (y+x);
//	motor [frontRight] = motor [backRight] = (y-x);
//}
//void shooter (int y)
//{
//	motor [shooterR] = motor [shooterL] = (y);
//}
//void intake (int x)
//{
//	motor[intake] = motor[conveyer] = x;
//}
//task usercontrol()
//{
//	// User control code here, inside the loop

//	while (true)
//	{
//		driveArcade (vexRT [Ch2],vexRT [Ch1]);
//		shooter (vexRT [Ch3]);
//		int intaker = vexRT[Btn7U];
//		intake(intaker*127);

void driveArcade(int y, int x)
{
	motor[frontLeft] = motor[backLeft] = y - x;
	motor[frontRight] = motor[backRight] = y + x;
}
void setShooter (float x, float y, float z)
{
float sum = x+y+z;
if (sum > 127)sum = 127;
motor[leftShoot1] = motor[rightShoot1] = sum;
  motor[leftShoot2] = motor[rightShoot2] = sum;
}
void setIntake (int x, int y)
{
	motor[intake] = motor[conveyer] = x - y;
}
task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
		// This is the main execution loop for the user control program. Each time through the loop
		// your program should update motor + servo values based on feedback from the joysticks.

		// .....................................................................................
		// Insert user code here. This is where you use the joystick values to update your motors, etc.
		// .....................................................................................
		int driveX = -vexRT[Ch2];
		float shoot = vexRT[Ch3];
		int driveY = vexRT[Ch1] ;
		int intakeForward = vexRT[Btn5U];
		int intakeBackwards = vexRT[Btn5D];
		float slow =vexRT[Btn7D]*60 + vexRT[Btn7R]*65 + vexRT[Btn7L]*70;
		float fast = vexRT[Btn7U]*75;
		driveArcade(driveY * 127 / 128, driveX * 127 / 128);
		setShooter(shoot, fast, slow);
		setIntake(intakeForward*127, intakeBackwards*127);

		// This is the main execution loop for the user control program. Each time through the loop
		// your program should update motor + servo values based on feedback from the joysticks.

		// .....................................................................................
		// Insert user code here. This is where you use the joystick values to update your motors, etc.
		// .....................................................................................
	}
}
