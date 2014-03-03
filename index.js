var services = require('bindings')('quartz_display_services');

function displays () {
  return services.GetActiveDisplayList().map(display);
}

function display (obj) {
  return {
    width : obj.getPixelsWide(),
    height : obj.getPixelsHigh(),
    active : obj.IsActive()
  }
}

exports.displays = displays;