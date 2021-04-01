# Stack
    An abstract data type that serves as a collection of elements, with two main principal operations:
        1. Push, which adds an element to the collection, and
        2. Pop, which removes the most recently added element that was not yet removed.
    
    The order in which elements come off a stack gives rise to its alternative name, LIFO (last in, first out).

### Implementing a Stack
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

# Queue
    A collection of entities that are maintained in a sequence and can be modified by the addition of entities at one end of the sequence and the removal of entities from the other end of the sequence. There are two principal operations on a queue.
    1. Enqueue: Addition of entities at one end of queue.
    2. Dqueue: Removal of entities from other end of queue.
    
    The operations of a queue make it a first-in-first-out (FIFO) data structure. In a FIFO data structure, the first element added to the queue will be the first one to be removed

### Implementing a Queue
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
# Shunting Yard Algorithm
Shunting yard Algorithm is a method of parsing mathematical expression in Infix notation and generating a reverse polish notation(aka Postfix notation). Which later used to evaluate the expression.

## Operator Precedence
| **Operator**  | **Precedence**    |
| -------------- |:-------------:|
| /          | 4 |
| *          | 3 |
| +          | 2 |
| -          | 1 |

### Implementing Operator precedence
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
### Algorithm
    while there are tokens to be read:
        read a token.
        if the token is a number, then:
            push it to the output queue. 
        else if the token is an operator then:
            if there is an operator at top of stack:
                while ((there is an operator at the top of the operator stack)
                    and ((the operator at the top of the operator stack has greater precedence)):
                    pop operators from the operator stack onto the output queue.
                push it onto the operator stack.
            else:
                push it onto the operator stack
        else if the token is a parenthesis then:
            if parenthesis is left parenthesis (i.e. "("), then
                push it onto the operator stack.
            else if the token is a right parenthesis (i.e. ")"), then:
                while the operator at the top of the operator stack is not a left parenthesis:
                    pop the operator from the operator stack onto the output queue.
                    /* If the stack runs out without finding a left parenthesis, then there are mismatched parentheses. */
                if there is a left parenthesis at the top of the operator stack, then:
                    pop the operator from the operator stack and discard it
        
    /* After while loop, if operator stack not null, pop everything to output queue */
    if there are no more tokens to read then:
        while there are still operator tokens on the stack:
            /* If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses. */
            pop the operator from the operator stack onto the output queue.
    exit.
## Detailed Example
> Input: **`3 + 4 / 2 * ( 1 − 5 )`**

| **Token**         | **Action**    | **Output in RPN** | **Operator Stack**  | **Notes** |
| ----------------- |:-------------:| -----------------:|--------------------:|----------:|
| 3          | Add token to output | 3 |
| +          | Push token to stack      |   3 | +
| 4     | Add token to output      |    3 4 | + |
| / | Push token to stack | 3 4 | / + | * has higher precedence than +|
| 2 | Push token to output | 3 4 2 | / + |
| * | Pop stack to output | 3 4 2  /|  + | * has lower precedence than /|
| * | Push token to stack | 3 4 2 /| * + | * has higher precedence than +|
| ( | Push token to stack | 3 4 2 /| ( * + | |
| 1 | Add token to output | 3 4 2 / 1|( * + | |
| - | Push token to stack | 3 4 2 / 1| - ( * + | |
| 5 | Add token to output | 3 4 2 / 1 5|( * + | |
| ) | Pop token to output | 3 4 2 / 1 5 -|( * + |Repeat until ( is found|
| ) | Pop stack | 3 4 2 / 1 5 -|( * + |( found discard matching parenthesis|
| | Pop entire stack to output | 3 4 2 / 1 5 - * + ||
| |

> Final RPN: **3 4 2 / 1 5 - * +**

### Implementing Shunting Yard
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

    // Shunting Yard implementation
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
## Evaluating RPN
### Algorithm
     Start with an empty stack.  We scan input from left to right.

     While (we have not reached the end of P)
        If an operand is found
           push it onto the stack
        End-If
        If an operator is found
           Pop the stack and call the value A
           Pop the stack and call the value B
           Evaluate B op A using the operator just found.
           Push the resulting value onto the stack
        End-If
    End-While
    Pop the stack (this is the final value)

> Input: **3 4 2 / 1 5 - * +**

| **Token**         | **Action**    | **Stack** | **Notes** |
| ----------------- |:-------------:| -----------------:|-----------:|
| 3          | Push token to stack | 3 |
| 4          | Push token to stack |4 3 |
| 2          | Push token to stack |2 4 3 |
| /          | Pop first token from stack | 4 3 | 2 popped from stack|
| /          | Pop second token from stack | 3 | 2 & 4 popped from stack|
| /          | Preform 2nd OP 1st | 3 | 4/2 = 2|
| /          | push result back to stack  | 2 3 | |
| 1          | Push token to stack | 1 2 3 | |
| 5          | Push token to stack | 5 1 2 3 | |
| -          | Pop first token from stack | 1 2 3 | 5 popped from stack|
| -          | Pop second token from stack | 2 3 | 5 and 1 popped from stack|
| -          | Preform 2nd OP 1st | 2 3 | 1-5 = -4|
| -          | Push result back to stack | -4 2 3 | |
| *          | Pop first token from stack | -4 2 3 | -4 popped from stack|
| *          | Pop second token from stack | 3 | -4 and 2 popped from stack|
| *          | Preform 2nd OP 1st | 3 | 2 * -4 = -8|
| *          | Push result back to stack | -8 3 | |
| +          | Pop first token from stack | 3 | -8 popped from stack|
| +          | Pop second token from stack |  | -8 and 3 popped from stack|
| +          | Preform 2nd OP 1st | 3 | 3 + -8 = -5|
| +          | Push result back to stack | -5 | |
|           | Token empty pop the stack | -5 | |
| |

### Implementation of RPN evaluation
    // Helper method to evalues two tokens and give an output
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

