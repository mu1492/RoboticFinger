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
ControlSystem.h

This file contains the definitions for the control system.
*/

#ifndef ControlSystem_h
#define ControlSystem_h

#include "Model.h"

#include <utility>


//************************************************************************
// Class for handling the control system of the robotic finger
//************************************************************************
class ControlSystem
{
    //************************************************************************
    // functions
    //************************************************************************
    public:
        ControlSystem();

        double getDampingRatio
            (
            const double aTs    //!< system time constant [s]
            );

        double getForceGainFromStiffness
            (
            const double aTs,   //!< system time constant [s]
            const double aS     //!< stiffness [Nm/rad]
            );

        std::pair<double, double> getFrequencyResponse
            (
            const double aTs,   //!< system time constant [s]
            const double aW     //!< frequency [rad/s]
            );

        Model& getModel();

        double getNaturalFrequency
            (
            const double aTs    //!< system time constant [s]
            );

        double getPositionGain
            (
            const double aTs    //!< system time constant [s]
            );

        double getStepResponse
            (
            const double aTs,   //!< system time constant [s]
            const double aTime  //!< time [s]
            );

        double getStiffnessFromForceGain
            (
            const double aTs,   //!< system time constant [s]
            const double aE     //!< strain gauge gain [V/Nm]
            );

        double getTorqueStepAngle
            (
            const double aTs,   //!< system time constant [s]
            const double aTauD, //!< torque [Nm]
            const double aE     //!< strain gauge gain [V/Nm]
            );

        double getVelocityGain
            (
            const double aTs    //!< system time constant [s]
            );


    //************************************************************************
    // variables
    //************************************************************************
    private:
        Model   mModel;     //!< model for the robotic finger
};

#endif // ControlSystem_h
