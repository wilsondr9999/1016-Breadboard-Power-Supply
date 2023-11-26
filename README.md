# BreadBrick
#### The breadboard power supply *with flair*

![[img/BreadBrick-OutputOn.jpg]]

![[img/KiCad-3DRender.jpg]]

![[img/FreeCAD-Render.jpg]]

## Why Another Breadboard Power Supply?

There's a million of these things out there, and they all work pretty much the same.  They plug in on one end of the breadboard and supply power to the voltage rails.  Many do 5V only, some have switchable 5V / 3.3V using jumpers.  Many use linear power regulators which are not terribly efficient.  Many have substantial voltage droop.  Many can't supply very much current.

I wanted something with a bit more, ummm, pizazz.  I wanted a case, not a bare PCB.  I wanted the ability to set the voltage independently for each rail, indicator lights for what voltages are set, up to 2A / 10W on each rail, and protection circuitry for those times when you plug something into the breadboard backwards.  And some efficiency so the thing doesn't get hot.

It took me a while, but I did it.

## Design

The design of the unit is actually not too complicated, there is an input section for protection and filtering, three [Texas Instruments TPS62130A](https://www.ti.com/product/TPS62130A) switching buck regulator circuits, two for the two power rails, and a 3rd that generates a dedicated 3.3V for the MCU, and an MCU section that uses the [STM32C011F4](https://www.st.com/en/microcontrollers-microprocessors/stm32c011f4.html).  The MCU is used to get user input from the buttons, drive the indicator LEDs, and control and monitor the rail regulators.

All components were selected for reasonable cost and wide availability.  However, the design is at the limit of what a hobbyist can successfully assemble.  While no parts smaller than 0603 are used, some ICs are QFN, and hand soldering these parts can be difficult for the hobbyists.  This board can be assembled by board assembly services at a reasonable cost.

## Tools and Software

Circuit design, schematics, and PCB layout were all done with [KiCad](https://www.kicad.org/).  Design of the case was done in [FreeCAD](https://www.freecad.org/).  Software code for the STM32C0 was written, compiled, and debugged using the [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) development environment.

## Licensing

Several different licenses apply to this repository and the files within.

All schematics and circuit board designs in the project (all KiCad files), as well as all case designs (all FreeCAD files) are licensed under the [[LICENSE-CERN-OHL-S|CERN Open Hardware License Version 2 - Strongly Reciprocal (CERN-OHL-S)]].

All software and firmware code in the project (all ) are licensed under the [[LICENSE-AGPL|GNU Affero General Public License v3.0 (AGPL 3.0)]].

Documentation, Bill of Materials, pictures, and documentation (i.e. all other files not covered by the other two licenses above) are licensed under the [[LICENSE-CC-BY-SA-4.0|Creative Commons Attribution Share Alike 4.0 International License (CC-BY-SA-4.0)]].

These licenses form a very restrictive license for this design and this project.  This is done specifically for a reason.  That reason is that this project is for the hobbyist, and the hobbyist only.  It is for those people who want to have one of these units to be able to make one for themselves.  What it is not for is for some no-name company to produce thousands of them and make money when they had nothing to do with the design and the hard work.  These licenses force anyone who wants to do that to share anything and everything that they derive from this work so that the community and the hobbyists have it also.

## Specifications
- Input Voltage: 7V - 17V
- DC Barrel Jack: 2.5mm ID x 5.5mm OD, Center pin is positive (+)
- Max Input Current: 2A
- Output Voltage: 5V +/- 0.05V, 3.3V +/- 0.05V, switchable per rail
- Output Voltage Ripple: 25 mV at 2A load
- Max Output Current: 2A per rail
- Typical Efficiency: 88.0% at 12V input and 5V / 1A output
- Worst-Case Efficiency: 84.0% at 17V input and 3.3V / 2A output
- Worst-Case heat sink temperature: 51.1 C at full 2A load

![[img/Efficiency-and-Temperature-Performance.png]]

## How To Build
#### Ordering the PCB
To order this PCB, you can submit the [[Fabrication Exports.zip]] file (located in [[KiCAD Project/Fabrication Exports]]) to your favorite PCB manufacturing company.  This is a 2 layer board so costs should be low.
#### Ordering the Stencil
If you want to assemble the board yourself, especially if you want to use a reflow oven, you can order a stencil using the [[1016 Breadboard Power Supply-F_Paste.gbr]] gerber layer.  This layer includes 2.5mm alignment pins on two corners, these are sized and located to fit on the [[1016 v2 Parametric Solder Stencil Jig.3mf|solder stencil jig]] that can be 3D-printed.  If instead you are having a PCB manufacturer assemble the SMD components for you, you do not need the solder stencil.
#### Ordering Parts
If you're assembling yourself, you'll need to order parts.  The [[1016 Breadboard Power Supply.csv]] file located in the [[KiCAD Project/BOM]] folder contains all parts and manufacturer part numbers.
#### Assembling the PCB
The [[ibom.html]] file located in the [[KiCAD Project/BOM]] folder is generated from the [KiCad Interactive BOM plug-in](https://github.com/openscopeproject/InteractiveHtmlBom), and can help you mark which parts have been placed on the board prior to reflow.

Be very careful placing the LEDs.  The silkscreen marks pin 1 of the LED, but in accordance with the [[[DS-006] Wurth Elektronik 150060VS75003.pdf|datasheets]] for the Wurth Elektronik LEDs, the pin 1 marking is NOT the cathode as would normally be expected.

After placing components, reflow the board in a reflow oven, hot plate, or use a hot air station.
#### Through-Hole Components
You will need to solder three through-hole components -- the DC power jack (PJ-102B), and the 2x2 pin headers (J3/J4).
#### Heat Sinks
The two heat sinks are glued onto the back side of the board using thermal adhesive.  Note that this is thermal adhesive (glue), not just an ordinary thermal compound or thermal paste.  The adhesive is required, there is no other mechanical support for the heat sinks.  I successfully used the [Gennel G109 Thermal Conductive Glue](https://www.amazon.com/dp/B072MSXHJD?psc=1&ref=ppx_yo2ov_dt_b_product_details).
#### 3D Printing the Case
The case can be 3D printed using the [[FreeCAD Project/Case/STL/Case Top-Bottom.3mf|Case Top-Bottom.3mf]], [[FreeCAD Project/Case/STL/Case Top-Bottom.3mf|Button.3mf]], and [[FreeCAD Project/Case/STL/LED Lens.3mf|LED Lens.3mf]] files and [PrusaSlicer](https://www.prusa3d.com/page/prusaslicer_424/), or if you want to slice the .stl files yourself, the .stl files are also included in the [[FreeCAD Project/Case/STL]] folder.  Printing settings are as follows:
- 0.12mm Layer Height
- 0.4mm Nozzle
- PETG material, do not use PLA.  The snap-together design needs a flexible plastic, PLA is too brittle and will likely break when trying to snap together the case.  Also, PLA is not as temperature-resistant as PETG, and the heat sinks could cause problems with PLA.
- For the LED lenses, you will need a clear PETG filament.  I have had good results with [PolyMaker PolyLite Clear PETG](https://us.polymaker.com/products/polylite-petg?variant=41266031099961).
- Supports are not required, but both case halves should be printed with their flat surface on the print bed.  You may need to turn the upper case half so that the flat top is on the print bed.  The LED lenses need to be turned so that the larger side is down on the print bed.
- The upper case half prints with a thin bridge covering the LED lens holes, you will need to clean out the bridges with a hobbyist knife prior to inserting the LED lenses.
- It is critical that the buttons are printed to accurate dimensions as the clearances and travel are very small.  Print the buttons at a very slow speed with adequate time for each layer to cool to prevent any warping or distortion.  The .3mf file already has these settings pre-set.
#### Programming Firmware to the STM32
The STM32C011F4 firmware is the [[1016 Breaadboard Power Supply.elf]] file located in the [[STM32 Project/Debug]] folder.  This can be programmed to the STM32C011F4 using the [ST-Link/V2](https://www.st.com/en/development-tools/st-link-v2.html) debugger and the [Tag-Connect ARM20-CTX SWD Solution](https://www.tag-connect.com/debugger-cable-selection-installation-instructions/st-link-v2#49_126_145).  The 6-pin Tag-Connect connector connects with the J2 connector on the PCB, and the [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) software can write the firmware to the MCU.

Note that if you order the Tag-Connect SWD solution, you need the "No-Legs" version of the package that includes the TC-2030-IDC-NL cable.  The version of the cable with legs (TC-2030-IDC) will not properly fit this PCB.
#### Assembling the Unit
Once the PCB has been populated and soldered with the SMD and THT components, the heat sinks are attached with the thermal adhesive, and the case parts have been printed you can assemble the entire unit.
- Turn the upper half of the case upside down, and insert the two buttons, aligning the base of the buttons so that they will fit over the SMD switches on the PCB.
- Place the PCB into the top side of the case with the components towards the buttons and the heat sinks protruding.  Ensure the base of the buttons goes over the SMD switches on the PCB.  Hold the PCB against the support columns with your fingers.
- Test the buttons on the other side of the case and ensure you can feel them actuate the switches and that the switches are NOT pressed when the PCB is seated against the support columns.
- If the switches are not getting pressed when you press the button, the buttons dimensions are too small.  Re-check your print settings.
- If the switches are getting pressed before the PCB is seated against the support columns, the buttons dimensions are too large.  Re-check your print settings.
- Once you are confident that the buttons are the correct size and will work, remove the PCB from the top case half.
- Tape the buttons in place on the top side.  Fold the tape around the protruding button so that the button is at the top of it's travel (most protrusion).
- Insert the PCB into the case bottom with the components up and the heat sinks down.  The heat sinks will fit inside the cooling passages, and the holes in the PCB will fit on the support pins.
- Carefully fit the top half with the taped buttons onto the bottom half, and carefully get the two halves to mate and snap together.
- Remove the tape from the buttons and re-check that the buttons are working properly.  If you need to get the case apart again, you will need to use a spudger to pry the case apart.

## Using the Breadboard Power Supply
Plug the unit into your breadboard into the power rails.  As you're looking at the unit, the power arms/leads should point towards your right.  In this position, the TOP pins of each rail (furthest away from you) are the positive voltage, the BOTTOM pins of each rail (closest to you) are the reference voltage (ground).  Orient your breadboard so that the red/positive row of pins aligns with the positive pin of the unit (away from you).  If your breadboard is turned 180 degrees, the colors of the power rails will be opposite, and will cause confusion.

Power the unit using a DC barrel jack and power supply.  The jack is a standard 2.5mm x 5.5mm DC barrel jack, the center pin is the positive lead.  The unit has reverse power protection, so if your power supply uses ground for the center pin, you will not damage the unit, but it will not power on.  Your power supply should be between 7V and 17V output, and should provide at least 24W of power.  The standard supply that the unit was designed for is a [12V, 2A supply](https://www.amazon.com/Chanzon-Switching-Adapter-100-240V-Transformer/dp/B07HNL5D56/ref=sr_1_19?keywords=12v+2a+power+supply&sr=8-19). 

Once the unit is powered on, it will self-test all LEDs.  You should see them sequentially light.

The left-most LED is the power-on LED, and indicates that input power is being received and is the correct voltage and polarity.  The LED remains green at all times when input power is supplied.

The top and bottom right-most LEDs indicate what voltage has been selected for the top rail and the bottom rail, respectively.  The LED is green when the rail has been selected for 5V output.  The LED is yellow when the rail has been selected for 3.3V output.

To configure the voltage setting, use the top-most button (colored green in the FreeCAD drawings).  Each press of the button cycles between the 4 combinations of rail voltages as follows:
1. Both rails 5V (LEDs green/green).
2. Top rail 3.3V / bottom rail 5V (LEDs yellow/green).
3. Top rail 5V / bottom rail 3.3V (LEDs green/yellow).
4. Both rails 3.3V (LEDs yellow/yellow).

Once you have selected the required voltage for your breadboard, turn the output on by pressing the bottom-most button (colored orange in the FreeCAD drawings).  The middle LED on the right will light orange to indicate that the output is on.  The unit begins monitoring the output power 50 msec after the output is turned on, and monitors the "Power Good" signal from both rail regulators.  If the output is subjected to a short circuit, an overcurrent condition, or the regulator temperatures get too high, the "power no good" signal from the regulators will be sensed and the MCU will turn off the output power, turn off all LEDs, and blink the middle LED red for 5 seconds.  The unit will then reset with the output power off.  This error condition can also occur if the input power source has problems, including undervoltage.  If this occurs, check the ratings on your input power source.

Press the bottom-most button again to turn the output power off on both rails.

The voltage configuration for the rails cannot be changed when the output is on.  When the output is on, pressing the top-most button will have no effect.  You must turn the output off using the bottom-most button before the voltage configuration can be changed.

## Caveats
The unit does **NOT** remember your voltage configuration setting between power cycles.  When input power is cycled, the unit will start up in a 5V/5V configuration.  If your breadboard needs 3.3V power on one or both of the rails, you will need to double-check and change the voltage configuration on each power-up before you turn the output power on.


Enjoy the unit, and happy breadboarding!
