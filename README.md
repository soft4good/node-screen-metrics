node-screen-metrics
===================

Node.js native c++ module (windows) for retrieving screen geometry information.

<h1>Exported Methods</h1>

<b>getMonitorsCount()</b> 
Returns the number of display monitors in the system.

<b>getTotalResolution()</b> 
Returns an array in the form [w,h] with the total width and height (pixels) of the virtual screen including all displays.

<b>getDisplayMetrics()</b> 
Returns an array of arrays in the form [[x,y,w,h],[x,y,w,h],[x,y,w,h]...] with the resolutions and virtual positions of each display monitor in the system.

<h1>Building</h1>

<code>
node-gyp configure
node-gyp build
</code>

<h2>Building for node-webkit (0.9.2)</h2>

<code>
nw-gyp configure --target=0.9.2
nw-gyp build
</code>

<h1>Testing</h1>

<code>
  node test.js
</code>

...work in progress...
