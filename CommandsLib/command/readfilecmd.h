#pragma once

#include "ICommand.h"
#include <QObject>

class ReadFileCmd : public QObject, public Command::ICommand
{
    Q_OBJECT
public:
    explicit ReadFileCmd(QString path_, size_t size_, qint64 off_, QObject *parent = nullptr);

    // ICommand interface
public:
    QString to_json() const override;

private:
    QString path;
    size_t size;
    qint64 off;
};

