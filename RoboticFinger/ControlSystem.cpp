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
ControlSystem.cpp

This file contains the sources for the control system.
*/

#include "ControlSystem.h"

#include <cmath>


//!************************************************************************
//! Constructor
//!************************************************************************
ControlSystem::ControlSystem()
{
}


//!************************************************************************
//! Calculate the damping ratio, zeta [-], based on relation (10)
//!
//! The returned value can be assigned to
//!     mModel.getControlParameters().dampingRatio
//! by the caller function.
//!
//! @returns the damping ratio
//!************************************************************************
double ControlSystem::getDampingRatio
    (
    const double aTs    //!< system time constant [s]
    )
{
    double zeta = 0;
    double wn = getNaturalFrequency( aTs );

    if( wn > 0 )
    {
        double kb = getVelocityGain( aTs );
        zeta = 0.5 * ( mModel.getMechanicalLoad().damping * mModel.getMotor().resistance + mModel.getMotor().torqueConstant * kb ) /
                ( mModel.getMotor().resistance * mModel.getMechanicalLoad().inertia * wn );
    }

    return zeta;
}


//!************************************************************************
//! Calculate the strain gauge gain, E(S) [V/Nm], based on relation (20)
//!
//! @returns the strain gauge gain [V/Nm]
//!************************************************************************
double ControlSystem::getForceGainFromStiffness
    (
    const double aTs,   //!< system time constant [s]
    const double aS     //!< stiffness [Nm/rad]
    )
{
    double e = 0;
    double g = mModel.getGearbox().ratio * getPositionGain( aTs ) * mModel.getMotor().torqueConstant * mModel.getControlParameters().positionSensorGain;

    if( aS > 0 && g > 0 )
    {
        e = 1.0 / aS - 1.0 / g;
    }

    return e;
}


//!************************************************************************
//! Calculate the frequency response, based on relations (23) and (24)
//!
//! @returns a pair with the modulus and phase [rad] of the response
//!************************************************************************
std::pair<double, double> ControlSystem::getFrequencyResponse
    (
    const double aTs,   //!< system time constant [s]
    const double aW     //!< frequency [rad/s]
    )
{
    double magnitude = 0;
    double phase = 0;

    double ka = getPositionGain( aTs );
    double kb = getVelocityGain( aTs );

    double km = mModel.getMotor().torqueConstant;
    double r = mModel.getMotor().resistance;
    double n = mModel.getGearbox().ratio;
    double j = mModel.getMechanicalLoad().inertia;
    double c = mModel.getMechanicalLoad().damping;
    double kp = mModel.getControlParameters().positionSensorGain;

    if( ka > 0 && kb > 0
     && aW >= 0
     && n > 0 && r > 0 && j > 0 )
    {
        double t1 = kp * ka * km;
        double t2 = aW * aW * n * r * j;
        double t3 = aW * n * ( c * r + km * kb );
        magnitude = t1 / sqrt( pow( t1 - t2, 2.0 ) + pow( t3, 2.0 ) );
        phase = atan2( -t3, t1 - t2 );
    }

    return { magnitude, phase };
}


//!************************************************************************
//! Get the model object
//!
//! @returns the model object
//!************************************************************************
Model& ControlSystem::getModel()
{
    return mModel;
}


//!************************************************************************
//! Calculate the natural frequency, wn [rad/s], based on relation (11)
//!
//! @returns the natural frequency [rad/s]
//!************************************************************************
double ControlSystem::getNaturalFrequency
    (
    const double aTs    //!< system time constant [s]
    )
{
    double wn = 0;

    if( aTs > 0 )
    {
        wn = mModel.getControlParameters().settlingFactor / ( aTs * mModel.getControlParameters().dampingRatio );
    }

    return wn;
}


//!************************************************************************
//! Calculate the position gain, Ka [-], based on relation (9)
//!
//! @returns the position gain [-]
//!************************************************************************
double ControlSystem::getPositionGain
    (
    const double aTs    //!< system time constant [s]
    )
{
    double ka = 0;
    double wn = getNaturalFrequency( aTs );

    if( wn > 0 )
    {
        ka = wn * wn * mModel.getGearbox().ratio * mModel.getMotor().resistance * mModel.getMechanicalLoad().inertia /
            ( mModel.getMotor().torqueConstant * mModel.getControlParameters().positionSensorGain );
    }

    return ka;
}


//!************************************************************************
//! Calculate the step response, h(t), based on relation (22)
//!
//! @returns the step response
//!************************************************************************
double ControlSystem::getStepResponse
    (
    const double aTs,   //!< system time constant [s]
    const double aTime  //!< time [s]
    )
{
    double h = 0;
    double wn = getNaturalFrequency( aTs );

    if( wn > 0 && aTime >= 0 )
    {
        h = 1.0 - ( 1.0 + wn * aTime ) * std::exp( -wn * aTime );
    }

    return h;
}


//!************************************************************************
//! Calculate the stiffness, S [Nm/rad], based on relation (20)
//!
//! @returns the stiffness [Nm/rad]
//!************************************************************************
double ControlSystem::getStiffnessFromForceGain
    (
    const double aTs,   //!< system time constant [s]
    const double aE     //!< strain gauge gain [V/Nm]
    )
{
    double s = 0;
    double g = mModel.getGearbox().ratio * getPositionGain( aTs ) * mModel.getMotor().torqueConstant * mModel.getControlParameters().positionSensorGain;

    if( g > 0 )
    {
        s = 1.0 / ( aE + 1.0 / g );
    }

    return s;
}


//!************************************************************************
//! Calculate the angle for unit-step torque, tho [rad], based on (19)
//!
//! The inner plot from Fig. 9 in the paper is using TauD=1 [rad/s] and
//! E=0 [V/Nm].
//! In practice, calls to this function should use a strain gauge gain E
//! calculated by getForceGainFromStiffness() with a measured stiffness S.
//!
//! @returns the angle [rad]
//!************************************************************************
double ControlSystem::getTorqueStepAngle
    (
    const double aTs,   //!< system time constant [s]
    const double aTauD, //!< torque [Nm]
    const double aE     //!< strain gauge gain [V/Nm]
    )
{
    double tho = 0;
    double g = mModel.getGearbox().ratio * getPositionGain( aTs ) * mModel.getMotor().torqueConstant * mModel.getControlParameters().positionSensorGain;

    if( g > 0 && aTauD >= 0 && aE >= 0 )
    {
        tho = aTauD * ( aE + 1.0 / g );
    }

    return tho;
}


//!************************************************************************
//! Calculate the velocity gain, Kb [-], based on relation (13)
//!
//! @returns the velocity gain
//!************************************************************************
double ControlSystem::getVelocityGain
    (
    const double aTs    //!< system time constant [s]
    )
{
    double kb = 0;
    double wn = getNaturalFrequency( aTs );

    if( wn > 0 )
    {
        kb = ( 2.0 * mModel.getMechanicalLoad().inertia * mModel.getControlParameters().dampingRatio * wn - mModel.getMechanicalLoad().damping ) *
                mModel.getMotor().resistance / mModel.getMotor().torqueConstant;
    }

    return kb;
}
