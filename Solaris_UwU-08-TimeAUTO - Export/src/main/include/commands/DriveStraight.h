// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/PIDCommand.h>

#include "subsystems/Drivetrain.h"

class DriveStraight : public frc2::CommandHelper<frc2::PIDCommand, DriveStraight> {
 public:
  explicit DriveStraight(double distance, Drivetrain& drivetrain);
  void Initialize() override;
  bool IsFinished() override;

 private:
  Drivetrain* m_drivetrain;
};
