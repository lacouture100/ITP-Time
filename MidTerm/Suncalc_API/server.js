//Required node packages
const express = require("express");
const path = require("path");
const fs = require("fs");
const port = 3000;

const moment = require("moment"); //include the moment package
const sunCalc = require("suncalc");

// NYC coords 
var lat = 40.69;
var long = -73.98;

// Response in this format: 2020-03-05T09:23:03-05:00
let logTime = moment().format().toString();

// Get suncalc times
var times = sunCalc.getTimes(new Date(), lat, long);

var sunrise                 = times.sunrise.getHours() + ':' + times.sunrise.getMinutes();
var sunriseEnd              = times.sunriseEnd.getHours() + ':' + times.sunriseEnd.getMinutes();
var morningGoldenHourEnd    = times.goldenHourEnd.getHours() + ':' + times.goldenHourEnd.getMinutes();
var solarNoon               = times.solarNoon.getHours() + ':' + times.solarNoon.getMinutes();
var goldenHour              = times.goldenHour.getHours() + ':' + times.goldenHour.getMinutes();
var sunsetStart             = times.goldenHour.getHours() + ':' + times.goldenHour.getMinutes();
var sunset                  = times.sunset.getHours() + ':' + times.sunset.getMinutes();
var dusk                    = times.dusk.getHours() + ':' + times.dusk.getMinutes();
var night                   = times.night.getHours() + ':' + times.night.getMinutes();
var nadir                   = times.nadir.getHours() + ':' + times.nadir.getMinutes();
var nightEnd                = times.nightEnd.getHours() + ':' + times.nightEnd.getMinutes();
var nauticalDawn            = times.nauticalDawn.getHours() + ':' + times.nauticalDawn.getMinutes();
var dawn                    = times.dawn.getHours() + ':' + times.dawn.getMinutes();
var sunPos = sunCalc.getPosition(new Date(), /*Number*/ lat, /*Number*/ long);

console.log(sunPos)





//absolute path to my index.html file. 
//__dirname is the absolute path of the directory containing the currently executing file.
const indexPath = path.join(__dirname, 'views/index.html');


//define express inside of a variable
const app = express();

//define my static server files directory, in this case the 'public' folder
app.use(express.static(__dirname + '/public'));
//It parses incoming and outgoing requests with JSON payloads(it means it converts them into JSON-formatted text)
app.use(express.json());
//a '/' request will send you to the index.html file
app.get('/', (req, res) => res.sendFile(indexPath))

/*
//Define our GET function.
function getToppings() {
    //grab the toppings json from the data folder on root
    const toppingsJSON = fs.readFileSync(path.join(__dirname, '/data/toppings.json'));
    //parse the toppings json
    const toppings = JSON.parse(toppingsJSON);
    return toppings
}
*/
function getTimes(){

    //Read our sunEvents in order to update the data on each request.
    const sunEventsJSON = fs.readFileSync(path.join(__dirname, '/data/suncalcData.json'));
    //parse our JSON
    const sunEvents = JSON.parse(sunEventsJSON);
    // Set the updated values
    sunEvents.sunrise.time = sunriseEnd;
    sunEvents.sunriseEnd.time = sunriseEnd;
    sunEvents.morningGoldenHourEnd.time = morningGoldenHourEnd;
    sunEvents.solarNoon.time = solarNoon;
    sunEvents.goldenHour.time = goldenHour;
    sunEvents.sunsetStart.time = sunsetStart;
    sunEvents.sunset.time = sunset;
    sunEvents.dusk.time = dusk;
    sunEvents.night.time = night;
    sunEvents.nadir.time = nadir;
    sunEvents.nightEnd.time = nightEnd;
    sunEvents.nauticalDawn.time = nauticalDawn;
    sunEvents.dawn.time = dawn;

    fs.writeFileSync(path.join(__dirname, '/data/suncalcData.json'), JSON.stringify(sunEvents));
    return sunEvents;
}

/*
//Define our POST function.
function addTopping(topping) {
    //read from the toppings json before adding a topping
    const toppings = getToppings();
    //add the topping to the 'pizzaToppings' item in the json
    toppings.pizzaToppings.push(topping);
    //update the pizzaToppings file with the new toppings
    fs.writeFileSync(path.join(__dirname, '/data/toppings.json'), JSON.stringify(toppings));
    return toppings
}

function addTime(sunEvent){

}

//Define our DELETE function.
function deleteTopping(deleteTopping) {
    //read from the toppings json before deleting a topping
    const toppings = getToppings();
    //Only keep the toppings that are different from the deleteTopping variable
    toppings.pizzaToppings = toppings.pizzaToppings.filter(topping => topping !== deleteTopping);
    //update the pizzaToppings file with the new toppings
    fs.writeFileSync(path.join(__dirname, '/data/toppings.json'), JSON.stringify(toppings));
    return toppings
}
*/
/*
//Express GET request
app.get("/toppings", (req, res) => {
    //read from the toppings json
    const toppings = getToppings();
    // Updated list will be returned by API
    res.json(
        */
        //Express GET request
app.get("/sun", (req, res) => {
    //read from the toppings json
    const sunEvents = getTimes();
    console.log(`Received request: ${req}`);
    // Updated list will be returned by API
    res.json(sunEvents);
});
/*

//Express POST request
app.post("/toppings", (req, res) => {
    //grab the 'topping' from the POST request. The request must be in the {"topping":"whatever"} format.
    const topping = req.body.topping;
    //add the topping to the toppings list
    const toppings = addTopping(topping);
    // Updated list will be returned by API
    res.json(toppings);
});

//Express DELETE request
app.delete("/toppings/:name", (req, res) => {
    //set the name at the end of the request as the name of the topping to delete
    const toppingToDelete = req.params.name;
    //update the toppings file after deleting the topping
    const toppings = deleteTopping(toppingToDelete);
    // Updated list will be returned by API
    res.json(toppings);
});

*/

//Open the port
app.listen(port, () => console.log(`Server app listening on port ${port}!`))
getTimes()