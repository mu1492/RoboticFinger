///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2004,2026 Mihai Ursu                                            //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
// (at your option) any later version.                                           //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

/*
RoboticFinger.cpp

This file contains the sources for the robotic finger.
*/

#include "RoboticFinger.h"
#include "./ui_RoboticFinger.h"

#include <iomanip>


//!************************************************************************
//! Constructor
//!************************************************************************
RoboticFinger::RoboticFinger
    (
    QWidget*    aParent     //!< parent widget
    )
    : QMainWindow( aParent )
    , mMainUi( new Ui::RoboticFinger )
{
    mMainUi->setupUi( this );

    //****************************************
    // Exit button
    //****************************************
    connect( mMainUi->ExitButton, &QPushButton::clicked, qApp, &QApplication::quit );

    //****************************************
    // motor
    //****************************************
    mMainUi->MotorResistanceSpinBox->setMinimum( Model::MOTOR_RESISTANCE.min );
    mMainUi->MotorResistanceSpinBox->setMaximum( Model::MOTOR_RESISTANCE.max );
    mMainUi->MotorResistanceSpinBox->setValue( mCtrlSys.getModel().getMotor().resistance );
    connect( mMainUi->MotorResistanceSpinBox, &QDoubleSpinBox::valueChanged, this, &RoboticFinger::handleMotorResistanceChanged );

    mMainUi->MotorTorqueConstantSpinBox->setMinimum( Model::MOTOR_TORQUE_CST.min );
    mMainUi->MotorTorqueConstantSpinBox->setMaximum( Model::MOTOR_TORQUE_CST.max );
    mMainUi->MotorTorqueConstantSpinBox->setValue( mCtrlSys.getModel().getMotor().torqueConstant );
    connect( mMainUi->MotorTorqueConstantSpinBox, &QDoubleSpinBox::valueChanged, this, &RoboticFinger::handleMotorTorqueConstantChanged );

    //****************************************
    // gearbox
    //****************************************
    mMainUi->GearboxRatioSpinBox->setMinimum( Model::GEARBOX_RATIO.min );
    mMainUi->GearboxRatioSpinBox->setMaximum( Model::GEARBOX_RATIO.max );
    mMainUi->GearboxRatioSpinBox->setValue( mCtrlSys.getModel().getGearbox().ratio );
    connect( mMainUi->GearboxRatioSpinBox, &QDoubleSpinBox::valueChanged, this, &RoboticFinger::handleGearboxRatioChanged );

    //****************************************
    // mechanical load
    //****************************************
    mMainUi->MechanicalLoadInertiaSpinBox->setMinimum( Model::MECH_LOAD_INERTIA.min );
    mMainUi->MechanicalLoadInertiaSpinBox->setMaximum( Model::MECH_LOAD_INERTIA.max );
    mMainUi->MechanicalLoadInertiaSpinBox->setValue( mCtrlSys.getModel().getMechanicalLoad().inertia );
    connect( mMainUi->MechanicalLoadInertiaSpinBox, &QDoubleSpinBox::valueChanged, this, &RoboticFinger::handleMechanicalLoadInertiaChanged );

    mMainUi->MechanicalLoadDampingSpinBox->setMinimum( Model::MECH_LOAD_DAMPING.min );
    mMainUi->MechanicalLoadDampingSpinBox->setMaximum( Model::MECH_LOAD_DAMPING.max );
    mMainUi->MechanicalLoadDampingSpinBox->setValue( mCtrlSys.getModel().getMechanicalLoad().damping );
    connect( mMainUi->MechanicalLoadDampingSpinBox, &QDoubleSpinBox::valueChanged, this, &RoboticFinger::handleMechanicalLoadDampingChanged );

    //****************************************
    // control parameters
    //****************************************
    mMainUi->ControlParametersPositionSensorGainSpinBox->setMinimum( Model::CTRL_PARAM_POS_SENSOR_GAIN.min );
    mMainUi->ControlParametersPositionSensorGainSpinBox->setMaximum( Model::CTRL_PARAM_POS_SENSOR_GAIN.max );
    mMainUi->ControlParametersPositionSensorGainSpinBox->setValue( mCtrlSys.getModel().getControlParameters().positionSensorGain );
    connect( mMainUi->ControlParametersPositionSensorGainSpinBox, &QDoubleSpinBox::valueChanged, this, &RoboticFinger::handleControlParametersPositionSensorGainChanged );

    mMainUi->ControlParametersSettlingFactorSpinBox->setMinimum( Model::CTRL_PARAM_SETTLING_FACTOR.min );
    mMainUi->ControlParametersSettlingFactorSpinBox->setMaximum( Model::CTRL_PARAM_SETTLING_FACTOR.max );
    mMainUi->ControlParametersSettlingFactorSpinBox->setValue( mCtrlSys.getModel().getControlParameters().settlingFactor );
    connect( mMainUi->ControlParametersSettlingFactorSpinBox, &QDoubleSpinBox::valueChanged, this, &RoboticFinger::handleControlParametersSettlingFactorChanged );

    mMainUi->ControlParametersDampingRatioSpinBox->setMinimum( Model::CTRL_PARAM_DAMPING_RATIO.min );
    mMainUi->ControlParametersDampingRatioSpinBox->setMaximum( Model::CTRL_PARAM_DAMPING_RATIO.max );
    mMainUi->ControlParametersDampingRatioSpinBox->setValue( mCtrlSys.getModel().getControlParameters().dampingRatio );
    connect( mMainUi->ControlParametersDampingRatioSpinBox, &QDoubleSpinBox::valueChanged, this, &RoboticFinger::handleControlParametersDampingRatioChanged );

    mMainUi->ControlParametersTimeConstantSpinBox->setMinimum( Model::CTRL_PARAM_TIME_CST.min );
    mMainUi->ControlParametersTimeConstantSpinBox->setMaximum( Model::CTRL_PARAM_TIME_CST.max );
    mMainUi->ControlParametersTimeConstantSpinBox->setValue( mCtrlSys.getModel().getControlParameters().timeConstant );
    connect( mMainUi->ControlParametersTimeConstantSpinBox, &QDoubleSpinBox::valueChanged, this, &RoboticFinger::handleControlParametersTimeConstantChanged );

    //****************************************
    // plots
    //****************************************
    mMainUi->Fig6->setPlotType( PlotCanvas::PLOT_TYPE_FIG6 );

    mMainUi->Fig7->setPlotType( PlotCanvas::PLOT_TYPE_FIG7 );

    mMainUi->Fig8Mod->setPlotType( PlotCanvas::PLOT_TYPE_FIG8_MODULUS );
    mMainUi->Fig8Phase->setPlotType( PlotCanvas::PLOT_TYPE_FIG8_PHASE );

    mMainUi->Fig9Thetao->setPlotType( PlotCanvas::PLOT_TYPE_FIG9_ANGLE );
    mMainUi->Fig9KaKb->setPlotType( PlotCanvas::PLOT_TYPE_FIG9_GAINS );

    //****************************************
    // copyright
    //****************************************
    mMainUi->statusbar->showMessage( "\t(c) 2004,2026 Mihai Ursu" );
}


