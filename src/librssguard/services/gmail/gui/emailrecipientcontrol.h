// For license of this file, see <project-root-folder>/LICENSE.md.

#ifndef EMAILRECIPIENTCONTROL_H
#define EMAILRECIPIENTCONTROL_H

#include <QWidget>

class QComboBox;
class QLineEdit;
class PlainToolButton;

class EmailRecipientControl : public QWidget {
  Q_OBJECT

  public:
    explicit EmailRecipientControl(const QString& recipient, QWidget* parent = nullptr);

  signals:
    void removalRequested();

  private:
    QComboBox* m_cmbRecipientType;
    QLineEdit* m_txtRecipient;
    PlainToolButton* m_btnCloseMe;
};

#endif // EMAILRECIPIENTCONTROL_H
