jQuery(function($){
  $(document).ready(function(){
      
    //superFish
    $(function() { 
      $("#main-menu > ul.menu").superfish({
        delay: 100,
        autoArrows: false,
        dropShadows: false,
        animation: {opacity:'show', height:'show'},
        speed: 'fast'
      });
    });
  
  }); // end doc ready
}); // end function