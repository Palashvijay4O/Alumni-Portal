Location Map module (http://drupal.org/project/locationmap)

** Description:
The Location Map module displays a single geographic location for a website via Google Maps. It has following features:

* Creates a single Google Maps page (at http://yoursite.com/locationmap), designed to display one location for the site, with an address marker.
* The map location is automatically geocoded from a street address.
* Anyone with "Administer location map" permissions can drag the marker to further fine-tune its position if geocoding did not place the marker exactly where you wish it to be.
* Creates a block with a static image of the centre of the map, which links to the location map page on your site.

Location map module is simple by design and will remain that way. It creates only a single map for a site. It is not designed to attach locations to nodes, users, or other content. If you wish any of these more extensive features, see the GMap project (http://drupal.org/project/gmap) which is significantly more powerful and is designed to do all of these things.

(Location map is the successor of the Drupal 5.x-6.x module "gmaplocation". The name of the module was changed to reduce confusion with the submodule of the gmap project called gmap_location. On installing Location Map, map configuration data stored by any previous version of gmaplocation, as well as role permissions and any URL aliases to the map page are automatically updated.)

** Credits:
Duncan Babbage (http://wavelength.org.nz), maintainer since the 6.x version of gmaplocation.
Bojan Mihelac (http://source.mihelac.org), original developer of gmaplocation module.