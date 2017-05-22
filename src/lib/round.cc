#include "round.h"

namespace tribeca {
  void Round::Init(Local<Object> target) {
    Nan::Export(target, "roundUp", Round::RoundUp);
    Nan::Export(target, "roundDown", Round::RoundDown);
    Nan::Export(target, "roundNearest", Round::RoundNearest);
    Nan::Export(target, "roundSide", Round::RoundSide);
  }

  NAN_METHOD(Round::RoundUp) {
    if (!Round::Valid(info)) return;

    float value = info[0]->NumberValue();
    float minTick = info[1]->NumberValue();

    v8::Local<v8::Number> num = Nan::New(ceil(value / minTick) * minTick);

    info.GetReturnValue().Set(num);
  }

  NAN_METHOD(Round::RoundDown) {
    if (!Round::Valid(info)) return;

    float value = info[0]->NumberValue();
    float minTick = info[1]->NumberValue();

    v8::Local<v8::Number> num = Nan::New(floor(value / minTick) * minTick);

    info.GetReturnValue().Set(num);
  }

  NAN_METHOD(Round::RoundNearest) {
    if (!Round::Valid(info)) return;

    float value = info[0]->NumberValue();
    float minTick = info[1]->NumberValue();

    v8::Local<v8::Number> num = Nan::New(round(value / minTick) * minTick);

    info.GetReturnValue().Set(num);
  }

  NAN_METHOD(Round::RoundSide) {
    if (!Round::Valid(info)) return;

    if (!info[2]->IsNumber()) {
      Nan::ThrowTypeError("Wrong side value");
      return;
    }

    int side = info[2]->NumberValue();

    switch (side) {
      case 0: Round::RoundDown(info); break;
      case 1: Round::RoundUp(info); break;
      default: Round::RoundNearest(info); break;
    }
  }

  bool Round::Valid(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if (info.Length() < 2) {
      Nan::ThrowTypeError("Wrong number of arguments");
      return false;
    }

    if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
      Nan::ThrowTypeError("Wrong arguments");
      return false;
    }

    return true;
  }
}