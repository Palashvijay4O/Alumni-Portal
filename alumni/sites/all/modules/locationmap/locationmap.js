(function($){
  Drupal.behaviors.locationmap = {
    attach: function(context, settings) {
      var target_point = new google.maps.LatLng(Drupal.settings.locationmap.lat, Drupal.settings.locationmap.lng);

      var mapOptions = {
        zoom: parseInt(Drupal.settings.locationmap.zoom),
        center: target_point,
        mapTypeId: eval(Drupal.settings.locationmap.type),
        mapTypeControl: true
        };

      var map = new google.maps.Map(document.getElementById("locationmap_map"), mapOptions);

      var markerOptions = {
        position: target_point,
        draggable: Drupal.settings.locationmap.admin,
        map: map
      };

      var marker = new google.maps.Marker(markerOptions);

      var infowindow = new google.maps.InfoWindow({
        content: Drupal.settings.locationmap.info
      });

      google.maps.event.addListener(marker, 'click', function() {
        infowindow.open(map, marker);
      });

      // Allow fine tuning of the marker position in admin mode.
      if (Drupal.settings.locationmap.admin) {

        google.maps.event.addListener(marker, 'dragend', function(event) {
          $('#edit-locationmap-lat').val(event.latLng.lat());
          $('#edit-locationmap-lng').val(event.latLng.lng());
        });

        google.maps.event.addListener(map, 'zoom_changed', function(event) {
          $('#edit-locationmap-zoom').val(map.getZoom());
        });
      }
    }
  };
})(jQuery);