// Code made by UwU 06/29/2022 <
// Timed Based translations - Solaris (Rapid React 2021 - 2022)

#include "Robot.h" //Robot Include
#include "ctre/Phoenix.h" //Falcon Library
#include <frc/motorcontrol/Talon.h> //Talon Library
#include <frc/motorcontrol/MotorControllerGroup.h> //Motor Library
#include <frc/drive/DifferentialDrive.h> // Drive Library
#include <frc/Joystick.h> // Joystick Library
#include <math.h> // Math Library 
#include <string> // String Library
#include "cameraserver/CameraServer.h" //Camera Server Library
#include "networktables/NetworkTable.h" //Network Tables Library
#include "networktables/NetworkTableEntry.h" //Network Tables Entry Library
#include "networktables/NetworkTableInstance.h" //Network Tables Instance Library
#include <frc/Timer.h> //Timer Library
#include <unordered_map> //Dictionaries library

std::unordered_map<auto, auto> RobVALS = {
  {"ValidTARGET", false},{"countACT", 0}
};

using namespace frc;

void Robot::RobotInit() {

  frc::CameraServer::StartAutomaticCapture();
  cs::CvSink cvSink = frc::CameraServer::GetVideo();
  cs::CvSource outputStream = frc::CameraServer::PutVideo("Blur", 640, 480);

  auto inst = nt::NetworkTableInstance::GetDefault();
  auto pc = inst.GetTable("SmartDashboard");
  nt::NetworkTableEntry streamEntry;
  streamEntry = limelight->GetEntry("stream");

  auto limelight = nt::NetworkTableInstance::GetDefault().GetTable("limelight")

  auto timer = frc::Timer();

  m_right1.SetInverted(true);
  m_left1.SetInverted(true);
}

void Robot::RobotPeriodic() {}

//--------------------------------

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

//--------------------------------

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  
  Robot::ReadControllerInput();

  double delta = 10;
  double vi = 50;
  double mod = 50;
  double vf = 70;
  int POW = 0;

  double x = Robot::x_AXIS;
  double y = Robot::y_AXIS;
  bool botonA = Robot::botonA;
  bool botonB = Robot::botonB;
  bool botonY = Robot::botonY;
  bool botonCAM = Robot::botonCAM;
  bool botonCOLGAR = Robot::botonCOLGAR;
  bool botonLB = Robot::botonLB;
  bool botonRB = Robot::botonSPIT;
  double countACT = RobVALS{"countACT"}

  double powerX = x<0.2 && x>-0.2 ? 0 : x;
  double powerY = y<0.2 && y>-0.2 ? 0 : y;

  double tv = limelight->GetNumber("tv",0.0);
  double tx = limelight->GetNumber("tx",0.0);
  double ty = limelight->GetNumber("ty",0.0);
  double ta = limelight->GetNumber("ta",0.0);

	if (botonCAM){
		limelight->PutNumber("stream", 1);
		POW = -1;
  } else{
		POW = 1;
		limelight->PutNumber("stream", 2);
  }

	if (botonINVCOLG == false){int isINV = -1;} else{int isINV = 1;}

	if (botonA){colector.set(-1);}
  else if (botonB){
		o_sucker.Set(1); 
	  if (botonY){falcon500.set(ControlMode::PercentOutput,0.5);}
  }
	else if (botonY){
		//wpilib.SmartDashboard.putNumber("Canon Charge", countACT)
		if (countACT < vi){falcon500.set(ControlMode::PercentOutput,0.5);}
		else if (countACT > vi and countACT < vi+delta){falcon500.set(ControlMode::PercentOutput,0.5);}
		else if (countACT > vi+delta and countACT < vf+delta){falcon500.set(ControlMode::PercentOutput,0.5);}
		else if (countACT > vf+delta*2){servo.SetAngle(-90);}
		state["countACT"] += 1
  }
	else{
  	RobVALS{"countACT"} = 0;
		o_sucker.Set(0);
		falcon500.set(ControlMode::PercentOutput,0);
		servo.SetAngle(90);
  }
	if(botonCOLGAR){
		//wpilib.SmartDashboard.putString("Colgar State:", "Colgandose")
		self.colgarONE.set(-1.0)
		self.colgarTWO.set(1.0)
  }
	else if (self.botonCOLGAR.off){
		if (int isINV == -1){
			//wpilib.SmartDashboard.putString("Colgar State:", "Apagado")
			o_colgarONE.Set(0.0);
			o_colgarTWO.Set(0.0);
    }
    else if (innt isINV == 1){
			//wpilib.SmartDashboard.putString("Colgar State:", "Bajando")
			o_colgarONE.set(0.7);
			o_colgarTWO.set(-0.7);
    }
  }
  
	if (botonRB){
		falcon500.set(ControlMode::PercentOutput,0.3);
		servo.SetAngle(-90);
  }

	if (botonLB){POW	= POW * 0.6}
	else{POW	= POW * 0.9}

  m_robotDrive.ArcadeDrive(powerY * POW, powerX * -POW);

}

//--------------------------------

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

//--------------------------------

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

//--------------------------------

void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

//--------------------------------

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
