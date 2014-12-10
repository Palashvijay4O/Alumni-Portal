                                                                                
General Information
-------------------
The nano Scrollbar module integrates the nanoScroller jQuery plugin with 
Drupal. The nano Scrollbar module allows the user to add contemporary minimalist
scrollbars to sections of content within a Drupal website.  There are options to
change the scrollbar settings and the animation of scroll-enabled-content as
well as a range of other features.

The aim of this module is to provide an easy implementation of many of
the standard features of this plugin for non-technical users of Drupal.

You can find out about this jQuery plugin on the developer's website:
http://jamesflorentino.github.io/nanoScrollerJS/ 

The nanoScroller jQuery Plugin, and the overthrowmin jQuery Plugin are
developed, maintained, and licensed independently of this Drupal module.

Please see the Drupal project page for a more detailed explanation.

https://www.drupal.org/project/nano_scrollbar

Downloads
---------

The nanoScroller plugin is provided together with various other example
files. It is recommended that you only download the files listed under 
"Installation and Usage" below.  Conveniently, you can obtain all of the
files required 


Additionally, you can refer to this modules project page on Drupal.org for links
to the required plugin files.

Installation and Usage
----------------------
This module is dependent on the Libraries API module version 7.x-2.1 or later.
You can install this with Drush ('drush dl libraries') or from its project page:

https://drupal.org/project/libraries

Install the Nano Scrollbar module in the usual manner, ensuring that the
scrollbar plugin files are found in the following directories:

    sites/all/libraries/nano_scrollbar

The 'nano_scrollbar' library folder should contain the following files:

    jquery.nanoscroller.min.js (required for loading of minified version)
    nanoscroller.css (required for scrollbar themes & styles)
    jquery.nanoscroller.js (required for extraction of library version)

If you don't already have the jQuery overthrowmin plugin installed and wish to
use it with this module, you should ensure that it is installed in the following 
folder:

    sites/all/libraries/overthrowmin

The 'overthrowmin' library folder should contain the following file:

    overthrow.min.js
Please download from URL:
https://github.com/jamesflorentino/nanoScrollerJS/blob/master/bin/javascripts/overthrow.min.js

Please see the module documentation for full installation and usage details:

http://drupal.org/project/nano_scrollbar



Compatibility Advice - jQuery Update Module
-------------------------------------------

There is NO dependency between this Module and the jQuery Update Module.

 'https://drupal.org/project/jquery_update'

For users of the jQuery Update Module version 7.x-2.3 (the current version)
The module is tested with jQuery 1.4.4 and will support up to version 10.0.

Drupal Module Author
--------------------

Shyam Kumar Kunkala (shyam kunkala)
https://drupal.org/user/2408974
