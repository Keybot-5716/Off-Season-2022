#pragma once

#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <chrono>
#include <iostream>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Joystick.h> // Joystick Library
#include <frc/motorcontrol/Talon.h> //Talon Library
#include <frc/motorcontrol/MotorControllerGroup.h> //Motor Library
#include <frc/drive/DifferentialDrive.h> // Drive Library
#include <frc/Servo.h>
#include <frc/Compressor.h>
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Timer.h>
#include <frc/Encoder.h>
#include <frc/DriverStation.h>
#include "frc/smartdashboard/Smartdashboard.h"
#include "ctre/Phoenix.h" //Falcon Library
#include "networktables/NetworkTable.h" //Network Tables Library
#include "networktables/NetworkTableEntry.h" //Network Tables Entry Library
#include "networktables/NetworkTableValue.h" //Network Tables Value Library
#include "cameraserver/CameraServer.h" //Camera Server Library
#include "networktables/NetworkTableInstance.h" //Network Tables Instance Library
#include "wpi/span.h"
#include "cscore_oo.h"

using namespace std;
using namespace cv;
using namespace frc;

class Robot : public frc::TimedRobot {
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

    double delta = 10;
    double vi = 30;
    double vf = 70;

    double contAuto = 0;

    void invertMotors(){
      motorTWO.SetInverted(true); 
      motorONE.SetInverted(true); 
    }

  private:
    std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    frc::SendableChooser<std::string> m_chooser;
    
    const std::string kAutoNameDefault = "Default";
    const std::string kAutoNameCustom = "My Auto";
    std::string m_autoSelected;

    frc::Joystick m_stickONE{1};  //Joystick Movimiento
    //frc::Joystick m_stickTWO{2};  //Joystick Botones

    frc::Compressor compressorMAIN{0, frc::PneumaticsModuleType::CTREPCM};
    
    frc::Solenoid solenoidZERO{frc::PneumaticsModuleType::CTREPCM, 0};
    frc::Solenoid solenoidONE{frc::PneumaticsModuleType::CTREPCM, 1};
    frc::Solenoid solenoidTWO{frc::PneumaticsModuleType::CTREPCM, 2};

    WPI_TalonSRX motorFOUR = {1};      //Talon 4 -> ID 01 Talon
    WPI_TalonSRX motorTHREE = {0};       //Talon 3 -> ID 00 Talon
    WPI_VictorSPX motorTWO = {0};      //Talon 2 -> ID 00 Victor
    WPI_VictorSPX motorONE = {1};     //Talon 1 -> ID 01 Victor

    TalonSRX o_sucker = {2};

    TalonSRX falconONE = {4}; //Falcon 2 -> Identificador 1
    TalonSRX falconTWO = {3}; //Falcon 3 -> Identificador 2

    double botonLB = m_stickONE.GetRawButton(5);  //Boton -> Disminuir velocidad
      
    frc::MotorControllerGroup m_leftGroup{motorTHREE, motorFOUR};     //Grupo de motores -> Izquierdo
    frc::MotorControllerGroup m_rightGroup{motorTWO, motorONE};    //Grupo de motores -> Derecho

    frc::DifferentialDrive m_drive{m_leftGroup, m_rightGroup};  //Conduccion de tipo Arcade

    double countsPR = 256;
    double wheelDiam = 2.3;

};
