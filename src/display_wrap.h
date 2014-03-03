#ifndef SRC_DISPLAY_WRAP_H_
#define SRC_DISPLAY_WRAP_H_

#include <node.h>
#include <ApplicationServices/ApplicationServices.h>

class DisplayWrap : public node::ObjectWrap {
  public:
    static void Init();
    static DisplayWrap * New(CGDirectDisplayID displayId);
  private:
    explicit DisplayWrap(CGDirectDisplayID displayId);
    ~DisplayWrap();

    static v8::Persistent<v8::Function> constructor;
    static v8::Handle<v8::Value> ScreenSize (const v8::Arguments& args);
    static v8::Handle<v8::Value> PixelsHigh (const v8::Arguments& args);
    static v8::Handle<v8::Value> PixelsWide (const v8::Arguments& args);
    static v8::Handle<v8::Value> IsActive (const v8::Arguments& args);

    CGDirectDisplayID displayId;
};

#endif  // SRC_DISPLAY_WRAP_H_