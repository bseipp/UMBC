// JavaScript source code
const TEACHER_PASSWORD = "time2teach"
var studentResults = [];
var currentPlayer
var name;
var password;
var level2Unlocked;
var level3Unlocked;
var level4Unlocked;
var optionsAvailable;
var nowTime;
var stopTime;

/************************************************
*        CODE TO GENERATE WEBPAGES              *
************************************************/

function generateLevel1() {
    var level1 = "";
    currentPlayer.questionOneStartTime = new Date();

    level1 += "<div id=\"quit\">";
    level1 += "<button onclick=\"generateQuitConfirmPage()\" class=\"dropbtn\" >Quit?</button>";
    level1 += "</div>";
    level1 += "<div id=\"L1Holder\">";
    level1 += "<div class=\"dropdown\" id=\"l1AnswerEntries\">";
    level1 += "<div id=\"questionText\">";
    level1 += "Match the letters to the hands of the clock! <br />";
    level1 += "</div>";
    level1 += "<div id=\"imageL1\">";
    level1 += "<img src=\"Level1.png\" alt=\"Identify the hand\" >";
    level1 += "</div>";
    level1 += "<div class=\"L1AnswerHolder\" id=\"hourHandAnswer\">";
    level1 += "Hour Hand - ";
    level1 += "<button onclick=\"createOptions('L1A1')\" class=\"dropbtn\" id=\"L1A1Button\">No Answer</button>";
    level1 += "<div id=\"L1A1\" class=\"dropdown-content\"></div >";
    level1 += "</div>";
    level1 += "<div class=\"L1AnswerHolder\" id=\"minuteHandAnswer\">";
    level1 += "Minute Hand - ";
    level1 += "<button onclick=\"createOptions('L1A2')\" class=\"dropbtn\" id=\"L1A2Button\">No Answer</button>";
    level1 += "<div id=\"L1A2\" class=\"dropdown-content\"></div>";
    level1 += "</div>";
    level1 += "<div class=\"L1AnswerHolder\" id=\"secondHandAnswer\">";
    level1 += "Second Hand - ";
    level1 += "<button onclick=\"createOptions('L1A3')\" class=\"dropbtn\" id=\"L1A3Button\">No Answer</button>";
    level1 += "<div id=\"L1A3\" class=\"dropdown-content\"></div>";
    level1 += "</div>";
    level1 += "</div>";
    level1 += "<div id=\"checkResultsL1\">";
    level1 += "<button onclick=\"checkL1()\" class=\"dropbtn\" id=\"L1Check\">Check Answers!</button>";
    level1 += "</div>";
    level1 += "</div>";

    document.getElementById("content").innerHTML = level1;

    drawOptions("L1A1");
    drawOptions("L1A2");
    drawOptions("L1A3");
}

function generateLevel2() {
    var level2 = "";
    currentPlayer.questionTwoStartTime = new Date();
    level2 += "<div id=\"quit\">";
    level2 += "<button class=\"dropbtn\" onclick=\"generateQuitConfirmPage()\">Quit?</button>";
    level2 += "</div>";
    level2 += "<div class=\"contentBox\" id=\"clockHolder\">";
    level2 += "<div class=\"contentBox\" id=\"L2A1Holder\">";
    level2 += "<canvas id=\"clock11\" width=\"200\" height=\"200\"></canvas><br>";
    level2 += "Enter the hour! <input class=\"inputBox\" type=\"text\" id=\"L2A1\"><br>";
    level2 += "<div id=\"L2A1CheckHolder\">";
    level2 += "</div>";
    level2 += "</div>";
    level2 += "<div class=\"contentBox\" id=\"L2A2Holder\">";
    level2 += "<canvas id=\"clock12\" width=\"200\" height=\"200\"></canvas><br>";
    level2 += "Enter the minutes! <input class=\"inputBox\" type=\"text\" id=\"L2A2\"><br>";
    level2 += "<div id=\"L2A2CheckHolder\">";
    level2 += "</div>";
    level2 += "</div>";
    level2 += "<div class=\"contentBox\" id=\"L2A3Holder\">";
    level2 += "<canvas id=\"clock13\" width=\"200\" height=\"200\"></canvas><br>";
    level2 += "Enter the seconds! <input class=\"inputBox\" type=\"text\" id=\"L2A3\"><br>";
    level2 += "<div id=\"L2A3CheckHolder\">";
    level2 += "</div>";
    level2 += "</div>";
    level2 += "</div>";

    document.getElementById("content").innerHTML = level2;

    addCheckAnswerButton("L2A1CheckHolder", "L2A1");
    addCheckAnswerButton("L2A2CheckHolder", "L2A2");
    addCheckAnswerButton("L2A3CheckHolder", "L2A3");

    drawStationaryClock("clock11", new Date("October 13, 2014 10:13:00"));
    drawStationaryClock("clock12", new Date("October 13, 2014 11:30:00"));
    drawStationaryClock("clock13", new Date("October 13, 2014 01:56:45"));
}

