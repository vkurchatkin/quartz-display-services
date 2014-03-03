var services = require('bindings')('quartz_display_services');

function displays () {
  return services.GetActiveDisplayList().map(Display);
}

function Display (displayId) {
  if (!(this instanceof Display)) return new Display(displayId);

  this._displayId = displayId
}

Object.defineProperties(Display.prototype, {
  width : { enumerable : true, get : getWidth },
  height : { enumerable : true, get : getHeight }
});

Display.prototype.toJSON = toJSON;

function toJSON () {
  return {
    height : this.height,
    width : this.width
  }
}

function getWidth () {
  return this._displayId.PixelsWide();
}

function getHeight () {
  return this._displayId.PixelsHigh();
}

exports.displays = displays;