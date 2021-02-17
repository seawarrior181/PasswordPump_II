//	PasswordPumpV2Box v6
//
//		By: scootercommuter
//
//		License: Creative Commons, Attribution
//
//		Updates for v6.1
//			In this version, do not modify object geometry.
//			Do comment and code cleanup.
//		Changes in v6.0
//			Parameterize mount holes, countersinks and standoffs

use <MCAD/boxes.scad>
$fa=1;
$fs=0.4;

create_box = false; 
create_lid = true;

part_separation = 5;	//	if generating both parts in one STL, 
								//	separate them by this y distance

//		=  =  =  =  =  =  =  =  =  =  =  =
//		Dimensions for the Lid and Holes
//		=  =  =  =  =  =  =  =  =  =  =  =

lid_h			= 5;			// total lid height
ltop_h		= 1.2;		// height (thickness) of top of lid
lid_wall	= 1.2;		// thickness of the lid wall
lid_slack	= 0.2;		// how tight the lid fits

//		LCD window
lcdw_l = 24.6;
lcdw_w = 9.5;
lcd_l_offset =  1.6;		// center of board (x) to right edge of lcd window
lcd_w_offset = -5.5;		// center of board (y) to lower edge of lcd window

//		Knob hole
kh_d = 16.2;
kh_l_offset = -26.425;	// center of board (x) to center of knob hole
kh_w_offset = -2.6;		// center of board (y) to center of knob hole

//		LED hole
ledh_d = 4.55;
ledh_l_offset = -31.6;
ledh_w_offset =  8.875;

//		=  =  =  =  =  =  =  =
//		Dimensions for the Box
//		=  =  =  =  =  =  =  =

wall_w   = 1.4; // thickness of box case walls
c_radius = 2; 	// corner curve radius

//		circuit board dimensions
//
board_l       = 75.75;
board_w       = 27.45;
board_h       = 1.5;	 // thickness of circuit board
board_holes_l = 70.5; // center distance between board mounting holes
board_holes_w = 22;
board_slack   = 1.0;	 // edge of board to inside wall of box (per side)
top_slack     = 0.8;	 // top of screen to inside top of box
screen_offset = 10;	 // top of circuit board to top of screen

reset_button_offset_r = 10.2;		// right edge of board to center of reset button
reset_button_hole_dia = 3.75;

usb_cutout_offset = 5.75; // offset, horiz center of USB cutout above top of board
cable_housing_l = 9.95;   // supplied USB cable housing size
cable_housing_w = 6.50; 
housing_slack   = 1.0;    // clearance from edge of cable housing to hole edge

standoff_h = 5;
standoff_d = 5;			// max possible diameter to avoid running into board parts
standoff_hole = 2.4;	// drill for M2 screws

countersink_d = 5;			// countersink diameter for M2 hex nut
countersink_h = 2.2;		// countersink height for M2 hex nut thickness;
									// Actual s/b 1.6, increased since 8mm screws are too short.

bottom_h = 2.5; // thickness of bottom, must be greater than countersink height

//  =  =  =  =  =  =  =  =  =
//  =  End of Definitions   =
//  =  =  =  =  =  =  =  =  =

box_l = board_l + (wall_w * 2) + (board_slack * 2);
box_w = board_w + (wall_w * 2) + (board_slack * 2);
box_h = bottom_h + standoff_h + board_h + screen_offset + top_slack;

lid_l = box_l + (lid_wall * 2) + lid_slack;
lid_w = box_w + (lid_wall * 2) + lid_slack;

if (create_box == true) make_box();
if (create_lid == true) make_lid();

