                                                                                
General Information
-------------------

The Neat Scrollbar module integrates the mCustomScrollbar jQuery plugin with 
Drupal. The Neat Scrollbar module allows the user to add contemporary minimalist
scrollbars to sections of content within a Drupal website.  There are options to
change the scrollbar theme and the animation of scroll-enabled-content as well 
as a range of other features.

The aim of this module is to provide an easy implementation of many of
the standard features of this plugin for non-technical users of Drupal, while at
the same time allowing developers to override this module's standard options and
settings in order to implement their own custom scripts and stylesheets.

You can find out about this jQuery plugin on the developer's website:
 
http://manos.malihu.gr/jquery-custom-content-scroller/

This module also provides you with the option to use the JQuery Mouse Wheel
plugin together with the mCustomScrollbar jQuery plugin.

You can find out about this jQuery plugin on the developer's project repository:

https://github.com/brandonaaron/jquery-mousewheel

The MCustomScrollbar jQuery Plugin, and the Mouse Wheel jQuery Plugin are
developed, maintained, and licensed independently of this Drupal module.

Please see the Drupal project page for a more detailed explanation.

http://drupal.org/project/neat_scrollbar

Downloads
---------

The mCustomScrollbar plugin is provided together with various other example
files. It is recommended that you only download the files listed under 
"Installation and Usage" below.  Conveniently, you can obtain all of the
files required (including the Mouse Wheel jQuery Plugin) at the following
repository folders:

  github.com/malihu/malihu-custom-scrollbar-plugin/tree/master/js/minified
  github.com/malihu/malihu-custom-scrollbar-plugin/tree/master/js/uncompressed
  github.com/malihu/malihu-custom-scrollbar-plugin/blob/master/mCSB_buttons.png

Additionally, you can refer to this modules project page on Drupal.org for links
to the required plugin files.


Installation and Usage
----------------------

This module is dependent on the Libraries API module version 7.x-2.1 or later.
You can install this with Drush ('drush dl libraries') or from its project page:

https://drupal.org/project/libraries

Install the Neat Scrollbar module in the usual manner, ensuring that the
scrollbar plugin files are found in the following directories:

    sites/all/libraries/neat_scrollbar

The 'neat_scrollbar' library folder should contain the following files:

    jquery.mCustomScrollbar.min.js (required for loading of minified version)
    jquery.mCustomScrollbar.css (required for scrollbar themes & styles)
    mCSB_buttons.png (required for buttons/arrows)
    jquery.mCustomScrollbar.js (required for extraction of library version)

If you don't already have the jQuery Mouse Wheel plugin installed and wish to
use it with this module, you should ensure that it is installed in the following 
folder:

    sites/all/libraries/mousewheel

The 'mousewheel' library folder should contain the following file:

    jquery.mousewheel.min.js

Please see the module documentation for full installation and usage details:

http://drupal.org/project/neat_scrollbar

note: if you use a different location for your libraries folder, you should
ensure that it is one that will be picked up by the Libraries API.  You should
then ensure that the sub-folders 'neat_scrollbar' and 'mousewheel' exist
therein.


Compatibility Advice - jQuery Update Module
-------------------------------------------

There is NO dependency between this Module and the jQuery Update Module.

 'https://drupal.org/project/jquery_update'

For users of the jQuery Update Module version 7.x-2.3 (the current version)
there is a minor issue where the scrollbars do not appear, ONLY if version 1.8
of jQuery is used.

This can be corrected by selecting jQuery version 1.7 which works as expected or
by downloading the latest development release of jQuery Update, which works for 
all versions up to jQuery 1.10.

Drupal Module Author
--------------------

David Mc Donnell (davidmac)
http://drupal.org/user/1445008
http://knooq.com
