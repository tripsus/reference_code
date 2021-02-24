type NodeValues = LLNode | null;
class LLNode{
    value: number;
    next: NodeValues;
    constructor(value:number){
        this.value = value;
        this.next = null;
    }
}

function main(){
    let input = [1,2, 3, 4];
    let head: NodeValues = null;
    let i=0;
    for(i=0; i<input.length; i++){
        if(head === null){
            head = new LLNode(input[i]);
        }else{
            let newNode = new LLNode(input[i]);
            let lastNode = head;
            while(lastNode.next != null){
                lastNode = lastNode.next;
            }
            lastNode.next = newNode;
        }
    }

    let llParser = head;
    while(llParser?.next != null){
        console.log(llParser.value);
        llParser = llParser.next;
    }
    

}

main();