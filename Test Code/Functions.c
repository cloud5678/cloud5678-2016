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

void warningKiller() {
	UserControlCodePlaceholderForTesting();
	AutonomousCodePlaceholderForTesting();
}
void setShooter (int x)
{
	motor[shooterL] = motor[shooterR] = x;
}
void setIntake (int x, int y)
{
	motor[intake1] = motor[intake2] = x - y;
}
void drive(int speed)//Some of these might need to be made negative
{	motor [leftFront] = speed;
	motor [rightFront] = -speed;
	motor [leftRear] = speed;
	motor [rightRear] = -speed;
}
void rotateL(int speed)//Test this
{	motor [leftFront] = -speed;
	motor [rightFront] = speed;
	motor [leftRear] = -speed;
	motor [rightRear] = speed;
}
void rotateR(int speed)//Test this
{	motor [leftFront] = speed;
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
	motor [shooterL] = motor[shooterR] = speed;
}
void stopAll()
{
	drive(0);
	intake(0);
	shoot(0);
}
