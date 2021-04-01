// Shuting Yard Algorithm
class Queue<T> {
    private data: Array<T>;
    private size: number;
    private front: number;
    private rear: number;

    constructor(size:number){
        this.size = size;
        this.data = new Array<T>(size);
        this.front = -1;
        this.rear = -1;
    }

    isEmpty(): boolean{
        let result:boolean = false;
    
        if (this.front === this.rear){
            result = true;
        }
        return result;
    }

    isFull(): boolean{
        if((this.rear === (this.size) || this.rear + 1 === this.front))
            return true;

        return false;
    }

    enqueue(param:T): boolean {
        let success:boolean = false;
        if(!this.isFull()){
            this.rear = (this.rear + 1) % this.size;
            this.data[this.rear] = param;
        }
        return success;
    }

    dequeue(): T{
        let value:T = null;
        if(!this.isEmpty()){
            this.front = (this.front + 1) % this.size;
            value = this.data[this.front];
            this.data[this.front] = null; 
        }
        return value;
    }
}

class Stack<T> {
    private data: Array<T>;
    private size: number;
    private currentIndex: number;

    constructor(size: number){
        this.size = size;
        this.data = new Array<T>(size);
        this.currentIndex = -1;
    };

    push(params:T): boolean {
        let succeeded = false;
        if (this.currentIndex < (this.size -1)){
            this.currentIndex++;
            this.data[this.currentIndex] = params;
            succeeded = true;
        }
        return succeeded;
    }

    pop(): T{
        let poppedElement:T = null;
        if(!this.isEmpty()){
            poppedElement = this.data[this.currentIndex];
            this.data[this.currentIndex] = null;
            this.currentIndex--;
        }
        return poppedElement;
    }

    topOfStack(): T{
        let poppedElement:T = null;
        if(!this.isEmpty()){
            poppedElement = this.data[this.currentIndex];
        }
        return poppedElement;
    }

    isEmpty(): boolean{
        return (this.currentIndex === -1) ? true:false;
    }
}
enum TokenType{
    Number,    // Number like 1,2,3
    Operator,   // e.g. +, -, *. /
    Parenthesis, // (, )
    Unknown     // God knows what this is :D
};

// Helper method to check if a token is number
function isNumber(token:string): boolean{
    return !isNaN(Number(token));
}

// Helper method to get what kind of token we are parsing.
function getTokenType(token: string): TokenType{
    if(token === '(' || token === ')'){
        return TokenType.Parenthesis;
    }else if(token === '/' || token === '*' || token === '+' ||token === '-'){
        return TokenType.Operator;
    }else if(isNumber(token)){
        return TokenType.Number
    }else{
        return TokenType.Unknown;
    }
}

// Helper method to get priority of tokens
function getPriority(operator: string): number{
    if (operator === '/'){
        return 4;
    }else if(operator === '*'){
        return 3;
    }else if(operator === '+'){
        return 2;
    }else{
        return 1;
    }
}

function generatePostFix(expression: string): string{
    let tokenQueue = new Queue<string>(expression.length);
    let operatorStack = new Stack<string>(expression.length);
    let postFixExpression:string = '';
    let errorEncountered = false;

    for(let i = 0; i < expression.length; i++){
        let token = expression[i];
        if (errorEncountered)
            break;

        let tokenType = getTokenType(token);
        
        if(tokenType === TokenType.Number){
            tokenQueue.enqueue(token);
        }else if(tokenType === TokenType.Operator){
            if(operatorStack.isEmpty()){
                operatorStack.push(token)
            }else{
                let tos = operatorStack.topOfStack();
                if (getTokenType(tos) === TokenType.Operator && getPriority(tos) > getPriority(token)){
                    while(getPriority(tos) > getPriority(token) && !operatorStack.isEmpty()){
                        let stackToken = operatorStack.pop();
                        if(stackToken){
                            tokenQueue.enqueue(stackToken)
                            tos = operatorStack.topOfStack();
                        }else{
                            console.error("Input is not correct");
                            errorEncountered = true;
                            break;
                        }
                        
                    }
                    operatorStack.push(token);
                }else{
                    operatorStack.push(token);
                }
            }
        }else if(tokenType === TokenType.Parenthesis){
            if (token === '('){
                operatorStack.push(token);
            }else{
                while(operatorStack.topOfStack() !== '('){
                    let stackToken = operatorStack.pop();
                    if(stackToken){
                        tokenQueue.enqueue(stackToken)
                    }else{
                        console.error("Input is not correct");
                        errorEncountered = true;
                        break;
                    }
                }
                operatorStack.pop(); // Pop the opening parenthesis from stack
            }
        }else{
            console.error("Unknown Character");
            errorEncountered = true;
            break;
        }
    }
    if (!errorEncountered){
        while(operatorStack.topOfStack()){
            if(operatorStack.topOfStack() === '('){
                console.error("Input is not correct");
                errorEncountered = true;
                break;
            }else{
                tokenQueue.enqueue(operatorStack.pop());
            }
        }
    }
    
    if(!errorEncountered){
        while(!tokenQueue.isEmpty()){
            postFixExpression += tokenQueue.dequeue();
        }
    }

    return postFixExpression;
}

function calculate(operation:string, aToken: string, bToken:string): number{
    let a = parseInt(aToken);
    let b = parseInt(bToken);
    if (operation === '/'){
        return b/a;
    }else if(operation === '*'){
        return b*a;
    }else if(operation === '+'){
        return b+a;
    }else{
        return b-a;
    }
}

function evaluateRPN(rpnExpression: string): number{
    let calculatedValue = 0;
    let numberStack = new Stack<string>(rpnExpression.length);

    for(let i = 0; i < rpnExpression.length; i++){
        let token = rpnExpression[i];
        if(isNumber(token)){
            numberStack.push(token);
        }else if(getTokenType(token) === TokenType.Operator){
            let aToken = numberStack.pop();
            let bToken = numberStack.pop();
            let result: number = calculate(token, aToken, bToken);
            numberStack.push(result.toString());
        }else{
            console.error("Shouldn't have reached here. Check your generatePostFix method for errors");
        }
    }
    return parseInt(numberStack.topOfStack());
}

function evaluteExpression(expression: string){
    let rpn = generatePostFix(expression);
    console.log(rpn);
    console.log("Calculated value for expression is");
    console.log(evaluateRPN(rpn));
}

// let equation = '3+4/2*(1−5)'
let equation = '3+4/2*(1-5)'
evaluteExpression(equation);