void
FwMotorSet( int value )
{
	motor[shooterL] = value;
	motor[shooterLB] = value;
	motor[shooterR] = value;
	motor[shooterRB] = value;
}

/*-----------------------------------------------------------------------------*/
/** @brief      Get the flywheen motor encoder count                           */
/*-----------------------------------------------------------------------------*/
long
FwMotorEncoderGet()
{
	return(nMotorEncoder[shooterL]);
	return(nMotorEncoder[shooterR]);
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

	// We are using Torque geared motors
	// Set the encoder ticks per revolution
	ticks_per_rev = MOTOR_TPR_393R;

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
