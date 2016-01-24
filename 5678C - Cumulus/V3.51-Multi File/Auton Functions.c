void pre_auton()
{
	bStopTasksBetweenModes = true;
}
int speeder = 73;//How fast the motors spin, assuming full battery power
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
void fire ()
{
	shoot(speeder);
	wait1Msec(1000);
	intake(127);
	wait1Msec(650);
	intake(0);
	wait1Msec(750);
}
void stopAll()
{
	drive(0);
	intake(0);
	shoot(0);
}