function generateLevel3() {
    var level3 = "";
    nowTime = new Date();
    stopTime = new Date(nowTime.getTime() + 10000);
    var stopTimeString = stopTime.toTimeString().slice(0, 8);

    level3 += "<div id=\"quit\">";
    level3 += "<button onclick=\"generateQuitConfirmPage()\" class=\"dropbtn\" >Quit?</button>";
    level3 += "</div>";
    level3 += "<div id=\"L3Holder\">";
    level3 +=   "<div id=\"L3questionText\">";
    level3 +=       "Press the button when the time reads <b>" + stopTimeString + "</b>!";
    level3 +=   "</div>";
    level3 +=   "<div id=\"tryAgainText\"></div>";
    level3 +=   "<div id=\"L3ClockHolder\">";
    level3 +=       "<div id=\"spacerDiv\"></div>";
    level3 +=       "<canvas id=\"canvas\" width=\"400\" height=\"400\"></canvas>";
    level3 +=   "</div>";
    level3 += "</div>";
    level3 += "<div id=\"checkResultsL3\">";
    level3 +=   "<button onclick=\"checkL3()\" class=\"dropbtn\" id=\"L3Check\">Go!</button>";
    level3 += "</div>";
    
    document.getElementById("content").innerHTML = level3;

    drawMovingClock();

}

function generateLevel4(){
    generateLevelCompletePage()
}  

function generateWelcomePage() {
    initializeVariables();

    var welcomePage = "";

    welcomePage += "<div id=\"login\">";
    welcomePage += "Password: <input type=\"password\" id=\"password\" class=\"inputBox\"><br><br />";
    welcomePage += "<button class=\"dropbtn\" onclick=\"validatePassword()\">Check results</button>";
    welcomePage += "</div>";
    welcomePage += "<div id=\"welcome\">";
    welcomePage += "<div class=\"title\">";
    welcomePage += "Welcome to the Time Game! <br><br>";
    welcomePage += "</div>";
    welcomePage += "Enter your First name: <input type=\"text\" class=\"inputBox\" id=\"studentFirstName\"><br>";
    welcomePage += "Enter your Last name: <input type=\"text\" class=\"inputBox\" id=\"studentLastName\"><br>";
    welcomePage += "<button class=\"dropbtn\" onclick=\"validateName()\">Lets Go!!</button>";
    welcomePage += "</div>";

    document.getElementById("content").innerHTML = welcomePage;
}

