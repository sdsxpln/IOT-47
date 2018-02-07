const Koa = require('koa');
const bodyParser = require('koa-bodyparser');
const templating = require('./templating');
const controller = require('./controller');
// const cors = require('koa-cors');
const net = require('net');
const WebSocket = require('ws');
const WebSocketServer = WebSocket.Server;
const app = new Koa();
var receive = 'undifined';
var con_num = 0;
var clientList = [];
var clientNum = 0;
var cliectSocket = [];
var platform_stm32 = {};

var server = net.createServer(function(socket) {

    console.log('cliect connetced');

    console.log('CONNECTED: ' + socket.remoteAddress + ':' + socket.remotePort);

    socket.write("You have connected\n");



    // cliectSocket.push(socket);



    socket.on('end', function() {
        console.log('客户端关闭连接');
    });

    socket.on('data', function(data) {
        let receive = data.toString();
        receive = receive.substring(0, receive.length - 2);
        let receive_arr = receive.split("_");
        for (let i of receive_arr) {
            console.log(i);
        }
        if (receive_arr.length === 9) {
            platform_stm32.platform = receive_arr[0];
            platform_stm32.id = receive_arr[1];
            platform_stm32.user = receive_arr[2];
            platform_stm32.ip = receive_arr[3];
            platform_stm32.port = receive_arr[4];
            platform_stm32.temperature = receive_arr[5];
            platform_stm32.led = receive_arr[6];
            platform_stm32.lo = receive_arr[7];
            platform_stm32.la = receive_arr[8];
            if (typeof(tmp) !== "undefined") {
                tmp.send(JSON.stringify(platform_stm32), (err) => {
                    if (err) {
                        console.log(`[SERVER] error: ${err}`);
                    }
                });
            }
        } else {
            console.log("format error\n");

        }
        // var index = cliectSocket.indexOf(socket);
        // // for (let i in cliectSocket) {
        // //     if (i != index) {
        // //         cliectSocket[i].write(data);
        // //     }
        // // }
        // cliectSocket.forEach((other) => {
        //     if (other !== socket) {
        //         other.write(data.toString());
        //     }
        // })



        // console.log("receive: " + data.toString());
        // receive = data.toString();
        // receive = receive.substring(0, receive.length - 2);
        // let arr = receive.split(' ');
        // if (con_num) {
        //     if (arr.length === 2) {
        //         tmp.send(JSON.stringify({
        //             lo: arr[0],
        //             la: arr[1]
        //         }), (err) => {
        //             if (err) {
        //                 console.log(`[SERVER] error: ${err}`);
        //             }
        //         });
        //     }
        // }
    })
});



let staticFiles = require('./static-files');
// app.use(cors());
//第一个参数是url链接地址，后面一个参数是url真实地址，两地址不一定相同所以都要传入
app.use(staticFiles('/static/', __dirname + '/static'));
app.use(bodyParser());
app.use(templating('views', { noCache: true, watch: true }));
app.use(controller());

let wsser = app.listen(3000);


server.listen(3001, function() {
    console.log("TCP server running");
})
console.log('app started at port 3000...');
let wss = new WebSocketServer({
    server: wsser
});
var tmp;
wss.on('connection', function(ws) {
    console.log("linked by websocket");
    con_num++;
    tmp = ws;
    console.log(`[SERVER] connection()`);
    ws.on('message', function(message) {
        console.log(`[SERVER] Received: ${message}`);
        ws.send(`ECHO: ${message}`, (err) => {
            if (err) {
                console.log(`[SERVER] error: ${err}`);
            }
        });
    })
});
wss.on('close', () => {
    con_num--;
});

// wss.broadcast = function(data) {
//     wss.clients.forEach(function(client) {
//         client.send(data);
//     });
// };

// wss.on('message', function(message) {
//     console.log(message);
//     if (message && message.trim()) {
//         let msg = createMessage('chat', 'song', message.trim());
//         this.wss.broadcast(msg);
//     }
// });

// var messageIndex = 0;

// function createMessage(type, user, data) {
//     messageIndex++;
//     return JSON.stringify({
//         id: messageIndex,
//         type: type,
//         user: user,
//         data: data
//     });
// }