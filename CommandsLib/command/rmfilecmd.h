#pragma once

#include "ICommand.h"
#include <QObject>

class RmFileCmd : public QObject, public Command::ICommand
{
    Q_OBJECT
public:
    explicit RmFileCmd(QString path_, QObject *parent = nullptr);

    // ICommand interface
public:
    QString to_json() const override;

private:
    QString path;
};

