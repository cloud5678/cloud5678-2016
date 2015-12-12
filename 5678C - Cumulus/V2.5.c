#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in1,    gyro,           sensorNone)
#pragma config(Motor,  port1,           shooterLB,     tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           intake1,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           intake2,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           leftRear,      tmotorVex393_MC29, openLoop, driveLeft, encoderPort, None)
#pragma config(Motor,  port5,           leftFront,     tmotorVex393_MC29, openLoop, driveLeft, encoderPort, None)
#pragma config(Motor,  port6,           rightRear,     tmotorVex393_MC29, openLoop, driveRight, encoderPort, None)
#pragma config(Motor,  port7,           rightFront,    tmotorVex393_MC29, openLoop, driveRight, encoderPort, None)
#pragma config(Motor,  port8,           shooterL,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           shooterR,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          shooterRB,     tmotorVex393_HBridge, openLoop)
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
void warningKiller() {
	UserControlCodePlaceholderForTesting();
	AutonomousCodePlaceholderForTesting();
}

void pre_auton()
{
	wait1Msec(2000);

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
/*void errorLeft ()
{
motor[leftRear] = 127;
motor[leftFront] = 127;
motor[rightRear] = 100;
motor[rightFront] = 100;
}
void errorRight ()
{
motor[leftRear] = 100;
motor[leftFront] = 100;
motor[rightRear] = 127;
motor[rightFront] = 127;
}*/
void drive(int speed)//Some of these might need to be made negative
{
	motor [leftFront] = speed;
	motor [rightFront] = -speed;
	motor [leftRear] = speed;
	motor [rightRear] = -speed;
}
void rotateL(int speed)//Test this
{
	motor [leftFront] = -speed;
	motor [rightFront] = speed;
	motor [leftRear] = -speed;
	motor [rightRear] = speed;
}
void rotateR(int speed)//Test this
{
	motor [leftFront] = speed;
	motor [rightFront] = -speed;
	motor [leftRear] = speed;
	motor [rightRear] = -speed;
}
void intake(int speed)
{
	motor[intake1] = motor[intake2] = speed;
}
void shoot(int speed)
{
	motor [shooterL] = motor[shooterR] = motor[shooterLB] = motor[shooterRB] = speed;
}
void stopAll()
{
	drive(0);
	intake(0);
	shoot(0);
}
task autonomous()
{
	//Old Auton, Keep Until new one is Proven

	/*
	drive(127);
	wait1Msec(7000);//Test this

	motor[shooterL] = motor[shooterR] = 127;
	drive(0);
	wait1Msec(3000);

	motor[shooterL] = motor[shooterR] = 0;
	drive(0);
	*/
	//Adujust Times Below

	//Ball One

	shoot(127);
	wait1Msec(1000);
	intake(127);
	wait1Msec(750);
	intake(0);
	wait1Msec(750);

	//Ball Two

	shoot(127);
	wait1Msec(1000);
	intake(127);
	wait1Msec(750);
	intake(0);
	wait1Msec(750);

	//Ball Three

	shoot(127);
	wait1Msec(1000);
	intake(127);
	wait1Msec(750);
	intake(0);
	wait1Msec(750);

	//Ball Four

	shoot(127);
	wait1Msec(1000);
	intake(127);
	wait1Msec(750);
	intake(0);
	wait1Msec(750);

	//All Stop

	stopAll();

}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////
void setShooter (int x)
{
	motor[shooterL] = motor[shooterR] = motor[shooterLB] = motor[shooterRB] = x;
}
void setIntake (int x, int y)
{
	motor[intake1] = motor[intake2] = x - y;
}
task usercontrol()
{
	while(true)
	{
		//Warning Killer
		if (0 == 1)
		{
			warningKiller();
			rotateL(0);
			rotateR(0);
		}
		//All the ints
		int shoot = vexRT[Btn7U];
		int intakeForward = vexRT[Btn6U];
		int intakeBackwards = vexRT[Btn6D];
		int deadBand = 10;
		//All the floats
		float xL = vexRT[Ch4];
		float yL = vexRT[Ch3];
		float xR = vexRT[Ch1];
		float yR = vexRT[Ch2];
		//Intake & Shooter
		setShooter(shoot*127);
		setIntake(intakeForward*75, intakeBackwards*75);
		//Drive Code
		motor[leftFront] = xR + yR;
		motor[rightRear] =  xR - yR;
		motor[leftRear] = xL + yL;
		motor[rightFront] =  xL - yL ;
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
