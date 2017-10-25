// For license of this file, see <project-root-folder>/LICENSE.md.

#include "gui/settings/settingsfeedsmessages.h"

#include "definitions/definitions.h"
#include "gui/dialogs/formmain.h"
#include "gui/feedmessageviewer.h"
#include "gui/feedsview.h"
#include "gui/guiutilities.h"
#include "gui/messagesview.h"
#include "gui/timespinbox.h"
#include "miscellaneous/application.h"
#include "miscellaneous/feedreader.h"

#include <QFontDialog>
#include <QLocale>
#include <QStringList>

SettingsFeedsMessages::SettingsFeedsMessages(Settings* settings, QWidget* parent)
  : SettingsPanel(settings, parent), m_ui(new Ui::SettingsFeedsMessages) {
  m_ui->setupUi(this);

  initializeMessageDateFormats();
  GuiUtilities::setLabelAsNotice(*m_ui->label_9, false);

  connect(m_ui->m_spinHeightRowsMessages, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          this, &SettingsFeedsMessages::requireRestart);
  connect(m_ui->m_spinHeightRowsFeeds, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          this, &SettingsFeedsMessages::requireRestart);

  connect(m_ui->m_checkAutoUpdateNotification, &QCheckBox::toggled, this, &SettingsFeedsMessages::dirtifySettings);
  connect(m_ui->m_checkAutoUpdate, &QCheckBox::toggled, this, &SettingsFeedsMessages::dirtifySettings);
  connect(m_ui->m_checkKeppMessagesInTheMiddle, &QCheckBox::toggled, this, &SettingsFeedsMessages::dirtifySettings);
  connect(m_ui->m_checkMessagesDateTimeFormat, &QCheckBox::toggled, this, &SettingsFeedsMessages::dirtifySettings);
  connect(m_ui->m_checkRemoveReadMessagesOnExit, &QCheckBox::toggled, this, &SettingsFeedsMessages::dirtifySettings);
  connect(m_ui->m_checkUpdateAllFeedsOnStartup, &QCheckBox::toggled, this, &SettingsFeedsMessages::dirtifySettings);
  connect(m_ui->m_spinAutoUpdateInterval, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
          this, &SettingsFeedsMessages::dirtifySettings);
  connect(m_ui->m_spinHeightImageAttachments, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          this, &SettingsFeedsMessages::dirtifySettings);
  connect(m_ui->m_spinHeightRowsMessages, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          this, &SettingsFeedsMessages::dirtifySettings);
  connect(m_ui->m_spinHeightRowsFeeds, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          this, &SettingsFeedsMessages::dirtifySettings);
  connect(m_ui->m_checkAutoUpdate, &QCheckBox::toggled, m_ui->m_spinAutoUpdateInterval, &TimeSpinBox::setEnabled);
  connect(m_ui->m_spinFeedUpdateTimeout, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &SettingsFeedsMessages::dirtifySettings);
  connect(m_ui->m_cmbMessagesDateTimeFormat, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
          &SettingsFeedsMessages::dirtifySettings);
  connect(m_ui->m_cmbCountsFeedList, &QComboBox::currentTextChanged, this, &SettingsFeedsMessages::dirtifySettings);
  connect(m_ui->m_cmbCountsFeedList, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
          &SettingsFeedsMessages::dirtifySettings);
  connect(m_ui->m_btnChangeMessagesFont, &QPushButton::clicked, this, &SettingsFeedsMessages::changeMessagesFont);

  if (!m_ui->m_spinFeedUpdateTimeout->suffix().startsWith(' ')) {
    m_ui->m_spinFeedUpdateTimeout->setSuffix(QSL(" ") + m_ui->m_spinFeedUpdateTimeout->suffix());
  }
}

SettingsFeedsMessages::~SettingsFeedsMessages() {
  delete m_ui;
}

void SettingsFeedsMessages::initializeMessageDateFormats() {
  QStringList best_formats;
  const QDateTime current_dt = QDateTime::currentDateTime();
  const QLocale current_locale = qApp->localization()->loadedLocale();

  foreach (const Language& lang, qApp->localization()->installedLanguages()) {
    QLocale locale(lang.m_code);

    best_formats << locale.dateTimeFormat(QLocale::LongFormat)
                 << locale.dateTimeFormat(QLocale::ShortFormat)
                 << locale.dateTimeFormat(QLocale::NarrowFormat);
  }

  best_formats.removeDuplicates();

  foreach (const QString& format, best_formats) {
    m_ui->m_cmbMessagesDateTimeFormat->addItem(current_locale.toString(current_dt, format), format);
  }
}

void SettingsFeedsMessages::changeMessagesFont() {
  bool ok;
  QFont new_font = QFontDialog::getFont(&ok, m_ui->m_lblMessagesFont->font(),
                                        this, tr("Select new font for message viewer"),
                                        QFontDialog::DontUseNativeDialog);

  if (ok) {
    m_ui->m_lblMessagesFont->setFont(new_font);
    dirtifySettings();
  }
}