function generateGameBoard() {
    var gameBoard = "";

    gameBoard += "<div id=\"quit\">";
    gameBoard += "<button class=\"dropbtn\" onclick=\"generateQuitConfirmPage()\">Quit?</button>";
    gameBoard += "</div>";
    gameBoard += "<div id=\"game\">";
    gameBoard += "<div id=\"preGame\">";
    gameBoard += "<div class=\"title\" id=\"gameBoardLabel\">";
    gameBoard += "Welcome to the Time Board " + currentPlayer.name + "! <br /> <br />";
    gameBoard += "</div>";
    gameBoard += "<div id=\"instructions\">";
    gameBoard += "Go ahead and pick a level to play! <br /> ";
    gameBoard += "Once you've beaten a level, the next will unlock! <br /> ";
    gameBoard += "Good luck! <br />";
    gameBoard += "</div>";
    gameBoard += "</div>";
    gameBoard += "<div id=\"levels\">";
    gameBoard += "<div id=\"1\" >";
    gameBoard += "<button class=\"dropbtn\" id=\"lvl1\" onclick=\"generateLevel1()\">Level 1</button>";
    gameBoard += "</div>";
    gameBoard += "<div><br /></div>";
    gameBoard += "<div id=\"2\" >";
    gameBoard += "<button class=\"dropbtn\" id=\"lvl2\" onclick=\"generateLevel2()\" disabled=\"true\">Level 2</button>";
    gameBoard += "</div>";
    gameBoard += "<div><br /></div>";
    gameBoard += "<div id=\"3\" >";
    gameBoard += "<button class=\"dropbtn\" id=\"lvl3\" onclick=\"generateLevel3()\" disabled=\"true\">Level 3</button>";
    gameBoard += "</div>";
    gameBoard += "<div><br /></div>";
    gameBoard += "<div id=\"4\" >";
    gameBoard += "<button class=\"dropbtn\" id=\"lvl4\" onclick=\"generateLevel4()\" disabled=\"true\">Level 4</button><br><br><br>";
    gameBoard += "</div>";
    gameBoard += "</div>";
    gameBoard += "</div>";

    document.getElementById("content").innerHTML = gameBoard;

    if (level2Unlocked) {
        document.getElementById("lvl2").removeAttribute("disabled");
        document.getElementById("lvl1").setAttribute('disabled', true);
        document.getElementById("lvl1").textContent = "Level complete!";
    }
    if (level3Unlocked) {
        document.getElementById("lvl3").removeAttribute("disabled");
        document.getElementById("lvl2").setAttribute('disabled', true);
        document.getElementById("lvl2").textContent = "Level complete!";
    }
    if (level4Unlocked) {
        document.getElementById("lvl4").removeAttribute("disabled");
        document.getElementById("lvl3").setAttribute('disabled', true);
        document.getElementById("lvl3").textContent = "Level complete!";
    }
}

function generateResultTable() {
    var results = "";

    results += "<div id=\"quit\">";
    results += "<button class=\"dropbtn\" onclick=\"generateQuitConfirmPage()\">Quit?</button>";
    results += "</div>";
    results += "<div id=\"studentResults\">";
    results += "<table id=\"resultTable\">";
    results += "</table>";
    results += "</div>";

    document.getElementById("content").innerHTML = results;

    var table = document.getElementById("resultTable");

    var newRow = table.insertRow();
    var name = newRow.insertCell(0);
    var furthest = newRow.insertCell(1);
    var attemptQ1 = newRow.insertCell(2);
    var attemptQ2 = newRow.insertCell(3);
    var attemptQ3 = newRow.insertCell(4);
    var attemptQ4 = newRow.insertCell(5);
    var avgTime = newRow.insertCell(6);

    name.innerHTML = "Name";
    furthest.innerHTML = "Furthest Question Attempted";
    attemptQ1.innerHTML = "Attempts at question 1";
    attemptQ2.innerHTML = "Attempts at question 2";
    attemptQ3.innerHTML = "Attempts at question 3";
    attemptQ4.innerHTML = "Attempts at question 4";
    avgTime.innerHTML = "Average Time on questions";

    var sr = studentResults;
    var srLen = studentResults.length;

    for (i = 0; i < studentResults.length; i++) {
        var newRow = table.insertRow();
        var name = newRow.insertCell(0);
        var furthest = newRow.insertCell(1);
        var attemptQ1 = newRow.insertCell(2);
        var attemptQ2 = newRow.insertCell(3);
        var attemptQ3 = newRow.insertCell(4);
        var attemptQ4 = newRow.insertCell(5);
        var avgTime = newRow.insertCell(6);

        name.innerHTML = studentResults[i].name;
        furthest.innerHTML = studentResults[i].furthestQuestion;
        attemptQ1.innerHTML = studentResults[i].questionOneAttempts;
        attemptQ2.innerHTML = studentResults[i].questionTwoAttempts;
        attemptQ3.innerHTML = studentResults[i].questionThreeAttempts;
        attemptQ4.innerHTML = studentResults[i].questionFourAttempts;
        avgTime.innerHTML = calculateAvgTime(studentResults[i]);
    }
}

