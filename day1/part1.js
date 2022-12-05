// ------------------------
// Codeabschnitt, der für die Verarbeitung der Eingabe zuständig ist
'use strict';

process.stdin.resume();
process.stdin.setEncoding('utf-8');

let inputString = '';
let currentLine = 0;

process.stdin.on('data', inputStdin => {
    inputString += inputStdin;
});

process.stdin.on('end', _ => {
    inputString = inputString.trim().split('\n').map(string => {
        return string.trim();
    });
    
    main();    
});

function readline() {
    return inputString[currentLine++];
}

const print = console.log

// ---------------------------

/**
 * Usage (Linux/Unix): cat input.txt | node index.js 
 */
let arr
let len
function main() {
    let str = readline()
    let maxSum = 0

    let tempSum = 0

    while(str != undefined){
        if(str == ""){
            if(maxSum < tempSum){
                maxSum = tempSum
            }
            tempSum = 0
        } else {
            tempSum += +str
        }
        
        str = readline()
    }

    print(maxSum)
}