# BreadBrick
#### The breadboard power supply *with flair*


## Why Another Breadboard Power Supply?

There's a million of these things out there, and they all work pretty much the same.  They plug in on one end of the breadboard and supply power to the voltage rails.  Many do 5V only, some have switchable 5V / 3.3V using jumpers.  Many use linear power converters which are not terribly efficient.  Many have substantial voltage droop.  Many can't supply very much current.

I wanted something with a bit more, ummm, pizazz.  I wanted a case, not a bare PCB.  I wanted the ability to set the voltage independently for each rail, indicator lights for what voltages are set, up to 2A / 10W on each rail, and protection circuitry for those times when you plug something into the breadboard backwards.  And some efficiency so the thing doesn't get hot.

It took me a while, but I did it.

## Design

The design of the unit is actually not too complicated, there is an input section for protection and filtering, three Texas Instruments TPS62130A switching buck regulator circuits, two for the two power rails, and a 3rd that generates a dedicated 3.3V for the MCU, and an MCU section that uses the STM32C0.  The MCU is used to get user input from the buttons, drive the indicator LEDs, and control and monitor the rail regulators.

All components were selected for reasonable cost and wide availability.  However, the design is at the limit of what a hobbyist can successfully assemble.  While no parts smaller than 0603 are used, some ICs are QFN, and hand soldering these parts can be difficult for the hobbyists.  This board can be assembled by board assembly services at a reasonable cost.

## Tools and Software

Circuit design, schematics, and PCB layout were all done with [KiCad](https://www.kicad.org/).  Design of the case was done in [FreeCAD](https://www.freecad.org/).  Software code for the STM32C0 was written, compiled, and debugged using the [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) development environment.

## Licensing

Several different licenses apply to this repository and the files within.

All schematics and circuit board designs in the project (all KiCad files), as well as all case designs (all FreeCAD files) are licensed under the CERN Open Hardware License Version 2 - Strongly Reciprocal (CERN-OHL-S).

All software and firmware code in the project (all ) are licensed under the GNU Affero General Public License v3.0 (AGPL 3.0).

Documentation, Bill of Materials, pictures, and documentation (i.e. all other files not covered by the other two licenses above) are licensed under the Creative Commons Attribution Share Alike 4.0 International License (CC-BY-SA-4.0).

These licenses form a very restrictive license for this design and this project.  This is done specifically for a reason.  That reason is that this project is for the hobbyist, and the hobbyist only.  It is for those people who want to have one of these units to be able to make one for themselves.  What it is not for is for some no-name company to produce thousands of them and make money when they had nothing to do with the design and the hard work.  These licenses force anyone who wants to do that to share anything and everything that they derive from this work so that the community and the hobbyists have it also.

## How To Build
#### Ordering the PCB
To order this PCB, you can submit the "Fabrication Exports.zip" file in the "KiCAD Project/Fabrication Exports/" folder to your favorite PCB manufacturing company.  This is a 2 layer board so costs should be low.
#### Ordering the Stencil
If you want to assemble the board yourself, especially if you want to use a reflow oven, you can order a stencil using the F_Paste gerber layer.  This layer includes 2.5mm alignment pins on two corners, these are sized and located to fit on the solder stencil jig that can be 3D-printed.  If instead you are having a PCB manufacturer assemble the SMD components for you, you do not need the solder stencil.
#### Ordering Parts
If you're assembling yourself, you'll need to order parts.  The "KiCAD Project/BOM/1016 Breadboard Power Supply.csv" file contains all parts and manufacturer part numbers.
#### Assembling the PCB
The "KiCAD Project/BOM/ibom.html" file is generated from the KiCad Interactive BOM plug-in, and can help you mark which parts have been placed on the board prior to reflow.

Be very careful placing the LEDs.  The silkscreen marks pin 1 of the LED, but in accordance with the datasheets for the Wurth Elektronik LEDs, the pin 1 marking is NOT the cathode as would normally be expected.

After placing components, reflow the board in a reflow oven, hot plate, or use a hot air station.
#### Through-Hole Components
You will need to solder three through-hole components -- the DC power jack (PJ-102B), and the 2x2 pin headers (J3/J4).
#### Heat Sinks
The two heat sinks are glued onto the back side of the board using thermal adhesive.  Note that this is thermal adhesive (glue), not just an ordinary thermal compound or thermal paste.  The adhesive is required, there is no other mechanical support for the heat sinks.
#### 3D Printing the Case
The case can be 3D printed using the .3mf files and PrusaSlicer, or if you want to slice the .stl files yourself, the .stl files are also included.  Printing settings are as follows:
	- 0.12mm Layer Height
	- 0.4mm Nozzle
	- PETG material, do not use PLA.  The snap-together design needs a flexible plastic, PLA is too brittle and will likely break when trying to snap together the case.  Also, PLA is not as temperature-resistant as PETG, and the heat sinks could cause problems the PLA.
	- For the LED lenses, you will need a clear PETG filament.  I have had good results with PolyMaker PolyLite Clear PETG.
	- Supports are not required, but both case halves should be printed with their flat surface on the print bed.  You may need to turn the upper case half so that the flat top is on the print bed.
	- The upper case half prints with a thin bridge covering the LED lens holes, you will need to clean out the bridges with a hobbyist knife prior to inserting the LED lenses.
	- It is critical that the buttons are printed to accurate dimensions as the clearances and travel are very small.  Print the buttons at a very slow speed with adequate time for each layer to cool to prevent any warping or distortion.  The .3mf file already has these settings pre-set.

#### Programming the STM32
The STM32C0 firmware file is in "STM32 Project/Debug/1016 Breadboard Power Supply.elf".  This can be programmed to the STM32C0 using the [ST-Link/V2](https://www.st.com/en/development-tools/st-link-v2.html) debugger and the [Tag-Connect ARM20-CTX SWD Solution](https://www.tag-connect.com/debugger-cable-selection-installation-instructions/st-link-v2#49_126_145).  The 6-pin Tag-Connect connector connects with the 

#### Assembling the Unit
Once the PCB has been populated and soldered with the SMD and THT components, the heat sinks are attached with the thermal adhesive, and the case parts have been printed you can assemble the entire unit.
	- Turn the upper half of the case upside down, and insert the two buttons, aligning the base of the buttons so that they will fit over the SMD switches on the PCB.  Tape the buttons in place on the top side.  Fold the tape around the protruding button so that the button is at the top of it's travel (most protrusion).
	- Insert the PCB into the case bottom, the heat sinks will fit inside the cooling passages, and the holes in the PCB will fit on the support pins.