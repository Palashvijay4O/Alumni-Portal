(function ($) {
/*
 * Neat Scrollbar Script.
 *
 */
Drupal.behaviors.neatScrollbar = {
  attach: function(context, settings) {

  // Ready variables.
    var theme = Drupal.settings.neatScrollbarSet.theme;
    var inertia = Drupal.settings.neatScrollbarSet.inertia;
    var buttons = Drupal.settings.neatScrollbarSet.buttons;
    var dragger = Drupal.settings.neatScrollbarSet.dragger_status;
    var autohide = Drupal.settings.neatScrollbarSet.autohide;
    var vertCss = Drupal.settings.neatScrollbarSet.vertical_css;
    var horzCss = Drupal.settings.neatScrollbarSet.horizontal_css;
    var mouseWheel = Drupal.settings.neatScrollbarSet.mousewheel_status;
    var touch = Drupal.settings.neatScrollbarSet.touch_status;
    var content = Drupal.settings.neatScrollbarSet.content_resize;
    var browser = Drupal.settings.neatScrollbarSet.browser_resize;
    var autoscroll = Drupal.settings.neatScrollbarSet.autoscroll;

// Apply configuration settings.
    $(vertCss + ".neat-scrollbar,.neat-scrollbar-blocks", context).once(function() {
      $(this).mCustomScrollbar({
        theme: theme,
        scrollButtons:{enable: buttons},
        horizontalScroll: false,
        mouseWheel: mouseWheel,
        scrollInertia: inertia,
        autoDraggerLength: dragger,
        contentTouchScroll: touch,
        autoHideScrollbar: autohide,
        advanced:{
        updateOnContentResize: content,
        updateOnBrowserResize: browser,
        autoScrollOnFocus: autoscroll
        }
      });
    });
// Apply configuration settings.
      $(horzCss, context).once(function() {
        $(this).mCustomScrollbar({
        theme: theme,
        scrollButtons:{enable: buttons},
        horizontalScroll: true,
        mouseWheel: mouseWheel,
        scrollInertia: inertia,
        autoDraggerLength: dragger,
        contentTouchScroll: touch,
        autoHideScrollbar: autohide,
        advanced:{
        updateOnContentResize: content,
        updateOnBrowserResize: browser,
        autoScrollOnFocus: autoscroll
        }
      });
    });
  }
};
//end
})(jQuery);
