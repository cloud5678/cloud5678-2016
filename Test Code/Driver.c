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

#include "Functions.c"
task usercontrol()
{
	while(true)
	{
  if (0 == 1) {
    warningKiller();
  }
		int shoot = vexRT[Btn7U];
		int intakeForward = vexRT[Btn6U];
		int intakeBackwards = vexRT[Btn6D];
		setShooter(shoot*127);
		setIntake(intakeForward*50, intakeBackwards*50);
		motor[leftFront] = vexRT[Ch1] + vexRT[Ch2];
		motor[rightRear] =  vexRT[Ch1] - vexRT[Ch2];
		motor[leftRear] = vexRT[Ch4] + vexRT[Ch3];
		motor[rightFront] =  vexRT[Ch4] - vexRT[Ch3];
	}
}
