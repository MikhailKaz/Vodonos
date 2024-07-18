/********************************************************************************
** Form generated from reading UI file 'game.ui'
**
** Created by: Qt User Interface Compiler version 5.15.14
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_H
#define UI_GAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_game
{
public:
    QPushButton *pbRock;
    QPushButton *pbScissors;
    QPushButton *pbPaper;
    QLabel *label;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QDialog *game)
    {
        if (game->objectName().isEmpty())
            game->setObjectName(QString::fromUtf8("game"));
        game->resize(389, 292);
        pbRock = new QPushButton(game);
        pbRock->setObjectName(QString::fromUtf8("pbRock"));
        pbRock->setGeometry(QRect(30, 170, 91, 81));
        QFont font;
        font.setPointSize(10);
        pbRock->setFont(font);
        pbScissors = new QPushButton(game);
        pbScissors->setObjectName(QString::fromUtf8("pbScissors"));
        pbScissors->setGeometry(QRect(150, 170, 91, 81));
        pbScissors->setFont(font);
        pbPaper = new QPushButton(game);
        pbPaper->setObjectName(QString::fromUtf8("pbPaper"));
        pbPaper->setGeometry(QRect(270, 170, 91, 81));
        pbPaper->setFont(font);
        label = new QLabel(game);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 361, 151));
        QFont font1;
        font1.setPointSize(36);
        font1.setBold(true);
        label->setFont(font1);
        plainTextEdit = new QPlainTextEdit(game);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(30, 30, 331, 101));
        QFont font2;
        font2.setPointSize(30);
        font2.setBold(true);
        plainTextEdit->setFont(font2);

        retranslateUi(game);

        QMetaObject::connectSlotsByName(game);
    } // setupUi

    void retranslateUi(QDialog *game)
    {
        game->setWindowTitle(QCoreApplication::translate("game", "Dialog", nullptr));
        pbRock->setText(QCoreApplication::translate("game", "\320\232\320\260\320\274\320\265\320\275\321\214", nullptr));
        pbScissors->setText(QCoreApplication::translate("game", "\320\235\320\276\320\266\320\275\320\270\321\206\321\213", nullptr));
        pbPaper->setText(QCoreApplication::translate("game", "\320\221\321\203\320\274\320\260\320\263\320\260", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class game: public Ui_game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_H
