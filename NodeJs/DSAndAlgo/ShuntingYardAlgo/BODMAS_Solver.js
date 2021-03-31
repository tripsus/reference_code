var equation = '2*3+4/4';
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
            poppedElement = this.data.pop();
            this.currentIndex--;
        }
        return poppedElement;
    };
    Stack.prototype.isEmpty = function () {
        return (this.currentIndex === -1) ? true : false;
    };
    return Stack;
}());
function evaluteExpression(expression) {
    var tokenStack = new Stack(3);
    console.log(tokenStack.push(4));
    tokenStack.push(3);
    tokenStack.push(1);
    console.log(tokenStack.push(8));
    console.log(tokenStack.pop());
    console.log(tokenStack.pop());
    console.log(tokenStack.pop());
    console.log(tokenStack.isEmpty());
    console.log(tokenStack.pop());
}
evaluteExpression(equation);
