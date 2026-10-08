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
PlotCanvas.cpp

This file contains the sources for plotting a trace.
*/

#include "PlotCanvas.h"

#include <cmath>
#include <iostream>

#include <QColor>
#include <QFont>
#include <QPen>
#include <QString>
#include <QTextDocument>


//!************************************************************************
//! Constructor
//!************************************************************************
PlotCanvas::PlotCanvas
    (
    QWidget* aParent    //!< parent widget
    )
    : QFrame( aParent )
    , mPlotType( PLOT_TYPE_UNDEFINED )
{
}


//!************************************************************************
//! Draw the x-axis labels
//!
//! @returns nothing
//!************************************************************************
void PlotCanvas::drawAbscissaLabels
    (
    QPainter&   aPainter    //!< painter
    )
{
    aPainter.setPen( Qt::white );
    QFont font( "Arial", 9 );
    QFontMetrics fm( font );
    aPainter.setFont( font );
    int y = height() * ( 1.0 - BOTTOM_RATIO ) + 1.2 * fm.height();
    int x = width() * ( 1.0 + LEFT_RATIO - RIGHT_RATIO ) / 2.0;
    QTextDocument doc;

    switch( mPlotType )
    {
        case PLOT_TYPE_FIG6:
            aPainter.drawText( x, y, "S" );
            break;

        case PLOT_TYPE_FIG7:
            aPainter.drawText( x, y, "t" );
            break;

        case PLOT_TYPE_FIG8_MODULUS:
        case PLOT_TYPE_FIG8_PHASE:
            doc.setHtml(
                "<span style='font-size: 9pt; color: white;'>"
                "&#x03C9;/&#x03C9;<sub>n</sub>"
                "</span>"
            );

            aPainter.save();
            aPainter.translate( x - 15, y - 15 );
            doc.drawContents( &aPainter, rect() );
            aPainter.restore();
            break;

        case PLOT_TYPE_FIG9_ANGLE:
        case PLOT_TYPE_FIG9_GAINS:
            doc.setHtml(
                "<span style='font-size: 9pt; color: white;'>"
                "T<sub>s</sub>"
                "</span>"
            );

            aPainter.save();
            aPainter.translate( x, y - 15 );
            doc.drawContents( &aPainter, rect() );
            aPainter.restore();
            break;

        default:
            break;
    }
}


