(function($) {
  /*
   * nano Scrollbar Script.
   *
   */
  Drupal.behaviors.nanoScrollbar = {
    attach: function(context, settings) {

      // Ready variables.
      var vertCss = settings.nanoScrollbarSet.vertical_css;
      var alwaysvisible = settings.nanoScrollbarSet.alwaysvisible;
      var scrollpos = settings.nanoScrollbarSet.scrollpos == 0 ? 'top' : 'bottom';
      var flashdelay = settings.nanoScrollbarSet.flashdelay;
      var prevtpagescroll = settings.nanoScrollbarSet.prevtpagescroll;
      var disableResize = settings.nanoScrollbarSet.disableResize;
      var iOSNativeScrolling = settings.nanoScrollbarSet.iOSNativeScrolling;
      var flash = settings.nanoScrollbarSet.flash;
      var destroy = settings.nanoScrollbarSet.destroy;
      var stop = settings.nanoScrollbarSet.stop;
      var mobile_browser = settings.nanoScrollbarSet.mobile_browser;

// Apply configuration settings.
      $(vertCss + ".nano-scrollbar,.nano-scrollbar-blocks", context).once(function() {
        $(this).wrapInner("<div class='content'></div>");
        $(this).nanoScroller({
          contentClass: 'content',
          alwaysVisible: alwaysvisible,
          scroll: scrollpos,
          flashDelay: flashdelay,
          preventPageScrolling: prevtpagescroll,
          disableResize: disableResize,
          iOSNativeScrolling: iOSNativeScrolling,
          flash: flash,
          destroy: destroy,
          stop: stop,
        });
      });
      if (mobile_browser) {
        $(vertCss.split(",").join(" .content,") + ".nano-scrollbar .content,.nano-scrollbar-blocks .content", context).addClass("overthrow");
      }
    }
  };
//end
})(jQuery);
