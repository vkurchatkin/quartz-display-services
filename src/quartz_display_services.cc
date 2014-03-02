#include <node.h>
#include <v8.h>
#include <ApplicationServices/ApplicationServices.h>
#include <stdio.h>
#include "display_wrap.h"

using namespace v8;

Handle<Value> GetActiveDisplayList (const Arguments& args) {
  HandleScope scope;

  uint32_t count;

  CGGetActiveDisplayList(0, NULL, &count);

  CGDirectDisplayID * displays = (CGDirectDisplayID *) malloc(sizeof(CGDirectDisplayID) * count);

  CGGetActiveDisplayList(count, displays, &count);

  Local<Array> display_arr = Array::New(count);

  for (int i = 0; i < count; i ++) {
    DisplayWrap * display = DisplayWrap::New(displays[i]);

    display_arr -> Set(i, display -> handle_);
  }

  free(displays);

  return scope.Close(display_arr);
}

void init(Handle<Object> exports) {
  DisplayWrap::Init();

  exports->Set(String::NewSymbol("GetActiveDisplayList"),
      FunctionTemplate::New(GetActiveDisplayList)->GetFunction());
}

NODE_MODULE(quartz_display_services, init)