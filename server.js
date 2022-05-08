const express = require('express')
const server =  express()

server.use('/', express.static(__dirname + '/public/'))

server.listen(2121, function(){console.log("Server started listening at localhost:2121: http://localhost:2121")});