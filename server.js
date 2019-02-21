const express = require('express')
const server =  express()

server.get('/', function(req, res, next){
	res.send('Home Page')
})

server.use('/public', express.static(__dirname + '/public'))


server.listen(2121);