function generateLevelCompletePage() {
    var levelComplete = "";

    levelComplete += "<div class=\"title\" id=\"levelCompleteText\">";
    levelComplete +=    "<br />Sweet! You just completed level " + currentPlayer.furthestQuestion + "! Nice job!!!<br /><br />";
    levelComplete +=    "Ready to move on? Lets go back to the game board!<br /><br /> ";
    levelComplete +=    "<div id=\"backToBoard\" >";
    levelComplete +=        "<button class=\"dropbtn\" id=\"backToBoardBtn\" onclick=\"generateGameBoard()\">Next Level</button>";
    levelComplete +=    "</div>";
    levelComplete +=    "<div>";
    levelComplete +=        "<br />";
    levelComplete +=    "</div>";
    levelComplete += "</div>";

    document.getElementById("content").innerHTML = levelComplete;
}

function generateQuitConfirmPage() {
    var levelComplete = "";

    levelComplete += "<div class=\"title\" id=\"quitConfirm\">";
    levelComplete +=    "<br />Are you sure you want to quit?<br /><br />";
    levelComplete +=    "<div id=\"backToWelcome\" >";
    levelComplete +=        "<button class=\"dropbtn\" id=\"backToWelcomeBtn\" onclick=\"playerDone()\">Confirm Quit</button>";
    levelComplete +=    "</div>";
    levelComplete +=    "<div>";
    levelComplete +=        "<br />";
    levelComplete +=    "</div>";
    levelComplete += "</div>";

    document.getElementById("content").innerHTML = levelComplete;

}

/************************************************
*  CODE TO VALIDATE INPUT AND CHECK ANSWERS     *
************************************************/

function checkAnswer(question) {
    var level = question.slice(0, 2);
    var studentAnswer = "";

    if (level == "L1") {
        studentAnswer = document.getElementById(question).innerHTML;
    } else if (level == "L2") {
        studentAnswer = document.getElementById(question).value;
    } else if (level == "L3") {
        nowTime = new Date();
        studentAnswer = nowTime.getTime();
    }

    if (!studentAnswer) {
        window.alert("Looks like you forgot to enter an answer, try again!");
        return true;
    }
    var correctAnswer = findCorrectAnswer(question);

    if (studentAnswer == correctAnswer) {
        if (level == "L1") {
            document.getElementById(question).setAttribute('disabled', true);
        } else if (level == "L2") {
            document.getElementById(question).setAttribute('disabled', true);
            document.getElementById(question + "Check").setAttribute('disabled', true);
            document.getElementById(question + "Check").textContent = "Answered correctly!";
        }
        checkIfLevelComplete(level);
    } else if (level == "L3" && (studentAnswer <= (correctAnswer + 500)) && (studentAnswer >= (correctAnswer - 500))) {
        checkIfLevelComplete(level);
    }
    else {
        incrementQuestionAttempt(level);
        return false;
    }
    return true;
}

function findCorrectAnswer(question) {
    switch (question) {
        case "L1A1Button":
            return 'C';
        case "L1A2Button":
            return 'A';
        case "L1A3Button":
            return 'B';
        case "L2A1":
            return 10;
        case "L2A2":
            return 30;
        case "L2A3":
            return 45;
        case "L3A1":
            return stopTime.getTime();
        default:
            return;
    }
}

function checkL1() {
    if (document.getElementById("L1A1Button").innerHTML == "No Answer" ||
        document.getElementById("L1A2Button").innerHTML == "No Answer" ||
        document.getElementById("L1A3Button").innerHTML == "No Answer") {
        window.alert("Opps, missing some answers, try again!");
    } else {
        if (!checkAnswer("L1A1Button") ||
            !checkAnswer("L1A2Button") ||
            !checkAnswer("L1A3Button")) {
            window.alert("One or more of the answers don't look right, try changing them up!");
        }
    }

}

function checkL3() {
    if (!checkAnswer("L3A1")) {
        resetL3();
    }
}

function validatePassword() {
    password = document.getElementById("password").value;
    if (password == TEACHER_PASSWORD) {
        generateResultTable();
    } else {
        window.alert("Sorry, you didn't enter the correct password, consult the documentation for help, or try again!");
    }
}

function validateName() {
    firstName = document.getElementById("studentFirstName").value;
    lastName = document.getElementById("studentLastName").value;
    name = firstName + " " + lastName;
    if (name) {
        currentPlayer.name = name;
        generateGameBoard();
    } else {
        window.alert("Sorry, you didn't enter a name! What's your name?");
    }
}

