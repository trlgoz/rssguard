// This file is part of RSS Guard.
//
// Copyright (C) 2011-2016 by Martin Rotter <rotter.martinos@gmail.com>
//
// RSS Guard is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// RSS Guard is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RSS Guard. If not, see <http://www.gnu.org/licenses/>.

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

#include "definitions/definitions.h"

#include "miscellaneous/settingsproperties.h"

#include <QNetworkProxy>
#include <QStringList>
#include <QColor>

#define KEY extern const char*
#define DKEY const char*
#define VALUE(x) extern const x
#define NON_CONST_VALUE(x) extern x
#define DVALUE(x) const x
#define NON_CONST_DVALUE(x) x
#define SETTING(x) x, x##Def
#define DEFAULT_VALUE(x) x##Def
#define GROUP(x) x::ID


// Feeds.
namespace Feeds {
  KEY ID;

  KEY UpdateTimeout;
  VALUE(int) UpdateTimeoutDef;

  KEY CountFormat;
  VALUE(char*) CountFormatDef;

  KEY AutoUpdateInterval;
  VALUE(int) AutoUpdateIntervalDef;

  KEY AutoUpdateEnabled;
  VALUE(bool) AutoUpdateEnabledDef;

  KEY FeedsUpdateOnStartup;
  VALUE(bool) FeedsUpdateOnStartupDef;

  KEY ShowOnlyUnreadFeeds;
  VALUE(bool) ShowOnlyUnreadFeedsDef;
}

// Messages.
namespace Messages {
  KEY ID;

  KEY MessageHeadImageHeight;
  VALUE(int) MessageHeadImageHeightDef;

  KEY UseCustomDate;
  VALUE(bool) UseCustomDateDef;

  KEY CustomDateFormat;
  VALUE(char*) CustomDateFormatDef;

  KEY ClearReadOnExit;
  VALUE(bool) ClearReadOnExitDef;

  KEY KeepCursorInCenter;
  VALUE(bool) KeepCursorInCenterDef;

  KEY PreviewerFontStandard;
  NON_CONST_VALUE(QString) PreviewerFontStandardDef;
}

// GUI.
namespace GUI {
  KEY ID;

  KEY SplitterFeeds;
  VALUE(char*) SplitterFeedsDef;

  KEY SplitterMessages;
  VALUE(char*) SplitterMessagesDef;

  KEY ToolbarStyle;
  VALUE(Qt::ToolButtonStyle) ToolbarStyleDef;

  KEY FeedsToolbarActions;
  VALUE(char*) FeedsToolbarActionsDef;

  KEY StatusbarActions;
  VALUE(char*) StatusbarActionsDef;

  KEY MainWindowInitialSize;
  KEY MainWindowInitialPosition;

  KEY IsMainWindowMaximizedBeforeFullscreen;
  VALUE(bool) IsMainWindowMaximizedBeforeFullscreenDef;

  KEY MainWindowStartsFullscreen;
  VALUE(bool) MainWindowStartsFullscreenDef;

  KEY MainWindowStartsHidden;
  VALUE(bool) MainWindowStartsHiddenDef;

  KEY MainWindowStartsMaximized;
  VALUE(bool) MainWindowStartsMaximizedDef;

  KEY MainMenuVisible;
  VALUE(bool) MainMenuVisibleDef;

  KEY ToolbarsVisible;
  VALUE(bool) ToolbarsVisibleDef;

  KEY ListHeadersVisible;
  VALUE(bool) ListHeadersVisibleDef;

  KEY StatusBarVisible;
  VALUE(bool) StatusBarVisibleDef;

  KEY HideMainWindowWhenMinimized;
  VALUE(bool) HideMainWindowWhenMinimizedDef;

  KEY UseTrayIcon;
  VALUE(bool) UseTrayIconDef;

  KEY EnableNotifications;
  VALUE(bool) EnableNotificationsDef;

  KEY TabCloseMiddleClick;
  VALUE(bool) TabCloseMiddleClickDef;

  KEY TabCloseDoubleClick;
  VALUE(bool) TabCloseDoubleClickDef;

  KEY TabNewDoubleClick;
  VALUE(bool) TabNewDoubleClickDef;

  KEY HideTabBarIfOnlyOneTab;
  VALUE(bool) HideTabBarIfOnlyOneTabDef;

  KEY MessagesToolbarDefaultButtons;
  VALUE(char*) MessagesToolbarDefaultButtonsDef;

  KEY DefaultSortColumnMessages;
  VALUE(int) DefaultSortColumnMessagesDef;

  KEY DefaultSortOrderMessages;
  VALUE(Qt::SortOrder) DefaultSortOrderMessagesDef;

  KEY DefaultSortColumnFeeds;
  VALUE(int) DefaultSortColumnFeedsDef;

  KEY DefaultSortOrderFeeds;
  VALUE(Qt::SortOrder) DefaultSortOrderFeedsDef;

  KEY IconTheme;
  VALUE(char*) IconThemeDef;

  KEY Skin;
  VALUE(char*) SkinDef;

