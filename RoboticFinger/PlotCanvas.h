///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2026 Mihai Ursu                                                 //
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
PlotCanvas.h

This file contains the definitions for plotting a trace.
*/

#ifndef PlotCanvas_h
#define PlotCanvas_h

#include "ControlSystem.h"

#include <QFrame>
#include <QPainter>


//************************************************************************
// Class for handling the plot for a trace
//************************************************************************
class PlotCanvas : public QFrame
{
    Q_OBJECT

    //************************************************************************
    // constants and types
    //************************************************************************
    public:
        typedef enum
        {
            PLOT_TYPE_FIG6,
            PLOT_TYPE_FIG7,
            PLOT_TYPE_FIG8_MODULUS,
            PLOT_TYPE_FIG8_PHASE,
            PLOT_TYPE_FIG9_ANGLE,
            PLOT_TYPE_FIG9_GAINS,

            // keep this last
            PLOT_TYPE_UNDEFINED
        }PlotType;

        typedef struct
        {
            double min;
            double max;
        }MinMax;

        typedef struct
        {
            MinMax x;
            MinMax y;
        }xyMinMax;

        static constexpr xyMinMax FIG6_MINMAX = { {0, 5}, {0, 4} };

        static constexpr xyMinMax FIG7_MINMAX = { {0, 2}, {0, 1} };

        static constexpr xyMinMax FIG8_MODULUS_MINMAX = { {0, 5}, {0, 1} };
        static constexpr xyMinMax FIG8_PHASE_MINMAX = { {0, 5}, {-180, 0} };

        static constexpr xyMinMax FIG9_ANGLE_MINMAX = { {0, 3}, {0, 0.15} };
        static constexpr xyMinMax FIG9_GAINS_MINMAX = { {0, 3}, {0, 30} };

    private:
        static constexpr double LEFT_RATIO = 0.15;  //!< width ratio from left edge to the plot area
        static constexpr double RIGHT_RATIO = 0.03; //!< width ratio from right edge to the plot area

        static constexpr double TOP_RATIO = 0.03;   //!< height ratio from top edge to the plot area
        static constexpr double BOTTOM_RATIO = 0.12;//!< height ratio from bottom edge to the plot area


    //************************************************************************
    // functions
    //************************************************************************
    public:
        explicit PlotCanvas
            (
            QWidget*    aParent = nullptr    //!< parent widget
            );

        bool setPlotType
            (
            const PlotType aType    //!< plot type
            );

        void updatePlots
            (
            const ControlSystem& aSystem    //!< control system
            );

    protected:
        void paintEvent
            (
            QPaintEvent*    aEvent  //!< paint event
            )
            override;

    private:
        void drawAbscissaLabels
            (
            QPainter&   aPainter    //!< painter
            );

        void drawGridMinMax
            (
            QPainter&   aPainter    //!< painter
            );

        void drawOrdinateLabels
            (
            QPainter&   aPainter    //!< painter
            );

        void drawTraces
            (
            QPainter&   aPainter    //!< painter
            );


    //************************************************************************
    // variables
    //************************************************************************
    private:
        PlotType        mPlotType;      //!< plot type
        ControlSystem   mSys;           //!< control system
};

#endif // PlotCanvas_h
