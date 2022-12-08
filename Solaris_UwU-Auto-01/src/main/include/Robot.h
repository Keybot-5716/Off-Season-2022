#pragma once

#include "AHRS.h"
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

  private:

    frc::SendableChooser<std::string> chooserAuto;
    const std::string autoDefault = "Default";
    const std::string autoStraightLine = "Linea recta";
    const std::string autoLineWithRot = "Linea con vuelta";
    const std::string autoLineWithTurn = "Linea con giro";
    const std::string autoComplex = "Secuencia compleja";
    std::string selectedAuto;

    AHRS gyro{SPI::Port::kMXP};

    frc::Timer timerAuto;
  
    bool hasSpin;
    bool firstAdvance;
    bool secondSpin;
    bool secondAdvance;

    frc::Joystick m_stickONE{1};

    WPI_TalonSRX motorFOUR = {1};      //Talon 4 -> ID 01 Talon
    WPI_TalonSRX motorTHREE = {0};       //Talon 3 -> ID 00 Talon
    WPI_VictorSPX motorTWO = {0};      //Talon 2 -> ID 00 Victor
    WPI_VictorSPX motorONE = {1};     //Talon 1 -> ID 01 Victor


    frc::MotorControllerGroup m_leftGroup{motorTHREE, motorFOUR};     //Grupo de motores -> Izquierdo
    frc::MotorControllerGroup m_rightGroup{motorTWO, motorONE};    //Grupo de motores -> Derecho

    frc::DifferentialDrive m_drive{m_leftGroup, m_rightGroup};  //Conduccion de tipo Arcade
};