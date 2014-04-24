node-screen-metrics
===================

Node.js native c++ module (windows) for retrieving screen geometry information (work in progress).

<h2>Exported Methods</h2>

<b>getMonitorsCount()</b> 
Returns the number of display monitors in the system.


<b>getTotalResolution()</b> 
Returns an array in the form [w,h] with the total width and height (pixels) of the virtual screen including all displays.


<b>getDisplayMetrics()</b> 
Returns an array of arrays in the form [[x,y,w,h],[x,y,w,h],[x,y,w,h]...] with the resolutions and virtual positions of each display monitor in the system.


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

<code>
  node test.js
</code>