/************************************************
*     GAME MECHANIC AND HELPER FUNCTIONS        *
************************************************/

function resetL3() {
    generateLevel3();
    document.getElementById("tryAgainText").innerHTML = "Opps, try again, try again with this new time!";
}

function playerDone() {
    if (currentPlayer.name) {
        studentResults.push(currentPlayer);
    }
    generateWelcomePage()
}

function incrementQuestionAttempt(level) {
    switch (level) {
        case "L1":
            currentPlayer.questionOneAttempts++;
            break;
        case "L2":
            currentPlayer.questionTwoAttempts++;
            break;
        case "L3":
            currentPlayer.questionThreeAttempts++;
            break;
        case "L4":
            currentPlayer.questionFourAttempts++;
            break;
        default:
            return;
    }
}

function checkIfLevelComplete(level) {
    var levelComplete = false;

    if (level == "L1") {
        if (document.getElementById('L1A1Button').disabled &&
            document.getElementById('L1A2Button').disabled &&
            document.getElementById('L1A3Button').disabled) {
            levelComplete = true;
            currentPlayer.questionOneEndTime = new Date();
        }
    } else if (level == "L2") {
        if (document.getElementById('L2A1').disabled &&
            document.getElementById('L2A2').disabled &&
            document.getElementById('L2A3').disabled) {
            levelComplete = true;
            currentPlayer.questionTwoEndTime = new Date();
        }
    } else if (level == "L3") {
        levelComplete = true;
        currentPlayer.questionThreeEndTime = new Date();
    }

    if (levelComplete == true) {
        incrementQuestionAttempt(level);
        if (currentPlayer.furthestQuestion < 4) {
            currentPlayer.furthestQuestion++;
            var nextLevel = currentPlayer.furthestQuestion + 1;
        } else {
            generateCongratsPage();
            return;
        }

        unlockNextLevel();
        generateLevelCompletePage();
    } else {
        //window.alert("Nice job! Now try for the other questions on this level!");
    }
}

function unlockNextLevel() {
    switch (currentPlayer.furthestQuestion) {
        case 1:
            level2Unlocked = true;
            break;
        case 2:
            level3Unlocked = true;
            break;
        case 3:
            level4Unlocked = true;
            break;
        default:
    }
}

function drawOptions(answerId) {
    var dropDownContent = "";
    for (option in optionsAvailable) {
        dropDownContent += "<a onclick=\"level1OptionSelect(" + option + ", '" + answerId + "')\">" + optionsAvailable[option] + "</a>";
    }

    document.getElementById(answerId).innerHTML = dropDownContent;
}

function level1OptionSelect(option, answerId) {
    optionText = document.getElementById(answerId + "Button").innerHTML;
    if (optionText != "No Answer") {
        optionsAvailable.push(optionText);
    }

    document.getElementById(answerId + "Button").innerHTML = optionsAvailable[option];

    optionsAvailable.splice(option, 1);
    optionsAvailable.sort();

    if (optionsAvailable.length == 0) {
        optionsAvailable.push("No Answer");
    }

    drawOptions("L1A1");
    drawOptions("L1A2");
    drawOptions("L1A3");
}

function createOptions(id) {
    document.getElementById(id).classList.toggle("show");
}

window.onclick = function (event) {
    if (!event.target.matches('.dropbtn')) {

        var dropdowns = document.getElementsByClassName("dropdown-content");
        var i;
        for (i = 0; i < dropdowns.length; i++) {
            var openDropdown = dropdowns[i];
            if (openDropdown.classList.contains('show')) {
                openDropdown.classList.remove('show');
            }
        }
    }
}

function initializeVariables() {
    currentPlayer = {
        name: "",
        furthestQuestion: 0,
        questionOneAttempts: 0,
        questionOneStartTime: new Date(),
        questionOneEndTime: new Date(),
        questionTwoAttempts: 0,
        questionTwoStartTime: new Date(),
        questionTwoEndTime: new Date(),
        questionThreeAttempts: 0,
        questionThreeStartTime: new Date(),
        questionThreeEndTime: new Date(),
        questionFourAttempts: 0,
        questionFourStartTime: new Date(),
        questionFourEndTime: new Date()
    }
    name = "";
    password = "";
    level2Unlocked = false;
    level3Unlocked = false;
    level4Unlocked = false;
    optionsAvailable = ["A", "B", "C"];
}

