#include <node.h>
#include <v8.h>
#include <ApplicationServices/ApplicationServices.h>

using namespace v8;

Handle <Value> MainDisplayID (const Arguments& args) {
  HandleScope scope;

  CGDirectDisplayID displayId = CGMainDisplayID();

  return scope.Close(Integer::NewFromUnsigned(displayId));
}

Handle <Value> GetActiveDisplayList (const Arguments& args) {
  HandleScope scope;

  uint32_t count;

  CGGetActiveDisplayList(0, NULL, &count);

  CGDirectDisplayID * displays = (CGDirectDisplayID *) malloc(sizeof(CGDirectDisplayID) * count);

  CGGetActiveDisplayList(count, displays, &count);

  Local<Array> display_arr = Array::New(count);

  for (uint32_t i = 0; i < count; i ++) {
    display_arr -> Set(i, Integer::NewFromUnsigned(displays[i]));
  }

  free(displays);

  return scope.Close(display_arr);
}

Handle <Value> DisplayIsActive (const Arguments& args) {
  HandleScope scope;

  CGDirectDisplayID displayId = (CGDirectDisplayID) args[0] -> Uint32Value();

  return scope.Close(v8::Boolean::New(CGDisplayIsActive(displayId)));
}

Handle <Value> DisplayIsBuiltin (const Arguments& args) {
  HandleScope scope;

  CGDirectDisplayID displayId = (CGDirectDisplayID) args[0] -> Uint32Value();

  return scope.Close(v8::Boolean::New(CGDisplayIsBuiltin(displayId)));
}

Handle <Value> DisplayPixelsHigh (const Arguments& args) {
  HandleScope scope;

  CGDirectDisplayID displayId = (CGDirectDisplayID) args[0] -> Uint32Value();

  return scope.Close(Integer::New(CGDisplayPixelsHigh(displayId)));
}

Handle <Value> DisplayPixelsWide (const Arguments& args) {
  HandleScope scope;

  CGDirectDisplayID displayId = (CGDirectDisplayID) args[0] -> Uint32Value();

  return scope.Close(Integer::New(CGDisplayPixelsWide(displayId)));
}

void init (Handle<Object> exports) {
  exports->Set(String::NewSymbol("MainDisplayID"),
      FunctionTemplate::New(MainDisplayID)->GetFunction());

  exports->Set(String::NewSymbol("GetActiveDisplayList"),
      FunctionTemplate::New(GetActiveDisplayList)->GetFunction());

  exports->Set(String::NewSymbol("DisplayIsActive"),
      FunctionTemplate::New(DisplayIsActive)->GetFunction());

  exports->Set(String::NewSymbol("DisplayIsBuiltin"),
      FunctionTemplate::New(DisplayIsBuiltin)->GetFunction());

  exports->Set(String::NewSymbol("DisplayPixelsWide"),
      FunctionTemplate::New(DisplayPixelsWide)->GetFunction());

  exports->Set(String::NewSymbol("DisplayPixelsHigh"),
      FunctionTemplate::New(DisplayPixelsHigh)->GetFunction());
}

NODE_MODULE(quartz_display_services, init)