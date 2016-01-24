void setIntake (int x, int y)
{
	motor[intake1] = motor[intake2] = x - y;
}
void warningKiller() {
	UserControlCodePlaceholderForTesting();
	AutonomousCodePlaceholderForTesting();
}
//All the ints
int intakeForward = vexRT[Btn6U];
int intakeBackwards = vexRT[Btn5U];
int deadBand = 10;
//All the floats
float xL = vexRT[Ch4];
float yL = vexRT[Ch3];
float xR = vexRT[Ch1];
float yR = vexRT[Ch2];
