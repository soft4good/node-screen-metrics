var screenMetrics = require('./build/Release/screen_metrics');
process.stdout.write( "getMonitorsCount()   -> " + String( screenMetrics.getMonitorsCount() ) 	+ "\n"  );
process.stdout.write( "getTotalResolution() -> " + String( screenMetrics.getTotalResolution() ) + "\n" );
process.stdout.write( "getDisplayMetrics() -> "  + String( screenMetrics.getDisplayMetrics() ) 	+ "\n" );