var services = require('./index.js');

console.log('Main display: ');

console.log(services.getMainDisplay().toJSON());

services.displays().forEach(function (display) {
  console.log(display.toJSON());
});