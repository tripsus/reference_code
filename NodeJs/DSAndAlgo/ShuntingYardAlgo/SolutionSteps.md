# Shunting Yard Algorithm
Shunting yard Algorithm is a method of parsing mathematical expression in Infix notation and generating a reverse polish notation(aka Postfix notation). Which later used to evaluate the expression.

## Operator Precedence
| **Operator**  | **Precedence**    |
| -------------- |:-------------:|
| /          | 4 |
| *          | 3 |
| +          | 2 |
| -          | 1 |

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

## Code
Implementing this solution requires having a stack and a queue as a data structure.

### Stack
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
                poppedElement = this.data.pop()
                this.currentIndex--;
            }
            return poppedElement;
        }

        isEmpty(): boolean{
            return (this.currentIndex === -1) ? true:false;
        }
    }

### Queue
    class Queue<T> {
        private data: Array<T>;
        private size: number;
        private front: number;
        private rear: number;

        constructor(size:number){
            this.size = size;
            this.data = new Array<T>(size);
            this.front = 0;
            this.rear = -1;
        }

        isEmpty(): boolean{
            let result:boolean = false;
        
            if (this.rear === -1 || this.front === this.rear){
                result = true;
            }
            return result;
        }

        isFull(): boolean{
            if((this.front === 0 && this.rear === this.size-1) || (this.rear + 1 == this.front))
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

        dequeue(param:T): T{
            let value:T = null;
            
            if(!this.isEmpty()){
                value = this.data[this.front]    
            }
            return value;
        }
    }

### Generating RPN(Reverse Polish notation)
    
