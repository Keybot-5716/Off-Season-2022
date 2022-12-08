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
  secondAdvance = false;
  secondSpin = false;
  firstAdvance = false;
}

void Robot::AutonomousPeriodic() {

  selectedAuto = chooserAuto.GetSelected();
  SmartDashboard::PutString("Auto: ", selectedAuto);

  if (selectedAuto == autoStraightLine){
    //-

    m_drive.TankDrive(-0.3,0.3,false);
    if (timerAuto.Get() >=  5_s) {
      m_drive.TankDrive(0.0, 0.0);
    }

    //-
  } else if (selectedAuto == autoLineWithRot){
    //-
    int numSpin= 1; 
    SmartDashboard::PutNumber("Angles: ", gyro.GetAngle());

    if (timerAuto.Get() < 2.5_s) {
      m_drive.ArcadeDrive(0.0, 0.3, false);
      }
    
    if (gyro.GetAngle() < 360*numSpin && timerAuto.Get() >= 2.5_s){
      m_drive.ArcadeDrive(-0.5, 0.0, false);
    }else if (gyro.GetAngle() >= 360*numSpin && timerAuto.Get() >= 2.5_s){
        hasSpin = true;
        timerAuto.Reset();
      }

    if (hasSpin && timerAuto.Get() < 2.5_s) {
      m_drive.ArcadeDrive(0.0, 0.3, false);
      } else if (hasSpin && timerAuto.Get() >= 5_s) {
      m_drive.ArcadeDrive(0.0, 0.0,false);
    }
    //-
  } else if (selectedAuto == autoLineWithTurn){
    //-
    SmartDashboard::PutNumber("Angles: ", gyro.GetAngle());

    //Avanza recto 4s
    if (timerAuto.Get() < 4_s && hasSpin == false && firstAdvance == false && secondSpin == false && secondAdvance == false) {
      
      m_drive.ArcadeDrive(0.0, 0.3, false);
    
    } else if (timerAuto.Get() >= 4_s && hasSpin == false && firstAdvance == false && secondSpin == false && secondAdvance == false){
      
      firstAdvance = true;
      gyro.Reset();

    } else if (timerAuto.Get() >= 4_s && hasSpin == false && firstAdvance == true && secondSpin == false && secondAdvance == false){
    
      if (gyro.GetAngle() < 95){m_drive.ArcadeDrive(0.3, 0.0,false);}
      else if (gyro.GetAngle() >= 95){
          hasSpin = true;
          //timerAuto.Reset();
      }

    }

    //-
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