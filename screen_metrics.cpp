/*/ HACK for node-gyp's node.h ( target=v0.11.? ) (https://github.com/TooTallNate/node-gyp/issues/398) !!!!!!!!!!!!!!!!!!
#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#define _SSIZE_T_
#endif
// HACK for node-gyp's node.h ( target=v0.11.? ) (https://github.com/TooTallNate/node-gyp/issues/398) ENDS !!!!!!!!!!!!!*/

#include <node.h>
#include "Windows.h"

using namespace v8;

BOOL CALLBACK MonitorEnumProc( HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData )
{
    Handle<Array> * monitors = (Handle<Array>*)dwData;
    RECT * monitorCoordinates = (RECT*)lprcMonitor;

    Handle<Array> monitorData = Array::New();

    monitorData->Set( 0, Integer::New( (*monitorCoordinates).left ) );
    monitorData->Set( 1, Integer::New( (*monitorCoordinates).top ) );
    monitorData->Set( 2, Integer::New( (*monitorCoordinates).right - (*monitorCoordinates).left ) );
    monitorData->Set( 3, Integer::New( (*monitorCoordinates).bottom - (*monitorCoordinates).top  ) );

    (*monitors)->Set( (*monitors)->Length(), monitorData );

    return TRUE;
}

#if NODE_VERSION_AT_LEAST(0, 11, 3)

void getDisplayMetrics( const v8::FunctionCallbackInfo<Value> &args ) // Returns an array of arrays with the resolutions and virtual positions of each monitor in the system
{
  Handle<Array> monitors = Array::New(); // [[x,y,w,h], [x,y,w,h], [x,y,w,h], ...]

  if ( EnumDisplayMonitors( NULL, NULL, MonitorEnumProc, ( LPARAM ) &monitors ) )
    args.GetReturnValue().Set( monitors );
  else
  {
    // TODO: Throw an exception
    args.GetReturnValue().Set( String::New( "Error! Cant get monitors information (EnumDisplayMonitors failed)." ) );
  }
}


void getTotalResolution( const v8::FunctionCallbackInfo<Value> &args ) // Returns the total width and height of the virtual screen including all display monitors
{
  Handle<Array> dimensions = Array::New( 2 ); // [width,height]

  dimensions->Set( 0, Integer::New( GetSystemMetrics( SM_CXVIRTUALSCREEN ) ) );
  dimensions->Set( 1, Integer::New( GetSystemMetrics( SM_CYVIRTUALSCREEN ) ) );

  args.GetReturnValue().Set( dimensions );
}

void getMonitorsCount( const v8::FunctionCallbackInfo<Value> &args ) // Returns the number of monitors in the system
{
  args.GetReturnValue().Set( Integer::New( GetSystemMetrics( SM_CMONITORS ) ) );
}

#else

/*
 * Code for 0.11.2 and lower.
 */

Handle<Value> getDisplayMetrics( const Arguments& args ) // Returns an array of arrays with the resolutions and virtual positions of each monitor in the system
{
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Handle<Array> monitors = Array::New(); // [[x,y,w,h], [x,y,w,h], [x,y,w,h], ...]

  if ( EnumDisplayMonitors( NULL, NULL, MonitorEnumProc, (LPARAM) &monitors ) )
    return scope.Close( monitors );

  // TODO: Throw an exception
  return scope.Close( String::New( "Error! Cant get monitors information (EnumDisplayMonitors failed)." ) );
}

Handle<Value> getTotalResolution( const Arguments& args ) // Returns the total width and height of the virtual screen including all display monitors
{
  HandleScope scope;

  Handle<Array> dimensions = Array::New( 2 ); // [width,height]

  dimensions->Set( 0, Integer::New( GetSystemMetrics( SM_CXVIRTUALSCREEN ) ) );
  dimensions->Set( 1, Integer::New( GetSystemMetrics( SM_CYVIRTUALSCREEN ) ) );

  return scope.Close( dimensions );
}

Handle<Value> getMonitorsCount( const Arguments& args ) // Returns the number of monitors in the system
{
    HandleScope scope;

    return scope.Close( Integer::New( GetSystemMetrics( SM_CMONITORS ) ) );
}

#endif // NODE_VERSION_AT_LEAST

void RegisterModule( Handle<Object> exports )
{
  exports->Set( String::NewSymbol( "getDisplayMetrics" ),  FunctionTemplate::New( getDisplayMetrics )->GetFunction() );
  exports->Set( String::NewSymbol( "getTotalResolution" ), FunctionTemplate::New( getTotalResolution )->GetFunction() );
  exports->Set( String::NewSymbol( "getMonitorsCount" ),   FunctionTemplate::New( getMonitorsCount )->GetFunction() );
}

NODE_MODULE( screen_metrics, RegisterModule )