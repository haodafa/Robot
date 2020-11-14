#ifndef ROBOTCONTROLQML_H
#define ROBOTCONTROLQML_H
#include <QObject>

#include "RCapplication.h"

class RobotControlQml : public RCTool
{
    Q_OBJECT
public:
    RobotControlQml(RCApplication *app, RCToolbox *toolbox);
    ~RobotControlQml();

    Q_PROPERTY(QString appName      READ appName CONSTANT)
    Q_PROPERTY(QString version      READ version CONSTANT)
    Q_PROPERTY(int currentTabIndex  READ currentTabIndex WRITE setCurrentTabIndex)
    Q_PROPERTY(int screenWidth      READ screenWidth CONSTANT)
    Q_PROPERTY(int screenHeight     READ screenHeight CONSTANT)
    Q_PROPERTY(double scaling       READ scaling CONSTANT)

    Q_PROPERTY(UserManager*     userManagerQml      READ userManagerQml     CONSTANT)
    Q_PROPERTY(VideoManager*    videoManagerQml     READ videoManagerQml    CONSTANT)
    Q_PROPERTY(SettingManager*  settingManagerQml   READ settingManagerQml  CONSTANT)
    Q_PROPERTY(PathManager*     pathManagerQml      READ pathManagerQml     CONSTANT)
    Q_PROPERTY(RobotManager*    robotManagerQml     READ robotManagerQml    CONSTANT)
    Q_PROPERTY(VehicleManager*  vehicleManagerQml   READ vehicleManagerQml  CONSTANT)
    Q_PROPERTY(ConnectManager*  connectManagerQml   READ connectManagerQml  CONSTANT)
    Q_PROPERTY(FactSystem*      factSystemQml       READ factSystemQml      CONSTANT)

    Q_PROPERTY(QList<QObject*> name READ name CONSTANT)

    QList<QObject*> name() {return m_name; }

    virtual void setToolbox(RCToolbox *toolbox);

    QString appName()       {return rcApp()->applicationName();}
    QString version()       {return rcApp()->applicationVersion();}
    int currentTabIndex()   {return m_currentTabIndex;}

    int screenWidth(void);
    int screenHeight(void);
    double scaling(void);


    UserManager*    userManagerQml(void)    {return m_userManagerQml;}
    VideoManager*   videoManagerQml(void)   {return m_videoManagerQml;}
    SettingManager* settingManagerQml(void) {return m_settingManagerQml;}
    PathManager*    pathManagerQml(void)    {return m_pathManagerQml;}
    RobotManager*   robotManagerQml(void)   {return m_robotManagerQml;}
    VehicleManager* vehicleManagerQml(void) {return m_vehicleManagerQml;}
    ConnectManager* connectManagerQml(void) {return m_connectManagerQml;}
    FactSystem*     factSystemQml(void)     {return m_factSystemQml;}

    void setCurrentTabIndex(int index){m_currentTabIndex = index;}

private:
    UserManager*    m_userManagerQml;
    VideoManager*   m_videoManagerQml;
    SettingManager* m_settingManagerQml;
    PathManager*    m_pathManagerQml;
    RobotManager*   m_robotManagerQml;
    VehicleManager* m_vehicleManagerQml;
    ConnectManager* m_connectManagerQml;
    FactSystem*     m_factSystemQml;

    int m_screenWidth;
    int m_screenHeight;
    double m_scaling;
    int m_currentTabIndex=0;

    QList<QObject*> m_name;

    QAction *m_Window;
};

#endif // ROBOTCONTROLQML_H
