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
Model.h

This file contains the definitions for the model parameters.
*/

#ifndef Model_h
#define Model_h


//************************************************************************
// Class for handling the model parameters of the robotic finger
//************************************************************************
class Model
{
    //************************************************************************
    // constants and types
    //************************************************************************
    public:
        typedef struct
        {
            double resistance;          //!< [Ohm]
            double torqueConstant;      //!< [Nm/V]
        }Motor;

        typedef struct
        {
            double ratio;               //!< [-]
        }Gearbox;

        typedef struct
        {
            double inertia;             //!< [Nms2/rad]
            double damping;             //!< [Nms/rad]
        }MechanicalLoad;

        typedef struct
        {
            double positionSensorGain;  //!< [V/rad]
            double settlingFactor;      //!< [-]
            double dampingRatio;        //!< [-]
            double timeConstant;        //!< [s]
        }ControlParameters;

        typedef struct
        {
            double min;
            double max;
        }MinMax;

        static constexpr MinMax MOTOR_RESISTANCE = { 0.5, 20.0 };           //!< R [Ohm]
        static constexpr MinMax MOTOR_TORQUE_CST = { 0.005, 0.25 };         //!< Km [Nm/V]

        static constexpr MinMax GEARBOX_RATIO = { 10, 1500 };               //!< N [-]

        static constexpr MinMax MECH_LOAD_INERTIA = { 1.e-6, 5.e-4 };       //!< J [Nms2/rad]
        static constexpr MinMax MECH_LOAD_DAMPING = { 1.e-6, 1.e-3 };       //!< c [Nms/rad]

        static constexpr MinMax CTRL_PARAM_POS_SENSOR_GAIN = { 0.1, 10 };   //!< Kp [V/rad]
        static constexpr MinMax CTRL_PARAM_SETTLING_FACTOR = { 2, 8 };      //!< alphas [-]
        static constexpr MinMax CTRL_PARAM_DAMPING_RATIO = { 0.4, 1.5 };    //!< zeta [-]
        static constexpr MinMax CTRL_PARAM_TIME_CST = { 0.1, 8.0 };         //!< Ts [s]


    //************************************************************************
    // functions
    //************************************************************************
    public:
        Model();

        ControlParameters& getControlParameters();

        Gearbox& getGearbox();

        MechanicalLoad& getMechanicalLoad();

        Motor& getMotor();


    //************************************************************************
    // variables
    //************************************************************************
    private:
        Motor               mMotor;                 //!< motor
        Gearbox             mGearbox;               //!< gearbox
        MechanicalLoad      mMechanicalLoad;        //!< mechanical load
        ControlParameters   mControlParameters;     //!< control parameters
};

#endif // Model_h
