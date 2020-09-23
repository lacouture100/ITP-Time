//My API endpoint
const url = '/api/v1/ideas'

let categories = [];

//Load when the DOM is loaded
window.addEventListener('DOMContentLoaded', () => {
    console.log("DOM content loaded");
    loadIdeas();
    submitIdea();
})

async function loadIdeas() {
    await fetch(url)
        .then(response => {
            //console.log(response.json())
            //convert the incoming message into JSON format
            return response.json()
        })
        .then(result => {
            const mainSection = document.querySelector('.catalogue');
            result.forEach(element => {
                switch (categories.includes(element.category)) {

                    //If the category does not exist create a container for it
                    case false:
                        categories.push(element.category);
                        //created the container for each category
                        const categoryContainer = document.createElement("div");
                        //set the category's class
                        categoryContainer.setAttribute("class", "category");

                        categoryContainer.setAttribute("id", `category__${element.category}`);
                        //append the empty list of containers onto the DOM body
                        mainSection.appendChild(categoryContainer);

                        //created the container for the category label
                        const categoryLabel = document.createElement("h2");
                        //set the class for each category label
                        categoryLabel.setAttribute("class", "category__label");
                        //set the category label's unique id
                        categoryLabel.setAttribute("id", `${element.category}__label`);
                        //Fill the label with text
                        categoryLabel.textContent = `${element.category}`;
                        //append the category's title to it's container
                        categoryContainer.appendChild(categoryLabel);

                        //created the container for the category content
                        const categoryContent = document.createElement("div");
                        //set the class for each category content
                        categoryContent.setAttribute("class", "category__content");
                        //set the category content's unique id
                        categoryContent.setAttribute("id", `${element.category}__content`);
                        //append the content full of ideas to the container
                        categoryContainer.appendChild(categoryContent);

                        //created the list of removable toppings
                        const categoryButton = document.createElement("button");
                        //set the toppings' class
                        categoryButton.setAttribute("class", `category__button`);
                        categoryButton.setAttribute("id", `category__remove__${element.category}`);

                        //grab each element in the json and implement it into the topping list element as a text field
                        categoryButton.textContent = `Remove category`;
                        //append each button to the list
                        categoryContainer.appendChild(categoryButton);

                        //If the category already exists only append the idea
                    case true:
                        const existingCategory = document.getElementById(`${element.category}__content`)
                        //created the container for each category    
                        const ideaContainer = document.createElement("div");
                        //set the category's class
                        ideaContainer.setAttribute("class", "idea");
                        //append the empty list of containers onto the DOM body
                        existingCategory.appendChild(ideaContainer);

                        //created the container for the category label
                        const ideaLabel = document.createElement("div");
                        //set the class for each category label
                        ideaLabel.setAttribute("class", "idea__label");
                        //set the category label's unique id
                        ideaLabel.setAttribute("id", `${element.idea}__label`);

                        //append the category's title to it's container
                        ideaContainer.appendChild(ideaLabel);

                        //created the container for the category content
                        const ideaContent = document.createElement("p");
                        //set the class for each category content
                        ideaContent.setAttribute("class", "idea__content");

                        ideaContent.textContent = `${element.idea}`;
                        //append the content full of ideas to the container
                        ideaContainer.appendChild(ideaContent);

                        categoryButton.onclick = async () => {
                            await deleteIdeas(element.category);
                        }

                }
                
            });
        });
    console.log(categories)
}

function submitIdea() {
    //look for the topping submit form button
    const submitButton = document.querySelector('.submit__button');
    //execute a function when the submit button is clicked
    submitButton.onclick = async () => {
        console.log("Button clicked!");
        //look for the Category input field
        const categoryInput = document.getElementById('submit__categoryinput');
        //look for the Idea input field
        const ideaInput = document.getElementById('submit__ideainput');
        //grab the value in the input field
        const category = categoryInput.value;
        //grab the value in the input field
        const idea = ideaInput.value;
        //If topping input field is not empty make the request
        if (category !== "" && idea !== "") {
            //wait for the url response
            await fetch(url, {
                //Define the request message
                method: "POST",
                //converts JSON into a string to be sent as the body
                body: JSON.stringify({
                    //message sent 
                    category: category,
                    idea: idea
                }),
                headers: {
                    'Content-Type': 'application/json'
                }
            })
            //console log the success message
            console.log(`Success! "${idea}" added in the "${category}" category!`)
            //set input value back to blank
            categoryInput.value = "";
            ideaInput.value = "";

        } else {
            //Alert the user they can't leace the input field empty
            alert("There's no such thing as an empty idea!");
        }
    };
}
function deleteIdeas(category) {
    //get the topping div
    const categoryContainer =  document.getElementById(`category__${category}`);
    //removethe topping div
    categoryContainer.remove();
        //console log the success message
    console.log(`Success! ${category} removed!`)
    //send the DELETE request for the selected topping
    fetch(`/api/v1/ideas/${category}`, 
    {
      method: "DELETE",
      headers: {
        'Content-Type': 'application/json'
      }
      //send the json request
    }).then(res => res.json())
  }
