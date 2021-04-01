// Shuting Yard Algorithm
var Queue = /** @class */ (function () {
    function Queue(size) {
        this.size = size;
        this.data = new Array(size);
        this.front = -1;
        this.rear = -1;
    }
    Queue.prototype.isEmpty = function () {
        var result = false;
        if (this.front === this.rear) {
            result = true;
        }
        return result;
    };
    Queue.prototype.isFull = function () {
        if ((this.rear === (this.size) || this.rear + 1 === this.front))
            return true;
        return false;
    };
    Queue.prototype.enqueue = function (param) {
        var success = false;
        if (!this.isFull()) {
            this.rear = (this.rear + 1) % this.size;
            this.data[this.rear] = param;
        }
        return success;
    };
    Queue.prototype.dequeue = function () {
        var value = null;
        if (!this.isEmpty()) {
            this.front = (this.front + 1) % this.size;
            value = this.data[this.front];
            this.data[this.front] = null;
        }
        return value;
    };
    return Queue;
}());
var Stack = /** @class */ (function () {
    function Stack(size) {
        this.size = size;
        this.data = new Array(size);
        this.currentIndex = -1;
    }
    ;
    Stack.prototype.push = function (params) {
        var succeeded = false;
        if (this.currentIndex < (this.size - 1)) {
            this.currentIndex++;
            this.data[this.currentIndex] = params;
            succeeded = true;
        }
        return succeeded;
    };
    Stack.prototype.pop = function () {
        var poppedElement = null;
        if (!this.isEmpty()) {
            poppedElement = this.data[this.currentIndex];
            this.data[this.currentIndex] = null;
            this.currentIndex--;
        }
        return poppedElement;
    };
    Stack.prototype.topOfStack = function () {
        var poppedElement = null;
        if (!this.isEmpty()) {
            poppedElement = this.data[this.currentIndex];
        }
        return poppedElement;
    };
    Stack.prototype.isEmpty = function () {
        return (this.currentIndex === -1) ? true : false;
    };
    return Stack;
}());
var TokenType;
(function (TokenType) {
    TokenType[TokenType["Operand"] = 0] = "Operand";
    TokenType[TokenType["Operator"] = 1] = "Operator";
    TokenType[TokenType["Parenthesis"] = 2] = "Parenthesis";
    TokenType[TokenType["Unknown"] = 3] = "Unknown";
})(TokenType || (TokenType = {}));
;
function getTokenType(token) {
    if (token === '(' || token === ')') {
        return TokenType.Parenthesis;
    }
    else if (token === '/' || token === '*' || token === '+' || token === '-') {
        return TokenType.Operator;
    }
    else if (!isNaN(Number(token))) {
        return TokenType.Operand;
    }
    else {
        return TokenType.Unknown;
    }
}
function getPriority(operator) {
    if (operator === '/') {
        return 4;
    }
    else if (operator === '*') {
        return 3;
    }
    else if (operator === '+') {
        return 2;
    }
    else {
        return 1;
    }
}
function generatePostFix(expression) {
    var tokenQueue = new Queue(expression.length);
    var operatorStack = new Stack(expression.length);
    var postFixExpression = '';
    var errorEncountered = false;
    for (var i = 0; i < expression.length; i++) {
        var token = expression[i];
        if (errorEncountered)
            break;
        var tokenType = getTokenType(token);
        if (tokenType === TokenType.Operand) {
            tokenQueue.enqueue(token);
        }
        else if (tokenType === TokenType.Operator) {
            if (operatorStack.isEmpty()) {
                operatorStack.push(token);
            }
            else {
                var tos = operatorStack.topOfStack();
                if (getTokenType(tos) === TokenType.Operator && getPriority(tos) > getPriority(token)) {
                    while (getPriority(tos) > getPriority(token) && !operatorStack.isEmpty()) {
                        var stackToken = operatorStack.pop();
                        if (stackToken) {
                            tokenQueue.enqueue(stackToken);
                            tos = operatorStack.topOfStack();
                        }
                        else {
                            console.error("Input is not correct");
                            errorEncountered = true;
                            break;
                        }
                    }
                    operatorStack.push(token);
                }
                else {
                    operatorStack.push(token);
                }
            }
        }
        else if (tokenType === TokenType.Parenthesis) {
            if (token === '(') {
                operatorStack.push(token);
            }
            else {
                while (operatorStack.topOfStack() !== '(') {
                    var stackToken = operatorStack.pop();
                    if (stackToken) {
                        tokenQueue.enqueue(stackToken);
                    }
                    else {
                        console.error("Input is not correct");
                        errorEncountered = true;
                        break;
                    }
                }
                operatorStack.pop(); // Pop the opening parenthesis from stack
            }
        }
        else {
            console.error("Unknown Character");
            errorEncountered = true;
            break;
        }
    }
    if (!errorEncountered) {
        while (operatorStack.topOfStack()) {
            tokenQueue.enqueue(operatorStack.pop());
        }
        while (!tokenQueue.isEmpty()) {
            postFixExpression += tokenQueue.dequeue();
        }
    }
    return postFixExpression;
}
function evaluteExpression(expression) {
    var rpn = generatePostFix(expression);
    console.log(rpn);
}
// let equation = '3+4/2*(1−5)'
var equation = '3+4/2*(1-5)';
evaluteExpression(equation);
//# sourceMappingURL=BODMAS_Solver.js.map