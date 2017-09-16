var rNA = new Array();
var value = 0;

function createRandomArray() {
    for (i = 0; i < 10000; i++) {
        rNA.push(Math.floor(Math.random() * 10));
    }
}

function getValueFromUser() {
    value = prompt("Please enter a value", "");
}

function determineFreq() {
    var count = 0;
    for (i = 0; i < rNA.length; i++) {
        if (rNA[i] == value) {
            count++;
        }
    }

    document.getElementById("count").innerHTML = count;
}
