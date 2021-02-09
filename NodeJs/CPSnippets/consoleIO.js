/*
Method 1 on based on addListener and not setting the encoding stream.
*/

const stdin = process.openStdin();
let content = '';

stdin.addListener('data', d => {
    let input = d.toString().trim();
    console.log("Data entered is ", input);
    // We need an extra \r when doing this on windows for linux \n should.
    // Or we could trim the string liek at line 9 and not use \r like line 13.
    if (input == "end\n"){
        console.log("End called exiting");
        process.exit();
    }else{
      console.log("User input data : " + input);
    }
});

//=============================================================================================================================
/*
Method 2 whcih uses event handler on 
*/

// var standard_input = process.stdin;
// standard_input.setEncoding('utf-8'); // We won't need to convert it to string when we receive 

// // Called when user enter something in console and presses enter key.
// standard_input.on('data', function (data) {
//     let parsedData = data;
//     // User input exit.
//     if(parsedData == 'exit\r\n'){
//         // Program exit.
//         console.log("User input complete, program exit.");
//         process.exit();
//     }else
//     {
//         // Print user input in console.
//         console.log('User Input Data : ' + parsedData);
//     }
// });