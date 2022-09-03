// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/button/JoystickButton.h>

#include "commands/TankDrive.h"

RobotContainer::RobotContainer()
    : m_autonomousCommand(m_drivetrain) {
  frc::SmartDashboard::PutData(&m_drivetrain);

  m_drivetrain.SetDefaultCommand(TankDrive([this] { return (m_joy.GetLeftX()*-0.8); }, //Rapidez = 1.45 m/s, Distancia = 5 m, Tiempo = 3.45 s (no se toma en cuenta la aceleración)
                                           [this] { return (m_joy.GetRightY()*0.8); },
                                           m_drivetrain));

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  frc2::JoystickButton(&m_joy, 8).WhenPressed(
      Autonomous(m_drivetrain));
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autonomousCommand;
}
