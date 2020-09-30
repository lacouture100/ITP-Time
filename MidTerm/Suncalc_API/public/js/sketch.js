
//My API endpoint
const url = '/sun'


// NYC coords 
var lat = 40.69;
var long = -73.98;

var sunrise;
var sunriseEnd;
var morningGoldenHourEnd;
var solarNoon;
var goldenHour;
var sunsetStart;
var sunset;
var dusk;
var night;
var nadir;
var nightEnd;
var nauticalDawn;
var dawn;

var times = [sunrise,sunriseEnd,morningGoldenHourEnd,solarNoon,goldenHour,sunsetStart,sunset,dusk,night,nadir,nightEnd,nauticalDawn,dawn]

let fromColor;
let toColor;

async function fetchData() {
  await fetch(url)
    .then(response => {
      return response.json()
    })
    .then(result => {

      sunrise = result.sunrise;
      sunriseEnd = result.sunriseEnd;
      morningGoldenHourEnd = result.morningGoldenHourEnd;
      solarNoon = result.solarNoon;
      goldenHour = result.goldenHour;
      sunsetStart = result.sunsetStart;
      sunset = result.sunset;
      dusk = result.dusk;
      night = result.night;
      nadir = result.nadir;
      nightEnd = result.nightEnd;
      nauticalDawn = result.nauticalDawn;
      dawn = result.dawn;


      console.log(sunrise.time);
    })

}



async function setup() {
  await fetchData();
  createCanvas(500, 800);
  textSize(18);


  text("From Color", 20, 20);
  fromColor = color("red");

  text("Lerped Color", 150, 20);

  text("To Color", 300, 20);
  toColor = color("blue");

  text("Adjust this slider to change the" +
    " amount of lerping", 20, 200)
  alphaSlider = createSlider(0, 100, 50);
  alphaSlider.position(20, 220);
  alphaSlider.style('width', '250px');
  
  let initialX = 20;
  let initialY = 300;

  text(`Sunrise is at ${sunrise.time}`,initialX,initialY);
  text(`Sunrise ends at ${sunriseEnd.time}`,initialX,initialY+20 *1);
  text(`Morning Golden Hour ends at ${morningGoldenHourEnd.time}`,initialX,initialY+20 *2);
  text(`Solar Noon is at ${solarNoon.time}`,initialX,initialY+20 *3);
  text(`Golden Hour is at ${goldenHour.time}`,initialX,initialY+20 *4);
  text(`Sunset Starts at ${sunsetStart.time}`,initialX,initialY+20 *5);
  text(`Sunset is at ${sunset.time}`,initialX,initialY+20 *6);
  text(`Dusk is at ${dusk.time}`,initialX,initialY+20 *7);
  text(`Nightime is at ${night.time}`,initialX,initialY+20 *8);
  text(`Nadir is at ${nadir.time}`,initialX,initialY+20 *9);
  text(`Night ends at ${nightEnd.time}`,initialX,initialY+20 *10);
  text(`Nautical Dawn is at ${nauticalDawn.time}`,initialX,initialY+20 *11);
  text(`Dawn is at ${dawn.time}`,initialX,initialY+20 *12);

  
      sunrise = result.sunrise;
      sunriseEnd = result.sunriseEnd;
      morningGoldenHourEnd = result.morningGoldenHourEnd;
      solarNoon = result.solarNoon;
      goldenHour = result.goldenHour;
      sunsetStart = result.sunsetStart;
      sunset = result.sunset;
      dusk = result.dusk;
      night = result.night;
      nadir = result.nadir;
      nightEnd = result.nightEnd;
      nauticalDawn = result.nauticalDawn;
      dawn = result.dawn;

}

async function draw() {
  lerpedColor = lerpColor(fromColor, toColor, alphaSlider.value() / 100);
  

  fill(fromColor);
  rect(30, 30, 50, 100);

  fill(lerpedColor);
  rect(170, 30, 50, 100);

  fill(toColor);
  rect(310, 30, 50, 100);

  fill(toColor);
  rect(450, 30, 50, 100);
}