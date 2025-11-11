#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QString>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void digitClicked();
    void operatorClicked();
    void equalClicked();
    void clearClicked();
    void backspaceClicked();
    void decimalClicked();

private:
    void createUI();
    QPushButton* createButton(const QString &text, const char* slot);
    
    QLineEdit *display;
    QString currentNumber;
    QString operand1;
    QString currentOperator;
    bool waitingForOperand;
};
#endif // WIDGET_H
