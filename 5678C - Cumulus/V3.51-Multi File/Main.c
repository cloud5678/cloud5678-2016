#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  leftShoot,      sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  rightShoot,     sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           shooterLB,     tmotorVex393HighSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           shooterL,      tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port3,           intake2,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           leftRear,      tmotorVex393_MC29, openLoop, driveLeft, encoderPort, None)
#pragma config(Motor,  port5,           leftFront,     tmotorVex393_MC29, openLoop, driveLeft, encoderPort, None)
#pragma config(Motor,  port6,           rightRear,     tmotorVex393_MC29, openLoop, driveRight, encoderPort, None)
#pragma config(Motor,  port7,           rightFront,    tmotorVex393_MC29, openLoop, driveRight, encoderPort, None)
#pragma config(Motor,  port8,           intake1,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           shooterR,      tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port10,          shooterRB,     tmotorVex393HighSpeed_HBridge, openLoop, reversed)
#pragma platform(VEX)
/////////////////////////////////////////////////////////////////////////////////////////
//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "Auton Functions.c"
#include "TBH Definitions.c"
#include "TBH Main.c"
#include "Functions.c"
/////////////////////////////////////////////////////////////////////////////////////////
task autonomous()
{
	//Adujust Times Below

	//Ball One

	shoot(speeder);
	wait1Msec(2000);
	intake(127);
	wait1Msec(400);
	intake(0);
	wait1Msec(750);

	//Ball Two
	fire();
	//Ball Three
	fire();
	//Ball Four
	fire();
	//All Stop
	stopAll();

}
///////////////////////////////////////////////////////////////
task usercontrol()
{
	// Start the flywheel control task
	startTask( FwControlTask );
	while(true)
	{
		// Different speeds set by buttons
		if( vexRT[ Btn8L ] == 1 )
			FwVelocitySet( 144, 0.55 );//Test These Numbers
		if( vexRT[ Btn8U ] == 1 )
			FwVelocitySet( 120, 0.38 );
		if( vexRT[ Btn8R ] == 1 )
			FwVelocitySet( 50, 0.2 );
		if( vexRT[ Btn8D ] == 1 )
			FwVelocitySet( 00, 0 );
		wait1Msec(10);

		//Warning Killer
		if (0 == 1)
		{
			warningKiller();
			rotateL(0);
			rotateR(0);
		}
		//Intake
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
		{
			yL = 0;
		}
		if(xR > deadBand || xR < -deadBand)
		{
			xR = xR;
		}
		else
		{
			xR = 0;
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
