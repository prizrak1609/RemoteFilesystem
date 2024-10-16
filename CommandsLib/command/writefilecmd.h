#pragma once

#include "ICommand.h"
#include <QObject>

class WriteFileCmd : public QObject, public Command::ICommand
{
    Q_OBJECT
public:
    explicit WriteFileCmd(QString path_, QByteArray buf_, size_t size_, qint64 off_, QObject *parent = nullptr);

    // ICommand interface
public:
    QString to_json() const override;

private:
    QString path;
    QByteArray buf;
    size_t size;
    qint64 off;
};

