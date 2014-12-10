jQuery(document).ready(function($){
  var title    = $('img.slide').attr("title");
  var desc      = $('img.slide').attr("longdesc");
  $('#header-image-title').text(title);      // set image title
  $('#header-image-description').text(desc);  // set image description
});