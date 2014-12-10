jQuery(document).ready(function($) {
  $('#slider').flexslider({
    directionNav: false,
    keyboardNav: false
  });
});
var x = document.getElementById("container"); 
var y= x.getElementsByClassName("slides")[0];
 z= y.getElementsByClassName("entry-header");
  z[0].innerHTML;
   z[0].style.visibility="hidden";
    var z= y.getElementsByClassName("slide-image");
    //z[0].width=500;
    var text = x.getElementsByClassName("entry-container");
    text[0].remove();
    var post = document.getElementsByClassName("post")[0];
    var w = post.offsetWidth;
    var h = post.offsetHeight;
    z[0].width=500;