function calculateAvgTime(i) {
    if (i.furthestQuestion == 0) {
        return "No questions Attempted";
    }

    var totMin = 0;
    totMin += (i.questionOneEndTime.getMinutes() - i.questionOneStartTime.getMinutes());
    totMin += (i.questionTwoEndTime.getMinutes() - i.questionTwoStartTime.getMinutes());
    totMin += (i.questionThreeEndTime.getMinutes() - i.questionThreeStartTime.getMinutes());
    totMin += (i.questionFourEndTime.getMinutes() - i.questionFourStartTime.getMinutes());

    var totSec = 0;

    i.questionOneEndTime.getSeconds() > i.questionOneStartTime.getSeconds() ?
        totSec += i.questionOneEndTime.getSeconds() - i.questionOneStartTime.getSeconds() :
        totSec += i.questionOneEndTime.getSeconds() - i.questionOneStartTime.getSeconds() + 60;

    i.questionTwoEndTime.getSeconds() > i.questionTwoStartTime.getSeconds() ?
        totSec += i.questionTwoEndTime.getSeconds() - i.questionTwoStartTime.getSeconds() :
        totSec += i.questionTwoEndTime.getSeconds() - i.questionTwoStartTime.getSeconds() + 60;

    i.questionThreeEndTime.getSeconds() > i.questionThreeStartTime.getSeconds() ?
        totSec += i.questionThreeEndTime.getSeconds() - i.questionThreeStartTime.getSeconds() :
        totSec += i.questionThreeEndTime.getSeconds() - i.questionThreeStartTime.getSeconds() + 60;

    i.questionFourEndTime.getSeconds() > i.questionFourStartTime.getSeconds() ?
        totSec += i.questionFourEndTime.getSeconds() - i.questionFourStartTime.getSeconds() :
        totSec += i.questionFourEndTime.getSeconds() - i.questionFourStartTime.getSeconds() + 60;

    var avgMin = totMin / i.furthestQuestion;
    var avgSec = totSec / i.furthestQuestion;

    var returnString = "";
    if (avgMin > 0) {
        returnString += avgMin + " Minutes and ";
    }
    returnString += avgSec + " Seconds";

    return returnString;
}

function addCheckAnswerButton(parent, id) {
    var checkText = document.createTextNode("Check Answer!");

    var button = document.createElement('BUTTON');
    button.id = id + "Check";
    button.className = "dropbtn";
    button.appendChild(checkText);
    button.addEventListener('click', function () {
        if (!checkAnswer(id)) {
            window.alert("Almost! Try again!");
        }

    });

    document.getElementById(parent).appendChild(button);
}

/************************************************
*             CODE TO DRAW CLOCK                *
************************************************/

function drawMovingClock() {
    var canvas = document.getElementById("canvas");
    var ctx = canvas.getContext("2d");
    var radius = canvas.height / 2;
    ctx.translate(radius, radius);
    radius = radius * 0.90
    setInterval(drawClock, 1000);

    function drawClock() {
        drawFace(ctx, radius);
        drawNumbers(ctx, radius);
        drawTime(ctx, radius);
    }

    function drawFace(ctx, radius) {
        var grad;
        ctx.beginPath();
        ctx.arc(0, 0, radius, 0, 2 * Math.PI);
        ctx.fillStyle = 'white';
        ctx.fill();
        grad = ctx.createRadialGradient(0, 0, radius * 0.95, 0, 0, radius * 1.05);
        grad.addColorStop(0, '#333');
        grad.addColorStop(0.5, 'white');
        grad.addColorStop(1, '#333');
        ctx.strokeStyle = grad;
        ctx.lineWidth = radius * 0.1;
        ctx.stroke();
        ctx.beginPath();
        ctx.arc(0, 0, radius * 0.1, 0, 2 * Math.PI);
        ctx.fillStyle = '#333';
        ctx.fill();
    }

    function drawNumbers(ctx, radius) {
        var ang;
        var num;
        ctx.font = radius * 0.15 + "px arial";
        ctx.textBaseline = "middle";
        ctx.textAlign = "center";
        for (num = 1; num < 13; num++) {
            ang = num * Math.PI / 6;
            ctx.rotate(ang);
            ctx.translate(0, -radius * 0.85);
            ctx.rotate(-ang);
            ctx.fillText(num.toString(), 0, 0);
            ctx.rotate(ang);
            ctx.translate(0, radius * 0.85);
            ctx.rotate(-ang);
        }
    }

    function drawTime(ctx, radius) {
        var now = new Date();
        var hour = now.getHours();
        var minute = now.getMinutes();
        var second = now.getSeconds();
        //hour
        hour = hour % 12;
        hour = (hour * Math.PI / 6) +
        (minute * Math.PI / (6 * 60)) +
        (second * Math.PI / (360 * 60));
        drawHand(ctx, hour, radius * 0.5, radius * 0.07);
        //minute
        minute = (minute * Math.PI / 30) + (second * Math.PI / (30 * 60));
        drawHand(ctx, minute, radius * 0.8, radius * 0.07);
        // second
        second = (second * Math.PI / 30);
        drawHand(ctx, second, radius * 0.9, radius * 0.02);
    }

    function drawHand(ctx, pos, length, width) {
        ctx.beginPath();
        ctx.lineWidth = width;
        ctx.lineCap = "round";
        ctx.moveTo(0, 0);
        ctx.rotate(pos);
        ctx.lineTo(0, -length);
        ctx.stroke();
        ctx.rotate(-pos);
    }
}