//!************************************************************************
//! Draw the grid and min-max values
//!
//! @returns nothing
//!************************************************************************
void PlotCanvas::drawGridMinMax
    (
    QPainter&   aPainter    //!< painter
    )
{
    int xLeft = width() * LEFT_RATIO;
    int xRight = width() * ( 1.0 - RIGHT_RATIO );
    int plotWidth = xRight - xLeft;

    int yTop = height() * TOP_RATIO;
    int yBottom = height() * ( 1.0 - BOTTOM_RATIO );
    int plotHeight = yBottom - yTop;

    aPainter.setPen( QPen( Qt::gray, 0.75 ) );
    aPainter.drawRect( xLeft, yTop, plotWidth, plotHeight );

    int horizGridLines = 0;
    int vertGridLines = 0;

    QString xMinStr;
    QString xMaxStr;
    QString yMinStr;
    QString yMaxStr;

    switch( mPlotType )
    {
        case PLOT_TYPE_FIG6:
            horizGridLines = 3;
            vertGridLines = 4;
            xMinStr = QString::number( FIG6_MINMAX.x.min );
            xMaxStr = QString::number( FIG6_MINMAX.x.max );
            yMinStr = QString::number( FIG6_MINMAX.y.min );
            yMaxStr = QString::number( FIG6_MINMAX.y.max );
            break;

        case PLOT_TYPE_FIG7:
            horizGridLines = 4;
            vertGridLines = 3;
            xMinStr = QString::number( FIG7_MINMAX.x.min );
            xMaxStr = QString::number( FIG7_MINMAX.x.max );
            yMinStr = QString::number( FIG7_MINMAX.y.min );
            yMaxStr = QString::number( FIG7_MINMAX.y.max );
            break;

        case PLOT_TYPE_FIG8_MODULUS:
            horizGridLines = 4;
            vertGridLines = 4;
            xMinStr = QString::number( FIG8_MODULUS_MINMAX.x.min );
            xMaxStr = QString::number( FIG8_MODULUS_MINMAX.x.max );
            yMinStr = QString::number( FIG8_MODULUS_MINMAX.y.min );
            yMaxStr = QString::number( FIG8_MODULUS_MINMAX.y.max );
            break;

        case PLOT_TYPE_FIG8_PHASE:
            horizGridLines = 5;
            vertGridLines = 4;
            xMinStr = QString::number( FIG8_PHASE_MINMAX.x.min );
            xMaxStr = QString::number( FIG8_PHASE_MINMAX.x.max );
            yMinStr = QString::number( FIG8_PHASE_MINMAX.y.min );
            yMaxStr = QString::number( FIG8_PHASE_MINMAX.y.max );
            break;

        case PLOT_TYPE_FIG9_ANGLE:
            horizGridLines = 2;
            vertGridLines = 2;
            xMinStr = QString::number( FIG9_ANGLE_MINMAX.x.min );
            xMaxStr = QString::number( FIG9_ANGLE_MINMAX.x.max );
            yMinStr = QString::number( FIG9_ANGLE_MINMAX.y.min );
            yMaxStr = QString::number( FIG9_ANGLE_MINMAX.y.max );
            break;

        case PLOT_TYPE_FIG9_GAINS:
            horizGridLines = 2;
            vertGridLines = 2;
            xMinStr = QString::number( FIG9_GAINS_MINMAX.x.min );
            xMaxStr = QString::number( FIG9_GAINS_MINMAX.x.max );
            yMinStr = QString::number( FIG9_GAINS_MINMAX.y.min );
            yMaxStr = QString::number( FIG9_GAINS_MINMAX.y.max );
            break;

        default:
            break;
    }

    aPainter.setPen( QPen( Qt::gray, 0.75, Qt::DotLine ) );

    for( int i = 1; i <= horizGridLines; i++ )
    {
        int y = yTop + i * plotHeight / ( horizGridLines + 1 );
        aPainter.drawLine( xLeft, y, xRight, y );
    }

    for( int i = 1; i <= vertGridLines; i++ )
    {
        int x = xLeft + i * plotWidth / ( vertGridLines + 1 );
        aPainter.drawLine( x, yTop, x, yBottom );
    }

    aPainter.setPen( Qt::green );
    QFont font( "Courier", 10 );
    QFontMetrics fm( font );
    int fontHeight = fm.height();
    aPainter.setFont( font );

    aPainter.drawText( xLeft, yBottom + fontHeight, xMinStr );
    aPainter.drawText( xRight - fm.horizontalAdvance( xMaxStr ), yBottom + fontHeight, xMaxStr );

    aPainter.drawText( xLeft - 10 - fm.horizontalAdvance( yMinStr ), yBottom, yMinStr );
    aPainter.drawText( xLeft - 10 - fm.horizontalAdvance( yMaxStr ), yTop + fontHeight, yMaxStr );
}


