var net = require('net');
var sockets = [];
var tcpServer = net.createServer({allHalfOpen:true});
tcpServer.on('connection', function (socket) {
    console.log('connection established ... ');

    sockets.push(socket);
    socket.on('data', function (data) {
        if (sockets.length >= 2) {
            if (sockets[0] === socket) {
                sockets[1].write(data);
            }
            else sockets[0].write(data);
        }
    });
    socket.on('close', function () {
        socketUtil.socketStats(socket);
        console.log('closed event fired');
    })
    socket.on('end', function () {
        console.log('disconnect.');
    })
    socket.on('error', function () {
        console.log('here is wrong ...');
        var pos = sockets.indexOf(socket);
        socket.destroy();
        if (pos >= 0) {
            sockets.splice(pos, 1);
        }

    })
})
tcpServer.listen(8080);
