/**
 *     Content text slider on post
 *     Copyright (C) 2011  www.gopiplus.com
 * 
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 * 
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 * 
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */	

function scrollctsop() {
	objctsop.scrollTop = objctsop.scrollTop + 1;
	ctsop_scrollPos++;
	if ((ctsop_scrollPos%ctsop_heightOfElm) == 0) {
		ctsop_numScrolls--;
		if (ctsop_numScrolls == 0) {
			objctsop.scrollTop = '0';
			ctsopContent();
		} else {
			if (ctsop_scrollOn == 'true') {
				ctsopContent();
			}
		}
	} else {
		setTimeout("scrollctsop();", 10);
	}
}

var IRNum = 0;
/*
Creates amount to show + 1 for the scrolling ability to work
scrollTop is set to top position after each creation
Otherwise the scrolling cannot happen
*/
function ctsopContent() {
	var tmp_IR = '';

	w_IR = IRNum - parseInt(ctsop_numberOfElm);
	if (w_IR < 0) {
		w_IR = 0;
	} else {
		w_IR = w_IR%ctsop.length;
	}
	
	// Show amount of IR
	var elementsTmp_IR = parseInt(ctsop_numberOfElm) + 1;
	for (i_IR = 0; i_IR < elementsTmp_IR; i_IR++) {
		
		tmp_IR += ctsop[w_IR%ctsop.length];
		w_IR++;
	}

	objctsop.innerHTML 	= tmp_IR;	
	IRNum 				= w_IR;
	ctsop_numScrolls 	= ctsop.length;
	objctsop.scrollTop 	= '0';
	// start scrolling
	setTimeout("scrollctsop();", 2000);
}

