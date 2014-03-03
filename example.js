var services = require('./index.js');

services.displays().forEach(function (display) {
  console.log(display.toJSON());
});