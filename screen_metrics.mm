#include <node.h>
#include <node_version.h>
#import <AppKit/AppKit.h>

using namespace v8;

// TODO: Handle Exceptions!

Handle<Array> displayMetrics()
{
  Handle<Array> monitors = Array::New();

  NSArray *systemScreens = [NSScreen screens];
  
  if ( systemScreens != NULL )
  {
    for( NSScreen *screen in systemScreens )
    {
      NSRect screenFrame = screen.frame;
      
      Handle<Array> displayMetrics = Array::New( 4 );
      
      displayMetrics->Set( 0, Integer::New( screenFrame.origin.x ) );
      displayMetrics->Set( 1, Integer::New( screenFrame.origin.y ) );
      displayMetrics->Set( 2, Integer::New( screenFrame.size.width ) );
      displayMetrics->Set( 3, Integer::New( screenFrame.size.height ) );
        
      monitors->Set( monitors->Length(), displayMetrics );
    }
  }

  return monitors;
}

Handle<Array> totalResolution()
{
  Handle<Array> dimensions = Array::New( 2 );

  unsigned totalWidth = 0;
  unsigned totalHeight = 0;
  
  NSArray *systemScreens = [NSScreen screens];
  
  if ( systemScreens != NULL )
  {
    for( NSScreen *screen in systemScreens )
    {
      NSRect screenFrame = screen.frame;
    
      totalWidth  += screenFrame.size.width;
      totalHeight += screenFrame.size.height;
    }
   
    dimensions->Set( 0, Integer::New( totalWidth ) ); // width
    dimensions->Set( 1, Integer::New( totalHeight ) ); // height
  }
  
  return dimensions;
}

Handle<Integer> monitorsCount()
{
  NSArray *systemScreens = [NSScreen screens];
  unsigned screenCount 	 = [systemScreens count];
    
  return Integer::New( screenCount );
}

#if NODE_VERSION_AT_LEAST(0, 11, 3)

	void getDisplayMetrics( const v8::FunctionCallbackInfo<Value> &args )  { args.GetReturnValue().Set( displayMetrics() ); }
	void getTotalResolution( const v8::FunctionCallbackInfo<Value> &args ) { args.GetReturnValue().Set( totalResolution() ); }
	void getMonitorsCount( const v8::FunctionCallbackInfo<Value> &args )   { args.GetReturnValue().Set( monitorsCount() ); }
		
#else

	Handle<Value> getDisplayMetrics( const Arguments& args )  { HandleScope scope; return scope.Close( displayMetrics() ); }
	Handle<Value> getTotalResolution( const Arguments& args ) { HandleScope scope; return scope.Close( totalResolution() ); }
	Handle<Value> getMonitorsCount( const Arguments& args )   { HandleScope scope; return scope.Close( monitorsCount() ); }
	
#endif // NODE_VERSION_AT_LEAST


void RegisterModule( Handle<Object> exports )
{
	/* getDisplayMetrics() ===============================================================================================
	 Returns an array in the form [[x1,y1,w1,h1], [x2,y2,w2,h2], ..., [xN,yN,wN,hN]] 
	 with the resolutions and virtual positions of each monitor in the system.
	*/
  exports->Set( String::NewSymbol( "getDisplayMetrics" ),  FunctionTemplate::New( getDisplayMetrics )->GetFunction() );
  	
  /* getTotalResolution() ==============================================================================================
  	Returns an array in the form [width, height] with the total width and height of 
  	the virtual screen including all display monitors.
	*/
  exports->Set( String::NewSymbol( "getTotalResolution" ), FunctionTemplate::New( getTotalResolution )->GetFunction() );
  	
  /* getMonitorsCount() ================================================================================================
  	Returns the number of monitors in the system.
  */	
  exports->Set( String::NewSymbol( "getMonitorsCount" ),   FunctionTemplate::New( getMonitorsCount )->GetFunction() );
}

NODE_MODULE( screen_metrics, RegisterModule )