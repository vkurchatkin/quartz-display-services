#include <node.h>
#include <v8.h>
#include <ApplicationServices/ApplicationServices.h>

#define DEFINE_BOOLEAN_METHOD(name) Handle <Value> name (const Arguments& args) { \
  HandleScope scope; \
  CGDirectDisplayID displayId = (CGDirectDisplayID) args[0] -> Uint32Value(); \
  return scope.Close(v8::Boolean::New(CG ## name (displayId))); \
} \

#define QDS_SET_METHOD(target, name) node::SetMethod(target, #name, name);

using namespace v8;

Handle <Value> MainDisplayID (const Arguments& args) {
  HandleScope scope;

  CGDirectDisplayID displayId = CGMainDisplayID();

  return scope.Close(Integer::NewFromUnsigned(displayId));
}

Handle <Value> ActiveDisplayList (const Arguments& args) {
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

Handle <Value> OnlineDisplayList (const Arguments& args) {
  HandleScope scope;

  uint32_t count;

  CGGetActiveDisplayList(0, NULL, &count);

  CGDirectDisplayID * displays = (CGDirectDisplayID *) malloc(sizeof(CGDirectDisplayID) * count);

  CGGetOnlineDisplayList(count, displays, &count);

  Local<Array> display_arr = Array::New(count);

  for (uint32_t i = 0; i < count; i ++) {
    display_arr -> Set(i, Integer::NewFromUnsigned(displays[i]));
  }

  free(displays);

  return scope.Close(display_arr);
}

DEFINE_BOOLEAN_METHOD (DisplayIsActive)
DEFINE_BOOLEAN_METHOD (DisplayIsAlwaysInMirrorSet)
DEFINE_BOOLEAN_METHOD (DisplayIsAsleep)
DEFINE_BOOLEAN_METHOD (DisplayIsBuiltin)
DEFINE_BOOLEAN_METHOD (DisplayIsInHWMirrorSet)
DEFINE_BOOLEAN_METHOD (DisplayIsInMirrorSet)
DEFINE_BOOLEAN_METHOD (DisplayIsMain)
DEFINE_BOOLEAN_METHOD (DisplayIsOnline)
DEFINE_BOOLEAN_METHOD (DisplayIsStereo)

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
  QDS_SET_METHOD (exports, MainDisplayID)
  QDS_SET_METHOD (exports, ActiveDisplayList)
  QDS_SET_METHOD (exports, OnlineDisplayList)
  QDS_SET_METHOD (exports, DisplayIsActive)
  QDS_SET_METHOD (exports, DisplayIsBuiltin)
  QDS_SET_METHOD (exports, DisplayIsAlwaysInMirrorSet)
  QDS_SET_METHOD (exports, DisplayIsAsleep)
  QDS_SET_METHOD (exports, DisplayPixelsWide)
  QDS_SET_METHOD (exports, DisplayPixelsHigh)
  QDS_SET_METHOD (exports, DisplayIsInHWMirrorSet)
  QDS_SET_METHOD (exports, DisplayIsInMirrorSet)
  QDS_SET_METHOD (exports, DisplayIsMain)
  QDS_SET_METHOD (exports, DisplayIsOnline)
  QDS_SET_METHOD (exports, DisplayIsStereo)
}

NODE_MODULE(quartz_display_services, init)