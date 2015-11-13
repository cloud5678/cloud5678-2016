#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in1,    gyro,           sensorNone)
#pragma config(Motor,  port2,           rightFront,    tmotorVex393_MC29, openLoop, driveRight, encoderPort, None)
#pragma config(Motor,  port3,           leftFront,     tmotorVex393_MC29, openLoop, driveLeft, encoderPort, None)
#pragma config(Motor,  port4,           rightRear,     tmotorVex393_MC29, openLoop, driveRight, encoderPort, None)
#pragma config(Motor,  port5,           leftRear,      tmotorVex393_MC29, openLoop, driveLeft, encoderPort, None)
#pragma config(Motor,  port6,           intake1,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           intake2,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           shooterL,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           shooterR,      tmotorVex393_MC29, openLoop, reversed)

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Driver.c"
#include "Auton.c"
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
  bStopTasksBetweenModes = false;

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


/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////
