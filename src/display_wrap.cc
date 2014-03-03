#include <node.h>
#include "display_wrap.h"

using namespace v8;

Persistent<Function> DisplayWrap::constructor;

DisplayWrap * DisplayWrap::New (CGDirectDisplayID displayId) {
  DisplayWrap * displayWrap = new DisplayWrap(displayId);
  Local<Object> object = constructor -> NewInstance();

  displayWrap -> Wrap(object);

  return displayWrap;
}

DisplayWrap::DisplayWrap (CGDirectDisplayID displayId) : displayId (displayId) { }

DisplayWrap::~DisplayWrap () { }

void DisplayWrap::Init() {
  Local<FunctionTemplate> tpl = FunctionTemplate::New();

  tpl->SetClassName(String::NewSymbol("Display"));

  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  tpl->PrototypeTemplate()->Set(String::NewSymbol("ScreenSize"),
      FunctionTemplate::New(ScreenSize)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("PixelsHigh"),
      FunctionTemplate::New(PixelsHigh)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("PixelsWide"),
      FunctionTemplate::New(PixelsWide)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("IsActive"),
      FunctionTemplate::New(IsActive)->GetFunction());

  tpl->PrototypeTemplate()->Set(String::NewSymbol("IsBuiltin"),
      FunctionTemplate::New(IsBuiltin)->GetFunction());

  constructor = Persistent<Function>::New(tpl->GetFunction());
}

Handle <Value> DisplayWrap::ScreenSize (const Arguments& args) {
  HandleScope scope;

  DisplayWrap * display = ObjectWrap::Unwrap <DisplayWrap> (args.This());

  CGSize size = CGDisplayScreenSize(display -> displayId);

  Local <Object> object = Object::New();

  object -> Set(String::NewSymbol("width"), Number::New(size.width));
  object -> Set(String::NewSymbol("height"), Number::New(size.height));

  return scope.Close(object);
}

Handle <Value> DisplayWrap::PixelsHigh (const v8::Arguments& args) {
  HandleScope scope;

  DisplayWrap * display = ObjectWrap::Unwrap <DisplayWrap> (args.This());

  return scope.Close(Number::New(CGDisplayPixelsHigh(display -> displayId)));
}

Handle <Value> DisplayWrap::PixelsWide (const v8::Arguments& args) {
  HandleScope scope;

  DisplayWrap * display = ObjectWrap::Unwrap <DisplayWrap> (args.This());

  return scope.Close(Number::New(CGDisplayPixelsWide(display -> displayId)));
}

Handle <Value> DisplayWrap::IsActive (const v8::Arguments& args) {
  HandleScope scope;

  DisplayWrap * display = ObjectWrap::Unwrap <DisplayWrap> (args.This());

  return scope.Close(v8::Boolean::New(CGDisplayIsActive(display -> displayId)));
}

Handle <Value> DisplayWrap::IsBuiltin (const v8::Arguments& args) {
  HandleScope scope;

  DisplayWrap * display = ObjectWrap::Unwrap <DisplayWrap> (args.This());

  return scope.Close(v8::Boolean::New(CGDisplayIsBuiltin(display -> displayId)));
}


