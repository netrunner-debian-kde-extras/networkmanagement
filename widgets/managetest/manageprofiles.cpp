#include "manageprofilewidget.h"

#include <QApplication>

#include <KApplication>
#include <KCmdLineArgs>
#include <KCmdLineOptions>
#include <KAboutData>
#include <KDialog>
#include <KConfig>
#include <KDebug>

int main(int argc, char **argv)
{
    KAboutData aboutData(QByteArray("testManageProfiles"), 0, ki18n("testManageProfiles"),
                         KDE_VERSION_STRING, ki18n("test"), KAboutData::License_BSD,
                         ki18n("test"));
    KCmdLineArgs::init(argc, argv, &aboutData);
    KApplication app;
    KConfig *config = new KConfig("nmrc", KConfig::SimpleConfig);
    KConfigGroup profileGroup(config, "Profiles");

    KDialog *profiledlg = new KDialog();
    profiledlg->setCaption("Manage Profiles");
    profiledlg->setButtons( KDialog::Ok | KDialog::Cancel);
    ManageProfileWidget *profile = new ManageProfileWidget(profiledlg);
    profile->setConfig(profileGroup);
    profiledlg->setMainWidget(profile);
    profiledlg->show();
    
    int rc =  app.exec();
    kDebug() << "Syncing config file.";
    config->sync();
    delete config;
    return rc;
}

