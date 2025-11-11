#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , waitingForOperand(true)
{
    setWindowTitle("Calculator");
    createUI();
    resize(300, 400);
}

Widget::~Widget()
{
}

void Widget::createUI()
{
    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);
    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);
    
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(display, 0, 0, 1, 4);
    
    // Number buttons - arranged in a non-standard layout as requested
    mainLayout->addWidget(createButton("1", SLOT(digitClicked())), 1, 0);
    mainLayout->addWidget(createButton("2", SLOT(digitClicked())), 1, 1);
    mainLayout->addWidget(createButton("3", SLOT(digitClicked())), 1, 2);
    mainLayout->addWidget(createButton("0", SLOT(digitClicked())), 1, 3);
    
    mainLayout->addWidget(createButton("4", SLOT(digitClicked())), 2, 0);
    mainLayout->addWidget(createButton("5", SLOT(digitClicked())), 2, 1);
    mainLayout->addWidget(createButton("6", SLOT(digitClicked())), 2, 2);
    mainLayout->addWidget(createButton(".", SLOT(decimalClicked())), 2, 3);
    
    mainLayout->addWidget(createButton("7", SLOT(digitClicked())), 3, 0);
    mainLayout->addWidget(createButton("8", SLOT(digitClicked())), 3, 1);
    mainLayout->addWidget(createButton("9", SLOT(digitClicked())), 3, 2);
    mainLayout->addWidget(createButton("<-", SLOT(backspaceClicked())), 3, 3);
    
    // Operation buttons
    mainLayout->addWidget(createButton("+", SLOT(operatorClicked())), 4, 0);
    mainLayout->addWidget(createButton("-", SLOT(operatorClicked())), 4, 1);
    mainLayout->addWidget(createButton("×", SLOT(operatorClicked())), 4, 2);
    mainLayout->addWidget(createButton("÷", SLOT(operatorClicked())), 4, 3);
    
    // Control buttons
    mainLayout->addWidget(createButton("C", SLOT(clearClicked())), 5, 0, 1, 2);
    mainLayout->addWidget(createButton("=", SLOT(equalClicked())), 5, 2, 1, 2);
    
    setLayout(mainLayout);
}

QPushButton* Widget::createButton(const QString &text, const char* slot)
{
    QPushButton *button = new QPushButton(text);
    button->setMinimumSize(60, 60);
    QFont font = button->font();
    font.setPointSize(font.pointSize() + 4);
    button->setFont(font);
    connect(button, SIGNAL(clicked()), this, slot);
    return button;
}

void Widget::digitClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString digit = button->text();
    
    if (waitingForOperand) {
        currentNumber = digit;
        waitingForOperand = false;
    } else {
        if (currentNumber == "0") {
            currentNumber = digit;
        } else {
            currentNumber += digit;
        }
    }
    display->setText(currentNumber);
}

void Widget::decimalClicked()
{
    if (waitingForOperand) {
        currentNumber = "0.";
        waitingForOperand = false;
    } else {
        if (!currentNumber.contains(".")) {
            currentNumber += ".";
        }
    }
    display->setText(currentNumber);
}

void Widget::operatorClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString op = button->text();
    
    if (!waitingForOperand && !currentOperator.isEmpty()) {
        equalClicked();
    }
    
    operand1 = currentNumber;
    currentOperator = op;
    waitingForOperand = true;
}

void Widget::equalClicked()
{
    if (currentOperator.isEmpty() || waitingForOperand) {
        return;
    }
    
    double operand1Value = operand1.toDouble();
    double operand2Value = currentNumber.toDouble();
    double result = 0.0;
    
    if (currentOperator == "+") {
        result = operand1Value + operand2Value;
    } else if (currentOperator == "-") {
        result = operand1Value - operand2Value;
    } else if (currentOperator == "×") {
        result = operand1Value * operand2Value;
    } else if (currentOperator == "÷") {
        if (operand2Value != 0.0) {
            result = operand1Value / operand2Value;
        } else {
            display->setText("Error");
            currentNumber = "0";
            currentOperator.clear();
            waitingForOperand = true;
            return;
        }
    }
    
    currentNumber = QString::number(result);
    display->setText(currentNumber);
    currentOperator.clear();
    waitingForOperand = true;
}

void Widget::clearClicked()
{
    currentNumber = "0";
    operand1.clear();
    currentOperator.clear();
    waitingForOperand = true;
    display->setText("0");
}

void Widget::backspaceClicked()
{
    if (!waitingForOperand && currentNumber.length() > 1) {
        currentNumber.chop(1);
        display->setText(currentNumber);
    } else if (!waitingForOperand) {
        currentNumber = "0";
        display->setText("0");
        waitingForOperand = true;
    }
}
