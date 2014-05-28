node-screen-metrics
===================

Node.js native c++ module for retrieving screen geometry information (work in progress).

<h2>Supported Platforms</h2>

<ul>
  <li>Windows (tested on 7 x86 & x64)</li>
  <li>OSX (tested on Mavericks 10.9)  <i>- thanks to <a target="_blank" href="https://github.com/karelium">karelium</a> for pointing the way - </i></li>
</ul>

<h2>Exported Methods</h2>

<b>getMonitorsCount()</b> 
Returns the number of display monitors in the system.


<b>getTotalResolution()</b> 
Returns an array [w,h] with the total width and height (pixels) of the virtual screen including all displays.


<b>getDisplayMetrics()</b> 
Returns an array of arrays [[x,y,w,h],[x,y,w,h],[x,y,w,h]...] with the resolutions and virtual positions of each display monitor in the system.


<h2>Building</h2>

<pre>
node-gyp configure
node-gyp build
</pre>

<h4>Building for node-webkit (0.9.2)</h4>

<pre>
nw-gyp configure --target=0.9.2
nw-gyp build
</pre>

<h2>Testing</h2>

<pre>
node test.js
</pre>

<h2>Usage</h2>

<pre>
var screenMetrics = require( 'screen_metrics' );
  
var monitorsCount   = screenMetrics.getMonitorsCount();
var totalResolution = screenMetrics.getTotalResolution();
var screenGeometry  = screenMetrics.getDisplayMetrics();
</pre>

Have fun!
