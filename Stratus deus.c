#pragma config(Motor,  port2,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           backLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           frontRight,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           backRight,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           intake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           lifter,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           pooper,        tmotorVex393_MC29, openLoop)
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


void intaked (float x)
{
	motor [intake] = x;
	motor [lifter] = x;
}
void driver (int x)
{
	motor[frontLeft] = x;
	motor[backLeft] = x;
	motor[frontRight] = -x;
	motor[backRight] = -x;
}

	void stopper ()
	{
		intaked(0);
		driver(0);
	}

	task autonomous()
	{

		driver(127);
		wait1Msec(8000);
		driver(0);
		intaked(-127);
		wait1Msec(4000);
		stopper();
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	//
	//                                 User Control Task
	//
	// This task is used to control your robot during the user control phase of a VEX Competition.
	// You must modify the code to add your own robot specific commands here.
	//
	/////////////////////////////////////////////////////////////////////////////////////////
	void setIntake (int x, int y)
	{
		motor[intake] = motor[lifter] = x-y;
	}
	task usercontrol()
	{
		// User control code here, inside the loop

		while (true)
		{
			//All the floats
			float xL = vexRT[Ch4];
			float yL = vexRT[Ch3];
			float xR = vexRT[Ch1];
			float yR = vexRT[Ch2];
			int deadBand = 5;
			int intakeForward = vexRT[Btn6U];
			int intakeBackwards = vexRT[Btn6D];
			setIntake(intakeForward*75, intakeBackwards*75);
			//Drive Code
			motor[frontLeft] = xR + yR;
			motor[backRight] =  xR - yR;
			motor[backLeft] = xL + yL;
			motor[frontRight] =  xL - yL ;
			//Deadband
			if(xL > deadBand || xL < -deadBand)
			{
				xL = xL;
			}
			else
			{
				xL = 0;
			}
			if(yL > deadBand || yL < -deadBand)
			{
				yL = yL;
			}
			else
			{yL = 0;
			}
			if(xR > deadBand || xR < -deadBand)
			{
				xR = xR;
			}
			else
			{xR = 0;
			}
			if(yR > deadBand || yR < -deadBand)
			{
				yR = yR;
			}
			else
			{
				yR = 0;
			}
		}
	}
