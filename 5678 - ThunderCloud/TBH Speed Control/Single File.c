#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  leftShoot,      sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  rightShoot,     sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           intake,        tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           conveyer,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           leftShoot1,    tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           leftShoot2,    tmotorVex393TurboSpeed_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port5,           rightShoot1,   tmotorVex393TurboSpeed_MC29, openLoop, reversed, encoderPort, I2C_2)
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

// Update inteval (in mS) for the flywheel control loop
#define FW_LOOP_SPEED              25

// Maximum power we want to send to the flywheel motors
#define FW_MAX_POWER              127

// encoder counts per revolution depending on motor
#define MOTOR_TPR_393R          261.333
#define MOTOR_TPR_393S          392
#define MOTOR_TPR_393T          627.2

// encoder tick per revolution
float           ticks_per_rev;          ///< encoder ticks per revolution

// Encoder
long            encoder_counts;         ///< current encoder count
long            encoder_counts_last;    ///< current encoder count

// velocity measurement
float           motor_velocity;         ///< current velocity in rpm
long            nSysTime_last;          ///< Time of last velocity calculation

// TBH control algorithm variables
long            target_velocity;        ///< target_velocity velocity
float           current_error;          ///< error between actual and target_velocity velocities
float           last_error;             ///< error last time update called
float           gain;                   ///< gain
float           driver;                  ///< final drive out of TBH (0.0 to 1.0)
float           drive_at_zero;          ///< drive at last zero crossing
long            first_cross;            ///< flag indicating first zero crossing
float           drive_approx;           ///< estimated open loop drive

// final motor drive
long            motor_drive;            ///< final motor control value

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
///////////////////////////////////////////////
void
FwMotorSet( int value )
{
	motor[leftShoot1] = value;
	motor[leftShoot2] = value;
	motor[rightShoot1] = value;
	motor[rightShoot2] = value;
}

/*-----------------------------------------------------------------------------*/
/** @brief      Get the flywheen motor encoder count                           */
/*-----------------------------------------------------------------------------*/
long
FwMotorEncoderGet()
{
	//return(nMotorEncoder[leftShoot]);
	return(nMotorEncoder[rightShoot]);
}

/*-----------------------------------------------------------------------------*/
/** @brief      Set the controller position                                    */
/** @param[in]  desired velocity                                               */
/** @param[in]  predicted_drive estimated open loop motor drive                */
/*-----------------------------------------------------------------------------*/
void FwVelocitySet( int velocity, float predicted_drive )
{
	// set target_velocity velocity (motor rpm)
	target_velocity = velocity;

	// Set error so zero crossing is correctly detected
	current_error = target_velocity - motor_velocity;
	last_error    = current_error;

	// Set predicted open loop drive value
	drive_approx  = predicted_drive;
	// Set flag to detect first zero crossing
	first_cross   = 1;
	// clear tbh variable
	drive_at_zero = 0;
}

/*-----------------------------------------------------------------------------*/
/** @brief      Calculate the current flywheel motor velocity                  */
/*-----------------------------------------------------------------------------*/
void FwCalculateSpeed()
{
	int     delta_ms;
	int     delta_enc;

	// Get current encoder value
	encoder_counts = FwMotorEncoderGet();

	// This is just used so we don't need to know how often we are called
	// how many mS since we were last here
	delta_ms = nSysTime - nSysTime_last;
	nSysTime_last = nSysTime;

	// Change in encoder count
	delta_enc = (encoder_counts - encoder_counts_last);

	// save last position
	encoder_counts_last = encoder_counts;

	// Calculate velocity in rpm
	motor_velocity = (1000.0 / delta_ms) * delta_enc * 60.0 / ticks_per_rev;
}

/*-----------------------------------------------------------------------------*/
/** @brief      Update the velocity tbh controller variables                   */
/*-----------------------------------------------------------------------------*/
void FwControlUpdateVelocityTbh()
{
	// calculate error in velocity
	// target_velocity is desired velocity
	// current is measured velocity
	current_error = target_velocity - motor_velocity;

	// Calculate new control value
	driver =  driver + (current_error * gain);

	// Clip to the range 0 - 1.
	// We are only going forwards
	if( driver > 1 )
		driver = 1;
	if( driver < 0 )
		driver = 0;

	// Check for zero crossing
	if( sgn(current_error) != sgn(last_error) ) {
		// First zero crossing after a new set velocity command
		if( first_cross ) {
			// Set drive to the open loop approximation
			driver = drive_approx;
			first_cross = 0;
		}
		else
			driver = 0.5 * ( driver + drive_at_zero );

		// Save this drive value in the "tbh" variable
		drive_at_zero = driver;
	}

	// Save last error
	last_error = current_error;
}

/*-----------------------------------------------------------------------------*/
/** @brief     Task to control the velocity of the flywheel                    */
/*-----------------------------------------------------------------------------*/
task FwControlTask()
{
	// Set the gain
	gain = 0.00025;

	// We are using Speed geared motors
	// Set the encoder ticks per revolution
	ticks_per_rev = MOTOR_TPR_393T;

	while(1)
	{
		// Calculate velocity
		FwCalculateSpeed();

		// Do the velocity TBH calculations
		FwControlUpdateVelocityTbh() ;

		// Scale drive into the range the motors need
		motor_drive  = (driver * FW_MAX_POWER) + 0.5;

		// Final Limit of motor values - don't really need this
		if( motor_drive >  127 ) motor_drive =  127;
		if( motor_drive < -127 ) motor_drive = -127;

		// and finally set the motor control value
		FwMotorSet( motor_drive );

		// Run at somewhere between 20 and 50mS
		wait1Msec( FW_LOOP_SPEED );
	}
}
void driveArcade(int y, int x)
{
	motor[frontLeft] = motor[backLeft] = y - x;
	motor[frontRight] = motor[backRight] = y + x;
}
void setIntake (int x, int y)
{
	motor[intake] = motor[conveyer] = x - y;
}
task usercontrol()
{
	float maxRPM = 230;
	// Start the flywheel control task
	startTask( FwControlTask );
	while (true)
	{
	// Different speeds set by buttons
        if( vexRT[ Btn8U ] == 1 )
            FwVelocitySet( .9*maxRPM, 0.80 );//Test These Numbers
        if( vexRT[ Btn8L ] == 1 )
            FwVelocitySet( .8*maxRPM, 0.70 );
        if( vexRT[ Btn8R ] == 1 )
            FwVelocitySet( .7*maxRPM, 0.60 );
        if( vexRT[ Btn8D ] == 1 )
            FwVelocitySet( 00, 0 );
		int driveX = -vexRT[Ch2];
		int driveY = vexRT[Ch1] ;
		int intakeForward = vexRT[Btn5U];
		int intakeBackwards = vexRT[Btn5D];
		driveArcade(driveY * 127 / 128, driveX * 127 / 128);
		setIntake(intakeForward*127, intakeBackwards*127);
		wait1Msec(10);
	}
}