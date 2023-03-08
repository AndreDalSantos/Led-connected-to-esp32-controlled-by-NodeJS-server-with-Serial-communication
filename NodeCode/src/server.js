const express = require('express');
const { SerialPort } = require('serialport');

const port = new SerialPort({
  path: '/dev/ttyUSB0',
  baudRate: 9600,
  dataBits: 8,
  stopBits: 1,
  parity: 'none'
});

const app = express();

const serverPort = 3000;

let status = 'Desligado';
let commandSent = false;

app.set('view engine', 'ejs');

port.on('readable', function () {
  const data = port.read();

  const auxiliarValue = data.toString();

  if (auxiliarValue === 'l' || auxiliarValue === 'd') {
    status = auxiliarValue === 'l' ? 'Ligado' : auxiliarValue === 'd' ? 'Desligado' : auxiliarValue;
    app.get('/status', (req, res) => {
      res.send({ status });
    });
  }
});

app.get("/", (req, res) => {
  if (!commandSent) {
    port.write('2\n');
    commandSent = true;
  }

  res.render('index', { status });
});

app.post('/led/on', (req, res) => {
  port.write('1\n');
  return res.redirect('/');
});

app.post('/led/off', (req, res) => {
  port.write('0\n');
  return res.redirect('/');
});

app.listen(serverPort, () => {
  console.log(`Listening on port ${serverPort}`);
});