//!************************************************************************
//! Destructor
//!************************************************************************
RoboticFinger::~RoboticFinger()
{
    delete mMainUi;
}


//!************************************************************************
//! Handle for changing the damping ratio control parameter
//!
//! @returns nothing
//!************************************************************************
/* slot */ void RoboticFinger::handleControlParametersDampingRatioChanged
    (
    double aValue       //!< value
    )
{
    mCtrlSys.getModel().getControlParameters().dampingRatio = aValue;
    updateFigures();
}


//!************************************************************************
//! Handle for changing the position sesnor gain control parameter
//!
//! @returns nothing
//!************************************************************************
/* slot */ void RoboticFinger::handleControlParametersPositionSensorGainChanged
    (
    double aValue       //!< value
    )
{
    mCtrlSys.getModel().getControlParameters().positionSensorGain = aValue;
    updateFigures();
}


//!************************************************************************
//! Handle for changing the settling factor control parameter
//!
//! @returns nothing
//!************************************************************************
/* slot */ void RoboticFinger::handleControlParametersSettlingFactorChanged
    (
    double aValue       //!< value
    )
{
    mCtrlSys.getModel().getControlParameters().settlingFactor = aValue;
    updateFigures();
}


//!************************************************************************
//! Handle for changing the system time constant control parameter
//!
//! @returns nothing
//!************************************************************************
/* slot */ void RoboticFinger::handleControlParametersTimeConstantChanged
    (
    double aValue       //!< value
    )
{
    mCtrlSys.getModel().getControlParameters().timeConstant = aValue;
    updateFigures();
}


//!************************************************************************
//! Handle for changing the gearbox ratio
//!
//! @returns nothing
//!************************************************************************
/* slot */ void RoboticFinger::handleGearboxRatioChanged
    (
    double aValue       //!< value
    )
{
    mCtrlSys.getModel().getGearbox().ratio = aValue;
    updateFigures();
}


//!************************************************************************
//! Handle for changing the mechanical load damping
//!
//! @returns nothing
//!************************************************************************
/* slot */ void RoboticFinger::handleMechanicalLoadDampingChanged
    (
    double aValue       //!< value
    )
{
    mCtrlSys.getModel().getMechanicalLoad().damping = aValue;
    updateFigures();
}


//!************************************************************************
//! Handle for changing the mechanical load inertia
//!
//! @returns nothing
//!************************************************************************
/* slot */ void RoboticFinger::handleMechanicalLoadInertiaChanged
    (
    double aValue       //!< value
    )
{
    mCtrlSys.getModel().getMechanicalLoad().inertia = aValue;
    updateFigures();
}


//!************************************************************************
//! Handle for changing the motor resistance
//!
//! @returns nothing
//!************************************************************************
/* slot */ void RoboticFinger::handleMotorResistanceChanged
    (
    double aValue       //!< value
    )
{
    mCtrlSys.getModel().getMotor().resistance = aValue;
    updateFigures();
}


//!************************************************************************
//! Handle for changing the motor torque constant
//!
//! @returns nothing
//!************************************************************************
/* slot */ void RoboticFinger::handleMotorTorqueConstantChanged
    (
    double aValue       //!< value
    )
{
    mCtrlSys.getModel().getMotor().torqueConstant = aValue;
    updateFigures();
}


//!************************************************************************
//! Update the figures
//!
//! @returns nothing
//!************************************************************************
void RoboticFinger::updateFigures()
{
    mMainUi->Fig6->updatePlots( mCtrlSys );

    mMainUi->Fig7->updatePlots( mCtrlSys );

    mMainUi->Fig8Mod->updatePlots( mCtrlSys );
    mMainUi->Fig8Phase->updatePlots( mCtrlSys );

    mMainUi->Fig9Thetao->updatePlots( mCtrlSys );
    mMainUi->Fig9KaKb->updatePlots( mCtrlSys );
}