  KEY Style;
  VALUE(char*) StyleDef;
}

// General.
namespace General {
  KEY ID;

  KEY UpdateOnStartup;
  VALUE(bool) UpdateOnStartupDef;

  KEY RemoveTrolltechJunk;
  VALUE(bool) RemoveTrolltechJunkDef;

  KEY FirstRun;
  VALUE(bool) FirstRunDef;

  KEY Language;
  VALUE(QString) LanguageDef;
}

// Downloads.
namespace Downloads {
  KEY ID;

  KEY AlwaysPromptForFilename;
  VALUE(bool) AlwaysPromptForFilenameDef;

  KEY TargetDirectory;
  VALUE(QString) TargetDirectoryDef;

  KEY RemovePolicy;
  VALUE(int) RemovePolicyDef;

  KEY TargetExplicitDirectory;
  VALUE(QString) TargetExplicitDirectoryDef;

  KEY ShowDownloadsWhenNewDownloadStarts;
  VALUE(bool) ShowDownloadsWhenNewDownloadStartsDef;

  KEY ItemUrl;
  KEY ItemLocation;
  KEY ItemDone;
}

// Proxy.
namespace Proxy {
  KEY ID;

  KEY Type;
  VALUE(QNetworkProxy::ProxyType) TypeDef;

  KEY Host;
  VALUE(QString) HostDef;

  KEY Username;
  VALUE(QString) UsernameDef;

  KEY Password;
  VALUE(QString) PasswordDef;

  KEY Port;
  VALUE(int) PortDef;
}

// Database.
namespace Database {
  KEY ID;

  KEY UseTransactions;
  VALUE(bool) UseTransactionsDef;

  KEY UseInMemory;
  VALUE(bool) UseInMemoryDef;

  KEY MySQLHostname;
  VALUE(QString) MySQLHostnameDef;

  KEY MySQLUsername;
  VALUE(QString) MySQLUsernameDef;

  KEY MySQLPassword;
  VALUE(QString) MySQLPasswordDef;

  KEY MySQLPort;
  VALUE(int) MySQLPortDef;

  KEY MySQLDatabase;
  VALUE(char*) MySQLDatabaseDef;

  KEY ActiveDriver;
  VALUE(char*) ActiveDriverDef;
}

// Keyboard.
namespace Keyboard {
  KEY ID;
}

// Web browser.
namespace Browser {
  KEY ID;

  KEY CustomExternalBrowserEnabled;
  VALUE(bool) CustomExternalBrowserEnabledDef;

  KEY CustomExternalBrowserExecutable;
  VALUE(QString) CustomExternalBrowserExecutableDef;

  KEY CustomExternalBrowserArguments;
  VALUE(char*) CustomExternalBrowserArgumentsDef;

  KEY CustomExternalEmailEnabled;
  VALUE(bool) CustomExternalEmailEnabledDef;

  KEY CustomExternalEmailExecutable;
  VALUE(QString) CustomExternalEmailExecutableDef;

  KEY CustomExternalEmailArguments;
  VALUE(char*) CustomExternalEmailArgumentsDef;
}

// Categories.
namespace CategoriesExpandStates {
  KEY ID;
}

class Settings : public QSettings {
    Q_OBJECT

  public:
    // Destructor.
    virtual ~Settings();

    // Type of used settings.
    inline SettingsProperties::SettingsType type() const {
      return m_initializationStatus;
    }

    // Returns the base folder to which store user data, the "data" folder.
    QString userSettingsRootFolder() const;

    // Getters/setters for settings values.
    inline QVariant value(const QString &section, const QString &key, const QVariant &default_value = QVariant()) const {
      return QSettings::value(QString("%1/%2").arg(section, key), default_value);
    }

    inline void setValue(const QString &section,  const QString &key, const QVariant &value) {
      QSettings::setValue(QString("%1/%2").arg(section, key), value);
    }

    inline void setValue(const QString &key, const QVariant &value) {
      QSettings::setValue(key, value);
    }

    inline bool contains(const QString &section, const QString &key) const {
      return QSettings::contains(QString("%1/%2").arg(section, key));
    }

    inline void remove(const QString &section, const QString &key) {
      QSettings::remove(QString("%1/%2").arg(section, key));
    }

    // Returns the path which contains the settings.
    QString pathName() const;

    // Synchronizes settings.
    QSettings::Status checkSettings();

    bool initiateRestoration(const QString &settings_backup_file_path);
    static void finishRestoration(const QString &desired_settings_file_path);

    static QString getAppPathUserFolder();
    static QString getHomeUserFolder();

    // Creates settings file in correct location.
    static Settings *setupSettings(QObject *parent);

    // Returns properties of the actual application-wide settings.
    static SettingsProperties determineProperties();

  private:
    // Constructor.
    explicit Settings(const QString &file_name, Format format, const SettingsProperties::SettingsType &type, QObject *parent = 0);

    SettingsProperties::SettingsType m_initializationStatus;
};

#endif // SETTINGS_H