//!************************************************************************
//! Draw the y-axis labels
//!
//! @returns nothing
//!************************************************************************
void PlotCanvas::drawOrdinateLabels
    (
    QPainter&   aPainter    //!< painter
    )
{
    aPainter.setPen( Qt::white );
    QFont font( "Arial", 9 );
    QFontMetrics fm( font );
    aPainter.setFont( font );
    int x = 5;
    int y = ( height() * ( 1.0 + TOP_RATIO - BOTTOM_RATIO ) - fm.height() ) / 2;
    QTextDocument doc;

    switch( mPlotType )
    {
        case PLOT_TYPE_FIG6:
            doc.setHtml(
                "<span style='font-size: 9pt; color: yellow;'>"
                "E"
                "</span>"
            );

            aPainter.save();
            aPainter.translate( x, y );
            doc.drawContents( &aPainter, rect() );
            aPainter.restore();
            break;

        case PLOT_TYPE_FIG7:
            doc.setHtml(
                "<span style='font-size: 9pt; color: yellow;'>"
                "&#x03B8;<sub>o</sub>/&#x03B8;<sub>i</sub>"
                "</span>"
            );

            aPainter.save();
            aPainter.translate( x, y );
            doc.drawContents( &aPainter, rect() );
            aPainter.restore();
            break;

        case PLOT_TYPE_FIG8_MODULUS:
            doc.setHtml(
                "<span style='font-size: 9pt; color: yellow;'>"
                "|&#x03B8;<sub>o</sub>/&#x03B8;<sub>i</sub>|"
                "</span>"
            );

            aPainter.save();
            aPainter.translate( x, y );
            doc.drawContents( &aPainter, rect() );
            aPainter.restore();
            break;

        case PLOT_TYPE_FIG8_PHASE:
            doc.setHtml(
                "<span style='font-size: 9pt; color: yellow;'>"
                "&#x03A6;"
                "</span>"
            );

            aPainter.save();
            aPainter.translate( x, y );
            doc.drawContents( &aPainter, rect() );
            aPainter.restore();
            break;

        case PLOT_TYPE_FIG9_ANGLE:
            doc.setHtml(
                "<span style='font-size: 9pt; color: yellow;'>"
                "&#x03B8;<sub>o</sub>"
                "</span>"
            );

            aPainter.save();
            aPainter.translate( x, y );
            doc.drawContents( &aPainter, rect() );
            aPainter.restore();
            break;

        case PLOT_TYPE_FIG9_GAINS:
            doc.setHtml(
                "<span style='font-size: 9pt; color: red;'>K<sub>a</sub></span>"
                "<span style='font-size: 9pt; color: magenta;'><br>50K<sub>b</sub></span>"
            );

            aPainter.save();
            aPainter.translate( x, y );
            doc.drawContents( &aPainter, rect() );
            aPainter.restore();
            break;

        default:
            break;
    }
}


