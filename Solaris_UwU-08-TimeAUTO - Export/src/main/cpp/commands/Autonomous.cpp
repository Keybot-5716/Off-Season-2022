// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Autonomous.h"

#include <frc2/command/ParallelCommandGroup.h>

#include "commands/DriveStraight.h"

Autonomous::Autonomous(Drivetrain& drivetrain,DriveFor& drivefor) {
  SetName("Autonomous");
  AddCommands(
      // clang-format off
      //DriveStraight(100, drivetrain) // Use encoders if ultrasonic is broken
      //SetDistanceToBox(0.10, drivetrain),
      //DriveStraight(-2, drivetrain) // Use encoders if ultrasonic is broken
      );
  // clang-format on
}
