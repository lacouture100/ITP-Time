const fs = require("fs");
const path = require("path");
const express = require("express");
const config = require("./config");  // Port and env configuration
const moment = require("moment"); //include the moment package
const sunCalc = require("suncalc");

const PORT= process.env.PORT ||3000;
const app = express(); // Assign express() to a variable
const bodyParser = require('body-parser');

app.use(bodyParser.urlencoded({extended:true}));
app.use(bodyParser.json());


//Middleware defines the order of files to run. If I would put an index.html file in the public folder it would grab that first
app.use(express.static(__dirname + '/public'));

// NYC coords 
var lat = 40.69;
var long = -73.98;

// Response in this format: 2020-03-05T09:23:03-05:00
let logTime = moment().format().toString();

// Get suncalc times
var times = sunCalc.getTimes(new Date(), lat, long);


var sunrise = times.sunrise.getHours() + ':' + times.sunrise.getMinutes();
var sunriseEnd = times.sunriseEnd.getHours() + ':' + times.sunriseEnd.getMinutes();
var morningGoldenHourEnd = times.goldenHourEnd.getHours() + ':' + times.goldenHourEnd.getMinutes();

var solarNoon = times.solarNoon.getHours() + ':' + times.solarNoon.getMinutes();

var goldenHour = times.goldenHour.getHours() + ':' + times.goldenHour.getMinutes();

var sunsetStart = times.goldenHour.getHours() + ':' + times.goldenHour.getMinutes();
var sunset = times.sunset.getHours() + ':' + times.sunset.getMinutes();

var sunsetStart = times.sunsetStart.getHours() + ':' + times.sunsetStart.getMinutes();


//Whenever we get a request it will send the user towards index.html
app.get("/", (req,res) =>{
    console.log(logTime)
    console.log(req);
    res.send(`Today's sunrise begins at ${sunriseEnd}`);
});

//GET If users visit our website/api/v1/todos we will get this message
app.get("/api/", async(req,res) => {
    console.log(req);
        res.send('Hello from js aPI');

});

//Open the port
app.listen(PORT, ()=>{
    console.log(`See the magic at http://localhost:${PORT}`);
});