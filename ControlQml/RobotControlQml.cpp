#include "RobotControlQml.h"
#include <QCoreApplication>
#include <QScreen>
#include <QRect>
#include <QDesktopWidget>


RobotControlQml::RobotControlQml(RCApplication *app, RCToolbox *toolbox)
    :RCTool(app,toolbox)
{
    m_Window = new QAction("4444444");
    m_Window->setCheckable(true);
    m_name.append(m_Window);
    m_name.append(m_Window);
}

RobotControlQml::~RobotControlQml()
{

}

void RobotControlQml::setToolbox(RCToolbox *toolbox)
{
    RCTool::setToolbox(toolbox);

    int dpiVal = qApp->primaryScreen()->logicalDotsPerInch();

    QDesktopWidget* desktopWidget = QApplication::desktop();

    QRect deskRect = desktopWidget->availableGeometry();


    if(dpiVal == 96)
    {
        m_scaling = 0.85;
    }
    else if(dpiVal == 120)
    {
        m_scaling = 1;
    }

    m_screenWidth = deskRect.width();
    m_screenHeight = deskRect.height();

    m_userManagerQml    = toolbox->userManager();
    m_videoManagerQml   = toolbox->videoManager();
    m_settingManagerQml = toolbox->settingManager();
    m_pathManagerQml    = toolbox->pathManager();
    m_robotManagerQml   = toolbox->robotManager();
    m_vehicleManagerQml = toolbox->vehicleManager();
    m_connectManagerQml = toolbox->connectManager();
    m_factSystemQml     = toolbox->factSystem();
}

int RobotControlQml::screenWidth(void)
{
    return m_screenWidth;
}

int RobotControlQml::screenHeight(void)
{
    return m_screenHeight;
}

double RobotControlQml::scaling(void)
{
    return m_scaling;
}
