#include "Robot.h"

void Robot::RobotInit() {
  chooserAuto.SetDefaultOption(autoDefault, autoDefault);
  chooserAuto.AddOption(autoStraightLine, autoStraightLine);
  chooserAuto.AddOption(autoLineWithRot, autoLineWithRot);
  chooserAuto.AddOption(autoLineWithTurn, autoLineWithTurn);
  chooserAuto.AddOption(autoComplex, autoComplex);
  frc::SmartDashboard::PutData("Auto Modes", &chooserAuto);
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  timerAuto.Reset();
  timerAuto.Start();
  gyro.Reset();
  
  hasSpin = false;
  secondSpin = false;
  thirdSpin = false;
  firstAdvance = false;
  secondAdvance = false;
  thirdAdvance = false;
  
}

void Robot::AutonomousPeriodic() {

  selectedAuto = chooserAuto.GetSelected();
  SmartDashboard::PutString("Auto: ", selectedAuto);

  if (selectedAuto == autoStraightLine){
    
    //-----------------------------------------------------------------------
    
    moveFor(3_s,firstAdvance);
    
    //-----------------------------------------------------------------------

  } else if (selectedAuto == autoLineWithRot){
    
    //-----------------------------------------------------------------------
    
    SmartDashboard::PutNumber("Angles: ", gyro.GetAngle());

    moveFor(2.5_s,firstAdvance);
    if (firstAdvance){
      rotateFor(360,hasSpin);
      if (hasSpin){
        moveFor(2.5_s,secondAdvance);
      }
    }

    //-----------------------------------------------------------------------
    
  } else if (selectedAuto == autoLineWithTurn){
    
    //-----------------------------------------------------------------------

    SmartDashboard::PutNumber("Angles: ", gyro.GetAngle());

    moveFor(4_s,firstAdvance);
    if (firstAdvance){
      rotateFor(120,hasSpin);
      if (hasSpin){
        moveFor(1.5_s,secondAdvance);
        if (secondAdvance){
          microRotate(1_s,secondSpin);
          if (secondSpin){
            moveFor(3_s,thirdAdvance);
          }
        }
      }
    }

    //-----------------------------------------------------------------------

  } else if (selectedAuto == autoComplex){
    // Custom Auto goes here
  } else{
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {

  double x_AXIS = m_stickONE.GetRawAxis(5);
  double y_AXIS = m_stickONE.GetRawAxis(1);
  
  double x = x_AXIS;
  double y = y_AXIS;

  double powerX = x<0.2 && x>-0.2 ? 0 : x;
  double powerY = y<0.2 && y>-0.2 ? 0 : y;

  m_drive.TankDrive(y,x*-1);

}
void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}
void Robot::TestInit() {}
void Robot::TestPeriodic() {}
void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif