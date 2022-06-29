// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>

class Robot : public frc::TimedRobot {
//--------------------------------
 public:
  void RobotInit() override;
  void RobotPeriodic() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void DisabledInit() override;
  void DisabledPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;

  void SimulationInit() override;
  void SimulationPeriodic() override;

  void ReadControllerInput(){
    double x_AXIS = m_stickONE.GetRawAxis(1);
    double y_AXIS = m_stickONE.GetRawAxis(4);

    double botonA = m_stickONE.GetRawButton(1);
    double botonB = m_stickONE.GetRawButton(2);
    double botonX = m_stickONE.GetRawButton(3);
    double botonY = m_stickONE.GetRawButton(4);

    double botonLB = m_stickONE.GetRawButton(5);
    double botonCAM = m_stickONE.GetRawButton(7);
    
    double botonRIGHTPUSH  = m_stickTWO.GetRawButton(3);
    double botonCOLGAR = m_stickTWO.GetRawButton(5);
    double botonSPIT = m_stickTWO.GetRawButton(6);
    double botonSHOOTER = m_stickTWO.GetRawButton(7);
    double botonINVHANG = m_stickTWO.GetRawButton(8);
    double botonGETDIS  = m_stickTWO.GetRawButton(9);
  };
//--------------------------------
 private:

    // CONFIGURACION CHASIS DE PRUEBA (SOPHRINE) -- r1(1,inv), r2(2,norm), l1(3,norm), l2(4,norm)
		// CONFIGURACION CHASIS DE COMPETENCIA (SOLARIS)
    frc::Joystick m_stickONE{1};
    frc::Joystick m_stickTWO{2};

    frc::Servo servo{9};
    
    frc::Talon m_right1{1};
    frc::Talon m_right2{2};
    frc::Talon m_left1{3};
    frc::Talon m_left2{4};

    frc::Talon o_sucker{5};
    frc::Talon o_colgarONE{7};
    frc::Talon o_colgarTWO{8};

    TalonSRX falcon500 = {5};

    frc::MotorControllerGroup m_leftGroup{m_left1, m_left2};
    frc::MotorControllerGroup m_rightGroup{m_right1, m_right2};

    frc::DifferentialDrive m_drive{m_leftGroup, m_rightGroup};

    double x_AXIS = m_stickONE.GetRawAxis(1);
    double y_AXIS = m_stickONE.GetRawAxis(4);

    double botonA = m_stickONE.GetRawButton(1);
    double botonB = m_stickONE.GetRawButton(2);
    double botonX = m_stickONE.GetRawButton(3);
    double botonY = m_stickONE.GetRawButton(4);

    double botonLB = m_stickONE.GetRawButton(5);
    double botonCAM = m_stickONE.GetRawButton(7);
    
    double botonRIGHTPUSH  = m_stickTWO.GetRawButton(3);
    double botonCOLGAR = m_stickTWO.GetRawButton(5);
    double botonSPIT = m_stickTWO.GetRawButton(6);
    double botonSHOOTER = m_stickTWO.GetRawButton(7);
    double botonINVHANG = m_stickTWO.GetRawButton(8);
    double botonGETDIS  = m_stickTWO.GetRawButton(9);
//--------------------------------
};
