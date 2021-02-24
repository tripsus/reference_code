// https://www.hackerearth.com/practice/basic-programming/input-output/basics-of-input-output/practice-problems/algorithm/mojtaba-prepares-contest-29b2a044/description/


// Sample code to perform I/O:

process.stdin.resume();
process.stdin.setEncoding("utf-8");
var stdin_input = "";

process.stdin.on("data", function (input) {
    stdin_input += input;                               // Reading input from STDIN
});

process.stdin.on("end", function () {
   main(stdin_input);
});

function getSolutionStatus(input_tokens, participantsCount, delta){
    let solutionStatus = [];
    //console.log(delta);
    //console.log(input_tokens);
    let i = delta + 3;
    for(i = delta + 3; i < (delta+ 3 + participantsCount) ; i++){
        firstStatus = parseInt(input_tokens[i].split(" ")[0]);
        secondStatus = parseInt(input_tokens[i].split(" ")[1]);
        solutionStatus.push([firstStatus, secondStatus]);
    }
    return solutionStatus;

}
function main(input) {
    input_tokens = input.split('\n');
    //console.log(input_tokens);
    let testCases = parseInt(input_tokens[0]);

    
    let currentTestCase = 0;
    while(currentTestCase < testCases){
        let delta = currentTestCase*12;
        let greenBalloonCost = input_tokens[delta+1].split(" ")[0];
        let purpleBalloonCost = parseInt(input_tokens[delta+1].split(" ")[1]);
        let cheap = greenBalloonCost > purpleBalloonCost ? purpleBalloonCost : greenBalloonCost;
        let costly = greenBalloonCost < purpleBalloonCost ? purpleBalloonCost : greenBalloonCost;  
        let numberOfParticipants = parseInt(input_tokens[delta+2]);
        let solutionStatus = getSolutionStatus(input_tokens, numberOfParticipants, delta);
        //console.log(solutionStatus);
        let firstSolveCount = solutionStatus.reduce((prev, cur) => {
            return parseInt(prev) + parseInt(cur[0]);
        }, 0);
        let secondSolveCount = solutionStatus.reduce((prev, cur) => {
            return parseInt(prev) + parseInt(cur[1]);
        }, 0);
        //console.log(secondSolveCount);
        let sum = 0;
        if(firstSolveCount < secondSolveCount){
            
            sum = firstSolveCount*costly + secondSolveCount*cheap;
        }else{
            sum = secondSolveCount*costly + firstSolveCount*cheap;
        }
        console.log(sum);
        currentTestCase++;
    }
}

