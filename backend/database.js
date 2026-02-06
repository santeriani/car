const mysql = require('mysql2');
const myConnectionString = "mysql://netuser:netpass@localhost:3306/netdb";
const connection = mysql.createPool(myConnectionString);

module.exports = connection;

