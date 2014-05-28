{
 	"conditions": [
    ['OS=="win"', {
		  "targets": [
		    {
		      "target_name": "screen_metrics",
		      "sources": [ "screen_metrics.cpp" ]
		    }
		  ]
	  }],
    [ 'OS=="mac"', {
		  "targets": [
		    {
		      "target_name": "screen_metrics",
		      "sources": [ "screen_metrics.mm" ],
		      "libraries": ["/System/Library/Frameworks/AppKit.framework"]
		    }
		  ]
    }]
  ],

}