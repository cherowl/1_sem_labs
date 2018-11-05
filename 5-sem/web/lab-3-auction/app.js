const express = require('express');
const server = express();
const port = 3000;

const routes = require("./routes");
server.use("/", routes);

const bodyParser = require("body-parser");

server.set("view engine", "pug");
server.set("views", `views`);
server.use(bodyParser.json());
server.use(bodyParser.urlencoded({extended: true}));



server.listen(port, (err) => {
	if (err)
		console.log("Error while starting server");
	else
		console.log(`Server started at port ${port}`);
});