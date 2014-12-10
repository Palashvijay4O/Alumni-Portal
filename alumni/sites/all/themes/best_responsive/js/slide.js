jQuery(document).ready(function($){
  $(window).load(function() {
    $("#single-post-slider").flexslider({
      animation: 'slide',
      slideshow: true,
      controlNav: false,
      prevText: '<',
      nextText: '>',
      smoothHeight: true,
      start: function(slider) {
        slider.container.click(function(e) {
          if( !slider.animating ) {
            slider.flexAnimate( slider.getTarget('next') );
          }
        });
      }
    });
  });
});