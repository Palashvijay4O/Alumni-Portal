(function($){
  
  Drupal.behaviors.MarqueeBlock = {
    attach: function(context, settings) {
      
      var blocks = $('marquee.marquee-block');
      if (blocks.length > 0) {
        blocks.marquee();
      }
      
    }
  };
  
})(jQuery);