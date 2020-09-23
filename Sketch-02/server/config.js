//Here we define the data we want to keep private
require('dotenv').config();

module.exports = {
    //This makes the default port be 3000
    PORT: process.env.PORT ||3000,

}