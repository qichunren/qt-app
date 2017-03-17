#ifndef CONFIGURATION_DIALOG_H
#define CONFIGURATION_DIALOG_H

#include <QDialog>

namespace Ui {
class ConfigurationDialog;
}

class ConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationDialog(QWidget *parent = 0);
    ~ConfigurationDialog();

private:
    Ui::ConfigurationDialog *ui;
};

#endif // CONFIGURATION_DIALOG_H