void SettingsFeedsMessages::loadSettings() {
  onBeginLoadSettings();

  m_ui->m_spinHeightRowsMessages->setValue(settings()->value(GROUP(GUI), SETTING(GUI::HeightRowMessages)).toInt());
  m_ui->m_spinHeightRowsFeeds->setValue(settings()->value(GROUP(GUI), SETTING(GUI::HeightRowFeeds)).toInt());

  m_ui->m_checkAutoUpdateNotification->setChecked(settings()->value(GROUP(Feeds), SETTING(Feeds::EnableAutoUpdateNotification)).toBool());
  m_ui->m_checkKeppMessagesInTheMiddle->setChecked(settings()->value(GROUP(Messages), SETTING(Messages::KeepCursorInCenter)).toBool());
  m_ui->m_checkRemoveReadMessagesOnExit->setChecked(settings()->value(GROUP(Messages), SETTING(Messages::ClearReadOnExit)).toBool());
  m_ui->m_checkAutoUpdate->setChecked(settings()->value(GROUP(Feeds), SETTING(Feeds::AutoUpdateEnabled)).toBool());
  m_ui->m_spinAutoUpdateInterval->setValue(settings()->value(GROUP(Feeds), SETTING(Feeds::AutoUpdateInterval)).toInt());
  m_ui->m_spinFeedUpdateTimeout->setValue(settings()->value(GROUP(Feeds), SETTING(Feeds::UpdateTimeout)).toInt());
  m_ui->m_checkUpdateAllFeedsOnStartup->setChecked(settings()->value(GROUP(Feeds), SETTING(Feeds::FeedsUpdateOnStartup)).toBool());
  m_ui->m_cmbCountsFeedList->addItems(QStringList() << "(%unread)" << "[%unread]" << "%unread/%all" << "%unread-%all" << "[%unread|%all]");
  m_ui->m_cmbCountsFeedList->setEditText(settings()->value(GROUP(Feeds), SETTING(Feeds::CountFormat)).toString());
  m_ui->m_spinHeightImageAttachments->setValue(settings()->value(GROUP(Messages), SETTING(Messages::MessageHeadImageHeight)).toInt());

  m_ui->m_checkMessagesDateTimeFormat->setChecked(settings()->value(GROUP(Messages), SETTING(Messages::UseCustomDate)).toBool());
  const int index_format = m_ui->m_cmbMessagesDateTimeFormat->findData(settings()->value(GROUP(Messages),
                                                                                         SETTING(Messages::CustomDateFormat)).toString());

  if (index_format >= 0) {
    m_ui->m_cmbMessagesDateTimeFormat->setCurrentIndex(index_format);
  }

  m_ui->m_lblMessagesFont->setText(tr("Font preview"));
  QFont fon;

  fon.fromString(settings()->value(GROUP(Messages),
                                   SETTING(Messages::PreviewerFontStandard)).toString());
  m_ui->m_lblMessagesFont->setFont(fon);
  onEndLoadSettings();
}

void SettingsFeedsMessages::saveSettings() {
  onBeginSaveSettings();

  settings()->setValue(GROUP(GUI), GUI::HeightRowMessages, m_ui->m_spinHeightRowsMessages->value());
  settings()->setValue(GROUP(GUI), GUI::HeightRowFeeds, m_ui->m_spinHeightRowsFeeds->value());

  settings()->setValue(GROUP(Feeds), Feeds::EnableAutoUpdateNotification, m_ui->m_checkAutoUpdateNotification->isChecked());
  settings()->setValue(GROUP(Messages), Messages::KeepCursorInCenter, m_ui->m_checkKeppMessagesInTheMiddle->isChecked());
  settings()->setValue(GROUP(Messages), Messages::ClearReadOnExit, m_ui->m_checkRemoveReadMessagesOnExit->isChecked());
  settings()->setValue(GROUP(Feeds), Feeds::AutoUpdateEnabled, m_ui->m_checkAutoUpdate->isChecked());
  settings()->setValue(GROUP(Feeds), Feeds::AutoUpdateInterval, m_ui->m_spinAutoUpdateInterval->value());
  settings()->setValue(GROUP(Feeds), Feeds::UpdateTimeout, m_ui->m_spinFeedUpdateTimeout->value());
  settings()->setValue(GROUP(Feeds), Feeds::FeedsUpdateOnStartup, m_ui->m_checkUpdateAllFeedsOnStartup->isChecked());
  settings()->setValue(GROUP(Feeds), Feeds::CountFormat, m_ui->m_cmbCountsFeedList->currentText());
  settings()->setValue(GROUP(Messages), Messages::UseCustomDate, m_ui->m_checkMessagesDateTimeFormat->isChecked());
  settings()->setValue(GROUP(Messages), Messages::MessageHeadImageHeight, m_ui->m_spinHeightImageAttachments->value());
  settings()->setValue(GROUP(Messages), Messages::CustomDateFormat,
                       m_ui->m_cmbMessagesDateTimeFormat->itemData(m_ui->m_cmbMessagesDateTimeFormat->currentIndex()).toString());

  // Save fonts.
  settings()->setValue(GROUP(Messages), Messages::PreviewerFontStandard, m_ui->m_lblMessagesFont->font().toString());
  qApp->mainForm()->tabWidget()->feedMessageViewer()->loadMessageViewerFonts();
  qApp->feedReader()->updateAutoUpdateStatus();

  qApp->feedReader()->feedsModel()->reloadWholeLayout();

  qApp->feedReader()->messagesModel()->updateDateFormat();
  qApp->feedReader()->messagesModel()->reloadWholeLayout();
  onEndSaveSettings();
}
