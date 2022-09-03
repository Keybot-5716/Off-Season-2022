// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Drivetrain.h"

#include <frc/Joystick.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <units/length.h>
#include <wpi/numbers>

Drivetrain::Drivetrain() {
  
  m_left.SetInverted(true);

  SetName("Drivetrain");
  SetSubsystem("DriveTrain");
}

void Drivetrain::Log() {}

void Drivetrain::Drive(double left, double right) {
  m_robotDrive.TankDrive(left, right);
}

void Drivetrain::Reset() {}

void Drivetrain::Periodic() {
  Log();
}
