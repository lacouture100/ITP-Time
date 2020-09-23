//My API endpoint
const url = '/api/vi/ideas'

//Load when the DOM is loaded
window.addEventListener('DOMContentLoaded', () => {
})

async function loadIdeas() {
  await fetch(url)
    .then(response => {
      //convert the incoming message into JSON format
      return response.json()
    })
    .then(result => {

      const mainSection = document.querySelector('.catalogue');
      
      //created the container for the list elements
      const ideaContainer = document.createElement("div");
      //set the list's class
      ideaContainer.setAttribute("class", "category");
      //append the empty list of toppings onto the DOM body
      mainSection.appendChild(ideaContainer);

      //Look into the JSON's 'pizzaToppings' field and 
      //create a list element with each of it's elements
      result.pizzaToppings.forEach(element => {

        //created the container for the topping names and buttons
        const toppingContainer = document.createElement("div");
        //set the containers' class
        toppingContainer.setAttribute("class", "topping");
        //set the container's unique id
        toppingContainer.setAttribute("id", `topping__${element}`);
        //Set a random background color for each topping
        randomBackground(toppingContainer);


        //created the list of available toppings
        const toppingName = document.createElement("li");
        //set the toppings' class
        toppingName.setAttribute("class", "topping__name");
        //grab each element in the json and implement it into the topping list element as a text field
        toppingName.textContent = `${element}`;
        //append each topping to the list
        toppingContainer.appendChild(toppingName);

        //created the list of removable toppings
        const toppingButton = document.createElement("button");
        //set the toppings' class
        toppingButton.setAttribute("class", "topping__button");
        //grab each element in the json and implement it into the topping list element as a text field
        toppingButton.textContent = `Remove ${element}`;
        //append each topping to the list
        toppingContainer.appendChild(toppingButton);

        //append the empty containers of toppings onto the DOM body
        toppingList.appendChild(toppingContainer);
        //when the user click the delete topping button it deletes it's div and db register
        toppingButton.onclick = async () => {
          await deleteTopping(element);
        }
      });
    })
}

function deleteTopping(topping) {
  //get the topping div
  const toppingContainer =  document.getElementById(`topping__${topping}`);
  //removethe topping div
  toppingContainer.remove();
      //console log the success message
  console.log(`Success! ${topping} removed!`)
  //send the DELETE request for the selected topping
  fetch(`/toppings/${topping}`, 
  {
    method: "DELETE",
    headers: {
      'Content-Type': 'application/json'
    }
    //send the json request
  }).then(res => res.json())
}

function submitTopping() {
  //look for the topping submit form button
  const submitButton = document.querySelector('.submit__button');
  //execute a function when the submit button is clicked
  submitButton.onclick = async () => {
    //look for the input field
    const toppingInput = document.querySelector('.submit__input');
    //grab the value in the input field
    const topping = toppingInput.value;
    //If topping input field is not empty make the request
    if(topping !== ""){
      //wait for the url response
    await fetch(url, {
      //Define the request message
      method: "POST",
      //converts JSON into a string to be sent as the body
      body: JSON.stringify({
        //message sent 
        topping: topping
      }),
      headers: {
        'Content-Type': 'application/json'
      }
    })
    //console log the success message
    console.log(`Success! ${topping} added!`)
    //set input value back to blank
    toppingInput.value = "";
  } else {
    //Alert the user they can't leace the input field empty
    alert("There's no such thing as an empty topping! Try again");
  }
  };
}

function randomBackground(container) {
  const maxRange = 150;
  const r = Math.floor(Math.random() * maxRange);
  const g = Math.floor(Math.random() * maxRange);
  const b = Math.floor(Math.random() * maxRange);
  container.style.backgroundColor = `rgb(${r},${g},${b})`;

}