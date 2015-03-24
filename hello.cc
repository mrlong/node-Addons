///usr/local/include/node 内有引用的文件
// hello.cc
//double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();

#include <node.h>
#include <string>


using namespace v8;

namespace img_obj{
	std::string text;
	std::string filename;
	int count;
	int width;
	int height;
	int offset;
	int quality;
	int isjpeg;
  int fontSize;
}


void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world444499222"));
}

//两个数相加，有参数传进来了
void Add(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if (args.Length() < 2) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }

  double value = args[0]->NumberValue() + args[1]->NumberValue();
  
  Local<Number> num = Number::New(isolate, value);

  args.GetReturnValue().Set(num);
};


//有回调功能
void RunCallback(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  
  if (args.Length() < 2) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }
  
  if (!args[0]->IsString() || !args[1]->IsFunction()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  };
  
  //std::string value = args[0]->ToString();
  
  String::Utf8Value utf8_value(args[0]->ToString());//转化成v8::Utf8Value
  //std::string str(*utf8_value);//转化为string
  std::string str= *utf8_value;
  char str2[2];
  strcpy(str2,'dd');
  //char s;
  int len = strlen(str.c_str());
  for(int i=0;i<=len;i++){ //strlen(str.c_str())
    //str2 = str2 + IntToHex(str[i],2);
    //str2='q';
    //strcat(str2.c_str(),str[i]);
    //strcat(str2,printf("%d\n",str[i]));
  }
  
  Local<Function> cb = Local<Function>::Cast(args[1]);
  const unsigned argc = 1;
  Local<Value> argv[argc] = {String::NewFromUtf8(isolate, str2)};// { args[0]->ToString() };
  //Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "hello world") };
  cb->Call(isolate->GetCurrentContext()->Global(), argc, argv);
};




void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
  NODE_SET_METHOD(exports, "add", Add);
  NODE_SET_METHOD(exports, "ord", RunCallback);
}

NODE_MODULE(addon, init)
  
  

  