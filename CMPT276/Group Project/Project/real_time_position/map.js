
// var socket = io();
// $(document).ready(function(){
// 	check_pos = setInterval(function(){ //create a loop and wait for the response
// 		if(typeof pos != 'undefined'){ //while the position is not defined the loop is checking every half seconds
// 			socket.emit('new_user', {pos: pos});
// 			clearInterval(check_pos);
// 		}
// 	}, 500);
// 	socket.on('already', function(data){
// 		$.each( data.visitors, function( key, pos ) {
// 			addMarker(pos);
// 		});
// 	});
// 	socket.on('connected', function(data){
// 		$("#users_count").html("<strong>" + data.users_count +"</strong>" + " connected users");
// 		$("#users_count").css({'visibility': 'visible'});
// 		addMarker(data.pos);
// 	});
// 	socket.on('disconnected', function(data){
// 		//we can now delete this position:
// 		var markerId = getMarkerUniqueId(data.del.lat, data.del.lng); // get marker id by using clicked point's coordinate
// 		var marker = markers[markerId]; // find marker
// 		removeMarker(marker, markerId); // remove it
// 		$("#users_count").html("<strong>" + data.users_count +"</strong>" + " connected users");
// 	});
// });

// var visitors = {};
// io.on('connection', function(socket){
// 	socket.on('new_user', function(data){
// 		if(parseInt(Object.keys(visitors).length) > 0)
// 			socket.emit('already', {visitors: visitors});
// 		visitors[socket.id] = data.pos;
// 		io.emit('connected', { pos: data.pos, users_count: Object.keys(visitors).length });
// 		console.log('someone CONNECTED:');
// 		console.log(visitors);
// 	});
// 	socket.on('disconnect', function(){
// 		if(visitors[socket.id]){
// 			var todel = visitors[socket.id];
// 			delete visitors[socket.id];
// 			io.emit('disconnected', { del: todel, users_count: Object.keys(visitors).length }); 	
// 		}
// 		console.log('someone DISCONNECTED:');
// 		console.log(visitors);
// 	});
// }); 

var express = require('express');
var app = express();
var server = require('http').Server(app);
var io = require('socket.io')(server);

server.listen(3000, function(){
	console.log('MAP started on port: 3000');
});
app.get('/', function(req, res){
	res.sendFile(__dirname + '/map/index.html');
	app.use(express.static('.'));
});


var visitors = {};
io.on('connection', function(socket){
	socket.on('new_user', function(data){
		if(parseInt(Object.keys(visitors).length) > 0)
			socket.emit('already', {visitors: visitors});
		visitors[socket.id] = data.pos;
		io.emit('connected', { pos: data.pos, users_count: Object.keys(visitors).length });
		console.log('someone CONNECTED:');
		console.log(visitors);
	});
	socket.on('disconnect', function(){
		if(visitors[socket.id]){
			var todel = visitors[socket.id];
			delete visitors[socket.id];
			io.emit('disconnected', { del: todel, users_count: Object.keys(visitors).length }); 	
		}
		console.log('someone DISCONNECTED:');
		console.log(visitors);
	});
}); 