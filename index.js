var CG = require('bindings')('quartz_display_services');

function getMainDisplay () {
  return new Display(CG.MainDisplayID());
}

function getActiveDisplays () {
  return CG.ActiveDisplayList().map(Display);
}

function getOnlineDisplays () {
  return CG.OnlineDisplayList().map(Display);
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
  var json = {
    height : this.height,
    width : this.width,
  };

  boolProps.forEach(addBoolProp, this);

  function addBoolProp (name) {
    json[name] = this[name];
  }

  return json;
}

function getWidth () {
  return CG.DisplayPixelsWide(this._displayId);
}

function getHeight () {
  return CG.DisplayPixelsHigh(this._displayId);
}

var boolProps = [
  'active',
  'alwaysInMirrorSet',
  'asleep',
  'builtin',
  'inHWMirrorSet',
  'inMirrorSet',
  'main',
  'online',
  'stereo'
];

function getBoolProperty (name) {
  return function () {
    return CG['DisplayIs' + name.slice(0, 1).toUpperCase() + name.slice(1)](this._displayId);
  };
}

boolProps.forEach(defineBoolProp);

function defineBoolProp (name) {
  Object.defineProperty(Display.prototype, name, { enumerable : true, get : getBoolProperty(name) });
}


/**
 * Exports
 */

exports.getMainDisplay = getMainDisplay;
exports.getActiveDisplays = getActiveDisplays;
exports.getOnlineDisplays = getOnlineDisplays;