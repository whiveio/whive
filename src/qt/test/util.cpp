// Copyright (c) 2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <QApplication>
#include <QMessageBox>
#include <QTimer>
#include <QString>
#include <QPushButton>
#include <QWidget>

void ConfirmMessage(QString* text, int msec)
{
    QTimer::singleShot(msec, makeCallback([text](Callback* callback) {
        for (QWidget* widget : QApplication::topLevelWidgets()) {
            if (widget->inherits("QMessageBox")) {
                QMessageBox* messageBox = qobject_cast<QMessageBox*>(widget);
                if (text) *text = messageBox->text();
                messageBox->defaultButton()->click();
            }
        }
        delete callback;
    }), SLOT(call()));
}
