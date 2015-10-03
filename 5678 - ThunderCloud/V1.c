#pragma config(Motor,  port1,           rightShooter,  tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftShooter,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           backLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           frontRight,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           backRight,     tmotorVex393_MC29, openLoop)
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
void drive(int speed)
{
	motor [frontLeft] = speed;
	motor [frontRight] = speed;
	motor [backLeft] = speed;
	motor [backRight] = speed;
}
task autonomous()
{
	// .....................................................................................
	// Insert user code here.
	// .....................................................................................


	drive(65);
	wait1Msec(5000);//Test this

	motor[leftShooter] = motor[rightShooter] = 127;
	drive(0);
	wait1Msec(3000);

	motor[leftShooter] = motor[rightShooter] = 0;
	drive(0);
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////
void driveArcade(int y, int x)
{
	motor[frontLeft] = motor[backLeft] = y - x;
	motor[frontRight] = motor[backRight] = y + x;
}
void setShooter (int x)
{
	motor[leftShooter] = motor[rightShooter] = x;
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
		int driveX = vexRT[Ch2];
		int shoot = vexRT[Btn8D];
		int driveY = vexRT[Ch1] ;
		driveArcade(driveY * -127 / 128, driveX * -127 / 128);
		setShooter(shoot*127);

	}
}