function drawStationaryClock(id, date) {
    var canvas = document.getElementById(id);
    var ctx = canvas.getContext("2d");
    var radius = canvas.height / 2;
    ctx.translate(radius, radius);
    radius = radius * 0.90
    setInterval(drawClock(ctx, radius, date), 1000);
}

function drawClock(ctx, radius, date) {
    drawFace(ctx, radius);
    drawNumbers(ctx, radius);
    drawTime(ctx, radius, date);
}

function drawFace(ctx, radius) {
    var grad;
    ctx.beginPath();
    ctx.arc(0, 0, radius, 0, 2 * Math.PI);
    ctx.fillStyle = 'white';
    ctx.fill();
    grad = ctx.createRadialGradient(0, 0, radius * 0.95, 0, 0, radius * 1.05);
    grad.addColorStop(0, '#333');
    grad.addColorStop(0.5, 'white');
    grad.addColorStop(1, '#333');
    ctx.strokeStyle = grad;
    ctx.lineWidth = radius * 0.1;
    ctx.stroke();
    ctx.beginPath();
    ctx.arc(0, 0, radius * 0.1, 0, 2 * Math.PI);
    ctx.fillStyle = '#333';
    ctx.fill();
}

function drawNumbers(ctx, radius) {
    var ang;
    var num;
    ctx.font = radius * 0.15 + "px arial";
    ctx.textBaseline = "middle";
    ctx.textAlign = "center";
    for (num = 1; num < 13; num++) {
        ang = num * Math.PI / 6;
        ctx.rotate(ang);
        ctx.translate(0, -radius * 0.85);
        ctx.rotate(-ang);
        ctx.fillText(num.toString(), 0, 0);
        ctx.rotate(ang);
        ctx.translate(0, radius * 0.85);
        ctx.rotate(-ang);
    }
}

function drawTime(ctx, radius, date) {
    var now = date;
    var hour = now.getHours();
    var minute = now.getMinutes();
    var second = now.getSeconds();
    //hour
    hour = hour % 12;
    hour = (hour * Math.PI / 6) +
        (minute * Math.PI / (6 * 60)) +
        (second * Math.PI / (360 * 60));
    drawHand(ctx, hour, radius * 0.5, radius * 0.07);
    //minute
    minute = (minute * Math.PI / 30) + (second * Math.PI / (30 * 60));
    drawHand(ctx, minute, radius * 0.8, radius * 0.07);
    // second
    second = (second * Math.PI / 30);
    drawHand(ctx, second, radius * 0.9, radius * 0.02);
}

function drawHand(ctx, pos, length, width) {
    ctx.beginPath();
    ctx.lineWidth = width;
    ctx.lineCap = "round";
    ctx.moveTo(0, 0);
    ctx.rotate(pos);
    ctx.lineTo(0, -length);
    ctx.stroke();
    ctx.rotate(-pos);
}

/************************************************
*                     EOF                       *
************************************************/



