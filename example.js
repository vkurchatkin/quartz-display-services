var services = require('./index.js');

console.log('Main display:');

console.log(services.getMainDisplay().toJSON());

console.log();
console.log('Online displays:');

services.getOnlineDisplays().forEach(function (display) {
  console.log(display.toJSON());
});

console.log();
console.log('Active displays:');

services.getActiveDisplays().forEach(function (display) {
  console.log(display.toJSON());
});