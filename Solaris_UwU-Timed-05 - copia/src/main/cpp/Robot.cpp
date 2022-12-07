#include "Robot.h"

int contVar = 0;
auto ValidTARGET = false; int countACT = 0; int powerONE = 0.67; int powerTWO = -0.7;
auto inst = nt::NetworkTableInstance::GetDefault(); auto pc = inst.GetTable("SmartDashboard");
std::shared_ptr<nt::NetworkTable> limelight = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

Encoder encoderOne{0, 1, false, Encoder::EncodingType::k2X};
Encoder encoderTwo{2, 3, false, Encoder::EncodingType::k2X};

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  SmartDashboard::PutData("Auto Modes", &m_chooser);

  CameraServer::StartAutomaticCapture();
  cs::CvSink cvSink = CameraServer::GetVideo();
  cs::CvSource outputStream = CameraServer::PutVideo("Blur", 640, 480);
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  fmt::print("Auto selected: {}\n", m_autoSelected);

  if (m_autoSelected == kAutoNameCustom) {/*Custom Auto*/} else {
    //Code goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {/*Custom Auto*/} else {
    //Code goes here
  }
}

void Robot::TeleopInit() {
  encoderOne.SetDistancePerPulse(3.1416*wheelDiam/countsPR);
  encoderTwo.SetDistancePerPulse(3.1416*wheelDiam/countsPR);
    
  encoderOne.Reset();
  encoderTwo.Reset();

  encoderOne.SetReverseDirection(true);
}

void Robot::TeleopPeriodic() {

  double tx = table->GetNumber("tx",0.0);                         //targetOffsetAngle_Horizontal
  double ty = table->GetNumber("ty",0.0);                         //targetOffsetAngle_Vertical
  double ta = table->GetNumber("ta",0.0);                         //targetArea
  double ts = table->GetNumber("ts",0.0);                         //targetSkew
  double tv = table->GetNumber("tv",0.0);                         //getIfValidTargets

  int switchCamCom = false;
  float POW = 0.0;

  Robot::invertMotors();

  int povANGLE = DriverStation::GetStickPOV(1,0);

  SmartDashboard::PutNumber("GetStickPOV", povANGLE);

  double x_AXIS = m_stickONE.GetRawAxis(4);
  double y_AXIS = m_stickONE.GetRawAxis(1);

  bool leftTrigger =  m_stickONE.GetRawAxis(2);   //Trigger -> Disparo Upper-Hub
  bool rightTrigger = m_stickONE.GetRawAxis(3);   //Trigger -> Disparo Lower-Hub

  double botonA = m_stickONE.GetRawButton(1);     //Boton -> Escupir pelota
  double botonB = m_stickONE.GetRawButton(2);     //Boton -> Tragar pelota
  double botonY = m_stickONE.GetRawButton(4);     //Boton -> Compresor

  double x = x_AXIS;
  double y = y_AXIS;

  double powerX = x<0.2 && x>-0.2 ? 0 : x;
  double powerY = y<0.2 && y>-0.2 ? 0 : y;
  
  if (rightTrigger){
    SmartDashboard::PutString("Shooting", "Shooter: ON");
		falconONE.Set(ControlMode::PercentOutput,0.55);//0.47);//0.77);
		falconTWO.Set(ControlMode::PercentOutput,-0.55);//-0.5);//-0.8);
  } else if (leftTrigger){
    SmartDashboard::PutString("Shooting", "Shooter: ON");
		falconONE.Set(ControlMode::PercentOutput,0.85);//0.47);//0.77);
		falconTWO.Set(ControlMode::PercentOutput,-0.85);//-0.5);//-0.8);
  } else{
    SmartDashboard::PutString("Shooting", "Shooter: OFF");
		falconONE.Set(ControlMode::PercentOutput,0);
		falconTWO.Set(ControlMode::PercentOutput,0);
  }

  if (botonB){
    SmartDashboard::PutNumber("Sucking", 1);
    o_sucker.Set(ControlMode::PercentOutput,1);
  }else if (botonA){
    SmartDashboard::PutNumber("Sucking", -1);
    o_sucker.Set(ControlMode::PercentOutput,-1);
  } else{
    SmartDashboard::PutNumber("Sucking", 0);
    o_sucker.Set(ControlMode::PercentOutput,0);
  }
  
  if (switchCamCom){
    /*if (botonY){
      compressorMAIN.Start();
    }else{
      compressorMAIN.Stop();
    }*/
  } else{
    if (tv == 0){
      SmartDashboard::PutBoolean("Limelight has target: ", false);
    } else{
      SmartDashboard::PutBoolean("Limelight has target: ", true);
      if (botonY){powerX = tx * 0.05;}
    }
  }
  /*
  if (povANGLE == 0){
    solenoidZERO.Set(false);
    solenoidTWO.Set(false);
    solenoidONE.Set(true);
  }else if(povANGLE == 90){
    solenoidZERO.Set(true);
    solenoidTWO.Set(false);
    solenoidONE.Set(false);
  }else{
    solenoidTWO.Set(true);
    solenoidONE.Set(false);
    solenoidZERO.Set(false);
  }*/

  if (botonLB){POW	= -0.6;}
	else{POW = -0.9;}

  double distOne = encoderOne.GetDistance();
  double distTwo = encoderTwo.GetDistance();

  SmartDashboard::PutNumber("distOne", distOne);
  SmartDashboard::PutNumber("distTwo", distTwo);

  SmartDashboard::PutNumber("Power Y", powerX*POW);

  if (powerY < 0){
    m_drive.ArcadeDrive(powerY*-POW,(powerX*-POW)-0.3);
  }else if (powerY > 0){
    m_drive.ArcadeDrive(powerY*-POW,(powerX*-POW)+0.3);
  } else{
    m_drive.ArcadeDrive(powerY*-POW,powerX*-POW);
  }
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return StartRobot<Robot>();
}
#endif
