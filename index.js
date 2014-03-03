var CG = require('bindings')('quartz_display_services');

function getMainDisplay () {
  return new Display(CG.MainDisplayID());
}

function displays () {
  return CG.GetActiveDisplayList().map(Display);
}

function Display (displayId) {
  if (!(this instanceof Display)) return new Display(displayId);

  this._displayId = displayId
}

Object.defineProperties(Display.prototype, {
  width : { enumerable : true, get : getWidth },
  height : { enumerable : true, get : getHeight },
  active : { enumerable : true, get : getActive },
  builtin : { enumerable : true, get : getBuiltin }
});

Display.prototype.toJSON = toJSON;

function toJSON () {
  return {
    height : this.height,
    width : this.width,
    active : this.active,
    builtin : this.builtin
  }
}

function getWidth () {
  return CG.DisplayPixelsWide(this._displayId);
}

function getHeight () {
  return CG.DisplayPixelsHigh(this._displayId);
}

function getActive () {
  return CG.DisplayIsActive(this._displayId);
}

function getBuiltin () {
  return CG.DisplayIsBuiltin(this._displayId);
}

/**
 * Exports
 */

exports.displays = displays;
exports.getMainDisplay = getMainDisplay;