module make_box() {
	difference () {
		// Outside of box
		roundedBox(size=[box_l, box_w, box_h], radius = c_radius, sidesonly=true);
		// cutout inner box to create hollow box
		//		(inner box cutout has square corners to fit the circuit board corners)
		translate([0, 0, bottom_h])
			cube(size = [box_l - (wall_w * 2), 
									   box_w - (wall_w * 2),
									   box_h],center=true);
		// cut counter-sink holes for hex nuts, and round holes for screws
		mount_hole( board_holes_l/2,  board_holes_w/2, -box_h/2 );
		mount_hole( board_holes_l/2, -board_holes_w/2, -box_h/2 );
		mount_hole(-board_holes_l/2,  board_holes_w/2, -box_h/2 );
		mount_hole(-board_holes_l/2, -board_holes_w/2, -box_h/2 );

		// cut reset button hole
		translate([board_l / 2 - reset_button_offset_r, 0, -box_h / 2 - .001])
			cylinder(h = bottom_h + .002, r = reset_button_hole_dia/2);
		// cut USB cable hole
		translate([ (box_l - 2*wall_w)/2, 0,
							(-box_h / 2) + bottom_h + standoff_h + board_h + usb_cutout_offset ])
			rotate([90, 0, 90])
			roundedBox(size=[cable_housing_l + housing_slack,
									 cable_housing_w + housing_slack,
									 wall_w*2 + .002],
						   radius = c_radius, sidesonly=true);
	} // end difference()
	
	//	generate standoffs
	make_standoff( board_holes_l/2,  board_holes_w/2, -box_h/2 + countersink_h );
	make_standoff( board_holes_l/2, -board_holes_w/2, -box_h/2 + countersink_h );
	make_standoff(-board_holes_l/2,  board_holes_w/2, -box_h/2 + countersink_h );
	make_standoff(-board_holes_l/2, -board_holes_w/2, -box_h/2 + countersink_h );

}	// end module make_box

module mount_hole(x, y, z) {
	// countersink hex nut hole and cut through-hole for M2 screw
	translate([x, y, z - .001])
		cylinder(h=countersink_h + .001, r=countersink_d/2, $fn=6);
	translate([x, y, z - .001])
		cylinder(h=bottom_h + countersink_h + .002, r=standoff_hole/2);
} // end module mount_holes

module make_standoff(x, y, z) {
	difference() {
		translate([x, y, z])	// puts us at the top of the contersink cutout
			cylinder(h=standoff_h + bottom_h - countersink_h, r=standoff_d/2);
		translate([x, y, z - .001])
			cylinder(h=standoff_h + bottom_h - countersink_h + .002, r=standoff_hole/2);
	}
} // end module make_standoff

module make_lid() {
	// if we're generating both box AND lid, offset the lid by part_separation (y),
	//	set z origin to same origin as the box part, so they sit on the same base plane.
	y_move = create_box==true ? -box_w - part_separation : 0;
	z_move = create_box==true ? -box_h/2 + lid_h/2 : 0;

	translate([0, y_move, z_move])
		difference() {
			// Outside of lid
			roundedBox( size=[lid_l, lid_w, lid_h], radius = c_radius, sidesonly=true );
			// inside lid box cutout
			translate([0, 0, ltop_h])
				roundedBox(size=[ lid_l - 2*lid_wall,
										  lid_w - 2*lid_wall, lid_h],
					radius = c_radius, sidesonly=true);
			// lcd window cutout
			translate([ lcd_l_offset, lcd_w_offset, -lid_h/2 - .001 ])
				cube([lcdw_l, lcdw_w, ltop_h + .002]);
			// knob hole
			translate([ kh_l_offset, kh_w_offset, -lid_h/2 - .001 ])
				cylinder(h=ltop_h + .002, r=kh_d/2);
			// led hole
			translate([ ledh_l_offset, ledh_w_offset, -lid_h/2 - .001 ])
				cylinder(h=ltop_h + .002, r=ledh_d/2);
			// USB cable cutout
			translate([ (lid_l/2 - lid_wall) - .001, 0,
							lid_h/2 + 1 ])
				rotate([90, 0, 90])
				roundedBox(size=[cable_housing_l + housing_slack,
										 cable_housing_w + housing_slack,
										 lid_wall*2 + .004],
							   radius = c_radius, sidesonly=true);
		}
}	// end module make_lid
