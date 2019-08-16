#include "MemoryWidget.h"

#include <QtCharts/QAreaSeries>
#include <QLinearGradient>
#include <QPen>

#include "SysInfo.h"

using namespace QtCharts;

const int CHART_X_RANGE_COUNT = 50;
const int CHART_X_RANGE_MAX = CHART_X_RANGE_COUNT - 1;
const int COLOR_DARK_BLUE = 0x209fdf;
const int COLOR_LIGHT_BLUE = 0xbfdfef;
const int PEN_WIDTH = 3;

MemoryWidget::MemoryWidget(QWidget *parent) :
    SysInfoWidget(parent),
    mSeries(new QLineSeries(this)),
    mPointPositionX(0)
{
    QPen pen(COLOR_DARK_BLUE);
    pen.setWidth(PEN_WIDTH);

    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setColorAt(1.0, COLOR_DARK_BLUE);
    gradient.setColorAt(0.0, COLOR_LIGHT_BLUE);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);

    QAreaSeries* areaSeries = new QAreaSeries(mSeries);
    areaSeries->setPen(pen);
    areaSeries->setBrush(gradient);

    QChart* chart = chartView().chart();
    chart->addSeries(areaSeries);
    QString s("Memory used: ");
    s += QString::number(0) + "/" + QString::number(10);

    chart->setTitle(s);
    chart->createDefaultAxes();
    chart->axisX()->setVisible(false);
    chart->axisX()->setRange(0, CHART_X_RANGE_MAX);
    chart->axisY()->setRange(0, 100);
}

void MemoryWidget::updateSeries()
{
    double memoryUsed = SysInfo::instance().memoryUsed();
    mSeries->append(mPointPositionX++, memoryUsed);

    //update used title
    QChart* chart = chartView().chart();
    QString s("Memory used: ");
    s += QString::number(SysInfo::instance().rawMemoryUsed()/1000000000.0)
            + "/" + QString::number(SysInfo::instance().rawMemoryHave()/1000000000.0);
    chart->setTitle(s);

    //prevent infinite dataset
    if (mSeries->count() > CHART_X_RANGE_COUNT) {
        QChart* chart = chartView().chart();
        //scroll to lastest point on x-axis
        chart->scroll(chart->plotArea().width()
                      / CHART_X_RANGE_MAX, 0);
        mSeries->remove(0);
    }
}
