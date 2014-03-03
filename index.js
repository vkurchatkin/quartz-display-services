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
  height : { enumerable : true, get : getHeight },
  active : { enumerable : true, get : getActive }
});

Display.prototype.toJSON = toJSON;

function toJSON () {
  return {
    height : this.height,
    width : this.width,
    active : this.active
  }
}

function getWidth () {
  return this._displayId.PixelsWide();
}

function getHeight () {
  return this._displayId.PixelsHigh();
}

function getActive () {
  return this._displayId.IsActive();
}

exports.displays = displays;