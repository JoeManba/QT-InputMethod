#ifndef DIALOG_H
#define DIALOG_H
#include <QApplication>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <softkeyboard.h>
#include <QEvent>
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

    QLineEdit *lineEdit;
    bool eventFilter (QObject *watched, QEvent *event);
    void showKeyboard();

    SoftKeyboard *keyboard ;//软键盘
};

#endif // DIALOG_H
