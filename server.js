const express = require('express')
const server =  express()

server.get('/', function(req, res, next){
	res.send('Home Page')
})


server.listen(2121);