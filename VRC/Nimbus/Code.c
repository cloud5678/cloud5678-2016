#pragma config(Sensor, dgtl1,  touchSensor,    sensorDigitalIn)
#pragma config(Motor,  port1,           leftFront,     tmotorVex393, openLoop)
#pragma config(Motor,  port2,           rightFront,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           leftRear,      tmotorVex393, openLoop)
#pragma config(Motor,  port10,           rightRear,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port5,           leftArm,       tmotorVex393, openLoop)
#pragma config(Motor,  port6,           rightArm,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           leftArm2,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port8,           rightArm2,     tmotorVex393, openLoop)
#pragma config(Motor,  port3,           leftIntake,    tmotorVex393, openLoop)
#pragma config(Motor,  port4,          rightIntake,   tmotorVex393, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

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

task autonomous()
{
  //if (SensorValue(touchSensor) == 0)
  //{
	//Hits first friendly large ball into goal zone. (Total time: 1 second)

	ClearTimer(T1);
	while(time1[T1] < 1000)
	{
  motor[leftFront] = 127;
  motor[leftRear] = 127;
    motor[rightFront] = 127;
  motor[rightRear] = 127;
    motor[leftArm] = 60;
  motor[rightArm] = 60;
  motor[leftArm2] = 60;
  motor[rightArm2] = 60;
	}
	//5 point code. Confirmed to work for 5+, 10+ potential.
	ClearTimer(T1);
	while(time1[T1] < 1000)
	{
  motor[leftFront] = -127;
  motor[leftRear] = -127;
    motor[rightFront] = -127;
  motor[rightRear] = -127;
    motor[leftArm] = -50;
  motor[rightArm] = -50;
  motor[leftArm2] = -50;
  motor[rightArm2] = -50;
	}
	ClearTimer(T1);
	while(time1[T1] < 5000)
	{
  motor[leftFront] = 0;
  motor[leftRear] = 0;
    motor[rightFront] = 0;
  motor[rightRear] = 0;
    motor[leftArm] = 0;
  motor[rightArm] = 0;
  motor[leftArm2] = 0;
  motor[rightArm2] = 0;
  motor[leftIntake] = 0;
		motor[rightIntake] = 0;
	}
		ClearTimer(T1);
	while(time1[T1] < 2000)
	{
  motor[leftFront] = 127;
  motor[leftRear] = 127;
    motor[rightFront] = 127;
  motor[rightRear] = 127;
    motor[leftArm] = 45;
  motor[rightArm] = 45;
  motor[leftArm2] = 45;
  motor[rightArm2] = 45;
	}
	motor[leftFront] = 0;
  motor[leftRear] = 0;
    motor[rightFront] = 0;
  motor[rightRear] = 0;
    motor[leftArm] = 0;
  motor[rightArm] = 0;
  motor[leftArm2] = 0;
  motor[rightArm2] = 0;
  motor[leftIntake] = 0;
		motor[rightIntake] = 0;
}
	//15 point + enemy ball middle zone. Currently does not work, needs testing.
	/*
	//Keeps arm lifted, turns to the right 90 degrees. (Total time: 1.75 seconds)
	ClearTimer(T1);
	while(time1[T1] < 750)
	{
	motor[leftFront] = 127;
  motor[leftRear] = 127;
  motor[rightFront] = -127;
  motor[rightRear] = -127;
  motor[leftArm] = 80;
  motor[rightArm] = 80;
  motor[leftArm2] = 80;
  motor[rightArm2] = 80;
	}
	//Hits second friendly large ball into goal zone. (Total time: 2.75 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1000)
	{
  motor[leftFront] = 127;
  motor[leftRear] = 127;
  motor[rightFront] = 127;
  motor[rightRear] = 127;
  motor[leftArm] = 80;
  motor[rightArm] = 80;
  motor[leftArm2] = 80;
  motor[rightArm2] = 80;
	}
	//Lowers arm in prep for going under barrier, turns to the left 90 degrees. (Total time: 3.5 seconds)
	ClearTimer(T1);
	while(time1[T1] < 750)
	{
  motor[leftFront] = -127;
  motor[leftRear] = -127;
  motor[rightFront] = 127;
  motor[rightRear] = 127;
  motor[leftArm] = -50;
  motor[rightArm] = -50;
  motor[leftArm2] = -50;
  motor[rightArm2] = -50;
	}
	//Moves up to the goal. (Total time: 4.5 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1000)
	{
  motor[leftFront] = 127;
  motor[leftRear] = 127;
  motor[rightFront] = 127;
  motor[rightRear] = 127;
	}
	//Lifts arm. (Total time: 5.5 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1000)
	{
		motor[leftArm] = 80;
		motor[rightArm] = 80;
		motor[leftArm2]= 80;
		motor[rightArm2] = 80;
	}
	//Deposits preloads in goal. (Total time: 7 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1500)
	{
		motor[leftIntake] = 127;
		motor[rightIntake] = 127;
		motor[leftArm] = 80;
		motor[rightArm] = 80;
		motor[leftArm2]= 80;
		motor[rightArm2] = 80;
	}
	//Turns to the right 120 degrees. (Total time: 8 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1000)
	{
		motor[leftArm] = 80;
		motor[rightArm] = 80;
		motor[leftArm2]= 80;
		motor[rightArm2] = 80;
		motor[leftFront] = 127;
		motor[leftRear] = 127;
		motor[rightFront] = -127;
		motor[rightRear] = -127;
	}
	//Hits enemy large ball into middle zone. (Total time: 9.5 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1500)
	{
		motor[leftArm] = 80;
		motor[rightArm] = 80;
		motor[leftArm2]= 80;
		motor[rightArm2] = 80;
		motor[leftFront] = 127;
		motor[leftRear] = 127;
		motor[rightFront] = 127;
		motor[rightRear] = 127;
	}
	//Turns to the left 60 degrees. (Total time: 10 seconds)
	ClearTimer(T1);
	while(time1[T1] < 500)
	{
		motor[leftArm] = 80;
		motor[rightArm] = 80;
		motor[leftArm2]= 80;
		motor[rightArm2] = 80;
		motor[leftFront] = -127;
		motor[leftRear] = -127;
		motor[rightFront] = 127;
		motor[rightRear] = 127;
	}
	//Hits other enemy large ball into middle zone. (Total time: 11 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1000)
	{
		motor[leftArm] = 80;
		motor[rightArm] = 80;
		motor[leftArm2]= 80;
		motor[rightArm2] = 80;
		motor[leftFront] = 127;
		motor[leftRear] = 127;
		motor[rightFront] = 127;
		motor[rightRear] = 127;
	}
	//Turns to the right 135 degrees and lowers arm. (Total time: 12.125 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1125)
	{
		motor[leftArm] = -40;
		motor[rightArm] = -40;
		motor[leftArm2] = -40;
		motor[rightArm2] = -40;
		motor[leftFront] = 127;
		motor[leftRear] = 127;
		motor[rightFront] = -127;
		motor[rightRear] = -127;
	}
	//Travels as far as possible southwest while attempting to pick up more buckyballs. (Time out)
	ClearTimer(T1);
	while(time1[T1] < 2875)
	{
		motor[leftIntake] = 127;
		motor[rightIntake] = 127;
		motor[leftFront] = 127;
		motor[leftRear] = 127;
		motor[rightFront] = 127;
		motor[rightRear] = 127;
	}
}
	while (SensorValue(touchSensor) == 1)
	{
		//Hits first friendly large ball into goal zone. (Total time: 1 second)
	ClearTimer(T1);
	while(time1[T1] < 1000)
	{
  motor[leftFront] = 127;
  motor[leftRear] = 127;
  motor[rightFront] = 127;
  motor[rightRear] = 127;
  motor[leftArm] = 80;
  motor[rightArm] = 80;
  motor[leftArm2] = 80;
  motor[rightArm2] = 80;
	}
	//Keeps arm lifted, turns to the left 90 degrees. (Total time: 1.75 seconds)
	ClearTimer(T1);
	while(time1[T1] < 750)
	{
	motor[leftFront] = -127;
  motor[leftRear] = -127;
  motor[rightFront] = 127;
  motor[rightRear] = 127;
  motor[leftArm] = 80;
  motor[rightArm] = 80;
  motor[leftArm2] = 80;
  motor[rightArm2] = 80;
	}
	//Hits second friendly large ball into goal zone. (Total time: 2.75 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1000)
	{
  motor[leftFront] = 127;
  motor[leftRear] = 127;
  motor[rightFront] = 127;
  motor[rightRear] = 127;
  motor[leftArm] = 80;
  motor[rightArm] = 80;
  motor[leftArm2] = 80;
  motor[rightArm2] = 80;
	}
	//Lowers arm in prep for going under barrier, turns to the right 90 degrees. (Total time: 3.5 seconds)
	ClearTimer(T1);
	while(time1[T1] < 750)
	{
  motor[leftFront] = 127;
  motor[leftRear] = 127;
  motor[rightFront] = -127;
  motor[rightRear] = -127;
  motor[leftArm] = -50;
  motor[rightArm] = -50;
  motor[leftArm2] = -50;
  motor[rightArm2] = -50;
	}
	//Moves up to the goal. (Total time: 4.5 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1000)
	{
  motor[leftFront] = 127;
  motor[leftRear] = 127;
  motor[rightFront] = 127;
  motor[rightRear] = 127;
	}
	//Lifts arm. (Total time: 5.5 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1000)
	{
		motor[leftArm] = 80;
		motor[rightArm] = 80;
		motor[leftArm2] = 80;
  motor[rightArm2] = 80;
	}
	//Deposits preloads in goal. (Total time: 7 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1500)
	{
		motor[leftIntake] = 127;
		motor[rightIntake] = 127;
		motor[leftArm] = 80;
		motor[rightArm] = 80;
		motor[leftArm2] = 80;
  motor[rightArm2] = 80;
	}
	//Turns to the left 120 degrees. (Total time: 8 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1000)
	{
		motor[leftArm] = 80;
		motor[rightArm] = 80;
		motor[leftArm2] = 80;
  motor[rightArm2] = 80;
		motor[leftFront] = -127;
		motor[leftRear] = -127;
		motor[rightFront] = 127;
		motor[rightRear] = 127;
	}
	//Hits enemy large ball into middle zone. (Total time: 9.5 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1500)
	{
		motor[leftArm] = 80;
		motor[rightArm] = 80;
		motor[leftArm2] = 80;
  motor[rightArm2] = 80;
		motor[leftFront] = 127;
		motor[leftRear] = 127;
		motor[rightFront] = 127;
		motor[rightRear] = 127;
	}
	//Turns to the right 60 degrees. (Total time: 10 seconds)
	ClearTimer(T1);
	while(time1[T1] < 500)
	{
		motor[leftArm] = 80;
		motor[rightArm] = 80;
		motor[leftArm2] = 80;
  motor[rightArm2] = 80;
		motor[leftFront] = 127;
		motor[leftRear] = 127;
		motor[rightFront] = -127;
		motor[rightRear] = -127;
	}
	//Hits other enemy large ball into middle zone. (Total time: 11 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1000)
	{
		motor[leftArm] = 80;
		motor[rightArm] = 80;
		motor[leftArm2] = 80;
  motor[rightArm2] = 80;
		motor[leftFront] = 127;
		motor[leftRear] = 127;
		motor[rightFront] = 127;
		motor[rightRear] = 127;
	}
	//Turns to the left 135 degrees and lowers arm. (Total time: 12.125 seconds)
	ClearTimer(T1);
	while(time1[T1] < 1125)
	{
		motor[leftArm] = -40;
		motor[rightArm] = -40;
		motor[leftArm2] = -40;
  motor[rightArm2] = -40;
		motor[leftFront] = -127;
		motor[leftRear] = -127;
		motor[rightFront] = 127;
		motor[rightRear] = 127;
	}
	//Travels as far as possible southeast while attempting to pick up more buckyballs. (Time out)
	ClearTimer(T1);
	while(time1[T1] < 2875)
	{
		motor[leftIntake] = 127;
		motor[rightIntake] = 127;
		motor[leftFront] = 127;
		motor[leftRear] = 127;
		motor[rightFront] = 127;
		motor[rightRear] = 127;
	}
	}
}*/

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

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

		//Arm
	  //Use Left Stick
		motor[leftArm] = 2*(vexRT[Ch3])/3;
		motor[rightArm] = 2*(vexRT[Ch3])/3;
		motor[leftArm2] = 2*(vexRT[Ch3])/3;
		motor[rightArm2] = 2*(vexRT[Ch3])/3;

		//Intake
		//RB Upper is Intake, LB Upper is Output
		if (vexRT[Btn5U] == 1)
		{
			motor[leftIntake] = -127;
			motor[rightIntake] = -127;
		}
		else if (vexRT[Btn6U] == 1)
		{
			motor[leftIntake] = 127;
			motor[rightIntake] = 127;
		}
		else
		{
			motor[leftIntake] = 0;
			motor[rightIntake] = 0;
		}
		//Turning/Straight driving
		//Use Right-Stick
		if((vexRT[Ch1] > 20) || (vexRT[Ch1] < -20))
		{
			motor[leftFront] = (vexRT[Ch2] + vexRT[Ch1]);
			motor[leftRear] = (vexRT[Ch2] + vexRT[Ch1]);
			motor[rightFront] = (vexRT[Ch2] - vexRT[Ch1]);
			motor[rightRear]= (vexRT[Ch2] - vexRT[Ch1]);
		}
		else
		{
			motor[leftFront] = vexRT[Ch2];
			motor[leftRear] = vexRT[Ch2];
			motor[rightFront] = vexRT[Ch2];
			motor[rightRear]= vexRT[Ch2];
		}
	}
}
