/* js menu (uses hoverintent) */

jQuery(document).ready(function($){
		   
var openmenu=null;

var config = {    
     sensitivity: 3, // number = sensitivity threshold (must be 1 or higher)    
     interval: 50, // number = milliseconds for onMouseOver polling interval    
     over: openMenu, // function = onMouseOver callback (REQUIRED)    
     timeout: 300, // number = milliseconds delay before onMouseOut    
     out: closeMenu // function = onMouseOut callback (REQUIRED)    
};


$("div.mega").addClass("open").css('display','none');


function openMenu(){ 
		 
		if(openmenu!=null && openmenu!=this)$("div.mega",openmenu).css('display','none');
		$("div.mega",this).css('display','block');
		openmenu=this;		
}
		

function closeMenu(){
		
		$("div.mega",this).css('display','none');
		
}

$("#navigation-primary ul > li:has('div.mega')").hoverIntent(config);
$("span.close-panel").click(function(){
									
	$("div.mega").fadeOut();
	
});

$("span.close-panel").hover(

	function(){$(this).parents("div.mega").addClass("closing");},
	function(){$(this).parents("div.mega").removeClass("closing");}
	
	);

});