//!************************************************************************
//! Draw the traces
//!
//! @returns nothing
//!************************************************************************
void PlotCanvas::drawTraces
    (
    QPainter&   aPainter    //!< painter
    )
{
    int xLeft = width() * LEFT_RATIO;
    int xRight = width() * ( 1.0 - RIGHT_RATIO );
    int plotWidth = xRight - xLeft;

    int yTop = height() * TOP_RATIO;
    int yBottom = height() * ( 1.0 - BOTTOM_RATIO );
    int plotHeight = yBottom - yTop;

    aPainter.setPen( QPen( Qt::yellow, 1.0 ) );
    int yOld = 0;
    const double PI = 4.0 * atan( 1.0 );

    switch( mPlotType )
    {
        case PLOT_TYPE_FIG6:
            {
                double ts = mSys.getModel().getControlParameters().timeConstant;
                yOld = yBottom - plotHeight * mSys.getForceGainFromStiffness( ts, FIG6_MINMAX.x.min ) / ( FIG6_MINMAX.y.max - FIG6_MINMAX.y.min );

                for( int x = xLeft + 1; x <= xRight; x++ )
                {
                    double s = FIG6_MINMAX.x.min + ( FIG6_MINMAX.x.max - FIG6_MINMAX.x.min ) * ( x - xLeft ) / plotWidth;
                    int y = yBottom - plotHeight * mSys.getForceGainFromStiffness( ts, s ) / ( FIG6_MINMAX.y.max - FIG6_MINMAX.y.min );

                    if( yOld >= yTop && y >= yTop && yOld <= yBottom && y <= yBottom )
                    {
                        aPainter.drawLine( x - 1, yOld, x, y );
                    }

                    yOld = y;
                }
            }
            break;

        case PLOT_TYPE_FIG7:
            {
                double ts = mSys.getModel().getControlParameters().timeConstant;
                yOld = yBottom - plotHeight * mSys.getStepResponse( ts, FIG7_MINMAX.x.min ) / ( FIG7_MINMAX.y.max - FIG7_MINMAX.y.min );

                for( int x = xLeft + 1; x <= xRight; x++ )
                {
                    double t = FIG7_MINMAX.x.min + ( FIG7_MINMAX.x.max - FIG7_MINMAX.x.min ) * ( x - xLeft ) / plotWidth;
                    int y = yBottom - plotHeight * mSys.getStepResponse( ts, t ) / ( FIG7_MINMAX.y.max - FIG7_MINMAX.y.min );

                    if( yOld >= yTop && y >= yTop && yOld <= yBottom && y <= yBottom )
                    {
                        aPainter.drawLine( x - 1, yOld, x, y );
                    }

                    yOld = y;
                }
            }
            break;

        case PLOT_TYPE_FIG8_MODULUS:
            {
                double ts = mSys.getModel().getControlParameters().timeConstant;
                double wn = mSys.getNaturalFrequency( ts );
                double w = wn * FIG8_MODULUS_MINMAX.x.min;
                auto response = mSys.getFrequencyResponse( ts, w );
                yOld = yBottom - plotHeight * response.first / ( FIG8_MODULUS_MINMAX.y.max - FIG8_MODULUS_MINMAX.y.min );

                for( int x = xLeft + 1; x <= xRight; x++ )
                {
                    w = wn * ( FIG8_MODULUS_MINMAX.x.min + ( FIG8_MODULUS_MINMAX.x.max - FIG8_MODULUS_MINMAX.x.min ) * ( x - xLeft ) / plotWidth );
                    response = mSys.getFrequencyResponse( ts, w );
                    int y = yBottom - plotHeight * response.first / ( FIG8_MODULUS_MINMAX.y.max - FIG8_MODULUS_MINMAX.y.min );

                    if( yOld >= yTop && y >= yTop && yOld <= yBottom && y <= yBottom )
                    {
                        aPainter.drawLine( x - 1, yOld, x, y );
                    }

                    yOld = y;
                }
            }
            break;

        case PLOT_TYPE_FIG8_PHASE:
            {
                double ts = mSys.getModel().getControlParameters().timeConstant;
                double wn = mSys.getNaturalFrequency( ts );
                double w = wn * FIG8_PHASE_MINMAX.x.min;
                auto response = mSys.getFrequencyResponse( ts, w );
                yOld = yTop - plotHeight * ( response.second * 180.0 / PI ) / ( FIG8_PHASE_MINMAX.y.max - FIG8_PHASE_MINMAX.y.min );

                for( int x = xLeft + 1; x <= xRight; x++ )
                {
                    w = wn * ( FIG8_PHASE_MINMAX.x.min + ( FIG8_PHASE_MINMAX.x.max - FIG8_PHASE_MINMAX.x.min ) * ( x - xLeft ) / plotWidth );
                    response = mSys.getFrequencyResponse( ts, w );
                    int y = yTop - plotHeight * ( response.second * 180.0 / PI ) / ( FIG8_PHASE_MINMAX.y.max - FIG8_PHASE_MINMAX.y.min );

                    if( yOld >= yTop && y >= yTop && yOld <= yBottom && y <= yBottom )
                    {
                        aPainter.drawLine( x - 1, yOld, x, y );
                    }

                    yOld = y;
                }
            }
            break;

        case PLOT_TYPE_FIG9_ANGLE:
            {
                yOld = yBottom - plotHeight * ( mSys.getTorqueStepAngle( FIG9_ANGLE_MINMAX.x.min, 1, 0 ) * 180.0 / PI ) / ( FIG9_ANGLE_MINMAX.y.max - FIG9_ANGLE_MINMAX.y.min );

                for( int x = xLeft + 1; x <= xRight; x++ )
                {
                    double ts = FIG9_ANGLE_MINMAX.x.min + ( FIG9_ANGLE_MINMAX.x.max - FIG9_ANGLE_MINMAX.x.min ) * ( x - xLeft ) / plotWidth;
                    int y = yBottom - plotHeight * ( mSys.getTorqueStepAngle( ts, 1, 0 ) * 180.0 / PI ) / ( FIG9_ANGLE_MINMAX.y.max - FIG9_ANGLE_MINMAX.y.min );

                    if( yOld >= yTop && y >= yTop && yOld <= yBottom && y <= yBottom )
                    {
                        aPainter.drawLine( x - 1, yOld, x, y );
                    }

                    yOld = y;
                }
            }
            break;

        case PLOT_TYPE_FIG9_GAINS:
            {
                // Ka
                aPainter.setPen( QPen( Qt::red, 1.0 ) );
                yOld = yBottom - plotHeight * mSys.getPositionGain( FIG9_GAINS_MINMAX.x.min ) / ( FIG9_GAINS_MINMAX.y.max - FIG9_GAINS_MINMAX.y.min );

                for( int x = xLeft + 1; x <= xRight; x++ )
                {
                    double ts = FIG9_GAINS_MINMAX.x.min + ( FIG9_GAINS_MINMAX.x.max - FIG9_GAINS_MINMAX.x.min ) * ( x - xLeft ) / plotWidth;
                    int y = yBottom - plotHeight * mSys.getPositionGain( ts ) / ( FIG9_GAINS_MINMAX.y.max - FIG9_GAINS_MINMAX.y.min );

                    if( yOld >= yTop && y >= yTop && yOld <= yBottom && y <= yBottom )
                    {
                        aPainter.drawLine( x - 1, yOld, x, y );
                    }

                    yOld = y;
                }

                // Kb
                aPainter.setPen( QPen( Qt::magenta, 1.0 ) );
                const int MUL = 50;
                yOld = yBottom - plotHeight * MUL * mSys.getVelocityGain( FIG9_GAINS_MINMAX.x.min ) / ( FIG9_GAINS_MINMAX.y.max - FIG9_GAINS_MINMAX.y.min );

                for( int x = xLeft + 1; x <= xRight; x++ )
                {
                    double ts = FIG9_GAINS_MINMAX.x.min + ( FIG9_GAINS_MINMAX.x.max - FIG9_GAINS_MINMAX.x.min ) * ( x - xLeft ) / plotWidth;
                    int y = yBottom - plotHeight * MUL * mSys.getVelocityGain( ts ) / ( FIG9_GAINS_MINMAX.y.max - FIG9_GAINS_MINMAX.y.min );

                    if( yOld >= yTop && y >= yTop && yOld <= yBottom && y <= yBottom )
                    {
                        aPainter.drawLine( x - 1, yOld, x, y );
                    }

                    yOld = y;
                }
            }
            break;

        default:
            break;
    }
}


//!************************************************************************
//! Handle paint events
//!
//! @returns nothing
//!************************************************************************
void PlotCanvas::paintEvent
    (
    QPaintEvent*    aEvent  //!< paint event
    )
{
    QFrame::paintEvent( aEvent );

    QPainter painter( this );
    painter.fillRect( rect(), Qt::black );

    drawAbscissaLabels( painter );
    drawOrdinateLabels( painter );
    drawGridMinMax( painter );    
    drawTraces( painter );
}


//!************************************************************************
//! Set the plot type
//!
//! @returns true if the type can be set
//!************************************************************************
bool PlotCanvas::setPlotType
    (
    const PlotType aType    //!< plot type
    )
{
    bool status = false;

    if( aType < PLOT_TYPE_UNDEFINED )
    {
        mPlotType = aType;
        status = true;
    }

    return status;
}


//!************************************************************************
//! Update the plots
//!
//! @returns nothing
//!************************************************************************
void PlotCanvas::updatePlots
    (
    const ControlSystem& aSystem    //!< control system
    )
{
    mSys = aSystem;
    update();
}
