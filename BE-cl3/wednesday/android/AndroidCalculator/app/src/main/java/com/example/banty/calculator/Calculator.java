package com.example.banty.calculator;

/**
 * Created by Banty on 16-02-2016.
 */
public class Calculator {
    private double operand;
    private double waitingOperand;
    private String waitingOperator;
    private double calculatorMemory;


    public Calculator() {
        // initialize variables upon start
        operand = 0;
        waitingOperand = 0;
        waitingOperator = "";
        calculatorMemory = 0;
    }

    public void setOperand(double newOperand) {
        operand = newOperand;
    }

    public double getResult() {
        return operand;
    }

    // used on screen orientation change
    public void setMemory(double newCalculatorMemory) {
        calculatorMemory = newCalculatorMemory;
    }

    // used on screen orientation change
    public double getMemory() {
        return calculatorMemory;
    }

    public String toString() {
        return Double.toString(operand);
    }

    protected double performOperation(String operator) {
        if (operator.equals("C")) {
            operand = 0;
            waitingOperator = "";
            waitingOperand = 0;
        } else if (operator.equals("MC")) {
            calculatorMemory = 0;
        } else if (operator.equals("M+")) {
            calculatorMemory = calculatorMemory + operand;
        } else if (operator.equals("M-")) {
            calculatorMemory = calculatorMemory - operand;
        } else if (operator.equals("MR")) {
            operand = calculatorMemory;
        } else if (operator.equals("√")) {
            // ALT + keypad(251)
            operand = Math.sqrt(operand);
        } else if (operator.equals("x²")) {
            // x + (ALT + 0178)
            operand = operand * operand;
        } else if (operator.equals("1/x")) {
            operand = 1 / operand;
        } else if (operator.equals("+/-")) {
            operand = -1 * operand;
        } else if (operator.equals("sin")) {
            operand = Math.sin(Math.toRadians(operand));
        } else if (operator.equals("cos")) {
            operand = Math.cos(Math.toRadians(operand));
        } else if (operator.equals("tan")) {
            operand = Math.tan(Math.toRadians(operand));
        } else {
            performWaitingOperation();
            waitingOperator = operator;
            waitingOperand = operand;
        }
        return operand;
    }

    private void performWaitingOperation() {
        if (waitingOperator.equals("+")) {
            operand = waitingOperand + operand;
        } else if (waitingOperator.equals("-")) {
            operand = waitingOperand - operand;
        } else if (waitingOperator.equals("*")) {
            operand = waitingOperand * operand;
        } else if (waitingOperator.equals("/")) {
            if (operand != 0) {
                operand = waitingOperand / operand;
            }
        }
    }
}
