// Shuting Yard Algorithm
let equation = '2*3+4/4'
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

function evaluteExpression(expression: string){
    let tokenStack = new Stack<number>(3);
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