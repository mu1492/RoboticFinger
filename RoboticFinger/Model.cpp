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
Model.cpp

This file contains the sources for the model parameters.
*/

#include "Model.h"


//!************************************************************************
//! Constructor
//!************************************************************************
Model::Model()
{
    mMotor = { 10.0, 0.2 };
    mGearbox = { 1000.0 };
    mMechanicalLoad = { 1.75e-5, 2.0e-5 };
    mControlParameters = { 5.7, 4.6, 1.0, 2.97 };
}


//!************************************************************************
//! Get the control parameters object
//!
//! @returns control parameters object
//!************************************************************************
Model::ControlParameters& Model::getControlParameters()
{
    return mControlParameters;
}


//!************************************************************************
//! Get the gearbox object
//!
//! @returns the gearbox object
//!************************************************************************
Model::Gearbox& Model::getGearbox()
{
    return mGearbox;
}


//!************************************************************************
//! Get the mechanical load object
//!
//! @returns the mechanical load object
//!************************************************************************
Model::MechanicalLoad& Model::getMechanicalLoad()
{
    return mMechanicalLoad;
}


//!************************************************************************
//! Get the motor object
//!
//! @returns the motor object
//!************************************************************************
Model::Motor& Model::getMotor()
{
    return mMotor;
}
