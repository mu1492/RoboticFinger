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
RoboticFinger.h

This file contains the definitions for the robotic finger.
*/

#ifndef RoboticFinger_h
#define RoboticFinger_h

#include "ControlSystem.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
    namespace Ui
    {
        class RoboticFinger;
    }
QT_END_NAMESPACE


//************************************************************************
// Class for handling the robotic finger
//************************************************************************
class RoboticFinger : public QMainWindow
{
    Q_OBJECT

    //************************************************************************
    // functions
    //************************************************************************
    public:
        explicit RoboticFinger
            (
            QWidget*    aParent = nullptr   //!< parent widget
            );

        ~RoboticFinger() override;

    private:
        void updateFigures();

    private slots:
        void handleControlParametersDampingRatioChanged
            (
            double aValue       //!< value
            );

        void handleControlParametersPositionSensorGainChanged
            (
            double aValue       //!< value
            );

        void handleControlParametersSettlingFactorChanged
            (
            double aValue       //!< value
            );

        void handleControlParametersTimeConstantChanged
            (
            double aValue       //!< value
            );

        void handleGearboxRatioChanged
            (
            double aValue       //!< value
            );

        void handleMechanicalLoadDampingChanged
            (
            double aValue       //!< value
            );

        void handleMechanicalLoadInertiaChanged
            (
            double aValue       //!< value
            );

        void handleMotorResistanceChanged
            (
            double aValue       //!< value
            );

        void handleMotorTorqueConstantChanged
            (
            double aValue       //!< value
            );


    //************************************************************************
    // variables
    //************************************************************************
    private:
        Ui::RoboticFinger*  mMainUi;        //!< main UI

        ControlSystem       mCtrlSys;       //!< control system
};

#endif // RoboticFinger_h
