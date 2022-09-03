// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/DriveStraight.h"

#include <frc/controller/PIDController.h>

#include "Robot.h"

DriveStraight::DriveStraight(double distance, Drivetrain& drivetrain) :
    frc2::CommandHelper<frc2::PIDCommand, DriveStraight>{
        frc2::PIDController{0, 0, 0},
        [&drivetrain] { return 1; },
        distance,
        [&drivetrain](double distance) { drivetrain.Drive(0,-0.8); },
        {&drivetrain}},
    m_drivetrain{&drivetrain} { m_controller.SetTolerance(0.01); }

// Called just before this Command runs the first time
void DriveStraight::Initialize() {
  m_drivetrain->Reset();
}

bool DriveStraight::IsFinished() {
  return m_controller.AtSetpoint();
}