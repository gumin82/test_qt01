# test_qt01

## Qt Calculator Application

A simple calculator application built with Qt framework without using .ui files. The entire UI is created programmatically.

### Features

- **Floating-point arithmetic**: Supports decimal numbers
- **Basic operations**: Addition (+), Subtraction (-), Multiplication (×), Division (÷)
- **Backspace functionality**: Use the "<-" button to delete the last digit
- **Clear function**: Press "C" to reset the calculator
- **Error handling**: Division by zero shows "Error" message
- **Chain operations**: Perform multiple operations in sequence

### Button Layout

```
Display: [______________]
Row 1:   [7] [4] [1] [0]
Row 2:   [8] [5] [2] [.]
Row 3:   [9] [6] [3] [<-]
Row 4:   [+] [-] [×] [÷]
Row 5:   [  C  ] [  =  ]
```

### Building the Project

1. Install Qt development tools (Qt5 or Qt6)
2. Navigate to the project directory
3. Build using qmake:
   ```bash
   qmake test_qt01.pro
   make
   ```
   Or using QtCreator:
   - Open `test_qt01.pro` in QtCreator
   - Build and run the project

### Usage

1. Click number buttons to enter numbers
2. Click "." to add a decimal point
3. Click an operation button (+, -, ×, ÷) to select an operation
4. Enter the second number
5. Click "=" to see the result
6. Use "<-" to delete the last digit
7. Use "C" to clear and start over

### Implementation Details

The calculator is implemented without using Qt Designer (.ui files). All UI elements are created programmatically using:
- `QLineEdit` for the display
- `QPushButton` for buttons
- `QGridLayout` for layout management

The number buttons are arranged in a non-standard layout as requested, demonstrating flexibility in UI design.