// siakinnik - terminal.js
const WebSocket = require('ws');
const readline = require('readline');

const SERVER_URL = 'ws://zerolamp.local:81';
let clientAuthorized = false;

// readline
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
    prompt: '> '
});

let ws;

const connect = () => {
    ws = new WebSocket(SERVER_URL);
    ws.on('open', () => {
        console.log('Connected. Waiting for code request...');
    });

    ws.on('message', (data) => {
        const msg = data.toString().trim();
        console.log('\n<<', msg);

        if (!clientAuthorized && msg.includes('Enter connection code:')) {
            rl.question('Enter code: ', (code) => {
                ws.send(code.trim());
            });
        } else if (!clientAuthorized && msg.includes('Authorized!')) {
            clientAuthorized = true;
            console.log('Authorization success!');
            rl.prompt();
        } else if (!clientAuthorized && msg.includes('Wrong code')) {
            console.log('Wrong code, try again!');
            ws.close();
            setTimeout(connect, 1000);
        }
    });

    ws.on('close', () => {
        clientAuthorized = false;
        console.log('\nConnection closed. Reconnecting in 3 seconds...');
        setTimeout(connect, 3000);
    });

    ws.on('error', (err) => {
        console.error('Connection error:', err.message);
        setTimeout(connect, 3000);
    });
};

rl.on('line', (line) => {
    if (!clientAuthorized) {
        console.log('Authorization first!');
        rl.prompt();
        return;
    }
    const command = line.trim().replace(/[\r\n]+$/, '').replace(/;$/, '');
    ws.send(command);
    rl.prompt();
});

connect();